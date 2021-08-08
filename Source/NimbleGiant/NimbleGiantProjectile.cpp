// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimbleGiantProjectile.h"
#include "NimbleGiant/Block.h"
#include "NimbleGiant/NimbleGiantGameMode.h"
#include "NimbleGiant/NimbleGiantCharacter.h"
#include "NimbleGiant/PS_NimbleGiant.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ANimbleGiantProjectile::ANimbleGiantProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ANimbleGiantProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ANimbleGiantProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority()) {
		if (ABlock* Block = Cast<ABlock>(OtherActor)) {

			if (ANimbleGiantGameMode* GameMode = GetWorld()->GetAuthGameMode<ANimbleGiantGameMode>()) 
			{
				if (ANimbleGiantCharacter* Player = Cast<ANimbleGiantCharacter>(GetOwner()))
				{
					GameMode->CubeHit(Block, Player);
				}
			}
		}
	}
	Destroy();
}