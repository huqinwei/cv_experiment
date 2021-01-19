#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <chrono>
#include <windows.h>
//#include "LLog.h"

using namespace std;
using namespace cv;
using namespace std::chrono;


LPCWSTR stringToLPCWSTR(std::string orig)
{
    size_t origsize = orig.length() + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

    return wcstring;
}

struct ImageInfo {
    cv::Mat image;
    std::vector<cv::KeyPoint> key_points;
    cv::Mat descriptors;
    cv::Point trans;
    cv::Mat homo;
    int flag = false;
};









//��Ҫ�۲��������
//ͬ�ӽǲ�ͬ֡�Աȣ�һ��ƽ������ƥ�䣬������Եͼ���ص�������û��������
//��ͬ�ӽ�ͬ֡�Ա�(����360�и������)
//��ͬ�ӽǲ�ͬ֡�Աȣ���װ���ӽǣ�

//����ƥ��ʵ�飬����һ����ȡʵ�飬��ȡ�������������������������Ҫ���к�Σ��ϵ��Ĳ��֡�
//ʵ��colmap������sift 2048��4096
void SouthStreet_Feature() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(2048);
    cv::namedWindow("good_match", 0);

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    //D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles_43_new
    //D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles
    //D:\AR\south_street\FOV80\2
    //D:\AR_Data\NanLuoGuXiang\VID_20200928_102456_00_003\out\2
    for (int i = 360; i <= 500; ++i) {
        sprintf_s(im1_path, "D:\\AR_Data\\NanLuoGuXiang\\VID_20200928_102456_00_003\\out\\2\\%08d.jpg", i + 1);
        sprintf_s(im2_path, "D:\\AR_Data\\NanLuoGuXiang\\VID_20200928_102456_00_003\\out\\2\\%08d.jpg", i + 2);

        im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
        im2 = imread(im2_path, cv::IMREAD_COLOR);
        start_time = std::chrono::high_resolution_clock::now();
        if (0)
        {
            cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
            cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));
        }

        // 		if (i % 2 == 0)//��ʱ����
        // 		{
        // 			flip(im2, im2, 0);
        // 			flip(im2, im2, 1);
        // 		}

        vector<cv::KeyPoint> key_points1, key_points2;
        start_time = std::chrono::high_resolution_clock::now();
        sift->detect(im1, key_points1);
        sift->detect(im2, key_points2);

        cv::Mat descriptors1, descriptors2;
        sift->compute(im1, key_points1, descriptors1);
        sift->compute(im2, key_points2, descriptors2);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
        vector<cv::DMatch> matchs;
        cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
        start_time = std::chrono::high_resolution_clock::now();
        bf_matcher.match(descriptors1, descriptors2, matchs);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        vector<cv::Point2f> points1, points2;
        for (const auto& match : matchs) {
            points1.push_back(key_points1[match.queryIdx].pt);
            points2.push_back(key_points2[match.trainIdx].pt);
        }

        if (1)
        {
            vector<uchar> inlier_mask;
            Mat H = cv::findHomography(points1, points2, RANSAC, 3, inlier_mask);

            if (1)//inlier��һ������
            {
                for (int i = 0; i < matchs.size(); ++i) {
                    if (!inlier_mask[i]) {
                        matchs.erase(matchs.begin() + i);
                        inlier_mask.erase(inlier_mask.begin() + i);
                        --i;
                    }
                }
            }


            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        }

        cout << "matchs:" << matchs.size() << endl;

        cv::Mat good_match;
        cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);

        char output_path[512];
        sprintf_s(output_path, "D:\\AR_Data\\NanLuoGuXiang\\VID_20200928_102456_00_003\\out\\match2\\%08d_%08d.png", i, i + 1);

        imwrite(output_path, good_match);
#if 0
        cv::imshow("good_match", good_match);
        cv::waitKey(0);
#endif
    }
}

//ͳ��ƥ��������
//�÷���ָ���ضΣ�������ƥ��ͼ�Ķ�����good_match�Ķ���������good_match����һ��Ҫ���ͼ��ƥ�����
void SouthStreet_FeatureMatches_Statistics() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(2048);//2048
    cv::namedWindow("good_match", 0);
    const int use_inlier_mask = 1;
    int u = 140;
    int v = 140;
    const int crop = 0;
    double total_matches = 0;//ͳ���ܵ�ƥ��ԣ�����Ա�
    int step_index = 13;
    int group_index = 1;
    for (int group_index = 2; group_index <= 2; group_index++)
    {

        std::chrono::high_resolution_clock::time_point start_time, end_time;
        for (int i = 20; i <= 40 - step_index; ++i) {
            sprintf_s(im1_path, "E:\\slicing\\fov_u=%dANDfov_v=%d\\%d\\%08d.jpg", u, v, group_index, (i) * 10);
            sprintf_s(im2_path, "E:\\slicing\\fov_u=%dANDfov_v=%d\\%d\\%08d.jpg", u, v, group_index, (i + step_index) * 10);

            im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
            im2 = imread(im2_path, cv::IMREAD_COLOR);

            start_time = std::chrono::high_resolution_clock::now();

#if 1//��ԭͼ���вü���ֻ�����Ĳ���(������ĵ�λ�ã��Աȱ�Ե)
            if (crop) {
                im1(cv::Rect(602, 802, 602, 602)).copyTo(im1);
                im2(cv::Rect(602, 802, 602, 602)).copyTo(im2);
            }
#endif
#if 0

            cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
            cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));

