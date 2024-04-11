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
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
		UStaticMeshComponent* Mesh;
	UFUNCTION()
		void UpdateXYZ(FVector FLC);
	UFUNCTION()
		void SetIndex(int Index);
	UFUNCTION()
		bool IsMyIndex(int Id);
	UFUNCTION()
		bool Used(int Id);
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
	UPROPERTY()
	bool NotUsed;
	FTimerHandle Timer;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Units = "Seconds"))
		float NoMsgOSC = 0.5f;
};
