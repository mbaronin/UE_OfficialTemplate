// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProject/FPSProjectGameModeBase.h"
#include "FPSProject/FPSCharacter.h"


AFPSProjectGameModeBase::AFPSProjectGameModeBase()
{
    /* 
    GameStateClass = ATowerDefenceGameState::StaticClass();
    PlayerControllerClass = ATowerDefencePlayerController::StaticClass();
    DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();
    PlayerStateClass = ATowerDefencePlayerState::StaticClass();
    HUDClass = ARuleofTheHUD::StaticClass();
    */
    
    //DefaultPawnClass = AFPSCharacter::StaticClass();


}


void AFPSProjectGameModeBase::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);

    // ��ʾ������Ϣ���롣 
    // -1"��"ֵ������ֹ����Ϣ�����»�ˢ�¡�
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameModeBase!"));

}