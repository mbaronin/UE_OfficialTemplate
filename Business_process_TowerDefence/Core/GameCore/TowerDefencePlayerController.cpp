// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"

#include "UI/GameUI/Core/RuleofTheHUD.h"
#include "UI/GameUI/UMG/UI_MainScreen.h"
#include "UI/GameUI/UMG/UI_RucksackSystem.h"
#include "UI/GameUI/UMG/Inventory/UI_Inventory.h"

#include "Global/UI_Datas.h"

#include "Engine/StaticMeshActor.h"			//测试用

ATowerDefencePlayerController::ATowerDefencePlayerController()
{
	//显示鼠标
	bShowMouseCursor = true;
	
	//允许点击事件
	bEnableClickEvents = true;

	ScreenMoveSpeed = -20.f; 
	//修正屏幕移动BUG
	CanScreenMove = true;
	Tmpbool = true;
	DoubleTmpbool = true;


	//获取预览材质
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialGreen(TEXT("/Game/Material/PreviewMaterial_Green.PreviewMaterial_Green"));
	if (MaterialGreen.Succeeded())	{GreenMaterial = MaterialGreen.Object;	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRed(TEXT("/Game/Material/PreviewMaterial_Red.PreviewMaterial_Red"));
	if (MaterialGreen.Succeeded())	{RedMaterial = MaterialRed.Object;	}


}


//在游戏中打印
void Printez(FString str1, FString str2){
	FString abc = str1;		abc = abc.Append(str2);
	GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Yellow, abc);}


void SetMeshMaterial(AActor* InTowerPreview, UMaterialInterface* PreviewMaterial) {

	if (AStaticMeshActor* MeshActor = Cast<AStaticMeshActor>(InTowerPreview))
	{
		for (int32 i = 0; i < MeshActor->GetStaticMeshComponent()->GetNumMaterials(); i++)
		{
			MeshActor->GetStaticMeshComponent()->SetMaterial(i, PreviewMaterial);
		}
	}
}


void ATowerDefencePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	////屏幕移动插件
	if (CanScreenMove) 	//拖拽时 光标位置会归零的BUG 双重检测
	{
		if (Tmpbool)
		{
			if (DoubleTmpbool)
			{
				ScreenMoveUnits.ListenScreenMove(this, ScreenMoveSpeed);
			}
			else	{DoubleTmpbool = true;}
		}
		else		
		{ 
			Tmpbool = true; 
			DoubleTmpbool = false;
		}
	}
	else	{Tmpbool = false;}

	//计算光标射线检测位置	if预览塔模式 
	if (TowerPreview)
	{
		FHitResult TaceOutHit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, true, TaceOutHit);//TOH 是构建范围检测
		if (TaceOutHit.Location !=FVector::ZeroVector)
		{
			//MouseHitPoint归零
			if (MouseHitPoint.Location != FVector::ZeroVector) { MouseHitPoint = FHitResult(); }

			TowerPreview->SetActorLocation(TaceOutHit.Location);//调整预览模型位置
			SetMeshMaterial(TowerPreview, GreenMaterial);//设置预览材质

			Printez(TEXT("Building indicator position : "), TaceOutHit.Location.ToString());
		}
		else//TOH 没有检测到   预览材质变红 启用普通检测
		{
			GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel5, true, MouseHitPoint);
			TowerPreview->SetActorLocation(MouseHitPoint.Location);//调整预览模型位置
			SetMeshMaterial(TowerPreview, RedMaterial);//设置预览材质

			Printez(TEXT("Can`t Building indicator position : "), MouseHitPoint.Location.ToString());
		}
	}
	else
	{
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel4, true, MouseHitPoint);//3号通道检测"可生成网格" 4号通道检测角色 5号为默认
		
		Printez(TEXT("Wait time indicator position : "), MouseHitPoint.Location.ToString());
	}
}

//	if (MouseHitPoint.Location != FVector::ZeroVector) { MouseHitPoint = FHitResult(); }
//FHitResult TaceOutHit;
//GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, true, TaceOutHit);
////通过通道检测地面 通道在蓝图中设计
//			//创建检测通道Construction(ignore)->创建碰撞类型Building(CE,WS,Block Visibility && Construction)
//			//项目/Config/DefaultEngine.ini文件	//+DefaultChannelResponses=(Channel=ECC_GameTraceChannel3,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="Construction")	
//			//3号通道检测"可生成网格" 4号通道检测角色 5号为默认
//FHitResult TaceOutHit;
//GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, true, TaceOutHit);
//TowerPreview->SetActorLocation(TaceOutHit.Location);


void ATowerDefencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//将光标锁定在视口中
	SetInputModeGameAndUI();

	//UpdateGlobalVar();

}




//将光标锁定在视口中
void ATowerDefencePlayerController::SetInputModeGameAndUI()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);

	SetInputMode(InputMode);
}

//绑定输入按键
void ATowerDefencePlayerController::SetupInputComponent()
{
	/*案例
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);IE_Released*/

	Super::SetupInputComponent();

	//绑定鼠标滚轮
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATowerDefencePlayerController::MouseWheelUp);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATowerDefencePlayerController::MouseWheelDown);
	InputComponent->BindAction("MouseRightButton", IE_Pressed, this, &ATowerDefencePlayerController::MouseRightButtonPressed);
	InputComponent->BindAction("MouseRightButton", IE_Released, this, &ATowerDefencePlayerController::MouseRightButtonReleased);

}
static float MouseWheelSpeed = 15.f;

//鼠标滚轮控制
void ATowerDefencePlayerController::MouseWheelUp()
{
	ATowerDefenceGameCamera* ZoomCamera = Cast< ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(true, MouseWheelSpeed);
	}
}

void ATowerDefencePlayerController::MouseWheelDown()
{
	ATowerDefenceGameCamera* ZoomCamera = Cast< ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(false, MouseWheelSpeed);
	}
}


void ATowerDefencePlayerController::MouseRightButtonPressed()
{

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, TEXT("Right Pressed"));

	EventMouseRightPressed.ExecuteIfBound();
	//执行代理
	//EventMouseRightPressed.Broadcast();
}

void ATowerDefencePlayerController::MouseRightButtonReleased()
{
	
	EventMouseRightReleased.ExecuteIfBound();
	//EventMouseRightReleased.Broadcast();

}

const FHitResult& ATowerDefencePlayerController::GetHitResult()
{
	return MouseHitPoint;

}

void ATowerDefencePlayerController::UpdateInventory_Client(const FGuid& InventorySlotGUID, bool bInCD)
{
	if (ARuleofTheHUD* NewHUD = GetHUD<ARuleofTheHUD>())
	{
		//NewHUD->UpdateInventorySlot(InventorySlotGUID, bInCD);
		
		if (UUI_Inventory* NewInventory = NewHUD->MainScreen->RucksackSystem->Inventory)
		{
			NewInventory->UpdateInventorySlot(InventorySlotGUID, bInCD);
		}
	}
}



