#include "math/transformation3d.h"
#include "math/transformation-matrices.h"

using namespace math;


Transformation3D math::transformations::translation(const Vector3D& v)
{
	Matrix4x4 tm = transformation_matrices::translation(v);
	Matrix4x4 itm = transformation_matrices::translation(-v);

	return Transformation3D(tm, itm);
}

Transformation3D math::transformations::scale(double sx, double sy, double sz)
{
	// http://3dcg.leone.ucll.be/reference/design/primitives/basics/explanations.html
	// check transformation
	Matrix4x4 tm = transformation_matrices::scaling(sx,sy,sz);
	Matrix4x4 itm = transformation_matrices::scaling(1/sx,1/sy,1/sz);

	return Transformation3D(tm,itm);
}
