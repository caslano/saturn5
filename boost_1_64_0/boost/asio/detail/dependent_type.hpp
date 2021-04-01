//
// detail/dependent_type.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP
#define BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename DependsOn, typename T>
struct dependent_type
{
  typedef T type;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

/* dependent_type.hpp
jqEQZApXsNPi7HosOLoD59LpWAb8hkqZZlbyqnFxAd0TWc6ibmRlJWy60usT20FtH/N+r7+GrApVOVyIUt6++nOJS4LlvRlHUep+KS2Q2RRwi9qenTyr8NDU0GBS1AQhpmFyqNLMtg1nMLs8SBvSmM1sSF7kmNuEKmnMrjs+JTdnxeTO4UDupjH8/EFGpqLXylygemvr1i4TbR9H9XhtMb5Qy4DQLajgpfAoi4Iv8/sVJ8N+JcC2881BUrfUN5zUvzbyrbP5kjttknZPxkK9lxcZP75E58XVjSPvJe3NA6qBfoWJGNn8TYN0yXRnnMfl2QI+oqIaky+9dIeTJB0NrNjdKgj7+9T4W7tcFg4m0hg58an/nolULp1adfqUtKBH/Nxp8XSAUscyfMnow3Vq0cHclTbI1PSBJCKoB8yCspqmVE9X6TDzOomvf+rmSlhY8KqbgsHXNUKdNSL1AjpGtfTZzH5kHbMTCy8yvLtECtYhwG6mBgmaJ4cfJWRZP8eTTjyWHulPm8rsxMSjOaan5Kl34EcC5RbgiPHCh3Lpk4e959StRWJKFTihjQ==
*/