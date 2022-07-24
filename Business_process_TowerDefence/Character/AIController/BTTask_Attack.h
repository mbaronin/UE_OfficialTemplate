// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class BUSINESS_PROCESS_2_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	//防止编译失败 必须添加的接口
	/** Notify called after GameplayTask finishes initialization (not active yet) */
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {}


public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	//用于蓝图接收
	UPROPERTY(EditAnywhere, Category = Blackboard)
		struct FBlackboardKeySelector Blackboard_Actor;


};
