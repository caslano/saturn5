//
// detail/win_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_MUTEX_HPP
#define BOOST_ASIO_DETAIL_WIN_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<win_mutex> scoped_lock;

  // Constructor.
  BOOST_ASIO_DECL win_mutex();

  // Destructor.
  ~win_mutex()
  {
    ::DeleteCriticalSection(&crit_section_);
  }

  // Lock the mutex.
  void lock()
  {
    ::EnterCriticalSection(&crit_section_);
  }

  // Unlock the mutex.
  void unlock()
  {
    ::LeaveCriticalSection(&crit_section_);
  }

private:
  // Initialisation must be performed in a separate function to the constructor
  // since the compiler does not support the use of structured exceptions and
  // C++ exceptions in the same function.
  BOOST_ASIO_DECL int do_init();

  ::CRITICAL_SECTION crit_section_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_MUTEX_HPP

/* win_mutex.hpp
IjdrJP1+sQU52RFZTrF00iKPTuqlNCegmUhdSVelDKMFHVBlnucy1cUe3z07pL4oHiEvMN8M/Itcay91ZGgdEfguFz3bM9IlLWSz5fJ+H/CDAxqfm/b1bn6uWTpxVGbivhztspnVxSubl8Vks9TI5pSrLdFU2Rzpls1Sl2yWxiGbpS7ZLI1TNqGzZDPbTzZLm5HNUqdsbo/Q353PUTZLm5FN0i3Z3MnDSZ/OTcim0tR2PgfZLPWRzVKbbGodezvHL5t3qmxm9o1fNke2UDbfYb3TqAJ/jNCTsJfQLyaba41sOnRmH6dcKt0IM07lEt9K+9sHy6XQDDZyuUrid4ay+TdQLk2+sSGPjOiceJekR2lnxCMjubHxl/Q7REYGdaG8VEtGol4ZUZpdqY0yEkmal9IhZYiIiUdGAt5DPyn1TbHkQco7mGrJQx9fedA4ctD8+6r1rt3HJgO5PjKQF+BrNjfA12xDN6++GkMdOeuMTMx130uvcMoFtE59tXRd8/qKPA59NW9dfPqKfEZfDfbRV19Y17S+2rvOqa9yaduybuemr9aua1pfFZBu6atxMHaEEKivlCanW8v11c3rvPrqN1wz+krrKOgWv776kOqrz18Uv766ooX6ypxLSPe+gx4aQ9+UOe3GVTj13dAlm2VN24yTHmwzLukJ2Yzb5yrvV4nbjFu8Z2Y0FnifvhffRfgavC8vM/bWnmfcIenCu/EJfJPQ3iDvwfkE7RMto2eQz1FNzzDv0xslvkPeiwsIRu54L8ZzqJkHe4RuGbZlnfS9zKkn08HfCE3XUC/6M5n4g2mN77Gz+lBvr5iMNf9Oa8kX/Nrky+sL1Hx7oYe3LwcPZmzXm770PJNlu/py+nr/vqSM4L7UdHtfTl0fX1+uWd98Xz6+3r8ve/RNvC+zm+5L8wxxOlO/K6jv/isIs2LXyk1f2mVS110oV/rLosthdbCDWR/Mkmsd3H1o9FlvSc8z306eYcrpHdg3SyU94n5+EJ2cA2ZKer6s36zpgYxkqk6OXBvhpu/RyxbdTui+JD5tx0TaZHl9SVvxD/eKT0/mgEeDfNp61gDgwSXbeb28sl2PnthlxsN7/x7sku2Hy/1lmzKCZVvT7bL9qfL4ZPtwefOy3avCX7Y/PiBx2R4cp57o0Nt7vxk4kPoqTF/a7ze++yjQBp9vkfSEzrf47bME+6DXsxFH+zRmvkn5qNbzLamNey+6ShM74eJ/xiVNzrRY9BPYXelmzrncKtc6BvkL1jxXwxM0cs3k8fcX7M3DNZOnWX/B7rxzXHmnKY+6jiush2zP7VOE9hIjZ8iVhHf1b9x7uaV/8+eP3q6zLtY3qsf1C8kvifZmgm8QDsbmeMVZP886qMUlKyuKS4Q/fX9jzpKg8mnl6Wfm7KMSf4m62oXuI/jtY80w+XqbtfJPS/xXoUn8+7BrrpPR6JYvCV0D+4Apod2EfvRzO9t8fovwgPwd35yOrWffFLWvZ2ufmncj4Vf71LEXJmvaQ9Rm/htjQv/XvpXz5SzNsfcU3/GpHn/44qvdV7x8eOvXh/77zvzMGxS7PiSrpM1bT33zcPqP0zPu+8A9N5y/Mz+pUs6P8u+Z8uojZaN2ZTc88/rfbr/4//MskJ4RkffLWvh/JCTvv/L34/z9cf17TIj5a/6Wd0Xzd5ntb+MLudicWyHNeV4EOuO7+LjSDVc6u+/ih/XcyiNgD/DTYB9wHzgI/Ax4Mfio+d627rHrXn2t63vbt6tP1ztA+X4QOAD8EDgMvBcU/8VgHngfuBy8H1wLfhAsAz9l6tP9YnC8T30lKOQYrgI7gqvBbuAaMBMsBQeCa8FssAwcCa4HrwDLwXFgBaj9SmE=
*/