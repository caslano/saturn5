
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FUTURE_STATUS_HPP
#define BOOST_FIBERS_FUTURE_STATUS_HPP

#include <future>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {

enum class future_status {
    ready = 1,
    timeout,
    deferred
};

}}

#endif // BOOST_FIBERS_FUTURE_STATUS_HPP

/* future_status.hpp
MMcs/+7w4RznwEi//sbK0zjb1GB+UZxV3arK3se9qfHLaUTcI2HPcKVKcw4ayWjOL8NbRXNmajRnM2sUe9fF1qjXNy2u0SXmRmsEJ5QyeWnr18g3zsX+CtmfJMlDSEAWtL7+NUhGxrl849hZPaSQP32anhay5bxHXdibtIWt+aXVC/viYbGw/zh80YUtaGZhI75uzcLOeb3ZhW1+/zx858XWZsFXLa6NqfHaoLqz9q3/dm0K+PoUsz9GZo0rxbXyR94YIZagfYS6BHk/t3oJOn4pliDpy4suQWkzSzD7cGuWIPy1Zpegmfk/MeJi82853OL82xrPP1BDiuvN/2b+xdyXzGNTDsuhbYYnvqTNAAsjDynhT++jpyVsVaLCxPp8ZVbX560fW70+U+vE+rjrLro+hc2sz3dftGZ9xr/a7Ppo9KcgPP2Ry03iyAR/VPZDPgv0p+TdmMxo0E0/2Exl09NM7rZb7WmmoHX9Iasp51Q10KMSyU2VTq/CImzWuVEJXSCDg3geCzXy+DAVBtIo7Js/9sTdySakT8Go/ky+f5ACKaSUp15IUklT1GWS26EZ9ACqvtJwrqLf2wOv0LmaI5Ji8VxS3vqY+qW/Ub4euJ/0q3Y/V3e/QHd/6Ix2/63ufpCunXa8vD/Sfthm2ox58EDBkJPs9Em2YSP5yBldX5IMFPd+TNoMzh7yDlK2OlClcAgMy73bzEHrO19h
*/