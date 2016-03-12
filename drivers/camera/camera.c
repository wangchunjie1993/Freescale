/********����ͷ��غ���*********/

#include "common.h"
#include "include.h"

extern u8 ImageBuf[ROW][COL];
u8 cross_flag=0;

u8 xielv=100;	 	//xielv��0~200֮��仯
point lr_dot[HANG][2];		//��Ҫɨ����е����ҵ�
point mid_dot[HANG]={{60,COL/2},{120,COL/2},{180,COL/2}};		//�������ߵĵ�(x,y)
u8 total_line_num=0;	//һ��ɨ������������

u8 miss_left_count=0,miss_right_count=0;                //��ʧ�����ߴ���

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

u8 turn_black(u8 *dot)			//�װ׺ں�
{
  if(white_black(dot,dot+2)&&white_black(dot,dot+3)&&white_black(dot+1,dot+2)&&white_black(dot+1,dot+3))
    return 1;
  else 
    return 0;
}

u8 turn_white(u8 *dot)			//�ںڰװ�
{
  if(black_white(dot,dot+2)&&black_white(dot,dot+3)&&black_white(dot+1,dot+2)&&black_white(dot+1,dot+3))
    return 1;
  else 
    return 0;
}


/********���󲹳����������************/
point aleft_half_restore(point p,u8 xielv,u8 hang)	
{
	if(xielv)
	{
		
	}
	
	//return val;
}

/********���Ҳ������������************/
point aright_half_restore(point p,u8 xielv,u8 hang)	
{

	//return val;
}

void pl_move(point * p,u8 xielv)		//��������(������ֱ����)�ƶ�
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

void pr_move(point * p,u8 xielv)		//�����ҷ���(������ֱ����)�ƶ�
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

u8 is_point_outside(point *p)				//�жϵ��Ƿ���ͼ����
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

void aleft_scan_1st(point p,u8 i)			//��������ɨ������
{
	u8 is_black=0;			//��ǰ�Ƿ�Ϊ�ڵ�
	total_line_num=0;
	while((p.x>=0)&&(p.x<=COL)&&(p.y>=0)&&(p.y<=ROW))		//�е㣨�ƶ��ĵ㣩��ͼ����
	{			
		if(!is_black&&turn_white(&ImageBuf[p.x][p.y]))		//�Ӱ׵��ɺڵ�
		{
			is_black=1;			//��ǰΪ�ڵ�
			if(total_line_num==0)
			{
				lr_dot[i][0]=p;		//��¼�¿��ܵ����		
			}
			else if(total_line_num==1)
			{
				lr_dot[i][1]=p;		//�ȼ�¼�¿��ܵ����
			}
			else
			{
				total_line_num=2;
				break;
			}	
		}		
		if(is_black&&turn_black(&ImageBuf[p.x][p.y]))		//�Ӻڵ��ɰ׵�
		{
			is_black=0;
			if(total_line_num==0)
			{
				total_line_num++;		//���һ������
			}
			else if(total_line_num==1)			//�����������
			{
				mid_dot[i].x=(lr_dot[i][0].x+p.x)/2;		//�����е�
				mid_dot[i].y=(lr_dot[i][0].y+p.y)/2;
				total_line_num++;
				break;
			}
		}		
		pl_move(&p,xielv);			//�������ƶ�һ��
	}
	
}


void aright_scan_2nd(point p,u8 i)			//�����ҷ���ɨ������
{
	u8 is_black=0;			//��ǰ�Ƿ�Ϊ�ڵ�
	while((p.x>=0)&&(p.x<=COL)&&(p.y>=0)&&(p.y<=ROW))		//�е㣨�ƶ��ĵ㣩��ͼ����
	{			
		if(!is_black&&turn_black(&ImageBuf[p.x][p.y]))			//�Ӱ׵��ɺڵ�
		{
			is_black=1;			//��ǰΪ�ڵ�
			if(total_line_num==0)
			{
				lr_dot[i][0]=p;		//��¼�¿��ܵ����		
			}
			else if(total_line_num==1)
			{
				lr_dot[i][1]=p;		//��¼�¿��ܵ��ҵ�
			}
			else 
			{
				total_line_num=2;
				break;
			}		
		}
	
		if(is_black&&turn_white(&ImageBuf[p.x][p.y]))			//�Ӻڵ��ɰ׵�
		{
			is_black=0;
			if(total_line_num==0)			//��ȡһ������
			{
				total_line_num++;
			}
			else if(total_line_num==1)			//��ȡ��������
			{
				mid_dot[i].x=(lr_dot[i][0].x+p.x)/2;		//�����е�
				mid_dot[i].y=(lr_dot[i][0].y+p.y)/2;
				total_line_num++;
				break;
			}
		}		
		pr_move(&p,xielv);			//�����ҷ��ƶ�һ��
	}
}

