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
WqtwxfdcPME5q1mrmVQ+v1gOTlqt+N37amNBQK60dqUSkhv0peC+eFvpXRcy5bO2BdosGdqIedyNo1713PUArG7WBf2Wfs+RsXLh0k3dw91MjTaGPXK/bb00zC7MPRoL1314unehEkOrw1wRkFj5YGJGhjjtWOEWjiQ0NJQl0kEMDJzn8H2RL7lQkYI55UZ4IJUkZweJKUgipx1pWFqphde5Be4S7Jw4f9Mp8F9IM7u8CHHO9yN8HVSCA1lC7AAX6zW5OOZZJrZy8unAa4foL8a1KvgW8SM7lG2nmbCPMzE/l5b0GU1L7ac69PZtT6gpRvpRBoF7lWC/1mH+/xD7JJrOssSt71QW7nMGHfOKPshJvlyfJiP5+/RAhi7m1pifwZDPujbfHtJMGjMfuOLInrgmxjRAThycXNaGjoJ41DEtHi+37CttyrZ4XQyXi1Xq0iDzmfpBd1/bwV/bBroYy5YsK78+dh1oLxKpB9vu2kmBIvv+5H6nZaxnLGj5a+G5mPRLjuXezmsUMwTvmeAWSTyzEpxVYUYE3L7JdZyoSIEVq3xNeoP5Hv+j2om2Tir/g+GcfrfcU/Z2OwhugLBWnJ/879nXFvGCPIAAU0CF6RX8RtNdGvY4znAfoaZrHFrbimofRP+j+WJkxWwuBZSEdwRqV2fFt4UZQ3VmLMgFLcyELMB7X+H6UCEYjF0HTmJYtSw6ZsgcK7G0HuV5
*/