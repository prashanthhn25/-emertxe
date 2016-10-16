package com.nanditha.M101JLecture.week2;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

import spark.ModelAndView;
import spark.Spark;

public class HelloWorldSparkfreemarkerStyle {

	public static void main(String[] args) {
		
		MongoClient client = new MongoClient();
		MongoDatabase db = client.getDatabase("course");
		final MongoCollection<Document> coll = db.getCollection("helloWorldSparkfreemarkerStyle");
		
		coll.drop();
		
		coll.insertOne(new Document("name", "Mongo DB with Spark and Freemarker"));
		
		Spark.get("/",  (req, res) ->
		{
			//get the Bson field 1st field into document and send to render
			Document document = coll.find().first();
			client.close();
			
			return new ModelAndView(document, "hello.ftl");
		}, 
		new FreeMarkerTemplateEngine()
		);
		
	}

}
