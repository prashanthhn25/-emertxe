package com.nanditha.M101JLecture.week2;

import java.util.Arrays;
import java.util.Date;

import org.bson.BsonDocument;
import org.bson.BsonString;
import org.bson.Document;
import org.bson.types.ObjectId;
import static com.nanditha.M101JLecture.week2.Helpers.printJson;

public class DocumentTest {
	public static void main(String[] args) {
		/*
		 * Document implements Map of String and Objects, Bson and Serializable
		 * Bson interface returns BsonDocument
		 *  which implements a Map of String and BsonValue that is type safe
		 * 
		 * BSON is a map of keys[String -> String] to values [Object -> native BSON values]
		 * If the document does not contain that key value, it gives null
		 */
		
		//to add BSON key-value, 
		Document document = new Document()
							.append("str", "Mongo DB, Hello")
							.append("int", 42)
							.append("l", 1L)
							.append("double", 1.1)
							.append("b", false)
							.append("date", new Date())
							.append("objectId", new ObjectId())
							.append("null", null)
							.append("embeddedDoc", new Document("x", 0))
							.append("list", Arrays.asList(1,2,3));
		
		//to pull the data: returns an Object so needs typecast
		String str = (String) document.get("strs");
		//or can let the document make the cast using helper class like
		System.out.println(document.getString("str")); 
		System.out.println(document.getInteger("int")); 
		
		printJson(document);
		
		//update the document with new field
		document.append("email", "nan@gmail.com");
		printJson(document);
		
		/*
		 *  BsonDocument implements a Map of String and BsonValue that is type safe
		 */
		BsonDocument bsondocument = new BsonDocument("str", new BsonString("Mongo Db, Hello"));
		
	}
}
