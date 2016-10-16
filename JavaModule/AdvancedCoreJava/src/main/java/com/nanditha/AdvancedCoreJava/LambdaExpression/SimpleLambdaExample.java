/**
 * ref: https://docs.oracle.com/javase/tutorial/java/javaOO/lambdaexpressions.html
 *  
 *   
 */

package com.nanditha.AdvancedCoreJava.LambdaExpression;

public class SimpleLambdaExample {
	
	interface IntergerMath {
		 int operation(int a, int b);
	}
	
	public int operateBinary(int a, int b, IntergerMath op)
	{
		return op.operation(a, b);
	}
	
	public static void main(String[] args) {
		SimpleLambdaExample myApp = new SimpleLambdaExample();
		IntergerMath addition = (a,b) -> a+b;
		IntergerMath subtraction = (a,b) -> a-b;
		
		System.out.println("addtion: 40+2 = " + myApp.operateBinary(40, 2, addition));
		System.out.println("subtraction: 40-2 = " + myApp.operateBinary(40, 2, subtraction));

	}
	
}
