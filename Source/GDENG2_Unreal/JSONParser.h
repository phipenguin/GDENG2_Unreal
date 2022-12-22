// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JSONParser.generated.h"

class FJsonObject;

USTRUCT(BlueprintType)
struct FVector3D
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float x;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float y;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float z;
};

USTRUCT(BlueprintType)
struct FDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector3D position;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector3D rotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector3D scale;
};

USTRUCT(BlueprintType)
struct FDataStructList
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FDataStruct> cubeStructList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FDataStruct> planeStructList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FDataStruct> sphereStructList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<FDataStruct> capsuleStructList;
};

UCLASS()
class GDENG2_UNREAL_API UJSONParser : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
	//Writing Files
    UFUNCTION(BlueprintCallable) static FDataStructList createObjectsFromJSON(FString filePath);

	//Reading Files
    UFUNCTION(BlueprintCallable) static void createJSONFromObjects(TArray<AActor*> cubeList, TArray<AActor*> planeList, TArray<AActor*> sphereList, TArray<AActor*> capsuleList);
};