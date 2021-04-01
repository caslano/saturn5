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
FdIM/iJ+xhJnkFI0M3m2rOJyflKLLNrlQCtwvSOmEhnrPP1Lp+xuNRw6bxcUqbeQsNMyivtwj6KQNKle1gVuYUkWX+xPQ6xBif2ftuhufqQCeOwj2fj/zuetLDAFYQZWT+PXkt/eqDuQXwoJSs/RNQpAquFVeWJekx7AILVtmte4btclGrzKJBwgLmDSjw652jBVHsQAzRstlSfU0GU79ecNmbTilF560ftJ3AteSz0/artVkefPfkvebFCMYB3/N3lESleflXdSJQm5FrQ8HRHlXPf6aztXnaH/NTU64G2aEpR5+VvWbADOstDArdhHB+srxn1LCebxgoCevQQUmtWI8yeI1cKXL7forDbZff7rrWgms/ELAZJGFicUmbcROts5RF/3EPGZjiHpiUdoFnWBEhF4ZtDA44GEaV4z95153iecKdWUPGBTTi4pY/tYUiuNLUC8EGW0nYnS8nqKuM1Gveh/VCjw8pYeyo36O3HHkIRcdCd9AxAJRwHkO5lGLlFsANVoEvcc6+G+eMdHlRyqbXb45cwEcMboFyXO1x9bPEBAiiULAWWviQ==
*/