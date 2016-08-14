/**
 * ref: https://docs.oracle.com/javase/tutorial/java/generics/upperBounded.html
 * 
 * 1. Upper Bound Wildcard: List<? extends Number>
 * restricts the unknown type to be a specific type or 
 * a subtype of that type and is represented using the extends keyword
 *  : The term List<Number> is more restrictive than List<? extends Number> 
 *  because the former matches a list of type Number only, 
 *  whereas the latter matches a list of type Number or any of its subclasses.
 *  
 * 2. Unbound Wildcard:  List<?>
 *  : List<Object> and List<?> are not the same. 
 *  You can insert an Object, or any subtype of Object, into a List<Object>.
 *  But you can only insert null into a List<?>. 
 *  
 * 3. Lower Bounded Wildcard:  List<? super Integer>
 * restricts the unknown type to be a specific type or
 * a super type of that type.
 * : The term List<Integer> is more restrictive than List<? super Integer> 
 * because the former matches a list of type Integer only,
 * whereas the latter matches a list of any type that is a supertype of Integer.
 * 
 */

package com.nanditha.AdvancedCoreJava.Generics;

import java.util.ArrayList;
import java.util.List;

class Employee{
	private String empName;
	private int empNo;
	
	public Employee(String empName, int empNo)
	{
		this.empName = empName;
		this.empNo = empNo;
	}
	public int getEmpNo() {
		return empNo;
	}
	public void setEmpNo(int empNo) {
		this.empNo = empNo;
	}
	public String getEmpName() {
		return empName;
	}
	public void setEmpName(String empName) {
		this.empName = empName;
	}
	
	@Override
	public String toString() {
		//return super.toString();
		return "Employee Name: " + empName;
	}
}
class TeamLead extends Employee{
	
	private String projectName;
	private int projectId;
	
	public TeamLead(String empName, int empNo, String projectName, int projectId) {
		super(empName, empNo);
		this.projectId = projectId;
		this.projectName = projectName;
	}

	public String getProjectName() {
		return projectName;
	}
	public void setProjectName(String projectName) {
		this.projectName = projectName;
	}
	public int getProjectId() {
		return projectId;
	}
	public void setProjectId(int projectId) {
		this.projectId = projectId;
	}
}
class Manager extends TeamLead{
	public Manager(String empName, int empNo, String projectName, int projectId, String unitName) {
		super(empName, empNo, projectName, projectId);
		this.unitName = unitName;
	}

	private String unitName;

	public String getUnitName() {
		return unitName;
	}

	public void setUnitName(String unitName) {
		this.unitName = unitName;
	}
}


public class GenericWildcards {

	//generic method to print
	public static void printListLowerBound(List <? super Manager> list)
	{
		for(Object element:list){
            System.out.print(element.toString());
        }
		System.out.println("");
	}
	
	public static void printListUpperBound(List <? extends Employee> list)
	{
		for(Object element:list){
            System.out.print(element.toString());
        }
		System.out.println("");
	}
	
	public static void printListUnbound(List <?> list)
	{
		for(Object element:list){
            System.out.print(element.toString());
        }
		System.out.println("");
	}
	public static void main(String[] args) {
		List<Employee> ls = new ArrayList<>();
		ls.add(new Employee("nanditha",1));
		ls.add(new Employee("Sushmitha",2));
		
		List<TeamLead> ls1 = new ArrayList<>();
		ls1.add(new TeamLead("kantha", 3, "fam", 111));
		
		List<Manager> ls2 = new ArrayList<>();
		ls2.add(new Manager("rathna", 4, "fam", 111, "blr"));
		
		/* if extends Teamlead is used, then compiler will throw error saying 
		 * that the method is restricted to Teamlead and it's subclasses
		 */
		printListLowerBound(ls);
		printListLowerBound(ls1);
		
		/* if super Teamlead is used, then compiler will throw error saying 
		 * that the method is restricted to Teamlead and it's superclasses
		 */
		printListLowerBound(ls2);
		
		/* lower bound */
		printListUpperBound(ls);
		printListUpperBound(ls1);
		printListUpperBound(ls2);
		
		/* unbound */
		printListUnbound(ls);
		printListUnbound(ls1);
		printListUnbound(ls2);
		
	}

}
