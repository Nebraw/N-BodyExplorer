#include <scene.hh>


Scene::Scene()
{
  frames_ = 0;
}

Scene::~Scene()
{

}

void Scene::add_planet(share_pointer<Planet> p)
{
  planets_.push_back(p);
}

void Scene::destroy_collision()
{

}

void Scene::print() const
{
  std::cout << "frames:" <<frames_ << std::endl;
  for (auto& i: planets_)
    {
      i->print();
    }
}

void Scene::update()
{
  frames_++;
    for (auto& i: planets_)
    {
     long double  F = 0;
     long double Ax = 0;
     long double Ay = 0;
     long double Az = 0;
      for(auto& j: planets_)
        {
          if (i == j)
            continue;

          long double  Dx = (j->get_X - i->get_X);
          long double  Dy = (j->get_Y - i->get_Y);
          long double  Dz = (j->get_Z - i->get_Z);
          
          A = G * j->get_masse()/((Dx * Dx)+(Dy * Dy)+(Dz * Dz));
         
          long double dp = abs(Dx)+abs(Dy)+abs(Dz);
          Ax =A * (Dx) / dp;
                    
          Ay = A * (Dy) / dp;
                
          Az = A * (Dz) / dp;
            
        }
      i->add_Vx(Ax);
      i->add_Vy(Ay);
      i->add_Vz(Az);
    }
  
}
