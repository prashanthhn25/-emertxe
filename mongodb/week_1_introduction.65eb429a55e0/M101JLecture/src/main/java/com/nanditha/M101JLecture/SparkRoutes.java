package com.nanditha.M101JLecture;

import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Spark;

public class SparkRoutes {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Spark.get("/",  (req, res) ->
				{
					Map<String, Object> helloMap = new HashMap<String,Object>();
					helloMap.put("name","SparkRoute");
					return new ModelAndView(helloMap, "hello.ftl");
				}, 
				new FreeMarkerTemplateEngine()
				);
		
		Spark.get("/test",  (req, res) -> "This is test page!");
		
	
		Spark.get("/echo/:thing",  (req, res) -> req.params(":thing"));
		
	}

}
