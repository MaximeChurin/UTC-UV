
import acm.program.ConsoleProgram;
import java.util.Arrays;

/**
 * Implementations of infinite precision naturals using arrays of ints
 * 
 * - Each position in the array corresponds to a digit (between 0 and 9)
 * - Least significative digit on pos 0
 * - No 0's allowed on the front (except for the case of number 0)
 * 
 * @author jmgimeno
 */

public class BigNaturals extends ConsoleProgram {
    
    public int[] zero() {
        int[] zero = new int[] {0};
        return zero;
    }
    
    public int[] one() {
        int[] one = new int[] {1};
        return one;
    }
    
    public boolean equals(int[] number1, int[] number2) {
        //verificacion de length
        if (number1.length==number2.length){
            boolean equals = true;
            for (int i=0;i<number1.length;i++){
                //test de igualdad y cambio del boolean y salgo del bucle for
                if (number1[i]!=number2[i]){
                    i=number1.length;
                    equals=false;                    
                }
            }
            return equals;
        }
        else{
            return false;
        }
    }
    ///* Version optimizada
    public int[] add(int[] num1, int[] num2) {
        //Encontrar el array mas grande
        int[] max = num1;
        int talla=num1.length-num2.length;
        
        if(talla<0){
            max= num2;
            talla=-talla;
        }
        
        int temp=0;
        int add=0;
        
        //Hacer la suma hasta el mas pequeno de los dos y despues solamente el mayor de los dos
        for (int i=0;i<max.length;i++){
            
            if(i<max.length-talla){
                add = num1[i]+num2[i]+temp;  
            }
            else{
                add =max[i]+temp;
            }
            
            if (add>9){
                max[i]=add-10;
                temp=1;
            }
            else {
                max[i]=add;                
                temp=0;                
            }
        }
        
        //En el caso donde la ultima suma es mas grande que 9 creo un nuevo array con una posicion max
        if (temp==1){
            int[] sum=new int[max.length+1];
            //System.arraycopy(max, 0, sum, 0, max.length);
            for(int i=0;i<max.length;i++){
                sum[i]= max[i];
            }
            sum[max.length]=temp;
            return sum;
        }
        else {
            return max;
        }
    }
    //*/
    /*  Version primera  
    public int[] add(int[] num1, int[] num2) {
        //Encontrar el max y min para crear el array y leer las entradas     
        int max= num1.length;
        int min= num2.length;
    
        if(num1.length<num2.length){
            max= num2.length;   
            min= num1.length;
        }
        int[] array = new int[max];
        int temp=0;
        int add=0;
        
        //Hacer la suma hasta el mas pequeno de los dos y despues solamente el mayor de los dos
        for (int i=0;i<max;i++){
    
            if(i<min){
                add = num1[i]+num2[i]+temp;  
            }
            else{
                if (num2.length>num1.length){
                    add =num2[i]+temp;
                }
                else{
                    add =num1[i]+temp;
                }
            }
            
            if (add>9){
                array[i]=add-10;
                temp=1;
            }
            else {
                array[i]=add;              
                temp=0;                
            }
        }
        
        if (temp==1){
            int[] sum=new int[max+1];
            for(int i=0;i<max;i++){
                sum[i]= array[i];
            }
            sum[max]=temp;
            return sum;
        }
        else {
            return array;
        }
    }
    */
        
    public int[] shiftLeft(int[] number, int positions) {
        //caso number igual a 0
        if(equals(number,zero())){
            return number;
        }
        //creo el nuevo array con bueno numero de positiones nuevas
        else{
            int[] shiftleft = new int[number.length+positions];
            for(int i=0;i<shiftleft.length;i++){
                //Caso de los 0
                if (i<positions){
                    shiftleft[i]=0;
                }
                //Copiar el string initial
                else{
                    shiftleft[i]=number[i-positions];
                }
            }
            return shiftleft;
        }
    }

