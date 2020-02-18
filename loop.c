#include "head.h"

int		wallat(t_sdl *s, float x, float y)
{
	return (s->m[(int)x][(int)y] == '1');
}

void	set_hp(t_sdl *sdl, int h)
{
	sdl->hp += h;
	if (sdl->hp > 200)
		sdl->hp = 200;
	if (sdl->hp < 0)
	{
		sdl->game_over = 1;
		sdl->height = 0.05;
		sdl->spd = 0.0;
	}
	sdl->txt[5].str[0] = sdl->hp / 100 + '0';
	sdl->txt[5].str[1] = sdl->hp / 10 - sdl->hp / 100 * 10 + '0';
	sdl->txt[5].str[2] = sdl->hp % 10 + '0';
}

void	set_arrows(t_sdl *sdl, int a)
{
	sdl->arrows += a;
	sdl->txt[7].str[0] = sdl->arrows / 1000 + '0';
	sdl->txt[7].str[1] = sdl->arrows / 100 + '0';
	sdl->txt[7].str[2] = sdl->arrows / 10 + '0';
	sdl->txt[7].str[3] = sdl->arrows % 10 + '0';
}

char	detect(t_vect a, float s1, t_vect b, float s2)
{
	float	s11;
	float	s22;

	s11 = s1 / 2;
	s22 = s2 / 2;
	return (((a.v[0] + s11) > (b.v[0] - s22)) &&
		((a.v[0] - s11) < (b.v[0] + s22)) &&
		((a.v[1] + s11) > (b.v[1] - s22)) &&
		((a.v[1] - s11) < (b.v[1] + s22)));
}

