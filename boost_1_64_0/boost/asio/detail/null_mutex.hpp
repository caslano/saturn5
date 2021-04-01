//
// detail/null_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_MUTEX_HPP
#define BOOST_ASIO_DETAIL_NULL_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<null_mutex> scoped_lock;

  // Constructor.
  null_mutex()
  {
  }

  // Destructor.
  ~null_mutex()
  {
  }

  // Lock the mutex.
  void lock()
  {
  }

  // Unlock the mutex.
  void unlock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_MUTEX_HPP

/* null_mutex.hpp
4ehw60nDtD2z5z4vDw2mcrAjGMnRDyIgy1IUfRtBY6DNzrxQ6PxJOchqT9rtUT86/zhpw2kURBNFdUi2XJhI17OqBsWD8pD7Znpj1Bn4y4nxFLW5eg/aX0eWprLM0hrBycBt1pF8s2pjr/5OVkA2hpjeA/3BhpjDsVyAM85tEeO8paOYJx3QXPT/nNK+xSBaM8Ka5lubCxzC9wpOh3E3NpFKdP7UD52HJCj9ZibgsCJYM0UaB3OfMTQU4ZeALMn9FrRaKSMIKnHy7v9mox0yT5hguCtfHkmBk9p9DXlzhniXJ+hvrj3LKNIlZL8S8y1EGJCD0sq+E5XKQ1PwQMcry6WLzkKj5Djrnoh816hXCIYTpNCVEK1lcCeP3ZKcdekKptSAgJacoXxpp0dzLUe8VmkKveqvZzICDOgCd11hx3lyJyTXoywbWdBfDV4oeJLGuWGI503VxjbjLPrMY0yMfJudl6EwQ40pZiIyihjPYzKXfNcHng0porGPc5bWqcqnWlzGeyC2iS04cVqfA/4cBPlYqFm328pvxoGu1sRlcEqyWidSgm4DLxo9uA==
*/