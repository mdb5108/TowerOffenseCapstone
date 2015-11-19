// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerOffense.h"
#include "PathNode.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


// Sets default values
APathNode::APathNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APathNode::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryActorTick.bCanEverTick = false;
}

void APathNode::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void APathNode::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    //Get arrows
    TArray<UArrowComponent*> arrows;
    {
        TArray<UArrowComponent*> ret;
        GetComponents(ret);
        for (UActorComponent* Component : ret)
        {
            if (Component && Component->IsA(UArrowComponent::StaticClass()))
            {
                arrows.Add(static_cast<UArrowComponent*>(Component));
            }
        }
    }

    //Increase or decrease arrows if necessary
    if(arrows.Num() < pathsOut.Num())
    {
        for(int i = arrows.Num(); i < pathsOut.Num(); i++)
        {
            UArrowComponent* tmp = NewObject<UArrowComponent>(GetRootComponent(), FName(*FString::Printf(TEXT("DisplayArrow%d"), i)));
            if(tmp != NULL)
            {
                arrows.Add(tmp);
                tmp->RegisterComponent();
                tmp->AttachTo(GetRootComponent());
            }
        }
    }
    else if(arrows.Num() > pathsOut.Num())
    {
        for(int i = pathsOut.Num(); i < arrows.Num(); i++)
        {
            arrows[i]->DestroyComponent();
            arrows[i]->UnregisterComponent();
        }

        for(int i = arrows.Num()-1; i >= pathsOut.Num(); i--)
        {
            arrows.RemoveAt(i);
        }
    }

    //Point arrows towards nodes
    for(int i = 0; i < arrows.Num(); i++)
    {
        if(pathsOut[i] != NULL)
        {
            FVector direction = (pathsOut[i]->GetActorLocation() - this->GetActorLocation());
            arrows[i]->SetWorldRotation(direction.Rotation());
        }
    }
}


bool APathNode::ShouldTickIfViewportsOnly() const
{
    return true;
}

inline void APathNode::SetSelectedPath(int8 const selected)
{
    check(IsSelectedValid(selectedPath));
    selectedPath = selected;
}
inline APathNode const * APathNode::GetSelectedPathNode() const
{
    check(IsSelectedValid(selectedPath));
    return pathsOut[selectedPath];
}

inline bool APathNode::IsSelectedValid( int8 const selected) const
{
    return 0 <= selected && selected < pathsOut.Num();
}