#endif
#if 0
            if (i % 2 == 0)
            {
                flip(im2, im2, 0);
                flip(im2, im2, 1);
            }
#endif

            vector<cv::KeyPoint> key_points1, key_points2;
            start_time = std::chrono::high_resolution_clock::now();
            sift->detect(im1, key_points1);
            sift->detect(im2, key_points2);

            cv::Mat descriptors1, descriptors2;
            sift->compute(im1, key_points1, descriptors1);
            sift->compute(im2, key_points2, descriptors2);
            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
            vector<cv::DMatch> matchs;
            cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
            start_time = std::chrono::high_resolution_clock::now();
            bf_matcher.match(descriptors1, descriptors2, matchs);
            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            vector<cv::Point2f> points1, points2;
            for (const auto& match : matchs) {
                points1.push_back(key_points1[match.queryIdx].pt);
                points2.push_back(key_points2[match.trainIdx].pt);
            }

            if (use_inlier_mask)
            {
                vector<uchar> inlier_mask;
                Mat H = cv::findHomography(points1, points2, RANSAC, 3, inlier_mask);

                if (1)//inlier��һ������
                {
                    for (int i = 0; i < matchs.size(); ++i) {
                        if (!inlier_mask[i]) {
                            matchs.erase(matchs.begin() + i);
                            inlier_mask.erase(inlier_mask.begin() + i);
                            --i;
                        }
                    }
                }


                end_time = std::chrono::high_resolution_clock::now();
                std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            }

            cout << "matchs:" << matchs.size() << endl;
            total_matches += matchs.size();

            cv::Mat good_match;
            cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);

            char output_path[512];
            std::string output_dir;
            sprintf_s(output_path, "E:\\slicing\\fov_u=%dANDfov_v=%d\\useinlier_%d_usecrop_%d_matches%d_%d\\%08d_%08d.png", u, v, use_inlier_mask, crop, group_index, step_index, i, i + step_index);
            output_dir = "E:\\slicing\\fov_u=" + std::to_string(u) + "ANDfov_v=" + std::to_string(v) + "\\useinlier_" + std::to_string(use_inlier_mask) + "_usecrop_" + std::to_string(crop) + "_matches" + std::to_string(group_index) + "_" + std::to_string(step_index);
            CreateDirectory(stringToLPCWSTR(output_dir), NULL);

            imwrite(output_path, good_match);
#if 0
            cv::imshow("good_match", good_match);
            cv::waitKey();
#endif
        }
        cout << "total_matchs:" << total_matches << endl;
    }


}


