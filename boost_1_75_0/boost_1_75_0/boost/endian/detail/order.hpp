#ifndef BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/scoped_enum.hpp>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__

# error The Boost.Endian library does not support platforms with PDP endianness.

#elif defined(__LITTLE_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BIG_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#else

# error The Boost.Endian library could not determine the endianness of this platform.

#endif

namespace boost
{
namespace endian
{

BOOST_SCOPED_ENUM_START(order)
{
    big,
    little,
    native = BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

}; BOOST_SCOPED_ENUM_END

} // namespace endian
} // namespace boost

#undef BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

#endif  // BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

/* order.hpp
vqGA3rxJAHpkXwXoD2/7h4BOjLQD+pHbENAXI6BTwhHQyazQVLnHblOA/uwuCegiSaD36GDeKRYpw7U0Or/MDFt+PCggXbHaVQEun/yMsv5NXeWXg/dnOTjvslJqfHQexz3lNhmN9wxYtRpdkfKIc63I8o0A1ndvb2xFnt4oV2TKE7Qiq27hFXkIX11yi74iO/KtFWkRUW9F9qWFrkia+Ii5Jk2tSLf8f7gi74fbV+TorbgiWBEx8DwamGsDTzpwZRLFxGhlftqiVqb3nSSCFst12aWvy03huC4RifaFuYoWpl+iWJnL6q3MlqB7361yZbqEn21lmoefa2U6bgDwti1obGWC6+XK7JtFK9P1Zl6ZQ+vh1bib9ZVJvdVamafC6q1M/9TQlXlOfMRMSlUrM2vCP1wZ6QOQK3PdBFyZRLSGNEUojZnA4hUFsm08BsL2peJm4GPxp5BOLAtmVfO4thAJmyye+ioHOSuOY83QoigIoijukPExtsysvEK0/DkeWkbhQAc566LoIVoD4AhSEr/k5uYfYfM946k5NMuFZheHNJuLzZZwM2iRLFpkpfUoduHqi2G6sionOesi8bJMyMNGUbRocHFicVPxsFlilpC1nPVKcVjn913ZlW+w+G1Z5BPtJVpqkujMqdGQM/jIQ6Q+zC6n36/FtfnIo3Rx/6OoU0zhy0mijXm4Karj47n9aH52LTzbQc8G87O+
*/