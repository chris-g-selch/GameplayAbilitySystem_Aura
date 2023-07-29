// its me mario


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

//Required Post Processing Volume
//Post Processing Highlight material
//For this to work

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	if(USkeletalMeshComponent* cachedMesh = GetMesh())
	{
		cachedMesh->SetRenderCustomDepth(true);
		cachedMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);	
	}

	if(Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
	
}

void AAuraEnemy::UnHighlightActor()
{
	if(USkeletalMeshComponent* cachedMesh = GetMesh())
	{
		cachedMesh->SetRenderCustomDepth(false);
	}

	if(Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}

}
