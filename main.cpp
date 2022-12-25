#include <QCoreApplication>
#include <QDebug>
#include "imagedenoizapi.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc != 1)
    {
        qDebug() << "Only 1 arg needed!";
        return 0;
    }

    ImageDenoizeAPI denoizeAPI;
    ProcessParameters params;

    params.aperture = 5;

    denoizeAPI.bDenoize(QString("C:/Users/simon/Documents/Image_noise-example.jpg"), TypeMedianBlur, params);

    return a.exec();
}
