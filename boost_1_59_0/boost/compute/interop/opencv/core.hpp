//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENCV_CORE_HPP
#define BOOST_COMPUTE_INTEROP_OPENCV_CORE_HPP

#include <opencv2/core/core.hpp>

#include <boost/throw_exception.hpp>

#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/image/image2d.hpp>
#include <boost/compute/image/image_format.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {

template<class T>
inline void opencv_copy_mat_to_buffer(const cv::Mat &mat,
                                      buffer_iterator<T> buffer,
                                      command_queue &queue = system::default_queue())
{
    BOOST_ASSERT(mat.isContinuous());

    ::boost::compute::copy_n(
        reinterpret_cast<T *>(mat.data), mat.rows * mat.cols, buffer, queue
    );
}

template<class T>
inline void opencv_copy_buffer_to_mat(const buffer_iterator<T> buffer,
                                      cv::Mat &mat,
                                      command_queue &queue = system::default_queue())
{
    BOOST_ASSERT(mat.isContinuous());

    ::boost::compute::copy_n(
        buffer, mat.cols * mat.rows, reinterpret_cast<T *>(mat.data), queue
    );
}

inline void opencv_copy_mat_to_image(const cv::Mat &mat,
                                     image2d &image,
                                     command_queue &queue = system::default_queue())
{
    BOOST_ASSERT(mat.data != 0);
    BOOST_ASSERT(mat.isContinuous());
    BOOST_ASSERT(image.get_context() == queue.get_context());

    queue.enqueue_write_image(image, image.origin(), image.size(), mat.data);
}

inline void opencv_copy_image_to_mat(const image2d &image,
                                     cv::Mat &mat,
                                     command_queue &queue = system::default_queue())
{
    BOOST_ASSERT(mat.isContinuous());
    BOOST_ASSERT(image.get_context() == queue.get_context());

    queue.enqueue_read_image(image, image.origin(), image.size(), mat.data);
}

inline image_format opencv_get_mat_image_format(const cv::Mat &mat)
{
    switch(mat.type()){
        case CV_8UC4:
            return image_format(CL_BGRA, CL_UNORM_INT8);
        case CV_16UC4:
            return image_format(CL_BGRA, CL_UNORM_INT16);
        case CV_32F:
            return image_format(CL_INTENSITY, CL_FLOAT);
        case CV_32FC4:
            return image_format(CL_RGBA, CL_FLOAT);
        case CV_8UC1:
            return image_format(CL_INTENSITY, CL_UNORM_INT8);
    }

    BOOST_THROW_EXCEPTION(opencl_error(CL_IMAGE_FORMAT_NOT_SUPPORTED));
}

inline cv::Mat opencv_create_mat_with_image2d(const image2d &image,
                                              command_queue &queue = system::default_queue())
{
    BOOST_ASSERT(image.get_context() == queue.get_context());

    cv::Mat mat;
    image_format format = image.get_format();
    const cl_image_format *cl_image_format = format.get_format_ptr();

    if(cl_image_format->image_channel_data_type == CL_UNORM_INT8 &&
            cl_image_format->image_channel_order == CL_BGRA)
    {
        mat = cv::Mat(image.height(), image.width(), CV_8UC4);
    }
    else if(cl_image_format->image_channel_data_type == CL_UNORM_INT16 &&
            cl_image_format->image_channel_order == CL_BGRA)
    {
        mat = cv::Mat(image.height(), image.width(), CV_16UC4);
    }
    else if(cl_image_format->image_channel_data_type == CL_FLOAT &&
            cl_image_format->image_channel_order == CL_INTENSITY)
    {
        mat = cv::Mat(image.height(), image.width(), CV_32FC1);
    }
    else
    {
        mat = cv::Mat(image.height(), image.width(), CV_8UC1);
    }

    opencv_copy_image_to_mat(image, mat, queue);

    return mat;
}

inline image2d opencv_create_image2d_with_mat(const cv::Mat &mat,
                                              cl_mem_flags flags,
                                              command_queue &queue = system::default_queue())
{
    const context &context = queue.get_context();
    const image_format format = opencv_get_mat_image_format(mat);

    image2d image(context, mat.cols, mat.rows, format, flags);

    opencv_copy_mat_to_image(mat, image, queue);

    return image;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENCV_CORE_HPP

/* core.hpp
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
*/