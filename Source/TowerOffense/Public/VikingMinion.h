// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "VikingMinion.generated.h"

class APathNode;

UCLASS()
class TOWEROFFENSE_API AVikingMinion : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVikingMinion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
    UPROPERTY(EditAnywhere, Category = "Minion")
    APathNode const * currentNode;

    UPROPERTY(EditAnywhere, Category = "Minion")
    float nearDestinationThreshold;

    UPROPERTY(EditAnywhere, Category = "Minion")
    float speed;

private:
    enum AI_STATE { FOLLOW_PATH, HOSTILE };
    AI_STATE curState;

    UCharacterMovementComponent* movementComp;
};
