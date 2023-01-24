//
// detail/array.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_HPP
#define BOOST_ASIO_DETAIL_ARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <boost/array.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
using std::array;
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
using boost::array;
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ARRAY_HPP

/* array.hpp
u8zgvp4TaqGd/qBLN5vUL2DYP0mxb4NxBZJJUSZgbiiXTZJ5dRZSN6qzsC/QsBDRl1VVbj2C3m7fh2zWJOsR0bqf/ltN/62QrARv0UvhpHGCPtN3byBJKgOArXtsDvLRm+pRH6uOXsoWSCKHwJrO1DfCA4zel2STdEr1x4PVe6vVX4PqSu2yiIRMSkfwTfRElsJCwYmRknDC/0JD0asTrfttDIvww0HeuhnnDt9C1/pG3ygJYM46GUiGr+qgvGfwo5hxFXCTxADMxisP0jjhoDv/CCdMRkw7HeT7N5Qj5MvzGmGpYMaNH1vlV3dJ1lpMaIUVzerbLH0zwIg3JKQlCTQHBPwn5dTJhMdH2kjLNCQBa637SnzHsZf19GWpaow8shQXr7L9d/BmPK9kX7WMv+f+OQ8+yHNPT2Yh8kvsTnp1q5hztigH7/KNwyvLLGt6uwP6Nd3cAYNgKrMGdHhkwXrSN5pMxaCKeHL1UlV7uPFmpj2UwySkp8QL51Lm6XhDGZeAD786XNMWOrzWDWCefzKNIkMUNpB39mAmMnPRUzhx196dQ3ObDPU6AtLuEn+4tFcyeG53ADP6blDJdxEpC4wGwXDTTOGEp8lcNFuH+QauSQY266ZkUra4OBxmO1e0loGCgVswCbexc2YVyJAHY4hpEk7jl94ZBjGrEf7VH8DTMU1rrFJ+I16RNIh+Fj6lN9Hvrp9i2GoRuhdF
*/