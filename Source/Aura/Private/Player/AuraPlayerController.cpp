// its me mario


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
    bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
    Super::BeginPlay();

    //Assertion to blow up application
    check(AuraContext);

    //Singleton
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    check(Subsystem);

    Subsystem->AddMappingContext(AuraContext, 0);

    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;

    FInputModeGameAndUI inputModeData;
    inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    inputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(inputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CursorTrace();
    
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2d inputAxisVector = InputActionValue.Get<FVector2d>();
    const FRotator rotation = GetControlRotation();
    const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

    const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
    const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

    if(APawn* controlledPawn = GetPawn<APawn>())
    {
        controlledPawn->AddMovementInput(forwardDirection, inputAxisVector.X);
        controlledPawn->AddMovementInput(rightDirection, inputAxisVector.Y);
    }
}

void AAuraPlayerController::CursorTrace()
{
    FHitResult cursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);
    if(!cursorHit.bBlockingHit) return;
    
    LastActor = ThisActor;
    ThisActor = Cast<IEnemyInterface>(cursorHit.GetActor());

    if(ThisActor == LastActor) return; //Work was done last frame

    if(LastActor)
        LastActor->UnHighlightActor();
    
    if(ThisActor)
        ThisActor->HighlightActor();
    
}
