/**
 * 
 * @author JongHyeonYeo 
 * Created by jonghyeon yeo on 18/03/24.
 * 
 * Convention: 
 * Transitions method name: ($previousStateName)To($nextStateName) + (By($WayOfTransit))-optional
 * 
 * Report: Two abnormal transition are discovered on 'Transition Coverage test'.
 * 1. filledToEmptyTest 
 * 2. fullToFilledTest 
 * 
 * And These transition fails makes 'transition fair coverage' fails.
 *  
 * It seems 'strStack.pop()' makes abnormal behavior 
 * 
 * Todo: 
 * 1. find a way to check stackoverflow error on transition coverage test 
 * In this test, I made OverflowedStackTest method, then ran coverage check tool(jacoco)
 * and checked Faiure Trace on JUnit
 * 
 * 2. To check some hiding error on filled to filled. 
 *
 * 
 * Every testing cases are self documented, but if you don't understand any method,
 * Please mail to 'jonghyeon.rw@gmail.com'
 * 
 */

import static org.junit.Assert.*;

import org.junit.Test;
import java.io.IOException;

import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;


public class TransitionPairCoverageTest {

	private static StringStack strStack; 


	// from init
	@Test
	public void initToEmptyTestByDefaltInitialzer() {
		strStack =  new StringStack();
		assertEquals( 0 , strStack.getSize()) ; 
		assertTrue(strStack.isEmpty()); 
	}

	@Test
	public void initToEmptyTestByNull() {
		String str = null; 
		strStack =  new StringStack(str);
		assertEquals( 0 , strStack.getSize()) ; 
		assertTrue(strStack.isEmpty()); 
	}

	@Test
	public void initToFilledTest() {
		String str = "asdf"; 
		strStack =  new StringStack(str);

		assertEquals( 1 , strStack.getSize()) ; 
	}

	// from empty
	@Test
	public void emptyToEmptyTest() {
        initToEmptyTestByNull();
		strStack =  new StringStack();
    	assertEquals( "", strStack.pop());
		assertEquals( 0 , strStack.getSize()) ; 
		assertTrue(strStack.isEmpty()); 
	}

    @Test
	public void emptyToFilledByStrTest() {
    	int preSize, nextSize;
        initToEmptyTestByNull();
		preSize = strStack.getSize();

		//test
		assertEquals( 0 , preSize) ; 
		assertEquals( 0 , strStack.getSize()) ; 

    	strStack.push("asdf");

    	nextSize = strStack.getSize();
		assertEquals( 1 , nextSize) ; 
		assertEquals( 1 , strStack.getSize()) ; 

	}

    @Test
	public void emptyToFilledByCharTest() {
    	
    	int preSize, nextSize;
        initToEmptyTestByNull();
		strStack =  new StringStack();
    	// initialized
		char alphabet = 'a';
		
		//test
		preSize = strStack.getSize();
		assertEquals( 0 , preSize) ; 
		assertEquals( 0 , strStack.getSize()) ; 

    	strStack.push(alphabet);

    	nextSize = strStack.getSize();
		assertEquals( 1 , nextSize) ; 
		assertEquals( 1 , strStack.getSize()) ; 
	}
    
    
    // from filled
    @Test
 	public void filledToFilledByStrTest() {
    	int preSize = 0, nextSize = 0;

    	emptyToFilledByCharTest();
		preSize = strStack.getSize();
    	strStack.push("asdf");
    	nextSize = strStack.getSize();

		assertEquals( preSize+1 , nextSize); 
		assertEquals( 2 , strStack.getSize()) ; 
	}  

    @Test
 	public void filledToFilledByChrTest() {
    	
    	int preSize = 0, nextSize = 0;
		char alphabet = 'a';

    	emptyToFilledByCharTest();
		preSize = strStack.getSize();
		strStack.push(alphabet);
    	nextSize = strStack.getSize();

		assertEquals( preSize+1 , nextSize); 
		assertEquals( 2 , strStack.getSize()) ; 
	}  

