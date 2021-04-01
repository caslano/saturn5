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
# ifndef BOOST_PREPROCESSOR_LIST_APPEND_HPP
# define BOOST_PREPROCESSOR_LIST_APPEND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
#
# /* BOOST_PP_LIST_APPEND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_APPEND(a, b) BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_APPEND_O, b, a)
# else
#    define BOOST_PP_LIST_APPEND(a, b) BOOST_PP_LIST_APPEND_I(a, b)
#    define BOOST_PP_LIST_APPEND_I(a, b) BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# define BOOST_PP_LIST_APPEND_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_APPEND_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_APPEND_D(d, a, b) BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_APPEND_O, b, a)
# else
#    define BOOST_PP_LIST_APPEND_D(d, a, b) BOOST_PP_LIST_APPEND_D_I(d, a, b)
#    define BOOST_PP_LIST_APPEND_D_I(d, a, b) BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# endif

/* append.hpp
oWw873fzgHHJ6C91zZUWmk1FsOx0FjHlrlkL7Fkxo7vW3qJrhbF3pF8cppJzcETLVCSU/iZ/Ezs76ZfDrbYOEhuZPyjn3BYw0wiy8Cf0en82fwQoR7Xg3rjiq5HNuVvBvic3zULwoig2fy5NPsydS3mfjZTZCpEKR8zzITSAF6lDHdm9pYm82OB66V4GfRSqos11TGLGXTwEZzLpna7NLY7vlio8Q9xvI99BIESBaTVuvlBV0DmaP+6OLUKa5HGCzAirUKSo8UuhEiVQLJNdGmjLB9jnIdibb1XtJOc6qg14crq78/xqiv3s0RqcTt8ESNWFGnvbkr5kbJDznVfe9oINyONTmA36L5dvgHbabEIT+xOpeO4LF8Wnk8eesSU3cvYR8ivyeiSSwkvorR6mVHrD+mc5cjuMqK/Wt2raDjk+EeE3iQqY36kdIfRCE2Z4KhfsfxhaaVRU5AgY1jqWF3TBm1p/3ijbgCmgXjkL2QqVm22z7OM9Sn/x89+4WcT0JwiXIHkzjS1G6FoljdVlDNmfOaMnpVP1JzJ/dxmcDQR/kVcnvFzHYF5P3A==
*/