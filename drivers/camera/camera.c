/********摄像头相关函数*********/

#include "common.h"
#include "include.h"

extern u8 ImageBuf[ROW][COL];
u8 cross_flag=0;

u8 xielv=100;	 	//xielv在0~200之间变化
point lr_dot[HANG][2];		//需要扫描的行的左右点
point mid_dot[HANG]={{60,COL/2},{120,COL/2},{180,COL/2}};		//赛道中线的点(x,y)
u8 total_line_num=0;	//一共扫到的赛道线数

u8 miss_left_count=0,miss_right_count=0;                //丢失左右线次数

//u16 left[HANG];
//u16 right[HANG];
//u16 mid[HANG]={COL/2,COL/2,COL/2};
s16 mid[ROW/4];

u8 is_white(u8 * p)
{
  if(!((*p++)<THRESHOLD&&(*p++)<THRESHOLD&&(*p)<THRESHOLD))
  return 1;
  else 
  return 0;
}
u8 is_black(u8 * p)
{
  if((*p++)<THRESHOLD&&(*p++)<THRESHOLD&&(*p)<THRESHOLD)
  return 1;
  else 
  return 0;
}

u8 black_to_white(u8 *p)
{
  u8 count=15;
  if(is_black(p))
  {
    while(count--)
    {
      if(is_white(p++))
        return 1;
    }
  }
  return 0;
}

u8 white_to_black(u8 *p)
{
  u8 count=15;
  if(is_white(p))
  {
    while(count--)
    {
      if(is_black(p++))
        return 1;
    }
  }
  return 0;
}

u8 white_black(u8 *first,u8 *second)
{
  if((*first-*second)>THRESHOLD)
    return 1;
  else
    return 0;
}

u8 black_white(u8 *first,u8 *second)
{
  if((*second-*first)>THRESHOLD)
    return 1;
  else
    return 0;
}

u8 turn_black(u8 *dot)			//白白黑黑
{
  if(white_black(dot,dot+2)&&white_black(dot,dot+3)&&white_black(dot+1,dot+2)&&white_black(dot+1,dot+3))
    return 1;
  else 
    return 0;
}

u8 turn_white(u8 *dot)			//黑黑白白
{
  if(black_white(dot,dot+2)&&black_white(dot,dot+3)&&black_white(dot+1,dot+2)&&black_white(dot+1,dot+3))
    return 1;
  else 
    return 0;
}


/********向左补偿半赛道宽度************/
point aleft_half_restore(point p,u8 xielv,u8 hang)	
{
	if(xielv)
	{
		
	}
	
	//return val;
}

/********向右补偿半赛道宽度************/
point aright_half_restore(point p,u8 xielv,u8 hang)	
{

	//return val;
}

void pl_move(point * p,u8 xielv)		//点向左方向(包括垂直向上)移动
{
        p->y-=1;
	/*if(xielv)
	{
		p->x-=1;
		p->y+=2;
	}
	else if(xielv)
	{
		p->x-=1;
		p->y+=1;
	}
	else if(xielv)
	{
		p->x-=2;
		p->y+=1;
	}
	else if(xielv)
	{
		p->x-=1;
	}
	else if(xielv)
	{
		p->x-=2;
		p->y-=1;
	}
	else if(xielv)
	{
		p->x-=1;
		p->y-=1;
	}
	else if(xielv)
	{
		p->x-=1;
		p->y-=2;
	}
	else 
	{
		p->y-=1;
	}*/
}

void pr_move(point * p,u8 xielv)		//点向右方向(包括垂直向下)移动
{
        p->y+=1;
	/*if(xielv)
	{
		p->x+=1;
		p->y-=2;
	}
	else if(xielv)
	{
		p->x+=1;
		p->y-=1;
	}
	else if(xielv)
	{
		p->x+=2;
		p->y-=1;
	}
	else if(xielv)
	{
		p->x+=1;
	}
	else if(xielv)
	{
		p->x+=2;
		p->y+=1;
	}
	else if(xielv)
	{
		p->x+=1;
		p->y+=1;
	}
	else if(xielv)
	{
		p->x+=1;
		p->y+=2;
	}
	else 
	{
		p->y+=1;
	}*/
}

