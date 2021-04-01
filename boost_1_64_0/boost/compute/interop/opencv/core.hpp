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
rWbN84Bj/Lng8FZTqNyz/ekrYWq8tog3JYyZxIuD2EkiDFagchwcVf/KXHz7VD6iyZCsXyx6OoJszJ2A7DshHyEYVqqZVtei88teNh6GkR4SHEuFiIQvbL95HMzzIIPXOQOH1kJyZUVDBByx1uallp4M/8Ly58OaeAQIN5sglq7cZh/T0DUWYZQVMSQqdLp3Cz6uKQv+YPjq+lyfEIeh8jSoIRrJKmDbQYUAoGNILVDOOBXYmqXz/BrnW/l9daMy2k21jHHzbffSIDroKJmNyHxMz3U7t4THoVyFFDuXG85svx4WwzggTpe7YGbehvqG8SnwL5gA/opfI3bVZ9iG0laiRa28LkIEj/0ZDKhxT9eCF6NxuL4TwNwKVp3IQqA5fTRj7PF0iR1QnE98enwdVcv8A/v1X4RPFlYDGbveGWNJQLqsq9CHKUOJ/LnE4lsI0uKjqk5GidTy2y4ockfMyChsIgIhUu0Whzmc+BnAPvY3lpSqUWGZfESb1MY4vdRSk0tpQZCzHIAEg/WmNh9/qiVPO/Ns0eJJ5E0ksoIwuAeOJGrUk8l7g+a/pA==
*/