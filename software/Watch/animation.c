/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"

#if COMPILE_ANIMATIONS

static anim_s animationStatus;

// http://javascript.info/tutorial/animation

void animation_init()
{
	animationStatus.active = false;
	animationStatus.animOnComplete = NULL;
}

void animation_update()
{
	if(animationStatus.active)
	{
		byte offsetY = animationStatus.offsetY;
		if(animationStatus.goingOffScreen)//形成关闭动画
		{
			if(offsetY < 4)
				offsetY += 1;
			else if(offsetY < 8)
				offsetY += 3;
			else if(offsetY < 16)
				offsetY += 5;
			else
				offsetY += 8;

			if(offsetY >= FRAME_HEIGHT)
			{
				animationStatus.active = false;
				offsetY = 0;
			}
		}
		else//形成开启动画
		{
			if(offsetY > 255 - 4)
				offsetY += 1;
			else if(offsetY > 255 - 8)
				offsetY += 3;
			else if(offsetY > 255 - 16)
				offsetY += 5;
			else
				offsetY += 8;

			if(offsetY < 10)
			{
				animationStatus.active = false;
				offsetY = 0;
			}
		}

		animationStatus.offsetY = offsetY;
		if(!animationStatus.active && animationStatus.animOnComplete != NULL)//一般是关闭动画有这个函数，动画结束后执行这个函数，用来注册新界面的功能
		{
			animationStatus.animOnComplete();//注册新界面的功能
			animationStatus.animOnComplete = NULL;
		}
	}
}




//开始动画函数
//参数：animOnComplete ，函数指针指向函数，动画过程中要执行的函数
//goingOffScreen  未知？？？？
void animation_start(void (*animOnComplete)(void), bool goingOffScreen)
{
	
	if(appConfig.animations)      
	{
		animationStatus.active = true;
		animationStatus.offsetY = goingOffScreen ? 0 : 192;
		animationStatus.animOnComplete = animOnComplete;
		animationStatus.goingOffScreen = goingOffScreen;
	}
	
	else
	{
		if(animOnComplete != NULL)
			animOnComplete();
	}	
		
}

bool animation_active()
{
	return animationStatus.active;
}

bool animation_movingOn()
{
	return !animationStatus.goingOffScreen;
}

byte animation_offsetY()
{
	return animationStatus.offsetY;
}


#else


 void animation_start(void (*animOnComplete)(void), bool goingOffScreen)
{
	(void)(goingOffScreen);
	if(animOnComplete != NULL)
		animOnComplete();
}


#endif