u8 is_point_outside(point *p)				//判断点是否在图像外
{
	if((p->x<0)||(p->x>COL)||(p->y<0)||(p->y>ROW))			
	{
		if(p->x<0)
		{
			p->x=0;
		}
		else if(p->x>COL)
		{
			p->x=COL;
		}         
		if(p->y<0)
		{
			p->y=0;
		}
		else if(p->y>ROW)
		{
			p->y=ROW;
		}
		return 1;
	}
	return 0;
}

void aleft_scan_1st(point p,u8 i)			//先向左方向扫描赛道
{
	u8 is_black=0;			//当前是否为黑点
	total_line_num=0;
	while((p.x>=0)&&(p.x<=COL)&&(p.y>=0)&&(p.y<=ROW))		//中点（移动的点）在图像内
	{			
		if(!is_black&&turn_white(&ImageBuf[p.x][p.y]))		//从白点变成黑点
		{
			is_black=1;			//当前为黑点
			if(total_line_num==0)
			{
				lr_dot[i][0]=p;		//记录下可能的左点		
			}
			else if(total_line_num==1)
			{
				lr_dot[i][1]=p;		//先记录下可能的左点
			}
			else
			{
				total_line_num=2;
				break;
			}	
		}		
		if(is_black&&turn_black(&ImageBuf[p.x][p.y]))		//从黑点变成白点
		{
			is_black=0;
			if(total_line_num==0)
			{
				total_line_num++;		//获得一条赛道
			}
			else if(total_line_num==1)			//获得两条赛道
			{
				mid_dot[i].x=(lr_dot[i][0].x+p.x)/2;		//计算中点
				mid_dot[i].y=(lr_dot[i][0].y+p.y)/2;
				total_line_num++;
				break;
			}
		}		
		pl_move(&p,xielv);			//点向左方移动一次
	}
	
}


void aright_scan_2nd(point p,u8 i)			//后向右方向扫描赛道
{
	u8 is_black=0;			//当前是否为黑点
	while((p.x>=0)&&(p.x<=COL)&&(p.y>=0)&&(p.y<=ROW))		//中点（移动的点）在图像内
	{			
		if(!is_black&&turn_black(&ImageBuf[p.x][p.y]))			//从白点变成黑点
		{
			is_black=1;			//当前为黑点
			if(total_line_num==0)
			{
				lr_dot[i][0]=p;		//记录下可能的左点		
			}
			else if(total_line_num==1)
			{
				lr_dot[i][1]=p;		//记录下可能的右点
			}
			else 
			{
				total_line_num=2;
				break;
			}		
		}
	
		if(is_black&&turn_white(&ImageBuf[p.x][p.y]))			//从黑点变成白点
		{
			is_black=0;
			if(total_line_num==0)			//获取一条赛道
			{
				total_line_num++;
			}
			else if(total_line_num==1)			//获取两条赛道
			{
				mid_dot[i].x=(lr_dot[i][0].x+p.x)/2;		//计算中点
				mid_dot[i].y=(lr_dot[i][0].y+p.y)/2;
				total_line_num++;
				break;
			}
		}		
		pr_move(&p,xielv);			//点向右方移动一次
	}
}

void get_mid()
{
  u16 i;
  u8 aleft_line_num=0;		//向左扫描时扫到的赛道线数

  for(i=0;i<HANG;i++)		//需要采集的行
  {
	if(is_point_outside(&mid_dot[i]))	break;		//中点在图像外
	
	/***********从中间往左扫*************/		
	aleft_scan_1st(mid_dot[i],i);	
	
	if((aleft_line_num=total_line_num)>=2)	 break;	   //记录下向左方向扫描时扫到的赛道线数
					//向左方向扫描时已经扫到两条赛道
					
	/***********从中间往右扫*************/
	else
	{
		aright_scan_2nd(mid_dot[i],i);		
	}		
				
	/************向左方向和右方向都扫完***************/
	if(total_line_num>=2)				//一共扫到两条赛道
	break;
	else if((total_line_num==1)&&(aleft_line_num==1))			//一共只扫到一条赛道，且为向左扫时扫到,则为左线	
	{
		//if(lr_dot[i][0].)
	}
	else if((total_line_num==1)&&(aleft_line_num==0))			//一共只扫到一条赛道，且为向右扫时扫到，则为右线	
	{
		//if(lr_dot[i][0].)
	}

  }
  
}



