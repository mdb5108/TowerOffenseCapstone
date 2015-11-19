// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PathNode.generated.h"

UCLASS()
class TOWEROFFENSE_API APathNode : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APathNode();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    // Called when the game ends or actor destroyed
    virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    virtual bool ShouldTickIfViewportsOnly() const override;

    void SetSelectedPath(int8 const selected);
    APathNode const * GetSelectedPathNode() const;

private:
    bool IsSelectedValid( int8 const selected) const;

    UPROPERTY(EditAnywhere, Category = "Nodes")
    TArray<APathNode*> pathsOut;

    UPROPERTY(EditAnywhere, Category = "Nodes")
    int8 selectedPath = 0;
};
