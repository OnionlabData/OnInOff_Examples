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
	// Sets default values for this actor's properties
	APerson();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
		void UpdateXYZ(FVector FLC);

	UFUNCTION(BlueprintCallable)
		void SetIndex(int Index);

	UFUNCTION(BlueprintCallable)
		bool IsMyIndex(int Id);

	UFUNCTION(BlueprintCallable)
		bool IsNotUsed(int Id);

	UFUNCTION()
		void DestroyPerson();

	UFUNCTION()
		void DestroyThis();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:

	int MyIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool NotUsed;
	FTimerHandle FuzeTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NoMsgOSC = 0.5f;
};