    public int[] multByDigit(int[] number, int digit) {
        //El caso de los dos zero
        if(equals(number,zero()) || digit==0){
            return zero();
        }
        //La multiplicacion con la suma
        else{
            int[] producto = new int[number.length];
            int[] calc = new int[2];
            int[] temp = new int[2];
            
            for(int i=0;i<number.length;i++){
                temp[0]=number[i];
                for(int n=0;n<digit;n++){
                    calc=add(calc,temp);                   
                }
                producto[i]=calc[0];
                calc[0]=calc[1];
                calc[1]=0;   
            }
            
            //En el caso donde la ultima multiplicacion es mas grande que 9 creo un nuevo array con una posicion max
            if (calc[0]!=0){
                int[] mult=new int[number.length+1];
                for(int i=0;i<number.length;i++){
                    mult[i]= producto[i];
                }
                mult[number.length]=calc[0];
                return mult;
            }
            else {
                return producto;
            }
        }
    } 
        
    public int[] mult(int[] number1, int[] number2) {
        //El caso de los arrays iguales a 0
        if(equals(number1,zero()) || equals(number2,zero())){
            return zero();
        }
        //La multiplicacion con la suma
        else{
            int[] sum=new int[number1.length];
            for(int i=0;i<number2.length;i++){
                //elegir el digit para utilizar multByDigit()
                int escalar=number2[i];
                int[]temp= multByDigit(number1, escalar);
                //Poner a la izquierda segun la escala de la multiplicacion
                int[]move=shiftLeft(temp, i);
                //Sumar al presente resultado
                sum=add(sum, move);
            }
            return sum;       
        }
    }

    public int[] factorial(int[] number) {
        //El caso del zero
        if(equals(number,zero()) ){
            return one();
        }
        //Caso>0
        else{
            //Initializacion
            int[] fact=new int[]{1};
            int[] sum=one();
            //Condicion de salida
            while(! equals(sum,number)){
                //Incrementacion de sum y multiplicacion
                sum=add(one(),sum);
                fact=mult(fact,sum);
            }
            return fact;
        }
    }
    
    public void run() {
        
        testFromString();
        testAsString();
        testZero();
        testOne();
        testEquals();
        testAdd();
        testShiftLeft();
        testMultByDigit();
        testMultiply();
        testFactorial();
    }
        
    // -----
    // TESTS 
    // -----
    
    // Functions for simplifying vector tests.
    
    public int[] fromString(String number) {
        // "25"  -> {5, 2}
        // "1"   -> {1}
        
        //Transforma en array
        int[] digits = new int[number.length()];
        
        
        for (int i = 0; i < number.length(); i++) {
            //number.substring(i, i+1) equivalente a CharAt()
            String digit = number.substring(i, i+1);
            
            //Para poner de la derecha a la izquieda
            digits[number.length()-i-1] = Integer.parseInt(digit);
        }
        return digits;
    }

    private void testFromString() {
        println("Inicio de las pruebas de fromString");
        if ( ! Arrays.equals(new int[] {5, 2}, fromString("25")) ) {
            println("Error en el caso \"25\"");
        }
        if ( ! Arrays.equals(new int[] {1}, fromString("1")) ) {
            println("Error en el caso \"1\"");
        }
        println("Final de las pruebas de fromString");
    }
        
    public String asString(int[] ints) {
        // {1}    -> "1"
        // {5, 2} -> "25"
        char[] intToChar = 
                new char[] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        //Recupera la talla del array
        char[] chars = new char[ints.length];
        //Ver uno a uno los elemetos del array
        for (int i = 0; i < chars.length; i++) {
            //pone en el nuevo array la cosa que tiene en el array ints mas 
            //a la derecha hasta la izquierda gracias al array intTOChar
            chars[i] = intToChar[ints[ints.length - i - 1]];
            
        }
        //Da un String
        return new String(chars);
    }
    
    private void testAsString() {
        println("Inicio de las pruebas de asString");
        if ( ! "25".equals( asString(new int[] {5, 2}) ) ) {
            println("Error en el caso int[] {5, 2}");
        }
        if ( ! "1".equals( asString(new int[] {1}) ) ) {
            println("Error en el caso int[] {1}");
        }
        println("Final de las pruebas de asString");
    }

   
    private void testZero() {
        println("Inicio de las pruebas de zero");
        if ( ! "0".equals(asString(zero())) ) {
            println("Error en la función zero");
        }
        println("Final de las pruebas de zero");
    }
    
    private void testOne() {
        println("Inicio de las pruebas de one");
        if ( ! "1".equals(asString(one())) ) {
            println("Error en la función one");
        }
        println("Final de las pruebas de one");
    }
    
