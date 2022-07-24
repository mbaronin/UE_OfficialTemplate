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

	//倒数的运行时长（以秒计）
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
	和 UPROPERTY 宏相同，需提供使用其进行操作的相关信息，以便非程序员开发者可使用更多功能和访问权。有三种选择可使用：
	BlueprintCallable 函数以C++编写，可从 蓝图图表 中调用，但只能通过编辑C++代码进行修改或重写。以此类方式标记的函数通常具备供非程序员使用而编写的功能，但是不应对其进行修改，否则修改将毫无意义。数学函数便是此类函数的经典范例。
	在C++ header (.h)文件中设置 BlueprintImplementableEvent 函数，但是函数的主体则在蓝图图表中完成编写，而非C++中。创建此类通常是为了使非程序员能够对无预期默认动作或标准行为的特殊情况创建自定义反应。在宇宙飞船游戏中，玩家飞船接触到能量升级时发生的事件便是这方面的范例。
	BlueprintNativeEvent 函数与 BlueprintCallable 和 BlueprintImplementableEvent 函数的组合类似。其具备用C++中编程的默认行为，但此类行为可通过在蓝图图表中覆盖进行补充或替换。对此类代码编程时，C++代码固定使用命名末尾添加了_Implementation的虚拟函数，如下所示。此为最为灵活的选项，因此本教程将采用这种方法。
	*/
};
