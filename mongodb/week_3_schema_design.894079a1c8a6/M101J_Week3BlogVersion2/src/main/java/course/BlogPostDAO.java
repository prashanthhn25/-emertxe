package course;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class BlogPostDAO {
    DBCollection postsCollection;

    public BlogPostDAO(final DB blogDatabase) {
        postsCollection = blogDatabase.getCollection("posts");
    }

    // Return a single post corresponding to a permalink
    public DBObject findByPermalink(String permalink) {

        // XXX HW 3.2,  Work Here
    	DBObject post = postsCollection.findOne(new BasicDBObject("permalink",permalink));
        return post;
    }

    // Return a list of posts in descending order. Limit determines
    // how many posts are returned.
    public List<DBObject> findByDateDescending(int limit) {

        // XXX HW 3.2,  Work Here
        // Return a list of DBObjects, each one a post from the posts collection
        List<DBObject> posts = new ArrayList<DBObject>();

        DBCursor cursor = postsCollection.find()
        				.limit(limit)
        				.sort(new BasicDBObject("date", -1));
        
        try{
        	while(cursor.hasNext())
        	{
        		DBObject post = cursor.next();
        		posts.add(post);
        	}
        }
        finally {
			cursor.close();
		}
        return posts;
        
    }


    public String addPost(String title, String body, List tags, String username) {

        System.out.println("inserting blog entry " + title + " " + body);

        String permalink = title.replaceAll("\\s", "_"); // whitespace becomes _
        permalink = permalink.replaceAll("\\W", ""); // get rid of non alphanumeric
        permalink = permalink.toLowerCase();


        // XXX HW 3.2, Work Here
        // Remember that a valid post has the following keys:
        // author, body, permalink, tags, comments, date, title
        //
        // A few hints:
        // - Don't forget to create an empty list of comments
        // - for the value of the date key, today's datetime is fine.
        // - tags are already in list form that implements suitable interface.
        // - we created the permalink for you above.

        // Build the post object and insert it
        BasicDBObject post = new BasicDBObject()
        					.append("title", title)
        					.append("author", username)
        					.append("body", body)
        					.append("permalink", permalink)
        					.append("tags", tags)
        					.append("comments", new ArrayList())
        					.append("date", new Date());

        postsCollection.insert(post);

        return permalink;
    }




    // White space to protect the innocent








    // Append a comment to a blog post
    public void addPostComment(final String name, final String email, final String body,
                               final String permalink) {

        // XXX HW 3.3, Work Here
        // Hints:
        // - email is optional and may come in NULL. Check for that.
        // - best solution uses an update command to the database and a suitable
        //   operator to append the comment on to any existing list of comments
    	DBObject findQuery = new BasicDBObject("permalink", permalink);
    	
    	BasicDBObject comment = new BasicDBObject()
    								.append("author", name)
    								.append("body", body);
    	
    	if(email != null && !email.equals(""))
    	{
    		comment.append("email", email);
    	}
    								
    	DBObject updateQuery = new BasicDBObject("$push", new BasicDBObject("comments", comment));
    	
    	postsCollection.update(findQuery, updateQuery);
    	
    
    }
}
