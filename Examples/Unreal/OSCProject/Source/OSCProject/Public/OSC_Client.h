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
	
	UFUNCTION(BlueprintCallable)
		float Map(float value, float LeftMin, float LeftMax, float RightMin, float RightMax);
	UPROPERTY(EditAnywhere, Category = "Spawn Character")
		TSubclassOf<AActor>ActorToSpawn;
	UPROPERTY(EditAnyWhere, Category = "TopLeftCorner")
		FVector2D _TopLeftCorner;
	UPROPERTY(EditAnyWhere, Category = "BottomRightCorner")
		FVector2D _BottomRightCorner;
public:
	TArray<APerson*> YourPersonArray;

	UPROPERTY(Category = Maps, EditAnywhere)
		TMap<int, APerson*> Person_Map;
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	FTimerHandle Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(Units="Seconds"))
		float NoMsgOSC = 0.2f;
};
