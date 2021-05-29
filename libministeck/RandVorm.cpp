#include "RandVorm.h"
#include <array>
#include <iostream>

RandVorm::RandVorm()
{

}

//v0 is een niet gebruikte variant dus die kunnen we gebruiken om te checken of een plek vrij is
//v0    v1    v2    v3    v4    v5    v6    v7    v8    v9    v10   v11   v12   v13   v14   v15
//000   111   111   111   111   101   111   101   111   111   100   001   101   111   111   101
//000   101   100   001   101   101   000   101   100   001   100   001   100   100   001   001
//000   111   111   111   101   111   111   101   100   001   111   111   111   101   101   111

std::vector<cv::Mat> RandVorm::GetRandVormen(int decimation) const
{
    std::vector<cv::Mat> vormen;
    //omdat de contructor van de cv::Mat geen copy maakt maar naar de data.data() blijft wijzen moet ik steeds
    // een nieuw std::array maken. Omdat de cv::Mat later overschreven word krijg ik geen stack problemen
    // met de gereturnde vector
    // v0
    std::array<uint8_t,9>data0 = { 0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data0.data()));

    // v1
    std::array<uint8_t,9>data1 = { 1, 1, 1,
                                   1, 0, 1,
                                   1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data1.data()));

    // v2
    std::array<uint8_t,9>data2 = { 1, 1, 1,
                                   1, 0, 0,
                                   1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data2.data()));

    // v3
    std::array<uint8_t,9>data3 = { 1, 1, 1,
                                   0, 0, 1,
                                   1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data3.data()));

    // v4
    std::array<uint8_t,9>data4 = { 1, 1, 1,
                                   1, 0, 1,
                                   1, 0, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data4.data()));

    // v5
    std::array<uint8_t,9>data5 = { 1, 0, 1,
                                   1, 0, 1,
                                   1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data5.data()));

    // v6
    std::array<uint8_t,9>data6 = { 1, 1, 1,
                                   0, 0, 0,
                                   1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data6.data()));

    // v7
    std::array<uint8_t,9>data7 = { 1, 0, 1,
                                   1, 0, 1,
                                   1, 0, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data7.data()));

    // v8
    std::array<uint8_t,9>data8 = { 1, 1, 1,
                                   1, 0, 0,
                                   1, 0, 0 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data8.data()));

    // v9
    std::array<uint8_t,9>data9 = { 1, 1, 1,
                                   0, 0, 1,
                                   0, 0, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data9.data()));

    // v10
    std::array<uint8_t,9>data10 = { 1, 0, 0,
                                    1, 0, 0,
                                    1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data10.data()));

    // v11
    std::array<uint8_t,9>data11 = { 0, 0, 1,
                                    0, 0, 1,
                                    1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data11.data()));

    // v12
    std::array<uint8_t,9>data12 = { 1, 0, 1,
                                    1, 0, 0,
                                    1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data12.data()));

    // v13
    std::array<uint8_t,9>data13 = { 1, 1, 1,
                                    1, 0, 0,
                                    1, 0, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data13.data()));

    // v14
    std::array<uint8_t,9>data14 = { 1, 1, 1,
                                    0, 0, 1,
                                    1, 0, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data14.data()));

    // v15
    std::array<uint8_t,9>data15 = { 1, 0, 1,
                                    0, 0, 1,
                                    1, 1, 1 };
    vormen.emplace_back(cv::Mat(3, 3, CV_8UC1, data15.data()));

    // convert de vormen naar een cv::Mat(decimation,decimation)
    for(auto& vorm:vormen)
    {
        cv::Mat out(decimation, decimation, CV_8UC1, cv::Scalar(0));

        // vul eerst de hoekpunten in
        out.at<uint8_t>(0,0) = vorm.at<uint8_t>(0,0);
        out.at<uint8_t>(decimation-1,0) = vorm.at<uint8_t>(2,0);
        out.at<uint8_t>(0,decimation-1) = vorm.at<uint8_t>(0,2);
        out.at<uint8_t>(decimation-1,decimation-1) = vorm.at<uint8_t>(2,2);
        for(int i=1;i<decimation-1;i++)
        {
            out.at<uint8_t>(0,i) = vorm.at<uint8_t>(0,1);
            out.at<uint8_t>(decimation-1,i) = vorm.at<uint8_t>(2,1);
            out.at<uint8_t>(i,0) = vorm.at<uint8_t>(1,0);
            out.at<uint8_t>(i,decimation-1) = vorm.at<uint8_t>(1,2);
        }
        vorm = out;  //overschijf de content
    }
    return vormen;
}
