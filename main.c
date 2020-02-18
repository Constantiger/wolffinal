#include "head.h"

#include "stdio.h"

int     texturebmp(t_sdl *sdl, float x, float y, int ind)
{
    int tx;
    int ty;

    tx = x * sdl->mx[ind];
    ty = y * sdl->my[ind];
    return (*(sdl->bmp[ind] + ty * sdl->mx[ind] + tx));
}

void    set_tang(t_sdl *s)
{
    int i;

    i = 0;
    s->tngm = PI2 / s->ang;
    s->pi = s->tngm / 2;
    s->hpi = s->pi / 2;
    s->pihpi = s->tngm * 3 / 4;
	s->qpi = s->tngm / 8;
	s->qpi3 = s->qpi * 3;
	s->qpi5 = s->qpi * 5;
	s->qpi7 = s->qpi * 7;
    s->tang = (float*)malloc((s->tngm) * sizeof(float));
    if (s->tang == NULL)
    {
        write(1, "tang array error.\n", 18);
        quit(s);
        exit(1);
    }
    while (i < s->tngm)
    {
        s->tang[i] = tan(i * s->ang);
        i++;
    }
}

void    print_map(t_sdl *s)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < s->msy)
    {
        while (i < s->msx)
        {
            write(1, &s->m[i][j], 1);
            i++;
        }
        write(1, "\n", 1);
        j++;
        i = 0;
    }
}

void    draw_map(t_sdl *s)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < s->msy)
    {
        while (i < s->msx)
        {
            if (s->m[i][j] == '1')
            put_box(s, i * s->bs + 25, j * s->bs + 25, s->bs, 255);
            i++;
        }
        j++;
        i = 0;
    }
	i = 0;
	while (i < s->obj_count)
	{
		j = s->bs * s->obj[i].bord;
		put_box(s, s->obj[i].p.v[0] * s->bs + 25 - j / 2,
				s->obj[i].p.v[1] * s->bs + 25 - j / 2,
				j , c(255, 0, 255));
		i++;
	}
}

void    draw_ray(t_sdl *s, t_ray r)
{
    float x;
    float y;
    float sz;
    int   color;

    color = c(0, 255, 0);
    sz = s->bs * s->bord;
    x = r.p.v[0] * s->bs;
    y = r.p.v[1] * s->bs;
    put_box(s, x + 25 - sz / 2 , y + 25 - sz / 2, sz, color);
    put_line(s, set_v(x + 25, y + 25, 0.0),
		set_v(x + cos(s->x_ang) * 200 + 25,
		y + sin(s->x_ang) * 200 + 25, 0.0), color);
    put_line(s, set_v(x + 25, y + 25, 0.0),
		set_v(x + cos(s->x_ang - s->hsize * s->ang) * 200 + 25,
		y + sin(s->x_ang - s->hsize * s->ang) * 200 + 25, 0.0), color);
    put_line(s, set_v(x + 25, y + 25, 0.0),
		set_v(x + cos(s->x_ang + s->hsize * s->ang) * 200 + 25,
		y + sin(s->x_ang + s->hsize * s->ang) * 200 + 25, 0.0), color);
}

char      check(t_vect *r)
{
    char    flag;

    flag = 0;
    if (r->v[0] > 100)
    {
        flag = 1;
        r->v[0] = 100;
    }
    if (r->v[0] < 0)
    {
        flag = 1;
        r->v[0] = 0;
    }
    if (r->v[1] > 100)
    {
        flag = 1;
        r->v[1] = 100;
    }
    if (r->v[1] < 0)
    {
        flag = 1;
        r->v[1] = 0;
    }
    return (flag);
}

int		text(float x, float y)
{
	if (x > 0.5 && y > 0.5)
		return (c(255, 255, 255));
	else if (x < 0.5 && y < 0.5)
		return (c(255, 0, 0));
	else
		return (255);
}

