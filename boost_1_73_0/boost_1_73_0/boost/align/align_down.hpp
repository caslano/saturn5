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
QriLE4Vw5UDBK815Yl1qGloDNW2MqFS4ZsPsdceH0M11xaGo3PWUtt9z8dQk8tIk8tC4e2eSeGaSeGXcPDIJvTH9eGISemESe2D0VVDEsfPoekNzCF80GYA1jdvWAhVZ+cGbBnxm3zqX4jw9ox2ecZ6d4SdV7IddJKpzJcCW7sbLfgzHcQrHdgjH/QyO2xEc2wkc48iN24mbACzrsK2UHzuVuhrwjZ2dJXn8l58oNMkKRVhgI8sTZIXFyf8TZMU=
*/