#pragma once

#include "IGlassRepartition.hpp"

class RandomRepartition : public IGlassRepartition
{
public:
   virtual void execute_repartition() override;
};

