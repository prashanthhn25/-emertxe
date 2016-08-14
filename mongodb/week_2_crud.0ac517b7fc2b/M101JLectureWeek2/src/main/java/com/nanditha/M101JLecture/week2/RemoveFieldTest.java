package com.nanditha.M101JLecture.week2;

import static com.mongodb.client.model.Sorts.ascending;
import static com.mongodb.client.model.Sorts.orderBy;
import static com.nanditha.M101JLecture.week2.Helpers.printJson;
import static com.mongodb.client.model.Filters.eq;


import java.util.ArrayList;
import java.util.List;

import org.bson.Document;
import org.bson.conversions.Bson;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;

public class RemoveFieldTest {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("students");
		MongoCollection<Document> coll = db.getCollection("grades");
		
		Bson filter = eq("type","homework");
		Bson sort = orderBy(ascending("student_id"), ascending("score"));
		
		int iter = 0;
		MongoCursor<Document> cursor = coll.find(filter).sort(sort).iterator();
		try{
			while(cursor.hasNext())
			{
				Document cur = cursor.next();
				if((iter % 2) == 0)
				{
					printJson(cur);
					coll.deleteOne(cur);
				}
				
				iter++;
			}
		}
		finally{
			//if there are exceptions or break early and dont want the cursor sitting upon the server
			cursor.close();
		}
	
		//print the values
		List<Document> all = coll.find().into(new ArrayList<>());
		all.forEach(System.out::println);
		
		client.close();
	}

}
