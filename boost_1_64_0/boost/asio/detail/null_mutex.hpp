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
Y07rTr06fAYKOjwl0FU+b7L1F81rsNIxWzzwdMfSef4seh2/ytswWoe/92FrWIfXoU9nZ3Snt2GeLvB5mK9LfDmW6gr/CIt0ne/FYt3kp7BM54rdKX+mfYytwtdiWVwvr8Fi3eBtWKpbvPwsa2yi5vLZxq/TlO70QazXJf4iJn/IMfkmjNN1vhejdZOfwijd5oPPMec642MxTOf5VPTqIl+MwbrM38AEXeVbsVjX+UHM1y1+EfN0mtqdjsRsneMTMV0X+DzM0CW+HLN0ha/HFF3jdVikG/wQBugWH/gRz4vrzfhY7NF5PhU7dZEvxmZd5m9gq67yrdih63wvNugmP4V+3eY3TjO/pzkmn48+XeYbUNJ1fhzTdJtHnute6gJfjUm6xg+iqNs847zuNFZX+W7M1S1+x0fd00n2519hnG7wEdM9YzrPMzFBV/gfmKzDXzrfeHT4KszVTR7yMe8onedzPm58pwxn14txOrwX03S5ZGyfcI90eC0W6fCfsEyHn8NaHT7pk92pqRu85gLr59Thr/rrM8yDDt+CSTp/oTHMNLe6xhM+5bsj5pOfw2zbw7f3Oa8Ob8IynbvI9yPW6vCsi51Xh7+K3brFWy6xrnQ2y3yj7trDn8FaHX4ETR0+8VKf1eEC+nV2mbWEwY5T5VXI4hr5uk/7Poi55afQb3uxbI1gdNwXvh4D4hp5HXbaJ33G+sceneMTsVeX+EoM1VW+Hznd5oGfjXei8fAIrNZ5nojNusgzsUGXeQH26Covx05d543Yqpu8C3t1mwd+zvrXGY/AqFgnPBE9usgzMViXeQH64/i8HL2213kjhukm78IA3eaBs72v4vg8Ait1nidimS7yT1GxBhrc+/nutFCHx6Gmw2uwVocbaOrwQ9ipc3P83rvcb7DJnrsrfMdhn+0lnoNke4V3YKwOL5tnfejwOvTp7ErjRF7neQp6Tnccvga9usZbMEy3eMiXzJvO8Tjs9NkiP4nNOvuy81esDfsU+DwM1jXeiNX2SV+xNjAgjsMnYm9cC5+Hfl3iy7FHV/l9X7U2dJmvxUpd43VYqpv8FBbrdFV3OmC+97Au8qVYptvcc7X1HOfl92CSLvFdWKhbPH6B94ku8QL06SqvwRLd4OdQ0tnXfBejrAt8O4q6yV0L3VOd53mo6yqvQt+HHYcfRlm3efzXnVcX+dPfMB7d4GcWmWtducYxME03+KBvuRc6z/MwWlf5N+jVbb7y2+6HbvA/qp5rnf+ONYmG8RR5JjbpMi/APl3l5WjpOm9EUzd5F9q6zQO/632iMx6B7brIP0XJuQo/8DmsPcN9WdKd/oumrl3Xnf6Kft3mSde717rEH/2he6pr/C8s0mmp30KYp0u8CjviunhPoMMfusExdfg0DLV/mX+I0Tr8Eibo8Cso6fyPutNZ2OqzJZ6DDbrC12K9rvEabNYN3obVusXPY5lOP/ZbFCt1judh8lnDX/UDKOnwETX3Woc/jqoO34IVOvwKGpr9c1zNrQ43sE+zP1PdNZ7tXMusYTSK5pNH3GQ8usFPoqWry80btuvCzbbfYpy6dqv7iaU6+5nzYtCZ8fd2dqfvIK9bfNQq99o+RV6Agu01XofFtrd4P5o6u813CnL2yfOHsc/2El+JkbZX+TYk3eJ9WKvTz91zTNLhN9fNmw7v+oV50+F/o6rDA293vbrJB91hPejwSvTrcBNDzVv4gNXWgy7yE9hhn+yXft+ioQv8H2zSuTX+eu1Oz9rZtq+1xhp+7+ni77vT6//gWT7Pdv40+j9izfA6jJ42nM3nButNh197t+9yXeaXN1o/5+g/ehfe6/fAFM8af3KLd4hjZn/2PY6tjlnlY+8=
*/