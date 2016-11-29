#include "InitPlayAVI.hpp"
#include "InitPicture.hpp"
#include "simpleChange.hpp"
#include "doCanny.hpp"
#include "readCamera.hpp"
#include "readCameraInformation.hpp"
int main(int argc, char **argv)
{
	//initPlayAVI();
	//initPicture();
	//simpleChange();
	initCanny();
	//readCamera(argc, argv);
	//readCameraInformation();
	getchar();
	return 0;
}