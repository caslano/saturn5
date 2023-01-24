//
// detail/tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_tss_ptr.hpp>
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
# include <boost/asio/detail/keyword_tss_ptr.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_tss_ptr.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_tss_ptr.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class tss_ptr
#if !defined(BOOST_ASIO_HAS_THREADS)
  : public null_tss_ptr<T>
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
  : public keyword_tss_ptr<T>
#elif defined(BOOST_ASIO_WINDOWS)
  : public win_tss_ptr<T>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
  : public posix_tss_ptr<T>
#endif
{
public:
  void operator=(T* value)
  {
#if !defined(BOOST_ASIO_HAS_THREADS)
    null_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
    keyword_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_WINDOWS)
    win_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_HAS_PTHREADS)
    posix_tss_ptr<T>::operator=(value);
#endif
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_TSS_PTR_HPP

/* tss_ptr.hpp
RXxR4soVq1djQBlfWlRaurb0lpD8F0vivtLlv/eQPaNAS7fEv/RlMUVD2kmUAXGnlVRFq0Che1emKLz5vZBmM+2gXA85Xen9+GhfhjkTzzt05Hp8mQav2UXuONpO3XnIZ4GlxHijye8nXlUCHDsbEZfS4SITNwQVKUpsMOfL5jug5f8Wx3DL5LrFqrVIX9yhdcsXPDRHmlxu9VCvde1PaJpPuxxp22feKAan8zfhDJ2gndU8yTKnXPB3GTs+W0abmTIZgyAg8K16WjQpdFr0PsS3el40eZe6/7scN7o3fKjvQfPzqIeusDOjydRrHn8LOzPaGsX2mzfdgMdEkdGQ7/ZCbqhAA2wnHiLFiFN71a3bb1RkKreRe4Dli8RE728CgrHjGamFAYyZNRLEOqjcVDI8KcYuZVnJiWNUgdGeZTELZrHYwmkK1otcuIKVClfk3vfaFd+eZ3A1v1Gea+84NfSgr8oKg67ynLEN6K/Sb7Bz3HwP+V9aKlJh5E1ZloxAJkvmAhAeeq+d+cAZ4SEvAH/PcHl8j7pQyZYHLddMR4Xh4lyLWc6y+Imxo1FsNqBeAT23P/5Fu3Kw1sppdPT524yOxPPxYdDiyZdodAvvzXeT0RowfCwNdLvIX4y06ymGVJfwt2HBP/skOPeOehI84+n/FyfBO0fHXP8kOFbR8yT4zG5hljGQffes8LDdrqd7Pwk+5+nrngTndvd+
*/