// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicLoadContentFromPath.h"

TArray<UObject*>DynamicLoadContentFromPath(FString PathFromContentFolder /*= "Images"*/, UClass* AssetClass, bool LoadFromSubfolders)
{
	TArray<UObject*> Array;
	FString RootFolderFullPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()) + "Content/" + PathFromContentFolder + "/";
    FPaths::NormalizeDirectoryName(RootFolderFullPath);


	IFileManager& FileManager = IFileManager::Get();

	TArray<FString> Files;

	FString Ext;

	if (LoadFromSubfolders)
	{
		if (!Ext.Contains(TEXT("*")))
		{
			if (Ext == "")
			{
				Ext = "*.*";
			}
			else
			{
				Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
			}
		}

		FileManager.FindFilesRecursive(Files, *RootFolderFullPath, *Ext, true, false);
	}
	else
	{
		if (!Ext.Contains(TEXT("*")))
		{
			if (Ext == "")
			{
				Ext = "*.*";
			}
			else
			{
				Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
			}
		}

		FileManager.FindFiles(Files, *(RootFolderFullPath + Ext), true, false);
	}

	for (int32 i = 0; i < Files.Num(); i++)
	{
		FString Path;
		if (LoadFromSubfolders)
		{
			int32 LastForwardSlash = Files[i].Find("/", ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			FString File = Files[i].RightChop(LastForwardSlash + 1);
			FString Folder = Files[i].RightChop(Files[i].Find(PathFromContentFolder, ESearchCase::CaseSensitive, ESearchDir::FromEnd) + PathFromContentFolder.Len());
			Folder = Folder.LeftChop(File.Len() + 1);
			File = File.Left(File.Find(".", ESearchCase::IgnoreCase, ESearchDir::FromEnd));
			Path = AssetClass->GetFName().ToString() + "'/Game/" + PathFromContentFolder + Folder + "/" + File + "." + File + "'";
		}
		else
		{
			Path = AssetClass->GetFName().ToString() + "'/Game/" + PathFromContentFolder + "/" + Files[i].LeftChop(7) + "." + Files[i].LeftChop(7) + "'";
		}
		UObject* LoadedObj = StaticLoadObject(AssetClass, NULL, *Path);

		Array.Add(LoadedObj);
	}

	
	return Array;
}

