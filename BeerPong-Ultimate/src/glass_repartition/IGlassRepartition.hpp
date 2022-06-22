#pragma once

/* Based on Strategy and Composite desing patterns */

class IGlassRepartition
{
public:
   virtual ~IGlassRepartition() {}

   virtual void execute_repartition() = 0;
};

