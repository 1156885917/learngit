#include <graphics.h>
#include <conio.h>
#include <math.h>

#define Height 480    //游戏画面尺寸
#define Width 640
#define BallNum 15     //定义小球个数

int main()
{
	float ball_x[BallNum], ball_y[BallNum];     //小球的坐标
	float ball_vx[BallNum], ball_vy[BallNum];   //小球的速度
	float radius;                               //小球的半径
	int i, j;
	radius = 20;

	for (i = 0;i < BallNum;i++)
	{
		ball_x[i] = rand() % (int)(Width - 4 * radius) + 2 * radius;
		ball_y[i] = rand() % (int)(Height - 4 * radius) + 2 * radius;
		ball_vx[i] = (rand() % 2) * 2 - 1;
		ball_vy[i] = (rand() % 2) * 2 - 1;
	}

	initgraph(Width, Height);   //初始化画布尺寸
	BeginBatchDraw();

	while (1)
	{
		//绘制黑线黑色填充的圆
		setcolor(BLACK);
		setfillcolor(BLACK);
		for (i = 0;i < BallNum;i++)
		{
			fillcircle(ball_x[i], ball_y[i], radius);
		}

		//更新小球地坐标
		for (i = 0;i < BallNum;i++)
		{
			ball_x[i] = ball_x[i] + ball_vx[i];
			ball_y[i] = ball_y[i] + ball_vy[i];

			//把超出边界的小球拉回来
			if (ball_x[i] < radius)
			{
				ball_x[i] = radius;
			}
			if (ball_y[i] < radius)
			{
				ball_y[i] = radius;
			}
			if (ball_x[i] > Width - radius)
			{
				ball_x[i] = Width - radius;
			}
			if (ball_y[i] > Height - radius)
			{
				ball_y[i] = Height - radius;
			}
		}

		//判断小球是否与墙壁相撞
		for (i = 0;i < BallNum;i++)
		{
			if ((ball_x[i] <= radius) || (ball_x[i] >= Width - radius))
			{
				ball_vx[i] = -ball_vx[i];
			}
			if ((ball_y[i] <= radius) || (ball_y[i] >= Height - radius))
			{
				ball_vy[i] = -ball_vy[i];
			}
		}

		float minDistances2[BallNum][2];      //记录某个小球和与它最近的小球之间的距离，以及这个小球的下标

		for (i = 0;i < BallNum;i++)
		{
			minDistances2[i][0] = 9999999;
			minDistances2[i][1] = -1;
		}

		//求所有小球两两之间距离的平方
		for (i = 0;i < BallNum;i++)
		{
			for (j = 0;j < BallNum;j++)
			{
				if (i != j)     //自己不需要和自己比
				{
					float dist2;
					dist2 = (ball_x[i] - ball_x[j]) * (ball_x[i] - ball_x[j]) + (ball_y[i] - ball_y[j]) * (ball_y[i] - ball_y[j]);
					if (dist2 < minDistances2[i][0])
					{
						minDistances2[i][0] = dist2;
						minDistances2[i][1] = j;
					}
				}
			}
		}

		//判断小球之间是否碰撞
		for (i = 0;i < BallNum;i++)
		{
			if (minDistances2[i][0] <= 4 * radius * radius)     //若距离小于阈值，则发生碰撞
			{
				j = minDistances2[i][1];
				//交换速度
				int temp;
				temp = ball_vx[i];
				ball_vx[i] = ball_vx[j];
				ball_vx[j] = temp;
				temp = ball_vy[i];
				ball_vy[i] = ball_vy[j];
				ball_vy[j] = temp;

				minDistances2[i][0] = 999999999;     //避免两次交换速度，又回去了
				minDistances2[i][1] = -1;
			}
		}

		//绘制黄线、绿色填充的圆
		setcolor(YELLOW);
		setfillcolor(GREEN);
		for (i = 0;i < BallNum;i++)
		{
			fillcircle(ball_x[i], ball_y[i], radius);
		}
		FlushBatchDraw();

		//延时
		Sleep(3);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}