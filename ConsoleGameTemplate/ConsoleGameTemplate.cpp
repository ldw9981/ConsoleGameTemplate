// ConsoleDoubleBuffering.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "ConsoleRenderer.h"
#include "Input.h"
#include "Time.h"
#include <stdio.h>

bool g_bQuit = false;
void Update();
void Render();
void ProcessInput();

COORD g_Player = { 0,0 };

int main()
{	
	ConsoleRenderer::ScreenInit();	
	Time::InitTime();
	while (!g_bQuit)
	{
		Time::UpdateTime();
		Input::Update();		
		Update();
		Render();
	};

	ConsoleRenderer::ScreenRelease();
}


void ProcessInput()
{
	if (Input::IsKeyDown(VK_LEFT)) { //왼쪽
		g_Player.X--;
	}
	if (Input::IsKeyDown(VK_RIGHT)) { //오른쪽
		g_Player.X++;
	}
	if (Input::IsKeyDown(VK_UP)) { //위
		g_Player.Y--;
	}
	if (Input::IsKeyDown(VK_DOWN)) { //아래
		g_Player.Y++;
	}
	if (Input::IsKeyDown(VK_ESCAPE)) { //종료
		g_bQuit = true;
	}

}

void Update()
{
	ProcessInput();

	if (g_Player.X < 0) g_Player.X = 0;
	if (g_Player.X >= ConsoleRenderer::ScreenWidth()) g_Player.X = ConsoleRenderer::ScreenWidth() - 1;
	if (g_Player.Y < 0) g_Player.Y = 0;
	if (g_Player.Y >= ConsoleRenderer::ScreenHeight()) g_Player.Y = ConsoleRenderer::ScreenHeight() - 1;
}

void Render()
{
	ConsoleRenderer::ScreenClear();

	char buf[256] = { 0, };
	float time = Time::GetTotalTime();
	sprintf_s(buf,"프로그램 시작이후의 시간입니다. %f",Time::GetTotalTime());
	
	ConsoleRenderer::ScreenDrawString(0, 0, buf, FG_PINK_DARK);
	ConsoleRenderer::ScreenDrawString(0, 1,L"특수문자는 Wide Character의 출력이 필요합니다.abcd한글🌊🏄‍♂️🚁😀⭠⭡⭢⭣⭦⭧⭨⭩⬤111", FG_PINK_DARK);
	ConsoleRenderer::ScreenDrawChar(g_Player.X, g_Player.Y, L'A', FG_WHITE);
	
	ConsoleRenderer::ScreenFlipping();
}


