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
jGh7Yoekt7d9F/T2tr/zUElH23Uuuv36e8xN7K7vkJZ9lZx+udx/9+v69ihOY7sI/fu9i8i3ySUun2s2jE1FmUu/YHv3WBNrvk0ur2nHqW+Tf47AwPZS/oZjhOO/YROr4vprCVf9nu042GBWuIujccifHzZ8FXFhxT3zu8CN9mk8v5Ew9+DTGG5q4sSlG5jdm4EZ6fd4W2Kaej4h3wd95N147gEMc3HkuCMW3BP0eAl56XbLLLCevzig5Fd0+sMGQ4kpsW+9WiZjeRB8L7dWmmVwz7Eeq53/MbEU+W5kJb3XMku9C2QtdWEedkW1T0+otlVYdM+z7TgNLZLEm6Vw/p/mbaFMUXQjlwXYcO1mU4hJoZZhwadzP+gWPpVpMoece481cif5rh8FdmnZ58hmbV5ktnDPk10eRgSx+0W/4PeWFwF1LLVm6rJaSfWOrbabWoGTdsmwLbPIQa5HvnbSbAb4y7wt4PPQTfIoSK0B8Lpt+lWtX/RASN3Czrpk9EgXO9Gr4hz9UXFFYvUf5KAU7SEHZTd2C3oEzMrixTkUNXNJXtfadqyo9EIvj2mTVfKyHAlJ0G/kItTatGlQwtTN04QaRTmUUuZl+QQjd1da+okTJWTHf2HpIjUV0G9PP+JkauTA0eelE6VpUiaFtcyLsUIogtyzPzbmSxDTI6Sb0Q2aMv+TkSPL1fHC+eH5ueWZ14iBseE7oZX1rJJ+9DhxfasvyxollTfWpsdp66G0u0ViJ5bdshxOIlemWia30iKKCi+hqd1cDydzOaefoMv+gq5LV/zovnWITEeykelOPsZ0JLXybCDsdZ5M8uE6uzBLNMyPZ9DqYLjVoa7Jm+ivW7/RFegp20l9vKt371BliWQtG/ilU9C2uDLAioTd6mNVbBHbUUg7jrXSht2vjuvRMijcNKLZLTqor9tjKvZ4Nw5tL3VLiyaWngAfe6X+O4dxGLup7fP3+snD5+jgQ/IR7EOnH2fkgvGy2EkyWWi5t0DL9GKvNb92XytrW1kaRmWadq3aH197nyFnu9avwPGCbuyldaZKgfdhq63iU8tPo6QkObDSjN6nz2t8dS03zHPbs302ch41sjx/doXtPSVrbGD4gxp9cpzQjrKCl52uG5wyYzrdfJwm0/fz1Cn90FpaXHitGndxSs6D36j4Z5ZZHjEZO8e7doW2EGfK4CnIM4cmTc7Rg6ULPW321Lnux/dpZ7vju17kxizlXCVZwA7VqW3L9+r+904U5WWZ8pZmhkP0A7xNCDzyneckiSBVQTNWv9AT4Fw39gqHmirc+/Zfwhmn8e1ktlumhW3JSQ/Z/0GcUfr+1vVJrRA6VsuEX3DkuSjK4ByNHDfvFi2O+Pgi2+3L3/0b+7TfvQyyuPALPr62+N3d5+KM0fNkJ3bokf163V7AUwayVyxrFL9NLOfkPn0ddCN6aORxXFcwKXqLSkzOjyOX1uP1fE1BGruhr/rpF9QFEfLyiHJYD8DY8UDOMa2u2OomDm05aWHW5dqtNeGeYmn1OMSTE3lF4tX1RGKm8wNcFh9g73u8uff5Rdf3U6tqfmqJRfOa1NaWDbtptSwt3CiK4jyLM7MP9rDabnrtXan70u/ofquBF7NDBNW1RsDozMt59YHHazb1dL9O6BavMe9RW8IuTt9PcieOnDT368Z4pLeoOmQws+bZufzTZxOvj2Llq00H8ZGIdunhdG/gNOMAmJ5ZuaT4sU/saWAgKtsj7I6vGhjTz33i0YxubMr1o5fjPrOH9gWOw25k1lfl2Hi4sOElNinaPf92SX6jdCKa/J7evcGY2S7seqG3MzGmb/1H2jCIFYPcHYQxxsm0IW7DmDbE65oYxG2WNsQ=
*/