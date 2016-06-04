#include "vector.h"
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846f

struct mat44_t mat44_multiply(const struct mat44_t* m1, const struct mat44_t* m2) 
{
	struct mat44_t out = IDENTITY_MATRIX;
	unsigned int row, column, row_offset;

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
	{
		for (column = 0; column < 4; ++column)
		{
			out.m[row_offset + column] =
				(m1->m[row_offset + 0] * m2->m[column + 0]) +
				(m1->m[row_offset + 1] * m2->m[column + 4]) +
				(m1->m[row_offset + 2] * m2->m[column + 8]) +
				(m1->m[row_offset + 3] * m2->m[column + 12]);
		}
	}

	return out;
}

struct vec4_t vec4_mulmat(const struct mat44_t* m, const struct vec4_t* v)
{
	struct vec4_t out;

	for (int i = 0; i < 4; ++i)
	{
		out.m[i] =
			(v->m[0] * m->m[i + 0]) +
			(v->m[1] * m->m[i + 4]) +
			(v->m[2] * m->m[i + 8]) +
			(v->m[3] * m->m[i + 12]);
	}

	return out;
}

void vec4_normalize(struct vec4_t* v)
{
	float sqr = v->m[0] * v->m[0] + v->m[1] * v->m[1] + v->m[2] * v->m[2];

	if (sqr == 1 || sqr == 0)
		return;

	float invrt = 1.0f / sqrtf(sqr);

	v->m[0] *= invrt;
	v->m[1] *= invrt;
	v->m[2] *= invrt;
}

float vec4_dot(struct vec4_t* v1, struct vec4_t* v2)
{
	return v1->m[0] * v2->m[0] + v1->m[1] * v2->m[1] + v1->m[2] * v2->m[2] + v1->m[3] * v2->m[3];
}

struct vec4_t vec4_cross(struct vec4_t* v1, struct vec4_t* v2)
{
	struct vec4_t out = { { 0 } };
	out.m[0] = v1->m[1] * v2->m[2] - v1->m[2] * v2->m[1];
	out.m[1] = v1->m[2] * v2->m[0] - v1->m[0] * v2->m[2];
	out.m[2] = v1->m[0] * v2->m[1] - v1->m[1] * v2->m[0];
	return out;
}
void mat44_rotateX(const struct mat44_t* m, float angle) {
	struct mat44_t rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[5] = cosine;
	rotation.m[6] = -sine;
	rotation.m[9] = sine;
	rotation.m[10] = cosine;

	memcpy(m->m, mat44_multiply(m, &rotation).m, sizeof(m->m));
}
void mat44_rotateY(const struct mat44_t* m, float angle) {
	struct mat44_t rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[8] = sine;
	rotation.m[2] = -sine;
	rotation.m[10] = cosine;

	memcpy(m->m, mat44_multiply(m, &rotation).m, sizeof(m->m));
}
void mat44_rotateZ(const struct mat44_t* m, float angle) {
	struct mat44_t rotation = IDENTITY_MATRIX;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[1] = -sine;
	rotation.m[4] = sine;
	rotation.m[5] = cosine;

	memcpy(m->m, mat44_multiply(m, &rotation).m, sizeof(m->m));
}
void mat44_scale(const struct mat44_t* m, float x, float y, float z) {
	struct mat44_t scale = IDENTITY_MATRIX;

	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;

	memcpy(m->m, mat44_multiply(m, &scale).m, sizeof(m->m));
}
void mat44_translate(const struct mat44_t* m, float x, float y, float z) {
	struct mat44_t translation = IDENTITY_MATRIX;

	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;

	memcpy(m->m, mat44_multiply(m, &translation).m, sizeof(m->m));
}

struct mat44_t mat44_perspective(float fovy, float aspect_ratio, float near_plane, float far_plane) {
	struct mat44_t out = { { 0 } };

	const float
		y_scale = (float)(1 / cosf(fovy * PI / 360.0f)),
		x_scale = y_scale / aspect_ratio,
		frustum_length = far_plane - near_plane;

	out.m[0] = x_scale;
	out.m[5] = y_scale;
	out.m[10] = -((far_plane + near_plane) / frustum_length);
	out.m[11] = -1;
	out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

	return out;
}

struct mat44_t mat44_orthogonal(float left, float right, float bottom, float top) {
	struct mat44_t out = IDENTITY_MATRIX;
	out.m[0] = 2 / (right - left);
	out.m[5] = 2 / (top - bottom);
	out.m[10] = -1;
	out.m[12] = -(right + left) / (right - left);
	out.m[13] = -(top + bottom) / (top - bottom);

	return out;
}

struct mat44_t mat44_lookAt(struct vec4_t pos, struct vec4_t dir) {
	struct vec4_t f = dir;
	vec4_normalize(&f);
	struct vec4_t u = { { 0, 1, 0, 0 } };
	struct vec4_t s = vec4_cross(&f, &u);
	vec4_normalize(&s);
	u = vec4_cross(&s, &f);

	struct mat44_t out = IDENTITY_MATRIX;
	out.m[0] = s.m[0];
	out.m[4] = s.m[1];
	out.m[8] = s.m[2];

	out.m[1] = u.m[0];
	out.m[5] = u.m[1];
	out.m[9] = u.m[2];

	out.m[2] = -f.m[0];
	out.m[6] = -f.m[1];
	out.m[10] = -f.m[2];

	out.m[12] = -vec4_dot(&s, &pos);
	out.m[13] = -vec4_dot(&u, &pos);
	out.m[14] = vec4_dot(&f, &pos);
	return out;
}

struct mat44_t mat44_transpose(struct mat44_t* m)
{
	struct mat44_t out;

	out.m[0] = m->m[0];
	out.m[1] = m->m[4];
	out.m[2] = m->m[8];
	out.m[3] = m->m[12];

	out.m[4] = m->m[1];
	out.m[5] = m->m[5];
	out.m[6] = m->m[9];
	out.m[7] = m->m[13];

	out.m[8] = m->m[2];
	out.m[9] = m->m[6];
	out.m[10] = m->m[10];
	out.m[11] = m->m[14];

	out.m[12] = m->m[3];
	out.m[13] = m->m[7];
	out.m[14] = m->m[11];
	out.m[15] = m->m[15];

	return out;
}