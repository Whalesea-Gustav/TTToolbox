// The MIT License (MIT)
// ---------------------
// 
// Copyright 2022 Achim Turan (https://www.instagram.com/tuatec/)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
// THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "AnimationModifier.h"
#include "TTCopyAllCurvesAndNotifiesAnimModifier.generated.h"

UCLASS()
class TTTOOLBOX_API UTTCopyAllCurvesAndNotifiesAnimModifier : public UAnimationModifier
{
	GENERATED_BODY()
private: // methods
	void OnApply_Implementation(UAnimSequence* TargetSequence) override;

public: // members
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	UAnimSequence* SourceSequence = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool ReplaceExistingCurves = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
	bool ReplaceExistingNotifies = false;
};
