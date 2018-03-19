import static org.junit.Assert.*;

import org.junit.Test;

public class TriangleClassificationTest {

	@Test
	public void testTriangle() {
		TriangleClassification triangleClassification = new TriangleClassification();
		
		//assertEquals( 1 , triangleClassification.triangle(2, 2, 3)); // �̵�ﰢ��
		//assertEquals( 1 , triangleClassification.triangle(2, 3, 2)); // �̵�ﰢ��
		//assertEquals( 1 , triangleClassification.triangle(3, 2, 2)); // �̵�ﰢ��
			

		//fail("Not yet implemented");
	}
	
	@Test
	public void Isoscelestriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();

		assertEquals( 1 , triangleClassification.triangle(2, 2, 3)); // �̵�ﰢ��
		assertEquals( 1 , triangleClassification.triangle(2, 3, 2)); // �̵�ﰢ��
		assertEquals( 1 , triangleClassification.triangle(3, 2, 2)); // �̵�ﰢ��
	}
	
	@Test
	public void EquilateralTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		
		assertEquals( 2 , triangleClassification.triangle(3, 3, 3)); // ���ﰢ��
	}
	
	@Test
	public void RightTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 3 , triangleClassification.triangle(3, 4, 5)); // �����ﰢ��
		assertEquals( 3 , triangleClassification.triangle(61, 60, 11)); // �����ﰢ��
		assertEquals( 3 , triangleClassification.triangle(84, 85, 13)); // �����ﰢ��
	}

	@Test
	public void NoneClassifiyedTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 4 , triangleClassification.triangle(40, 90, 60)); // �����ﰢ��
	}
	
	@Test
	public void InvalideTriangle(){
		TriangleClassification triangleClassification = new TriangleClassification();
		assertEquals( 4 , triangleClassification.triangle(40, 90, 60)); // �����ﰢ��
		assertEquals( 0 , triangleClassification.triangle(1,1,100)); // invalide
	}
}
