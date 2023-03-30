// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "GameFramework/Actor.h"
#include "ImportedDynamicMesh.generated.h"

UCLASS()
class DYNAMICMESHTEST_API AImportedDynamicMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImportedDynamicMesh();

	UPROPERTY(BlueprintReadWrite)
	UDynamicMeshComponent* DynamicMeshComponent;

	UFUNCTION(BlueprintCallable)
	void LoadMeshUpdate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void BuildMesh(const FString File);
};
