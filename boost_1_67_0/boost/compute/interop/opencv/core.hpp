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