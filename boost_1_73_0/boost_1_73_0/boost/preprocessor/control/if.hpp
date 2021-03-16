# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_CONTROL_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# else
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IF_I(cond, t, f)
#    define BOOST_PP_IF_I(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# endif
#
# endif

/* if.hpp
hg0dnDsiK3NYtmSWWmDrd+MMtx9sZ465IoygKbdsghXrNExiGS0cmJvnyysScstzDt/n94v3+Fw2zYyb8v0Fvori8txCkmWJdtlAk9ZKmNfEDIfSlIuklWmTdqSdZ26SMpx5b6jANfTAtbDhLJvFeFSblSJ428oD19AD11rAXZ3h9lWMr6MLVseALNhrPDi7JblzpfYCroMHJ8NJn52aZOHsJGA7K+PWPfhjPfi7iDZdPfhjFfxxAn93AZtqw8o=
*/