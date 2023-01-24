//
// detail/keyword_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class keyword_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  keyword_tss_ptr()
  {
  }

  // Destructor.
  ~keyword_tss_ptr()
  {
  }

  // Get the value.
  operator T*() const
  {
    return value_;
  }

  // Set the value.
  void operator=(T* value)
  {
    value_ = value;
  }

private:
  static BOOST_ASIO_THREAD_KEYWORD T* value_;
};

template <typename T>
BOOST_ASIO_THREAD_KEYWORD T* keyword_tss_ptr<T>::value_;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)

#endif // BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP

/* keyword_tss_ptr.hpp
O95UHnf8v6Z6ntmbZ14g1uNheSB+00BH4XpiIW6p+Y2L5H7ZALsF5c1zH+Hfhyc/U55BS3ukvyrKX/4QVaS1ShiKJcvOX2Eo5kg/iMn1fRR0teEEhlFanywadlrVw1W0maU9spHFWHnzr3SW7Fij6SGLzWJ9uQglgDQuzmPRkRDibwNpSuVqrGDk6BrnSYKHq62oRtKJ4OdQEG05EQMPKEsDKx2kYEMge891cLtr86CMCqkdiq3IujNxbSL8HbYhtsJ6p0O5FL6PWHsh/E3eMAmujFImVEhCD7e7nsVsnBYc4ct4A4jAU0IcUEEOyx4X4DiRr9ih/Kzauhg0qSOwsketvweDst21OfB8RVY21ZxNNWc7lAz4PmLtZfA3ecPFcGWUcn4FkdvsMlF4BkVej2uwHBESHPgEHtYOFqMT7iFmAhajvjdiMTq07K39h+mqmqgly5u30zIDUI+49M5gFQ3zsXCNZHm03LRd7zT5DrMaEy5jWlsPWvvHyP1GuK/MBTEWt6C/ws1wlhTK9lZNTSeHN9icS5xqPLdbV9Hqe1UV5ftp5YAZXJ+2FGlqiUoJt194lOwFG5FL0gbk6h5WZyYo69hymlHAxBHy14/q5A9B8ktwhOudwNd290E+x90kXCw3whN/T2PPVL+hjMtI5S+BXEH8BpfgJWUsN/PDvKO8i8ygoFBikvJJfWyakrgYHovzDssDKekAdxTd
*/