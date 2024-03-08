// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Person.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSC_Client.generated.h"

UCLASS()
class OSCPROJECT_API AOSC_Client : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOSC_Client();

	UFUNCTION(BlueprintCallable)
		void OSCMsgReceived(int index, float x, float y, float height, float size);
	UFUNCTION(BlueprintCallable)
		void DestroyPerson();
	UPROPERTY(EditAnywhere, Category = "Spawn Character")
		TSubclassOf<AActor>ActorToSpawn;

public:
	TArray<APerson*> YourPersonArray;

	UPROPERTY(Category = Maps, EditAnywhere)
		TMap<int, FVector> OSC_Map;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle FuzeTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NoMsgOSC = 0.2f;
};
