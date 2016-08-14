package com.nanditha.M101JLecture.week2;

import com.mongodb.MongoClient;
import com.mongodb.MongoClientOptions;
import com.mongodb.MongoClientURI;
import com.mongodb.ReadPreference;
import com.mongodb.ServerAddress;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

import static java.util.Arrays.asList;

import org.bson.BsonDocument;
import org.bson.Document;
import org.eclipse.jetty.util.annotation.ManagedOperation;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello Week2!" );
        /*
         * instantiate MongoClient
         **/
        //MongoClient client = new MongoClient();
        // MongoClient client = new MongoClient("localhost", 27017);
        //MongoClient client = new MongoClient(new ServerAddress("localhost", 27017));
        
        /*
         * connecting Mongodb Clusters:
         * To send list of mongoserver addresses
         * */
        //MongoClient client = new MongoClient(asList(new ServerAddress("localhost", 27017)));
        
        /*
         * Connection String
         * */
        //MongoClient client = new MongoClient(new MongoClientURI("mongodb://localhost:27017"));
    
        /*
         * along with number of options
         * MongoClientOptions class is immutable and builder().build() returns the class
         */
        //MongoClientOptions options = MongoClientOptions.builder().build();
        //MongoClient client = new MongoClient(new ServerAddress(), options);
        
        /*
         * Example : default connection is 100, i.e a pool of atmost 100 connections.
         * 
         */
        MongoClientOptions options = MongoClientOptions.builder().connectionsPerHost(100).build();
        MongoClient client = new MongoClient(new ServerAddress(), options);
        
        /*
         * Database are immutable, so once instantiated, 
         * if you want another instance you need to reconfigure it
         * No need to cache them
         * 
         */
        //MongoDatabase db = client.getDatabase("test");
        
        /*
         * Example : to change the configuration, 
         * Note: Since MangoDatabase is immutable, always save the results
         * of the configurations in an instance of MangoDatabase, because since
         * it returns new instance and if might loose the result or will be ignored
         */
        MongoDatabase db = client.getDatabase("test").withReadPreference(ReadPreference.secondary());
  
        /*
         * MangoCollection is gateway to all CRUD operations
         * also lightweight
         * It is a generic collection returns a collection of Document{BSON Document representation}
         * Note: Since MangoCollection is immutable, always save the results
         * of the configurations in an instance of MangoCollection, because since
         * it returns new instance and if might loose the result or will be ignored
         * 
         */
       // MongoCollection<Document> coll = db.getCollection("test");
        
        /*
         * Example: BsonDocument A type safe map, thus has a collection of Bson documenst 
         */
        MongoCollection<BsonDocument> coll = db.getCollection("test", BsonDocument.class);
        
    }
}
