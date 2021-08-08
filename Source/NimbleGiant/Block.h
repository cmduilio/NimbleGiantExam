// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class NIMBLEGIANT_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	UPROPERTY(ReplicatedUsing = UpdateColor)
	int32 ColorIndex = 0;
	
	UPROPERTY()
	TMap<int32, UMaterial*> Colors;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionNeighbors;

	UFUNCTION()
	void UpdateColor();

	UFUNCTION(Server, Reliable)
	void SelectColor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int32 GetColorIndex();

	void GetNeighbors(TSet<AActor*>* Hits);

};
