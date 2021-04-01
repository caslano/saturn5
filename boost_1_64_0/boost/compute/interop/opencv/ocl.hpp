//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENCV_OCL_HPP
#define BOOST_COMPUTE_INTEROP_OPENCV_OCL_HPP

#include <opencv2/ocl/ocl.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>

namespace boost {
namespace compute {

context opencv_ocl_get_context()
{
    void *ocl_context = cv::ocl::getoclContext();
    if(!ocl_context){
        return context();
    }

    return context(*(static_cast<cl_context *>(ocl_context)));
}

command_queue opencv_ocl_get_command_queue()
{
    void *ocl_queue = cv::ocl::getoclCommandQueue();
    if(!ocl_queue){
        return command_queue();
    }

    return command_queue(*(static_cast<cl_command_queue *>(ocl_queue)));
}

buffer opencv_ocl_get_buffer(const cv::ocl::oclMat &mat)
{
    return buffer(reinterpret_cast<cl_mem>(mat.data));
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENCV_OCL_HPP

/* ocl.hpp
EMJs8czPfbCk/zeNN5wSvfDelTP3eRiTeX+2LNQOcf2d68EAT9rTJ5eJzdT11rfzy9zyuq081SS5+4L6ppam4FHOJAZZLMzMnajAIBi3+6ksKBq227rAf08kZdnvSVhWFWOTEM6/V4kxjR154JvsdZbXX7rWIidp2IDbToSBo9d8ArGcSK943NqjKn9yw7hxF/ju51/BFfqb2Z7SZIKqJ/dNe9xyhXy+3Uul9Egk/FVbTdL6upv6s6vZ9rjfS/jn6UmjQhappEoUshzfiUd7yZw6UWyl0rqumrBIb2XODU59olEFFCPvFY6oCkoAzWEJ/7AKHeeFGSUH40vxOZ8tdl+engTnv6LgVIV4OR4/ot6aYv/Rj/Ac5lMT48V135I7Y/OvVAg+J9rDPJ7qxJ5XLJdY5RAw67g1bBnYQaRFNGfrxTbLl3zXWAZ1vLU1cl6JyWOTNt8nyCoOJ4Ep13NDHdhS5EE2p/AkZDuEWPt17cMCDo0Cu+PeFZtC/Rl24+qBhg0P72CXSxbtUzSlV6hmxJ2LroY7bR/g9h0DA/wM1Zce+IK/Z/4i8SVKaw==
*/