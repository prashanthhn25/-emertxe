package com.nanditha.M101JLecture;

import java.io.IOException;
import java.io.StringWriter;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Logger;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import spark.ModelAndView;
import spark.TemplateEngine;

public class FreeMarkerTemplateEngine extends TemplateEngine{
	private Configuration configuration;
	
	private static final Logger logger = Logger.getLogger(FreeMarkerTemplateEngine.class);
	
	 protected FreeMarkerTemplateEngine() {
	        this.configuration = createFreemarkerConfiguration();
	    }
	 
	private Configuration createFreemarkerConfiguration() {
		BasicConfigurator.configure();
		
		Configuration retVal = new Configuration();
		retVal.setClassForTemplateLoading(FreeMarkerTemplateEngine.class, "/");

		return retVal;
	}

	@Override
	public String render(ModelAndView modelAndView) {
		
		try {
			StringWriter writer = new StringWriter();
			Template helloTemplate = configuration.getTemplate(modelAndView.getViewName());
			helloTemplate.process(modelAndView.getModel(), writer);
		
			return writer.toString();
			
		} catch (IOException e) {
			logger.error(e.getMessage());
			//e.printStackTrace();
		} catch (TemplateException e) {
			logger.error(e.getMessage());
			//e.printStackTrace();
		}
		
		return null;
	}
}