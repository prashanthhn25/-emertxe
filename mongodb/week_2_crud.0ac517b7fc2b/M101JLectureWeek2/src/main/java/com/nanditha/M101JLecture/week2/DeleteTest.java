package com.nanditha.M101JLecture.week2;

import java.util.ArrayList;
import java.util.List;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;

import static com.mongodb.client.model.Filters.*;
public class DeleteTest {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("deleteTest");
		coll.drop();
	
		//insert 8 documents, with _id set to the value of loop variable
		for(int i = 0; i< 8; i++)
		{
			coll.insertOne(new Document().append("_id", i));
		}
		
		/*
		 * Delete:
		 * delete many documents whose id is > 4
		 * delete just one document
		 */
		//coll.deleteMany(gt("_id", 4));
		coll.deleteOne(gt("_id", 4));
		
		//print the values
		List<Document> all = coll.find().into(new ArrayList<>());
		all.forEach(System.out::println);
		
		
		client.close();
	}

}
