// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "BlutilityExercises.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSCLASS_API UBlutilityExercises : public UAssetActionUtility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(CallInEditor, Category = "Editor Scripting_1")
	void Exercise1();

	UFUNCTION(CallInEditor, Category = "Editor Scripting_2")
	void Exercise2();

	void ExportFolderByExtension(FString _directory, TArray<FString> _extensions, FString _exportDir);
	void ExportStaticMeshes(FString _directory, FString _exportDir, int _minPoligonNumber);
};