void	draw_flor(int x, int y, t_vect p, t_sdl *sdl)
{
	float	tx;
	float	ty;
	float	t;
	float	d;
    int     ya;

	while (y < WIN_H)
	{
        ya = sdl->y_ang_i + HWH - y;
        ya = (ya + sdl->tngm) % sdl->tngm;
        t = sdl->tang[ya];
		d = sdl->height / t / p.v[2];
		tx = d * (sdl->r.p.v[0] - p.v[0]) + sdl->r.p.v[0];
		tx = tx - (int)tx;
		ty = d * (sdl->r.p.v[1] - p.v[1]) + sdl->r.p.v[1];
		ty = ty - (int)ty;
		put_pixel(sdl, x + sdl->off, y,
            texturebmp(sdl, tx, ty, 1));
		y++;
	}
}

void	draw_ceil(int x, int y, t_vect p, t_sdl *sdl)
{
	float	tx;
	float	ty;
	float	t;
	float	d;
    int     ya;

	while (y > 0)
	{
        ya = -sdl->y_ang_i - HWH + y;
        ya = (ya + sdl->tngm) % sdl->tngm;
        t = sdl->tang[ya];
		d = (1.0 - sdl->height) / t / p.v[2];
		tx = d * (sdl->r.p.v[0] - p.v[0]) + sdl->r.p.v[0];
		ty = d * (sdl->r.p.v[1] - p.v[1]) + sdl->r.p.v[1];
		if (isceil(sdl, (int)tx, (int)ty))
        {
            tx = tx - (int)tx;
            ty = ty - (int)ty;
            put_pixel(sdl, x + sdl->off, y,
                texturebmp(sdl, tx, ty, 4));
        }
		y--;
	}
}

int		texture_ind(t_sdl *sdl, int i)
{
	int	tx;

	tx = 2;
	if (sdl->l[i].c == 0)
	{
		if (sdl->r.p.v[1] > sdl->l[i].v[1])
			tx = 2;
		else
			tx = 16;
	}
	else
	{
		if (sdl->r.p.v[0] > sdl->l[i].v[0])
			tx = 17;
		else
			tx = 18;
	}
	return tx;
}

