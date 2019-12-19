// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Guaduation_ARPGEditorTarget : TargetRules
{
	public Guaduation_ARPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Guaduation_ARPG" } );
	}
}
