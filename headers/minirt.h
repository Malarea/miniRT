/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:08:35 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 06:05:02 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <float.h>
# include "libft.h"
# include "mlx.h"

# define WIDTH				8
# define HEIGHT				8
# define EPSILON			0.00001

# define ERR_EXT			"File extension invalid.\n"
# define ERR_DUP_EL			" can only be declared once in the scene.\n"
# define ERR_MISS_INF		": missing information.\n"
# define ERR_FLOAT_INF		": information should be numeric.\n"
# define ERR_RANGE_INF		": information is not in the valid range.\n"
# define ERR_FORMAT_COLOR	": invalid color format.\n"
# define ERR_FORMAT_COORD	": invalid coordinates format.\n"
# define ERR_FORMAT_ORIENT	": invalid orientation format.\n"
# define ERR_TOO_MANY_INF	": too many informations.\n"
# define ERR_INV_EL			" is not a valid element.\n"

# define A					"Ambient lighting"
# define C					"Camera"
# define L					"Light"
# define S					"Sphere"
# define P					"Plane"
# define CY					"Cylinder"
# define CO					"Cone"

typedef float			t_tuple __attribute__((ext_vector_type(4)));

typedef t_tuple			t_point;
typedef t_tuple			t_vector;

typedef struct s_object	t_object;

typedef enum e_bool
{
	TRUE = 0,
	FALSE,
	ERR
}	t_bool;

typedef enum e_direction
{
	ROW = 0,
	COL
}	t_dir;

typedef enum e_axes
{
	X = 0,
	Y
}	t_axes;

typedef enum e_tupletype
{
	ERROR = -1,
	VECTOR,
	POINT
}	t_tupletype;

typedef enum e_finish
{
	MATTE = 0,
	GLOSSY
}	t_finish;

typedef union u_color
{
	unsigned int		c;
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
	};
}	t_color;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
}	t_quadratic;

typedef struct s_matrix
{
	float	**val;
	int		size;
}	t_matrix;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_ambient
{
	float	lighting;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_point			position;
	t_vector		direction;
	unsigned int	fov;
	t_matrix		*transform;
}	t_camera;

typedef struct s_light
{
	t_point			position;
	float			brightness;
	t_color			color;
	struct s_light	*next;
	struct s_light	*prev;
}	t_light;

typedef struct s_sphere
{
	float	diameter;
}	t_sphere;

typedef struct s_plane
{
	t_vector	orientation;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	orientation;
	float		diameter;
	float		height;
	float		min;
	float		max;
	t_bool		closed;
}	t_cylinder;

typedef struct s_cone
{
	t_vector	orientation;
	float		diameter;
	float		height;
	float		min;
	float		max;
	t_bool		closed;
}	t_cone;

typedef enum e_objtype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE
}	t_objtype;

typedef union u_objattr
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
}	t_objattr;

typedef void			(*t_uvmap)(t_point p, float *u, float *v);

typedef struct s_material
{
	float		diffuse;
	float		specular;
	int			shininess;
	t_color		color;
	t_color		color2;
	bool		checkerboard;
	t_uvmap		uv_map_checker;
	char		*filename_bm;
	t_data		*bumpmap;
}	t_material;

typedef struct s_intersection
{
	float					t;
	t_object				*obj;
	struct s_intersection	*next;
	struct s_intersection	*prev;
}	t_intersection;

typedef int				(*t_fct_intersect)(t_object *obj, t_ray *r,
							t_intersection **x);

typedef t_vector		(*t_normal_at)(t_object *obj, t_point p);

typedef struct s_object
{
	t_objtype		type;
	t_objattr		attr;
	t_point			position;
	t_matrix		*transform;
	t_material		*material;
	t_fct_intersect	intersect;
	t_normal_at		normal_at;
	struct s_object	*next;
	struct s_object	*prev;
}	t_object;

typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_object	*obj;
	float		pixel_size;
	float		half_w;
	float		half_h;
}	t_scene;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			image;
	t_scene			*scene;
}	t_vars;

typedef struct s_comps
{
	float		t;
	t_object	*obj;
	t_point		point;
	t_vector	eyev;
	t_vector	normalv;
	t_bool		inside;
	t_point		overpoint;
}	t_comps;

/************ PARSER ***********/
t_scene			*parser(char *file);
void			split_file(int fd, t_scene **scene);
int				detect_item(t_scene **scene, char **split);
void			compute_pixel_size(unsigned int deg, t_scene *scene);

