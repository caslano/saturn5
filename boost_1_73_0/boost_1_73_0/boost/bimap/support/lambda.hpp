// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/lambda.hpp
/// \brief Placeholders definition to help in bimap modify function

#ifndef BOOST_BIMAP_SUPPORT_LAMBDA_HPP
#define BOOST_BIMAP_SUPPORT_LAMBDA_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/lambda/lambda.hpp>

namespace boost {
namespace bimaps {

namespace {

/*
boost::lambda::placeholder1_type & _first  = boost::lambda::_1;
boost::lambda::placeholder2_type & _second = boost::lambda::_2;

boost::lambda::placeholder1_type & _left   = boost::lambda::_1;
boost::lambda::placeholder2_type & _right  = boost::lambda::_2;
*/

boost::lambda::placeholder1_type & _key  = boost::lambda::_1;
boost::lambda::placeholder1_type & _data = boost::lambda::_1;

}

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_LAMBDA_HPP


/* lambda.hpp
qQYKJhCHftaGSDxkxw3gFd6MnjIPF7pZlii2g56bnBkDfYiB+YYWtIiC1sAJM5D/drxJOA3de3hzAv9VwNDUIQbTf0DXLsxWzjXdytXRbCS9RvbEhkm9GTJn5d1EeebiUjcsgsskYlOeEEEsJtOq+7xlEnbpK3dN7hfAbWDjnphgLAM0rw47vWaDwkQkCWbYGdYTyvyYzr0EgSPXFAvnjxNiNhFu+jhBHeNFpuAGPG2D1oLdn9sGlS34dQ/ZfiZkc4qIbSiiqK02KKf0pbVax3uYBFOF+HxzAph+BvrE/Ps+C7YwAZhiVYqyqYIBiei1obmh1mvsm/K/FkzdIBT+R3jt30bNdslEfl4hlq8QzFdam4zcYcOaJk/wMEPOSq/V2O4rrJbUrSBEL7Lwqx1Wctr02kqlZ5lZ4fSVrqtw2uk/qeAWx5GjpIPW8cd9lOI+zDOsycXHRuJ/LQV2fLiXipRFeQqSLF1MMEio/1PIGHhL8tvUXaWUoNwE3i6TIE9oRMDtbw6lNJ7SQGFF8zYisR9Lua9T1pdYENm2/ZsLJGa4aELLKS/o6uVkbBkvXmpRE2BjnVTCOLpv0RxP4PikUGqTnUSaRlqUyNZQpMqEPYtewkitMjWCAlJ/QXAsEC9BPacLU3TEVpx9kXrY
*/