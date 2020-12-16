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
9PJ99Hfb1xsXb9hT3awbhzs/xBzoxEmzTtx97btFJ67zXvI53VhtXrjn/i4MfNbhh/38Hynj8EgeeLkTJ7m19HhhpxUI3ItVnMuC8nt55JeRtbY4XB7M8JP8xJhi9j8xRpMD/5ukNHIuaXIcKw2S0iuCguTQXQpx0eAeo7aZGKv3FJpMJT/XVDlOablx6XhJ2JJj5EmGkYGc/T/WY3Fmjuc4RRRrcmYHbNoxZI0PJ8YaOZUmx6Vy+ZXnVUG3HMoG55cmoY2cdU2OZ6Wln3pJacjhzg1NFdXBoyfGHt/IefOP9foJWJD1rAgtrTpgklpfhDXvTYw8WMZ11+SEVpX6YRb6jkVF2IB/gHbS+AsrCbIosENbz8c81cXiElXMk1mL8ccsakHIx/6fqHJiK4pit8gKV5czN02CSCs6vyLiFoF/XOMPrDx2qjT3I16O/vQR//bhGr9tJTnddoZ2xfnb6aIdln9i3JOGIXWvKLTOLa2cn6bE+EmQcrBo9C6eI6U9NTmFVVSRW3hhcL1yrmhyIqv0Q7uwvbxDDnppY2fcyNnzU12OlyYsgIO7kZzGDtlCvVqqHKqeonCdzC+spTWSsXRuYuz84PzSCt41mZDtWf1U7w+V40VxGsQW03bUHdOYkIx20fJfWKFb2dQvs35+pW4pJ2gXox4KJ8qKKnHb8xCP32hMa01+vm/IqdwySxJ92Ne7Lfp7jo23+ZXhapMfR77N8jO1XjIrCaPEsXNPHyd8w8aELrF8LT5Wj5N8SJPhU91mYZiXji5DCw+2JNvF0ngjy099p0wja36xHlVjrt3RKiMHExlTTeV3bSvLwrJIw9RiSiDKLH/UnyRAg8HG3cxgMCtzQia4gbRFNmVVdmLngc3WrLXlZbKZbjWxUG3oc8dFrUyxRSPfDWn6UOtDzB9C/a3X52WNP7DKpLLLqlWdtP8C60GZ9jUj7TIKmetWgRd80KHOzw/5MVnv53uu6PNPFCZpUdFEjnd4J8amF6kaII80TCR0drCo9fNIk5OTYXecZplfmXKQndoKnptVnFXkXNDkVJbvV2UYVaHFk10bTj+W6mJ2aSAn5PnFmYW12UFrvHxQk0N1ShWa+7Y57PjkY+4l1PFy9Yq+PnlRaAdJSHLmqDgLrIPIrST1ND2aYyLr+Of62E1SGjGJU/3HMtVrqNZnLU2WQ+XyyjKuuvIj+JEpi7HLPM393JjfiqD07NhrBuIiFeN+xmjktjkxX82sJk+v12SFlhOXgR/ENCZXltaphBsOTWtkIpDjwMhTlCRhmfr5f6wnCnExv6r06V8ocqjN/ThzvDKoRH6UAkHU9AKFYKfKO6zu2c78wlibYycvsypt6qhewViJ5odUy8oO0FL2tK9W5XiBlZRuGvte8d/Kub9cA36hx6dPqyysvMS2Fqkzi7teYuWqWbEijkneaxqvbwVR4BU5VbJHFh8Ddi8iuxvZ6Bhr4egvjb10VHlFFtnWaXWeRD+jtWegvk0GOYdVOZ5nxU4QhJFrnQzcibGjJ07cj81yw6W1lRk5XdKkMxyIhd7CmFzW8sN8VRMvpUnXWh6snJ9fpdxwTmZFQYvi/BK9FY4x6cg20WRkNG86buRHBT0ixjrVRiKaOcYoT1pGaeQXkcWU6GpHH7LZd3H+/Np5MQmen15X5Pztl/qYjrI4CF36Y3qZtSlPGscl/i9sp7Wz04Ff6XKKJA4c20719QyZwyhkDthqO0WanNLK0zJI7ShW5Mg+i8kCQtW5XJPjWUFZJZHrRf9RzvDJi6vKHHxRleOkLMhXUKZewPbWcnbh/Lxu5NaSt9XiveXcosq4X0lHlCyzS6vizNnS0nKNn8c+WMt7QHm3iyA=
*/