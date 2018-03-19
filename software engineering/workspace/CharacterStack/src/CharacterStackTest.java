import static org.junit.Assert.*;

import org.junit.Test;

public class CharacterStackTest {

	@Test
	public void test() {
		char testChar = '3';
		String testStr= "Hello World";
		String overflowtestStr= "If the implementation is easy to explain, it may be a good idea.";
								 		
		CharacterStack characterstack1 = new CharacterStack();
		CharacterStack characterstack2 = new CharacterStack();
        CharacterStack characterstack1_arrow;
        characterstack1_arrow = characterstack1;
        
		// assertNotNull test
		assertNotNull( characterstack1); 

		// assertSame test
	    assertSame(characterstack1,characterstack1_arrow);	
		// assertNotSame test
	    assertNotSame(characterstack1,characterstack2);	

		// assertEquals test
		characterstack1.push(testChar);
		assertEquals( '3' , characterstack1.pop());
		characterstack1.push(testStr);
		
		
		assertEquals( 11 , characterstack1.getSize()); // Hello World string 의 size
		
		assertEquals( 'd', characterstack1.pop());
		assertEquals( 'l', characterstack1.pop());
		assertEquals( 'r', characterstack1.pop());
		assertEquals( 'o', characterstack1.pop());
		assertEquals( 'W', characterstack1.pop());
		assertEquals( ' ', characterstack1.pop());
		assertEquals( 'o', characterstack1.pop());
		assertEquals( 'l', characterstack1.pop());
		assertEquals( 'l', characterstack1.pop());
		assertEquals( 'e', characterstack1.pop());

		// assertTrue test
		assertTrue(characterstack1.pop() == 'H'); // 마지막 H
		assertTrue(characterstack1.getMaxSize() == 20);  
		
		// assertNotNull 테스트를 위해 강제 Null 화 시킴 
		characterstack1 = null;
		assertNull( characterstack1 ); 
		//fail("Not yet implemented");
	}

	@Test
	public void test1() {
		
	}
}