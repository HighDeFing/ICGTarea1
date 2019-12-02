#include "Triangle.h"
#include <math.h> 
#include <algorithm> 
CTriangle::CTriangle()
{

	mVertices = new float* [3];
	for (int i = 0; i < 3; ++i)
		mVertices[i] = new float[2];

	mType = TRIANGLE;
}

CTriangle::~CTriangle()
{
	for (int i = 0; i < 3; ++i)
		delete[] mVertices[i];
}

void CTriangle::box() {

}

void CTriangle::display()
{
	int x1, x2, y1, y2, x3, y3;
	
	x1 = int(mVertices[0][0]); x2 = long long int(mVertices[1][0]); y1 = long long int(mVertices[0][1]); y2 = long long int(mVertices[1][1]);
	x3 = int(mVertices[2][0]); y3 = long long int(mVertices[2][1]);
	if (bfill) {
		fill();
	}
	draw_triangle(x1, x2, x3, y1, y2, y3);
}

void CTriangle::draw_pixel( int x,int y) {
	glColor3fv(mColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CTriangle::draw_fpixel(int x, int y) {
	glColor3fv(fColor);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void CTriangle::draw_fline(int x1, int y1, int x2, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_fpixel(x, y);
		e = (dy << 1) - dx;
		inc1 = (dy - dx) << 1;
		inc2 = dy << 1;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_fpixel(x, y);
		}

	}
	else {
		draw_fpixel(x, y);
		e = (dx << 1) - dy;
		inc1 = (dx - dy) << 1;
		inc2 = dx << 1;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_fpixel(x, y);
		}
	}
}


void CTriangle::draw_line(long long int x1, long long int x2,long long int y1,long long int y2) {
	long long int dx, dy, i, e;
	long long int incx, incy, inc1, inc2;
	long long int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = (dy << 1) - dx;
		inc1 = (dy - dx) << 1;
		inc2 = dy << 1;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	}
	else {
		draw_pixel(x, y);
		e = (dx << 1) - dy;
		inc1 = (dx - dy) << 1;
		inc2 = dx << 1;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}


void CTriangle::draw_triangle(long long int x1,long long int x2, long long int x3, long long int y1, long long int y2, long long int y3) {
	draw_line(x1, x2, y1, y2);
	draw_line(x1, x3, y1, y3);
	draw_line(x2, x3, y2, y3);
}

