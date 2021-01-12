# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_REMOVE_PARENS_HPP
#define BOOST_PREPROCESSOR_REMOVE_PARENS_HPP

#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

#define BOOST_PP_REMOVE_PARENS(param) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(param), \
      BOOST_PP_REMOVE_PARENS_DO, \
      BOOST_PP_IDENTITY \
      ) \
    (param)() \
/**/

#define BOOST_PP_REMOVE_PARENS_DO(param) \
  BOOST_PP_IDENTITY(BOOST_PP_TUPLE_ENUM(param)) \
/**/

#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_REMOVE_PARENS_HPP */

/* remove_parens.hpp
tyHOe8rx/+Bsoacj/Nz+QUIu7ybkjdeDA/Lf7+fum6CX976XX08gTQ/h2N9GSB5ybhglpOc9Zc53vQ3xCp18Cun71xvmp3ntTpRt6CIs6uPnk/PxSxDm+LH5bpvOK1/fDfnTgyijohydvQZyiPjWzBLyV6pv6OYNtYSsvwq6RL694k7i+YvTtL+VkNvuqZBVlOePvFakx1EmviiwhhuQN6KOdkJn73ak94XPF2mCTDeLj0Pc
*/