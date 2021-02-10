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
k8JYcZ3UCC0VmDM5ItcPQD8U8J5qgbntjkc+rkfGocQMWhq808OR11g+p8VVLPGi8KjS8EZaUzYuEBmnFx0Zl+xbuPd6qyTdigKOH9lP/lgkoai6+O8D+JgygfbWNqk6HUFxgriKu2FSS7grRI1ZPYbRDUMxbFbOPxyHLxWtlpsb59+qrSamZ3NVT2hHdK7NiN2wEiUKY/nW0A9Qrd0HF4F3tT2BrKpG1DnS5HC560f+YbVIepqBvC1PK7s0wQBqXTdzGkmKVI3b6j831OzTjELOHhR5WZRT2bJT+/i6gveG0zP0zmchy53z5wbsCccRg091yWh822RoPYg4eScq9Es/9DWm03bultihj8D5+D3hL2xDZMfMVgbnEfNPEWd1vigeJbqiEOg7tdhFytfCh+Zbzjbf1dKZZEYtCbWnSO9ts0i8KpfY/iQ4ZKDeW8LlpODiDhXvK/udE6XNZ3Jw14FONyt9z840hJdYqQk7X8PWCKdeJuhIdnoAT+ryqh0MdWtwuhDjZVcGleRUS0we/K1ay3Ztu8rsMB/UBtHrdy+1JSVzQSsYixN2S0d10RoaRV+dqO57HXlvUF3+XbWCXdlsltPoGMuV+XIGJj6uqHFW3fdf/yjbkCG3i0ZuH32V+c0BYHiLWE09FFPI
*/