#pragma once

#include "CoreMinimal.h"
#include <memory>
#include <vector>
#include "VehicleConnectorBase.h"
#include "physics/FastPhysicsEngine.hpp"
#include "physics/World.hpp"
#include "common/StateReporterWrapper.hpp"
#include "api/ControlServerBase.hpp"
#include "SimModeBase.h"
#include "SimModeWorldBase.generated.h"



UCLASS()
class AIRSIM_API ASimModeWorldBase : public ASimModeBase
{
    GENERATED_BODY()
    
public:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick( float DeltaSeconds ) override;


    virtual void reset() override;
    virtual std::string getReport() override;
    virtual void setupInputBindings() override;

protected:
    typedef std::shared_ptr<VehicleConnectorBase> VehiclePtr;
    virtual void createVehicles(std::vector<VehiclePtr>& vehicles);
    size_t getVehicleCount() const;

    static const char kUsageScenarioComputerVision[];
    UPROPERTY() UManualPoseController* manual_pose_controller;

private:
    void createWorld();

private:
    msr::airlib::World world_;
    std::unique_ptr<msr::airlib::PhysicsEngineBase> physics_engine_;

    std::vector<VehiclePtr> vehicles_;
    msr::airlib::StateReporterWrapper reporter_;
};
