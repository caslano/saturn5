# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SLOT_SLOT_HPP
# define BOOST_PREPROCESSOR_SLOT_SLOT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/slot/detail/def.hpp>
#
# /* BOOST_PP_ASSIGN_SLOT */
#
# define BOOST_PP_ASSIGN_SLOT(i) BOOST_PP_CAT(BOOST_PP_ASSIGN_SLOT_, i)
#
# define BOOST_PP_ASSIGN_SLOT_1 <boost/preprocessor/slot/detail/slot1.hpp>
# define BOOST_PP_ASSIGN_SLOT_2 <boost/preprocessor/slot/detail/slot2.hpp>
# define BOOST_PP_ASSIGN_SLOT_3 <boost/preprocessor/slot/detail/slot3.hpp>
# define BOOST_PP_ASSIGN_SLOT_4 <boost/preprocessor/slot/detail/slot4.hpp>
# define BOOST_PP_ASSIGN_SLOT_5 <boost/preprocessor/slot/detail/slot5.hpp>
#
# /* BOOST_PP_SLOT */
#
# define BOOST_PP_SLOT(i) BOOST_PP_CAT(BOOST_PP_SLOT_, i)()
#
# endif

/* slot.hpp
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
*/