void	collx(t_sdl *s, float sx)
{
	int		i;
	float	sign;

	i = -1;
	if (sx > 0)
		sign = 1.0;
	else
		sign = -1.0;
	s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
	s->p.v[1] = s->r.p.v[1];
	while (i < 2)
	{
		if (wallat(s, s->r.p.v[0] + sign, s->r.p.v[1] + i))
		{
			s->wa[i + 1].v[0] = (int)s->r.p.v[0] + sign + 0.5;
			s->wa[i + 1].v[1] = (int)s->r.p.v[1] + i + 0.5;
		}
		else
		{
			s->wa[i + 1].v[0] = -1.0;
			s->wa[i + 1].v[1] = -1.0;
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (detect(s->p, s->bord, s->wa[i], 1.0))
		{
			s->spdx = 0.0;
			s->p.v[0] = s->r.p.v[0];
			return ;
		}
		i++;
	}
	s->p.v[0] = s->r.p.v[0];
}

void		colly(t_sdl *s, float sy)
{
	int		i;
	float	sign;

	i = -1;
	if (sy > 0)
		sign = 1.0;
	else
		sign = -1.0;
	s->p.v[0] = s->r.p.v[0]+ s->spdx * s->spd;
	s->p.v[1] = s->r.p.v[1]+ s->spdy * s->spd;
	while (i < 2)
	{
		if (wallat(s, s->r.p.v[0] + i, s->r.p.v[1] + sign))
		{
			s->wa[i + 1].v[0] = (int)s->r.p.v[0] + i + 0.5;
			s->wa[i + 1].v[1] = (int)s->r.p.v[1] + sign + 0.5;
		}
		else
		{
			s->wa[i + 1].v[0] = -1.0;
			s->wa[i + 1].v[1] = -1.0;
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (detect(s->p, s->bord, s->wa[i], 1.0))
		{
			s->spdy = 0.0;
			s->p.v[1] = s->r.p.v[1];
			return ;
		}
		i++;
	}
}

void	coll(t_sdl *s, t_vect obj, float obj_bord)
{
	s->p = s->r.p;
	s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
	s->p.v[1] = s->r.p.v[1] + s->spdy * s->spd;
	if (detect(s->p, s->bord, obj, obj_bord))
	{
		s->p = s->r.p;
		s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
		if (detect(s->p, s->bord, obj, obj_bord))
		{
			if (s->spdx > 0)
				s->p.v[0] = obj.v[0] - (obj_bord + s->bord) / 2 - 0.01;
			else
				s->p.v[0] = obj.v[0] + (obj_bord + s->bord) / 2 + 0.01;
			s->spdx = 0;
		}
		s->p.v[1] = s->r.p.v[1] + s->spdy * s->spd;
		if (detect(s->p, s->bord, obj, obj_bord))
		{
			if (s->spdy > 0)
				s->p.v[1] = obj.v[1] - (obj_bord + s->bord) / 2 - 0.01;
			else
				s->p.v[1] = obj.v[1] + (obj_bord + s->bord) / 2 + 0.01;
			s->spdy = 0;
		}
	}
}

void	wall_coll(t_sdl *s)
{
	float	sx;
	float	sy;
	int		i;

	i = 0;
	sx = s->spd * s->spdx;
	sy = s->spd * s->spdy;
	collx(s, sx);
	colly(s, sy);
	while (i < s->obj_count)
	{
		if (s->obj[i].iter)
			coll(s, s->obj[i].p, s->obj[i].bord);
		i++;
	}
	s->r.p = s->p;
	s->spdx = 0.0;
	s->spdy = 0.0;
}

void    move(t_sdl *sdl)
{
	wall_coll(sdl);
}

void	set_speed(float sx, float sy, t_sdl *s)
{
	s->spdx += sx;
	s->spdy += sy;
}

void	jump_f(t_sdl *sdl)
{
	if (sdl->jump == 1)
	{
		if (sdl->height > 0.49)
		{
			sdl->height += sdl->spdz;
			sdl->spdz -= sdl->gforce;
		}
		else
		{
			sdl->jump = 0;
			sdl->height = 0.5;
			sdl->spdz = 0.0;
		}
	}
}

void	click(t_sdl *sdl)
{
	int		i;
	t_vect	cl;

	i = sdl->obj_count - 1;
	cl.v[0] = sdl->r.p.v[0] + cos(sdl->x_ang) * 0.3;
	cl.v[1] = sdl->r.p.v[1] + sin(sdl->x_ang) * 0.3;
	while (i >= 0)
	{
		if (detect(cl, 0.5, sdl->obj[i].p, sdl->obj[i].bord))
		{
			(*sdl->obj[i].act_f)((void*)sdl, i);
			break;
		}
		i--;
	}
}

void    key_logic(t_sdl *sdl)
{
    if (sdl->up)
        sdl->height += 0.05;
    if (sdl->down)
        sdl->height -= 0.05;
    if (sdl->right)
        sdl->spdx = sdl->spd;
    if (sdl->left)
        sdl->spdx = -sdl->spd;
    if (sdl->q)
        sdl->x_ang -= 0.02;
    if (sdl->e)
        sdl->x_ang += 0.02;
	if (sdl->sp && sdl->jump == 0)
	{
		sdl->sp = 0;
		sdl->height = 0.5;
		sdl->jump = 1;
		sdl->spdz = 0.08;
	}
    if (sdl->w)
    {
        sdl->spdx += cos(sdl->x_ang) * sdl->spd;
        sdl->spdy += sin(sdl->x_ang) * sdl->spd;
    }
    if (sdl->s)
    {
        sdl->spdx += -cos(sdl->x_ang) * sdl->spd;
        sdl->spdy += -sin(sdl->x_ang) * sdl->spd;
    }
    if (sdl->a)
    {
        sdl->spdx += cos(sdl->x_ang - HPI) * sdl->spd;
        sdl->spdy += sin(sdl->x_ang - HPI) * sdl->spd;
    }
    if (sdl->d)
    {
        sdl->spdx += cos(sdl->x_ang + HPI) * sdl->spd;
        sdl->spdy += sin(sdl->x_ang + HPI) * sdl->spd;
    }
	if (sdl->rb)
	{
		if (sdl->sky_i == 5)
			sdl->sky_i = 6;
		else
			sdl->sky_i = 5;
		sdl->rb = 0;
	}
	if (sdl->f)
	{
		click(sdl);
		sdl->f = 0;
	}
	if (sdl->mleft)
	{
		shoot(sdl);
		sdl->mleft = 0;
	}
}

int		partition(t_sdl *s, int low, int high)
{
	t_obj	pivor;
	t_obj	temp;
	int		i;
	int		j;

	pivor = s->obj[high];
	i = (low - 1);
	j = low;
	while (j <= (high - 1))
	{
		if (s->obj[j].len <  pivor.len)
		{
			i++;
			temp = s->obj[j];
			s->obj[j] = s->obj[i];
			s->obj[i] = temp;
		}
		j++;
	}
	temp = s->obj[i + 1];
	s->obj[i + 1] = s->obj[high];
	s->obj[high] = temp;
	return (i + 1);
}

void	qwsort(t_sdl *s, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(s, low, high);

		qwsort(s, low, pi - 1);
		qwsort(s, pi + 1, high);
	}
}

void	remove_obj(t_sdl *sdl)
{
	int	i;

	i = sdl->obj_count - 1;
	while (i >= 0)
	{
		if (sdl->obj[i].p.v[0] > 100.0)
			sdl->obj_count--;
		i--;
	}
}

void	obj_len(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->obj_count)
	{
		sdl->obj[i].len = leng(sdl->r.p, sdl->obj[i].p);
		i++;
	}
	qwsort(sdl, 0, sdl->obj_count - 1);
	remove_obj(sdl);
}

