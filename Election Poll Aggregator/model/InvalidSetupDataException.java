package model;

/**
 * Class that creates exceptions if the pollList is provided with invalid data.
 * This exception class only contains constructors from its parent class.
 * @author Anay Bhutoria
 */
@SuppressWarnings("serial")
public class InvalidSetupDataException extends Exception {
	
	/**
	 * The default constructor for the exception
	 */
	public InvalidSetupDataException() {
		// TODO Auto-generated constructor stub
	}
	
	/**
	 * The constructor that calls the parent class
	 * @param message to send to parent
	 */
	public InvalidSetupDataException(String message) {
		super(message);
		// TODO Auto-generated constructor stub
	}
	/**
	 * The constructor that calls the parent class
	 * @param cause to send to parent
	 */
	public InvalidSetupDataException(Throwable cause) {
		super(cause);
		// TODO Auto-generated constructor stub
	}
	
	/**
	 * The constructor that calls the parent class
	 * @param message to send to parent class
	 * @param cause to send to parent class
	 */
	public InvalidSetupDataException(String message, Throwable cause) {
		super(message, cause);
		// TODO Auto-generated constructor stub
	}
	/**
	 * The default constructor for the exception
	 * @param message to send to parent class
	 * @param cause to send to parent class
	 * @param enableSuppression to send to parent class
	 * @param writableStackTrace to send to parent class
	 */
	public InvalidSetupDataException(String message, Throwable cause, boolean enableSuppression,
			boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
		// TODO Auto-generated constructor stub
	}

}
