package com.nanditha.M101JLecture.week2;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase ;

import static java.util.Arrays.asList;
import static com.nanditha.M101JLecture.week2.Helpers.printJson;

public class InsertTest {

	public static void main(String[] args) {

		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll =db.getCollection("insertTest");
		
		coll.drop();
		
		Document smith = new Document("name", "Smith")
						.append("age", 30)
						.append("profession", "programmer");
		
		Document jones = new Document("name", "Jones")
				.append("age", 30)
				.append("profession", "tester");
		
		//printJson(smith);
		/*
		 * To insert: the driver is generating the id on the client
		 * and inserting into the document before inserting into the database.
		 */
		
		/*
		 * a single document insertion
		 */
		//coll.insertOne(smith);
		//printJson(smith);
		
		/*
		 * Inserting many documents at a time
		 */
		coll.insertMany(asList(smith,jones));
	
		printJson(smith);
		printJson(jones);
		client.close();
	}

}
