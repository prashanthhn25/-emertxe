package com.nanditha.M101JLecture.week2;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.bson.Document;
import org.bson.conversions.Bson;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;

import static com.mongodb.client.model.Filters.*;
import static com.nanditha.M101JLecture.week2.Helpers.printJson;


public class FindWithFilterTest {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("findWithFilterTest");
		coll.drop();
		
		//insert 10 documents with random integers
		for(int i=0; i< 10; i++)
		{
			coll.insertOne(new Document()
							.append("x", new Random().nextInt(2))
							.append("y", new Random().nextInt(100)));
		}
		
		/*
		 * Query filter Using Raw documents
		 * 
		 */
		Bson filter = new Document("x", 0)
					.append("y", new Document("$gt", 10)
					.append("$lt", 90));
		
		/*
		 * Query filters using driver 
		 * Filters has static methods like eq, gt that needs to be imported
		 */
		//Bson filter2 = Filters.eq("x", 0);
		Bson filter2 = and(eq("x", 0), gt("y", 10), lt("y", 90));
		
		//print the first document that matches this criteria
		Document firstField = coll.find(filter2).first();
		
		  if (firstField == null) {
	            System.out.println("firstField not in database");
	        }
		  else
		  {
			  printJson(firstField);
		  }
		
		//print all the documents 
		List<Document> all = coll.find().into(new ArrayList<>());
		all.forEach(System.out::println);
		
		//long count = coll.count(filter);
		long count = coll.count(filter2);
		System.out.println(count);
		client.close();
	}

}
