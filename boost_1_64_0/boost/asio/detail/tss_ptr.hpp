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
J6D4jYFcb7YxcAlwPN/HBOCVwFLmxVsAvBXowv9rgDXAR4DLgNuBk4CvAB3AQ2yboAE4HfghMA94AjiDx93LgTHAWcDOwCuAvYFXAvsCrwJmA68GOoCFwFJgEfA24DzgSmAl8EFgFXAjcCFwG/B64E7gDcBngDcB9wMXi/tk/xHgtcC3gbdweR1UeG8LcDCXVyLVh/u3mm0x/Iz5BtcCuwMfAKYDnwIOBD4IHAXcAKwAPqRwewHeAqwD3gn8ObAWuBFYB9wEfI39R4Dbxf0BNwNPsv8LTvcfwMfFfdjQ3oFpwCeBGcCntLZFlkgbFOgf1rYqGgOUU24MTM7ukcPPW+6wRi4nQDlngHKuAOXqApSr9yG3SVt+AcopSwOTswcol6ORS9LJjdeWX4ByrgDksuR3ATyzcj8R42d3oPj9GXKZwC+BWcC/AAcAv2abJWeBM4B/A+YDv+Pnvu95nPs7cJlbadddAoAPAkP4uTgM+CwwHPgG0A78FNiNx+FU4N+A3Xne6QGMBvYEpgFbAS8GRgOnA2OBc4FxwAXA1sBy9ruACcBVwETgFmAScDuwA3AXUOjzMrAz/G8B/8HjShv4TwGj+L6S5DojZEOo3KjMY7jckDfZ3KkE9mH/APYPB1YBLwLez88JC4Eu4PX8fLAYuJr99wNv4Pl5EfAhDn8EuETcP3Ap8AngzcADwJ/wc0QN8AxwGVDc7HJgKvBWYD/gbcAxwBVAB/AOYBHwTiDyoPu6E7gaeDdwHfBx4N1cPquAFwj9gYnAB4DnwjHOnwKXZFSosgfuOJwSHUocrHZgbrR/DtZBWPyaBFcB2eVw2ZvBlbjVv80Zx2YPL6tDZ3umePO/h6N16eb/DZ7W5tigqd3cdL7WHYhTvzlwezTHNgfO3/rJZg+Ha9gW3zyubbd4uFyztjSfzzV3y/mzU+PcEpytmuotHp7XlVvOn82aui2B873u3vLfxfnauMXD+wp+aEvu1zNbmsf/uhbj3T64RriwmFAlDW4SXAVcLdwOuMNwp+GSYkOVkXCFcCvgdsAdhjsNl3RhqJIFlwe3CG4t3D64E3Dn4Nq2DlUGwTngSuFq4XbAHYY7A5cUF6rkwDnhVsDtgGuAOwPXKR5hcIVwK+H2wDXCnY1v4a5t+bX8Wn4tv5Zfy6/l1/Jr+bX8Wn4tv5bf//fvh+P/rygvrRIGAJrH/9+buffPJhL3/thpeePHjR8N232OKZPGjx4/Vsu/n8Jc/472QpYEZo2fPG6KyrufwmnVUzjur2TO4sKiuQULS6sR7LYVkIkPto2a+FNnjJpEaRQUXlN9Tam0J+BMMsrIfFimgWRmTB87bfKUvPGjx+rDczqIcHfYtLHjONht1/CxTEVyk40xsQ9wn+B+ddBeZ7NCkTz1Jwbq+F8dTeJ99uIeQ1oG3ud6CxsBOVb31kQ7AUntrXmfs0y4++8XnLBWeQdpK0Dl7Ttgkt9a5KdMpfxkRfKxKCr/x7257iAbfPkjLVn+A/ieBlnYCXA5vO8JhRdwmbs6WHPVrzexD/CA4IjQlQGVdBAc22o+WQZOfAhBf6c7H0/n1nCc5+rK2tm0svbiOM81sQ2w0cI2gMOhu6cmcpvXtrcu75gIYzmsG4E4+nJoJqf5ighz3WpZN8NgKPWzbrfJ0O/jDqhLGgdxGqkIvEClIrI3j6T9AqOOJ1H+9VONeWvr+yNdfdc3o76RltH+Ce7LlNNeXyZB1Hldkg/7JyY8/w8KmyT68mhGvQ9RdTTJawPysk+jvDyTl6bcr2rnVe6QbVK5e41pSMvQz2JamZd7hUN3T00s8zgf41q1iQ2BhwS/rL4cgixvdc46EeUOeIP3QzwDV4d8XO4=
*/