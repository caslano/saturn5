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
Wriv1IIXD/aXXICOIxegIY+VkXeanvHj6bSOwAyKQTQToCBNXjrxOf+sG6qMTnilG6esdwguNFwN6GiuTSkG8z2Urg0qSMMky5IDlEE0+t761m4a32pAXKQ30pkmG8QyAe/E2bzm2hI7EtpJ/r/0erXFmgpVvZK6rVFLKonX0fbR1ADilfTROJ365QHtiPsFpuB+v+sFJOQKg9Im8dN3PW/Il6GsKCWUH03jCcuHUY/o3idlQz6yi0mGdmwems0pVt0tNTtfl0mX1tDw4vpClC/OYMFvMLueELXWjCgrNGYd+0qavGzydBAeLrNUNaQUE4BaOjX0yTQbf54Mr+MAMH4mUzd7e00hJaiMbgal7BJWI+22Ei/gVWixW1M/YLkD7mGuB4hpCCKoAJI2LlkbbWgYRjTIlT0iHhDs4N5hao5eaRzWSCMB5RtazKfH7Bl8znb4xA6ZdoeQcr6bHN7D2FFtwruVxzT2OHcpm2JSGzzZKO4ASYVloaOUpbWyDWBQgP8zAp7280YrEdeRnyUhocVYODQ3n92Xj4dzIWf9MPYPxoYfZX5WlYJH0Mh8Le0DsZszKJuNZ5fsxEOC3wrED0TpunBkGqUlwXa+Won6NGUT40TAEfYdpeZlJ2H//HoHVMgtFWSyg8ZK1wSP
*/