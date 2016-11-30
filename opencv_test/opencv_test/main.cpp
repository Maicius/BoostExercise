#include "InitPlayAVI.hpp"
#include "InitPicture.hpp"
#include "simpleChange.hpp"
#include "doCanny.hpp"
#include "readCamera.hpp"
#include "readCameraInformation.hpp"
#include "initPixelSegment.hpp"
#include "createDemarcate.hpp"
int main(int argc, char **argv)
{
	//initPlayAVI();
	//initPicture();
	//simpleChange();
	//initCanny();
	//readCamera(argc, argv);
	readCameraInformation();
	//initPiexelSegment();
	//createDemarcate();
	getchar();
	return 0;
}