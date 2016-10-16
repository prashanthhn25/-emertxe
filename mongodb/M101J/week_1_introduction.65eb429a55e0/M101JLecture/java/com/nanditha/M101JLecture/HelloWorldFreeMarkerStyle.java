package com.nanditha.M101JLecture;

import java.io.IOException;
import java.io.StringWriter;
import java.util.HashMap;
import java.util.Map;
//import java.util.logging.Logger;

import org.apache.log4j.BasicConfigurator;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class HelloWorldFreeMarkerStyle {

	//static final Logger logger = Logger.getLogger(HelloWorldFreeMarkerStyle.class);
	
	public static void main(String[] args) {
		
		BasicConfigurator.configure();
		
		//logger.info("HelloWorldFreeMarkerStyle");
		Configuration configuration = new Configuration();
		
		configuration.setClassForTemplateLoading(HelloWorldFreeMarkerStyle.class, "/");

		try {
			Template helloTemplate = configuration.getTemplate("hello.ftl");
			StringWriter writer = new StringWriter();
			Map<String, Object> helloMap = new HashMap<String,Object>();
			helloMap.put("name","FreeMarker");
			helloTemplate.process(helloMap, writer);
			System.out.println(writer);
		} catch (IOException e) {
			//logger.error(e.getMessage());
			e.printStackTrace();
		} catch (TemplateException e) {
			//logger.error(e.getMessage());
			e.printStackTrace();
		}
	}

	}

