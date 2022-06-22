#pragma once

#include "IGlassRepartition.hpp"

class ManualRepartition : public IGlassRepartition
{
public:
   virtual void execute_repartition() override;
};
