/**
 * 
 * @author JongHyeon Yeo 
 * Created by jonghyeon yeo on 18/03/24.
 * Report: Cannot find abnormal states on these 'state coverage test'.
 * 
 * 
 */


import static org.junit.Assert.*;


import java.io.IOException;

import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

public class StateCoverageTest {

	private static StringStack strStack; 

	@BeforeClass
	public static void init() {
		strStack =  new StringStack();
	}

    @Test
	public void EmptyStackStateCases() {
		strStack =  new StringStack();
		assertEquals( 0 , strStack.getSize()) ; 
		assertEquals( "", strStack.pop()) ; 
	}  

    @Test
 	public void FilledStackStateCases() {
		EmptyStackStateCases();
		String str = "test";
		strStack.push(str);
		strStack.push(str);
		strStack.push(str);
		assertEquals( 3 , strStack.getSize()) ; 
		assertEquals( "test" , strStack.pop()) ; 
	}  
    
	@Test
	public void FulledStackTestCases() {
		int startSize;
		FilledStackStateCases();
		startSize = strStack.getSize();
	    for(int i = startSize; i < strStack.getMaxSize(); i++)
		{
	    	if(strStack.getSize() < strStack.getMaxSize())
			strStack.push("toMax");
		}
		assertEquals( strStack.getMaxSize(), strStack.getSize()) ; 
		assertEquals( 20, strStack.getSize()) ; 
	}
	
}