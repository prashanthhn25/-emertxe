package com.nanditha.M101JLecture;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import org.apache.log4j.Logger;

import spark.ModelAndView;
import spark.Spark;

public class SparkFormHandling {

private static final Logger logger = Logger.getLogger("logger");
	
	public static void main(String[] args) {
		
		logger.info("Form Handling");
		
		Spark.port(5678);
		Spark.get("/",  (req, res) ->
		{
			Map<String, Object> fruitsMap = new HashMap<String,Object>();
			fruitsMap.put("fruits",Arrays.asList("Apple", "Orange","Bananan","Peach"));
			
			return new ModelAndView(fruitsMap, "fruitPicker.ftl");
		}, 
		new FreeMarkerTemplateEngine()
		);

		Spark.post("/favorite_fruit",  (req, res) ->
			{
				final String fruit = req.queryParams("fruit");
				if(fruit == null)
				{
					return "Why dont you pick one?";
				}
				else
				{
					return "Your favorite fruit is " + fruit;
				}
				
			}
	    );
		
	}
	

}
