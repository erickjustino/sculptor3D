#include "sculptor.h"
#include "math.h"
#include <fstream>
#include <iostream>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
  nx = _nx;
  ny = _ny;
  nz = _nz;

  v = new Voxel **[nx];
  for (int i = 0; i < nx; i++) {
    v[i] = new Voxel *[ny];
    for (int j = 0; j < ny; j++) {
      v[i][j] = new Voxel[nz];
    }
  }
}

Sculptor::~Sculptor() {
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      delete[] v[i][j];
    }
    delete[] v[i];
  }
  delete[] v;
}

void Sculptor::setColor(float r_, float g_, float b_, float a_) {
  r = r_;
  g = g_;
  b = b_;
  a = a_;
}

void Sculptor::putVoxel(int x_, int y_, int z_) {
  if (x_ >= 0 && x_ < nx && y_ >= 0 && y_ < ny && z_ >= 0 && z_ < nz) {
    v[x_][y_][z_].show = true;
    v[x_][y_][z_].r = r;
    v[x_][y_][z_].g = g;
    v[x_][y_][z_].b = b;
    v[x_][y_][z_].a = a;
  }

  else {
    std::cout << "Digite um valor válido" << std::endl;
  }
}

void Sculptor::cutVoxel(int x, int y, int z) {
  if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
    v[x][y][z].show = false;
  } else {
    std::cout << "Digite um valor válido" << std::endl;
  }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int xi = x0; xi <= x1; xi++) {
    for (int yi = y0; yi <= y1; yi++) {
      for (int zi = z0; zi <= z1; zi++) {
        v[xi][yi][zi].r = r;
        v[xi][yi][zi].g = g;
        v[xi][yi][zi].b = b;
        v[xi][yi][zi].a = a;
        v[xi][yi][zi].show = true;
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  for (int xi = x0; xi <= x1; xi++) {
    for (int yi = y0; yi <= y1; yi++) {
      for (int zi = z0; zi <= z1; zi++) {
        v[xi][yi][zi].show = false;
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int x = xcenter - radius; x <= xcenter + radius; x++) {
    for (int y = ycenter - radius; y <= ycenter + radius; y++) {
      for (int z = zcenter - radius; z <= zcenter + radius; z++) {
        if ((x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) +
                (z - zcenter) * (z - zcenter) <=
            radius * radius) {
          if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
            v[x][y][z].r = r;
            v[x][y][z].g = g;
            v[x][y][z].b = b;
            v[x][y][z].a = a;
            v[x][y][z].show = true;
          }
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
  for (int x = xcenter - radius; x <= xcenter + radius; x++) {
    for (int y = ycenter - radius; y <= ycenter + radius; y++) {
      for (int z = zcenter - radius; z <= zcenter + radius; z++) {
        if ((x - xcenter) * (x - xcenter) + (y - ycenter) * (y - ycenter) +
                (z - zcenter) * (z - zcenter) <=
            radius * radius) {
          if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
            v[x][y][z].show = false;
          }
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  for (int xi = xcenter - rx; xi <= xcenter + rx; xi++) {
    for (int yi = ycenter - ry; yi <= ycenter + ry; yi++) {
      for (int zi = zcenter - rz; zi <= zcenter + rz; zi++) {
        if (pow(xi - xcenter, 2) / (float)pow(rx, 2) +
                pow(yi - ycenter, 2) / (float)pow(ry, 2) +
                pow(zi - zcenter, 2) / (float)pow(rz, 2) <=
            1) {
          putVoxel(xi, yi, zi);
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  for (int xi = xcenter - rx; xi <= xcenter + rx; xi++) {
    for (int yi = ycenter - ry; yi <= ycenter + ry; yi++) {
      for (int zi = zcenter - rz; zi <= zcenter + rz; zi++) {
        if (pow(xi - xcenter, 2) / (float)pow(rx, 2) +
                pow(yi - ycenter, 2) / (float)pow(ry, 2) +
                pow(zi - zcenter, 2) / (float)pow(rz, 2) <=
            1) {
          cutVoxel(xi, yi, zi);
        }
      }
    }
  }
}

void Sculptor::writeOFF(const char *filename) {
  int n_vertices = 0;
  int n_faces = 0;
  int ni = 0;
  float r, g, b, a;

  ofstream fout(filename);
  if (fout.is_open()) {
    fout << "OFF" << std::endl;
    for (int i = 0; i < nx; i++) {
      for (int j = 0; j < ny; j++) {
        for (int k = 0; k < nz; k++) {
          if (v[i][j][k].show) {
            n_vertices += 8;
            n_faces += 6;
          }
        }
      }
    }

    fout << n_vertices << " " << n_faces << " 0\n";

    for (int xi = 0; xi < nx; xi++) {
      for (int yi = 0; yi < ny; yi++) {
        for (int zi = 0; zi < nz; zi++) {
          if (v[xi][yi][zi].show) {
            fout << xi - 0.5 << " " << yi + 0.5 << " " << zi - 0.5 << std::endl;
            fout << xi - 0.5 << " " << yi - 0.5 << " " << zi - 0.5 << std::endl;
            fout << xi + 0.5 << " " << yi - 0.5 << " " << zi - 0.5 << std::endl;
            fout << xi + 0.5 << " " << yi + 0.5 << " " << zi - 0.5 << std::endl;
            fout << xi - 0.5 << " " << yi + 0.5 << " " << zi + 0.5 << std::endl;
            fout << xi - 0.5 << " " << yi - 0.5 << " " << zi + 0.5 << std::endl;
            fout << xi + 0.5 << " " << yi - 0.5 << " " << zi + 0.5 << std::endl;
            fout << xi + 0.5 << " " << yi + 0.5 << " " << zi + 0.5 << std::endl;
          }
        }
      }
    }

    for (int xi = 0; xi < nx; xi++) {
      for (int yi = 0; yi < ny; yi++) {
        for (int zi = 0; zi < nz; zi++) {
          if (v[xi][yi][zi].show) {
            r = v[xi][yi][zi].r;
            g = v[xi][yi][zi].g;
            b = v[xi][yi][zi].b;
            a = v[xi][yi][zi].a;
            fout << "4 " << 0 + ni << " " << 3 + ni << " " << 2 + ni << " "
                 << 1 + ni << " " << r << " " << g << " " << b << " " << a
                 << std::endl;
            fout << "4 " << 4 + ni << " " << 5 + ni << " " << 6 + ni << " "
                 << 7 + ni << " " << r << " " << g << " " << b << " " << a
                 << std::endl;
            fout << "4 " << 0 + ni << " " << 1 + ni << " " << 5 + ni << " "
                 << 4 + ni << " " << r << " " << g << " " << b << " " << a
                 << std::endl;
            fout << "4 " << 0 + ni << " " << 4 + ni << " " << 7 + ni << " "
                 << 3 + ni << " " << r << " " << g << " " << b << " " << a
                 << std::endl;
            fout << "4 " << 3 + ni << " " << 7 + ni << " " << 6 + ni << " "
                 << 2 + ni << " " << r << " " << g << " " << b << " " << a
                 << std::endl;
            fout << "4 " << 1 + ni << " " << 2 + ni << " " << 6 + ni << " "
                 << 5 + ni << " " << r << " " << g << " " << b << " " << a
                 << std::endl;
            ni += 8;
          }
        }
      }
    }
    std::cout << "Projeto gerado com sucesso!" << std::endl;
  } else {
    std::cerr << "Não foi possível abrir o arquivo" << std::endl;
  }
  fout.close();
}