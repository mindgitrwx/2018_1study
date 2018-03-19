import static org.junit.Assert.*;

import org.junit.Test;

public class TriangleClassificationTest {

	@Test
	public void testTriangle() {
		TriangleClassification triangleClassification = new TriangleClassification();
		
		//assertEquals( 1 , triangleClassification.triangle(2, 2, 3)); // 이등변삼각형
		//assertEquals( 1 , triangleClassification.triangle(2, 3, 2)); // 이등변삼각형
		//assertEquals( 1 , triangleClassification.triangle(3, 2, 2)); // 이등변삼각형
			

		//fail("Not yet implemented");
	}
	
	@Test
	public void Isoscelestriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();

		assertEquals( 1 , triangleClassification.triangle(2, 2, 3)); // 이등변삼각형
		assertEquals( 1 , triangleClassification.triangle(2, 3, 2)); // 이등변삼각형
		assertEquals( 1 , triangleClassification.triangle(3, 2, 2)); // 이등변삼각형
	}
	
	@Test
	public void EquilateralTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		
		assertEquals( 2 , triangleClassification.triangle(3, 3, 3)); // 정삼각형
	}
	
	@Test
	public void RightTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 3 , triangleClassification.triangle(3, 4, 5)); // 직각삼각형
		assertEquals( 3 , triangleClassification.triangle(61, 60, 11)); // 직각삼각형
		assertEquals( 3 , triangleClassification.triangle(84, 85, 13)); // 직각삼각형
	}

	@Test
	public void NoneClassifiyedTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 4 , triangleClassification.triangle(40, 90, 60)); // 직각삼각형
	}
	
	@Test
	public void InvalideTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 4 , triangleClassification.triangle(40, 90, 60)); // 직각삼각형
		assertEquals( 0 , triangleClassification.triangle(1,1,100)); // invalide
	}
}
