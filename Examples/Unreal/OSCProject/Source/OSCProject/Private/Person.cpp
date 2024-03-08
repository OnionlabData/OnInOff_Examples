// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Components/SphereComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
// Sets default values
APerson::APerson()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
	
}
void APerson::UpdateXYZ(FVector FLC)
{
	SetActorLocation(FLC);
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &APerson::DestroyPerson, NoMsgOSC, false);
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
bool APerson::IsNotUsed(int Id)
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
// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

