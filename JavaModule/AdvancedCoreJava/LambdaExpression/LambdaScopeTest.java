/**
 * ref: https://docs.oracle.com/javase/tutorial/java/javaOO/lambdaexpressions.html
 *  
 *  Shadowing: 
 *  If a declaration of type (member variable or parameter name)
 *  in a particular scope (such as inner class or method definition) 
 *  has the same name as another declaration in the enclosed scope,
 *  then the declaration shadows the declaration of the enclosing scope.
 *  Cannot refer to a shadowed declaration by its name alone
 *  
 *   
 */

package com.nanditha.AdvancedCoreJava.LambdaExpression;
import java.util.function.Consumer;
public class LambdaScopeTest {
	
	public int x = 0;
	
	//inner class first level
	class FirstLevel{
		public int x = 1;
		
		//method 
		void methodInFirstLevel(int x){
			/*
			 * Note 1: Because of this assignment statement, 
			 * the variable FirstLevel.x is not effectively final anymore. 
			 * As a result, the Java compiler generates an error message similar to 
			 * "local variables referenced from a lambda expression 
			 * must be final or effectively final" where the lambda expression
			 *  myConsumer tries to access the FirstLevel.x variable at line 67
			 */
			//x = 10;
			
			/*
			 * Normal Shadowing Issue: line 26 is still valid and line 31 would have given 10 value
			 * as it would shadow
			 */
			System.out.println("Shodowing Test");
			System.out.println("x = " + x); //x = 10
			System.out.println("this.x = " + this.x ); // this.x = 1
			System.out.println("LambdaScopeTest.this.x = " 
					+ LambdaScopeTest.this.x); //LambdaScopeTest.this.x = 0 
			
			
			/*
			 * With Lambda Expression
			 */
			System.out.println();
			System.out.println("Lambda Expression Scope");
			
			
			/*
			 * Note 2:  Consumer<Integer> myConsumer = (x) will be error
			 * as variable x is already defined in method methodInFirstLevel(int)
			 * and the lambda expression does not introduce a new level of scoping.
			 */
			Consumer<Integer> myConsumer = (y) ->
			{
				/* 
				 * Note 1: In lambda Expression, local variable referenced must be final
				 * or effectively final so, we cannot change x value inside the method 
				 * and then try to read line 26 will lead to error on line 67 and line68 would give 10
				 */
				
				System.out.println("x = " + x); //error
				System.out.println("y = " + y);  //would be 10
				System.out.println("this.x = " + this.x ); // this.x = 1
				System.out.println("LambdaScopeTest.this.x = " 
						+ LambdaScopeTest.this.x); //LambdaScopeTest.this.x = 0 
				
			};
			
			myConsumer.accept(x);
		}
	}
	
	public static void main(String[] args) {
		LambdaScopeTest myApp = new LambdaScopeTest();
		LambdaScopeTest.FirstLevel innerClass = myApp.new FirstLevel();
		innerClass.methodInFirstLevel(23);
	}
	
}
