// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    ASTUBaseWeapon();

    virtual void StartFire();
    virtual void StopFire();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName MuzzleSocketName = "MuzzleFlashSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float TraceMaxDistance = 1500.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float DamageAmount = 10.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float BulletSpred = 1.5f;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    bool CheckShootingAngle(FVector ImpactPoint);
    void MakeDamage(const FHitResult& HitResult);

    void MakeShot();

private:
    FTimerHandle ShotTimerHandle;
};
