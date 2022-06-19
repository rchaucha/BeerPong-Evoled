#include "BPUApp.hpp"

int main(int argc, char* argv[])
{
   BPUApp qt_application(argc, argv);
   qt_application.init();

   return qt_application.exec();
}