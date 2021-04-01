/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_DOWN_HPP
#define BOOST_ALIGN_ALIGN_DOWN_HPP

#include <boost/align/detail/align_down.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_down(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T(value & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
ajsleVHg6CQ+UFfSUGgHKLXEkEcNw6zcYDsqiMs5ypZJTewwiiuclennUVFbdRhI8l2aP5rgY504lwN8t0jHl4qGxd8sWZckNgJGvYnrF6cmToihI3R5pPpN5IOz7FJIOhH8VPKPxb+8DpJqJiTwiwHSuvCDQi0/KHqg3fKsVeaBSLH/TUMCmd81O810oDXn/CJcZYbbh1B049WYYui5Vn1U76ZMISR6A8/MzKWYeNCOqE/0CH7HIIpfZwMfsvIfAU+yPfUKvjgTwf23oPyiaOzxUe3vRrpUwgORmW+ysuG8Ivlkf5rw6ycVDUhMEv0D5Ss1t058HVxSAB68gY1U2WHrwhLy/rMwrXleqpr2fwJjaXxG1GEufMZNGf4E5IDmcll04vw7mUuJm+05kvwf3KmzZIUvW/hKwH+QTp00QQcmd1VGglLMOgXuZ+zcGbh53bot7YjPkeZqMOMj9gA6irGEFhlvkuuPETSbGzoVB4XxaeotZ2OsFLuwcksLjLy8d0CjIz/pC/CQuK8ONlHwZXPVW5Pf815VOZDBGfdhcWegKvSaVfy63h4IaQ==
*/