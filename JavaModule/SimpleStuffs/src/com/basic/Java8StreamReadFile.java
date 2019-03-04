package com.basic;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Java8StreamReadFile {
	public static StringHandlerUtility strHandler;
	
	
	public static void readEachLineAsListOfStrings(String fileName) {

		// To save it as list of Strings
		List<String> strList = new ArrayList<>();

		// for each line, convert it into a list of Strings
		try {

			Stream<String> stream = Files.lines(Paths.get(fileName));
			strList = stream.collect(Collectors.toList());

		} catch (IOException e) {
			e.printStackTrace();
		}

		strList.forEach(System.out::println);

	}
	
	
	public static void readEachLineMapAsIntegersUsingBufferdRead(String fileName) {
        try {
            BufferedReader br = Files.newBufferedReader(Paths.get(fileName));
            Stream<Integer> lines = br.lines().map(s -> Integer.parseInt(s));
            lines.forEach(System.out::println);
            lines.close();
 
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
	
	public static void testSomething(String fileName) {
		// To save it as list of Strings after making some changes
		List<String> strList = new ArrayList<>();

        try {
        	Stream<String> stream = Files.lines(Paths.get(fileName));
        	strList = stream.filter(line -> !line.startsWith("line3"))
        			.map(String::toUpperCase).collect(Collectors.toList());
 
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        strList.forEach(System.out::println);
    }
	
	
	public static void readCsvFileFormatDateColumn(String fileName, String fileName2) {
		try {
			BufferedReader br = Files.newBufferedReader(Paths.get(fileName));
			BufferedWriter bw = Files.newBufferedWriter(Paths.get(fileName2));
			
			String strLine;
			int lineCount=0, indexPostDate=0, indexCreatedDate=0;
			while ((strLine = br.readLine()) != null)   {
				lineCount++;
				if(lineCount ==1 ) {
					indexPostDate = StringHandlerUtility.findIndexOfGivenFieldInString("PostDate", strLine);
					indexCreatedDate  = StringHandlerUtility.findIndexOfGivenFieldInString("CreatedDate", strLine);
				}
				else {
					String postDateField =StringHandlerUtility.findFieldFromGivenIndexinString(indexPostDate, strLine);
					String createdDateField =StringHandlerUtility.findFieldFromGivenIndexinString(indexCreatedDate, strLine);
					
					//System.out.println(postDateField + ":  " + DateHandlerUtility.dateTimeFormat_FromUserFormatterToISO_LOCAL_DATE(postDateField, "E MMM d H:m:s z yyyy"));
					//System.out.println(createdDateField + ":  " + DateHandlerUtility.dateTimeFormat_FromUserFormatterToISO_LOCAL_DATE(createdDateField, "E MMM d H:m:s z yyyy"));
				
					//System.out.println(postDateField + ":  " + DateHandlerUtility.dateTimeFormat_FromUserFormatterToUserFormat(postDateField, "E MMM d H:m:s z yyyy", "dd/MM/yyyy"));
					//System.out.println(createdDateField + ":  " + DateHandlerUtility.dateTimeFormat_FromUserFormatterToUserFormat(createdDateField, "E MMM d H:m:s z yyyy", "dd/MM/yyyy"));
				
					String postDateModifiedField = DateHandlerUtility.dateTimeFormat_FromUserFormatterToUserFormat(postDateField, "E MMM d H:m:s z yyyy", "dd/MM/yyyy");
					String createdDateModifiedField = DateHandlerUtility.dateTimeFormat_FromUserFormatterToUserFormat(createdDateField, "E MMM d H:m:s z yyyy", "dd/MM/yyyy");
				
					strLine = strLine.replaceAll(postDateField, postDateModifiedField);
					strLine = strLine.replaceAll(createdDateField, createdDateModifiedField);
				}
				bw.write(strLine);
				bw.write("\n");
			}
			bw.flush();
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	public static void replaceTabWithComma(String fileName, String fileName2) {
		try {
			BufferedReader br = Files.newBufferedReader(Paths.get(fileName));
			BufferedWriter bw = Files.newBufferedWriter(Paths.get(fileName2));
			String strLine;
			
			while ((strLine = br.readLine()) != null)   {
				strLine = strLine.replaceAll("\t", ",");
				bw.write(strLine);
				bw.write("\n");
			}
			bw.flush();
			br.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
        
	}
	
		
	public static void fileListInFolder(String filepath) {
		List<String> results = new ArrayList<String>();
		
		File[] files = new File(filepath).listFiles();
		
		for(File file : files) {
			if (file.isFile()) {
				results.add(file.getName());
			}
		}
        System.out.println(results);
	}
	
	public static void copyToSplitFile(String fileName, String fileName2) {
		try {
			BufferedReader br = Files.newBufferedReader(Paths.get(fileName));
			BufferedWriter bw;
			bw = null;
			//= Files.newBufferedWriter(Paths.get(fileName2));
			String strLine;
			String commonName = "";
			int count = 0;
			while ((strLine = br.readLine()) != null)   {
				count++;
				//System.out.println(count+commonName + ": CommonName");
				
				if(!commonName.equals(strLine)) {
					commonName = strLine;
					fileName2 = "data/test2"+commonName+".txt";
					System.out.println("File name "+fileName2);
					if (bw != null) {
						bw.flush();
					}			
					bw = Files.newBufferedWriter(Paths.get(fileName2));
					
					//System.out.println(commonName + "if CommonName");
				} 
				bw.write(strLine);
				bw.write("\n");
				
			}
			bw.flush();
			br.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
        
	}
	
}
