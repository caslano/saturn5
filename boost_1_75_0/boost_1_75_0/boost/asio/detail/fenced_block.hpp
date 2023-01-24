//
// detail/fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_DISABLE_FENCED_BLOCK)
# include <boost/asio/detail/null_fenced_block.hpp>
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <boost/asio/detail/std_fenced_block.hpp>
#elif defined(__MACH__) && defined(__APPLE__)
# include <boost/asio/detail/macos_fenced_block.hpp>
#elif defined(__sun)
# include <boost/asio/detail/solaris_fenced_block.hpp>
#elif defined(__GNUC__) && defined(__arm__) \
  && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
# include <boost/asio/detail/gcc_arm_fenced_block.hpp>
#elif defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))
# include <boost/asio/detail/gcc_hppa_fenced_block.hpp>
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
# include <boost/asio/detail/gcc_x86_fenced_block.hpp>
#elif defined(__GNUC__) \
  && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)) \
  && !defined(__INTEL_COMPILER) && !defined(__ICL) \
  && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)
# include <boost/asio/detail/gcc_sync_fenced_block.hpp>
#elif defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)
# include <boost/asio/detail/win_fenced_block.hpp>
#else
# include <boost/asio/detail/null_fenced_block.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_DISABLE_FENCED_BLOCK)
typedef null_fenced_block fenced_block;
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef std_fenced_block fenced_block;
#elif defined(__MACH__) && defined(__APPLE__)
typedef macos_fenced_block fenced_block;
#elif defined(__sun)
typedef solaris_fenced_block fenced_block;
#elif defined(__GNUC__) && defined(__arm__) \
  && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
typedef gcc_arm_fenced_block fenced_block;
#elif defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))
typedef gcc_hppa_fenced_block fenced_block;
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
typedef gcc_x86_fenced_block fenced_block;
#elif defined(__GNUC__) \
  && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)) \
  && !defined(__INTEL_COMPILER) && !defined(__ICL) \
  && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)
typedef gcc_sync_fenced_block fenced_block;
#elif defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)
typedef win_fenced_block fenced_block;
#else
typedef null_fenced_block fenced_block;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FENCED_BLOCK_HPP

/* fenced_block.hpp
llIqViMhqfvkc4pDXnncEIImNC9fRtDWCvnq42gQSvGf/MsGY5yU3zdOuiJyITqC0A7FMut1yGkNCPIpi6Nih5C4KA20Db51QlqOwQSoIHycAK2Fj+PzfXkULk1DofHlJcP39hJfXopc2BmG6Cm3q0zF43Dcrv+4mkpHjKt0qVJeIo+Hl/aQM7HmJZehR6mQ8hwVqk/JS2Q+Jc/OfEqejfmUWHQp4FoSmVNB6jPINeA55XgQKhkmRoY1QsYNgznyf7fpjtyLjnzH1cyR36M68psMjrz07I48gznyMejQ5M8n4nlPteDHQSXAnb9K7tzO3Pk5qiSAO7+97X/mznf2c+dPOvFqX3f+zE9P/w/c+c5B3fnOfu78Sd2dnzN2EHe+UtHduXt/lDu/Sol251mKLsXX7x/MnS/5bX93fjLKnXd8HeXO/z5Wd+cffh1x5+g+Sl/3gg+TG/7FoCh+nLh5rolGwsfK2e/SSHgebjtrlTbPhaJcY0tp2RoEkuhkIK7XDtwtUmN5zv0MwbqJJu6+x2gyB3wfW+GL4+6tRhmg477cuG2etBzCXs7L49dF4Bo4788Jo03gtt2Ah16Cej6AUiluto/mthXQJRv3wDV0yZbFbcM11Zmx3AMYZIpz4MKFdCvRzD2Ap2ZKNv+LiB7b/Og3GnLtCCFn5SVW5m6tI89Q1wdCrkMQCSFk+PZPQn67EUJ+F9t72sx58BhX
*/