// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPToolTest.h"

// Sets default values
ACPPToolTest::ACPPToolTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Body->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACPPToolTest::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPPToolTest::OnConstruction(const FTransform& _transform)
{
	Super::OnConstruction(_transform);

	if (ComponentList.Num() >= NumberOfElements)
		return;

	for (auto* Comp : ComponentList) 
	{
		Comp->UnregisterComponent();
		Comp->MarkAsGarbage();
	}

	ComponentList.Empty();

	for (int32 i = 0; i < NumberOfElements; i++) 
	{
		UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this);

		NewComp->SetupAttachment(Body);
		NewComp->RegisterComponent();

		if(Visualizer)
			NewComp->SetStaticMesh(Visualizer);

		ComponentList.Add(NewComp);
	}
}

void ACPPToolTest::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = PropertyChangedEvent.GetPropertyName();

	if (PropertyName.IsEqual(GET_MEMBER_NAME_CHECKED(ACPPToolTest, NumberOfElements))) 
	{
		RegenerateComponents();
	}
}

void ACPPToolTest::RegenerateComponents()
{
	if (NumberOfElements != ComponentList.Num())
	{
		for (auto* Comp : ComponentList)
		{
			Comp->UnregisterComponent();
			Comp->MarkAsGarbage();
		}
		ComponentList.Empty();

		for (int32 i = 0; i < NumberOfElements; ++i)
		{
			UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this);
			NewComp->SetupAttachment(Body);
			NewComp->RegisterComponent();

			if (Visualizer)
			{
				NewComp->SetStaticMesh(Visualizer);
			}

			ComponentList.Add(NewComp);
		}
	}
}

void ACPPToolTest::AlignComponents()
{
}

void ACPPToolTest::SetStaticMesh()
{
	ComponentList[0]->SetStaticMesh(Visualizer);
}

// Called every frame
void ACPPToolTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

