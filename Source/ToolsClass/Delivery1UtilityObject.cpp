// Fill out your copyright notice in the Description page of Project Settings.


#include "Delivery1UtilityObject.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "Framework/Application/SlateApplication.h"
#include <AssetRegistry/AssetRegistryModule.h>

void UDelivery1UtilityObject::RunBase()
{
    UE_LOG(LogTemp, Warning, TEXT("Delivery1: StartupModule called!"));
    LogAssetDependencies();
}

void UDelivery1UtilityObject::LogAssetDependencies()
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    AssetRegistryModule.Get().SearchAllAssets(true);

    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    TArray<FAssetData> AssetList;
    AssetRegistry.GetAllAssets(AssetList);

    TMap<FString, TMap<FString, TArray<FName>>> AssetDependencies;

    for (const FAssetData& AssetData : AssetList)
    {
        TArray<FName> Dependencies;
        AssetRegistry.GetDependencies(AssetData.PackageName, Dependencies);

        if (Dependencies.Num() > 0)
        {
            TMap<FString, TArray<FName>> dependencies;
            TArray<FName> subDependencies;

            for (const FName& Dependency : Dependencies)
            {
                subDependencies.Empty();
                AssetRegistry.GetDependencies(Dependency, subDependencies);

                dependencies.Add(Dependency.ToString(), subDependencies);
            }

            AssetDependencies.Add(AssetData.PackageName.ToString(), dependencies);
        }
    }

    FString OutputLog;
    for (const auto& Pair : AssetDependencies)
    {
        OutputLog += FString::Printf(TEXT("AssetRoot [%s]\n"), *Pair.Key);
        for (const auto& Dependency : Pair.Value)
        {
            OutputLog += FString::Printf(TEXT("|- %s\n"), *Dependency.Key);

            for (const auto& SubDependency : Dependency.Value)
            {
                OutputLog += FString::Printf(TEXT("  |- %s\n"), *SubDependency.ToString());
            }

        }
        OutputLog += TEXT("\n");
    }

    FString logPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Logs"));
    FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*logPath);
    FString logFileName = FString::Printf(TEXT("RefLogOutput_%s.log"), *FDateTime::Now().ToString(TEXT("%Y%m%d")));
    FString fullLogPath = FPaths::Combine(logPath, logFileName);

    FFileHelper::SaveStringToFile(OutputLog, *fullLogPath);
    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Asset Dependency Log exported correctly!")));
}

