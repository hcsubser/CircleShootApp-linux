#include "Zuma_Prefix.pch"

#include "CurveData.h"
#include "Board.h"
#include "Bullet.h"
#include "CurveMgr.h"
#include "WayPoint.h"
#include "DataSync.h"

using namespace Sexy;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int gVersion = 3;
float INV_SUBPIXEL_MULT = 0.01f;

CurveData::CurveData()
{
    Clear();
}

bool CurveData::Save(const std::string &theFilePath, bool smallVersion)
{
    // TODO: doesn't seem to be present in any .exe?

    return false;
}

bool CurveData::Load(const std::string &theFilePath)
{
	FILE* file = fopen(theFilePath.c_str(), "rb");

    if (!file){
        mErrorString = "Failed to open file";
		printf("\n(Debug)<CircleShoot/CurveData.cpp> %s %s",__func__,mErrorString.c_str());
        return false;
	}

    fseek(file, 0x10, SEEK_SET);
    int32_t count = 0;
    fread(&count, sizeof(int32_t), 1, file);
    fseek(file, 0x14 + count * 10, SEEK_SET);

    int32_t c;
    float cx;
	float cy;
	//float dx,dy;

    fread(&c, sizeof(int32_t), 1, file);
    fread(&cx, sizeof(float), 1, file);
    fread(&cy, sizeof(float), 1, file);


    //level->spiral2Start.x = cx;
    //level->spiral2Start.y = cy;
    mPointList.push_back(PathPoint());
    PathPoint &aStartPoint = mPointList.back();

    aStartPoint.x = cx;
    aStartPoint.y = cy;
    //aStartPoint.mInTunnel = t1;//doesnt matter here on first point?
    //aStartPoint.mPriority = t2;
    printf("\n(Debug)<CircleShoot/CurveData.cpp>, spiral_start %lf, %lf, %d",cx, cy, c-1);
	fflush(stdout);

    int spiralLen = c-1;
    //level->spiral2 = malloc(sizeof(SpiralDot) * level->spiral2Len);
	//mPointList.push_back(PathPoint());
    // i;
    for (long i = 0; i < spiralLen; i++) {
		//if(i<40)
		//printf("\n here %d %i", spiralLen, i); fflush(stdout);
        char t1, t2, x, y;
        fread(&t1, 1, 1, file);
        fread(&t2, 1, 1, file);
        fread(&x, 1, 1, file);
        fread(&y, 1, 1, file);

        /*level->spiral2[i].t1 = t1;
        level->spiral2[i].t2 = t2;
        level->spiral2[i].dx = (float)x / 100.0;
        level->spiral2[i].dy = (float)y / 100.0;*/
		//PathPoint &aPrevPoint = mPointList.back();
        mPointList.push_back(PathPoint());
		PathPoint &aPoint = mPointList.back();

        //signed char dx = aReader.ReadByte();
        //signed char dy = aReader.ReadByte();

        aPoint.x = mPointList[i].x+(float)x / 100.0;// / 100.0 * INV_SUBPIXEL_MULT + cx;
        aPoint.y = mPointList[i].y+(float)y / 100.0;// / 100.0 * INV_SUBPIXEL_MULT + cy;
        aPoint.mInTunnel = t1;
        aPoint.mPriority = t2;
		//if(i<40)
    	//	printf("(Debug) raw bytes: x=%lf y=%lf t1=%d t2=%d %d %d\n",aPoint.x, aPoint.y, (int)x, (int)y,t1,t2);
		//	fflush(stdout);
    }

    fclose(file);
    return true;
}
//original curve loading code by alula
//did not work for me for some reason
/*bool CurveData::Load(const std::string &theFilePath)
{
    Clear();

    DataReader aReader;
    if (!aReader.OpenFile(theFilePath))
    {
        mErrorString = "Failed to open file";
		printf("\n(Debug)<CircleShoot/CurveData.cpp> %s %s",__func__,mErrorString.c_str());
		fflush(stdout);
        return false;
    }

    char aBuf[5];
    aBuf[3] = 0;
    aBuf[4] = 0;

    aReader.ReadBytes(aBuf, 4);
    if (strcmp(aBuf, "CURV") != 0)
    {
        mErrorString = "Invalid file header";
		printf("\n(Debug)<CircleShoot/CurveData.cpp> %s %s",__func__,mErrorString.c_str());
		fflush(stdout);
        return false;
    }

    mVersion = aReader.ReadLong();
    if (mVersion < 1 || mVersion > gVersion)
    {
        mErrorString = "Invalid file version";
		printf("\n(Debug)<CircleShoot/CurveData.cpp> %s %s",__func__,mErrorString.c_str());
		fflush(stdout);
        return false;
    }

    bool smallVersion;
    bool hasTunnels;

    if (mVersion <= 2)
    {
        smallVersion = false;
        hasTunnels = true;
    }
    else
    {
        smallVersion = aReader.ReadBool();
        hasTunnels = aReader.ReadBool();
    }

    if (smallVersion)
    {
        mEditType = 0;
    }
    else
    {
        mEditType = aReader.ReadLong();
        ulong aBufferSize = aReader.ReadLong();
		aBufferSize = 20000;

        if (aBufferSize > 1000000)
        {
            mErrorString = "File is corrupt";
			printf("\n(Debug)<CircleShoot/CurveData.cpp> %s %s: %lu",__func__,mErrorString.c_str(),aBufferSize);
			fflush(stdout);
            return false;
        }

        uchar *aByteArray = new uchar[aBufferSize];
        aReader.ReadBytes(aByteArray, aBufferSize);
        mEditData.WriteBytes(aByteArray, aBufferSize);
        delete[] aByteArray;
    }

    ulong aSize = aReader.ReadLong();
    if (aSize > 0)
    {
        if (mVersion > 1)
        {
            mPointList.push_back(PathPoint());
            PathPoint &aStartPoint = mPointList.back();

            aStartPoint.x = aReader.ReadFloat();
            aStartPoint.y = aReader.ReadFloat();

            if (hasTunnels)
            {
                aStartPoint.mInTunnel = aReader.ReadBool();
                aStartPoint.mPriority = aReader.ReadByte();
            }

            float ox = aStartPoint.x;
            float oy = aStartPoint.y;

            for (ulong i = 0; i < aSize - 1; i++)
            {
                mPointList.push_back(PathPoint());
                PathPoint &aPoint = mPointList.back();

                signed char dx = aReader.ReadByte();
                signed char dy = aReader.ReadByte();

                aPoint.x = dx * INV_SUBPIXEL_MULT + ox;
                aPoint.y = dy * INV_SUBPIXEL_MULT + oy;

                if (hasTunnels)
                {
                    aPoint.mInTunnel = aReader.ReadBool();
                    aPoint.mPriority = aReader.ReadByte();
                }

                ox = aPoint.x;
                oy = aPoint.y;
            }
        }
        else
        {
            for (ulong i = 0; i < aSize; i++)
            {
                mPointList.push_back(PathPoint());
                PathPoint &aPoint = mPointList.back();

                aPoint.x = aReader.ReadFloat();
                aPoint.y = aReader.ReadFloat();
                aPoint.mInTunnel = aReader.ReadBool();
                aPoint.mPriority = aReader.ReadByte();
            }
        }
    }

    return true;
}*/

void CurveData::Clear()
{
    mPointList.clear();
    mEditType = 0;
    mEditData.Clear();
}