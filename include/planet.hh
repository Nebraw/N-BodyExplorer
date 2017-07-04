#pragma once

#include <cmath>

class Planet
{
public:
  Planet();
  Planet(int masse,
         double px, double py, double pz,
         double vx, double vy, double vz);

  void print() const;


  void set_Vx(long  double Vx);
  void set_Vx(long  double Vx);
  void set_Vx(long  double Vx);

  void add_Vx(long  double Ax);
  void add_Vy(long  double Ay);
  void add_Vz(long  double Az);
    
  void set_Vx(long  double Vx);
  void set_Vx(long  double Vx);
  void set_Vx(long  double Vx);

  void add_Px(long  double Vx);
  void add_Py(long  double Vy);
  void add_Pz(long  double Vz);

  long double get_Px();
  long double get_Py();
  long double get_Pz();

  long double get_Vx();
  long double get_Vy();
  long double get_Vz();

private:

  static const int planet_id();

  int masse_;
  unsigned id_;
  
  long double px_;
  long double py_;
  long double pz_;
  
  long  double vx_ = 0;
  long  double vy_ = 0;
  long double vz_ = 0;
};


//--------------set V-------------------//

inline void Planet::set_Vx(long  double Vx)
{
  vx_ = Vx;
}

inline void Planet::set_Vy(long  double Vy)
{
  vy_ = Vy;
}

inline void Planet::set_Vz(long  double Vz)
{
  vz_ = Vz;
}
//--------------add V-------------------//

inline void Planet::add_Vx(long  double Ax)
{
  vx_ += Ax;
}

inline void Planet::add_Vy(long  double Ay)
{
  vy_ += Ay;
}

inline void Planet::add_Vz(long  double Az)
{
  vz_ += Az;
}

//--------------set Pos-------------------//

inline void Planet::set_Px(long  double Px)
{
  px_ = Px;
}

inline void Planet::set_Py(long  double Py)
{
  py_ = Py;
}

inline void Planet::set_Pz(long  double Pz)
{
  pz_ = Pz;
}

//--------------add Pos-------------------//

inline void Planet::add_Px(long  double Vx)
{
  px_ += Vx;
}

inline void Planet::add_Py(long  double Vy)
{
  py_ += Vy;
}

inline void Planet::add_Pz(long  double Vz)
{
  pz_ += Vz;
}
//--------------get Px-------------------//

inline long double Planet::get_Px()
  {
    return px_;
  }
inline long double Planet::get_Py()
  {
    return py_;
  }

inline long double Planet::get_Pz()
  {
    return pz_;
  }
//--------------get Vx-------------------//

inline long double Planet::get_Vx()
  {
    return vx_;
  }
inline long double Planet::get_Vy()
  {
    return vy_;
  }

inline long double Planet::get_Vz()
  {
    return vz_;
  }
