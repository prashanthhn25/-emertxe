package com.nanditha.M101JLecture.week5;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.bson.Document;
import org.bson.conversions.Bson;

import com.mongodb.MongoClient;
import org.bson.*;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Accumulators;
import com.mongodb.client.model.Aggregates;
import com.mongodb.client.model.Filters;
public class AggregationTest {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("zipcodes");
		
		/*
		 * Using find
		 
		List<Document> results = coll.find().into(new ArrayList<>());
				
		*/
		
		/*
		 * Aggregation : pipeline using Document class
		 */
		/*
		List<Document> pipeline = Arrays.asList(
				new Document("$group", new Document("_id", "$state").append("totalPop", new Document("$sum", "$pop"))),
				new Document("$match", new Document("totalPop", new Document("$gte", 10000000))));
		
		List<Document> results = coll.aggregate(pipeline).into(new ArrayList<>());
		*/
		
		/*
		 * Using Builders : in mongodb 3.1>
		 
		List<Bson> pipeline = Arrays.asList(Aggregates.group("$state", Accumulators.sum("totalPop", "$pop")),
				Aggregates.match(Filters.gte("totalPop", 10000000)));
		
		List<Document> results = coll.aggregate(pipeline).into(new ArrayList<>());
		*/
		
		/*
		 * Using Document Parse method: using shell syntax in java
		 */
		List<Bson> pipeline = Arrays.asList(Document.parse("{$group : {_id: \"$state\", totalPop : {$sum: \"$pop\"}}}"), 
											Document.parse("{$match : {totalPop : {$gte: 10000000}}}"));
		List<Document> results = coll.aggregate(pipeline).into(new ArrayList<>());
		
		for (Document cur : results) {
			System.out.println(cur.toJson());
		}
		
		client.close();
	}
	
}