void NLGX_FeatureMatches_Statistics_DJI() {
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(4096);//2048
    int u = 70;
    int v = 80;
    int n = 6;

    const int use_inlier_mask = 1;
    const int crop = 0;
    double total_matches = 0;//ͳ���ܵ�ƥ��ԣ�����Ա�
    int step_index = 1;
    for (int group_index = 0; group_index <= 0; group_index++)
    {

        std::chrono::high_resolution_clock::time_point start_time, end_time;
        for (int i = 481; i <= 676 - step_index; ++i) {
            //G:\nanluo_ar_data\NLGX421_640_u50v50n8

            char im1_path[512];
            char im2_path[512];
            sprintf_s(im1_path, "G:\\NLGX291_650_pic\\NLGX291_650_u%dv%dn%d\\dji_pic\\DJI_%04d.JPG", u, v, n, (i));
            sprintf_s(im2_path, "G:\\NLGX291_650_pic\\NLGX291_650_u%dv%dn%d\\dji_pic\\DJI_%04d.JPG", u, v, n, (i + step_index));

            cv::Mat im1, im2;
            im1 = imread(im1_path, cv::IMREAD_UNCHANGED);//IMREAD_UNCHANGED
            im2 = imread(im2_path, cv::IMREAD_UNCHANGED);


            //��ԭͼ���вü���ֻ�����Ĳ���(������ĵ�λ�ã��Աȱ�Ե)
            if (crop) {
                double resize_ratio = (double)1 / (double)3;
                im1(cv::Rect(im1.cols*(1 - resize_ratio) / 2, im1.rows*(1 - resize_ratio) / 2, im1.cols*resize_ratio, im1.rows*resize_ratio)).copyTo(im1);
                im2(cv::Rect(im2.cols*(1 - resize_ratio) / 2, im2.rows*(1 - resize_ratio) / 2, im2.cols*resize_ratio, im2.rows*resize_ratio)).copyTo(im2);
            }

            vector<cv::KeyPoint> key_points1, key_points2;
            sift->detect(im1, key_points1);
            sift->detect(im2, key_points2);

            cv::Mat descriptors1, descriptors2;
            sift->compute(im1, key_points1, descriptors1);
            sift->compute(im2, key_points2, descriptors2);
            vector<cv::DMatch> matchs;
            cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
            bf_matcher.match(descriptors1, descriptors2, matchs);

            vector<cv::Point2f> points1, points2;
            for (const auto& match : matchs) {
                points1.push_back(key_points1[match.queryIdx].pt);
                points2.push_back(key_points2[match.trainIdx].pt);
            }

            if (use_inlier_mask)
            {
                vector<uchar> inlier_mask;
                Mat H = cv::findHomography(points1, points2, RANSAC, 3, inlier_mask);

                if (1)//inlier��һ������
                {
                    for (int i = 0; i < matchs.size(); ++i) {
                        if (!inlier_mask[i]) {
                            matchs.erase(matchs.begin() + i);
                            inlier_mask.erase(inlier_mask.begin() + i);
                            --i;
                        }
                    }
                }
                end_time = std::chrono::high_resolution_clock::now();
                std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            }

            cout << "matchs:" << matchs.size() << endl;
            total_matches += matchs.size();

            cv::Mat good_match;
            cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);

            //����
            std::string match_size = "u:" + std::to_string(u)
                + "  v:" + std::to_string(v)
                + "  n:" + std::to_string(n)
                + "  index:" + std::to_string(group_index)
                + "  pic:" + std::to_string(i)
                + "  step:" + std::to_string(step_index)
                + "  matches:" + std::to_string(matchs.size());

            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = 2;
            int thickness = 2;
            int baseline;
            //��ȡ�ı���ĳ���
            cv::Size text_size = cv::getTextSize(match_size, font_face, font_scale, thickness, &baseline);
            cv::Point origin;
            origin.x = good_match.cols - text_size.width;//good_match.cols / 2 - text_size.width / 2;
            origin.y = good_match.rows;// +text_size.height;//good_match.rows / 2 + text_size.height / 2;
            cv::putText(good_match, match_size, origin, font_face, font_scale, cv::Scalar(255, 0, 255), thickness, 8, 0);

            char output_path[512];
            std::string output_dir;
            sprintf_s(output_path, "G:\\NLGX291_650_pic\\NLGX291_650_u%dv%dn%d\\dji_useinlier_%d_usecrop_%d_matches%d_%d\\%08d_%08d.png", u, v, n, use_inlier_mask, crop, group_index, step_index, i, i + step_index);
            output_dir = "G:\\NLGX291_650_pic\\NLGX291_650_u" + std::to_string(u) + "v" + std::to_string(v) + "n" + std::to_string(n) + "\\dji_useinlier_" + std::to_string(use_inlier_mask) + "_usecrop_" + std::to_string(crop) + "_matches" + std::to_string(group_index) + "_" + std::to_string(step_index);
            CreateDirectory(stringToLPCWSTR(output_dir), NULL);

            imwrite(output_path, good_match);

        }
        cout << "total_matchs:" << total_matches << endl;
    }


}
void NLGX_FeatureMatches_Statistics_634_samples() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(2048);//2048
    cv::namedWindow("good_match", 0);
    int u = 70;
    int v = 70;
    int n = 8;

    const int use_inlier_mask = 1;
    const int crop = 0;
    double total_matches = 0;//ͳ���ܵ�ƥ��ԣ�����Ա�
    int step_index = 1;
    for (int group_index = 1; group_index <= 8; group_index++)
    {

        std::chrono::high_resolution_clock::time_point start_time, end_time;
        for (int i = 26; i <= 31 - step_index; ++i) {
            //G:\nanluo_ar_data\NLGX421_640_u50v50n8
            //D:\nanluo_ar_data\NLGX_0928_634_samples_u50v50n8\3
            sprintf_s(im1_path, "D:\\nanluo_ar_data\\NLGX_0928_634_samples_u%dv%dn%d\\%d\\%08d.jpg", u, v, n, group_index, (i));
            sprintf_s(im2_path, "D:\\nanluo_ar_data\\NLGX_0928_634_samples_u%dv%dn%d\\%d\\%08d.jpg", u, v, n, group_index, (i + step_index));

            im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
            im2 = imread(im2_path, cv::IMREAD_COLOR);

            start_time = std::chrono::high_resolution_clock::now();

            //��ԭͼ���вü���ֻ�����Ĳ���(������ĵ�λ�ã��Աȱ�Ե)
            if (crop) {
                double resize_ratio = (double)1 / (double)3;
                im1(cv::Rect(im1.cols*(1 - resize_ratio) / 2, im1.rows*(1 - resize_ratio) / 2, im1.cols*resize_ratio, im1.rows*resize_ratio)).copyTo(im1);
                im2(cv::Rect(im2.cols*(1 - resize_ratio) / 2, im2.rows*(1 - resize_ratio) / 2, im2.cols*resize_ratio, im2.rows*resize_ratio)).copyTo(im2);
            }

            vector<cv::KeyPoint> key_points1, key_points2;
            start_time = std::chrono::high_resolution_clock::now();
            sift->detect(im1, key_points1);
            sift->detect(im2, key_points2);

            cv::Mat descriptors1, descriptors2;
            sift->compute(im1, key_points1, descriptors1);
            sift->compute(im2, key_points2, descriptors2);
            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
            vector<cv::DMatch> matchs;
            cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
            start_time = std::chrono::high_resolution_clock::now();
            bf_matcher.match(descriptors1, descriptors2, matchs);
            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            vector<cv::Point2f> points1, points2;
            for (const auto& match : matchs) {
                points1.push_back(key_points1[match.queryIdx].pt);
                points2.push_back(key_points2[match.trainIdx].pt);
            }

            if (use_inlier_mask)
            {
                vector<uchar> inlier_mask;
                Mat H = cv::findHomography(points1, points2, RANSAC, 8, inlier_mask);

                if (1)//inlier��һ������
                {
                    for (int i = 0; i < matchs.size(); ++i) {
                        if (!inlier_mask[i]) {
                            matchs.erase(matchs.begin() + i);
                            inlier_mask.erase(inlier_mask.begin() + i);
                            --i;
                        }
                    }
                }
                end_time = std::chrono::high_resolution_clock::now();
                std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            }

            cout << "matchs:" << matchs.size() << endl;
            total_matches += matchs.size();

            cv::Mat good_match;
            cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);

            //����
            std::string match_size = "u:" + std::to_string(u)
                + "  v:" + std::to_string(v)
                + "  n:" + std::to_string(n)
                + "  index:" + std::to_string(group_index)
                + "  pic:" + std::to_string(i)
                + "  step:" + std::to_string(step_index)
                + "  matches:" + std::to_string(matchs.size());

            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = 1.2;
            int thickness = 2;
            int baseline;
            //��ȡ�ı���ĳ���
            cv::Size text_size = cv::getTextSize(match_size, font_face, font_scale, thickness, &baseline);
            cv::Point origin;
            origin.x = good_match.cols - text_size.width;//good_match.cols / 2 - text_size.width / 2;
            origin.y = good_match.rows;// +text_size.height;//good_match.rows / 2 + text_size.height / 2;
            cv::putText(good_match, match_size, origin, font_face, font_scale, cv::Scalar(255, 0, 255), thickness, 8, 0);

            char output_path[512];
            std::string output_dir;
            //G:\\nanluo_ar_data\\NLGX421_640_u%dv%dn%d
            //D:\nanluo_ar_data\NLGX_0928_634_samples_u50v50n8\3
            sprintf_s(output_path, "D:\\nanluo_ar_data\\NLGX_0928_634_samples_u%dv%dn%d\\useinlier_%d_usecrop_%d_matches%d_%d\\%08d_%08d.png", u, v, n, use_inlier_mask, crop, group_index, step_index, i, i + step_index);
            output_dir = "D:\\nanluo_ar_data\\NLGX_0928_634_samples_u" + std::to_string(u) + "v" + std::to_string(v) + "n" + std::to_string(n) + "\\useinlier_" + std::to_string(use_inlier_mask) + "_usecrop_" + std::to_string(crop) + "_matches" + std::to_string(group_index) + "_" + std::to_string(step_index);
            CreateDirectory(stringToLPCWSTR(output_dir), NULL);

            imwrite(output_path, good_match);
#if 0
            cv::imshow("good_match", good_match);
            cv::waitKey();
#endif
        }
        cout << "total_matchs:" << total_matches << endl;
    }


}

