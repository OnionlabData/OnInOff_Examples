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
	AOSC_Client();
	UFUNCTION(BlueprintCallable)
		void OSCMsgReceived(int index, float x, float y, float height, float size);
	UFUNCTION(BlueprintCallable)
		void DestroyPerson();
	UPROPERTY(EditAnywhere, Category = "Spawn Character")
		TSubclassOf<AActor>ActorToSpawn;
	
	TArray<APerson*> YourPersonArray;
	
	UPROPERTY(Category = Maps, EditAnywhere)
		TMap<int, FVector> OSC_Map;

	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	
	FTimerHandle Timer;
	float NoMsgOSC = 0.2f;
};