void CTriangle::fill(){

	int pasoy;
	int pasox;
	int pasoy2;
	int pasox2;
	int x1 = mVertices[0][0];
	int x2 = mVertices[1][0];
	int x3 = mVertices[2][0], y1 = mVertices[0][1], y2 = mVertices[1][1], y3 = mVertices[2][1];
	if (std::min((y1, y2), std::min(y2, y3)) == y2) {
		x1 = mVertices[1][0]; x2 = mVertices[0][0];
		y1 = mVertices[1][1]; y2 = mVertices[0][1];
	}
	if (std::min(std::min(y1, y3), std::min(y2, y3)) == y3) {
		x1 = mVertices[2][0]; x3 = mVertices[0][0];
		y1 = mVertices[2][1]; y3 = mVertices[0][1];

	}
	int deltaX = (x2 - x1);
	int deltaY = (y2 - y1);
	int deltaX2 = (x3 - x1);
	int deltaY2 = (y3 - y1);
	if (deltaY < 0) {
		deltaY = -deltaY;
		pasoy = -1;


	}
	else {
		pasoy = 1;
	}


	if (deltaX < 0) {
		deltaX = -deltaX;
		pasox = -1;
	}
	else {
		pasox = 1;
	}
	if (deltaY2 < 0) { //otros puntos
		deltaY2 = -deltaY2;
		pasoy2 = -1;


	}
	else {
		pasoy2 = 1;
	}


	if (deltaX2 < 0) {
		deltaX2 = -deltaX2;
		pasox2 = -1;
	}
	else {
		pasox2 = 1;
	}
	int x = x1;
	int y = y1;
	int xx = x;
	int yy = y;
	int p2;
	int incE2;
	int incNE2;

	if (deltaX > deltaY) {

		int p = 2 * deltaY - deltaX;
		int incE = 2 * deltaY;
		int incNE = 2 * (deltaY - deltaX);
		if (deltaX2 > deltaY2) {
			p2 = 2 * deltaY2 - deltaX2;
			incE2 = 2 * deltaY2;
			incNE2 = 2 * (deltaY2 - deltaX2);

			while (x != x2 && xx != x3) {

				x = x + pasox;
				xx = xx + pasox2;
				if (p < 0) {
					p = p + incE;
				}
				else {
					y = y + pasoy;
					p = p + incNE;
				}
				if (p2 < 0) {
					p2 = p2 + incE2;
				}
				else {
					yy = yy + pasoy2;
					p2 = p2 + incNE2;
				}
				while (y != yy && x != x2 && xx != x3) {
					if (y > yy) {
						xx = xx + pasox2;
						if (p2 < 0) {
							p2 = p2 + incE2;
						}
						else {
							yy = yy + pasoy2;
							p2 = p2 + incNE2;
						}
					}
					if (yy > y) {

						x = x + pasox;
						if (p < 0) {
							p = p + incE;
						}
						else {
							y = y + pasoy;
							p = p + incNE;
						}
					}
				}
				if (x > xx)
					draw_fline((x - 1), y, (xx + 1), yy);
				else draw_fline(x + 1, y, xx - 1, yy);
			}


		}
		else {
			p2 = 2 * deltaX2 - deltaY2;
			incE2 = 2 * deltaX2;
			incNE2 = 2 * (deltaX2 - deltaY2);

			while (x != x2 && yy != y3) {
				x = x + pasox;
				yy = yy + pasoy2;
				if (p < 0) {
					p = p + incE;
				}
				else {
					y = y + pasoy;
					p = p + incNE;
				}
				if (p2 < 0) {
					p2 = p2 + incE2;
				}
				else {
					xx = xx + pasox2;
					p2 = p2 + incNE2;
				}
				while (y != yy && x != x2 && yy != y3) {
					if (y > yy) {
						yy = yy + pasoy2;
						if (p2 < 0) {
							p2 = p2 + incE2;
						}
						else {
							xx = xx + pasox2;
							p2 = p2 + incNE2;
						}
					}
					if (yy > y) {

						x = x + pasox;
						if (p < 0) {
							p = p + incE;
						}
						else {
							y = y + pasoy;
							p = p + incNE;
						}
					}
				}
				if (x > xx)
					draw_fline((x - 1), y, (xx + 1), yy);
				else draw_fline(x + 1, y, xx - 1, yy);
			}


		}



	}
	else {

		int p = 2 * deltaX - deltaY;
		int incE = 2 * deltaX;
		int incNE = 2 * (deltaX - deltaY);
		if (deltaX2 > deltaY2) {
			p2 = 2 * deltaY2 - deltaX2;
			incE2 = 2 * deltaY2;
			incNE2 = 2 * (deltaY2 - deltaX2);

			while (y != y2 && xx != x3) {

				y = y + pasoy;
				xx = xx + pasox2;
				if (p < 0) {
					p = p + incE;
				}
				else {
					x = x + pasox;
					p = p + incNE;
				}
				if (p2 < 0) {
					p2 = p2 + incE2;
				}
				else {
					yy = yy + pasoy2;
					p2 = p2 + incNE2;
				}
				while (y != yy && xx != x3 && y != y2) {

					if (y > yy) {
						xx = xx + pasox2;
						if (p2 < 0) {
							p2 = p2 + incE2;
						}
						else {
							yy = yy + pasoy2;
							p2 = p2 + incNE2;
						}
					}
					if (yy > y) {

						y = y + pasoy;
						if (p < 0) {
							p = p + incE;
						}
						else {
							x = x + pasox;
							p = p + incNE;
						}
					}
				}
				if (x > xx)
					draw_fline((x - 1), y, (xx + 1), yy);
				else draw_fline(x + 1, y, xx - 1, yy);
			}
		}
		else {
			p2 = 2 * deltaX2 - deltaY2;
			incE2 = 2 * deltaX2;
			incNE2 = 2 * (deltaX2 - deltaY2);
			while (y != y2 && yy != y3) {
				y = y + pasoy;
				if (p < 0) {
					p = p + incE;
				}
				else {
					x = x + pasox;
					p = p + incNE;
				}
				yy = yy + pasoy2;
				if (p2 < 0) {
					p2 = p2 + incE2;
				}
				else {
					xx = xx + pasox2;
					p2 = p2 + incNE2;
				}
				while (y != yy && y != y2 && yy != y3) {
					if (y > yy) {
						yy = yy + pasoy2;
						if (p2 < 0) {
							p2 = p2 + incE2;
						}
						else {
							xx = xx + pasox2;
							p2 = p2 + incNE2;
						}
					}
					if (yy > y) {

						y = y + pasoy;
						if (p < 0) {
							p = p + incE;
						}
						else {
							x = x + pasox;
							p = p + incNE;
						}
					}
				}
				if (x > xx)
					draw_fline((x - 1), y, (xx + 1), yy);
				else draw_fline(x + 1, y, xx - 1, yy);


			}


		}
	}

	if (x != x2 || y != y2) {
		deltaX = (x1 - x2);
		deltaY = (y1 - y2);
		deltaX2 = (x3 - x2);
		deltaY2 = (y3 - y2);


		if (deltaY < 0) {
			deltaY = -deltaY;
			pasoy = -1;


		}
		else {
			pasoy = 1;
		}


		if (deltaX < 0) {
			deltaX = -deltaX;
			pasox = -1;
		}
		else {
			pasox = 1;
		}
		if (deltaY2 < 0) { //otros puntos
			deltaY2 = -deltaY2;
			pasoy2 = -1;


		}
		else {
			pasoy2 = 1;
		}


		if (deltaX2 < 0) {
			deltaX2 = -deltaX2;
			pasox2 = -1;
		}
		else {
			pasox2 = 1;
		}
		x = x2;
		y = y2;
		xx = x;
		yy = y;

		if (deltaX > deltaY) {

			int p = 2 * deltaY - deltaX;
			int incE = 2 * deltaY;
			int incNE = 2 * (deltaY - deltaX);
			if (deltaX2 > deltaY2) {
				p2 = 2 * deltaY2 - deltaX2;
				incE2 = 2 * deltaY2;
				incNE2 = 2 * (deltaY2 - deltaX2);

				while (x != x1 && xx != x3) { //nunca caeraaaaaa
					x = x + pasox;
					xx = xx + pasox2;
					if (p < 0) {
						p = p + incE;
					}
					else {
						y = y + pasoy;
						p = p + incNE;
					}
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						yy = yy + pasoy2;
						p2 = p2 + incNE2;
					}
					while (y != yy && x != x1 && xx != x3) {
						if (y < yy) {
							xx = xx + pasox2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								yy = yy + pasoy2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							x = x + pasox;
							if (p < 0) {
								p = p + incE;
							}
							else {
								y = y + pasoy;
								p = p + incNE;
							}
						}
					}
					draw_fline(x, y, xx, yy);
				}


			}
			else {
				p2 = 2 * deltaX2 - deltaY2;
				incE2 = 2 * deltaX2;
				incNE2 = 2 * (deltaX2 - deltaY2);

				while (x != x1 && yy != y3) {
					x = x + pasox;
					yy = yy + pasoy2;
					if (p < 0) {
						p = p + incE;
					}
					else {
						y = y + pasoy;
						p = p + incNE;
					}
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						xx = xx + pasox2;
						p2 = p2 + incNE2;
					}
					while (y != yy && x != x1 && yy != y3) {
						if (y < yy) {

							yy = yy + pasoy2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								xx = xx + pasox2;
								p2 = p2 + incNE2;
							}

						}
						if (yy < y) {

							x = x + pasox;
							if (p < 0) {
								p = p + incE;
							}
							else {
								y = y + pasoy;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);
				}


			}



		}
		else {

			int p = 2 * deltaX - deltaY;
			int incE = 2 * deltaX;
			int incNE = 2 * (deltaX - deltaY);
			if (deltaX2 > deltaY2) {
				p2 = 2 * deltaY2 - deltaX2;
				incE2 = 2 * deltaY2;
				incNE2 = 2 * (deltaY2 - deltaX2);

				while (y != y1 && xx != x3) {
					y = y + pasoy;
					xx = xx + pasox2;
					if (p < 0) {
						p = p + incE;
					}
					else {
						x = x + pasox;
						p = p + incNE;
					}
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						yy = yy + pasoy2;
						p2 = p2 + incNE2;
					}
					while (y != yy && y != y1 && xx != x3) {

						if (y < yy) {
							xx = xx + pasox2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								yy = yy + pasoy2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							y = y + pasoy;
							if (p < 0) {
								p = p + incE;
							}
							else {
								x = x + pasox;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);
				}
			}
			else {
				p2 = 2 * deltaX2 - deltaY2;
				incE2 = 2 * deltaX2;
				incNE2 = 2 * (deltaX2 - deltaY2);
				while (y != y1 && yy != y3) {
					y = y + pasoy;
					if (p < 0) {
						p = p + incE;
					}
					else {
						x = x + pasox;
						p = p + incNE;
					}
					yy = yy + pasoy2;
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						xx = xx + pasox2;
						p2 = p2 + incNE2;
					}
					while (y != yy && y != y1 && yy != y3) {
						if (y < yy) {
							yy = yy + pasoy2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								xx = xx + pasox2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							y = y + pasoy;
							if (p < 0) {
								p = p + incE;
							}
							else {
								x = x + pasox;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);


				}


			}
		}
	}
	else {
		deltaX = (x1 - x3);
		deltaY = (y1 - y3);
		deltaX2 = (x2 - x3);
		deltaY2 = (y2 - y3);


		if (deltaY < 0) {
			deltaY = -deltaY;
			pasoy = -1;


		}
		else {
			pasoy = 1;
		}


		if (deltaX < 0) {
			deltaX = -deltaX;
			pasox = -1;
		}
		else {
			pasox = 1;
		}
		if (deltaY2 < 0) { //otros puntos
			deltaY2 = -deltaY2;
			pasoy2 = -1;


		}
		else {
			pasoy2 = 1;
		}


		if (deltaX2 < 0) {
			deltaX2 = -deltaX2;
			pasox2 = -1;
		}
		else {
			pasox2 = 1;
		}
		x = x3;
		y = y3;
		xx = x;
		yy = y;

		if (deltaX > deltaY) {

			int p = 2 * deltaY - deltaX;
			int incE = 2 * deltaY;
			int incNE = 2 * (deltaY - deltaX);
			if (deltaX2 > deltaY2) {
				p2 = 2 * deltaY2 - deltaX2;
				incE2 = 2 * deltaY2;
				incNE2 = 2 * (deltaY2 - deltaX2);

				while (x != x1 && xx != x2) {

					x = x + pasox;
					xx = xx + pasox2;
					if (p < 0) {
						p = p + incE;
					}
					else {
						y = y + pasoy;
						p = p + incNE;
					}
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						yy = yy + pasoy2;
						p2 = p2 + incNE2;
					}
					while (y != yy && x != x1 && xx != x2) {
						if (y < yy) {
							xx = xx + pasox2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								yy = yy + pasoy2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							x = x + pasox;
							if (p < 0) {
								p = p + incE;
							}
							else {
								y = y + pasoy;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);
				}


			}
			else {
				p2 = 2 * deltaX2 - deltaY2;
				incE2 = 2 * deltaX2;
				incNE2 = 2 * (deltaX2 - deltaY2);

				while (x != x1 && yy != y2) {
					x = x + pasox;
					yy = yy + pasoy2;
					if (p < 0) {
						p = p + incE;
					}
					else {
						y = y + pasoy;
						p = p + incNE;
					}
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						xx = xx + pasox2;
						p2 = p2 + incNE2;
					}
					while (y != yy && x != x1 && yy != y2) {
						if (y < yy) {
							yy = yy + pasoy2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								xx = xx + pasox2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							x = x + pasox;
							if (p < 0) {
								p = p + incE;
							}
							else {
								y = y + pasoy;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);
				}


			}



		}
		else {

			int p = 2 * deltaX - deltaY;
			int incE = 2 * deltaX;
			int incNE = 2 * (deltaX - deltaY);
			if (deltaX2 > deltaY2) {
				p2 = 2 * deltaY2 - deltaX2;
				incE2 = 2 * deltaY2;
				incNE2 = 2 * (deltaY2 - deltaX2);

				while (y != y1 && xx != x2) {

					y = y + pasoy;
					xx = xx + pasox2;
					if (p < 0) {
						p = p + incE;
					}
					else {
						x = x + pasox;
						p = p + incNE;
					}
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						yy = yy + pasoy2;
						p2 = p2 + incNE2;
					}
					while (y != yy && y != y1 && xx != x2) {

						if (y < yy) {
							xx = xx + pasox2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								yy = yy + pasoy2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							y = y + pasoy;
							if (p < 0) {
								p = p + incE;
							}
							else {
								x = x + pasox;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);
				}
			}
			else {
				p2 = 2 * deltaX2 - deltaY2;
				incE2 = 2 * deltaX2;
				incNE2 = 2 * (deltaX2 - deltaY2);
				while (y != y1 && yy != y2) {
					y = y + pasoy;
					if (p < 0) {
						p = p + incE;
					}
					else {
						x = x + pasox;
						p = p + incNE;
					}
					yy = yy + pasoy2;
					if (p2 < 0) {
						p2 = p2 + incE2;
					}
					else {
						xx = xx + pasox2;
						p2 = p2 + incNE2;
					}
					while (y != yy && y != y1 && yy != y2) {
						if (y < yy) {
							yy = yy + pasoy2;
							if (p2 < 0) {
								p2 = p2 + incE2;
							}
							else {
								xx = xx + pasox2;
								p2 = p2 + incNE2;
							}
						}
						if (yy < y) {

							y = y + pasoy;
							if (p < 0) {
								p = p + incE;
							}
							else {
								x = x + pasox;
								p = p + incNE;
							}
						}
					}
					if (x > xx)
						draw_fline((x - 1), y, (xx + 1), yy);
					else draw_fline(x + 1, y, xx - 1, yy);


				}


			}
		}
	}
}
