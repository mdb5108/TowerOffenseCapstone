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

    UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Minion")
    float speed;

	//minions take damage
	UPROPERTY(EditAnywhere, Category = "Minion")
	float current_health;

	UFUNCTION()
	void on_collision(class AActor* otherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UPROPERTY(EditAnywhere, Category = "Minion")
	float delta_local = 0;

	UENUM(BlueprintType)
	enum  class AI_STATE : uint8//class//PATTERN_ENUM : uint8
	{
		FOLLOW_PATH = 0 UMETA(DisplayName = "Follow Path"),
		HOSTILE UMETA(DisplayName = "Hostile"),
		DEAD UMETA(DisplayName = "Dead"),
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minion")
	AI_STATE curState;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minion")
	//static int32   count_of_minions;
	////Set to public to access from blueprint
	//UPROPERTY(EditAnywhere, Category = "Minion")
	

private:
    //enum AI_STATE { FOLLOW_PATH, HOSTILE, DEAD };    
	//AI_STATE curState;
    UCharacterMovementComponent* movementComp;
};
