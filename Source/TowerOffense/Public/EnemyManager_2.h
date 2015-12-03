// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "VikingMinion.h"
#include "EnemyManager_2.generated.h"


/**
 * 
 */

UCLASS()
class TOWEROFFENSE_API AEnemyManager_2 : public AGameMode
{
	GENERATED_BODY()

	public:
	//Begin Playing 
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyManager")
	TArray<AVikingMinion *> minions_list;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyManager")
	int32 minion_count;

	float delta_local = 0;
};
