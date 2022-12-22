// Fill out your copyright notice in the Description page of Project Settings.
#include "JSONParser.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

FDataStructList UJSONParser::createObjectsFromJSON(FString JsonFilePath)
{
	//converts JSON to string
	FString stringJSON; 
	FFileHelper::LoadFileToString(stringJSON, *JsonFilePath);

	TSharedPtr<FJsonObject> objectJSON = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> readerJSON = TJsonReaderFactory<>::Create(stringJSON);

	if (FJsonSerializer::Deserialize(readerJSON, objectJSON) && objectJSON.IsValid())
	{
		FDataStructList dataStructList;
		FJsonObjectConverter::JsonObjectStringToUStruct<FDataStructList>(stringJSON, &dataStructList, 0, 0);

		return dataStructList;
	}

	return FDataStructList();
}

void UJSONParser::createJSONFromObjects(TArray<AActor*> cubeList, TArray<AActor*> planeList, TArray<AActor*> sphereList, TArray<AActor*> capsuleList)
{
	FDataStructList dataStructList;
	FDataStruct dataStruct;

#pragma region cubeDataStruct
	//Translating cubes from our engine into Unreal
	TArray<FDataStruct> cubeDataStruct;

	for (auto object : cubeList)
	{
		dataStruct.name = object->GetActorLabel();

		dataStruct.position.x = object->GetActorLocation().X / 10.0f;
		dataStruct.position.y = object->GetActorLocation().Z / 10.0f;
		dataStruct.position.z = object->GetActorLocation().Y / 10.0f;

		dataStruct.rotation.x = object->GetActorRotation().Roll;
		dataStruct.rotation.y = object->GetActorRotation().Yaw;
		dataStruct.rotation.z = object->GetActorRotation().Pitch;

		dataStruct.scale.x = object->GetActorScale3D().X * 5.0f;
		dataStruct.scale.y = object->GetActorScale3D().Z * 5.0f;
		dataStruct.scale.z = object->GetActorScale3D().Y * 5.0f;

		cubeDataStruct.Add(dataStruct);
	}

	dataStructList.cubeStructList = cubeDataStruct;
#pragma endregion

#pragma region planeDataStruct
	//Translating planes from our engine into Unreal
	TArray<FDataStruct> planeDataStruct;

	for (auto object : planeList)
	{
		dataStruct.name = object->GetActorLabel();

		dataStruct.position.x = object->GetActorLocation().X / 100.0f;
		dataStruct.position.y = object->GetActorLocation().Z / 100.0f;
		dataStruct.position.z = object->GetActorLocation().Y / 100.0f;

		dataStruct.rotation.x = object->GetActorRotation().Roll;
		dataStruct.rotation.y = object->GetActorRotation().Yaw;
		dataStruct.rotation.z = object->GetActorRotation().Pitch;

		dataStruct.scale.x = object->GetActorScale3D().X;
		dataStruct.scale.y = object->GetActorScale3D().Z;
		dataStruct.scale.z = object->GetActorScale3D().Y;

		planeDataStruct.Add(dataStruct);
	}

	dataStructList.planeStructList = planeDataStruct;
#pragma endregion

#pragma region sphereDataStruct
	//Translating spheres from our engine into Unreal
	TArray<FDataStruct> sphereDataStruct;

	for (auto object : sphereList)
	{
		dataStruct.name = object->GetActorLabel();

		dataStruct.position.x = object->GetActorLocation().X / 100.0f;
		dataStruct.position.y = object->GetActorLocation().Z / 100.0f;
		dataStruct.position.z = object->GetActorLocation().Y / 100.0f;

		dataStruct.rotation.x = object->GetActorRotation().Roll;
		dataStruct.rotation.y = object->GetActorRotation().Yaw;
		dataStruct.rotation.z = object->GetActorRotation().Pitch;

		dataStruct.scale.x = object->GetActorScale3D().X;
		dataStruct.scale.y = object->GetActorScale3D().Z;
		dataStruct.scale.z = object->GetActorScale3D().Y;

		sphereDataStruct.Add(dataStruct);
	}

	dataStructList.sphereStructList= sphereDataStruct;
#pragma endregion

#pragma region capsuleDataStruct
	//Translating capsules from our engine into Unreal
	TArray<FDataStruct> capsuleDataStruct;

	for (auto object : capsuleList)
	{
		dataStruct.name = object->GetActorLabel();

		dataStruct.position.x = object->GetActorLocation().X / 100.0f;
		dataStruct.position.y = object->GetActorLocation().Z / 5.0f;
		dataStruct.position.z = object->GetActorLocation().Y / 5.0f;

		dataStruct.rotation.x = object->GetActorRotation().Roll - 90.0f;
		dataStruct.rotation.y = object->GetActorRotation().Yaw;
		dataStruct.rotation.z = object->GetActorRotation().Pitch;

		dataStruct.scale.x = object->GetActorScale3D().X / 5.0f;
		dataStruct.scale.y = object->GetActorScale3D().Z / 5.0f;
		dataStruct.scale.z = object->GetActorScale3D().Y / 5.0f;

		capsuleDataStruct.Add(dataStruct);
	}

	dataStructList.capsuleStructList = capsuleDataStruct;
#pragma endregion

	FString JSON;

	FJsonObjectConverter::UStructToJsonObjectString(dataStructList, JSON, 0, 0);
	FString saveToFile = "D:/Apps/Github/GDENG2_Unreal/Content/Sample.level";
	FFileHelper::SaveStringToFile(JSON, *saveToFile);
}