#include "Block.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/BoxComponent.h"

// Sets default values
ABlock::ABlock()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	CollisionNeighbors = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionNeighbors"));
	CollisionNeighbors->SetupAttachment(StaticMeshComponent);

	RootComponent = StaticMeshComponent;

	ConstructorHelpers::FObjectFinder<UMaterial> Red(TEXT("Material'/Game/FirstPersonCPP/Materials/M_Red.M_Red'"));
	ConstructorHelpers::FObjectFinder<UMaterial> Green(TEXT("Material'/Game/FirstPersonCPP/Materials/M_Green.M_Green'"));
	ConstructorHelpers::FObjectFinder<UMaterial> Blue(TEXT("Material'/Game/FirstPersonCPP/Materials/M_Blue.M_Blue'"));

	Colors.Add(0, Red.Object);
	Colors.Add(1, Green.Object);
	Colors.Add(2, Blue.Object);

}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
	SelectColor();
}

int32 ABlock::GetColorIndex()
{
	return ColorIndex;
}

/*
	This is the Balancer method, the idea here is to don't have more than 3 blocks of the same color at spawn time.
	This does not mean that every cube can only have 2 neighbors of the same color in the final product just at spawn time.
	Pyramid is made from bottom up and left to right. In case there are 3 of the same random color, just pick the next one.
	if for some reason i can't put any color (since there are 3 colors and 6 neighbors it can happen) i just pick 
	the original random color.
*/
void ABlock::SelectColor_Implementation()
{
	int Count = 0;
	bool Found = false;

	int32 Random = FMath::RandRange(0, 2);

	while (!Found && Count < 3) {


		if (Colors.Find(Random))
		{
			TSet<AActor*> Neighbors;
			GetNeighbors(&Neighbors);
			int ColorCount = 0;
			for (AActor* Neighbor : Neighbors) {
				if (ABlock* NeighborBlock = Cast<ABlock>(Neighbor))
				{
					if (NeighborBlock->GetColorIndex() == Random)
					{
						ColorCount++;
					}
				}
			}

			if (ColorCount < 3) {
				ColorIndex = Random;
				UpdateColor();
				Found = true;
			}
			else
			{
				Random = (Random + 1) % 3;
			}

		}
		Count++;
	}

}

void ABlock::UpdateColor()
{
	StaticMeshComponent->SetMaterial(0, *(Colors.Find(ColorIndex)));
}

void ABlock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABlock, ColorIndex);
}

void ABlock::GetNeighbors(TSet<AActor*>* Hits) {
	CollisionNeighbors->GetOverlappingActors(*Hits);
}