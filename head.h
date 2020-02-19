/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:50:03 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 16:00:59 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "bmp.h"

# define WIN_L 1280
# define WIN_H 640
# define HWL 720
# define HWH 320
# define PI 3.141592
# define PI2 6.283185
# define HPI 1.570796

typedef struct		s_vect
{
	float			v[3];
	int				c;
}					t_vect;

typedef struct		s_ray
{
	t_vect			p;
	int				a_i;
}					t_ray;

typedef struct		s_obj
{
	t_vect			p;
	t_vect			pl;
	float			size;
	float			bord;
	float			len;
	char			dr;
	char			txtr;
	int				anim;
	int				ind;
	char			iter;
	char			lock;
	char			move;
	char			atack;
	char			see;
	char			proj;
	char			enem;
	int				hp;
	int				fram;
	void			(*draw_f)(void *, int);
	void			(*anim_f)(void *, int);
	void			(*act_f)(void *, int);
}					t_obj;

typedef struct		s_text
{
	int				x;
	int				y;
	char			str[100];
}					t_text;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*text;
	int				*img;
	char			run;
	SDL_Event		event;
	int				bs;
	int				hbs;
	char			m[100][100];
	int				msx;
	int				msy;
	int				off;
	int				size;
	int				hsize;
	float			ang;
	float			pov;
	float			x_ang;
	float			y_ang;
	int				y_ang_i;
	int				x_ang_i;
	t_ray			r;
	t_vect			p;
	t_vect			doory[100];
	int				doory_count;
	t_vect			doorx[100];
	int				doorx_count;
	t_obj			obj[200];
	int				obj_count;
	t_ray			ar[1000];
	t_vect			l[1000];
	float			*tang;
	int				tngm;
	int				pi;
	int				hpi;
	int				pihpi;
	int				qpi;
	int				qpi3;
	int				qpi5;
	int				qpi7;
	float			pls;
	t_vect			wa[3];
	float			bord;
	float			spd;
	float			spdx;
	float			spdy;
	float			height;
	char			jump;
	float			spdz;
	float			gforce;
	float			msence;
	char			up;
	char			down;
	char			left;
	char			right;
	char			w;
	char			s;
	char			a;
	char			d;
	char			q;
	char			e;
	char			f;
	char			rb;
	char			sp;
	char			mk;
	char			mleft;
	int				*bmp[32];
	int				mx[32];
	int				my[32];
	int				text_count;
	int				sky_i;
	t_text			txt[100];
	int				txt_count;
	int				score;
	char			key;
	int				lock;
	int				unlock;
	int				hp;
	int				arrows;
	int				reload;
	int				weap_fr;
	t_obj			*arr_i;
	Mix_Music		*gmusic;
	Mix_Chunk		*gchunk;
	char			mouse_look;
	char			game_over;
}					t_sdl;

