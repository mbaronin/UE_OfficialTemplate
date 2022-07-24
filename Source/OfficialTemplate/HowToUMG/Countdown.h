// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class OFFICIALTEMPLATE_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//����������ʱ��������ƣ�
	UPROPERTY(EditAnywhere)
		int32 CountdownTime;
	class UTextRenderComponent* CountdownText;

	void UpdateTimerDisplay();

	void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();

	virtual void CountdownHasFinished_Implementation();

	FTimerHandle CountdownTimerHandle;

	/*
	�� UPROPERTY ����ͬ�����ṩʹ������в����������Ϣ���Ա�ǳ���Ա�����߿�ʹ�ø��๦�ܺͷ���Ȩ��������ѡ���ʹ�ã�
	BlueprintCallable ������C++��д���ɴ� ��ͼͼ�� �е��ã���ֻ��ͨ���༭C++��������޸Ļ���д���Դ��෽ʽ��ǵĺ���ͨ���߱����ǳ���Աʹ�ö���д�Ĺ��ܣ����ǲ�Ӧ��������޸ģ������޸Ľ��������塣��ѧ�������Ǵ��ຯ���ľ��䷶����
	��C++ header (.h)�ļ������� BlueprintImplementableEvent ���������Ǻ���������������ͼͼ������ɱ�д������C++�С���������ͨ����Ϊ��ʹ�ǳ���Ա�ܹ�����Ԥ��Ĭ�϶������׼��Ϊ��������������Զ��巴Ӧ��������ɴ���Ϸ�У���ҷɴ��Ӵ�����������ʱ�������¼������ⷽ��ķ�����
	BlueprintNativeEvent ������ BlueprintCallable �� BlueprintImplementableEvent ������������ơ���߱���C++�б�̵�Ĭ����Ϊ����������Ϊ��ͨ������ͼͼ���и��ǽ��в�����滻���Դ��������ʱ��C++����̶�ʹ������ĩβ�����_Implementation�����⺯����������ʾ����Ϊ��Ϊ����ѡ���˱��̳̽��������ַ�����
	*/
};
