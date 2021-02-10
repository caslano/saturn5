
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_BARRIER_H
#define BOOST_FIBERS_BARRIER_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL barrier {
private:
    std::size_t         initial_;
    std::size_t         current_;
    std::size_t         cycle_{ 0 };
    mutex               mtx_{};
    condition_variable  cond_{};

public:
    explicit barrier( std::size_t);

    barrier( barrier const&) = delete;
    barrier & operator=( barrier const&) = delete;

    bool wait();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_BARRIER_H

/* barrier.hpp
3D5+0YNeJVbUfPg1+OVp8AQX6FfKmdmkhltqM/4howw6jU9hGp6PvHs9XxwhHW1J+Nda3WxgyLUVhcgYdj5sbKm0sBucrvAAVtiaijuH8XIazeJx7D0SMquanMNryqBlZPnGc8Eyhet3E+vTGzgsGfny7y0XuVkyDYeU2MHvLt67UTycj2fJOJp6rt9tedTtAluTKSlR6oS8pEKw4adJMovbinyQyu7WDNdXXAeeN2PYVtaFcmYgm6o6ItYJyYg8RCN0KdmaHqwd91JVOf1UkhMr1kpzL9uB5iiPEXCqHG9vZQLXyCmMPC7gohjvVx7Hk/T9aD4+Wc5Go3n/2cFFMaPq/uFaubkiQWFXSuSdc1dryb22nscGbuXgf+2/RbbzKzkWR6jwK44YyrxtN5MeyzJkuyCdaQftLtqrDapgwZrKIpJOTKhIszGWr1smXePYcOgISnkxymxLHnSBuDfrduRXaGoRwNwnXeTGMic/JJNkIVA9rVjzFjNHeEoB17Ghl0xIY134aRwDAkhBNdPY8e3ibHQOs7Nh/Oj4mJSuwQT6uEkaU/N1YNSBg8J0qew0ljhlbxVOKqb0J2ojClu1wYT6IopdY9Ysw29KVpsD+GaWMcd1Dolm0tRKW5eidDG8Hbimqekllk8JrFj2
*/