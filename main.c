#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "vec_3.c"
#define G 1

typedef struct {
	v_3 pos, vel;
	float m;
} obj;

typedef struct {
	obj objects[50];
	int n_objects;
	int print, step;
	float dt;
} sys;

v_3 force_v(obj a, obj b) {
	/* This function returns the unitary force between two objects, from the 
	 * perspective of object a. */
	/* Calculates F = GMm/r^2, and then returns a vector of magnitude F along
	 * the vector connecting the two objects */
	float r = mag_3(sub_3(a.pos, b.pos));

	if (r < 0.00001) {
		printf("Too close..\n");
		exit(0);
	}
	float F = (G * a.m * b.m) / pow(r, 2);

	v_3 radial = norm_3(sub_3(a.pos, b.pos), F);
	return radial;
}

int gravity_v(float dt, sys *syst, int n) {
	/* We are object n in system syst and we are iterating dt */
	v_3 resultant;
	v_3 force;
	int i;
	for (i = 0; i < dim; i++)
		resultant.v[i] = 0;
	for (i = 0; i < syst->n_objects; i++) {
		if (n == i)
			continue;
		force = force_v(syst->objects[i], syst->objects[n]);
		force = s_mul_3(1, force); // acceleration
		force = s_mul_3(dt, force); // a = dv/dt, dv = a dt
		resultant = add_3(resultant, force);
	}
	
	
	syst->objects[n].vel = add_3(syst->objects[n].vel, resultant);
	return 1;
}

int iterate_pos_v(float dt, sys *syst, int n) {
	/* object pos = object pos + dt*object vel */
	v_3 v_dt = s_mul_3(dt, syst->objects[n].vel);

	syst->objects[n].pos = add_3(syst->objects[n].pos, v_dt);
	return 1;
}

int read_input(char * filename, sys *syst) {
	printf("%s\n", filename);
	FILE * fp;
	fp = fopen(filename, "r");
	int n = 0;
	fscanf(fp, "%d:%d:%f", &syst->step, &syst->print, &syst->dt);
	while (fscanf(fp, "%f,%f,%f,%f,%f,%f,%f", 
		&syst->objects[n].pos.v[0],
		&syst->objects[n].pos.v[1],
		&syst->objects[n].pos.v[2],
		&syst->objects[n].vel.v[0],
		&syst->objects[n].vel.v[1],
		&syst->objects[n].vel.v[2],
		&syst->objects[n].m) != EOF) 
	{
		n++;
	}
	syst->n_objects = n;
	printf("%d\n", n);
	fclose(fp);
}

int main(int argc, char*argv[]) {
	/*v_3 a = {2, 3, 4};
	v_3 b = {4, 3, 8};
	v_3 o = add_3(a, b);
	print_3(a);
	print_3(b);
	print_3(mul_3(a, b));
	print_3(norm_3(a, 3));
	printf("%f\n", mag_3(norm_3(a, 3)));*/
	
	sys syst;
	int t;
	int n;
	FILE * outputs[50];
	char fname[50];
	char base_name[50] = "";
	char input_name[50];

	if (argc == 1) {
		printf("Please enter filename\n");
		exit(0);
	}
	strcpy(input_name, argv[1]);
	if (argc > 2)
		strcpy(base_name, argv[2]);
	if (read_input(input_name, &syst) == -1) {
		printf("Error in reading file\n");
		exit(0);
	}
	
	
	for (t = 0; t < syst.n_objects; t++) {
		sprintf(fname, "%s-%d.csv", base_name, t);
		outputs[t] = fopen(fname, "w");
		if (outputs[t] == NULL) {
			printf("Failed to open file\n");
			exit(0);
		}
	}
	char in[50];
	while (strcmp(in, "exit") != 0) {
		scanf("%s", in);
		for (t = 0; t < syst.step; t++) {
			for (n = 0; n < syst.n_objects; n++) {
				if (t % syst.print == 0) {
					fprintf(outputs[n], "%f, ", t*syst.dt);
					f_print_3(&outputs[n], syst.objects[n].pos);
				}
				gravity_v(syst.dt, &syst, n);
				
			}
			for (n = 0; n < syst.n_objects; n++)
				iterate_pos_v(syst.dt, &syst, n);
			
		}
	}
	for (t = 0; t < syst.n_objects; t++) {
		fclose(outputs[t]);
	}
	return 1;
}
