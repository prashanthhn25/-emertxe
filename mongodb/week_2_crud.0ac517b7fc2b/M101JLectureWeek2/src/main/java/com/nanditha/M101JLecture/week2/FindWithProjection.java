package com.nanditha.M101JLecture.week2;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.bson.Document;
import org.bson.conversions.Bson;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

import static com.mongodb.client.model.Projections.*;
import static com.mongodb.client.model.Filters.*;


public class FindWithProjection {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("findWithProjection");
		coll.drop();
		
		//insert 10 documents with random integer
		for(int i =0; i< 10; i++)
		{
			coll.insertOne(new Document().append("x", new Random().nextInt(2))
							.append("y", new Random().nextInt(100))
							.append("i", i)
					);
		}
		
		Bson filter = and(eq("x", 0), gt("y", 10), lt("y", 90));
		/*
		 * Projection of raw data: 
		 */
		// 0 means exclude x field here and add that projection into the find 
		//Bson projection = new Document("x", 0).append("_id", 0);
		
		// 1 means include x field here and add that projection into the find 
		/*
		Bson projection = new Document("y", 1)
							.append("i", 1)
							.append("_id", 0);
		
		*/
		
		
		/*
		 * Using Projection class from driver
		 * exclude and include takes variable arguments
		 * 
		 * To do both, we use fields method 
		 */
		//Bson projection = Projections.exclude("x","_id");
		//Bson projection = Projections.include("y","i");
		//Bson projection = Projections.fields(Projections.exclude("_id"), Projections.include("y","i"));
		//Bson projection = Projections.fields(Projections.excludeId(), Projections.include("y","i"));
		
		//as we have done static imports
		Bson projection = fields(excludeId(), include("y","i"));
		
		List<Document> all = coll.find(filter)
							.projection(projection)	
							.into(new ArrayList<>());
		all.forEach(System.out::println);
		
		client.close();
	}

}
