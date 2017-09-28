
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 *
 * @author jmgimeno
 */
public class TimeTeller {

    private final SimpleDateFormat hourFormat;
    private final SimpleDateFormat minuteFormat;
    private final SimpleDateFormat secondsFormat; 
    
    public TimeTeller() {
        hourFormat = new SimpleDateFormat("HH");
        minuteFormat = new SimpleDateFormat("mm");
        secondsFormat = new SimpleDateFormat("ss");
    }
    
    public int getHours() {
        return extractUsingFormat(hourFormat);
    }
    
    public int getMinutes() {
        return extractUsingFormat(minuteFormat);
    }

    public int getSeconds() {
        return extractUsingFormat(secondsFormat);
    }
    
    private int extractUsingFormat(SimpleDateFormat format) {
        Date now = getNow();
        String hours = format.format(now);
        return Integer.parseInt(hours);
    }
    
    private Date getNow() {
        Calendar cal = Calendar.getInstance();
        return cal.getTime();
    }
}