void NLGX_FeatureMatches_Statistics() {
    int u = 70;
    int v = 80;
    int n = 8;

    const int use_inlier_mask = 1;
    const int crop = 0;
    double total_matches = 0;//ͳ���ܵ�ƥ��ԣ�����Ա�
    int step_index = 1;
    for (int group_index = 1; group_index <= 2; group_index++)
    {
        for (int i = 301; i <= 400 - step_index; ++i) {
            cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(2048);//2048
            char im1_path[512];
            char im2_path[512];

            sprintf_s(im1_path, "D:\\NLGX634_PIC\\NLGX_634_u%dv%dn%d\\%d\\%08d.jpg", u, v, n, group_index, (i));
            sprintf_s(im2_path, "D:\\NLGX634_PIC\\NLGX_634_u%dv%dn%d\\%d\\%08d.jpg", u, v, n, group_index, (i + step_index));
            cv::Mat im1, im2;
            im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
            im2 = imread(im2_path, cv::IMREAD_COLOR);

            //��ԭͼ���вü���ֻ�����Ĳ���(������ĵ�λ�ã��Աȱ�Ե)
            if (crop) {
                double resize_ratio = (double)1 / (double)3;
                im1(cv::Rect(im1.cols*(1 - resize_ratio) / 2, im1.rows*(1 - resize_ratio) / 2, im1.cols*resize_ratio, im1.rows*resize_ratio)).copyTo(im1);
                im2(cv::Rect(im2.cols*(1 - resize_ratio) / 2, im2.rows*(1 - resize_ratio) / 2, im2.cols*resize_ratio, im2.rows*resize_ratio)).copyTo(im2);
            }

            vector<cv::KeyPoint> key_points1, key_points2;
            sift->detect(im1, key_points1);
            sift->detect(im2, key_points2);

            cv::Mat descriptors1, descriptors2;
            sift->compute(im1, key_points1, descriptors1);
            sift->compute(im2, key_points2, descriptors2);
            vector<cv::DMatch> matchs;
            cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
            bf_matcher.match(descriptors1, descriptors2, matchs);

            vector<cv::Point2f> points1, points2;
            for (const auto& match : matchs) {
                points1.push_back(key_points1[match.queryIdx].pt);
                points2.push_back(key_points2[match.trainIdx].pt);
            }

            if (use_inlier_mask)
            {
                vector<uchar> inlier_mask;
                Mat H = cv::findHomography(points1, points2, RANSAC, 3, inlier_mask);

                for (int i = 0; i < matchs.size(); ++i) {
                    if (!inlier_mask[i]) {
                        matchs.erase(matchs.begin() + i);
                        inlier_mask.erase(inlier_mask.begin() + i);
                        --i;
                    }
                }
            }

            cout << "matchs:" << matchs.size() << endl;
            total_matches += matchs.size();

            cv::Mat good_match;
            cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);

            //����
            std::string match_size = "u:" + std::to_string(u)
                + "  v:" + std::to_string(v)
                + "  n:" + std::to_string(n)
                + "  index:" + std::to_string(group_index)
                + "  pic:" + std::to_string(i) + "-" + std::to_string(i + step_index)
                + "  matches:" + std::to_string(matchs.size());

            int font_face = cv::FONT_HERSHEY_COMPLEX;
            double font_scale = 1.4;
            int thickness = 2;
            int baseline;
            //��ȡ�ı���ĳ���
            cv::Size text_size = cv::getTextSize(match_size, font_face, font_scale, thickness, &baseline);
            cv::Point origin;
            origin.x = good_match.cols - text_size.width;//good_match.cols / 2 - text_size.width / 2;
            origin.y = good_match.rows;// +text_size.height;//good_match.rows / 2 + text_size.height / 2;
            cv::putText(good_match, match_size, origin, font_face, font_scale, cv::Scalar(200, 0, 200), thickness, 8, 0);

            char output_path[512];
            std::string output_dir;
            //G:\\nanluo_ar_data\\NLGX421_640_u%dv%dn%d
            sprintf_s(output_path, "D:\\NLGX634_PIC\\NLGX_634_u%dv%dn%d\\useinlier_%d_usecrop_%d_matches%d_step%d\\%08d_%08d.png", u, v, n, use_inlier_mask, crop, group_index, step_index, i, i + step_index);
            output_dir = "D:\\NLGX634_PIC\\NLGX_634_u" + std::to_string(u) + "v" + std::to_string(v) + "n" + std::to_string(n)
                + "\\useinlier_" + std::to_string(use_inlier_mask) + "_usecrop_" + std::to_string(crop)
                + "_matches" + std::to_string(group_index) + "_step" + std::to_string(step_index);
            CreateDirectory(stringToLPCWSTR(output_dir), NULL);

            imwrite(output_path, good_match);
        }
        cout << "total_matchs:" << total_matches << endl;
    }
}

