// Fill out your copyright notice in the Description page of Project Settings.


#include "PyramidGenerator.h"
#include "Block.h"

// Sets default values
APyramidGenerator::APyramidGenerator()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APyramidGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlocks();
}

void APyramidGenerator::SpawnBlocks_Implementation()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		//Using rotation of pyramid
		const FRotator SpawnRotation = GetActorRotation();
		FVector SpawnLocation = GetActorLocation();

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = this;

		for(int Row = 0; Row < Size; Row++)
		{
			FVector origin;
			FVector boxExtent;
			FVector Right;
			FVector Up;
			for (int Col = 0; Col < Size-Row; Col++)
			{
				ABlock* Block = World->SpawnActor<ABlock>(BlockClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

				boxExtent = Block->StaticMeshComponent->GetStaticMesh()->GetBounds().BoxExtent;

				//Using rightvector to adjust rotation of pyramid generator
				Right = Block->GetActorRightVector();
				Up = Block->GetActorUpVector();
				//Multiplying by 2 because bounds is distance from center, +10 es distance between each block
				SpawnLocation = Block->GetActorLocation() + (Right * ((boxExtent.Y * 2) + 10));
			}
			//going in the 
			SpawnLocation += Up * (boxExtent.Z * 2);

			//the offset represent how much do i have to "go back" in the next line, the Size-Row is how many cubes i have in this row the -1 changes the direction so i go back
			float offset = (-1 * (Size - Row) * ((boxExtent.Y * 2) + 10)) + (boxExtent.Y);
			SpawnLocation += (Right * offset);
		}

	}
}
