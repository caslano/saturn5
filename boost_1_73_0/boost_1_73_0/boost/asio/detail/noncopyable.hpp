//
// detail/noncopyable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NONCOPYABLE_HPP
#define BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);
  const noncopyable& operator=(const noncopyable&);
};

} // namespace detail

using boost::asio::detail::noncopyable;

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

/* noncopyable.hpp
Bd5AY6OM0vjQS+JKFIHP3S7W1q3rCZsc+Xm/Ob445aOXgIKxbaGRaaoCzC6EJ9f4WLBHwC24dlbI+FNFouMROAUnoxPJSO4LrmDz+Ox4S/vpB8ASqjTN0hxt/1dclaUIGDllJq7r6uzi4vTN1cfX52ciI/1ZPx+0cuP1zbU+243fg/jXWKKoBfLtUCRSLAToI7JA0wXfE5BLq1Xc1w72fKcUOkj+7kUJKtslAFuEn/xYzKVf/h7Eso+yBQHNludCeK9xmopswr/kkKKLVdHKCGwIqwfTAk1+5FNMsNsd5bN7oeaOgqC1kpnSMwzRYZLhJPvKWGUXyhs/3Fv7MCG5TobVfNY4Cj2alLUqkH2hrqAk/NWPL2U+1TfpCSguBviHyyu/EBnFOOSDZR8Ep2mYF4kcJSEHtdCZOt7Me1nvlcpHQscO9rYwIdDi63eeL9V8JKIUpBBR9r4oBoNQv6PwE99V5QI4di3CAUmOfhKMq/xShMUifv9mP4ZAKAdYWCD4lDRt8cVRyqsPp//w8ZLi7KEcYEyoBODA6K5NbCZdmYKL4+gK+EmvhPaflNMppA5RLSH6UM49kiXUy2LEn4P4blIOick1HwhWV9ln7CtJJoZayInUpR7J/LpdjjnSnvlwP/5487Z7xC88Iz4B
*/