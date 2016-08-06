package com.nanditha.M101JLecture;

import java.util.HashMap;
import java.util.Map;

import spark.ModelAndView;
import spark.Spark;

public class HelloWorldSparkfreemarkerStyle {

	public static void main(String[] args) {
		
		Spark.get("/",  (req, res) ->
				{
					Map<String, Object> helloMap = new HashMap<String,Object>();
					helloMap.put("name","SparkFreeMarker");
					return new ModelAndView(helloMap, "hello.ftl");
				}, 
				new FreeMarkerTemplateEngine()
				);
	}
	

}