u8 is_line(u8 *p)
{
  u8 count=15;
  if(turn_black(p++))
  {
    while(count--)
    {
      if(turn_white(p++))
        return 1;
    }
  }
  return 0;
}


//半赛道补偿
u16 half_restore(u8 hang)
{
  if(hang<=100)
    return (22+hang*0.6);
  else 
    return (41+hang*0.4);
}

//获取中线
/*void scan_mid()    //120行             
{
	s16 i,j,k=ROW/2-1,temp;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //采集到左右线
	for(i=ROW-1;i>=0;i-=2,k--)
	{     
		for(j=mid[k];j>=0;j--)          //扫描左线
		{
			if(is_line(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[k];j<COL-4;j++)               //扫描右线
		{
			if(get_left&&is_line(&ImageBuf[i][j]))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)                 //扫描到左右双线
		{
                  miss_left_count=0;
                  miss_right_count=0;
                  temp=(left+right)/2;
                  if(i==(ROW-1))
                  {
                    mid[ROW/2-1]=temp;
                  }
                  else if((temp-mid[k+1]<50)&&(mid[k+1]-temp<50))
                  {
                    mid[k]=temp;
                  }
                  else 
                    mid[k]=mid[k+1];
		}
                else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //左右线都没扫描到
                mid[k]=mid[k+1];
                
                if((miss_left_count>50)&&((temp=(mid[i]-miss_left_count+30))>=0))
                  mid[k]-=temp;
                if((miss_right_count>50)&&((temp=(mid[i]+miss_right_count-30))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
}*/

/*void scan_mid()               //带补偿          
{
	s16 i,j,temp;
        u16 left=0,right=COL;
	u8 get_left=0,get_right=0;      //采集到左右线
	for(i=ROW-1;i>=0;i--)
	{
		for(j=mid[i];j>=0;j--)
		{
			if(turn_white(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[i];j<COL-22;j++)
		{
			if(get_left&&turn_black(&ImageBuf[i][j]))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)
		{
                  temp=(left+right)/2;
                  if(i==(ROW-1))
                  {
                    mid[ROW-1]=temp;
                  }
                  else if((temp-mid[i+1]<150)&&(mid[i+1]-temp<150))
                  {
                    mid[i]=temp;
                  }
                  else 
                    mid[i]=mid[i+1];
		}
                else if(get_left&&(!get_right))
                {
                  if((temp=left+half_restore(i))<=COL)
                  mid[i]=temp;
                }
                else if((!get_left)&&get_right)
                {
                  if((temp=right-half_restore(i))>=0)
                  {
                    mid[i]=temp;
                  }
                }
                else if(i<(ROW-1))
                mid[i]=mid[i+1];
                get_left=get_right=0;
	}
}*/


/*void scan_mid()    //60行             
{
	signed int i,j,k=ROW/4-1,temp,count_diff;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //采集到左右线
	for(i=ROW-1;i>=0;i-=4,k--)
	{     
		for(j=mid[k];j>=0;j--)          //扫描左线
		{
			if(turn_black(&ImageBuf[i][j])||turn_white(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[k];j<COL-4;j++)               //扫描右线
		{
			if(get_left&&(turn_black(&ImageBuf[i][j])||turn_white(&ImageBuf[i][j])))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)                 //扫描到左右双线
		{
                  miss_left_count=0;
                  miss_right_count=0;
                  temp=(left+right)/2;
                  if(i==(ROW-1))
                  {
                    mid[ROW/4-1]=temp;
                  }
                  else if((temp-mid[k+1]<60)&&(mid[k+1]-temp<60))
                  {
                    mid[k]=temp;
                  }
                  else 
                    mid[k]=mid[k+1];
		}
                else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //左右线都没扫描到
                mid[k]=mid[k+1];
                
                if(((count_diff=(miss_left_count-miss_right_count))>25)&&((temp=(mid[k]-count_diff+15))>=0))
                  mid[k]-=temp;
                else if((count_diff<-25)&&((temp=(mid[k]-count_diff-15))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
}*/