void get_mid()
{
  u16 i;
  u8 aleft_line_num=0;		//����ɨ��ʱɨ������������

  for(i=0;i<HANG;i++)		//��Ҫ�ɼ�����
  {
	if(is_point_outside(&mid_dot[i]))	break;		//�е���ͼ����
	
	/***********���м�����ɨ*************/		
	aleft_scan_1st(mid_dot[i],i);	
	
	if((aleft_line_num=total_line_num)>=2)	 break;	   //��¼��������ɨ��ʱɨ������������
					//������ɨ��ʱ�Ѿ�ɨ����������
					
	/***********���м�����ɨ*************/
	else
	{
		aright_scan_2nd(mid_dot[i],i);		
	}		
				
	/************��������ҷ���ɨ��***************/
	if(total_line_num>=2)				//һ��ɨ����������
	break;
	else if((total_line_num==1)&&(aleft_line_num==1))			//һ��ֻɨ��һ����������Ϊ����ɨʱɨ��,��Ϊ����	
	{
		//if(lr_dot[i][0].)
	}
	else if((total_line_num==1)&&(aleft_line_num==0))			//һ��ֻɨ��һ����������Ϊ����ɨʱɨ������Ϊ����	
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


//����������
u16 half_restore(u8 hang)
{
  if(hang<=100)
    return (22+hang*0.6);
  else 
    return (41+hang*0.4);
}

//��ȡ����
/*void scan_mid()    //120��             
{
	s16 i,j,k=ROW/2-1,temp;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //�ɼ���������
	for(i=ROW-1;i>=0;i-=2,k--)
	{     
		for(j=mid[k];j>=0;j--)          //ɨ������
		{
			if(is_line(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[k];j<COL-4;j++)               //ɨ������
		{
			if(get_left&&is_line(&ImageBuf[i][j]))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)                 //ɨ�赽����˫��
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
                else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //�����߶�ûɨ�赽
                mid[k]=mid[k+1];
                
                if((miss_left_count>50)&&((temp=(mid[i]-miss_left_count+30))>=0))
                  mid[k]-=temp;
                if((miss_right_count>50)&&((temp=(mid[i]+miss_right_count-30))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
}*/

/*void scan_mid()               //������          
{
	s16 i,j,temp;
        u16 left=0,right=COL;
	u8 get_left=0,get_right=0;      //�ɼ���������
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


/*void scan_mid()    //60��             
{
	signed int i,j,k=ROW/4-1,temp,count_diff;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //�ɼ���������
	for(i=ROW-1;i>=0;i-=4,k--)
	{     
		for(j=mid[k];j>=0;j--)          //ɨ������
		{
			if(turn_black(&ImageBuf[i][j])||turn_white(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[k];j<COL-4;j++)               //ɨ������
		{
			if(get_left&&(turn_black(&ImageBuf[i][j])||turn_white(&ImageBuf[i][j])))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)                 //ɨ�赽����˫��
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
                else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //�����߶�ûɨ�赽
                mid[k]=mid[k+1];
                
                if(((count_diff=(miss_left_count-miss_right_count))>25)&&((temp=(mid[k]-count_diff+15))>=0))
                  mid[k]-=temp;
                else if((count_diff<-25)&&((temp=(mid[k]-count_diff-15))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
}*/




void scan_mid()    //60��(59)  ,320/3��           
{
	signed int i,j,k=ROW/4-2,temp,count_diff;
        u16 left=0,right=COL-6; 
        u8 get_left=0,get_right=0;      //�ɼ��������߱�־
        u8 miss_double_count=0;         //��ʧ˫�߼���
	for(i=ROW-2;i>=0;i-=4,k--)
	{     
                if(!is_black(&ImageBuf[i][160]))          //��ǰΪ�׵�,��������
		{
                        for(j=COL/2-3;j>=0;j-=3)          //ɨ������
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                            left=j;
                            get_left=1;
                            break;
                          }
                        }
                        
                        for(j=COL/2+3;j<COL-10;j+=3)               //ɨ������
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                             right=j;
                             get_right=1;
			     break;
                          }
                        }
		}
                else                      //��ǰΪ�ڵ�,����������
                {
                        for(j=COL/2-3;j>=0;j-=3)          //����ɨ��
                        {
                          if(!is_black(&ImageBuf[i][j]))        //��ȡ����
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
                        
                        if((!get_left)&&(!get_right))            //�����߶�ûɨ�赽
                        {
                          for(j=COL/2+3;j<COL-10;j+=3)          //����ɨ��
                          {
                            if(!is_black(&ImageBuf[i][j]))        //��ȡ����
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
                

		if(get_left&&get_right&&((right-left)<(half_restore(i)*2+40))&&((right-left)>(half_restore(i)*2-40)))                 //ɨ�赽����˫��
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
                else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  //miss_left_count++;
                  //if(i<ROW-2)
                  //mid[k]=mid[k+1]-10;
                  mid[k]=right-half_restore(i);
                }
                else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  mid[k]=left+half_restore(i);
                }
                /*else if(i<(ROW-2))                              //�����߶�ûɨ�赽
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
        u8 get_left=0,get_right=0;      //�ɼ���������
	for(i=ROW-1;i>=0;i-=4,k--)
	{     
		for(j=mid[k];j>=0;j--)          //ɨ������
		{
			if(black_to_white(&ImageBuf[i][j]))
			{
				left=j;
				get_left=1;
				break;
			}
		}
		for(j=mid[k];j<COL-4;j++)               //ɨ������
		{
			if(white_to_black(&ImageBuf[i][j]))
			{
				right=j;
				get_right=1;
				break;
			}
		}

		if(get_left&&get_right)                 //ɨ�赽����˫��
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
                else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //�����߶�ûɨ�赽
                mid[k]=mid[k+1];
                
                if(((count_diff=(miss_left_count-miss_right_count))>25)&&((temp=(mid[k]-count_diff+15))>=0))
                  mid[k]-=temp;
                else if((count_diff<-25)&&((temp=(mid[k]-count_diff-15))<=COL))
                  mid[k]+=temp;
                
                get_left=0,get_right=0; 
	}
  
}

/*void scan_mid()    //60��  ,320��           
{
	signed int i,j,k=ROW/4-1,temp,count_diff;
        u16 left=0,right=COL;
        u8 get_left=0,get_right=0;      //�ɼ���������

	for(i=ROW-1;i>=0;i-=4,k--)
	{     
                if(!is_black(&ImageBuf[i][mid[k]]))          //��ǰΪ�׵�,��������
		{
                        for(j=mid[k]-1;j>=0;j--)          //ɨ������
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                            left=j;
                            get_left=1;
                            break;
                          }
                        }
                        
                        for(j=mid[k]+1;j<COL-4;j++)               //ɨ������
                        {
                          if(is_black(&ImageBuf[i][j]))
                          {
                             right=j;
                             get_right=1;
			     break;
                          }
                        }
		}
                else                      //��ǰΪ�ڵ�,����������
                {
                        for(j=mid[k]-1;j>=0;j--)          //����ɨ��
                        {
                          if(!is_black(&ImageBuf[i][j]))        //��ȡ����
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
                        
                        if((!get_left)&&(!get_right))            //�����߶�ûɨ�赽
                        {
                          for(j=mid[k]+1;j<COL-4;j++)          //����ɨ��
                          {
                            if(!is_black(&ImageBuf[i][j]))        //��ȡ����
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
                

		if(get_left&&get_right)                 //ɨ�赽����˫��
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
                else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_left_count++;
                }
                else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
                {
                  miss_right_count++;
                }
                else if(i<(ROW-1))                              //�����߶�ûɨ�赽
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
  u8 get_left=0,get_right=0;      //�ɼ��������߱�־
  u8 line_current;
  s16 mid_need_temp[3];
  u8 get_mid_num=0;       //�ɼ����е����
  //u8 miss_double_count=0;         //��ʧ˫�߼���
  u8 *p,*q;

  for(i=0;i<3;i++)
  {
    q=p=((*(ImageBuf+(*(line_need_scan1+i))))+160);
    //q=p=&ImageBuf[line_need_scan1[i]][160];
    if(!is_black(p))          //��ǰΪ�׵�,��������
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //ɨ������
      {
        if(is_black(p))
        {
          left=j;
          get_left=1;
          break;
        }
      }
      p=q;                   
      for(j=164,p+=4;j<COL-11;j+=4,p+=4)               //ɨ������
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
    else                      //��ǰΪ�ڵ�,����������
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //����ɨ��
      {
        if(!is_black(p))        //��ȡ����
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
                        
      if((!get_left)&&(!get_right))            //����ɨ��ʱ�����߶�ûɨ�赽
      {
        p=q;
        for(j=164,p+=4;j<COL-11;j+=4,p+=4)          //����ɨ��
        {
          if(!is_black(p))        //��ȡ����
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
    if(get_left&&get_right&&((right-left)<(half_restore(line_current)*2+40))&&((right-left)>(half_restore(line_current)*2-40)))                 //ɨ�赽����˫��
    {         
        *(mid_need_temp+i)=(left+right)/2;
        get_mid_num++;
    }
    else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
    {
        *(mid_need_temp+i)=right-half_restore(line_current);
        get_mid_num++;
    }
    else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
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
  u8 get_left=0,get_right=0;      //�ɼ��������߱�־
  u8 line_current;
  s16 mid_need_temp[4];
  u8 get_mid_num=0;       //�ɼ����е����

  u8 *p,*q;

  for(i=0;i<4;i++)
  {
    line_current=*(line_need_scan1+i);
    q=p=((*(ImageBuf+(*(line_need_scan1+i))))+160);
    get_left=get_right=0;
    
    if(!is_black(p))          //��ǰΪ�׵�,��������
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //ɨ������
      {
        if(is_black(p))
        {
          left=j;
          get_left=1;
          break;
        }
      }
      p=q;                   
      for(j=164,p+=4;j<COL-11;j+=4,p+=4)               //ɨ������
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
        cross_flag=1;           //ʮ��·�ڱ�־
        return 1;
      }
 //     else
   //     cross_flag=0;
    }
    else                      //��ǰΪ�ڵ�,����������
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //����ɨ��
      {
        if(!is_black(p))        //��ȡ����
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
                        
      if((!get_left)&&(!get_right))            //����ɨ��ʱ�����߶�ûɨ�赽
      {
        p=q;
        for(j=164,p+=4;j<COL-11;j+=4,p+=4)          //����ɨ��
        {
          if(!is_black(p))        //��ȡ����
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
  
    
   /* if(get_left&&get_right&&((right-left)<(half_restore(line_current)*2+80))&&((right-left)>(half_restore(line_current)*2-80)))                 //ɨ�赽����˫��
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
    else if((!get_left)&&get_right)                 //ɨ�赽���ߣ�û��ɨ�赽����
    {
        *(mid_need_temp+i)=right-half_restore(line_current);
        get_mid_num++;
        cross_flag=0;
    }
    else if(get_left&&(!get_right))                 //ɨ�赽���ߣ�û��ɨ�赽����
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
  u8 get_left=0,get_right=0;      //�ɼ��������߱�־
  u8 line_current;
  s16 mid_need_temp[4];
  u8 get_mid_num=0;       //�ɼ����е����
  u8 *p,*q;
  
  cross_flag=0;			//ʮ��·�ڱ�־
  
  for(i=0;i<4;i++)
  {
	get_left=get_right=0;
    line_current=*(line_need_scan1+i);
    q=p=((*(ImageBuf+(*(line_need_scan1+i))))+160);
	
    if(!is_black(p))          //��ǰΪ�׵�,��������
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //ɨ������
      {
        if(is_black(p))
        {
          left=j;
          get_left=1;
          break;
        }
      }
	  
	  if(get_left)			//����ɨ��ʱɨ�赽����
	  {
		*(mid_need_temp+i)=left+half_restore(line_current);
        get_mid_num++;
		continue;
	  }
	  else			//����ɨ��ʱû��ɨ�������,������ɨ��
	  {
		p=q;                   
		for(j=164,p+=4;j<COL-11;j+=4,p+=4)               //ɨ������
		{
			if(is_black(p))
			{
			right=j;
			get_right=1;
			break;
			}
		}
		
		if(get_right)			//����ɨ��ʱɨ�赽����
		{
			*(mid_need_temp+i)=right-half_restore(line_current);
			get_mid_num++;
			continue;
		}
	  }

      cross_flag=1;           //ʮ��·�ڱ�־
      return 1;

    }
    else                      //��ǰΪ�ڵ�,����������
    {
      for(j=156,p-=4;j>=0;j-=4,p-=4)          //����ɨ��
      {
        if(!is_black(p))        //��ȡ����
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
      else            //����ɨ��ʱû��ɨ�赽����
      {
        p=q;
        for(j=164,p+=4;j<COL-11;j+=4,p+=4)          //����ɨ��
        {
          if(!is_black(p))        //��ȡ����
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