/*----------------------------------------------------------
* COSC363  Ray Tracer
*
*  The sphere class
*  This is a subclass of Object, and hence implements the
*  methods intersect() and normal().
-------------------------------------------------------------*/

#include "Cylinder.h"
#include <math.h>

/**
* Sphere's intersection method.  The input is a ray.
*/
float Cylinder::intersect(glm::vec3 p0, glm::vec3 dir)
{
    float lower, higher;
    float xDiff = p0.x - center.x;
    float zDiff = p0.z - center.z;

    float a = (dir.x * dir.x) + (dir.z * dir.z);
    float b = 2 * ((dir.x * xDiff) + (dir.z * zDiff));
    float c = (xDiff * xDiff) + (zDiff * zDiff) - (radius * radius);
    float delta = (b * b) - (4 * a * c);

    if (fabs(delta) < 0.001) return -1.0;
    if (delta < 0.0) return -1.0;

    float t1 = (-b + sqrt(delta)) / (2 * a);
    float t2 = (-b - sqrt(delta)) / (2 * a);

    if (t1 > t2) { lower = t2; higher = t1; }
    else { lower = t1; higher = t2; }

    float r1 = p0.y +  lower * dir.y;
    float r2 = p0.y + higher * dir.y;

    if ((r1 > (center.y + height)) && (r2 > (center.y + height))) return -1.0;
    if ((r1 > (center.y + height)) && (r2 < (center.y + height))) return higher;
    return lower;
}

/**
 * Returns the surface normal vector at a given point in a normalised form. This requires
 * an assumption that the point lies on the Cylinder
 * @param point: A point that lies on the Cylinder
 * @return the normalised surface normal vector
 */
glm::vec3 Cylinder::normal(glm::vec3 point) {
    float maxHeight = center.y + height;
    glm::vec3 centrePoint = point - center;
    glm::vec3 n = glm::vec3 (centrePoint.x, 0.0, centrePoint.z);
    if (point.y >= maxHeight) n = glm::vec3 (0.0, 1.0, 0.0);
    n = glm::normalize(n);
    return n;

}