    private void testEquals() {
        println("Inicio de las pruebas de equals");
        if ( equals(zero(), one()) ) {
            println("Error en el caso 0 != 1");
        }
        if (! equals(one(), one()) ) {
            println("Error en el caso 1 = 1");
        }
        if (! equals(fromString("12345"), fromString("12345")) ) {
            println("Error en el caso 12345 = 12345");
        }
        println("Final de las pruebas de equals");
    }
    
    private boolean checkAdd(String number1, String number2, String result) {
        return Arrays.equals(add(fromString(number1), fromString(number2)),fromString(result));
    }
    
    private void testAdd() {
        println("Inicio de las pruebas de add");
        if ( ! checkAdd("1", "1", "2") ) {
            println("Error en la suma 1 + 1 = 2");
        }
        if ( ! checkAdd("5", "5", "10") ) {
            println("Error en la suma 5 + 5 = 10");
        }
        if ( ! checkAdd("99", "999", "1098") ) {
            println("Error en la suma 99 + 999 = 1098");
        }
        if ( ! checkAdd("999", "99", "1098") ) {
            println("Error en la suma 999 + 99 = 1098");
        }
        if ( ! checkAdd("5", "0", "5") ) {
            println("Error en la suma 5 + 0 = 5");
        }
        println("Final de las pruebas de add");
    }
    
    private boolean checkShiftLeft(String number, int exponent, String result) {
        return Arrays.equals(shiftLeft(fromString(number), exponent), 
                             fromString(result));
    }
    
    private void testShiftLeft() {
        println("Inicio de las pruebas de shiftLeft");
        if ( ! checkShiftLeft("54", 1, "540") ) {
            println("Error en 54 1 posición a la izquierda = 540");
        }
        if ( ! checkShiftLeft("54", 3, "54000") ) {
            println("Error en 54 3 posiciones a la izquierda = 54000");
        }
        if ( ! checkShiftLeft("0", 3, "0") ) {
            println("Error en 0 3 posiciones a la izquierda = 0");
        }
        println("Final de las pruebas de shiftLeft");
    }
    
    
    private boolean checkMultByDigit(String number, int digit, String result) {
        return Arrays.equals(multByDigit(fromString(number), digit), 
                             fromString(result));
    }
    
    private void testMultByDigit() {
        println("Inicio de las pruebas de multByDigit");
        if ( ! checkMultByDigit("24", 2, "48") ) {
            println("Error en 24 * 2 = 48");
        }
        if ( ! checkMultByDigit("54", 3, "162") ) {
            println("Error en 54 * 3 = 162");
        }
        if ( ! checkMultByDigit("0", 3, "0") ) {
            println("Error en 0 * 3 = 0");
        }
        if ( ! checkMultByDigit("24", 0, "0") ) {
            println("Error en 24 * 0 = 0");
        }
        println("Final de las pruebas de multByDigit");        
    }
 
    private boolean checkMultiply(String number1, String number2, String result) {
        return Arrays.equals(mult(fromString(number1), fromString(number2)), 
                             fromString(result));
    }
    
    private void testMultiply() {
        println("Inicio de las pruebas de mult");
        if (! checkMultiply("2", "3", "6") ) {
            println("Error en 2 * 3 = 6");
        }
        if (! checkMultiply("999", "888", "887112") ) {
            println("Error en 999 * 888 = 887112");
        }
        if (! checkMultiply("999", "0", "0") ) {
            println("Error en 999 * 0 = 0");
        }
        if (! checkMultiply("0", "888", "0") ) {
            println("Error en 0 * 888 = 0");
        }
        println("Final de las pruebas de mult");
    }

    
    private boolean checkFactorial(String number, String result) {
        return Arrays.equals(factorial(fromString(number)), fromString(result));
    }
    
    private void testFactorial() {
        println("Inicio de las pruebas de factorial");
        if (! checkFactorial("5", "120")) {
            println("Error en 5! = 120");
        }
        if (! checkFactorial("0", "1")) {
            println("Error en 0! = 1");
        }
        if (! checkFactorial("42", "1405006117752879898543142606244511569936384000000000")) {
            println("Error en 42! = 1405006117752879898543142606244511569936384000000000");
        }
        println("Final de las pruebas de factorial");
    }
    

}