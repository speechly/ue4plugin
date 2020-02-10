// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class Speechly : ModuleRules
{
    public Speechly(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
        PublicDefinitions.Add("GPR_FORBID_UNREACHABLE_CODE");
        PublicDefinitions.Add("GRPC_ALLOW_EXCEPTIONS=0");
        PublicDefinitions.Add("GOOGLE_PROTOBUF_USE_UNALIGNED=0");
        PublicDefinitions.Add("__NVCC__");

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //PCHUsage = ModuleRules.PCHUsageMode.NoSharedPCHs;
        //PrivatePCHHeaderFile = "Public/Speechly.h";

        string PluginPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
        string IncludePath = Path.GetFullPath(Path.Combine(PluginPath, "GrpcIncludes"));

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(IncludePath, "include"),
                Path.Combine(IncludePath, "third_party", "protobuf", "src")
            }
            );

        string[] GrpcLibraries = Directory.GetFiles(Path.Combine(PluginPath, "GrpcLibraries", Target.Platform.ToString()));
        PublicAdditionalLibraries.AddRange(GrpcLibraries);

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Projects",
                "Engine",
                "AudioCapture",
                "AudioCaptureCore"
            }
            );

        AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
        AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
        
        string EngineCertFile = Path.Combine(EngineDirectory, "Content", "Certificates", "ThirdParty", "cacert.pem");
        if (!File.Exists(EngineCertFile))
        {
            throw new Exception("Requires a cacert.pem file to build");
        }
        RuntimeDependencies.Add(EngineCertFile, StagedFileType.NonUFS);
    }
}
