#include "sculptor.h"
#include <iostream>

int main(void) {
  Sculptor s(100, 100, 100);
  s.setColor(0.043, 0.239, 0.961, 1);
  s.putSphere(30, 30, 58, 30);
  s.putEllipsoid(30, 30, 80, 10, 7, 4);

  s.setColor(0.439, 0.439, 0.38, 1);
  s.putSphere(60, 60, 20, 15);
  s.cutSphere(60, 60, 10, 15);

  s.setColor(0.98, 0.98, 0.314, 1);
  s.putSphere(10, 10, 18, 10);
  s.putEllipsoid(10, 10, 20, 8, 4, 2);
  s.cutEllipsoid(10, 10, 20, 8, 4, 2);

  s.setColor(0.949, 0.949, 0.918, 1);
  s.putBox(10, 10, 10, 10, 10, 10);
  s.cutBox(10, 10, 10, 10, 10, 10);

  s.writeOFF("fout.off");
  return 0;
}
