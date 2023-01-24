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
zvn3PVHv8ySTCYiY6Exi4iPW8YEXySx7w6TmfER0widqNZG/sl9BTu/T2NllEmoLhIp0LWxFTVjoCsoLTHDyeucVv8vPGyltO9T3ikLIzlDXMJELPJmbiusm9Jpks86Tf0MVTtylkil2p+7GiJKT46mW3kU6v7dSjlJCb7viM+2U27clQAG7hsfHR2C1Vf9VRdqt20fhlgMc8L7cEHy5jKens1sYMUeqz4JJ5sgnXmD9YWsUeH6DvXd98Xz34F6+7CED6cwq/O1besfo/iXK0G+jJQe0G27dtZZbKL3By8pKmOTDSEHqqjZbj/NlIOyLFzw/VBsfKsITsf86IpqkhI7UjsOV18oa87iq/abmPzEoEXu1j93qTH3b+zqZ6Mmf+qw1YsHJsZypLDdskmHQ8A/n3P/6kwtApYaeCLHQ4IXFP19lPdeDgLjsvf3KoUCH0Axnsk2Joci5gh/OlE/9hgNlnJ+PeLoJhnX4swYoIhJ2A5umy/WlHy08vzPIeZiko/UQaWtDmh5FRj/OT6CIAfNvcOrgdv8e+UfSnumK+3jHXlOXNGE/RDnT3uAQGjnTtfxomzp4swAGrt53ckMJ3O1beIaJZ+XSRDyCtcWODH6AmmxnpxiqbueKe+jCQMLZ5BxCu/vKkpI0Bo7pjXwd/QGsIiA76PlTGvM1Dh3+TeDJQn8ejVfEL71h9TaJdvdR71aAHa0MI0Uyk5rn
*/