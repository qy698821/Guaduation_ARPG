// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Guaduation_ARPGTarget : TargetRules
{
	public Guaduation_ARPGTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Guaduation_ARPG" } );
	}
}
