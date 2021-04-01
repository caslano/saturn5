//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENCV_HIGHGUI_HPP
#define BOOST_COMPUTE_INTEROP_OPENCV_HIGHGUI_HPP

#include <opencv2/highgui/highgui.hpp>

#include <boost/compute/interop/opencv/core.hpp>

namespace boost {
namespace compute {

inline void opencv_imshow(const std::string &winname,
                          const image2d &image,
                          command_queue &queue = system::default_queue())
{
    const cv::Mat mat = opencv_create_mat_with_image2d(image, queue);

    cv::imshow(winname, mat);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENCV_HIGHGUI_HPP

/* highgui.hpp
2NPngelWu9WxZfr7nImv7adfPXzN28YJ/wMmvazO67QPW3t7gFQKNZi+F4P1/8bc4gJaumhntsoY8uMulj33PJxdmjTzCXFLmNQXxQ6sxMISG8XiULuqvWHJxkDDiO4pTFIgFjBr7dzNday6b6C3PuQOkx1wq+arz+C4rpBecl8ddPM7gIqlXzw9M1/61AV58mkjqbnsc2R2/cbOsJchf75mFma/5OdtTPnKvxYhoVgNU5RsHq1WwCianSV7sKVPucQBCV2xDXorPVtqna0CkjfiqZ6kpkoQ5t5yRRZ05bDbmksNnOtwmQwZUAbq28pbXmCXjjAHrMPEEb0yBX+6FOpgxYpdEIUFT+VqPNX0O206ZPZ6T4tqMWRX0TxCAVUPM3E3M/5tWAOJVWe8svs/SKyHmF23iaekFVIb76HrgCdPXvhaubIqlOcbemM1KPtmlSiMyZ9P3UT38VbmGKLdK92YGf/mBvNozRTIyKaNH1XbNRQRAZyEfG5NHh75o4KmWiKsWoIAMAfFIBMufCsE3IRPrQGIP5g5GKmRpBx1ltidevEFztO/GN2SOA==
*/