 	@Test
 	public void filledToFilledByPopTest() {
    	int preSize = 0, nextSize = 0;
	    
    	filledToFilledByChrTest(); 
		preSize = strStack.getSize();
		
    	if( 1 < preSize && preSize < 20)
    	{
			assertEquals( "a", strStack.pop());
			nextSize = strStack.getSize();
			assertEquals( preSize-1 , nextSize); 
    	}
    	

	   	filledToFilledByStrTest(); 
		preSize = strStack.getSize();
    	if( 1 < preSize && preSize < 20)
    	{
			assertEquals( "asdf", strStack.pop());
			nextSize = strStack.getSize();
			assertEquals( preSize-1 , nextSize); 
    	}
    } 
 	
 	@Test
  	public void filledToEmptyTest() {
    	int preSize = 0, nextSize = 0;
    
    	emptyToFilledByCharTest();
		preSize = strStack.getSize();
    	if( 1 == preSize )
    	{
    		preSize = strStack.getSize();
			strStack.pop();
			nextSize = strStack.getSize();
			assertEquals( preSize-1 , nextSize); 
			assertEquals( 0, nextSize); 
			assertTrue( strStack.isEmpty()); 
		}
	}
			 
  
 	/* note: It cannot coverage all the char values. 
 	 * try to change it with boundary char value
 	 */
	@Test
	public void filledToFullByCharTest() {
    	int preSize = 0, nextSize = 0;

    	// Move to Filled 
    	filledToFilledByChrTest(); 
		preSize = strStack.getSize();

		char chars[] = 
		{
			 'a', 'b', 'c', 'd',
			 'e', 'f', 'g', 'h',
			 'i', 'j', 'k', 'l',
			 'n', 'm', 'o', 'p',
			 'q', 'r', 's', 't',
			 'u', 'v', 'w', 'x',
			 'y', 'z', '0', '1',
		};
		
		int i = 0;
		while(strStack.getSize()<strStack.getMaxSize()-1)
		{
			i++;
			strStack.push(chars[i]);
		}
		preSize = strStack.getSize();
		
		if( strStack.getMaxSize() - 1 == preSize )
		{
			preSize = strStack.getSize();
			strStack.push('t');
			nextSize = strStack.getSize();
			assertEquals( preSize , nextSize-1); 

			// full Test
			assertEquals( 20 , strStack.getSize()) ; 
			assertEquals( strStack.getMaxSize(), strStack.getSize()) ; 
			assertTrue(strStack.isFull());
		}	
	}
	
	//from 
	@Test
	public void filledToFullByStrTest() {
		int preSize = 0, nextSize = 0;

    	// Move to Filled 
    	filledToFilledByChrTest(); 
		preSize = strStack.getSize();
		
		String strs[] = 
		{
				"test1","test2","test3","test4","test5","test6",
				"test7","test8","test9","test10","test11",
				"test12", "test13", "test14", "test15", "test16",
				"test17", "test18", "test19", "test20", 
				"abundant", "abundant", "abundant", "abundant", "abundant",
				"abundant", "abundant", "abundant", "abundant", "abundant",
				"abundant", "abundant", "abundant", "abundant", "abundant"
				
		};
	
		int i = 0;
		while(strStack.getSize()<strStack.getMaxSize()-1)
		{
			i++;
			strStack.push(strs[i]);
		}
		
     	preSize = strStack.getSize();
		if( strStack.getMaxSize() - 1 == preSize )
		{	
			strStack.push("lastone");
			// full Test
			assertEquals( 20 , strStack.getSize()) ; 
			assertEquals( strStack.getMaxSize(), strStack.getSize()) ; 
			assertTrue(strStack.isFull());
		}
	}

