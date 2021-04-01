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
# ifndef BOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
# define BOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ITERATION_DEPTH */
#
# define BOOST_PP_ITERATION_DEPTH() 0
#
# /* BOOST_PP_ITERATION */
#
# define BOOST_PP_ITERATION() BOOST_PP_CAT(BOOST_PP_ITERATION_, BOOST_PP_ITERATION_DEPTH())
#
# /* BOOST_PP_ITERATION_START && BOOST_PP_ITERATION_FINISH */
#
# define BOOST_PP_ITERATION_START() BOOST_PP_CAT(BOOST_PP_ITERATION_START_, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_ITERATION_FINISH() BOOST_PP_CAT(BOOST_PP_ITERATION_FINISH_, BOOST_PP_ITERATION_DEPTH())
#
# /* BOOST_PP_ITERATION_FLAGS */
#
# define BOOST_PP_ITERATION_FLAGS() (BOOST_PP_CAT(BOOST_PP_ITERATION_FLAGS_, BOOST_PP_ITERATION_DEPTH())())
#
# /* BOOST_PP_FRAME_ITERATION */
#
# define BOOST_PP_FRAME_ITERATION(i) BOOST_PP_CAT(BOOST_PP_ITERATION_, i)
#
# /* BOOST_PP_FRAME_START && BOOST_PP_FRAME_FINISH */
#
# define BOOST_PP_FRAME_START(i) BOOST_PP_CAT(BOOST_PP_ITERATION_START_, i)
# define BOOST_PP_FRAME_FINISH(i) BOOST_PP_CAT(BOOST_PP_ITERATION_FINISH_, i)
#
# /* BOOST_PP_FRAME_FLAGS */
#
# define BOOST_PP_FRAME_FLAGS(i) (BOOST_PP_CAT(BOOST_PP_ITERATION_FLAGS_, i)())
#
# /* BOOST_PP_RELATIVE_ITERATION */
#
# define BOOST_PP_RELATIVE_ITERATION(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_)
#
# define BOOST_PP_RELATIVE_0(m) BOOST_PP_CAT(m, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_RELATIVE_1(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))
# define BOOST_PP_RELATIVE_2(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))
# define BOOST_PP_RELATIVE_3(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))))
# define BOOST_PP_RELATIVE_4(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))))
#
# /* BOOST_PP_RELATIVE_START && BOOST_PP_RELATIVE_FINISH */
#
# define BOOST_PP_RELATIVE_START(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_START_)
# define BOOST_PP_RELATIVE_FINISH(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FINISH_)
#
# /* BOOST_PP_RELATIVE_FLAGS */
#
# define BOOST_PP_RELATIVE_FLAGS(i) (BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FLAGS_)())
#
# /* BOOST_PP_ITERATE */
#
# define BOOST_PP_ITERATE() BOOST_PP_CAT(BOOST_PP_ITERATE_, BOOST_PP_INC(BOOST_PP_ITERATION_DEPTH()))
#
# define BOOST_PP_ITERATE_1 <boost/preprocessor/iteration/detail/iter/forward1.hpp>
# define BOOST_PP_ITERATE_2 <boost/preprocessor/iteration/detail/iter/forward2.hpp>
# define BOOST_PP_ITERATE_3 <boost/preprocessor/iteration/detail/iter/forward3.hpp>
# define BOOST_PP_ITERATE_4 <boost/preprocessor/iteration/detail/iter/forward4.hpp>
# define BOOST_PP_ITERATE_5 <boost/preprocessor/iteration/detail/iter/forward5.hpp>
#
# endif

/* iterate.hpp
kUpsbzuzhskUm0W15uBl3gNRHuYPIC9+DTIGosky9PrnOZhNb2MzJpJsBgBIxHrnVhA4aOc/f6X5ZTtRIGL3iRMfKsDcrCcDbNB3Q9riDOlAkSUag+3lI1I/jzao+aAxPWK4tcp/NSNH71ceIsBrxsqlVooV551UVss/Z0jkJIFIm1QYEFF2cD0Tpf3pVj87i6YP/cwkaStJSXBXUBtlVttTRPOqn0DA6Uvbt04wsGecmV7lOItUlyyEvIyaSCu05sBF7ai2Rb7zuJg2Ri2rIj9k1tXIsbRjK1KOcacySDcfNUotwNi4tr5sbsYvqAwG7FJ/mhpLjwyHu/FKZz8KcdL3m128JH+HRlPi3/XmRfAJ7qqm0mJ2DT+Ehibv7GNfkYkFmQnKWX0gcEbBxmdoeh8xcMSt/FwKFv7VYRu6LviNkJCZSWRdVKDRjJeRjc3QLkptQobwoBRb1ALetPyTjYKdX9SAc0g0s02+z3zfTR48IlRrBHWDQJXIVj8nNEO9VvlHWkBVVRx2wnn/WJO+E5qulyw5bL0xUA3QjHIRruV5/2MWNoA1hxKVoA==
*/