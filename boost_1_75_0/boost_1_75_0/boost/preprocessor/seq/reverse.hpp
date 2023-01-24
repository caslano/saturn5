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
# ifndef BOOST_PREPROCESSOR_SEQ_REVERSE_HPP
# define BOOST_PREPROCESSOR_SEQ_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/seq/fold_left.hpp>
#
# /* BOOST_PP_SEQ_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REVERSE(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# else
#    define BOOST_PP_SEQ_REVERSE(seq) BOOST_PP_SEQ_REVERSE_I(seq)
#    define BOOST_PP_SEQ_REVERSE_I(seq) BOOST_PP_SEQ_FOLD_LEFT(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# endif
#
# define BOOST_PP_SEQ_REVERSE_O(s, state, elem) (elem) state
#
# /* BOOST_PP_SEQ_REVERSE_S */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REVERSE_S(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# else
#    define BOOST_PP_SEQ_REVERSE_S(s, seq) BOOST_PP_SEQ_REVERSE_S_I(s, seq)
#    define BOOST_PP_SEQ_REVERSE_S_I(s, seq) BOOST_PP_SEQ_FOLD_LEFT_ ## s(BOOST_PP_SEQ_REVERSE_O, BOOST_PP_EMPTY, seq)()
# endif
#
# endif

/* reverse.hpp
FSfqdtUw6n111Vi/KzsucGIM78p78bMAiUJtGgptZv7smUIGPMj5JWfhgrA7uA01MVf+4sDdNOYK0H/w2h7FApg8hP/6uufFcc39O1fv4Sn0nkRMu1pR2Hxbx1E5wN9iOxwLYPAw260yViJ0XqD4+ncG9pTZn3ChkJu955wbbflm3MYbgUefqsy6TKQ4jPXA9NjY2JgPab2WdUeXk0XCy183NT31NNf0UHwXk0itAgjONriqqSSHaKySb0Hrn19WxDNhRIA9F51QakMw0mhRmy7fdf+wXNH58kft9iZX6KlrPLSDoV0fFC0yRrThnWQbv9gbDBJKM0ZWtUALnojPVIiecW19qn7L7GOv4RMFlG5hNCQbv/EtDvbFTdF9KrltnqI5fQohCIK8hD6A1ud3bbHdHz1g3QUVn6oc2dkIgwcMVZng9j0QmmzLnalciQTEZk2Pfb8D5BxxG4De4IoCARjqloK4brLyyR9sgGmQV9UqZTwz90zNTKlFwGyup/NKzu6fwFEk3F3X5zYQdB14o11/uw6MjoQrHKVB8r47oHY9GxW41NT7o9wBIh/y5ZAUQST+kCsjnE2MAKYtjl2KdCrBABha6FTZ7QkghjRsHyYgjEXxiLBOFQIhhQieGT8Qnfl0+oEJj5541u6Ps43qECTpXuh4MMirZ+GHQWz/p7e3aaIINak2e2AFaPTV2V0aCC3L+fnG/82qaw+M
*/