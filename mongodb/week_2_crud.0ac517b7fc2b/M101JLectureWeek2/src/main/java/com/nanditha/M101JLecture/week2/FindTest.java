package com.nanditha.M101JLecture.week2;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;

import static com.nanditha.M101JLecture.week2.Helpers.printJson;

import java.util.ArrayList;
import java.util.List;

public class FindTest {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("findTest");
		
		coll.drop();
		
		//To insert 10 documents
		for(int i = 0; i < 10; i++)
		{
			coll.insertOne(new Document("x", i));
		}
		
		/*
		 * a single result:
		 * 
		 * find() returns am instance of FindIterable that extends MongoIterable
		 * which has first that returns a single result
		 * 
		 */
		System.out.println("Find one: ");
		Document firstField = coll.find().first();
		printJson(firstField);
		
		/*
		 * To get all the documents:
		 * 
		 *  find() returns am instance of FindIterable that extends MongoIterable
		 * which has into that returns a list of documents as result
		 */
		System.out.println("Find all with into: ");
		List<Document> all = coll.find().into(new ArrayList<>());
		//all.forEach(System.out::println);
		
		for(Document cur : all)
		{
			printJson(cur);
		}
		
		/*
		 * If the document is too large:
		 * We use MongoCursor and we need to close the cursor
		 * 
		 */
		System.out.println("Find all with iteration: ");
		MongoCursor<Document> cursor = coll.find().iterator();
		try{
			while(cursor.hasNext())
			{
				Document cur = cursor.next();
				printJson(cur);
			}
		}
		finally{
			//if there are exceptions or break early and dont want the cursor sitting upon the server
			cursor.close();
		}
		
		/*
		 * To give the count
		 */
		System.out.println("Count: ");
		long count = coll.count();
		System.out.println(count);
		client.close();
	}

}