void SouthStreet_FeatureMatches_Statistics_fov40() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(2048);//2048
    cv::namedWindow("good_match", 0);
    double total_matches = 0;//ͳ���ܵ�ƥ��ԣ�����Ա�
    int group_index = 6;
    int step_index = 2;
    const int use_inlier_mask = 1;
    int u = 40;
    int v = 80;
    const int crop = 0;

    char output_path[512];
    std::string output_dir;
    output_dir = "E:\\slicing\\v40u40n9\\useinlier_" + std::to_string(use_inlier_mask) + "_usecrop_" + std::to_string(crop) + "_matches" + std::to_string(group_index) + "_" + std::to_string(step_index);
    CreateDirectory(stringToLPCWSTR(output_dir), NULL);

    std::chrono::high_resolution_clock::time_point start_time, end_time;

    for (int i = 500; i <= 600 - step_index; ++i) {
        sprintf_s(im1_path, "E:\\slicing\\v40u40n9\\%d\\%08d.jpg", group_index, i);
        sprintf_s(im2_path, "E:\\slicing\\v40u40n9\\%d\\%08d.jpg", group_index, i + step_index);

        im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
        im2 = imread(im2_path, cv::IMREAD_COLOR);

        start_time = std::chrono::high_resolution_clock::now();

#if 1//��ԭͼ���вü���ֻ�����Ĳ���(������ĵ�λ�ã��Աȱ�Ե)
        if (crop) {
            im1(cv::Rect(602, 802, 602, 602)).copyTo(im1);
            im2(cv::Rect(602, 802, 602, 602)).copyTo(im2);
        }
#endif
#if 0

        cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
        cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));

#endif
#if 0
        if (i % 2 == 0)
        {
            flip(im2, im2, 0);
            flip(im2, im2, 1);
        }
