// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_USAGE_DWA2006919_HPP
# define BOOST_CONCEPT_USAGE_DWA2006919_HPP

# include <boost/concept/assert.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts { 

template <class Model>
struct usage_requirements
{
    ~usage_requirements() { ((Model*)0)->~Model(); }
};

#  if BOOST_WORKAROUND(__GNUC__, <= 3)

#   define BOOST_CONCEPT_USAGE(model)                                    \
      model(); /* at least 2.96 and 3.4.3 both need this :( */           \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  else

#   define BOOST_CONCEPT_USAGE(model)                                    \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  endif

}} // namespace boost::concepts

#endif // BOOST_CONCEPT_USAGE_DWA2006919_HPP

/* usage.hpp
swwvTvBqXR0R4p/PZL3QV6nyD1ReOLPsH7HbFzbIORM2evobzhALP6B/9L5uspBUOR3PWUvtJc66cNZZFVkSHYktja6KdDqr7DXG+F9vxSDouny0yVV2nmodX69aM59RrVVrArnKUqui6oCbK62fKjuoJHzsXJVfY3vcH4EFHd6U8co7usdjf6eGr9Xnhqx6+zJnk93p+pM5beGBSHv0UGxvfCSxS6+l1dNOFD5htVO9o1wvqOGEm3Y2RrKri70S1KZa408wl9YRraVRXkt74E/wEjW1/V/p8uYq18fVFXXG7PUm1TXx965Pp+vPaeizsVknPxVVl7m27wVUWfop8ZmUgGZvb+2LTapOPWJvcprsMVVyXL1Ng1azqj5lxmuMXt3ojtdFVJn4lPtt489lf6CVmwAfdG6uCh/h/Df0E5PT/qtUuetTrs3dbSszSZGValKnrBU6rpZb8C0+wvyf/72nqESW0k8XWRn6aYpzc9TRequj9VZ3xPMVUCO+92bTTXSjuk8vtcb0cjWiOy3kSozBN+AI3sn43zmdbiKr1LUkr6Z0kypZkl+Rfk/jH9+DdzaNcPzzVqrsHolybm1/zO+IDzvvTE6qRbrRWmRnwyN6OFy0O6wOYspGw8ZeR315aZ6q28b9ebr2uMl/MMK80U+o8qb7jbPKeonDWJlGruXgYqOXeH/E2/bqnrDaMDv5C+ub2j6udzhLwnsd
*/