/********* CHECK_FORMAT ********/
int				check_float_range(char *ratio, float min, float max,
					char *elem);
int				check_color_format(char *arg, t_color *c, char *elem);
int				check_coordinates(char *arg, t_point *p, char *elem);
int				check_orientation(char *arg, t_vector *v, char *elem);

/******** PARSING_TOOLS ********/
t_bool			str_is_int(char *num);
t_bool			str_is_float(char *num);
t_bool			check_file_extension(char *file, char *ext);

/************ ERROR ************/
int				error_parsing(char *err, char *arg);
int				check_args(int dup, char *elem, int expected, char **args);
int				check_args_bonus(int dup, char *elem, int expected[2],
					char **args);

/************ OBJECT ***********/
void			add_back_object(t_object **first, t_object *n);
t_material		*create_material(t_finish f);
int				parse_color(t_object *obj, char **args, char *elem);
void			free_material(t_material *m, t_vars *vars);

/*********** AMBIENT ***********/
int				create_ambient(char **args, t_scene **scene);

/************ CAMERA ***********/
int				create_camera(char **args, t_scene **scene);
int				matrix_transform_camera(t_camera *c,
					t_point from, t_vector dir);

/************ LIGHT ************/
int				create_light(char **args, t_scene **scene);
void			add_back_light(t_light **first, t_light *new);

/************ SPHERE ***********/
int				create_sphere(char **args, t_scene **scene);
int				matrix_transform_sphere(t_object *s, char **args);

/************ PLANE ************/
int				create_plane(char **args, t_scene **scene);
int				matrix_transform_plane(t_object *p, char **args);

/********** CYLINDER ***********/
int				create_cylinder(char **args, t_scene **scene);
int				matrix_transform_cylinder(t_object *cy, char **args);

/************* CONE ************/
int				create_cone(char **args, t_scene **scene);
int				matrix_transform_cone(t_object *co, char **args);

/********* MATH_TOOLS **********/
t_bool			comparison_float(float a, float b);
float			radians(float deg);
t_matrix		*identity_matrix(void);
void			swap(float *a, float *b);
t_matrix		*orientation_matrix(t_vector left, t_vector up,
					t_vector forward);

/************ VECTOR ***********/
float			magnitude(t_tuple tuple);
float			dot(t_tuple a, t_tuple b);
t_vector		normalize(t_tuple tuple);
t_vector		cross(t_vector a, t_vector b);
t_bool			tuple_equality(t_tuple a, t_tuple b);

/************ COLOR ************/
t_color			blend_colors(t_color c1, t_color c2);
t_color			color_ratio(t_color c, float ratio);
t_color			color_sum(t_color a, t_color b);
int				clamp_color(int n);
void			set_color(t_color *c, int r, int g, int b);

/********** MLX_TOOLS **********/
void			clear_mlx(t_vars *vars);
t_data			init_image(void *mlx);
void			mlx_pixel_put_img(t_data *image, int x, int y, int color);
unsigned int	get_pixel_color(t_data *data, int x, int y);
void			*init_win(void *mlx);

/************ EVENTS ***********/
int				close_win(t_vars *vars);
int				keypress_events(int key, t_vars *vars);

/************ MATRIX ***********/
t_matrix		*create_matrix(int size);
float			**create_matrix_val(int size, t_matrix **matrix);
void			free_matrix(t_matrix **m);
t_matrix		*submatrix(t_matrix *m, int rdel, int cdel);
void			incr_row_col(int *m, int *s, int del);

/******** MATRIX_INVERSE *******/
t_matrix		*inverse(t_matrix *m);
int				determinant(t_matrix *m, float *det);
int				minor(t_matrix *m, int rdel, int cdel, float *minor);
int				cofactor(t_matrix *m, int rdel, int cdel, float *cofactor);
int				fill_inverse_matrix(t_matrix *m, t_matrix **inv);

/****** MATRIX_OPERATIONS ******/
t_bool			matrix_equality(t_matrix *a, t_matrix *b);
t_matrix		*matrix_mult(t_matrix *a, t_matrix *b);
void			fill_product_matrix(t_matrix *a, t_matrix *b,
					t_matrix *m, int i[2]);
t_tuple			matrix_tuple_mult(t_matrix *a, t_tuple b);
t_matrix		*transpose(t_matrix *m);

/****** MATRIX_SCALE_ROT *******/
t_matrix		*scaling(float x, float y, float z);
t_matrix		*rodrigues_rotation(t_vector a, t_vector b);
float			get_angle_vector(t_vector a, t_vector b);
t_matrix		*get_rot_matrix(t_vector v, float theta);

