#include <QCoreApplication>
#include <QFileInfo>
#include "imagedenoizerapi.h"

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

int main(int argc, char *argv[])
{
    ImageDenoizeAPI denoizeAPI;
    ProcessParameters params;
    QImage output;

    // Set default parameters
    params.aperture = 5;
    params.sigma = 15;
    params.kernelSizeWidth = 5;
    params.kernelSizeHeight = 5;

    if(argc < 2)
    {
        printf("2 arguments required (filename; gaussian|median|nlmeans) ! \n");
        return 0;
    }

    QString fileName = QString(argv[1]);
    QString filterType = QString(argv[2]);

    // Load image
    //
    if(denoizeAPI.bLoadImage(fileName))
        printf("File successfully loaded!\n");
    else
        printf("Error while loading! \n"
               "File path shall be in ASCII standard (no é, è, ê, µ, ¨, ...) \n"
               "File format shall be .jpg, .png, .tiff\n");

    // Denoize target image with target filter
    //
    if(denoizeAPI.bApplyDenoizeToQImage(GetFilterTypeFromString(filterType), params, output))
        printf("File successfully denoized!\n");
    else
        printf("Error while denoizing! \n");

    // Save denoized image at target location
    //
    if(denoizeAPI.bSaveImage("./Image_Denoized.jpg", output))
        printf("Denoize file saved!\n");
    else
        printf("Error while saving denoized file!\n");
}
