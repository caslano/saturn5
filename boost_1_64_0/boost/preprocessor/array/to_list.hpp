# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_ARRAY_TO_LIST */
#
#    define BOOST_PP_ARRAY_TO_LIST(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_LIST_DO, \
            BOOST_PP_ARRAY_TO_LIST_EMPTY \
            ) \
        (array) \
/**/
#
#    define BOOST_PP_ARRAY_TO_LIST_EMPTY(array) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(BOOST_PP_TUPLE_TO_LIST, array)
#    define BOOST_PP_ARRAY_TO_LIST_I(m, args) BOOST_PP_ARRAY_TO_LIST_II(m, args)
#    define BOOST_PP_ARRAY_TO_LIST_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(array)
#    define BOOST_PP_ARRAY_TO_LIST_I(array) BOOST_PP_TUPLE_TO_LIST ## array
# else
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_TUPLE_TO_LIST array
# endif
#
# endif

/* to_list.hpp
2JH4vxoMhR69w5g1Rofss4kl+xFb18DfpmCYlWDZInAa+toGO3RRCvlBeJzehvHHhs5HR5fQvyaLGLtUbPMU9uYlBihFHq6A943egb/EOl+lk88h79NVx7Zj377EL3VJJP5pzTitxleBeQbjExohM5Vgk0mUlzbYcvz/b8TFbmzLEfBJUn/GH5w2g/4lloh8jk3pFINc0p83idV3bic3SzzzyBvw40fsE+N961ns74x+dH2H/Bv4KJlxPsA45J0ODtlOPsLAkOjgT+HEiORVh+5FVq/hG9284Vbi6enYQfjfBf6U4t8wd6afXYh/TMDHPoDsFeCfJ76EnyS/dSl2rxt2tPe1xKb4s00fI3fEVVvb4sOZK0nFTpyHf+1LTrZZPDIGPm2KnZ3hxKZ1I1f+K3hSw49GgY2RgRnYvouYj3KhXxf1AXuTL61+DDuEnmfBBzfyfy9lnsR+DOmkyUdzyTHcgM/9KzINn58hL92sCe0rJn95Onwln70vFp6CG9Ju0aQ5996CHXx8OXxzkhsKAdPk0Wdk4qTe8PR59P8O7Bi2PpI+hbYEVxE75oIZ23egTy28czOO08l1VSHf5BvC4X8cZa8nt1G+CGx/CrqFr21+JuNFnyM66MgFMZUhUzk2Ylze4YxD3h4jd0auICaL3PooYjf8V78Q+M2LD8tpyybG4Erk2A5mHDkHv4W+XplMDNUN/341OUHaMhe5XbSY53ViPoVxu+B8xulbcobQN56HTee+ae8h76dSrhz8gc+1ES89iL6HrWNe5lX8czJ9moKfgt/r8YW9SsmPICcR6PpX5+KDySsl5RIPzEeGatCtQuLctuRHmafrm00+/2psVxE2cxEylI49wqY1AaP/gp04ZQ2y8zNzAMhiFDh1zGH6cKvIOdiMpeDssdjuS0LIW4DJohn33/B7388Ej8TDG3T29e7kZJnzcmCT11H3NOzalDXg8yng/S3447a63FkuUsr9G87FRoALbkxg7B6DP6XIM3mGCS3BhTcgX9iL97FZj44gL6KTsyoE07yAnclk7mcp/SWH3X0Uea5V8IVY7bse1BdNnm6eLp8R24ZG4L9pbxJ5qoG0Ydc3+DH8u/HO5CLsVh468t4ptB+s+xN4ee5t+N/myD56fcsKcOr72MgDyIJG/N8a23A2OYFd1LUDew/vnob/8ZHMYXVkngDMUwatAr3cvwQciT6/vRFZ5XdsNG1D/7bA8/27sRHI3njisXWNKQt/f6Sdreh/Mnm1O87QpXcq8T7ytQp9LYJXN5BL3xsFRs3lfdBB6AyxUnQ7bPnL2EHmCdti2z+GHy7s7agd2LvRzBdth1fo0/XYnenkCjrDq+HY5tCLiCMXkZPag/9hzA6QU39+A/YYfF5gzA3Qx0ExxPcDkfcR3r0+MslF/Mgb/nPCwbrYll3Mxw1mbJbAmPbcf0VXZJy8UU4CPrkj+rKC8VxHPu1SZAAb0+EcMM8CvqvQ9Tm0mX69vYq8YSZzgcTX48krXeXU6AvYA3zTArl6oze+htj6gubIzWQwLHnR0Pn4IepYuB8/SWyZCGauYAwqwTuD2mC3L6A/34N7toLPuHcrunPoFfoxE1nBp7sfwl6MIJ4ihm6Jbrz9OLn7DPQ2FTt8Mn76NjHnA1/qyz2f83xw0+x54CRynVXY5E74qjB08aIs9Ir+ZzLWRcSR+lyw4cvE6NikHYsZi8OMfSXxzCeM20hkMJa5PPDeZUYMtQU9Bx+GkXc/ooHJyBM3icTPvIrtRuZikKFW4/AJtG0PPvfTDziHnnnFR7CFH/VkvvAjbF04Pnk2eGIG8X86Y1pIn94mhgsFTzPeF8WKzOyLf70OXoLBv2zJnNk=
*/