void scan_mid()    //60行(59)  ,320/3列           
{
	signed int i,j,k=ROW/4-2,temp,count_diff;
        u16 left=0,right=COL-6; 
        u8 get_left=0,get_right=0;      //采集到左右线标志
        u8 miss_double_count=0;         //丢失双线计数
	for(i=ROW-2;i>=0;i-=4,k--)
	{     
                if(!is_black(&ImageBuf[i][160]))          //当前为白点,在赛道上
		{
                        for(j=COL/2-3;j>=0;j-=3)          //扫描左线
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                            left=j;
                            get_left=1;
                            break;
                          }
                        }
                        
                        for(j=COL/2+3;j<COL-10;j+=3)               //扫描右线
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                             right=j;
                             get_right=1;
			     break;
                          }
                        }
		}
                else                      //当前为黑点,不在赛道上
                {
                        for(j=COL/2-3;j>=0;j-=3)          //向左扫描
                        {
                          if(!is_black(&ImageBuf[i][j]))        //获取右线
                          {
                            right=j;
                            get_right=1;
                            break;
                          }
                        }
                        if(get_right)
                        {
                          for(j-=3;j>=0;j-=3)
                          {
                            if(is_black(&ImageBuf[i][j]))
                            {
                              left=j;
                              get_left=1;
                              break;
                            }
                          }
                        }
                        
                        if((!get_left)&&(!get_right))            //左右线都没扫描到
                        {
                          for(j=COL/2+3;j<COL-10;j+=3)          //向右扫描
                          {
                            if(!is_black(&ImageBuf[i][j]))        //获取左线
                            {
                              left=j;
                              get_left=1;
                              break;
                            }
                          }
                          if(get_left)
                          {
                            for(j+=3;j<COL-10;j+=3)
                            {
                              if(is_black(&ImageBuf[i][j]))
                              {
                                right=j;
                                get_right=1;
                                break;
                              }
                            }
                          }
                        }

                }
                

		if(get_left&&get_right&&((right-left)<(half_restore(i)*2+40))&&((right-left)>(half_restore(i)*2-40)))                 //扫描到左右双线
		{
                  miss_left_count=0;
                  miss_right_count=0;
                  temp=(left+right)/2;
                  /*if(i==(ROW-2))
                  {
                    mid[ROW/4-2]=temp;
                  }
                  else if((temp-mid[k+1]<40)&&(mid[k+1]-temp<40))
                  {*/
                    mid[k]=temp;
                 /* }
                  else 
                    mid[k]=mid[k+1];*/
		}
                else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
                {
                  //miss_left_count++;
                  //if(i<ROW-2)
                  //mid[k]=mid[k+1]-10;
                  mid[k]=right-half_restore(i);
                }
                else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
                {
                  mid[k]=left+half_restore(i);
                }
                /*else if(i<(ROW-2))                              //左右线都没扫描到
                {
                  mid[k]=mid[k+1];
                  miss_double_count++;
                }*/
                
                get_left=0,get_right=0; 
	}
       /* if(miss_double_count>=20)
          cross_flag=1;
        else
          cross_flag=0;*/
}









