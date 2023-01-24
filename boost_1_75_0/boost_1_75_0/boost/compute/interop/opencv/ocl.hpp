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
MNbhIcnQTSy0nAtvIYpv7k5LsnlH+Dxd/4VxtDd4Wza7vn9ddrlVui8UmbjTMZNOkj5S97OlevuPWgeq94Rh+lcYQ9aS/Nwzot6JR+J+inPixl/07e8obXqBleuxovOvzkt5+DVSeq6cDiEcteYFyB+zPQFRZkrt8x6w5pCSNEavllDjB26YzXYd9Cz1a9c4f+drW6n1a9DPtpYToeGjlE0Zb3yaBIG2TdfaxryO9JBLxSXKi7oC3DxE5ObKW9YzBgLVqjXYfyOrugi58Xycot+2aXaRC98joqDCpvmqMk+R3nqrIpWNkvgltsX+75W4IJPiLyegi/VjirGPDWBfPoevvAgk41P/BAYm3QYiIm9DfdtARwzxSljoa1JLm9j4RUHLiVegPko91EI0ayS+TeCYY05lKykFf8UknqaAfNN+5QV3XqQdev3kIeo2/X4mjYt9ZTzJ5HVq8+uHlJBDPLbY9afgKzt0Fwszdr+0VoHLIaVtXwB9mfgeEmvw3OuWZrtJhAb7P8wpSXKCkNxEgsqT5xoIvSotkLuGSB5SinZ6oGAC1cUCbErHWDXTe2oeLtVhjnT0u8aEzr2EmqDhjyiK2o5XEr3g18zWykFZI3KUB4bw+r2hML4eIJRb9xtfJf4GGKHCOcYVMo9Qxlxtw+ndSGNfWDwqSs7u9DuF9W1vguZxR9tF2OLq59fPli5ftBj2GUpNVOPxOixM
*/