	/* from full */
	@Test
	public void fullToFilledTest() {
		int preSize , nextSize ;
        
		filledToFullByStrTest(); 
		preSize =  strStack.getSize();
		if(preSize == strStack.getMaxSize())
		{
			strStack.pop();
			nextSize = strStack.getSize();
			assertEquals( preSize-1 , nextSize); 
			assertEquals( strStack.getMaxSize() - 1 , strStack.getSize()) ; 
		}
	}

	// Overflow Test
	@Test
	public void OverflowedStackTest() throws IOException  {
		filledToFullByStrTest();
		strStack.push("overflowing abundunt Str");
	}

	// Upper codes are transition coverage test codes.
	// Every methods that written on upper define each transition
	// Compounding upper codes, We can make transition pair coverage test

	@Test
	public void initToemptyByDefaltToEmptyPair(){
		initToEmptyTestByDefaltInitialzer();
		emptyToEmptyTest();
	}	
	@Test
	public void initToemptyByNullToEmptyPair(){
		initToEmptyTestByNull();
		emptyToEmptyTest();
	}
	@Test
	public void filledToemptyToEmptyPair(){
		filledToEmptyTest();
		emptyToEmptyTest();
	}
	@Test
	public void initToEmptyTestByDefaltToFilledByCharPair(){
		initToEmptyTestByDefaltInitialzer();
		emptyToFilledByCharTest();
	}	
	@Test
	public void initToEmptyByNullToFilledByCharPair(){
		initToEmptyTestByNull();
		emptyToFilledByCharTest();
	}
	@Test
	public void emptyToFilledByCharPairs(){
		filledToEmptyTest();
		emptyToEmptyTest();
	}
	
	// To low readability so just added number for checking Transition Pair coverage
	// In fact, I don't know what is the right way to naming these methods.
	@Test
	public void emptyToFilledByStrPair1(){
		initToEmptyTestByDefaltInitialzer();
		emptyToFilledByStrTest();
	}	
	@Test
	public void emptyToFilledByStrPair2(){
		initToEmptyTestByNull();
		emptyToFilledByStrTest();
	}
	@Test
	public void emptyToFilledByStrPair3(){
		filledToEmptyTest();
		emptyToFilledByStrTest();
	}
	@Test
	public void filledToFilledByChrPair1(){
		emptyToFilledByCharTest();
		filledToFilledByChrTest();
	}
	@Test
	public void filledToFilledByChrPair2(){
		emptyToFilledByStrTest();
		filledToFilledByChrTest();
	}	
	@Test
	public void filledToFilledByChrPair3(){
		filledToFilledByChrTest();
		filledToFilledByChrTest();
	}	
	@Test
	public void filledToFilledByChrPair4(){
		filledToFilledByStrTest();
		filledToFilledByChrTest();
	}	
	@Test
	public void filledToFilledByChrPair5(){
		filledToFilledByPopTest();
		filledToFilledByChrTest();
	}	
	@Test
	public void filledToFilledByChrPair6(){
		fullToFilledTest();
		filledToFilledByChrTest();
	}
	@Test
	public void filledToFilledByChrPair7(){
		initToFilledTest();
		filledToFilledByChrTest();
	}	
	@Test	
	public void filledToFilledByPopPair1(){
		emptyToFilledByStrTest();
		filledToFilledByPopTest();
	}	
	@Test
	public void filledToFilledByPopPair2(){
		filledToFilledByChrTest();
		filledToFilledByPopTest();
	}	
	@Test
	public void filledToFilledByPopPair3(){
		filledToFilledByStrTest();
		filledToFilledByPopTest();
	}	
	@Test
	public void filledToFilledByPopPair4(){
		filledToFilledByPopTest();
		filledToFilledByPopTest();
	}	
	@Test
	public void filledToFilledByPopPair5(){
		fullToFilledTest();
		filledToFilledByPopTest();
	}	
	@Test
	public void filledToFilledByPopPair6(){
		initToFilledTest();
		filledToFilledByPopTest();
	}
	
