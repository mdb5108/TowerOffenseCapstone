// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerOffense.h"
#include "EnemyManager_2.h"
#include "VikingMinion.h"




// Called when the game starts or when spawned
void AEnemyManager_2::BeginPlay()
{
	Super::BeginPlay();

	

	for (TObjectIterator<AVikingMinion> Itr; Itr; ++Itr)
	{
		if (Itr->ActorHasTag("VikingMinion"))
		{
			//minions_list.Add(reinterpret_cast<AVikingMinion*>(Itr->GetActorClass()));			
			//minions_list.Add(Itr);
		}
	}

	
	//UE_LOG(LogTemp, Warning, TEXT("enemy manager called, number is %d"), minion_count);

	//minions_list.Shrink();
	//minion_count = minions_list.Max();

}


void AEnemyManager_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("enemy is not dead\n"));  //,*minions_list[i]->GetName()); 
	delta_local += DeltaTime;


	
	//UE_LOG(LogTemp, Warning, TEXT("enemy is not dead %d"), minions_list.Max());  //,*minions_list[i]->GetName()); 
	//if (delta_local >= 2)
	//{
	//	for (size_t i = 0; i < minions_list.Max(); i++)
	//	{
	//		if (minions_list[i] != nullptr)
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("enemy is not dead %s"), *minions_list[i]->GetName());
	//			//UE_LOG(LogTemp, Warning, TEXT("enemy is not dead %s"), *minions_list[i]->GetName());			
	//		}
	//		else
	//		{
	//			minions_list.RemoveAt(i, 1, true);
	//			minions_list.Shrink();
	//			minion_count--;
	//		}
	//	}
	//	//minion_count = minions_list.Max();
	//	delta_local = 0;
	//	UE_LOG(LogTemp, Warning, TEXT("enemy is not dead %d"), minion_count);
	//}

	


	
}