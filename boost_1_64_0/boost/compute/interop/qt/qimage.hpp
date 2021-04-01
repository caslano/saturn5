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
SL6EsWhObaNnNpc5HYNZtlD4ezw7+rbKfKYChLiJIT9C7ZISo2yoDL5BXncFAnO/BAxuD6DpZ3xqde1DaPOGlYiv3jwgoxGIc29sfKyw1dC0aQl+4VOaq8q9/4qzc6YbYab0HSxlMr/BMZCIT/slP9T+gFMnbcG0e3qfS25f2VjUZ0kVho0mxxgMVfPIbds8D38slyzZSFYdnx2eiowKQvYEGdmt2PgiLFlwzbnq6/T+iPiXU0e1qAQWHzRY0moDwCTAP5fmqF/M6E3P38/2er6xuisjaZzbdmR4VyBsCRK7XZOxHOLsw/3H6jiTS2vp6mxtzYci1PxUwv//61hTbWybDYL+1onzSR2FqpUndm0YtjIsP6B4aP2R8Vu6iBg6UlnQ/7uMknmwdKduMYmqFhdPLTAiI7sDCWIrnNOjPaqxJ2mxCQq64eBmPIKt2AmBIbQ9dExbfm3tXO0JRP44T5xvvi8S3GQgt4Evr440Ut2r0kx7ZHPH37UH/VwCzWCaabnY5q0zrgd2SteXOP/kjSX8GFMwGz1nSbtlmWikkACVC0ql+FcAjx/gyw==
*/