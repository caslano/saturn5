# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2015.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_IS_EMPTY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
/* An empty seq is one that is just BOOST_PP_SEQ_NIL */
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY(seq) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_EMPTY_SIZE(size) \
    BOOST_PP_COMPL \
        ( \
        BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
        ) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY(seq) \
    BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq)) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size) \
    BOOST_PP_BOOL(size) \
/**/
#
# define BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq) \
    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq (nil))) \
/**/
#
# endif

/* is_empty.hpp
TjZKyF7VyZS4z+hkBULmUGVjSpmQTdRkoxVZriYrUWRZmqxYkSVqsiJFtn+6KhulyD7QZIWK7DVNVqDIntRk+YpsnSorHaPIVmoytRyLNZlqc5cmU212ajLV5ipNpto8WpOpNg/RZKrNfTWZavPBaYpstGrzDk2m2vyKJhut+kCTqeW4W5Op5ViuydRyXKLJ1HJcqMnUckzTZGo5yjSZWo6RqqxELUemJlPLcXiqKlPLsVOTqTZv1mSqfQ9rMtW+K1RZsZrvOE2m+mWEJtPapCZT0/u6UZWp5d2lydTyvqjKitR8V2kytbzLNZla3gWaTLUvoMlU+5o0mVpvuZpMtSVdlY1SbbFqMtWWnQ2qTM3375pMzeMZTab65Q5NpuZ7nSorVPMNaTK1vO0zVJma77OyDE8V2iVvQH4HiN6noIcXEd8W0Ps22jvoX6cIWZd43w3rbNJTn4uTnJ7Zdn+vTpY/+a3Q156bcjk9z+Fr73TxnEe8c0TnAv25fvdnCDwOndEN4WHq2Z0sD38r5OJsTH0XCfp90yGnMypZN0exXz1/kvOdrZOrloo4u9UyaOdOqcLWVC5XzzVsdGahvT9H8WlPObg/l2lnCsmQ832pJZ3slvWUe21PyvVo/5hjJTm/p/1bp1xenqe8j6J4HW7F7ysVPyr7JPGN+HlyW2XPpMv3Y9vk+03p4ptx8SHuG334e34/+asr0XvelMvfib8iMPTUujvx/CyWy9fc2Fr/iPWfbz9118lHblqx+C7M0yQ/9Nazcb+6dMGyM9/Y7/Scc9J2rBdjuPyMHGn/Jc1tIyxdbYnzPpb+DDnpT6pxZe9o2jcyPjBw+2XFB3/P8O4Kly+8++a/vP98fv6C5xtme5au3YXvga1cHs6+6ssFZ980c9Hw6belFMXvhM/juPzOB296ZutLsw7OTd2YNiLuQDWek5LcfJdnyNBL94/JPphtS/9Ny5vYR5m53O2sf+nmktPWzq25quXT959dg3UD6f8hqf+TjqKi506PGTFm1qDKE7BuJXl+/prGD7Z+k1X/+tyB9bcNfAFrJirXrJ+emvNI5ooHv57z2OJXr9pbj9MrsrP2sXtq/nHkfvvn625YmbD+pFvh03gu3zr3zy8e+fKX++Zc/dPMh5ec06f3b/BrSH/cgWGnNO6fd+V9Z87M2hV79WX4VoXy/du1O16cKHluX/DFxS0PDbkXshLy2+GWte2bBp4ydsu038U9seXREViXUzox+zK/6qhtP/fNhFOWBq5dwN/jJP3ntjZ9eq/3hI+OLF9V8eaJD+PD7Gbyz+6JtQM7h12z5HdZ466J3374E6yvSb5+xsVNu/pcs+bSe/pv37z22k3Yd1D62c/MW3LoxKanrpx91oNXPPHAZiSfwOX33r6m4nKr5fBE1+h1vvdG86/DSP7YL2ddN3LJxtZ3M7+978thg4tgJ8l3Lcm5OXeT79CCvasf//nqn96PtSjZGdjSccWXu0958c/LyweO3FGKdnIq+WHDjhmDf3X+uoRFiZtNGfvvfhx7Bkpn3pLpgTtHveO5/4GdU9avvrjp+/1Ng8WMk7wnbYLejbhep7u+U3f9gO56lXot709zUMeZZnlfnWKWr+/RXa/RXa/WXd+vu97Ln+oo36eJb+VeF+93eoWd31rYfB4WY2XzbcA+wAze74E/AfYD8gnFBuQT0AlAPgH2B54OTANO52MG8DLgAOAVQo/nv1j9Dgv2i/x5U5on8h9vlf+GwwRgFrAMmAOcKPItB44HVgAdwEogH7AmAfn4eiaQl3EykOd1FvBGEZ93oSrgWmC1sOce5dsb8d3T6xF/WyLHKv/tgCHAYcChwDLgycBpwGHAc4E=
*/