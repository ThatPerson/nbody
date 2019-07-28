#define dim 3

typedef struct {
	float v[dim];
} v_3;


v_3 add_3(v_3 a, v_3 b){
	v_3 out;
	int i;
	for (i = 0; i < dim; i++)
		out.v[i] = a.v[i] + b.v[i];
	return out;
}

v_3 mul_3(v_3 a, v_3 b){
	v_3 out;
	int i;
	for (i = 0; i < dim; i++)
		out.v[i] = a.v[i] * b.v[i];
	return out;
}

v_3 div_3(v_3 a, v_3 b) {
	v_3 out;
	int i;
	for (i = 0; i < dim; i++)
		out.v[i] = a.v[i] / b.v[i];
	return out;
}

v_3 sub_3(v_3 a, v_3 b) {
	v_3 out;
	int i;
	for (i = 0; i < dim; i++)
		out.v[i] = a.v[i] - b.v[i];
	return out;
}

v_3 s_mul_3(float scalar, v_3 a) {
	int i;
	for (i = 0; i < dim; i++) {
		a.v[i] = a.v[i] * scalar;
	}
	return a;
}

float mag_3(v_3 a) {
	float sum = 0;
	int i;
	for (i = 0; i < dim; i++)
		sum = sum + pow(a.v[i], 2);

	return sqrt(sum);
}


void print_3(v_3 a) {
	int i;
	for (i = 0; i < dim-1; i++)
		printf("%f, ", a.v[i]);
		
	printf("%f\n", a.v[dim-1]);
	return;
}

void f_print_3(FILE** f, v_3 a) {
	int i;
	for (i = 0; i < dim-1; i++)
		fprintf(*f, "%f, ", a.v[i]);
		
	fprintf(*f, "%f\n", a.v[dim-1]);
	return;
}    

v_3 norm_3(v_3 a, float m) {
	float norm_fac = mag_3(a);
	norm_fac = (norm_fac==0)?1:norm_fac;
	int i;
	for (i = 0; i < dim; i ++)
		a.v[i] = m * a.v[i] / norm_fac;

	return a;
}

v_3 gen_3(float a, float b, float c) {
	v_3 n;
	n.v[0] = a;
	n.v[1] = b;
	n.v[2] = c;
	return n;
}
