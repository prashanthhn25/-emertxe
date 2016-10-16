package com.nanditha.M101JLecture;


import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;

import spark.Spark;

public class HelloWorldSparkStyle {
	static final Logger logger = Logger.getLogger(HelloWorldSparkStyle.class);
	
	public static void main(String[] args) {
		BasicConfigurator.configure();
		
		logger.info("HelloWorldSparkStyle");
		try
		{
			Spark.get("/", (req, res) -> "Hello World");
		}
		catch (Exception e)
		{
			logger.error(e.getMessage());
		}

	}

}