#endif

        vector<cv::KeyPoint> key_points1, key_points2;
        start_time = std::chrono::high_resolution_clock::now();
        sift->detect(im1, key_points1);
        sift->detect(im2, key_points2);

        cv::Mat descriptors1, descriptors2;
        sift->compute(im1, key_points1, descriptors1);
        sift->compute(im2, key_points2, descriptors2);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
        vector<cv::DMatch> matchs;
        cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
        start_time = std::chrono::high_resolution_clock::now();
        bf_matcher.match(descriptors1, descriptors2, matchs);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        vector<cv::Point2f> points1, points2;
        for (const auto& match : matchs) {
            points1.push_back(key_points1[match.queryIdx].pt);
            points2.push_back(key_points2[match.trainIdx].pt);
        }

        if (use_inlier_mask)
        {
            vector<uchar> inlier_mask;
            Mat H = cv::findHomography(points1, points2, RANSAC, 3, inlier_mask);

            if (1)//inlier��һ������
            {
                for (int i = 0; i < matchs.size(); ++i) {
                    if (!inlier_mask[i]) {
                        matchs.erase(matchs.begin() + i);
                        inlier_mask.erase(inlier_mask.begin() + i);
                        --i;
                    }
                }
            }


            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        }

        cout << "matchs:" << matchs.size() << endl;
        total_matches += matchs.size();

        cv::Mat good_match;
        cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);


        std::string output_dir;
        sprintf_s(output_path, "E:\\slicing\\v40u40n9\\useinlier_%d_usecrop_%d_matches%d_%d\\%08d_%08d.png", use_inlier_mask, crop, group_index, step_index, i, i + step_index);

        imwrite(output_path, good_match);
#if 0
        cv::imshow("good_match", good_match);
        cv::waitKey();
#endif
    }
    cout << "total_matchs:" << total_matches << endl;
}


//˫��ѭ��ƥ��

void SouthStreet_FeatureMatch_specified() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create(2048);
    cv::namedWindow("good_match", 0);

    double  ransac_value = 8.0;
    double total_matches = 0;

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    //D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles_43_new
    //D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles
    //D:\AR\south_street\FOV80\2  

    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= 10; ++j)
        {
            //E:\slicing\fov_u=80ANDfov_v=80\1
            sprintf_s(im1_path, "E:\\slicing\\fov_u=80ANDfov_v=80\\2\\%08d.jpg", (25 + i) * 10);//��3/65Ϊ����
            sprintf_s(im2_path, "E:\\slicing\\fov_u=80ANDfov_v=80\\3\\%08d.jpg", (25 + j) * 10);//��4/78Ϊ����

            im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
            im2 = imread(im2_path, cv::IMREAD_COLOR);
            start_time = std::chrono::high_resolution_clock::now();
            if (0)
            {
                cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
                cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));
            }

            // 		if (i % 2 == 0)//��ʱ����
            // 		{
            // 			flip(im2, im2, 0);
            // 			flip(im2, im2, 1);
            // 		}

            vector<cv::KeyPoint> key_points1, key_points2;
            start_time = std::chrono::high_resolution_clock::now();
            sift->detect(im1, key_points1);
            sift->detect(im2, key_points2);

            cv::Mat descriptors1, descriptors2;
            sift->compute(im1, key_points1, descriptors1);
            sift->compute(im2, key_points2, descriptors2);
            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
            vector<cv::DMatch> matches;
            cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
            start_time = std::chrono::high_resolution_clock::now();
            bf_matcher.match(descriptors1, descriptors2, matches);
            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            vector<cv::Point2f> points1, points2;
            for (const auto& match : matches) {
                points1.push_back(key_points1[match.queryIdx].pt);
                points2.push_back(key_points2[match.trainIdx].pt);
            }

            if (1)
            {
                vector<uchar> inlier_mask;
                Mat H = cv::findHomography(points1, points2, RANSAC, ransac_value, inlier_mask);

                if (1)//inlier��һ������
                {
                    for (int i = 0; i < matches.size(); ++i) {
                        if (!inlier_mask[i]) {
                            matches.erase(matches.begin() + i);
                            inlier_mask.erase(inlier_mask.begin() + i);
                            --i;
                        }
                    }
                }


                end_time = std::chrono::high_resolution_clock::now();
                std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

            }

            cout << "matchs:" << matches.size() << endl;
            total_matches += matches.size();

            cv::Mat good_match;
            cv::drawMatches(im1, key_points1, im2, key_points2, matches, good_match);

            char output_path[512];
            sprintf_s(output_path, "E:\\slicing\\fov_u=80ANDfov_v=80\\matches_2_3_ransac%0.0f\\1_%08d_4_%08d.png", ransac_value, i + 25, j + 25);

            imwrite(output_path, good_match);
        }
        std::cout << "total_matches:" << total_matches << std::endl;
#if 0
        cv::imshow("good_match", good_match);
        cv::waitKey(0);
#endif
    }
}