/***** MATRIX_SHEAR_TRANSL ******/
t_matrix		*translation(float x, float y, float z);
t_matrix		*shearing_x(float xy, float xz);
t_matrix		*shearing_y(float yx, float yz);
t_matrix		*shearing_z(float zx, float zy);

/************ RAYS *************/
t_ray			*create_ray(t_point p, t_vector v);
t_point			position(t_ray *r, float t);
t_ray			*transform(t_ray *r1, t_matrix *m);
t_ray			*ray_for_pixel(t_scene *scene, int x, int y);

/********* INTERSECTION ********/
t_intersection	*create_intersection(float t, t_object *obj);
t_intersection	*get_hit(t_intersection *x);
void			free_intersection(t_intersection *x);
void			intersection_add_sort(t_intersection **first,
					t_intersection *n);
int				intersect_scene(t_object *obj, t_ray *ray,
					t_intersection **first);

/***** INTERSECTION_SPHERE *****/
float			discriminant(t_ray *r, float *a, float *b);
int				intersect_sphere(t_object *s, t_ray *r, t_intersection **first);

/****** INTERSECTION_PLANE *****/
int				intersect_plane(t_object *s, t_ray *r, t_intersection **first);

/**** INTERSECTION_CYLINDER ****/
int				intersect_cylinder(t_object *c, t_ray *r,
					t_intersection **first);
int				check_min_max_cylinder(t_intersection **first,
					float t[2], t_ray *r, t_object *c);
float			discr_cylinder(float *a, float *b, t_ray *r);
int				intersect_caps(t_object *c, t_ray *r, t_intersection **first);
t_bool			check_cap(t_ray *r, float t);

/****** INTERSECTION_CONE ******/
int				intersect_cone(t_object *c, t_ray *r,
					t_intersection **first);
float			discr_cone(t_quadratic *q, t_ray *r);
int				check_min_max_cone(t_intersection **first,
					float t[2], t_ray *r, t_object *c);

/************ RENDER ***********/
int				render(t_vars *vars);
t_comps			*prepare_computation(t_intersection *i, t_ray *r);
int				color_at(t_scene *scene, t_ray *r, t_color *color);

/************ NORMAL ***********/
t_vector		normal_at_sphere(t_object *s, t_point objp);
t_vector		normal_at_plane(t_object *p, t_point objp);
t_vector		normal_at_cylinder(t_object *c, t_point objp);
t_vector		normal_at_cone(t_object *c, t_point objp);
t_vector		normal_at(t_object *obj, t_point p);

/********** REFLECTION *********/
t_color			lighting(t_scene *scene, t_object *obj, t_comps *comps,
					t_bool shadow);
t_color			compute_specular(t_light *light, t_object *obj, t_comps *comps);
t_color			compute_diffuse(t_object *obj, t_comps *comps, t_light *light,
					t_color color);
t_color			compute_ambient(t_scene *scene, t_color color);
int				shade_hit(t_scene *scene, t_object *obj, t_comps *comps,
					t_color *color);
/************ SHADOW ***********/
int				is_shadowed(t_scene *scene, t_point p);
int				compare_hit_distance(float distance, t_intersection *x);

/******* TRANSFORM_MATRIX ******/
t_matrix		*compute_transform_sphere(float diam, t_point pos);
t_matrix		*compute_transform_plane(t_vector orientation, t_point pos);
t_matrix		*view_transform(t_point from, t_vector forward);
t_matrix		*compute_transform_cylinder(t_vector v, t_point p, float diam);
void			*free_all_matrix(t_matrix *m1, t_matrix *m2, t_matrix *m3,
					t_matrix *m4);

/********* CHECKERBOARD ********/
t_color			uv_checkers(t_object *obj, t_point p);
void			spherical_checker_map(t_point p, float *u, float *v);
void			planar_checker_map(t_point p, float *u, float *v);
void			cylindrical_checker_map(t_point p, float *u, float *v);

/*********** BUMPMAP ***********/
int				load_normal_map(t_vars *vars, t_object *obj);
t_vector		get_perturbation(t_data *image, int x, int y);
int				apply_perturbation_normal(t_comps *comps, t_object *obj);
t_vector		perturb_normal(t_vector n, t_vector texcoord, t_data *tex);

/************* MAIN ************/
void			free_scene(t_scene *scene, t_vars *vars);

#endif
