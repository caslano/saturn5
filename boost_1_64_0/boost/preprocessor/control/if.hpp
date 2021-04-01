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
J6yfYRzVRxNclatUsLY7Qc2kcHt1eCsqTa/LQx215mIGL7+7w84rDBzKvkp82zSgG0pOOPPTO9gdFnuB1xB2pomhrMN0mBbRy+ALR/Pmoc7j4YlFvneUDk5bN5xvUtoa65lrHkOuoFtx+pqBqVW1KW32V6oq7MGYxBB6+Op8c3rTHsDMP77lycRszCkMMRpqnSIYSvmMChNMOygP1C4Rml+pTiakINhlmcw/cMclcYyDf6nL1UbQE9brMXPL1p5zNJJQsR41wxU0pShveCAgjpaenaH/n5HkVtVTejVnODvJ6LyrHyzyW/md9/c4czluFM9wYvmfHilnv8clwLk8B/c1vq+I9g14klk6URWrA3lmKzoDhWO7Ymjd8mmpup2Oa5IgAvaftOVSpsv7Oubo0EZRScNUmq1oeTzNT5cJ1+81aFMtC2hUDwdqfiOWkjT3cFQGXksvxR2ERebSfEkO7+AZjso5yak9DChrmDybeajybd/neEQd5Sa1FBJiXOHMKzDhd7tm6+nkf5UgXNoAMd4Pojt8nAfHpoq70zgTmB1tY4aCOgJa83Ctbw==
*/