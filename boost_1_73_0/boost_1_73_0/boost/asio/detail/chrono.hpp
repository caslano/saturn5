//
// detail/chrono.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CHRONO_HPP
#define BOOST_ASIO_DETAIL_CHRONO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_CHRONO)
# include <chrono>
#elif defined(BOOST_ASIO_HAS_BOOST_CHRONO)
# include <boost/chrono/system_clocks.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_CHRONO)

namespace boost {
namespace asio {
namespace chrono {

#if defined(BOOST_ASIO_HAS_STD_CHRONO)
using std::chrono::duration;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::minutes;
using std::chrono::hours;
using std::chrono::time_point_cast;
#if defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
typedef std::chrono::monotonic_clock steady_clock;
#else // defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
using std::chrono::steady_clock;
#endif // defined(BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK)
using std::chrono::system_clock;
using std::chrono::high_resolution_clock;
#elif defined(BOOST_ASIO_HAS_BOOST_CHRONO)
using boost::chrono::duration;
using boost::chrono::time_point;
using boost::chrono::duration_cast;
using boost::chrono::nanoseconds;
using boost::chrono::microseconds;
using boost::chrono::milliseconds;
using boost::chrono::seconds;
using boost::chrono::minutes;
using boost::chrono::hours;
using boost::chrono::time_point_cast;
using boost::chrono::system_clock;
using boost::chrono::steady_clock;
using boost::chrono::high_resolution_clock;
#endif // defined(BOOST_ASIO_HAS_BOOST_CHRONO)

} // namespace chrono
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CHRONO_HPP

/* chrono.hpp
Q0VGv320OkJBcsc0MPOTZtjLcj6XLiI7DD5g2d467/JJRT2XfRJgM1vlGw2o+zST5YK9itgDGKKaw5VgR7qNeRS1/UkFS9l23iYQ1CFO06eV6iHN0/tCccpkrePXb5rntx/eLcxvt5v3CyO5eqF7woWGMaPfNhwCSnwm0Ljd0KuR8kmm4BziktZRlf9AmSX8bvX6NSioO75K8T8ioluCOX48oghzffGnc1vDFEVs7rnnhecqlFPHnUfw6cWi0ArSI4+VaHAaWJkiNml/jBefmd8R8JDo5P2gn/dIqq2PaBlV4WPrQDqyRLibYyTp/ML03J72NiXSSRebEYZZ6MFTyxE/ixMUu9LPTdysR9ogbhqbSjgG2QzoNPmaepBfqyRrfHJJa5aDOwoUvF5RSK7+AlBLAwQKAAAACAAtZ0pSQXUwpCQNAACVIAAAHAAJAGN1cmwtbWFzdGVyL2RvY3MvU1NMQ0VSVFMubWRVVAUAAbZIJGCtWWtv20YW/c5fMWugcBxI9KZJ0K2LduE6cutdNw4it92iLewRObKmpjgsh7Ks/fV7zp0ZinLstCjWQBxZnLnPc5+cTs/ViWk7O7eF7oz6wbTho3V19uVHfrJsiqvWq8vzaTbuf/qvu4VRripVrZcmV2cdvyt0VZmS
*/