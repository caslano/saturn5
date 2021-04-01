//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GETENV_HPP
#define BOOST_COMPUTE_DETAIL_GETENV_HPP

#include <cstdlib>

namespace boost {
namespace compute {
namespace detail {

inline const char* getenv(const char *env_var)
{
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4996)
#endif
    return std::getenv(env_var);
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_GETENV_HPP

/* getenv.hpp
1zBfKFYSC8x1WHT/2UisivCpZsjkMvsdirq2XxBnbNQgCwzAqDvOq1uBVh+IKqxp9iap8Ncf0+xcn48QDje/kMW0svg6qxnwrXOmhQHu1p/cTAfsd3vTJcGlawvde/1uyvbPp9iXiXI9IWZ4BM8iISJLxTnURZndTvnsjjAMYb5L0+Gy4pQ9tfDjHaEwLA8gVaWkD181vh6Tqt0PML5OAYqZvvhu6iuNm9mpbwYdeMF7FFQcM7UnzmmjhNPfjYQzKFZNmQdwvyajbnehlbhw1HYCYjHqmqdbo3ET3ajA7X4HIvz9HhmVxlPC8e5tVCfd6zqw78+R//l9OZDLsVkz+tY7IF5r1Bv/BcR4VTTBYyUmsNuD+vcBcne3bK7MLpRXs20OI1i1yD8n/p3kMlHiKVUOVOhuJX2Um741gwNwaHQyX4e+BvHM/zLq1jDhLKAjws725bDuO3efSyt32S4GAcboYFhc4uBIqeP9eVicjkqKY4jy88Hh/VTZ+fxtk62OXz4w5g5H+EDueN2SFj8yE3KORUMoBrFq4p0xbzJmKC7xR3fSLggRLNdLFQ==
*/