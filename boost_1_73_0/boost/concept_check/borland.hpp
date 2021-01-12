// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

namespace boost {

template <class ModelFn>
struct concept_check;

template <class Model>
struct concept_check<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT( ModelInParens )                     \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =               \
         boost::concept_check<void(*)ModelInParens>::instantiate    \
  }

} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

/* borland.hpp
7yV6bzgQ/S7R+8NE9ATRB8HB6ENETzGJPlz0NJiKniV6NkxHv0f0e2Em+v2ij4Mj0R8QfTIcjT5N9OnwPvRHRJ8F/4r+uOhz4Xj0p0V/Bk5Cf0H0BXAK+kuiL4EPoS8XfQV8GH2N6GvhTPQ3RN8AZ6NvEX0rfAx9u+g74Dz090X/AD6F/qHo++Gz6B+JfgQ+j/6J6CfgQvTPRT+t6jf3JdHPw6Xo34h+Eb6C/oPol+FK9J9F
*/