void				loop(t_sdl *sdl);
void				reload(t_sdl *sdl);
void				shoot(t_sdl *sdl);
void				set_hp(t_sdl *sdl, int h);
void				set_arrows(t_sdl *sdl, int a);
int					wallat(t_sdl *s, float x, float y);
char				detect(t_vect a, float s1, t_vect b, float s2);
void				put_line(t_sdl *sdl, t_vect p1, t_vect p2, int color);
void				put_box(t_sdl *sdl, int x, int y, int size, int color);
void				put_pixel(t_sdl *sdl, int x, int y, int color);
void				draw(t_sdl *s);
int					load_map(t_sdl *s);
t_vect				set_v(float x, float y, float z);
void				set_vc(t_vect *v, float x, float y, int c);
int					c(int r, int g, int b);
t_vect				cast_ray(t_sdl *sdl, t_ray r);
char				check(t_vect *r);
char				iswall(t_sdl *sdl, int x, int y);
char				isceil(t_sdl *sdl, int x, int y);
char				isdoorx(t_sdl *sdl, int x, int y);
char				isdoory(t_sdl *sdl, int x, int y);
char				isplayer(t_sdl *sdl, int x, int y);
char				isobj(t_sdl *sdl, int x, int y);
char				isscor(t_sdl *sdl, int x, int y);
char				iskey(t_sdl *sdl, int x, int y);
char				islock(t_sdl *sdl, int x, int y);
char				isenem(t_sdl *sdl, int x, int y);
char				isarrow(t_sdl *sdl, int x, int y);
char				ishp(t_sdl *sdl, int x, int y);
void				push_proj(t_sdl *sdl);
void				push_doory(t_sdl *sdl, int x, int y);
void				push_doorx(t_sdl *sdl, int x, int y);
void				push_obj(t_sdl *sdl, int x, int y);
void				push_score(t_sdl *sdl, int x, int y);
void				push_key(t_sdl *sdl, int x, int y);
void				push_enemy(t_sdl *sdl, int x, int y);
void				push_arrows(t_sdl *sdl, int x, int y);
void				push_hp(t_sdl *sdl, int x, int y);
char				load_obj(t_sdl *sdl);
void				swapi(int *a, int *b);
void				draw_doory(t_sdl *sdl, int ind);
void				draw_doorx(t_sdl *sdl, int ind);
void				draw_obj(void *s, int ind);
void				draw_enemy(void *s, int ind);
int					xon_screen(t_sdl *sdl, t_vect v);
void				draw_doors(t_sdl *sdl, int f, int l, int i);
void				draw_sky(t_sdl *sdl);
t_vect				cast_cube(t_sdl *sdl, int a_i);
float				leng(t_vect a, t_vect b);
int					texturebmp(t_sdl *sdl, float x, float y, int ind);
void				act_doorx(void *s, int ind);
void				act_doory(void *s, int ind);
void				act_obj(void *s, int ind);
void				act_score(void *s, int i);
void				act_arrow(void *s, int i);
void				act_key(void *s, int i);
void				act_hp(void *s, int i);
void				act_arrows(void *s, int i);
void				anim_doorx(void *s, int i);
void				anim_doory(void *s, int i);
void				anim_enemy(void *s, int i);
void				death_enemy(void *s, int i);
void				push_text(t_sdl *sdl, int x, int y, const char *str);
void				put_text(t_sdl *sdl, int ind);
void				change_score(t_sdl *sdl);
void				obj_len(t_sdl *sdl);
void				show_lock(t_sdl *sdl);
void				show_unlock(t_sdl *sdl);
void				draw_weapon(t_sdl *sdl, int size);
void				damage_enemy(t_sdl *sdl, int ind);
int					init(t_sdl *s);
void				set(t_sdl *s);
void				load_texture(t_sdl *sdl, const char *fname);
void				load_textures(t_sdl *sdl);
void				load_audio(t_sdl *sdl);
void				quit(t_sdl *sdl);
void				move_proj(t_sdl *sdl, int ind);
void				wall_coll(t_sdl *sdl);
void				move(t_sdl *sdl);
void				jump_f(t_sdl *sdl);
void				collx_cicle(t_sdl *s, float sign);
void				colly_cicle(t_sdl *s, float sign);
void				keyup(t_sdl *sdl);
void				keydown(t_sdl *sdl);
void				key_logic(t_sdl *sdl);
void				mousedown(t_sdl *sdl);
void				mousemove(t_sdl *sdl);
void				click(t_sdl *sdl);
void				draw_bmp(t_sdl *sdl, int sx, int sy, int ind);
void				draw_skybox(t_sdl *sdl);
void				draw_gui(t_sdl *sdl);
void				draw_fow(t_sdl *sdl);
void				draw_ray(t_sdl *s, t_ray r);
void				draw_map(t_sdl *s);
void				draw_ceil(int x, int y, t_vect p, t_sdl *sdl);
void				draw_flor(int x, int y, t_vect p, t_sdl *sdl);
int					texture_ind(t_sdl *sdl, int i);
void				move_enemy(t_sdl *sdl, int ind);
void				see_enemy(t_sdl *sdl, int ind);
void				coll_enemy(t_sdl *sdl, int ind);
void				free_textures(t_sdl *s);

#endif
