// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"

#include "UI/GameUI/Core/RuleofTheHUD.h"
#include "UI/GameUI/UMG/UI_MainScreen.h"
#include "UI/GameUI/UMG/UI_RucksackSystem.h"
#include "UI/GameUI/UMG/Inventory/UI_Inventory.h"

#include "Global/UI_Datas.h"

#include "Engine/StaticMeshActor.h"			//������

ATowerDefencePlayerController::ATowerDefencePlayerController()
{
	//��ʾ���
	bShowMouseCursor = true;
	
	//�������¼�
	bEnableClickEvents = true;

	ScreenMoveSpeed = -20.f; 
	//������Ļ�ƶ�BUG
	CanScreenMove = true;
	Tmpbool = true;
	DoubleTmpbool = true;


	//��ȡԤ������
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialGreen(TEXT("/Game/Material/PreviewMaterial_Green.PreviewMaterial_Green"));
	if (MaterialGreen.Succeeded())	{GreenMaterial = MaterialGreen.Object;	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRed(TEXT("/Game/Material/PreviewMaterial_Red.PreviewMaterial_Red"));
	if (MaterialGreen.Succeeded())	{RedMaterial = MaterialRed.Object;	}


}


//����Ϸ�д�ӡ
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
	
	////��Ļ�ƶ����
	if (CanScreenMove) 	//��קʱ ���λ�û�����BUG ˫�ؼ��
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

	//���������߼��λ��	ifԤ����ģʽ 
	if (TowerPreview)
	{
		FHitResult TaceOutHit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, true, TaceOutHit);//TOH �ǹ�����Χ���
		if (TaceOutHit.Location !=FVector::ZeroVector)
		{
			//MouseHitPoint����
			if (MouseHitPoint.Location != FVector::ZeroVector) { MouseHitPoint = FHitResult(); }

			TowerPreview->SetActorLocation(TaceOutHit.Location);//����Ԥ��ģ��λ��
			SetMeshMaterial(TowerPreview, GreenMaterial);//����Ԥ������

			Printez(TEXT("Building indicator position : "), TaceOutHit.Location.ToString());
		}
		else//TOH û�м�⵽   Ԥ�����ʱ�� ������ͨ���
		{
			GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel5, true, MouseHitPoint);
			TowerPreview->SetActorLocation(MouseHitPoint.Location);//����Ԥ��ģ��λ��
			SetMeshMaterial(TowerPreview, RedMaterial);//����Ԥ������

			Printez(TEXT("Can`t Building indicator position : "), MouseHitPoint.Location.ToString());
		}
	}
	else
	{
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel4, true, MouseHitPoint);//3��ͨ�����"����������" 4��ͨ������ɫ 5��ΪĬ��
		
		Printez(TEXT("Wait time indicator position : "), MouseHitPoint.Location.ToString());
	}
}

//	if (MouseHitPoint.Location != FVector::ZeroVector) { MouseHitPoint = FHitResult(); }
//FHitResult TaceOutHit;
//GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, true, TaceOutHit);
////ͨ��ͨ�������� ͨ������ͼ�����
//			//�������ͨ��Construction(ignore)->������ײ����Building(CE,WS,Block Visibility && Construction)
//			//��Ŀ/Config/DefaultEngine.ini�ļ�	//+DefaultChannelResponses=(Channel=ECC_GameTraceChannel3,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="Construction")	
//			//3��ͨ�����"����������" 4��ͨ������ɫ 5��ΪĬ��
//FHitResult TaceOutHit;
//GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel3, true, TaceOutHit);
//TowerPreview->SetActorLocation(TaceOutHit.Location);


void ATowerDefencePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//������������ӿ���
	SetInputModeGameAndUI();

	//UpdateGlobalVar();

}




//������������ӿ���
void ATowerDefencePlayerController::SetInputModeGameAndUI()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);

	SetInputMode(InputMode);
}

//�����밴��
void ATowerDefencePlayerController::SetupInputComponent()
{
	/*����
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);IE_Released*/

	Super::SetupInputComponent();

	//��������
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATowerDefencePlayerController::MouseWheelUp);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATowerDefencePlayerController::MouseWheelDown);
	InputComponent->BindAction("MouseRightButton", IE_Pressed, this, &ATowerDefencePlayerController::MouseRightButtonPressed);
	InputComponent->BindAction("MouseRightButton", IE_Released, this, &ATowerDefencePlayerController::MouseRightButtonReleased);

}
static float MouseWheelSpeed = 15.f;

//�����ֿ���
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
	//ִ�д���
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



