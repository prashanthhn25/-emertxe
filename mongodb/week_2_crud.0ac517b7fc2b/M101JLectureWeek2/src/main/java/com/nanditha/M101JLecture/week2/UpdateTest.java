package com.nanditha.M101JLecture.week2;

import java.util.ArrayList;
import java.util.List;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.UpdateOptions;
import com.mongodb.client.model.Updates;

import static com.mongodb.client.model.Filters.*;
import static com.mongodb.client.model.Updates.*;

public class UpdateTest {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("UpdateTest");
		
		coll.drop();
		
		//insert 8 documents, with both _id and x set to the value of the loop variable
		for(int i = 0 ; i < 9;i++)
		{
			coll.insertOne(new Document()
							.append("_id", i)
							.append("x", i)
							.append("y", true));
		}
		
		/*
		 * replaceOne: wholesale replacement
		 * Example: replace x = 5 document, with x =20 along with new field
		 * here y field is gone as we did wholesale replacement of the document
		 * 
		 */
		//coll.replaceOne(eq("x", 5), new Document("x", 20).append("updated", true));
		
		/*
		 * update to change the existing fields, remove fields or add new fields
		 * updateOne will update one single document that matches the filter
		 */
		
		/*
		 * updateOne: Using raw documents: 
		 * 
		 * y field will not be removed, 
		 * as we are updating using $set, which will only change the values of
		 * said fields and will not change anything else
		 */
		//coll.updateOne(eq("x", 5), new Document("$set", new Document("x", 20).append("updated", true) ));
		
		/*
		 * Using Updates builder class
		 * to just set single field, we use set
		 * to combine multiple queries, we use combine
		 */
		//coll.updateOne(eq("x", 6), Updates.set("x", 20));
		//coll.updateOne(eq("x", 6), combine(set("x", 20), set("updated", true)));
		
		/*
		 * updateOne can also be used to do upsert: 
		 * if the document is not found, it creates
		 * using UpdateOptions()
		 */
		coll.updateOne(eq("_id", 9), combine(set("x", 20), set("updated", true)),
					new UpdateOptions().upsert(true));
		
		/*
		 * updateMany:
		 * More than one document can be updated at a time
		 */
		coll.updateMany(gte("x", 5), inc("x", 1));
		
		//to print all the values
		List<Document> all = coll.find().into(new ArrayList<>());
		all.forEach(System.out::println);
		
		client.close();
	}

}
