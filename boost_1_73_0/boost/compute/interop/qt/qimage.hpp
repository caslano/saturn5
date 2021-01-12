//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_QT_QIMAGE_HPP
#define BOOST_COMPUTE_INTEROP_QT_QIMAGE_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/image/image2d.hpp>
#include <boost/compute/image/image_format.hpp>
#include <boost/compute/utility/dim.hpp>

#include <QImage>

namespace boost {
namespace compute {

inline image_format qt_qimage_format_to_image_format(const QImage::Format &format)
{
    if(format == QImage::Format_RGB32){
        return image_format(image_format::bgra, image_format::unorm_int8);
    }

    BOOST_THROW_EXCEPTION(opencl_error(CL_IMAGE_FORMAT_NOT_SUPPORTED));
}

inline QImage::Format qt_image_format_to_qimage_format(const image_format &format)
{
    if(format == image_format(image_format::bgra, image_format::unorm_int8)){
        return QImage::Format_RGB32;
    }

    return QImage::Format_Invalid;
}

inline image_format qt_qimage_get_format(const QImage &image)
{
    return qt_qimage_format_to_image_format(image.format());
}

inline void qt_copy_qimage_to_image2d(const QImage &qimage,
                                      image2d &image,
                                      command_queue &queue)
{
    queue.enqueue_write_image(image, image.origin(), image.size(), qimage.constBits());
}

inline void qt_copy_image2d_to_qimage(const image2d &image,
                                      QImage &qimage,
                                      command_queue &queue)
{
    queue.enqueue_read_image(
        image, dim(0, 0), dim(qimage.width(), qimage.height()), qimage.bits()
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_QT_QIMAGE_HPP

/* qimage.hpp
N7fWOPaIn/ZIlBWNlEOSkUpIVaQW0gBphvA0c8Zl3TaJeEPMCUnBsj+VePpzxg+Jp68hfBt6P9Tun0G7ZgG7zxNPX2v4qNh9e8+Y24r5rcTwtYhdEe5rY7mHUuZhawnLmljye4DGW03ZxbmHSeYeRtpLZtbdXxN/17uzmed+wvrBVHfE5wbiK/25YV9Reu4s623rZ95X9nHdZR13DbAGuSM+NxDf2a8vBL6r+5aE/YO7v10V
*/