struct Voxel {
  float r, g, b; // Cores do voxel
  float a;       // Transparência do voxel
  bool show;     // Exibição do voxel
};

class Sculptor {

private:
  Voxel ***v;       // Matriz 3D
  int nx, ny, nz;   // Dimensões da matriz
  float r, g, b, a; // Desenho da matriz

public:
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  void setColor(float r, float g, float b, float a);
  void putVoxel(int x, int y, int z);
  void cutVoxel(int x, int y, int z);
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  void writeOFF(const char *filename);
};