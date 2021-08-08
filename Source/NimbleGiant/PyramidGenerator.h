#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PyramidGenerator.generated.h"

UCLASS()
class NIMBLEGIANT_API APyramidGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APyramidGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION(Server, Reliable)
	void SpawnBlocks();

public:	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABlock>  BlockClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size;

};
