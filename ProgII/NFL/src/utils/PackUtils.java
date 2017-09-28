package utils;

/**
 * This class provides static methods for packing and unpacking
 * some primitive types (char, int, long and double) and Strings
 * (limiting their maximum length).
 *
 * The ordering of bytes has been chosen to be the same, when possible,
 * to that used by classes java.io.DataOutput and java.io.DataInput.
 *
 * @author jmgimeno
 */

public class PackUtils {

    /**
     * Writes a boolean in the given position of the given byte array.
     * 
     * @param b the boolean to be written on the buffer at position offset
     * @param buffer the byte array where the boolean is to be written 
     * @param offset the position in the array where the boolean is written
     */
    public static void packBoolean(boolean b, byte[] buffer, int offset) {
        if (b) {
            buffer[offset] = (byte) 1;
        } else {
            buffer[offset] = (byte) 0;
        }
    }

    /**
     * Reads a boolean from the given position of the given byte array.
     * 
     * @param buffer the byte array from where the boolean is to be read 
     * @param offset the position in the array where the boolean is read
     * @return the boolean that has been read
     */
    public static boolean unpackBoolean(byte[] buffer, int offset) {
        return buffer[offset] == (byte) 1;
    }
    
     /**
     * Writes a char in the two bytes starting at the given position 
     * of the given byte array. 
     * 
     * The char is laid out with the most significant byte first in the array.
     * 
     * @param c the char to be written on the buffer beginning at position offset
     * @param buffer the byte array where the boolean is to be written 
     * @param offset the starting position in the array where the char is written
     */
    public static void packChar(char c, byte[] buffer, int offset) {
        buffer[offset    ] = (byte) (c >> 8);
        buffer[offset + 1] = (byte)  c;
    }

    /**
     * Reads a char in the two bytes starting at the given position in the given array.
     * 
     * The char is laid out with the most significant byte first in the array.
     * 
     * @param buffer the byte array from where the char is to be read 
     * @param offset the position in the array where the char is read
     * @return the char that has been read
     */
    public static char unpackChar(byte[] buffer, int offset) {
        return (char) (((buffer[offset    ]       ) << 8) |
                       ((buffer[offset + 1] & 0xFF)     )) ;
    }

    /**
     * Writes, al most, the first maxLenght characters of the String starting 
     * at the given position in the given array.
     * 
     * @param str the string from wich the characters are read
     * @param maxLength the maximum number of characters to consider
     * @param buffer the byte array where the characters are written
     * @param offset the starting position in the array where the characters are
     * written.
     */
    public static void packLimitedString(
            String str, int maxLength, byte[] buffer, int offset) {

        for (int i = 0; i < maxLength; i++) {
            if ( i < str.length() ) {
                packChar(str.charAt(i), buffer, offset+2*i);
            } else {
                // We mark with a zero
                packChar('\0', buffer, offset+2*i);
                break;
            }
        }
    }

    /**
     * Reads, at most, maxLenghth characters tarting at the given position in 
     * the given array.
     * 
     * @param maxLength the maximum number of characters to consider
     * @param buffer the byte array from where the characters are to be read 
     * @param offset the starting position in the array from where the 
     * characters are read.
     * @return the String that has been read.
     */
    public static String unpackLimitedString(
            int maxLength, byte[] buffer, int offset) {
        
        String result = "";
        for (int i = 0; i < maxLength; i++ ) {
            char c = unpackChar(buffer, offset+2*i);
            if ( c != '\0' ) {
                result += c;
            } else {
                break;
            }
        }
        return result;
    }
    
    /**
     * Writes a int in the four bytes starting at the given position 
     * of the given byte array. 
     * 
     * The int is laid out with the most significant byte first in the array.
     * 
     * @param n the int to be written on the buffer beginning at position offset
     * @param buffer the byte array where the int is to be written 
     * @param offset the starting position in the array where the int is written
     */
    public static void packInt(int n, byte[] buffer, int offset ) {
        buffer[offset    ] = (byte) (n >> 24);
        buffer[offset + 1] = (byte) (n >> 16);
        buffer[offset + 2] = (byte) (n >>  8);
        buffer[offset + 3] = (byte)  n       ;
    }
    
