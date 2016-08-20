package com.nanditha.M101JLecture.week3;

import com.mongodb.BasicDBList;
import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.MongoClient;
import com.mongodb.WriteResult;
public class RemoveEmbeddedDocElem {

	public static void main(String[] args) {
		MongoClient client = new MongoClient();
		DB db = client.getDB("school");
		DBCollection coll = db.getCollection("students");
		
		DBCursor cursor = coll.find();
		try{
			while(cursor.hasNext())
			{
				BasicDBObject cur = (BasicDBObject) cursor.next();
				//to get the _id value 
				int studentId = cur.getInt("_id");
				
				//scores will be a list of BasicDBObject of scores
				BasicDBList scores = (BasicDBList) cur.get("scores");
				
				//to find the score that is minimum for homework
				//initial values for each scores doc
				DBObject scoreToRemove = null;
				double minScoreVal = 100;
				
				for(Object eachscoreObj : scores)
				{
					//change the type to DBObject from Object type
					BasicDBObject eachscore = (BasicDBObject) eachscoreObj;
					String scoreType = eachscore.getString("type");
					
					if(!"homework".equals(scoreType))
					{
						continue;
					}
					double currentScoreVal = eachscore.getDouble("score");
					System.out.printf("type[%s], current score value[%f] %n",
							scoreType, currentScoreVal);
					if(minScoreVal > currentScoreVal)
					{
						scoreToRemove = eachscore;
						minScoreVal = currentScoreVal;
					}
				}
				System.out.printf("score to remove[%s] %n", scoreToRemove);
				
				//To do the actual remove
				if(scoreToRemove != null)
				{
					//remove only the homework DBobject with minimum score from the score
					scores.remove(scoreToRemove);
					
					//update the new score in db for each student
					BasicDBObject query = new BasicDBObject("_id", studentId);
					BasicDBObject scoresUpdate = new BasicDBObject(
											"$set", new BasicDBObject("scores", scores));
					 WriteResult result = coll.update(query, scoresUpdate);
					 
					 
	                 //print the update count   
					 System.out.printf("update count[%d] %n", result.getN());
				}
			}
		}
		finally{
			//if there are exceptions or break early and don't want the cursor sitting upon the server
			cursor.close();
		}
		client.close();
	}
	
}