	@Test
	public void filledToEmptyPair1(){
		emptyToFilledByCharTest();
		filledToEmptyTest();
	}	
	@Test
	public void filledToEmptyPair2(){
		emptyToFilledByStrTest();
		filledToEmptyTest();
	}	
	@Test
	public void filledToEmptyPair3(){
		filledToFilledByChrTest();
		filledToEmptyTest();
	}	
	@Test
	public void filledToEmptyPair4(){
		filledToFilledByStrTest();
		filledToEmptyTest();
	}	
	@Test
	public void filledToEmptyPair5(){
		filledToFilledByPopTest();
		filledToEmptyTest();
	}	
	@Test
	public void filledToEmptyPair6(){
		fullToFilledTest();
		filledToEmptyTest();
	}	
	@Test
	public void filledToEmptyPair7(){
		initToFilledTest();
		filledToEmptyTest();
	
	}
	
	@Test
	public void fullToFilledPair1(){
		filledToFullByCharTest();
		fullToFilledTest();
	}	
	@Test
	public void fullToFilledPair2(){
		filledToFullByStrTest();
		fullToFilledTest();
	}
	
	@Test
	public void filledToFullByStrPair1(){
		emptyToFilledByCharTest();
		filledToFullByStrTest();
	}	
	@Test
	public void filledToFullByStrPair2(){
		emptyToFilledByStrTest();
		filledToFullByStrTest();
	}	

	@Test
	public void filledToFullByStrPair3(){
		filledToFilledByChrTest();
		filledToFullByStrTest();
	}	

	@Test
	public void filledToFullByStrPair4(){
		filledToFilledByStrTest();
		filledToFullByStrTest();
	}
	
	@Test
	public void filledToFullByStrPair5(){
		filledToFilledByPopTest();
		filledToFullByStrTest();
	}	

	@Test
	public void filledToFullByStrPair6(){
		fullToFilledTest();
		filledToFullByStrTest();
	}	

	@Test
	public void filledToFullByStrPair7(){
		initToFilledTest();
		filledToFullByStrTest();
	}

	@Test
	public void filledToFilledByStrPair1(){
		emptyToFilledByCharTest();
		filledToFilledByStrTest();
	}	
	@Test
	public void filledToFilledByStrPair2(){
		emptyToFilledByStrTest();
		filledToFilledByStrTest();
	}	
	@Test
	public void filledToFilledByStrPair3(){
		filledToFilledByChrTest();
		filledToFilledByStrTest();
	}	
	@Test
	public void filledToFilledByStrPair4(){
		filledToFilledByStrTest();
		filledToFilledByStrTest();
	}
	
	@Test
	public void filledToFilledByStrPair5(){
		filledToFilledByPopTest();
		filledToFilledByStrTest();
	}	
	@Test
	public void filledToFilledByStrPair6(){
		fullToFilledTest();
		filledToFilledByStrTest();
	}	
	@Test
	public void filledToFilledByStrPair7(){
		initToFilledTest();
		filledToFilledByStrTest();
	}

	@Test
	public void filledToFullByCharPair1(){
		emptyToFilledByCharTest();
		filledToFullByCharTest();
	}
	
	@Test
	public void filledToFullByCharPair2(){
		emptyToFilledByStrTest();
		filledToFullByCharTest();
    }	
	@Test
	public void filledToFullByCharPair3(){
		filledToFilledByChrTest();
		filledToFullByCharTest();
    }	
	@Test
	public void filledToFullByCharPair4(){
		filledToFilledByStrTest();
		filledToFullByCharTest();
    }	
	@Test
	public void filledToFullByCharPair5(){
		filledToFilledByPopTest();
		filledToFullByCharTest();
	}	
	@Test
	public void filledToFullByCharPair6(){
		fullToFilledTest();
		filledToFullByCharTest();
	}	
	@Test
	public void filledToFullByCharPair7(){
		initToFilledTest();
		filledToFullByCharTest();
	}
}