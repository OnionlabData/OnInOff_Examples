// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Components/SphereComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
APerson::APerson()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);	
}
void APerson::BeginPlay()
{
	Super::BeginPlay();
}
void APerson::UpdateXYZ(FVector FLC)
{
	SetActorLocation(FLC);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &APerson::DestroyPerson, NoMsgOSC, false);
}

void APerson::SetIndex(int index)
{	
	MyIndex = index;
	NotUsed = true;
}
bool APerson::IsMyIndex(int Index)
{
	return MyIndex == Index;
}
bool APerson::Used(int Id)
{
	return NotUsed;
}
void APerson::DestroyPerson()
{
	NotUsed = false;
}
void APerson::DestroyThis()
{
	Destroy();	
}
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

