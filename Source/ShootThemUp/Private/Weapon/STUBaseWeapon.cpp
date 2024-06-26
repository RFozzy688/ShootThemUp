// Shoot Them Up Game. All Rights Reserved


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    
    check(WeaponMesh);
}

void ASTUBaseWeapon::StartFire() {}

void ASTUBaseWeapon::StopFire() {}

void ASTUBaseWeapon::MakeShot() {}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

bool ASTUBaseWeapon::CheckShootingAngle(FVector ImpactPoint)
{
    FVector MuzzleWorldLocation = GetMuzzleWorldLocation();
    const auto Player = Cast<ACharacter>(GetOwner());
    FVector WeaponSocketWorldLocation = Player->GetMesh()->GetSocketLocation("WeaponSocket");

    FVector VectorA = WeaponSocketWorldLocation - MuzzleWorldLocation;
    FVector VectorB = MuzzleWorldLocation - ImpactPoint;
    FVector VectorC = WeaponSocketWorldLocation - ImpactPoint;

    //DrawDebugLine(GetWorld(), WeaponSocketWorldLocation, MuzzleWorldLocation, FColor::Red, true, 3.f, 0, 1.f);
    //DrawDebugLine(GetWorld(), MuzzleWorldLocation, ImpactPoint, FColor::Red, true, 3.f, 0, 1.f);
    //DrawDebugLine(GetWorld(), WeaponSocketWorldLocation, ImpactPoint, FColor::Red, true, 3.f, 0, 1.f);

    float A = VectorA.Size();
    float B = VectorB.Size();
    float C = VectorC.Size();

    float AngleBetween = FMath::Acos((A * A + B * B - C * C) / (2 * A * B));
    float Degrees = FMath::RadiansToDegrees(AngleBetween);

    if (Degrees >= 100.f) return true;

    return false;
}
