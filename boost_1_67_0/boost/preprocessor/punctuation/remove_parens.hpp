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
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
*/