void	show_lock(t_sdl *sdl)
{
	if (sdl->lock > 0)
	{
		sdl->lock++;
		if (sdl->lock > 150)
			sdl->lock = 0;
	}
}

void	show_unlock(t_sdl *sdl)
{
	if (sdl->unlock > 0)
	{
		sdl->unlock++;
		if (sdl->unlock > 150)
			sdl->unlock = 0;
	}
}

void	anim(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->obj_count)
	{
		if (sdl->obj[i].anim)
			(*sdl->obj[i].anim_f)((void*)sdl, i);
		i++;
	}
}

void	change_score(t_sdl *sdl)
{
	sdl->txt[1].str[0] = sdl->score / 10 + '0';
	sdl->txt[1].str[1] = sdl->score % 10 + '0';
}

void    logic(t_sdl *sdl)
{
    move(sdl);
	jump_f(sdl);
	obj_len(sdl);
	anim(sdl);
	show_lock(sdl);
	show_unlock(sdl);
	reload(sdl);
    if (-sdl->x_ang > PI)
        sdl->x_ang += PI2;
    if (sdl->x_ang > PI)
        sdl->x_ang -= PI2;
	if (sdl->y_ang < -0.65)
		sdl->y_ang = -0.65;
	if (sdl->y_ang > 0.75)
		sdl->y_ang = 0.75;
	if (sdl->height > 0.95)
		sdl->height = 0.95;
	if (sdl->height < 0.05)
		sdl->height = 0.05;
    sdl->y_ang_i = (int)(sdl->y_ang / sdl->ang);
    sdl->x_ang_i = (int)(sdl->x_ang / sdl->ang + sdl->tngm) % sdl->tngm;
}

