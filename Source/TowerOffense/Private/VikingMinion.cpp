// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerOffense.h"
#include "VikingMinion.h"
#include "PathNode.h"

// Sets default values
AVikingMinion::AVikingMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    movementComp = static_cast<UCharacterMovementComponent*>(this->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
}

// Called when the game starts or when spawned
void AVikingMinion::BeginPlay()
{
	Super::BeginPlay();

    curState = AI_STATE::FOLLOW_PATH;
}

// Called every frame
void AVikingMinion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    switch(curState)
    {
        case FOLLOW_PATH:
            if(currentNode != NULL)
            {
                UCharacterMovementComponent::FStepDownResult* outStepDownResult = NULL;
                FVector direction = currentNode->GetActorLocation() - GetActorLocation();
                direction.Z = 0;
                if(direction.Size() < nearDestinationThreshold)
                {
                    currentNode = currentNode->GetSelectedPathNode();
                }
                direction.Normalize();
                AddMovementInput(direction, speed);
                SetActorRotation(direction.Rotation());
            }
            break;
        case HOSTILE:
            break;
        default:
            checkf(false, TEXT("Ran into unknown state!"));
            break;
    }
}

// Called to bind functionality to input
void AVikingMinion::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

