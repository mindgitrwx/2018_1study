import static org.junit.Assert.*;

import org.junit.Test;

public class TriangleClassificationTest {

	/* Isoscelestraiangle test */
	@Test
	public void Isoscelestriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 1 , triangleClassification.triangle(2, 2, 3)); 
		assertEquals( 1 , triangleClassification.triangle(2, 3, 2)); 
		assertEquals( 1 , triangleClassification.triangle(3, 2, 2)); 
		
	}
	
	/* EquilateralTriangle test */
	@Test
	public void EquilateralTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		
		assertEquals( 2 , triangleClassification.triangle(3, 3, 3)); 
	}
	
	/* RightTriangle test */
	@Test
	public void RightTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 3 , triangleClassification.triangle(3, 4, 5)); 
		assertEquals( 3 , triangleClassification.triangle(61, 60, 11)); 
		assertEquals( 3 , triangleClassification.triangle(84, 85, 13)); 
	}

	/* NoneClassifiyedTriangle test */
	@Test
	public void NoneClassifiyedTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 4 , triangleClassification.triangle(40, 90, 60)); 
	}
	
	/* InvalideTriangle test */
	@Test
	public void InvalideTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 4 , triangleClassification.triangle(40, 90, 60)); 
		assertEquals( 0 , triangleClassification.triangle(1,1,100)); 
	}
}
