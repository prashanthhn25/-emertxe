/**
 * Reflection: field and it's type access can be done given the class name is known at
 * compile time.
 */
package com.nanditha.AdvancedCoreJava.Reflection;

import java.awt.GridBagConstraints;
import java.lang.reflect.Field;

public class ReflectField {

	public static void main(String[] args) {
		GridBagConstraints g = new GridBagConstraints();
		printFieldNames(g);
	}

	private static void printFieldNames(Object o) {
		Class<?> c = o.getClass();

		/*
		 * Field provides info about, and gives dynamic access to a single field
		 * of a class or an interface
		 */
		Field[] publicFields = c.getFields();
		for (int i = 0; i < publicFields.length; i++) {
			String fieldName = publicFields[i].getName();
			Class<?> typeClass = publicFields[i].getType();
			String fieldType = typeClass.getName();
			// System.out.println(typeClass);
			System.out.println("Name: " + fieldName + ", Type: " + fieldType);
		}
	}

}
