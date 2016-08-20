package com.nanditha.AdvancedCoreJava.Reflection;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;

/**
 * Reflection Notes:
 * 
 * 1. helps in analyze classes, fields, methods and interfaces at runtime,
 * without knowing the names of the classes at compile time.
 *
 * 2 package, classname, superclass, modifiers, fields, method, constructor
 * using reflection
 */
class Child1 extends SuperClasss {
}

public class SuperClasss {
	public double d;
	public static final int i = 37;
	private String example = "testing";
	protected float f;
	Boolean bool;
	protected Child1 ch;

	public SuperClasss() {
		super();
		double d1 = 12.8;
	}

	// Parameterized constructor
	public SuperClasss(int ival, double jval, float kval) {

	}

	// method
	public void display() {
		System.out.println("Hai, display!");

	}

	public static void main(String[] args) {
		Child1 child1 = new Child1();

		/*
		 * Note: in 1.6: java uses unchecked or unsafe operations. a warning
		 * would be given at compile time. Thus unchecked call is made as a
		 * member of the raw type java.lang.Class
		 * 
		 * to avoid this in 1.8: child2 should be included wth an appropriate
		 * genetric type
		 */

		/*
		 * If you know the name of the class at compile time you can obtain a
		 * Class object
		 */
		// If an instance of the class is available, Object.getClass is invoked.
		Class<?> child2 = child1.getClass();
		System.out.println(child2);

		// From the Class object you can access the superclass of the class
		Class<?> superClass = child2.getSuperclass();

		// The fully qualified class name (including package name) is obtained
		System.out.println("chile classs with package is: " + child2.getName());
		System.out.println("parent class  with package is: " + superClass.getName());

		// The class name without the package name is obtained
		System.out.println("chile classs name is: " + child2.getSimpleName());
		System.out.println("parent class nameis: " + superClass.getSimpleName());

		// to get package information only
		System.out.println("chile classs package is: " + child2.getPackage());
		System.out.println("parent class package is: " + superClass.getPackage());

		// another way to get the classname by giving full path
		// If the class name is unknown at compile time, but available at
		// runtime, you can use the forName method
		try {
			Class<?> cls = Class.forName("com.nanditha.AdvancedCoreJava.Reflection.SuperClasss");
			System.out.println("class is: " + cls);
			String clsName = cls.getName();
			System.out.println("Class Name: " + clsName);

			// modifier
			int modif = cls.getModifiers();
			System.out.println("is modif public?: " + Modifier.isPublic(modif));
			System.out.println("is modif praivate?: " + Modifier.isPrivate(modif));
			System.out.println("modifier: " + modif);

			// methods in the class
			Method[] method = cls.getDeclaredMethods();
			for (int i = 0; i < method.length; i++) {
				Method m = method[i];
				System.out.println("name of method= " + m.getName());
			}

			// constructors
			Constructor<?>[] constructors = cls.getConstructors();
			for (int i = 0; i < constructors.length; i++) {
				Constructor<?> co = constructors[i];
				System.out.println("name of constructor  = " + co.getName());
				Class<?> pvec[] = co.getParameterTypes();
				for (int j = 0; j < pvec.length; j++)
					System.out.println("param #" + j + " " + pvec[j]);
			}

			// to get the declaredfields and fieldlist
			Field[] fieldlist = cls.getDeclaredFields();
			System.out.println("field: ");
			for (int i = 0; i < fieldlist.length; i++) {
				Field fld = fieldlist[i];

				// field names
				System.out.println("name= " + fld.getName());
				// class name
				System.out.println("decl class = " + fld.getDeclaringClass());
				// field type
				System.out.println("type= " + fld.getType());
				// modifier
				int mod = fld.getModifiers();
				System.out.println("modifiers = " + Modifier.toString(mod));
				System.out.println("-----");
			}
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

	public String getExample() {
		return example;
	}

	public void setExample(String example) {
		this.example = example;
	}
}