void SURFTest() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(500);//��ǰд��1500
    cv::namedWindow("good_match", 0);

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    //D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles_43_new
    //D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles
    //D:\AR\south_street\FOV80\2

    for (int i = 0; i < 30; ++i) {
        sprintf_s(im1_path, "D:\\AR\\south_street\\FOV80\\2\\0000%d.png", i + 3459);//D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\good_output\lines
        sprintf_s(im2_path, "D:\\VS2015\\Projects\\image_mosaicing\\image_mosaicing\\airlook_image_mosaicing\\test_exe\\output\\lines_43_5frame\\4_504.png", i + 3460);

        im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
        im2 = imread(im2_path, cv::IMREAD_COLOR);
        start_time = std::chrono::high_resolution_clock::now();
        if (0)
        {
            cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
            cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));
        }

        // 		if (i % 2 == 0)//��ʱ����
        // 		{
        // 			flip(im2, im2, 0);
        // 			flip(im2, im2, 1);
        // 		}

        vector<cv::KeyPoint> key_points1, key_points2;
        start_time = std::chrono::high_resolution_clock::now();
        surf->detect(im1, key_points1);
        surf->detect(im2, key_points2);

        cv::Mat descriptors1, descriptors2;
        surf->compute(im1, key_points1, descriptors1);
        surf->compute(im2, key_points2, descriptors2);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
        vector<cv::DMatch> matchs;
        cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
        start_time = std::chrono::high_resolution_clock::now();
        bf_matcher.match(descriptors1, descriptors2, matchs);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        vector<cv::Point2f> points1, points2;
        for (const auto& match : matchs) {
            points1.push_back(key_points1[match.queryIdx].pt);
            points2.push_back(key_points2[match.trainIdx].pt);
        }

        if (1)
        {
            vector<uchar> inlier_mask;
            Mat H = cv::findHomography(points1, points2, RANSAC, 8, inlier_mask);

            if (0)//inlier��һ������
            {
                for (int i = 0; i < matchs.size(); ++i) {
                    if (!inlier_mask[i]) {
                        matchs.erase(matchs.begin() + i);
                        inlier_mask.erase(inlier_mask.begin() + i);
                        --i;
                    }
                }
            }


            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        }

        cout << "matchs:" << matchs.size() << endl;

        cv::Mat good_match;
        cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);
        imwrite("D:\\VS2015\\Projects\\image_mosaicing\\image_mosaicing\\airlook_image_mosaicing\\test_exe\\output\\lines_43_5frame\\surf1500_43_frame5_match_3_4.png", good_match);

        cv::imshow("good_match", good_match);
        cv::waitKey(0);

    }
}

void SURFTest_new1() {
    cv::Mat im1, im2;
    char im1_path[512];
    char im2_path[512];
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(500);//����ǰд��1500
    cv::namedWindow("good_match", 0);

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    //D:\airlook_image_mosaicing\test_exe\output\lines
    for (int i = 0; i < 3; ++i) {//D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\output_43_new\singles
        sprintf_s(im1_path, "D:\\airlook_image_mosaicing\\test_exe\\output\\lines\\%d.png", i + 1);//D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\good_output\lines
        sprintf_s(im2_path, "D:\\airlook_image_mosaicing\\test_exe\\output\\lines\\%d.png", i + 2);

        im1 = imread(im1_path, cv::IMREAD_COLOR);//IMREAD_UNCHANGED
        im2 = imread(im2_path, cv::IMREAD_COLOR);//��ͨ��ֱ��

        start_time = std::chrono::high_resolution_clock::now();
        if (0)
        {
            cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
            cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));
        }

        vector<cv::KeyPoint> key_points1, key_points2;
        start_time = std::chrono::high_resolution_clock::now();
        surf->detect(im1, key_points1);
        surf->detect(im2, key_points2);

        cv::Mat descriptors1, descriptors2;
        surf->compute(im1, key_points1, descriptors1);
        surf->compute(im2, key_points2, descriptors2);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
        vector<cv::DMatch> matchs;
        cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
        start_time = std::chrono::high_resolution_clock::now();
        if (descriptors1.dims == 0 || descriptors2.dims == 0)
        {
            cout << "ƥ�䲻��" << endl;
            continue;

        }
        bf_matcher.match(descriptors1, descriptors2, matchs);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        vector<cv::Point2f> points1, points2;
        for (const auto& match : matchs) {
            points1.push_back(key_points1[match.queryIdx].pt);
            points2.push_back(key_points2[match.trainIdx].pt);
        }

        if (1)
        {
            vector<uchar> inlier_mask;
            Mat H = cv::findHomography(points1, points2, RANSAC, 30, inlier_mask);
            cout << H << endl;
            for (int i = 0; i < matchs.size(); ++i) {
                if (!inlier_mask[i]) {
                    matchs.erase(matchs.begin() + i);
                    inlier_mask.erase(inlier_mask.begin() + i);
                    --i;
                }
            }

            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        }


        cv::Mat good_match;
        char out_path[512];
        sprintf_s(out_path, "D:\\airlook_image_mosaicing\\test_exe\\output\\lines\\match_%d.png", i + 1, i + 2);
        cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);
        cv::imshow("good_match", good_match);
        cv::imwrite(out_path, good_match);
        cv::waitKey(0);
    }


    cout << "endl" << endl;
}

