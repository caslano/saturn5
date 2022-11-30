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
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
*/