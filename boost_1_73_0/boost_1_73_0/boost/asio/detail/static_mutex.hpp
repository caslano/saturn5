//
// detail/static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_static_mutex.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_static_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_static_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_static_mutex.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_NULL_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_WIN_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_POSIX_STATIC_MUTEX_INIT
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_static_mutex static_mutex;
# define BOOST_ASIO_STATIC_MUTEX_INIT BOOST_ASIO_STD_STATIC_MUTEX_INIT
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_STATIC_MUTEX_HPP

/* static_mutex.hpp
aVNfcJXaub7nw8fZ+/Z5I9iDnSNrnowGzR4wNfo35u7fzVn2Aq8/Aj3QvEMihi3iJevBTsQLdBtE1mqc+XWW7ZB58Mb8X+yBD5lfUiXYI9xAV89GrAsH3UEPjk5OvsMBHB8eH4ZwwZRACXOHaolmHcIZbyr9gm02kcXzENABk1FDlBbCgtUr98QMAq2lyFFZ5MAscLS5EUt6EQpcgbASEmEwmS5G48sQngqRF8TxrGuwha4lh4I9IhjMUTy+UlTMONArQhM3F9YRX+2EVhFJIzg0pSUKL86k1cAemZBsSTLMQeFcZU/jOK+NJOcx17mN87ejR4Ur21MsyEHJnkFXDpyG2mIIvi+EUnOx8jNFQcWqXkphi3BrhYQUj7UBi1ISFcEE2lfLCPM2mdB3QUVuhfOT1cp6padClx8aKUIiWdVGkQxFQD1cU8Ah1IqjaXqbQ78ptGk20f7nSrZeOWhFTqCTzGE078CSWWFDuB+lV5O7FO6T2SwZpwuY/IRkvCCu69H4gu5bkJIB3FQGLSkbEGUlBfJG8PNGECR36eQ2uR5mk2k6mozn8ANW2qBYK1D6gGOFlILKKeEguE3G0+RySC1fu05X2bIWknNheu09+0s/CgKhcllzhFv2B5uQqBAEw1/pLMkuRvO0wV94
*/