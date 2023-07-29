// its me mario


#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	DrawDebugSphere(GetWorld(),GetActorLocation(),50.f,12,FColor::Blue, false, .5f);
}

void AAuraEnemy::UnHighlightActor()
{
	DrawDebugSphere(GetWorld(),GetActorLocation(),12.f,12,FColor::Red,false,.5f);
}
