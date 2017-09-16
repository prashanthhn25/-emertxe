package com.nanditha.AdvancedCoreJava.Reflection;

/**
 * Reflection Notes:
 * constructor and its parameter lists, using reflection
 */

import java.awt.Rectangle;
import java.lang.reflect.Constructor;

public class ReflectConstructor {

	public static void main(String[] args) {
		Rectangle rect = new Rectangle();
		showConstructors(rect);

	}

	// static class
	static void showConstructors(Object obj) {
		// If an instance of the class is available, Object.getClass is invoked.
		Class<?> classObj = obj.getClass();
		System.out.println(classObj);

		/*
		 * In 1.6: getConstructors() and other methods were generified in in
		 * java.lang.Class, and hence the compilation warning In 1.8 :
		 * Constructor is a raw type. References to generic type Constructor<T>
		 * should be parameterized to not get the warnings
		 * 
		 */

		// to access the constructors of a class
		Constructor<?>[] theConstructors = classObj.getConstructors();

		/*
		 * The Constructor[] array will have one Constructor instance for each
		 * public constructor declared in the class.
		 */
		for (int i = 0; i < theConstructors.length; i++) {
			System.out.print("( ");

			/*
			 * In 1.8 : Class is a raw type. References to generic type Class<T>
			 * should be parameterized
			 * 
			 */

			// read what parameters a given constructor takes
			Class<?>[] parameterTypes = theConstructors[i].getParameterTypes();
			for (int k = 0; k < parameterTypes.length; k++) {
				String parameterString = parameterTypes[k].getName();
				System.out.print(parameterString + " ");
			}
			System.out.println(")");
		}
	}

}
