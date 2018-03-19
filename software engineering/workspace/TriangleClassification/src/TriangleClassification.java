
public class TriangleClassification {

	int triangle(int a, int b, int c) {
		int perim;
		int tri_kind = 0; 

		if (a > 0) {
			if (b > 0) {
				if (c > 0) {
					perim = a + b + c;
					if ((2 * a) < perim) {
						if ((2 * b) < perim) {
							if ((2 * c) < perim) {
								if (a == b) {
									if (b == c) {
										tri_kind = 2;
									} else {
										tri_kind = 1;
									}
								} else if (a == c) {
									tri_kind = 1;
								} else if (b == c) {
									tri_kind = 1;
								} else {
									if ((a * a + b * b) == (c * c)) {
										tri_kind = 3;
									} else if ((b * b + c * c) == (a * a)) {
										tri_kind = 3;
									} else if ((a * a + c * c) == (b * b)) {
										tri_kind = 3;
									} else {
										tri_kind = 4;
									}
								}
							} else {
							}
						} else {
						}
					} else {
					}
				} else {
				}
			} else {
			}
		} else {
		}
		return tri_kind;
	}
}
