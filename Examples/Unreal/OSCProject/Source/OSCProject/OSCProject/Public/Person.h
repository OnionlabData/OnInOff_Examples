// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Person.generated.h"

UCLASS()
class OSCPROJECT_API APerson : public AActor
{
	GENERATED_BODY()
	
public:	
	APerson();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UFUNCTION()
		void UpdateXYZ(FVector FLC);

	UFUNCTION()
		void SetIndex(int Index);

	UFUNCTION()
		bool IsMyIndex(int Id);

	UFUNCTION()
		bool Used();

	UFUNCTION()
		void DestroyPerson();

	UFUNCTION()
		void DestroyThis();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
private:

	int MyIndex = 0;
	bool Exist;
	FTimerHandle Timer;
	float NoMsgOSC = 0.5f;
};
