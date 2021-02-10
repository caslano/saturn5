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
E01IneWVgD90ngq6Igg2qjNj04TkC9Bnw631EuGwRVka0JTxysDheLzv4Wg7k94eVRrjzCIuJZJoalmjHirjnYByo3eB8RDtCo0C/UVWIoSUkceg8oLa+T4y8iwEU4jacURQcsfZQritEAfhdE4v2qQhT0LsXtBnbckLcez7i7mhArfCwakx8SH3WnI8QWM5eX9Kno1ub66zq+lsnl9PR79/up2MvNT+8e2ke5F66s2vs2S89MZ9tysK1BsZu5rPZxkV3if6hLylLPEQWKQqYKm41qLudwoSRKeJMAWcB/r7kH1jUS39M8uuidw1r9un6shZtzaQxAGbVH64+BYOHTLAUYs/GlmLSmhnqcP4Ri6tbUTKdkTXIrS1DkzkOUEwbmvQ9nThiUvvuQJ3mfSNuXtBQhty9rckHc/YdCM0XE7iJ3ubvk3P/8Z6xICF8PWgWuJauePxQUAbtK2CB3vRGQqRu8Q2m43BLFqa+ilC04ztm8FwNqbSXzRSuTOp0x4ba68BHLQemEToldS++3o3Fu2u2ficbQGIF8CBZaNUG7Wfke9geTfRttttisi1tSo19SpMNmTYR0xf3g9GN3ez+TSfX91cDi/yutG50YXwQ+8vF5fZ6GY8m4+nk2SH1od/ALDz9F0I0aIqPcnB
*/