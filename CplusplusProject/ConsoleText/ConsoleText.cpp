#include "Windows.h"
#include <iostream>
#include <tchar.h>
#include <string>
#include <strsafe.h>
#include <conio.h>
#include <stdio.h>
#include <consoleapi2.h>
#include "parser.h"
#include "GameCore.h"
// 직접만들 헤더1.
// 직접만들 헤더2.


int main()
{
	// 콘솔 크기를 먼저 결정
	TCHAR buf[256]; // 키보드 자판을 모두 대응하는 크기
	StringCchPrintfW(buf, 256, TEXT("%s 콘솔 텍스트 게임 버전 %d"), _T("MadyBy 황은중"), 1.00f);
	SetConsoleTitleW(buf);

	// 1. 메인 메뉴 : 게임 시작(데이터의 초기화를 진행한다) : 맵 생성(크기), 맵의 종류가 다항하다면 시작맵을 설정한다.
	// 플레이어의 시작 위치, 시작 아이템, 시작 소지금, 시작 스탯 등등..
	// InitializeGame();
	PlayerState player;
	WorldState world;
	InitializeGame(player, world);



	// namespace ConsoleText GamePlay 클래스 -> 1. 플레이어의 입력을 변환해주는 클래스 2. 플레이 함수를 구현하는 클래스

	while (true)
	{
		RenderGame(player, world);  // Rendering : 이미지(맵)를 그려주는 것
		GetInput(player, world);   // 플레이어의 입력 : if(Async wasd) -> if() -> if()
		//ParseCommand();
		UpdateGame(player, world); // Update    : 특정 위치에 도착하면 다음 맵으로 이동한다. 플레이어의 위치, 특정 장소의 위치 같은지 아닌지

		
		
		// Quit : 게임 종료 기능 함수, Bool Quit = true => break Exit(0);
	}
}


