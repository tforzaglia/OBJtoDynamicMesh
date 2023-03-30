// Fill out your copyright notice in the Description page of Project Settings.


#include "ImportedDynamicMesh.h"
#include "DynamicMeshOBJReader.h"
#include "DynamicMesh/MeshAttributeUtil.h"
#include "DynamicMesh/MeshNormals.h"

// Sets default values
AImportedDynamicMesh::AImportedDynamicMesh()
{
	DynamicMeshComponent = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("DynamicMesh"));
	RootComponent = DynamicMeshComponent;
}

// Called when the game starts or when spawned
void AImportedDynamicMesh::BeginPlay()
{
	Super::BeginPlay();

	const FString File = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()).Append(TEXT("OBJs/stage6.obj"));
	BuildMesh(File);
}

// Called every frame
void AImportedDynamicMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AImportedDynamicMesh::LoadMeshUpdate()
{
	const FString File = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()).Append(TEXT("OBJs/stage11.obj"));

	BuildMesh(File);
}

void AImportedDynamicMesh::BuildMesh(const FString File)
{
	FDynamicMesh3 BaseMesh;

	FDynamicMeshOBJReader::Read(TCHAR_TO_ANSI(*File), BaseMesh, true, true, true);

	BaseMesh.ReverseOrientation();

	UE_LOG(LogTemp, Display, TEXT("Mesh has %d vertices, %d triangles, %d edges"), BaseMesh.VertexCount(), BaseMesh.TriangleCount(), BaseMesh.EdgeCount());
	UE_LOG(LogTemp, Display, TEXT("Mesh has %d normals"), BaseMesh.Attributes()->PrimaryNormals()->ElementCount());
	UE_LOG(LogTemp, Display, TEXT("Mesh has %d UVs"), BaseMesh.Attributes()->PrimaryUV()->ElementCount());

	CopyVertexUVsToOverlay(BaseMesh, *BaseMesh.Attributes()->PrimaryUV());
	CopyVertexNormalsToOverlay(BaseMesh, *BaseMesh.Attributes()->PrimaryNormals());
	
	FMeshNormals::QuickComputeVertexNormals(BaseMesh);

	SetActorTransform(FTransform(FVector(0, -50, -20 )));
	SetActorRotation(FRotator(0, 0, -90));
	
	DynamicMeshComponent->GetDynamicMesh()->SetMesh(std::move(BaseMesh));

	UMaterialInterface* UseMaterial = UMaterial::GetDefaultMaterial(MD_Surface);
	DynamicMeshComponent->SetMaterial(0, UseMaterial);
}
