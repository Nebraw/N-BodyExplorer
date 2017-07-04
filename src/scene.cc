#include <scene.hh>
#include <iostream>
#include <memory>

Scene::Scene()
{
  frames_ = 0;
}

Scene::~Scene()
{

}

void Scene::add_planet(std::shared_ptr<Planet> p)
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
     long double Ax = 0;
     long double Ay = 0;
     long double Az = 0;
      for(auto& j: planets_)
        {
          if (i == j)
            continue;

          long double  Dx = (j->get_Px() - i->get_Px());
          long double  Dy = (j->get_Py() - i->get_Py());
          long double  Dz = (j->get_Pz() - i->get_Pz());
          
          long double A = G * j->get_masse()/((Dx * Dx)+(Dy * Dy)+(Dz * Dz));
         
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
