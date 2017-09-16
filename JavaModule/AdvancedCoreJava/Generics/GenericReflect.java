/**
 * ref: https://docs.oracle.com/javase/tutorial/java/generics/genTypeInference.html
 * ref: http://tutorials.jenkov.com/java-reflection/generics.html
 * 
 * The type cast is unsafe because the compiler won’t check whether 
 * the typecast is to the same type as stored in the stack.
 *  So the cast may fail at run-time. So generic gives type safety.
 *  The elements pushed onto and popped from the stack are type E, and any type change will 
 *  not be allowed at compile time. Thus, once the compiler knows the element type of the stack,
 *   the compiler can check whether the correct type is used consistently 
 *   and can insert the correct casts on the values taken out
 *    from the stack.
 *    
 *    All the collection types in J2SE 5.0 has been made Generic.
 *    
 *    Generic Methods introduced you to type inference, which enables you to invoke a generic 
 *    method as you would an ordinary method, without specifying a type between angle brackets.
 *    
 *     In 1.8:
 *     You can replace the type arguments required to invoke the constructor of a generic class
 *      with an empty set of type parameters (<>) as long as the compiler 
 *      can infer the type arguments from the context. This pair of angle brackets is informally 
 *      called the diamond.
 *      
 *      Example: Map<String, List<String>> myMap = new HashMap<String, List<String>>();
 *     valid in 1.8: Map<String, List<String>> myMap = new HashMap<>();
 *      without <> , we get unchecked conversion warning
 *      
 *      Example 2: MyClass<Integer> myObject = new MyClass<>("");
 *      			class MyClass<X> {
 * 						<T> MyClass(T t) {
 *   						// ...
 * 						}
 *					}
 *		: the compiler infers the type Integer for the formal type parameter, X, 
 *	of the generic class MyClass<X>. It infers the type String for the formal
 *	 type parameter, T, of the constructor of this generic class.
 *      	
 *      
 *      Example 3:  static <T> List<T> emptyList(); {in Collections}
 *      			List<String> listOne = Collections.emptyList();
 *      								(or)
 *      			List<String> listOne = Collections.<String>emptyList();
 *      here, List<String> is the target type, because emptyList returns List<T> value type,
 *     T will be inferred as String by compiler. But wont work in all the context, 
 *     Example 3b:  void processStringList(List<String> stringList) { // process stringList }
 *      			processStringList(Collections.emptyList());
 *      : here, in 1.7, compiler fails with List<Object> cannot be converted to List<String> error.
 *      ie., The compiler requires a value for the type argument T so it starts with the value Object. 
 *      Consequently, the invocation of Collections.emptyList returns a value of type List<Object>, 
 *      which is incompatible with the method processStringList. So need to specify type value:
 *      			processStringList(Collections.<String>emptyList());
 *      : in 1.8: In this case, processStringList requires an argument of type List<String>. 
 *      The method Collections.emptyList returns a value of List<T>, so using the target type of List<String>,
 *       the compiler infers that the type argument T has a value of String. 
 *      			processStringList(Collections.emptyList()); works!.
 *      
 *
 */
package com.nanditha.AdvancedCoreJava.Generics;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GenericReflect {

	protected static List<String> stringList;
	public List<String> stringList2;

	public List<String> getStringList() {
		return GenericReflect.stringList;
	}

	public void setStringList(List<String> list) {
		GenericReflect.stringList = list;
	}

	class GenericClass<X> {
		Map<String, List<String>> myMap = new HashMap<String, List<String>>();
		// unchecked conversion warning if <> is removed
		Map<String, List<Integer>> myMap2 = new HashMap<>();

		// parameterized constructor
		<T> GenericClass(T t) {

		}

		// generic method to print elements
		public void printList(List<?> list) {
			// mehod refernce to see what's been added into array list
			list.forEach(System.out::println);
		}
	}

	public static void main(String[] args) {

		List<String> exampleList = new ArrayList<>();
		exampleList.add("Nanditha");
		exampleList.add("Sushmitha");
		exampleList.add("Kantha");
		exampleList.add("Rathna");

		List<Integer> li = new ArrayList<Integer>();
		li.add(new Integer(100));
		li.add(new Integer(200));
		li.add(new Integer(300));
		
		// instantiation of GenericClass
		GenericClass<Integer> intObj = new GenericReflect().new GenericClass<Integer>("");

		// print any given list
		intObj.printList(exampleList);
		System.out.println("---");

		GenericReflect genRef = new GenericReflect();
		genRef.setStringList(exampleList);
		// adding to map names: array list of strings thats been added
		intObj.myMap.put("Name", genRef.getStringList());

		// in 1.8 using just <>
		GenericClass<Integer> intObj2 = new GenericReflect().new GenericClass<>("");
		intObj2 = intObj;
		//print integer list and add to map2
		intObj2.printList(li);
		intObj.myMap2.put("Numbers", li);
		System.out.println("---");
		
		// just show what's added 
		System.out.println(intObj2.myMap);
		System.out.println(intObj2.myMap2);
		
		// iterate map
		intObj2.myMap.forEach((k, v) -> {
			System.out.println("Key: " + k + " ;Value: " + v);
			System.out.println("---");
		});

		try {
			// access Generic Method Return Types
			// getStringList() returns a List<String> and not just a List.
			Method method = GenericReflect.class.getMethod("getStringList");
			Type returnType = method.getGenericReturnType();

			if (returnType instanceof ParameterizedType) {
				ParameterizedType type = (ParameterizedType) returnType;
				/*
				 * Type[] array typeArguments array will contain one item - a
				 * Class instance representing the class java.lang.String. Class
				 * implements the Type interface.
				 */
				Type[] typeArguments = type.getActualTypeArguments();
				for (Type typeArgument : typeArguments) {
					Class<?> typeArgClass = (Class<?>) typeArgument;
					System.out.println("typeArgClass = " + typeArgClass);
				}
				System.out.println("----");
				// access the generic parameter types of the method parameters
				method = GenericReflect.class.getMethod("setStringList", List.class);

				Type[] genericParameterTypes = method.getGenericParameterTypes();

				for (Type genericParameterType : genericParameterTypes) {
					if (genericParameterType instanceof ParameterizedType) {
						ParameterizedType aType = (ParameterizedType) genericParameterType;
						Type[] parameterArgTypes = aType.getActualTypeArguments();
						for (Type parameterArgType : parameterArgTypes) {
							Class<?> parameterArgClass = (Class<?>) parameterArgType;
							System.out.println("parameterArgClass = " + parameterArgClass);
						}
					}
				}
				System.out.println("----");
				// access generic public field types: class member variables -
				// either static or instance variables.
				Field field = GenericReflect.class.getField("stringList2");

				Type genericFieldType = field.getGenericType();

				if (genericFieldType instanceof ParameterizedType) {
					ParameterizedType aType = (ParameterizedType) genericFieldType;
					Type[] fieldArgTypes = aType.getActualTypeArguments();
					for (Type fieldArgType : fieldArgTypes) {
						Class<?> fieldArgClass = (Class<?>) fieldArgType;
						System.out.println("fieldArgClass = " + fieldArgClass);
					}
				}
			}

		} catch (NoSuchMethodException | SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			e.printStackTrace();
		}
	}

}
