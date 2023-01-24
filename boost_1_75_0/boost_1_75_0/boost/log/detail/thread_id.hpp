/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   thread_id.hpp
 * \author Andrey Semashev
 * \date   08.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/cstdint.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The thread id descriptor
struct thread
{
#if defined(BOOST_WINDOWS)
    typedef uint32_t native_type;
#else
    typedef uintmax_t native_type;
#endif
    typedef boost::log::aux::id< thread > id;
};

namespace this_thread {

//! The function returns current thread identifier
BOOST_LOG_API thread::id const& get_id();

} // namespace this_thread

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, thread::id const& tid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_THREAD_ID_HPP_INCLUDED_

/* thread_id.hpp
begDz5jZ9R18xsyOF3zGzA4LPmOWWW2FBd8P43qIeJVsscbLS2Rc/phXzqz+HfVEmZG1HfxETqY2oLfY8+tCS+YsdmWImSNc12OZdQF+omXbbDNVFl8dcYUlj+zHxeq88ItiNrNFpo/jWhLpm9Gvh9lxzBxpOdHOhPF6bNSE6XlcrAzg9ZioDvKhio8aezrdNRFhmteKqDF7OGfnyXF8HcJLIVZE0KMQy0L0h3MBWeDwjwyTNFbHxEM6KyPjHc5Zdeg4p47Acyo1EXj060AdOrxiwphfbUwYeNZG6Q9ik+u3Z9CBtT8GQtv3zhiwdFXexvH7nvvkukkn6MiX557j4mU3o2SE5V13hfod8qhbpfCWF12Mc4OTcMtjLsaFDrc95WLOOR7wAIzxeNzyigtd67jlDdeEKy+4Jlx5v4VecjzkdVfF0d5udVmNl1uVf+XZVvHT3mwzmQr1m73YLja82U+s0Z+MQ9ulNk72DP3+E+Ecdm1MmB6/tg5s+1b18QHnrdV2+oJc7vY1fQ3FntMcX7HuHOi7baU1XZy3VtM11brU9lhqwh6wZHTIWajf70NHP3H9nu++2TpCcNJoiObnnybbjAOyx3GW+YDVBlF+Rpda4do3qd8OlpPPR7zd8a49rcw8YOc7PGU56yL7wK3Gql8b78vCgHNNXn8EvFpaON+T5VKD8/1QLlI48VqZ0fEcb5U8FgNeNf35Ftzs
*/