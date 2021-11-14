package model;

/**
 * Class that creates exceptions if the party data provided is invalid.
 * Only contains constructors for parent class Exception.
 * @author Mika Ong
 *
 */
@SuppressWarnings("serial")
public class InvalidPartyDataException extends java.lang.Exception {
	
	/**
	 * Basic Constructor
	 */
	public InvalidPartyDataException() {
		super();
	}
	
	/**
	 * Constructor with message
	 * @param message error message 
	 */
	public InvalidPartyDataException(String message) {
		super(message);
	}
	
	/**
	 * Constructor with message and cause of exception
	 * @param message error message
	 * @param cause for exception
	 */
	public InvalidPartyDataException(String message, Throwable cause) {
		super(message, cause);
	}
	
	/**
	 * Constructor with error message, cause, if suppression is allowed and if a stack trace should be made.
	 * @param message error message
	 * @param cause cause of exception
	 * @param enableSuppression if suppression is allowed
	 * @param writableStackTrace if a stacktrace should be printed
	 */
	protected InvalidPartyDataException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}
	
	/**
	 * Constructor with cause of exception
	 * @param cause cause of exception
	 */
	public InvalidPartyDataException(Throwable cause) {
		super(cause);
	}
}
