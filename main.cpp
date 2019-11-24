#include "installmainwindow.h"
#include "myapplication.h"
#include "iostream"
#include <exception>

int main(int argc, char *argv[])
{
        int ret;
        try {
    MyApplication a(argc, argv);
    InstallMainWindow w;
    w.show();




            ret =  a.exec();
}
catch(const std::exception &E) {
    // send error message
    std::cout << "std::exception caught: \"" << E.what() << "\" in file "<< __FILE__ << " at line " << __LINE__ << std::endl;
    // exit with error code
    return ret;

}
catch(...) {
    std::cout << "Internal Software Error: Unknown Exception caught";
    // exit with error code
    return ret;
}
}
