#include <QCoreApplication>
#include <QFileInfo>
#include "imagedenoizerapi.h"

int main(int argc, char *argv[])
{
    ImageDenoizeAPI denoizeAPI;
    ProcessParameters params;
    QImage output;

    // Set default parameters
    params.aperture = 5;

    if(argc < 2)
    {
        printf("2 arguments required (filename; gaussian|median|nlmeans) ! \n");
        return 0;
    }

    QString fileName = QString(argv[1]);
    QString filterType = QString(argv[2]);

    // Denoize target image with target filter
    //
    if(denoizeAPI.bDenoize(fileName, GetFilterTypeFromString(filterType), params, output))
        printf("File successfully denoized!\n");
    else
        printf("Error while denoizing! \n"
               "File path shall be in ASCII standard (no é, è, ê, µ, ¨, ...) \n"
               "File format shall be .jpg, .png, .tiff\n");

    // Save denoized image at target location
    //
    if(denoizeAPI.bSaveImage("./Image_Denoized.jpg", output))
        printf("Denoize file saved!\n");
    else
        printf("Error while saving denoized file!\n");
}

ProcessType GetFilterTypeFromString(QString type)
{
    ProcessType eType;

    if(type == "median")
    {
        eType = TypeMedianBlur;
        printf("TypeMedianBlur\n");
    }
    else if(type == "gaussian")
    {
        eType = TypeGaussianBlur;
        printf("TypeGaussianBlur\n");
    }
    else if(type == "nlmeans")
    {
        eType = TypeNlMeans;
        printf("TypeNlMeans\n");
    }
    else
    {
        printf("Default TypeGaussianBlur\n");
        eType = TypeGaussianBlur;
    }

    return eType;
}
