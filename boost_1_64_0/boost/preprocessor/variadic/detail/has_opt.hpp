# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_HAS_OPT_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_HAS_OPT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS && defined(__cplusplus) && __cplusplus > 201703L
#
# if BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/cat.hpp>
# endif
#
# define BOOST_PP_VARIADIC_HAS_OPT_FUNCTION(...) \
    __VA_OPT__(,) , 1, 0 \
/**/
#
# if BOOST_PP_VARIADICS_MSVC
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM0(e0, ...) BOOST_PP_CAT(BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0,__VA_ARGS__),)
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM2(e0, ...) BOOST_PP_CAT(BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0,__VA_ARGS__),)
# else
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM0(e0, ...) BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0,__VA_ARGS__)
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM2(e0, ...) BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0,__VA_ARGS__)
# endif
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM_0(e0, ...) e0
# define BOOST_PP_VARIADIC_HAS_OPT_ELEM_2(e0, e1, e2, ...) e2
#
# endif
#
# endif

/* has_opt.hpp
Z4ivBzG24U70xUWfg6S2OK6M0YzY8uZI/iDh+b7uXNGewJ3gC5gknR9oTIU7L2eAGSnX72u5pj7Ml0d0/fNN6t+II0xlnrP11OH/8dyclOhzc3T/GcrKekdQnsi8MknV+TWkGXmFzK1pqXWz2qkQXYOWivsEl5BlzOj2wbopqygvcGauJXn1EqVOVF/L8eQ66FnvdWkA90v4eU57i1oPxA+fe0l8HW658xQ/EJ0i09gkRJ0jZqehpaSh1I1fF5ZJ+DtmufFFnR9mx59qgvFJgjvvrVLCfxl1bpgdNxCn++UY4+2vJOGZUeadenGT5Li6L5PmeYGEFZrmZiRlFmwbmzI8txlnyfR9U7HbTWp4u3Hnc1Fn+ClzbUcpUNqLXQ/I02BL0S11ZXUh6RYZqu68x4DEl3KQNtdB21xd4jufcwOkR1nLaXMdpM05m48UOCPOqVVO0zuEttchatmjo/Um4X0CO0yF7P2R6MYZZ0aZgNUOw23trRucn1dovS+sS0cnvNR9X9LLov+m39Ff6ehTBvxycuckTpPwswLtffFis3aW4cPPnCpsaloeCh4zELF3keR1D8eItv/QPuQrJF6mFU/2/pB4rxKe5L53a4Z7Dj0pca7wnWMWu/uiNJU81Xffs7VDdD7Wd0CFt8e9nZywc38UN8NLY1VFUXEl7cBt+xM6y3xg9Yfi1An29dIW5De2e4yhcowz3WMcL/q1RT8tK1gOU6zzulrS2zvQyRcnOsvFZmnYXi1LxWa/qHl+mzzfJDayA14+plYVF3jXoI+0HtL1+FUVXr/UWWxd4p9irvJFs/8ZcZdhH6lXV9Zc172Ea7/nlp8x4e8HS6uj7cbqU76WPNU0zh4ja+jHWyBcSX2nJM6eE9pH5K403UdEdfqFdJIvHhqpk606s9F5NAOduDnnpyTWSIlrmZIY7xwXfT/8bRouwu7txHnMiZM0Z0mk3d/gb4b/Dfxb0ElAdyt0/Asjrn01CXucsCdw23C/0euho7sI9ySyp3CL+f4q7mm1sx0+g9uBexa3E7cL9xzuj6qzG+7S789rX9niJ+aPSz1S8JWVMftOu59zZbWzkOl5jkzOY+o9bM7sqyGZnreZyD5y3zml7U9t7lVde37tAfea7rUZ+ll33LW7rpHPx3od+ADXkXRt6hxcZ1JcFj7uKg/2sXRfUcddxIs57op2TUc/cmzFzZBp3nzt5yR8j1mA9fDxl9d3vyk6T8hb9FK962MR/Yt7/n8hOmvNWFMjbG1Cy4h+IB0OOEX2RnT7oi8lbrLbn78v/q2U70jJ/8MZ4e1T9gg8hDnTst+flmXUcZk1t1+unZon+zo5t17Q8CicDzfSccjWSB5ml1QWF4cqkBIzEWXo9X33i36+FV7tKLhl8oETji+DPAfMj/Mbds/Vzq+2t1NC4/z6OrdU29s83CccL+1USe+44vLiSu6kFXh3x4JpvvBvj/c1Pil0x4bEtPr/ekH7ZorxRW2HGj+4Z53G1+2t3LaYJTpTudLFRR1b2mnQd/9Nnlpe7V4DsiW8whSZeLefHE6pvCD9TL7cG0w9zcngj+4NSj04TbWD2GgVLPNDaGMXWmN/7Xd0zEb5WOO4qSrTPIf1ESdiw/k8qmW1GXcqfcTyUJ1VH95vM+JFjsGL7HLeJOHLactZUeuK+OFrNCLO9Q0Sfoc5T+OH1ZMVP8Ndu8JyurGTK2bquCnN1VkRNvbXeDH7obslfI2ZQy6T3L6lwrV51mmyf6qeQ967GV/MMIdcn5Oi1CfH0fr01llUe/2Ft84iDpmdV3usrr/5ztA6P6h1for2K51xtyGrOM1bA6SVzh3eseOLC6Qbi7hGeP3LVInXLlp7UJs=
*/