void    draw_wall(t_sdl *sdl)
{
    int     i;
    float   j;
    float   k;
    float   h;

    i = 0;
    j = 0;
    while (i < sdl->size)
    {
        k = atan(sdl->height / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
        j = -atan((1.0 - sdl->height) / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
		h = k - j;
		draw_ceil(i, j + HWH, sdl->l[i], sdl);
		while (j < k)
        {
            put_pixel(sdl, i + sdl->off, j + HWH,
					texturebmp(sdl, sdl->l[i].v[sdl->l[i].c] -
					(int)(sdl->l[i].v[sdl->l[i].c]),
					((k - j) / h ), texture_ind(sdl, i)));
            j++;

		}
        draw_flor(i, j + HWH, sdl->l[i], sdl);
		i++;
    }
}

void    draw_fow(t_sdl *sdl)
{
    int i;

    i = 0;
    while (i < sdl->size)
    {
        sdl->ar[i].p = sdl->r.p;
        sdl->ar[i].a_i = (sdl->x_ang_i - sdl->hsize + i + sdl->tngm) % sdl->tngm;
        sdl->l[i] = cast_ray(sdl, sdl->ar[i]);
        i++;
    }
    draw_wall(sdl);
}

float   leng(t_vect a, t_vect b)
{
    float   dy;
    float   dx;

    dy = a.v[1] - b.v[1];
    dx = a.v[0] - b.v[0];
    return (sqrt(dx * dx + dy * dy));
}

int   xon_screen(t_sdl *sdl, t_vect v)
{
    float   a;
    int     l;
    float   dy;
    float   dx;

    dy = v.v[1] - sdl->r.p.v[1];
    dx = v.v[0] - sdl->r.p.v[0];
    a = atan(dy / dx) - sdl->x_ang;
    if (dx < 0)
		a = a - 3.141592;
	if(a > 3.141592)
		a -= 6.28318;
	if (a < -3.141592)
		a += 6.28318;
    l = a / sdl->ang + sdl->hsize;
    return (l);
}

void    draw_doors(t_sdl *sdl, int f, int l, int i)
{

    float   j;
    float   k;
    float   h;
	int		color;

    j = 0;
    k = atan(sdl->height / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
    j = -atan((1.0 - sdl->height) / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
    h = k - j;
    while (j < k)
    {
        color = texturebmp(sdl, 1.0 - (float)(i - l)/(f - l), (1.0 - (k - j) / h ), 3);
        put_pixel(sdl, i + sdl->off, j + HWH, color);
        j++;
    }
}

void    swapi(int *a, int *b)
{
    int c;

    c = *a;
    *a = *b;
    *b = c;
}

void    draw_bmp(t_sdl *sdl, int sx, int sy, int ind)
{
    int i;
    int j;
	int	color;

    i = 0;
    j = 0;
    while (j < sdl->my[ind])
    {
        while (i < sdl->mx[ind])
        {
			color = *(sdl->bmp[ind] + j * sdl->mx[ind] + i);
			if ((color & 255) != 255)
            	put_pixel(sdl, sx + i, sy + j, color);
            i++;
        }
        j++;
        i = 0;
    }
}

void	draw_skybox(t_sdl *sdl)
{
	int	i;
	t_vect	p;

	p = set_v(0.5, 0.5, 0.5);
	i = 0;
	while (i < sdl->size)
		{
			sdl->ar[i].p = p;
			sdl->ar[i].a_i = (sdl->x_ang_i - sdl->hsize
					+ i + sdl->tngm) % sdl->tngm;
			sdl->l[i] = cast_cube(sdl, sdl->ar[i].a_i);
			i++;
		}
	draw_sky(sdl);
}

void	draw_gui(t_sdl *sdl)
{
	int	i;

	i = 0;
	if (!sdl->game_over)
	{
		while (i < sdl->txt_count - 1)
		{
			if ((i != 2 || (i == 2 && sdl->lock > 0)) &&
			(i != 3 || (i == 3 && sdl->unlock > 0)))
				put_text(sdl, i);
			i++;
		}
	}
	else
	{
		put_text(sdl, sdl->txt_count - 1);
	}
}

void    draw(t_sdl *sdl)
{
    int i;

    draw_map(sdl);
    draw_ray(sdl, sdl->r);
	draw_skybox(sdl);
	draw_fow(sdl);
	i = 0;
	while (i < sdl->doory_count)
        draw_doory(sdl, i++);
    i = 0;
    while (i < sdl->doorx_count)
    draw_doorx(sdl, i++);
	i = sdl->obj_count - 1;
	while (i >= 0)
	{
		if (sdl->obj[i].dr)
			(*sdl->obj[i].draw_f)(sdl, i);
		i--;
	}
	if (!sdl->game_over) draw_weapon(sdl, sdl->size);
	draw_gui(sdl);
	if (sdl->key)
		draw_bmp(sdl, WIN_L - 10 - sdl->mx[9], -70, 9);
	put_box(sdl, sdl->off + sdl->hsize-3, HWH-3, 6, 0);
}

int main(int argc, char **argv)
{
    t_sdl   sdl;
    if(init(&sdl))
    {
		write(1, "init error\n", 11);
        quit(&sdl);
    }
	set(&sdl);
	if (!load_map(&sdl))
		quit(&sdl);
	if (!load_obj(&sdl))
		quit(&sdl);
	set_tang(&sdl);
	load_audio(&sdl);
	load_textures(&sdl);
    print_map(&sdl);
	SDL_ShowCursor(SDL_DISABLE);
	if( Mix_PlayingMusic() == 0 )
	{
		Mix_PlayMusic( sdl.gmusic, -1 );
		Mix_VolumeMusic(MIX_MAX_VOLUME / 12);
	}
	loop(&sdl);
    return (0);
}
