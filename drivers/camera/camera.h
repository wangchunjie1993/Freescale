/********摄像头相关函数*********/


#ifndef _CAMERA_H_
#define _CAMERA_H_

typedef struct point	//点坐标
{
	s16 x,y;
}point;
u8 is_black(u8 * p);
u8 white_black(u8 *first,u8 *second);
u8 black_white(u8 *first,u8 *second);
u8 turn_black(u8 *dot);
u8 turn_white(u8 *dot);
point aleft_half_restore(point p,u8 hang,u8 xielv);
point aright_half_restore(point p,u8 hang,u8 xielv);
void pl_move(point * p,u8 xielv);
void pr_move(point * p,u8 xielv);
u8 is_point_outside(point *p);
void aleft_scan_1st(point p,u8 i);
void aright_scan_2nd(point p,u8 i);
void get_mid();
void scan_mid();
void white_line_mid();
u8 scan_any_mid(u8 *line_need_scan1,s16 *mid_need1);
#endif