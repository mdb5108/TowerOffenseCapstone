// Fill out your copyright notice in the Description page of Project Settings.

//#include <string>
//#include <iostream>
#include "TowerOffense.h"
#include "VikingMinion.h"
#include "PathNode.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

//#include "BasicClasses.h"

static FName NORDIC_NAMES[] =
{
TEXT("Kevin A"),
TEXT("Vega B"),
TEXT("Yash B"),
TEXT("Matt B"),
TEXT("Michael B"),
TEXT("Jared B"),
TEXT("Arpit C"),
TEXT("Leigh C"),
TEXT("Alan C"),
TEXT("Kun C"),
TEXT("Shreyas D"),
TEXT("Ajinkya D"),
TEXT("Jon D"),
TEXT("Rony D"),
TEXT("Karteek E"),
TEXT("Mitch E"),
TEXT("Ameya G"),
TEXT("Kenny G"),
TEXT("Yashas G"),
TEXT("Jeff J"),
TEXT("Utsav J"),
TEXT("Seth J"),
TEXT("Rishabh K"),
TEXT("Mitch K"),
TEXT("Cody L"),
TEXT("Kamchai L"),
TEXT("Wesley M"),
TEXT("Tara M"),
TEXT("James M"),
TEXT("Rohan M"),
TEXT("Sean M"),
TEXT("Kevin A"),
TEXT("Vega B"),
TEXT("Yash B"),
TEXT("Matt B"),
TEXT("Michael B"),
TEXT("Jared B"),
TEXT("Arpit C"),
TEXT("Leigh C"),
TEXT("Alan C"),
TEXT("Kun C"),
TEXT("Shreyas D"),
TEXT("Ajinkya D"),
TEXT("Jon D"),
TEXT("Rony D"),
TEXT("Karteek E"),
TEXT("Mitch E"),
TEXT("Ameya G"),
TEXT("Kenny G"),
TEXT("Yashas G"),
TEXT("Jeff J"),
TEXT("Utsav J"),
TEXT("Seth J"),
TEXT("Rishabh K"),
TEXT("Mitch K"),
TEXT("Cody L"),
TEXT("Kamchai L"),
TEXT("Wesley M"),
TEXT("Tara M"),
TEXT("James M"),
TEXT("Rohan M"),
TEXT("Sean M"),
};

FName AVikingMinion::GetRandomName()
{
    static const size_t arraySize = (sizeof(NORDIC_NAMES)/sizeof((NORDIC_NAMES[0])));
    return NORDIC_NAMES[FMath::RandRange(0, arraySize-1)];
}


// Sets default values
AVikingMinion::AVikingMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    movementComp = static_cast<UCharacterMovementComponent*>(this->GetComponentByClass(UCharacterMovementComponent::StaticClass()));

	//increment minion count
	//AVikingMinion::count_of_minion++;
	
	
	
}

// Called when the game starts or when spawned
void AVikingMinion::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* capComp = nullptr;
    curState = AI_STATE::FOLLOW_PATH;

	TArray<UCapsuleComponent*> Components;
	//this->GetComponents<UStaticMeshComponent>(Stat_Components);
	this->GetComponents<UCapsuleComponent>(Components);
	for (int32 i = 0; i<Components.Num(); i++)
	{
		//UStaticMeshComponent* StaticMeshComponent = Components[i];
		capComp = Components[i];
		//UE_LOG(LogTemp, Warning, TEXT("My Object's location is "));
		//UStaticMesh* StaticMesh = StaticMeshComponent->StaticMesh;
	}
	

	//OnActorHit.AddDynamic(this, &AVikingMinion::on_collision);
	//StaticMeshComponent->OnComponentHit.AddDynamic(this, &AVikingMinion::on_collsion);
	capComp->OnComponentBeginOverlap.AddDynamic(this, &AVikingMinion::on_overlap);
	
}

//void AVikingMinion::on_collision(class AActor* otherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


// Called every frame
void AVikingMinion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//UE_LOG(LogTemp, Warning, TEXT("Delta Time %f"),DeltaTime)
    switch(curState)
    {
		case AI_STATE::FOLLOW_PATH:
			//below code for debug
			//curState = AI_STATE::WON;

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
			//changes to include win condition
			else
			{
				curState = AI_STATE::WON;
				//for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
				//{
				//	//UE_LOG(LogTemp, Warning, TEXT("Actor %d"), ActorItr->GetUniqueID());// ->GetName());
				//	if (ActorItr->GetName().Contains(TEXT("AlliesManager"), ESearchCase::CaseSensitive, ESearchDir::FromStart))
				//	{
						//UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *ActorItr->GetName());
						//*ActorItr->IncrementWin();
						this->SetDead();
					//}
					//ClientMessage(ActorItr->GetActorLocation().ToString());
				//}
			}
            break;
        case AI_STATE::HOSTILE:
            break;
		case AI_STATE::DEAD:
			//speed = 2.0f;
			break;
		// do nothing on win state
		case AI_STATE::WON:
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

void AVikingMinion::on_overlap(class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor->ActorHasTag("FlamingBall"))
	{
		current_health--;
		UE_LOG(LogTemp, Warning, TEXT("Current health %f"),current_health);
		if (current_health <= 0)
		{
			curState = AI_STATE::DEAD;					
            GetMesh()->SetSimulatePhysics(true);
            GetMesh()->WakeRigidBody();
            /* Other interactions are don in the blueprint for simplicity's sake */
		}
		UE_LOG(LogTemp, Warning, TEXT("Collider triggered"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("My Object's location is %s"), *ActorItr->GetActorLocation().ToString());
}
