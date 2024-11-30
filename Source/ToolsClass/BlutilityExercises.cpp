// Fill out your copyright notice in the Description page of Project Settings.


#include "BlutilityExercises.h"
#include "FileHelpers.h"
#include "Exporters/Exporter.h"
#include "AssetExportTask.h"
#include <Misc/OutputDeviceNull.h>
#include "Engine/StaticMeshActor.h"
#include "AssetToolsModule.h"
#include <AssetRegistry/AssetRegistryModule.h>
#include <IAssetTools.h>

void UBlutilityExercises::Exercise1()
{
    //FString contentDir = FPaths::ProjectContentDir();

    //FString exportDir = contentDir + "Export/";
    //FString pathToFind = contentDir + "StarterContent/Textures";

    //TArray<FString> allowedExtensions;
    //allowedExtensions.Add(TEXT("uasset"));
    //allowedExtensions.Add(TEXT("png"));
    //allowedExtensions.Add(TEXT("jpg"));
    //allowedExtensions.Add(TEXT("wav"));
    //allowedExtensions.Add(TEXT("mp3"));
    //allowedExtensions.Add(TEXT("fbx"));
    //allowedExtensions.Add(TEXT("obj"));

    //ExportFolderByExtension(pathToFind, allowedExtensions, exportDir);

    Exercise2();
}

void UBlutilityExercises::Exercise2()
{
    FString contentDir = FPaths::ProjectContentDir();

    FString exportDir = contentDir + "Export/";
    FString pathToFind = "/Game/Characters/Mannequin_UE4/Meshes/";

    ExportStaticMeshes(pathToFind, exportDir, 20);
}

void UBlutilityExercises::ExportFolderByExtension(FString _directory, TArray<FString> _extensions, FString _exportDir)
{
	IFileManager& fileManager = IFileManager::Get();

    if (!fileManager.DirectoryExists(*_directory))
    {
        UE_LOG(LogTemp, Warning, TEXT("Directory not found"), *_directory);
        return;
    }

    TArray<FString> foundFiles;

    for (const FString& extension : _extensions)
    {
        FString pattern = _directory + "/*." + extension;
        fileManager.FindFiles(foundFiles, *pattern, true, false);
    }

    for (const FString& fileName : foundFiles)
    {
        FString fullFile = _directory + "/" + fileName;
        FString newFilePath = FPaths::Combine(_exportDir, fileName);

        if (fileManager.Copy(*newFilePath, *fullFile) == 0)
        {
            UE_LOG(LogTemp, Log, TEXT("File Exported: %s"), *newFilePath);
        }
        else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Error finding the file: %s"), *newFilePath);
        }
    }


}

void UBlutilityExercises::ExportStaticMeshes(FString _directory, FString _exportDir, int _minPolygonNumber)
{
    FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    assetRegistryModule.Get().SearchAllAssets(true);

    FARFilter filter;
    filter.PackagePaths.Add(FName(*_directory));
    filter.bRecursivePaths = true;

    TArray<FAssetData> assetDataList;
    assetRegistryModule.Get().GetAssets(filter, assetDataList);

    for (const FAssetData& assetData : assetDataList)
    {
        UStaticMesh* staticMesh = Cast<UStaticMesh>(assetData.GetAsset());

        if (staticMesh)
        {
            int32 numTriangles = staticMesh->GetNumTriangles(0);

            if (numTriangles >= _minPolygonNumber)
            {
                FString filePath = assetData.ObjectPath.ToString();
                FString exportFilePath = _exportDir + staticMesh->GetName() + TEXT(".fbx");

                IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

                TArray<UObject*> AssetsToExport;
                AssetsToExport.Add(staticMesh);

                AssetTools.ExportAssets(AssetsToExport, exportFilePath);

                if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*exportFilePath))
                {
                    UE_LOG(LogTemp, Log, TEXT("File Exported: %s"), *exportFilePath);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to export the file: %s"), *exportFilePath);
                }
            }
        }
    }
}

