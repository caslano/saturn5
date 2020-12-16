//
// posix/stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_stream_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of a stream-oriented descriptor.
typedef basic_stream_descriptor<> stream_descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

/* stream_descriptor.hpp
mSUmfohZH10m/j9aK5DKbzwYABbfpfcSaPndeKfamjZ7JrKEae4Z+KHEL6XkpgvNGzKGRGyxTd2vFpqjtNGxznpl1sf+LvGztJ6FDP2Z1oejbWyKPpcGXxWJr9N9V+iuVH+Mb6rUod2DyP8Q1n+lDrU+4alDSrNySGx/ovXdiXVotNIchaan3W6GyJJUairNZy4/+vXOTGb6l7jmmrh+K+PUKpHt5cT1WzMeXCbxZfDO1vLT/FAWUpdVlpyhuk+SzN1ZqWmZyRORJy4D+fPmccZQk8ejrjwaW+i61oXsA8bbruPxWvcYzLqxuVPAvRfh6puPDhN++TZhjOK1Uxkn7nLVf90Ol849aM+Z+q981JIhxgZ/9eb11VVV1VWuHXXTdz8r9I+HPhEKSTn8SOqVPMbsX3xOaL4XeiqUJHuktwy0aXQDXtNj3VPaebaxwx99nOWwwf4VbUexvvMb4v96aAt3YMTs+3/5bjvsc/KcsVJfXGKb9vNn4d2IRD2c/W5tU6Q5bt/+HpsmyczrlkjaV2o8PYPEj9D42LO/Em0rQyl/ymY35Z/ZM5LY35p+9NPImDeeMUrnKD923DNVEmp/X6w4JPti0nc2hrz77AXad6Jvwl36dtWhkaN0Hk8a4xWb7f2He00d4phFS3O1+WDQeT+NfMyp9SfGM8v0j0vF/2Bor5USPK8zfKVCMzcfGue6t9a1FUJzT2iPlkmJ4ZsrfFulP3evrS83NOeZsr9I/PeFPkjZy95AGnzuvQGz1r5YaB8JPWr1dN2dSJrm7sTd4Wi9HTxM95k3RMcu51r+Pf10LZ9laecdLhdLOnciS8hxPwwybGyukXdFrYsp77LpvskYV209xP+xOrhX+NOhc+8XyJEUx7i2Sugy8FMG2VE6y7G/fpPEV7CLU6LvIZo2+zwXUFdFhhzZ4yUF7ODqvDMXjK3XX049KwNzCPtWYXS/d2hWFOsG2rS6pt/Bfm+RY78XGdzr++HY97tS76Tu7wgnztF1vZ5w6pJj/V3X5QmnrrjW62krUo7UBd+1/yKQ8iVOyzdhLWXRGEv+XscNV7yRNlR+n7YhsVcv0w8z/obM+GvKSenHmvazQ/zfsZ7kf50vKJ+2HcMzypTljeJ/mp4ozXfO+ZTE34xtyjyR5XiemQtwaGuS1NtCbeP7x0mcvqfoO7fwT9dxli/275d9VHP3z3PRMSASn1eBQtPb3PdSJP5h8PQTWyBj6YPuG61zi+RqBuDM5Iv5P2AMFvonoA/LXYQRK2gMbqT8b4BuKZg/3uwptVv/ZoDUP/P+TFnhN2VlxmTKQsOljojO0CVhRpeuOvKGLsBcpWfK1uMG2HsO9zvriL4/6ftMKOF9Bl0q/RizXvAN8V+AP/bOZdNreRn64WaO9xWl95s3fkniFnneRbJ1DHxS4ifwBjRCw0L6/IsIaf995Cf3x99Hlo6hDY6NvY+M8b6PKM3usbH3kSmeMo6/W3VsUyHWhpPlvSOuU13j0vcRO8w9Nob1I65x+n6RC95MmRU/oGUmRxFccwzR3SvSviVAyy3GU2jKrVz86SG/cqiSuIfNfWnrxP8KLeynZk4fetAOW0PLH6V0sbAyTrT19BtPzNwmV+j6m7nNekn/XvVz45HE57rvYtI+6aTQrlZ/nDbb0DL4tNQ1O/esvyE877TG6DygOMu/jlwjdGlmrG4VfxPzkvl6DzK3JkjY68hWZL2N9N5jzWw3zQyRL82swWWJHx7xx3RWTXrF0hdZ4xhwztC5W+rIzOTpmak9At4HcpV+KfTvBTN7FWUmsxDkuVdU6Vo1Xd41PinvGnMzU9M7SHuPSbv1y3biQXeWZmTHbRUxNutaYeffO14=
*/