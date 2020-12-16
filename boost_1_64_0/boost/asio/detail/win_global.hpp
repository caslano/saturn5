//
// detail/win_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_WIN_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/static_mutex.hpp>
#include <boost/asio/detail/tss_ptr.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct win_global_impl
{
  // Destructor automatically cleans up the global.
  ~win_global_impl()
  {
    delete ptr_;
  }

  static win_global_impl instance_;
  static static_mutex mutex_;
  T* ptr_;
  static tss_ptr<T> tss_ptr_;
};

template <typename T>
win_global_impl<T> win_global_impl<T>::instance_ = { 0 };

template <typename T>
static_mutex win_global_impl<T>::mutex_ = BOOST_ASIO_STATIC_MUTEX_INIT;

template <typename T>
tss_ptr<T> win_global_impl<T>::tss_ptr_;

template <typename T>
T& win_global()
{
  if (static_cast<T*>(win_global_impl<T>::tss_ptr_) == 0)
  {
    win_global_impl<T>::mutex_.init();
    static_mutex::scoped_lock lock(win_global_impl<T>::mutex_);
    if (win_global_impl<T>::instance_.ptr_ == 0)
      win_global_impl<T>::instance_.ptr_ = new T;
    win_global_impl<T>::tss_ptr_ = win_global_impl<T>::instance_.ptr_;
  }

  return *win_global_impl<T>::tss_ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_GLOBAL_HPP

/* win_global.hpp
PXbCppq8pKTXPUfuvEMSn7OvW9I52tEv20PPhdD5qzmYP/CMZdaSTuavZZljDo+ck95OLSS9RXnFpWbON0/iOJf8J/De0Vzz4cR9/KH30CD9DmOMfwfzvE4V+3QrhX+zrFjo6IDJKykp+6kzOMgrzS8074UXSJgC8hQnby26fkXjbidzRBspuJ3d2V/f1n5PODVE941pK7WOpNSjfjhl3amFlLWURYuQOhLIZwfcMo2OGXcegs/eXMuzJG0hCTle+bQ9pg7cn8AkTVlpBdeaI+NM8+27nKWlpRVB6940TA/T9qT8OfCN9jVZY6HhuIesWdV74YTpZs7rbC1hPvZs9/j0fTRsnKvtZUuR2+t5Q/WYFJm4Oge935eb937KLdjdvC9nhbz355tv7xMl/js8l3raBvmXi79dj0eL/32eSk/XoHjzTbyUf7C7SQf3V8bWU3rQ/vV03kWy/LEteCM5nzeSaO2fhsnsqe8VPzevFQO7W9HfK1pouIKe2sc3K3e/16nMGifuRS1N5P261x13jRN300WNwuI2MrudvMZXfhP+HNj1vrKOd4RcfUdIDvmm6dRB/a5p3KWOiWy1eQ6C61Dwuh2pI2Y+1Ljps5Vp3PKNW2qQG2Hleeqjz1P7E3W+Xr/RXY1ZZuv2eeHQ81Q4vzyvtMDSeSDXOFlle5mxyRNiX+BeX6Xt4GPiP1OfKSd8j8jzRNp+PSIyF1sTrdb6/Djhusl1fBJuenGJnnmbbOt8Ef/5Yj/PyHeu9/pS8hr+bY2YpG+bY3SSued0zLudT9wlTSFreXJPUj1zMYE+5lH4rP0e96KUubsTpDWsKJxdmlfi6gtNmS6TsHfG6D3RuLq6+iItc/XvZHTdLBH7C74rvAvVDb08L0vfwDT+Fo/dFpC5iH2UnOcVSLue1+7En2rpOhkyK+skfZXMbqV5CqytnsHImjWThdDct0sk7P0xzrUspw3WtvRi8X8wJvydswS/z8RvYMzTIWsyLzLtYKWkYytajt4zbacl+WziXWFtslJELjS9lmeFpDdF5B2/pBC/Jka/0nzTN3wlaeke86h1YvC7ab4VpH/vBolrBO/zjc37aZNX5czj8DDmfbadpLep+caQJvb3KNVNEcu7nWeWlreJr5x/zL0/VcJv8YwjfKR7f6gcf2LeuXvZ/tjC4jRp/Kv4tzR5GvSKyMt7RiptzvA++p4Rf4LlGuepTAkyF8i7SCVrUuLd76wqtxK59ukytmzqyEzoEiqzvo/zTaPyB9f7vcrs0TTRsy1mngDcHG2ewMTr76tpbLaoytVPqUxmX2fcsLidDBw68a9Ve7wFfZ339cUZ0fK9vK/myb/4ymh52njo2jeQGfL0eZ152uVcO2nxC65xh8rE96PtCqTvcX9sU/e4Q+Uy+mlcCYur/b5WUe9hNnLH2nLNli4JW6Nk8jK/n46llqa5xlKmLvRzxlJLnTVo4r6vnzP/taTc36g40ho0qcv3DXbr4fuD1OVE893FL89nfMh1W/bX8khYcn1YWRiZgf21LJotqYxWDlOQ6SDf55beH64rKx17E0u+mxlzTDphwuzQjN8yan0/j01KkrxYnQvKSgudvis3eHykbkUR3uPLw97jm1mDkia8RHzax9n2aVtD7TvD7Be/HGrv+UqofYexh+21GeBeV/Rn7l35NnMOSOh+G11n9VzYOSDIRz8HRP2jngMi/g0/B+S5IzgHJHegO/8vEl+VO/+6hyOQ/y1h+a+qI/9VdeS/6gjyv+VI8j/Inf+tgzGu/Js10ZL/G8Lyv7WO/G+tI/9bjyD/NxxJ/ge78/+q7faaO/+Sex03vhyWf+Sj51/9o+Zf/Bue/5cbkH9nHiA=
*/