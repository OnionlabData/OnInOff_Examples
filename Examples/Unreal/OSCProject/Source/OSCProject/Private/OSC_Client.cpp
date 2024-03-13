// Fill out your copyright notice in the Description page of Project Settings.


#include "OSC_Client.h"
#include "Person.h"
#include <map>
#include <iostream>
#include "GameFramework/Actor.h"
// Sets default values
AOSC_Client::AOSC_Client()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOSC_Client::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AOSC_Client::DestroyPerson, NoMsgOSC, true);
}

void AOSC_Client::OSCMsgReceived(int index, float x, float y, float height, float size) 
{	
	float CoordX = x * 500;
	float CoordY = y * 500;
	float CoordZ = 0;
	const FRotator Rot = GetActorRotation();
	const FVector FLC = FVector(CoordX, CoordY, CoordZ);
	OSC_Map.Add(index, FLC);	
	bool indexExists = false;

	for (int i = 0; i < YourPersonArray.Num() && !indexExists; i++) 
		{
			indexExists = YourPersonArray[i]->IsMyIndex(index);
		}

	if (!indexExists) 
		{
		    APerson* YourPerson;
			YourPerson = GetWorld()->SpawnActor<APerson>(ActorToSpawn, FLC, Rot);  
			YourPerson->SetIndex(index); 
			YourPersonArray.Add(YourPerson);	 
		}
	
	
	for (int i = 0; i < YourPersonArray.Num(); i++)
		{
			if (YourPersonArray[i]->IsMyIndex(index))
			{ 
				YourPersonArray[i]->UpdateXYZ(OSC_Map[index]);
				break;
			}
		}	
	if (false == YourPersonArray[index]->Used())
	{
		DestroyPerson();
	}
}

void AOSC_Client::DestroyPerson() 
{
	for (int i = YourPersonArray.Num()-1; i>=0; i--) 
	{	
		if (false == YourPersonArray[i]->Used()) 
		{
			OSC_Map.Remove(i); 
			YourPersonArray[i]->DestroyThis();
			YourPersonArray.RemoveAt(i); 
		}		
	}
}
// Called every frame
void AOSC_Client::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

