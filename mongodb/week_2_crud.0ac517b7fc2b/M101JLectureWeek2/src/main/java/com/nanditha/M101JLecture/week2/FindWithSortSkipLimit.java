package com.nanditha.M101JLecture.week2;

import java.util.ArrayList;
import java.util.List;

import org.bson.Document;
import org.bson.conversions.Bson;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Projections;
import com.mongodb.client.model.Sorts;

import static com.mongodb.client.model.Projections.*;
import static com.mongodb.client.model.Sorts.*;

public class FindWithSortSkipLimit {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		MongoCollection<Document> coll = db.getCollection("findWithSortSkipLimit");
		coll.drop();
		
		//insert 100 documents with random integers
		for(int i = 0; i< 10; i++)
		{
			for(int j = 0; j< 10; j++)
			{

				coll.insertOne(new Document()
								.append("i", i)
								.append("j", j)
								);
			}
		}
		
		//projection to print only i and j fields
		Bson projection = fields(include("i","j"), excludeId());
		
		/*
		 * Sort with raw documents
		 */
		//Bson sort = new Document("i", 1); //j will also seem like its ordered but it takes in insertion order
		//Bson sort = new Document("i", 1).append("j", -1); //descending
		
		/*
		 * Using Builders called Sort
		 * To combine we use orderBy
		 */
		//Bson sort = Sorts.ascending("i");
		//Bson sort = ascending("i");
		//Bson sort = descending("j");
		Bson sort = orderBy(ascending("i"), descending("j"));
		
		/*
		 * to find the documents with said projection using into method
		 * in said sorting order 
		 * using limit(50) :  first 50 and skip(20) first 20
		 */
		List<Document> all = coll.find()
							.sort(sort)
							.limit(50)
							.skip(20)
							.projection(projection)
							.into(new ArrayList<>());
		all.forEach(System.out::println);
		
		client.close();
	}

}
