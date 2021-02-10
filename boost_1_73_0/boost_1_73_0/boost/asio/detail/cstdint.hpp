//
// detail/cstdint.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CSTDINT_HPP
#define BOOST_ASIO_DETAIL_CSTDINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CSTDINT)
# include <cstdint>
#else // defined(BOOST_ASIO_HAS_CSTDINT)
# include <boost/cstdint.hpp>
#endif // defined(BOOST_ASIO_HAS_CSTDINT)

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_CSTDINT)
using std::int16_t;
using std::int_least16_t;
using std::uint16_t;
using std::uint_least16_t;
using std::int32_t;
using std::int_least32_t;
using std::uint32_t;
using std::uint_least32_t;
using std::int64_t;
using std::int_least64_t;
using std::uint64_t;
using std::uint_least64_t;
using std::uintmax_t;
#else // defined(BOOST_ASIO_HAS_CSTDINT)
using boost::int16_t;
using boost::int_least16_t;
using boost::uint16_t;
using boost::uint_least16_t;
using boost::int32_t;
using boost::int_least32_t;
using boost::uint32_t;
using boost::uint_least32_t;
using boost::int64_t;
using boost::int_least64_t;
using boost::uint64_t;
using boost::uint_least64_t;
using boost::uintmax_t;
#endif // defined(BOOST_ASIO_HAS_CSTDINT)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CSTDINT_HPP

/* cstdint.hpp
jjM0QGWGrBdd60Iq9DnBnckrGvZGbdhkZF3ijXUd6QKjIJBX7FChbk2dlR0Yq7ayLtJOLzG0V5nJQ93I8odATQxauLtrgtEUr5gpeRWzyjrcWrdREaym6P7urge9xPxsIsAdtoj1fLKN2qFbbIBzzJa6rwOGqHX+CH3b0y+mqoy012e0jXbJJUST0QPGdas2poiVDaybYoNeHTAmhfLaDRnWO4VRNmQ5VVcQG2pf5+2AP1WH0K8RP+nd7qSsJ10XrRrWcYH+Mg0G87CcZ6d8OsAv58mzyTMbR0nkfspQsf3gdSAHn0wYhJ8xri6tO8QbgG6cLlGG6X+e6aJCs/u8Y6ByDbq172+wFqZU/e+fVJ5h4DWxCKiQK+X2FKAdnqpkbH3TsM3XtqotpU1jK8EO4nqsl6G1C+ibJ1/UZi3tYyuFfq5rTGhVckSWQ0FQQhBMVNNS6Ja2wHTHI2SWlGjATMlLVarBT5e6QFtGZDC1ljK42V41JkOe6yPSbtPRY4/OXNci+wLnTu17em4/Y+BGRBmvaiUPifjZ1plpPcTS8ReT3Ktsq0iiW8beiPBINUS3101k30HW6FWuA4QevlZl2YNbVaC6eL1qwHJLNlgHDebnAEMqNq3LVc/AfDwM73/AWxYcyhE/Ft07C5wb
*/