void    keydown(t_sdl *sdl)
{
    if (sdl->event.key.keysym.sym == SDLK_UP)
        sdl->up = 1;
    if (sdl->event.key.keysym.sym == SDLK_DOWN)
        sdl->down = 1;
    if (sdl->event.key.keysym.sym == SDLK_RIGHT)
        sdl->right = 1;
    if (sdl->event.key.keysym.sym == SDLK_LEFT)
        sdl->left = 1;
    if (sdl->event.key.keysym.sym == SDLK_q)
        sdl->q = 1;
    if (sdl->event.key.keysym.sym == SDLK_w)
        sdl->w = 1;
    if (sdl->event.key.keysym.sym == SDLK_e)
        sdl->e = 1;
    if (sdl->event.key.keysym.sym == SDLK_a)
        sdl->a = 1;
    if (sdl->event.key.keysym.sym == SDLK_s)
        sdl->s = 1;
    if (sdl->event.key.keysym.sym == SDLK_d)
        sdl->d = 1;
	if (sdl->event.key.keysym.sym == SDLK_r)
		sdl->rb = 1;
	if (sdl->event.key.keysym.sym == SDLK_f)
		sdl->f = 1;
    if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
        sdl->run = 0;
	if (sdl->event.key.keysym.sym == SDLK_SPACE)
		sdl->sp = 1;
	if (sdl->event.key.keysym.sym == SDLK_m)
		sdl->mk = 1;
}

void    keyup(t_sdl *sdl)
{
    if (sdl->event.key.keysym.sym == SDLK_UP)
        sdl->up = 0;
    if (sdl->event.key.keysym.sym == SDLK_DOWN)
        sdl->down = 0;
    if (sdl->event.key.keysym.sym == SDLK_RIGHT)
        sdl->right = 0;
    if (sdl->event.key.keysym.sym == SDLK_LEFT)
        sdl->left = 0;
    if (sdl->event.key.keysym.sym == SDLK_q)
        sdl->q = 0;
    if (sdl->event.key.keysym.sym == SDLK_w)
        sdl->w = 0;
    if (sdl->event.key.keysym.sym == SDLK_e)
        sdl->e = 0;
    if (sdl->event.key.keysym.sym == SDLK_a)
        sdl->a = 0;
    if (sdl->event.key.keysym.sym == SDLK_s)
        sdl->s = 0;
    if (sdl->event.key.keysym.sym == SDLK_d)
        sdl->d = 0;
	if (sdl->event.key.keysym.sym == SDLK_SPACE)
		sdl->sp = 0;
	if (sdl->event.key.keysym.sym == SDLK_r)
		sdl->rb = 0;
	if (sdl->event.key.keysym.sym == SDLK_f)
		sdl->f = 0;
	if (sdl->event.key.keysym.sym == SDLK_m)
	{
		sdl->mk = 0;
		if (!sdl->mouse_look)
			SDL_ShowCursor(SDL_DISABLE);
		else
			SDL_ShowCursor(SDL_ENABLE);
		sdl->mouse_look = !sdl->mouse_look;
	}
}

void	mousemove(t_sdl *sdl)
{
	if (sdl->mouse_look)
	{
		sdl->x_ang += (sdl->event.motion.x - HWL) * sdl->msence;
		sdl->y_ang -= (sdl->event.motion.y - HWH) * sdl->msence;
		SDL_WarpMouseInWindow(NULL, HWL, HWH);
	}
}

void	mousedown(t_sdl *sdl)
{
	if (sdl->mouse_look)
	{
		if (sdl->event.button.button == SDL_BUTTON_LEFT)
			sdl->mleft = 1;
	}
}

void    loop(t_sdl *sdl)
{
    while (sdl->run)
    {

        while(SDL_PollEvent(&sdl->event) != 0)
        {
            if (sdl->event.type == SDL_QUIT)
                sdl->run = 0;
            if (sdl->event.type == SDL_KEYDOWN)
                keydown(sdl);
            if (sdl->event.type == SDL_KEYUP)
                keyup(sdl);
			if (sdl->event.type == SDL_MOUSEMOTION)
				mousemove(sdl);
			if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
				mousedown(sdl);
        }
        memset(sdl->img, 0, WIN_L * WIN_H * sizeof(int));
        key_logic(sdl);
        logic(sdl);
        draw(sdl);
        SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_L * sizeof(int));
        SDL_RenderClear(sdl->ren);
        SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
        SDL_RenderPresent(sdl->ren);
    }
}
