package com.nanditha.AdvancedCoreJava.Reflection;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

class A {
	public A() {

	}

	public void m() {
	}

	public void m1() {
	}

	public void m2() {
	}
}

class B extends A {
	public void bm() {
	}

	public void bm1() {
	}

	public void bm2() {
	}
}

public class ReflectMethodConstructor {

	public static void main(String[] args) throws ClassNotFoundException {

		B b1 = new B();
		Class<?> f1 = b1.getClass();

		Constructor<?>[] superclass = f1.getSuperclass().getConstructors();

		for (int i = 0; i < superclass.length; i++) {
			// get the parameterlist for each constructor type
			Class<?>[] parameterTypes = superclass[i].getParameterTypes();
			// get the parameter type names of each
			for (int k = 0; k < parameterTypes.length; k++) {
				String parameterString = parameterTypes[k].getName();
				System.out.print(parameterString + " ");
			}
		}

		// get the methods, of B, A, and Object
		System.out.println("B's method along with its parent's: ");
		B b2 = new B();
		Method arr[] = b2.getClass().getMethods();
		for (Method a : arr) {
			System.out.println(a.getName());
		}

		System.out.println("A's method along with its parent's: ");
		Class<?> f2 = b2.getClass().getSuperclass();
		Method arr2[] = f2.getMethods();
		for (Method a : arr2) {
			System.out.println(a.getName());
		}
	}

}
