#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifdef _WIN64
#endif

struct mat44_t
{
	float m[16];
};

/*
0 1 2 3
4 5 6 7
8 9 A B
C D E F
*/

struct vec4_t
{
	float m[4];
};

static const struct vec4_t X_AXIS = { { 1, 0, 0, 0 } };
static const struct vec4_t Y_AXIS = { { 0, 1, 0, 0 } };
static const struct vec4_t Z_AXIS = { { 0, 0, 1, 0 } };
static const struct vec4_t INV_X_AXIS = { { -1, 0, 0, 0 } };
static const struct vec4_t INV_Y_AXIS = { { 0, -1, 0, 0 } };
static const struct vec4_t INV_Z_AXIS = { { 0, 0, -1, 0 } };
static const struct vec4_t VEC4_ZERO = { { 0, 0, 0, 0 } };
static const struct vec4_t VEC4_ONE = { { 1, 1, 1, 1 } };

static const struct mat44_t IDENTITY_MATRIX = 
{ {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
} };


struct vec4_t vec4_mulmat(const struct mat44_t* m, const struct vec4_t* v);
void vec4_normalize(struct vec4_t* v);
float vec4_dot(struct vec4_t* v1, struct vec4_t* v2);
//float vec4_distance(struct vec4_t* v1, struct vec4_t* v2);
struct vec4_t vec4_cross(struct vec4_t* v1, struct vec4_t* v2);

struct mat44_t mat44_multiply(const struct mat44_t* m1, const struct mat44_t* m2);
void mat44_rotateX(const struct mat44_t* m, float angle);
void mat44_rotateY(const struct mat44_t* m, float angle);
void mat44_rotateZ(const struct mat44_t* m, float angle);
void mat44_scale(const struct mat44_t* m, float x, float y, float z);
void mat44_translate(const struct mat44_t* m, float x, float y, float z);
struct mat44_t mat44_perspective(float fovy, float aspect_ratio, float near_plane, float far_plane);
struct mat44_t mat44_orthogonal(float left, float right, float bottom, float top);
struct mat44_t mat44_lookAt(struct vec4_t pos, struct vec4_t dir);
struct mat44_t mat44_transpose(struct mat44_t* m);

#endif // _VECTOR_H_
