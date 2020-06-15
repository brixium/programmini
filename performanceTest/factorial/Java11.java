public class Java11{
	public static void main (String [] args){
		long val;
		val = 19;

		System.out.println( factorial(val) );
		return;
	}

	public static long factorial(long n){
		if(n == 0)
			return 1;
		return n * factorial(n-1);
	}
}
