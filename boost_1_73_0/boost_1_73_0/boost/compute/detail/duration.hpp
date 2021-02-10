//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_DURATION_HPP
#define BOOST_COMPUTE_DETAIL_DURATION_HPP

#include <boost/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
#include <chrono>
#endif

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
#include <boost/chrono/duration.hpp>
#endif

namespace boost {
namespace compute {
namespace detail {

#ifndef BOOST_COMPUTE_NO_HDR_CHRONO
template<class Rep, class Period>
inline std::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(std::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return std::chrono::duration_cast<std::chrono::duration<Rep, Period> >(
        std::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_HDR_CHRONO

#ifndef BOOST_COMPUTE_NO_BOOST_CHRONO
template<class Rep, class Period>
inline boost::chrono::duration<Rep, Period>
make_duration_from_nanoseconds(boost::chrono::duration<Rep, Period>, size_t nanoseconds)
{
    return boost::chrono::duration_cast<boost::chrono::duration<Rep, Period> >(
        boost::chrono::nanoseconds(nanoseconds)
    );
}
#endif // BOOST_COMPUTE_NO_BOOST_CHRONO

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_DURATION_HPP

/* duration.hpp
JjUadbF0O/Q+qAfwERRBc1WuhLsNO/eCkEtRVlBGbcBK/OL8+KN5IAjeqnIlHz+3ElPeBDx5GvFQ+3nHO8x5LaLd8+l8fRm/SbxRD+kAzwdpUSGMlqzHlYHcgQ/il5ygHVoYGowD/Wbn/dfx1eV0Nh5NptEg1JKaEUvUYs1hA2RXwlpWcwFlkpmwUUWBsnkrt6gb8nvgUTi0t5jJXFRFGWzlJtSvihnm0qVcyccQJWcXfYj2UUxh12+jih5FRY+gqq0p7UqQn5UgrTV2H9RwdBQprLVViuA+7gUs06ZsnIlwcF2t0GpJ5dAFIJZwG6T0aHgeRgb/zvtno/N+FLvb3/CMdTibr0n7ZAbVcuZEAMV8hzxpUEY+ZAxXlKVchR64tz8A6QaV7p2jxplX2A2XNdV/qaS9h8/VGjwELb1x36NZjuuick9L89StReqR3aERctqEV5PRlUM1lDryKQVfmdbgL4wPTcl40N/93PaQ/iDOl0kmeqWFb3RcI/iW4f2za+HlEXHXVHpf9XOR1gJGqRDBRdqUJlYqOm7m0yL2qlQkdXAOaIGjVj7BIfQ9ze+B9E4UFdKLeuXbNWrr82fNvSgEtwEQIguIkcG1QOxY3LBHBz42BA11YBxPpsmOHPyTCRK9Q/QQzdtQ8/bY
*/