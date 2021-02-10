//
// detail/functional.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUNCTIONAL_HPP
#define BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <functional>

#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# include <boost/function.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_FUNCTION)
using std::function;
#else // defined(BOOST_ASIO_HAS_STD_FUNCTION)
using boost::function;
#endif // defined(BOOST_ASIO_HAS_STD_FUNCTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
4wwb54CqTBwkFop54nosrvSS2klVbAO45WEJqdpUYqeS03lv9JDfv4n3zJ/wNxUDipJ/ByRxD4hq3RzgM3VYuhwoz1XyZDj/fBEyCquGVQ3owS4L3YHHeidGVUAhUYtdI1UU3rNqCwqngD4JoWWXAVS6Mp87xoNa6qYDcysGgK/ODKWDTUxj4QhDmmw40UFuCn22tHZjTroCTjXde4su885sk0UpDicA3J62llVuDPqwZMwU1qYDN9yH1KPbQjeyzSbiCVd6xbwJeKY2G+r+7V6rgx6u/24P5uTUgvv3byorGTIa/vn9+3fu/buSoYxQ/Pv3btNtCjp7tvRkZGPLHZwq5lOPJudca3/lzlw3ytWfDoqeKF188cUXpyzDJU++CckHjA4hFrZEz6ypBgDPvnqjTSELxxNu2cCchdGF8TthohnjQznvgyX/0bqc1EYMIBJn9yZY2GiTqD2F4gTlhJwwHoXhoxt3ULzXNVzowxTbygMwYJiAQ/N0Am9bhy0sIGvPnf/Jx8fF3YfrC3AOHp35mPvRRIszZvNAXcN84oOY9EexEQ37iFdjz6SZDspNVfT9SN0Zx5A6yTkDOZISA8SVO0uCubGWa9YTWOxqTzXctACyE4MumTSUwFtT55G8N5GYMqtGiiRC3136
*/