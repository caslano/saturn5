# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014,2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/punctuation/is_begin_parens.hpp>
# include <boost/preprocessor/facilities/detail/is_empty.hpp>
#
#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400
#
#define BOOST_PP_IS_EMPTY(param) \
    BOOST_PP_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS \
        ( \
        param \
        ) \
      ) \
      ( \
      BOOST_PP_IS_EMPTY_ZERO, \
      BOOST_PP_DETAIL_IS_EMPTY_PROCESS \
      ) \
    (param) \
/**/
#define BOOST_PP_IS_EMPTY_ZERO(param) 0
# else
# if defined(__cplusplus) && __cplusplus > 201703L
# include <boost/preprocessor/variadic/has_opt.hpp>
#define BOOST_PP_IS_EMPTY(...) \
    BOOST_PP_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_VARIADIC_HAS_OPT() \
      ) \
      ( \
      BOOST_PP_IS_EMPTY_OPT, \
      BOOST_PP_IS_EMPTY_NO_OPT \
      ) \
    (__VA_ARGS__) \
/**/
#define BOOST_PP_IS_EMPTY_FUNCTION2(...) \
    __VA_OPT__(0,) 1 \
/**/
#define BOOST_PP_IS_EMPTY_FUNCTION(...) \
    BOOST_PP_IS_EMPTY_FUNCTION2(__VA_ARGS__) \
/**/
#define BOOST_PP_IS_EMPTY_OPT(...) \
    BOOST_PP_VARIADIC_HAS_OPT_ELEM0(BOOST_PP_IS_EMPTY_FUNCTION(__VA_ARGS__),) \
/**/
# else
#define BOOST_PP_IS_EMPTY(...) \
    BOOST_PP_IS_EMPTY_NO_OPT(__VA_ARGS__) \
/**/
# endif /* defined(__cplusplus) && __cplusplus > 201703L */
#define BOOST_PP_IS_EMPTY_NO_OPT(...) \
    BOOST_PP_DETAIL_IS_EMPTY_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS \
        ( \
        __VA_ARGS__ \
        ) \
      ) \
      ( \
      BOOST_PP_IS_EMPTY_ZERO, \
      BOOST_PP_DETAIL_IS_EMPTY_PROCESS \
      ) \
    (__VA_ARGS__) \
/**/
#define BOOST_PP_IS_EMPTY_ZERO(...) 0
# endif /* BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
# endif /* BOOST_PP_VARIADICS */
# endif /* BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP */

/* is_empty_variadic.hpp
5H0yJ7Djbbd6o5qbuGd7XUvuVEo39gSuvUeCGyK+l3nv8NO0L91dQBugLpCQse9nzO7jI6NO9jXlPW7KZ8RqTJNyRs/sIoMxc0yGDEY7x1fP+UwZjnZ1eQHH9ISMVTMxMJ4HjrwBFh27H2KPe4P51p5d9dgUR+WgNfjFPsoCI1C5Nu75YUC/G1dn1zftO1FTx2gaFnoz/qtlXO/tlHs8t6o9Oil+CDLU/TLD/EzCNH3qwlpwDxWiZ9OnWUjnTasczziZL1ECgk/GKJhl478E3esj1t11boeoUzWKbP9AmXlRPNe6KbbbU2W250/6mO15dj85m6yXB1N6rFxO/FIBv4MjqA1ebsDUFThXb8sW+3SwtW/R9kkirGLUzMblRXyiEJxGRbLULTrAWTrAwiACLNYB8tQ0t4N4V68hIva9fZn9av38rjI160dn9if6YAlKReZfM4AH4dsLZiDMeTATYGbAhGCovrjrdTPPT9wV7121M+oeuXN+O0Rp4pe4RZ9Enwk+rT9vpnNCgPTn7XQ17RD9eRgtLJKd0YrJ1Cun0pnrgY/6qQ4HV1ZwFfLefkhY6otEzugFuXCi61a3yPhcjYmhGRbBb3PzBeZJbDjdIboQnILCnnfvAahUqvGEmAn9ACllwAbRjji/rbTisCcFzpKIhGTnL3f4KaIdJ5JlFNPwGJ/uDz4YLeN0ZTynaUdW17LtqTLLBlUKmTJIJ0dpRhxOj2MGMv3/xP7SRxJk/PaSWV9CmbAQRbeXfbk4zRSn8dIvry85On17+ZfJKjo4ZFTYM+yfpd2qi2WLvySP6onQxgtLHj5Wi8sQIn83wOpGbjB3e3Iq0C/2sfxZZj6gfn4BIXJfG2OitowNxzjjfH7i96mFWC3wAOgLUEANN3ptpnfKgVnGMoC5N+sRmAuV8WccmmV12gvwNzps91PkPmG7Hya3O2i5v0vuPNu9kdz5tvtmchfa7gjnX4H8P69+T5Wx/qOyLvX71sgvUT9jpF2/bucfkIRDwKE8mCl0dnkfwPCzm1G1kPqkQrbQAr7ksWwl4lQfMWpQ+DEhmtFKYuxRnaNZuMlumPdHaJ6BP7NP1PZ5bQQj0ylmAc2M8jQ8kGa+q20DgN7avQHjHtv3B2aCCU7wMdtnA3zoVmn704BpXeO7Le9WaBRRV3Ge5XXqDNSMpOkL0nS2kJMF2BEqJ9IOFm1gAYfQM+SonH8iVhXfm7mRTaUDWabqwp6crAfrQIFdnI/OFZGRPT7iWGybPzczxiH29CzoIk9Y4ib835+J/xe7Gf8vwyckDIEeWsI0d0QBjE8VZ+lrlPsM5mv87am0OJeRc4XllPeI4LyPJqbQhXFyQNIBtcNJd4WHgJAabwZQhdeFxeai7Ufh+nLrRawn9r2NcnyD7WbYjE5OU3DU0YZnpo1dljACVo5CwNdGwHrWEE6JBtFSoDUrSGf3eAvZJjZ5NbLzVFrtcbG2GI+onUmPUc0+ADqY4i3XPYVmtGgRBWwdg+HjwaIP4kgFMqC1H7GTi5CkWZTjzuhomkcXN+1wtwosMDPMjNLjj6ctumHraCdfO5bwgWwU6YIILrH0b4BLsvxZh1u/LrZkc8S5J8eRfi3Q/Mb2MrRAWzF+8PZxAIoGEBHKJF6DdRtZKVQY930HeT1k+Qi6PgQrJVikYInvSQScmzd6alj56i6I767Nb1xTdmperFeTwisxIzuzOkBkut2kLBRCe+NezfsfXUirhzaF6tpOFoim08FVdEvCx6EyI2B30ahzMp/dluG7EzAB6ECPcaCipIfwq3I7csdwW3CfblrmXimPTt0VIBKfGoZoxnEBUBwewD4AeYaf9gkS+9T0ZXL60eFEKuM=
*/