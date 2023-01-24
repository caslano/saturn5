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
6M7mZVc39AILbVKOxVMjdPu8DpDuivFFfs5thB895wEHxDDLbnbyHJ6C8/VAVcRJTnNK5O5ozAYx/QWZXxgpm6vzfUPDgJaQmRzN0V8jXO0yLQzaMjBKshY5elY8IkdHhgBQgJAVYpJPcD86ihPMrhhy1UikmYxRGCQoZYwSrUanK8ZGjjpktyr/D+VkZkq7Dq+GSXCShrnQJs1qWhrrGoIfpEctRPhIGcf51jkZG/V9in67fETO90ZErpgCU/AK/Czt0q5963tmR2nvFbHT6CxMjjHsLxznXanLzk5rX3qzdDDxQGqWaflUV0JyDTDNL7+gTCc9zWpZluxKcBm9WWdn20jd+zJHEJK81rOJzXq8tcNJmucqw4vy9SHJwMG1ubF9QzHKgfHtqVDGrlgy6Trc0WNPrnE4pXOJpbxjBj99hjDJ1XMXzugihUU+M1f1Tf8bRuedqVs/JTBpAW+cNJY3lOkWTIEJ1AmPlOl430qJXvLji92FK/JzXCu+GFfMLiSVRbTa216Pv11JJBuIi31VvpnnKnanz4rBcrn3Zt1sB+mtfFqY6705oD+QXONza4dopEMs0y2bIpUllrgS9OW22eT1v6B//733FJT1ypvEBjLweeVU3S6KFV+kQhRD2xh6aAgn5kJKt5Eh52jkZnY2O11rofnfzqmnFJSqtrzAWpoylu5tvtQWEu45Ww5xe2CIqn54z+nwfp/K
*/