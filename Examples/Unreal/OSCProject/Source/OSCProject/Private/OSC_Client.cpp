// Fill out your copyright notice in the Description page of Project Settings.


#include "OSC_Client.h"
#include "Person.h"
#include <map>
#include <iostream>
#include "GameFramework/Actor.h"
// Sets default values
AOSC_Client::AOSC_Client()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOSC_Client::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &AOSC_Client::DestroyPerson, NoMsgOSC, true);
}

void AOSC_Client::OSCMsgReceived(int index, float x, float y, float height, float size)
{	

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AOSC_Client::DestroyPerson, NoMsgOSC, true);
	float CoordX = x;	
	float CoordY = y;	
	float CoordZ = 0;	
	const FRotator Rot = GetActorRotation();	
	float MapCoordX = Map(CoordX, 0, 1, _TopLeftCorner.X, _BottomRightCorner.X);	
	MapCoordX *= -1;	
	float MapCoordY = Map(CoordY, 0, 1, _TopLeftCorner.Y, _BottomRightCorner.Y);	
	FVector FLC = FVector(MapCoordX,MapCoordY, CoordZ);
		if(Person_Map.Find(index))
		{
			YourPersonArray[index]->UpdateXYZ(FLC);				
		}
		else
		{
			APerson* YourPerson;
			YourPerson = GetWorld()->SpawnActor<APerson>(ActorToSpawn, FLC, Rot);
			YourPerson->SetIndex(index);
			YourPersonArray.Add(YourPerson);
			Person_Map.Add(index,YourPerson);
		}
}

void AOSC_Client::DestroyPerson()
{
	for (int i = YourPersonArray.Num()-1; i>=0; i--)
	{	
		if (false == YourPersonArray[i]->Used(i))
		{			
			Person_Map.Remove(i);
			YourPersonArray[i]->DestroyThis();
			YourPersonArray.RemoveAt(i);
		}		
	}
}

float AOSC_Client::Map(float value, float LeftMin, float LeftMax, float RightMin, float RightMax)
{	
	if (LeftMax - LeftMin == 0)
	{
	return 0;		
	}	
	float valuee = RightMin + (value - LeftMin) * (RightMax - RightMin) / (LeftMax - LeftMin);	
	return  valuee;
}

void AOSC_Client::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

