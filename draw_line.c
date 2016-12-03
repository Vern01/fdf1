#include "fdf.h"

void      set_line_info(line_t *line, cor_t cor)
{
    line->dx = cor.x2 - cor.x1;
    line->dy = cor.y2 - cor.y1;
    line->eps = 0;
}

int     swap_xy(cor_t *cor)
{
    int     temp;

    temp = cor->x1;
    cor->x1 = cor->y1;
    cor->y1 = temp;
    temp = cor->x2;
    cor->x2 = cor->y2;
    cor->y2 = temp;
    return (1);
}

void    swap_points(cor_t *cor)
{
    int     temp;

    temp = cor->x1;
    cor->x1 = cor->x2;
    cor->x2 = temp;
    temp = cor->y1;
    cor->y1 = cor->y2;
    cor->y2 = temp;
}

void	draw_line(cor_t cor, mlx_t mlx)
{
	line_t	line;

	set_line_info(&line, cor);
	line.swap = 0;
	if (cor.x1 - cor.x2 < cor.y1 - cor.y2)
        line.swap = swap_xy(&cor);
    if (cor.x1 > cor.x2)
        swap_points(&cor);
	while (cor.x1 <= cor.x2)
	{
		if (line.swap)
			mlx_pixel_put(mlx.mlx, mlx.win, cor.y1, cor.x1, 0x00FFFFFF);
		else
			mlx_pixel_put(mlx.mlx, mlx.win, cor.x1, cor.y1, 0x00FFFFFF);
		line.eps += line.dy;
		if((line.eps << 1) >= line.dx)
		{	
			cor.y1++;
			line.eps -= line.dx;
		}
		cor.x1++;
	}
}