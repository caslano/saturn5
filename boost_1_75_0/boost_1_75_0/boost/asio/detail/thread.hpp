//
// detail/thread.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_HPP
#define BOOST_ASIO_DETAIL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_thread.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
#  include <boost/asio/detail/wince_thread.hpp>
# elif defined(BOOST_ASIO_WINDOWS_APP)
#  include <boost/asio/detail/winapp_thread.hpp>
# else
#  include <boost/asio/detail/win_thread.hpp>
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_thread.hpp>
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
# include <boost/asio/detail/std_thread.hpp>
#else
# error Only Windows, POSIX and std::thread are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_thread thread;
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
typedef wince_thread thread;
# elif defined(BOOST_ASIO_WINDOWS_APP)
typedef winapp_thread thread;
# else
typedef win_thread thread;
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_thread thread;
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
typedef std_thread thread;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THREAD_HPP

/* thread.hpp
gwYMlZeoiX+c7Cfrb4eBeQbWecMaTNTAf8B8svIroJumfAiMbjChcb9YB9huRkXth9Ap82mFspDkNbg1oZntJqNeDGbrM95odwiUFgSlGmK33BMGyp3XghK4jZ03AFAiNVCavmxnZw0AFHrOQKwHUFrUcwaT57tpdQa97YDywQAcrihyqdLuBNlO9WtAIE1u8vRt9JbeJ7AmZ1O+r+iAfnCgrT+uNpjNHHKfA1BUn9kVUzk+8q6qg8J/Zqf4Z2l3vdI7AdrIsv54ijPJ52zrflTaTuXI2VRjmlhRjr748ErwFeuu0gqo9rBHcqoHI2HasVBoZ3jotZlaQqq98ODzoeBr8zT3VAe2ddMWBrWv60J6MSw9GQJ9lK9/GVvCvy5+Qb8EA8Mc51qQ6/YcAaQvWih/Se0eXtgJY/qFp/DxO3w8jY9n8PEsPp7Dx+9x2NfU7W9RF0Mecu95ZG1oDorrXVxvvYvLhPRlyUKcF9ZXdche8qXsZCRNvO5I3pqMqvgo5lt6XHF6PD+mBJcaLreHvPovupcO414oIbjs9pD3UzVx8z7yhR36OZUkUC/LbeR/BuL68Q1cyaQcAAokT2IArV8+CiEesg0DfOZsVy4pcXSp+ydDSlo60GkjWaUXHSU3LF28rECVXI+1KsoR4PW4axjaYxlICu3a4mJbK1VS4kJLdfc8gGTpscU0NnB/rlxgp9sOMIAnF6eb+NRc
*/