//ƥ��֮�����ӳ��
void SURF_Stitch() {
    cv::Mat im1, im2, im1_origin, im2_origin;
    char im1_path[512];
    char im2_path[512];
    char dst_path[512];
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(1500);//��ǰд��1500
                                                                              //cv::namedWindow("good_match", 0);

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    for (int i = 0; i < 1; ++i) {
        sprintf_s(im1_path, "D:\\VS2015\\Projects\\image_mosaicing\\image_mosaicing\\my_image_stitching\\test_exe\\output\\singles\\%d.png", i + 1);//D:\VS2015\Projects\image_mosaicing\image_mosaicing\my_image_stitching\test_exe\output\good_output\lines
        sprintf_s(im2_path, "D:\\VS2015\\Projects\\image_mosaicing\\image_mosaicing\\my_image_stitching\\test_exe\\output\\singles\\%d.png", i + 2);
        sprintf_s(dst_path, "D:\\VS2015\\Projects\\image_mosaicing\\image_mosaicing\\my_image_stitching\\test_exe\\output\\singles\\%d_%d.png", i + 1, i + 2);

        im1_origin = imread(im1_path, cv::IMREAD_UNCHANGED);//��������ͨ���ģ����ƴ������ͨ�����У�ƥ������ͨ��
        im2_origin = imread(im2_path, cv::IMREAD_UNCHANGED);

        std::vector<cv::Mat> im1_Channels;
        cv::split(im1_origin, im1_Channels);
        im1_Channels.pop_back();
        cv::merge(im1_Channels, im1);
        cout << im1.channels() << endl;

        std::vector<cv::Mat> im2_Channels;
        cv::split(im2_origin, im2_Channels);
        im2_Channels.pop_back();
        cv::merge(im2_Channels, im2);
        cout << im2.channels() << endl;



        start_time = std::chrono::high_resolution_clock::now();
        if (0)
        {
            cv::resize(im1, im1, cv::Size(im1.cols, im1.rows));
            cv::resize(im2, im2, cv::Size(im2.cols, im2.rows));
        }

        // 	if (i % 2 == 0)//��ʱ����
        // 	{
        // 		flip(im2, im2, 0);
        // 		flip(im2, im2, 1);
        // 	}

        vector<cv::KeyPoint> key_points1, key_points2;
        start_time = std::chrono::high_resolution_clock::now();
        surf->detect(im1, key_points1);
        surf->detect(im2, key_points2);

        cv::Mat descriptors1, descriptors2;
        surf->compute(im1, key_points1, descriptors1);
        surf->compute(im2, key_points2, descriptors2);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature extract cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;
        vector<cv::DMatch> matchs;
        cv::BFMatcher  bf_matcher(cv::NORM_L2, true);
        start_time = std::chrono::high_resolution_clock::now();
        bf_matcher.match(descriptors1, descriptors2, matchs);
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "feature match cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        vector<cv::Point2f> points1, points2;
        for (const auto& match : matchs) {
            points1.push_back(key_points1[match.queryIdx].pt);
            points2.push_back(key_points2[match.trainIdx].pt);
        }

        if (1)
        {
            vector<uchar> inlier_mask;
            Mat H = cv::findHomography(points1, points2, RANSAC, 300, inlier_mask);//RANSAC    0     

            std::cout << "H: " << H << std::endl;

            // 		for (int i = 0; i < matchs.size(); ++i) {
            // 			if (!inlier_mask[i]) {
            // 				matchs.erase(matchs.begin() + i);
            // 				inlier_mask.erase(inlier_mask.begin() + i);
            // 				--i;
            // 			}
            // 		}

            end_time = std::chrono::high_resolution_clock::now();
            std::cout << "cost time: " << double(duration_cast<microseconds>((end_time - start_time)).count()) / 1e6 << std::endl;

        }


        cv::Mat good_match;
        cv::drawMatches(im1, key_points1, im2, key_points2, matchs, good_match);
        cv::imshow("good_match", good_match);
        cv::waitKey(1);
        cv::imwrite(dst_path, good_match);

        //�������warp��������imshow
        //��im2 warp��im1��أ�ƴ����
        //todo�����ں�ߵľ���Ӧ�ÿ���һ��˹�����im3*H2*H1
        //ͼ����׼  

        // 	CalcCorners(H, im1);
        // 	Mat imageTransform1, imageTransform2;
        // 	warpPerspective(im1, imageTransform1, H, Size(MAX(corners.right_top.x, corners.right_bottom.x), im2.rows));
        // 	//warpPerspective(image01, imageTransform2, adjustMat*homo, Size(image02.cols*1.3, image02.rows*1.8));
        // 	imshow("ֱ�Ӿ���͸�Ӿ���任", imageTransform1);
        // 	imwrite("trans1.jpg", imageTransform1);

    }
}


int main()


{
    SouthStreet_Feature();



}