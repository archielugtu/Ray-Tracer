#include "Cone.h"
#include <math.h>

/**
* Cone's intersection method.  The input is a ray (pos, dir).
*/
float Cone::intersect(glm::vec3 p0, glm::vec3 dir)
{
   float lower, higher;
   float xDiff = p0.x - center.x;
   float zDiff = p0.z - center.z;
   float yDiff = height - p0.y + center.y;
   float radHeight = (radius / height);

   float a = (dir.x * dir.x) + (dir.z * dir.z) - (radHeight * radHeight) * (dir.y * dir.y);
   float b = 2 * ((xDiff * dir.x + zDiff * dir.z) + (radHeight *radHeight) * (yDiff * dir.y));
   float c = (xDiff * xDiff) + (zDiff * zDiff) - (radHeight * radHeight) * (yDiff * yDiff);
   float delta = (b * b) - (4 * a * c);

   if (fabs(delta) < 0.001) return -1.0;
   if (delta < 0.0) return -1.0;

   float t1 = (-b + sqrt(delta)) / (2 * a);
   float t2 = (-b - sqrt(delta)) / (2 * a);

   if (t1 > t2){ lower = t2; higher = t1; }
   else { lower = t1; higher = t2; }

   float r1 = p0.y +  lower * dir.y;
   float r2 = p0.y + higher * dir.y;

   if ((r1 > (center.y + height)) && (r2 > (center.y + height))) return -1.0;
   if ((r1 > (center.y + height)) && (r2 < (center.y + height))) return higher;
   return lower;
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the cone.
*/
glm::vec3 Cone::normal(glm::vec3 p)
{
    glm::vec3 centrePoint = p - center;
    float alpha = atan(centrePoint.x / centrePoint.z);
    float theta = atan(radius / height);
    glm::vec3 n = glm::vec3 (sin(alpha) * cos(theta), sin(theta), cos(alpha) * cos(theta));
    return n;
}
