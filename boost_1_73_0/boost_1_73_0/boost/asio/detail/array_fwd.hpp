//
// detail/array_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_FWD_HPP
#define BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {

template<class T, std::size_t N>
class array;

} // namespace boost

// Standard library components can't be forward declared, so we'll have to
// include the array header. Fortunately, it's fairly lightweight and doesn't
// add significantly to the compile time.
#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

#endif // BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

/* array_fwd.hpp
46vqohmDOP/+XGDfOyj0aPSYB1gn8giG38CzEtSHhFXmWUkvoTd050lOMJMyC4fCkm2AcRgpGEbEPlsfxKXzlCd1YsVimTmCR6WyOO9PkHDm47l18y/NDXjXqd1j4tkSyP+Dn/Ub/T3cP+11TM9p0Ny+m812c1RrtdoCdF7qfOwLUecza0VMWCf8s1AmOYfxcPcIlxlVOXperxRgj3gLk0jMt20rzD43hDI2nA7tJLNvh+RGqe2uHkLmaCBdXTrq7U1hWKY+hD6doqgHd55UHTyi96zbZpljUhdeAq/BVuRh/7S7qipQ7LeF+5RtBcQW7Nf+LTrV9DFTa592vy/feVrmTcZ2duRbT119s73+Vm+/tFv9GqN9ZaPMbyux/DQfUbmwCySk4ZV9xle9tT3+cOBAMi1d0/NcQM5HXLxvv26vr6u/UEsDBAoAAAAIAC1nSlLi2nhWgQkAAHIWAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9TRUNVUklUWS1QUk9DRVNTLm1kVVQFAAG2SCRgjVjbjty4EX3XVxB+Gdvo6cEmThAECBLbcGI/xF7sjnewMAIsW6JadFOkwktrOl+fU0VSrZ4LEj8YPboUq06dOlWlNnkjgmqT1/EkJu9aFULzl6f+Nc3toIPoXJtG
*/