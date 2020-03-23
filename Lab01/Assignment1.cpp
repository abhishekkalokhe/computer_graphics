#include <iostream> 
using namespace std; 
  
class Vector { 
private: 
    int x, y, z; 
  
public: 
    
    Vector(int ax, int ay, int az) 
    { 
        x = ax; 
        y = ay; 
        z = az;

       // cout<< "Constructor Executed";                            //Uncomment to print "Constructer Executed" after every constructor execution.
    } 
  
  	~Vector()
  	{
  		//cout<<"Deconstructor Executed";                           //Uncomment to print "Deconstructer Executed" after every deconstructor execution.
  	}

    int getX() 
    { 
        return x; 
    } 
    int getY() 
    { 
        return y; 
    } 
    int getZ() 
    { 
        return z; 
    }
}; 
  
Vector add (Vector i, Vector j)                                     //Function for Addition
{
	int t = i.getX() + j.getX();
	int u = i.getY() + j.getY();
	int v = i.getZ() + j.getZ();
	Vector k (t,u,v);

	return k;
}

Vector subtract (Vector i, Vector j)                               //Function for Subtraction
{
	int t = i.getX() - j.getX();
	int u = i.getY() -j.getY();
	int v = i.getZ() - j.getZ();
	Vector k (t,u,v);

	return k;
}

Vector dot (Vector i, Vector j)                                   //Function for Dot Product
{
	int t = i.getX() * j.getX();
	int u = i.getY() *j.getY();
	int v = i.getZ() * j.getZ();
	Vector k (t,u,v);

	return k;
}

Vector cross (Vector i, Vector j)                                //Function for Cross Product
{
	int t = (i.getY() * j.getZ()) - (i.getZ() * j.getY());
	int u = (i.getZ() * j.getX()) - (i.getX() * j.getZ());
	int v = (i.getX() * j.getY()) - (i.getY() * j.getX());
	Vector k (t,u,v);

	return k;
}



int main()                                                      //Main Body
{ 	
	int ax,ay,az,bx,by,bz,p;                                    //Variables defined


	cin>>ax>>ay>>az>>bx>>by>>bz>>p;                             //Inputs from the user in order ax,ay,az,bx,by,bz and then the operation to be executed
	


    Vector a(ax, ay, az);                                       //Class instance creation
    Vector b(bx, by, bz);



 switch(p)                                                      //Switch to assign different tasks
 {
   case 1: {Vector l = add(a,b);
   cout<< l.getX()<<"i + "<<l.getY()<<"j + "<<l.getZ()<<"k";    //1 for addition
   break;}

   case 2: {Vector m = subtract(a,b);
   cout<< m.getX()<<"i + "<<m.getY()<<"j + "<<m.getZ()<<"k";    //2 for subtraction
   break;}

   case 3: {Vector n = dot(a,b);
   cout<< n.getX()<<"i + "<<n.getY()<<"j + "<<n.getZ()<<"k";    //3 for dot product
   break;}

   case 4: {Vector o = cross(a,b);
   cout<< o.getX()<<"i + "<<o.getY()<<"j + "<<o.getZ()<<"k";    //4 for cross product
   break;}
 };
  
     return 0; 
} 