void white_line_mid()
{
  signed int i,j,k=ROW/4-1,temp,count_diff;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //采集到左右线
	for(i=ROW-1;i>=0;i-=4,k--)
	{     
		for(j=mid[k];j>=0;j--)          //扫描左线
		{
			if(black_to_white(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[k];j<COL-4;j++)               //扫描右线
		{
			if(white_to_black(&ImageBuf[i][j]))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)                 //扫描到左右双线
		{
                  miss_left_count=0;
                  miss_right_count=0;
                  temp=(left+right)/2;
                  if(i==(ROW-1))
                  {
                    mid[ROW/4-1]=temp;
                  }
                  else if((temp-mid[k+1]<60)&&(mid[k+1]-temp<60))
                  {
                    mid[k]=temp;
                  }
                  else 
                    mid[k]=mid[k+1];
		}
                else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //左右线都没扫描到
                mid[k]=mid[k+1];
                
                if(((count_diff=(miss_left_count-miss_right_count))>25)&&((temp=(mid[k]-count_diff+15))>=0))
                  mid[k]-=temp;
                else if((count_diff<-25)&&((temp=(mid[k]-count_diff-15))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
  
}

/*void scan_mid()    //60行  ,320列           
{
	signed int i,j,k=ROW/4-1,temp,count_diff;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //采集到左右线

	for(i=ROW-1;i>=0;i-=4,k--)
	{     
                if(!is_black(&ImageBuf[i][mid[k]]))          //当前为白点,在赛道上
		{
                        for(j=mid[k]-1;j>=0;j--)          //扫描左线
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                            left=j;
                            get_left=1;
                            break;
                          }
                        }
                        
                        for(j=mid[k]+1;j<COL-4;j++)               //扫描右线
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                             right=j;
                             get_right=1;
			     break;
                          }
                        }
		}
                else                      //当前为黑点,不在赛道上
                {
                        for(j=mid[k]-1;j>=0;j--)          //向左扫描
                        {
                          if(!is_black(&ImageBuf[i][j]))        //获取右线
                          {
                            right=j;
                            get_right=1;
                            break;
                          }
                        }
                        if(get_right)
                        {
                          for(j--;j>=0;j--)
                          {
                            if(is_black(&ImageBuf[i][j]))
                            {
                              left=j;
                              get_left=1;
                              break;
                            }
                          }
                        }
                        
                        if((!get_left)&&(!get_right))            //左右线都没扫描到
                        {
                          for(j=mid[k]+1;j<COL-4;j++)          //向右扫描
                          {
                            if(!is_black(&ImageBuf[i][j]))        //获取左线
                            {
                              left=j;
                              get_left=1;
                              break;
                            }
                          }
                          if(get_left)
                          {
                            for(j++;j<COL-4;j++)
                            {
                              if(is_black(&ImageBuf[i][j]))
                              {
                                right=j;
                                get_right=1;
                                break;
                              }
                            }
                          }
                        }

                }
                

		if(get_left&&get_right)                 //扫描到左右双线
		{
                  miss_left_count=0;
                  miss_right_count=0;
                  temp=(left+right)/2;
                  if(i==(ROW-1))
                  {
                    mid[ROW/4-1]=temp;
                  }
                  else if((temp-mid[k+1]<60)&&(mid[k+1]-temp<60))
                  {
                    mid[k]=temp;
                  }
                  else 
                    mid[k]=mid[k+1];
		}
                else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //左右线都没扫描到
                mid[k]=mid[k+1];
                
                if(((count_diff=(miss_left_count-miss_right_count))>25)&&((temp=(mid[k]-count_diff+15))>=0))
                  mid[k]-=temp;
                else if((count_diff<-25)&&((temp=(mid[k]-count_diff-15))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
}*/











/*u8 scan_any_mid(u8 *line_need_scan1,s16 *mid_need1)
{
  s16 i,j;
  u16 left=0,right=COL; 
  u8 get_left=0,get_right=0;      //采集到左右线标志
  u8 line_current;
  s16 mid_need_temp[3];
  u8 get_mid_num=0;       //采集到中点个数
  //u8 miss_double_count=0;         //丢失双线计数
  u8 *p,*q;

  for(i=0;i<3;i++)
  {
    q=p=((*(ImageBuf+(*(line_need_scan1+i))))+160);
    //q=p=&ImageBuf[line_need_scan1[i]][160];
    if(!is_black(p))          //当前为白点,在赛道上
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //扫描左线
      {
        if(is_black(p))
        {
          left=j;
          get_left=1;
          break;
        }
      }
      p=q;                   
      for(j=164,p+=4;j<COL-11;j+=4,p+=4)               //扫描右线
      {
        if(is_black(p))
        {
          right=j;
          get_right=1;
          break;
        }
      }
      if((!get_left)&&(!get_right))
      {
        cross_flag=1;
        return 1;
      }
      else
        cross_flag=0;
    }
    else                      //当前为黑点,不在赛道上
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //向左扫描
      {
        if(!is_black(p))        //获取右线
        {
          right=j;
          get_right=1;
          break;
        }
      }
      if(get_right)
      {
        for(j-=4;j>=0;j-=4,p-=4)
        {
          if(is_black(p))
          {
            left=j;
            get_left=1;
            break;
          }
        }
      }
                        
      if((!get_left)&&(!get_right))            //向左扫描时左右线都没扫描到
      {
        p=q;
        for(j=164,p+=4;j<COL-11;j+=4,p+=4)          //向右扫描
        {
          if(!is_black(p))        //获取左线
          {
            left=j;
            get_left=1;
            break;
          }
        }
        if(get_left)
        {
          for(j+=4,p+=4;j<COL-11;j+=4)
          {
            if(is_black(p))
            {
              right=j;
              get_right=1;
              break;
            }
          }
        }
      }
    }
  
    line_current=*(line_need_scan1+i);
    if(get_left&&get_right&&((right-left)<(half_restore(line_current)*2+40))&&((right-left)>(half_restore(line_current)*2-40)))                 //扫描到左右双线
    {         
        *(mid_need_temp+i)=(left+right)/2;
        get_mid_num++;
    }
    else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
    {
        *(mid_need_temp+i)=right-half_restore(line_current);
        get_mid_num++;
    }
    else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
    {
        *(mid_need_temp+i)=left+half_restore(line_current);
        get_mid_num++;
    }
  }

  if(get_mid_num!=3)
    return 0;
  else
  {
    while(get_mid_num--)
    {
      *(mid_need1+get_mid_num)=mid_need_temp[get_mid_num];
    }
    return 1;
  }
}*/



u8 scan_any_mid(u8 *line_need_scan1,s16 *mid_need1)
{
  s16 i,j;
  u16 left=0,right=COL; 
  u8 get_left=0,get_right=0;      //采集到左右线标志
  u8 line_current;
  s16 mid_need_temp[4];
  u8 get_mid_num=0;       //采集到中点个数

  u8 *p,*q;

  for(i=0;i<4;i++)
  {
    line_current=*(line_need_scan1+i);
    q=p=((*(ImageBuf+(*(line_need_scan1+i))))+160);
    get_left=get_right=0;
    
    if(!is_black(p))          //当前为白点,在赛道上
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //扫描左线
      {
        if(is_black(p))
        {
          left=j;
          get_left=1;
          break;
        }
      }
      p=q;                   
      for(j=164,p+=4;j<COL-11;j+=4,p+=4)               //扫描右线
      {
        if(is_black(p))
        {
          right=j;
          get_right=1;
          break;
        }
      }
      if((!get_left)&&(!get_right))
      {
        cross_flag=1;           //十字路口标志
        return 1;
      }
 //     else
   //     cross_flag=0;
    }
    else                      //当前为黑点,不在赛道上
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //向左扫描
      {
        if(!is_black(p))        //获取右线
        {
          right=j;
          get_right=1;
          break;
        }
      }
      if(get_right)
      {
        for(j-=4;j>=0;j-=4,p-=4)
        {
          if(is_black(p))
          {
            left=j;
            get_left=1;
            break;
          }
        }
      }
                        
      if((!get_left)&&(!get_right))            //向左扫描时左右线都没扫描到
      {
        p=q;
        for(j=164,p+=4;j<COL-11;j+=4,p+=4)          //向右扫描
        {
          if(!is_black(p))        //获取左线
          {
            left=j;
            get_left=1;
            break;
          }
        }
        if(get_left)
        {
          for(j+=4,p+=4;j<COL-11;j+=4)
          {
            if(is_black(p))
            {
              right=j;
              get_right=1;
              break;
            }
          }
        }
      }
    }
  
    
   /* if(get_left&&get_right&&((right-left)<(half_restore(line_current)*2+80))&&((right-left)>(half_restore(line_current)*2-80)))                 //扫描到左右双线
    {         
        *(mid_need_temp+i)=(left+right)/2;
        get_mid_num++;
    }*/
    
    if(get_left&&get_right)
    {
      if(((right-left)<(half_restore(line_current)*2+80))&&((right-left)>(half_restore(line_current)*2-80)))
      {
        *(mid_need_temp+i)=(left+right)/2;
        get_mid_num++;
        cross_flag=0;
      }
      else 
      {
        cross_flag=1;
        return 1;
      }
    }
    else if((!get_left)&&get_right)                 //扫描到右线，没有扫描到左线
    {
        *(mid_need_temp+i)=right-half_restore(line_current);
        get_mid_num++;
        cross_flag=0;
    }
    else if(get_left&&(!get_right))                 //扫描到左线，没有扫描到右线
    {
        *(mid_need_temp+i)=left+half_restore(line_current);
        get_mid_num++;
        cross_flag=0;
    }
  }
  
  for(i=0;i<3;i++)
  {
    if((*(mid_need_temp+i)-*(mid_need_temp+i+1))>80||(*(mid_need_temp+i+1)-*(mid_need_temp+i))>80)
      return 0;
  }

  if(get_mid_num!=4)
    return 0;
  else
  {
    while(get_mid_num--)
    {
      *(mid_need1+get_mid_num)=*(mid_need_temp+get_mid_num);
    }
    return 1;
  }
}    


/*
u8 scan_any_mid(u8 *line_need_scan1,s16 *mid_need1)
{
  s16 i,j;
  u16 left=0,right=COL; 
  u8 get_left=0,get_right=0;      //采集到左右线标志
  u8 line_current;
  s16 mid_need_temp[4];
  u8 get_mid_num=0;       //采集到中点个数
  u8 *p,*q;
  
  cross_flag=0;			//十字路口标志
  
  for(i=0;i<4;i++)
  {
	get_left=get_right=0;
    line_current=*(line_need_scan1+i);
    q=p=((*(ImageBuf+(*(line_need_scan1+i))))+160);
	
    if(!is_black(p))          //当前为白点,在赛道上
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //扫描左线
      {
        if(is_black(p))
        {
          left=j;
          get_left=1;
          break;
        }
      }
	  
	  if(get_left)			//向左扫描时扫描到左线
	  {
		*(mid_need_temp+i)=left+half_restore(line_current);
        get_mid_num++;
		continue;
	  }
	  else			//向左扫描时没有扫描的左线,则向右扫描
	  {
		p=q;                   
		for(j=164,p+=4;j<COL-11;j+=4,p+=4)               //扫描右线
		{
			if(is_black(p))
			{
			right=j;
			get_right=1;
			break;
			}
		}
		
		if(get_right)			//向右扫描时扫描到右线
		{
			*(mid_need_temp+i)=right-half_restore(line_current);
			get_mid_num++;
			continue;
		}
	  }

      cross_flag=1;           //十字路口标志
      return 1;

    }
    else                      //当前为黑点,不在赛道上
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //向左扫描
      {
        if(!is_black(p))        //获取右线
        {
          right=j;
          get_right=1;
          break;
        }
      }
	  
	  if(get_right)
	  {
		*(mid_need_temp+i)=right-half_restore(line_current);
		get_mid_num++;
		continue;
	  }                
      else            //向左扫描时没有扫描到右线
      {
        p=q;
        for(j=164,p+=4;j<COL-11;j+=4,p+=4)          //向右扫描
        {
          if(!is_black(p))        //获取左线
          {
            left=j;
            get_left=1;
            break;
          }
        }
		
		if(get_left)
		{
			*(mid_need_temp+i)=left+half_restore(line_current);
			get_mid_num++;
			continue;
		}
      }
    }	
  }

  if(get_mid_num!=4)
    return 0;
  else
  {
    while(get_mid_num--)
    {
      *(mid_need1+get_mid_num)=mid_need_temp[get_mid_num];
    }
    return 1;
  }
}*/