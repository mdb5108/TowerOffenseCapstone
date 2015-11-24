// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerOffense.h"
#include "VikingMinion.h"
#include "PathNode.h"
//#include "BasicClasses.h"

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
	delta_local += DeltaTime;
    switch(curState)
    {
		case AI_STATE::FOLLOW_PATH:
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
        case AI_STATE::HOSTILE:
            break;
		case AI_STATE::DEAD:
			//speed = 2.0f;
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
	if (otherActor->ActorHasTag("FlamingBall") && delta_local >= 2)
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
		delta_local = 0;
		UE_LOG(LogTemp, Warning, TEXT("Collider triggered"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("My Object's location is %s"), *ActorItr->GetActorLocation().ToString());
}