    /**
     * Reads a int in the four bytes starting at the given position in the given array.
     * 
     * The int is laid out with the most significant byte first in the array.
     * 
     * @param buffer the byte array from where the int is to be read 
     * @param offset the position in the array where the int is read
     * @return the int that has been read
     */
    public static int unpackInt(byte[] buffer, int offset) {
        return ((buffer[offset    ]       ) << 24) |
               ((buffer[offset + 1] & 0xFF) << 16) |
               ((buffer[offset + 2] & 0xFF) <<  8) |
               ((buffer[offset + 3] & 0xFF)      ) ;
    }

    /**
     * Writes a long in the eight bytes starting at the given position 
     * of the given byte array. 
     * 
     * The char is laid out with the most significant byte first in the array.
     * 
     * @param n the char to be written on the buffer beginning at position offset
     * @param buffer the byte array where the char is to be written 
     * @param offset the starting position in the array where the char is written
     */
    public static void packLong(long n, byte[] buffer, int offset)  {
//        int high = (int) (n >> 32);
//        int low = (int) n;
//        packInt(high, buffer, offset);
//        packInt(low, buffer, offset+4);
        buffer[offset    ] = (byte) (n >> 56);
        buffer[offset + 1] = (byte) (n >> 48);
        buffer[offset + 2] = (byte) (n >> 40);
        buffer[offset + 3] = (byte) (n >> 32);
        buffer[offset + 4] = (byte) (n >> 24);
        buffer[offset + 5] = (byte) (n >> 16);
        buffer[offset + 6] = (byte) (n >>  8);
        buffer[offset + 7] = (byte)  n       ;
    }

    /**
     * Reads a long in the eight bytes starting at the given position in the given array.
     * 
     * The long is laid out with the most significant byte first in the array.
     * 
     * @param buffer the byte array from where the long is to be read 
     * @param offset the position in the array where the long is read
     * @return the long that has been read
     */
    public static long unpackLong(byte[] buffer, int offset) {
//        int high = unpackInt(buffer, offset);
//        int low = unpackInt(buffer, offset + 4);
//        return  ((long)high << 32) | (low & 0xFFFFFFFFL);
        return ((long)(buffer[offset    ]       ) << 56) |
               ((long)(buffer[offset + 1] & 0xFF) << 48) |
               ((long)(buffer[offset + 2] & 0xFF) << 40) |
               ((long)(buffer[offset + 3] & 0xFF) << 32) |
               ((long)(buffer[offset + 4] & 0xFF) << 24) |
               ((long)(buffer[offset + 5] & 0xFF) << 16) |
               ((long)(buffer[offset + 6] & 0xFF) <<  8) |
               ((long)(buffer[offset + 7] & 0xFF)      ) ;
    }

    /**
     * Writes a float in the four bytes starting at the given position 
     * of the given byte array. 
     * 
     * @param f the float to be written on the buffer beginning at position offset
     * @param buffer the byte array where the float is to be written 
     * @param offset the starting position in the array where the float is written
     */
    public static void packFloat(float f, byte[] buffer, int offset) {
        int bits = Float.floatToIntBits(f);
        packInt(bits, buffer, offset);
    }

    /**
     * Reads a float in the four bytes starting at the given position in the given array.
     * 
     * The char is laid out with the most significant byte first in the array.
     * 
     * @param buffer the byte array from where the char is to be read 
     * @param offset the position in the array where the char is read
     * @return the char that has been read
     */
    public static float unpackFloat(byte[] buffer, int offset) {
        int bits = unpackInt(buffer, offset);
        return Float.intBitsToFloat(bits);
    }
    
    /**
     * Writes a double in the eight bytes starting at the given position 
     * of the given byte array. 
     * 
     * @param d the double to be written on the buffer beginning at position offset
     * @param buffer the byte array where the double is to be written 
     * @param offset the starting position in the array where the double is written
     */
    public static void packDouble(double d, byte[] buffer, int offset) {
        long bits = Double.doubleToLongBits(d);
        packLong(bits, buffer, offset);
    }

    /**
     * Reads a double in the eight bytes starting at the given position in the given array.
     * 
     * The double is laid out with the most significant byte first in the array.
     * 
     * @param buffer the byte array from where the double is to be read 
     * @param offset the position in the array where the double is read
     * @return the double that has been read
     */
    public static double unpackDouble(byte[] buffer, int offset) {
        long bits = unpackLong(buffer, offset);
        return Double.longBitsToDouble(bits);
    }
}
