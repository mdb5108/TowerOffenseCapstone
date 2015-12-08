// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "MyGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class TOWEROFFENSE_API UMyGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
	//To get rid of keyboard show cursor
	virtual TOptional<bool> QueryShowFocus(const EFocusCause InFocusCause) const override;
	
	
};
