//
//! Copyright (c) 2011-2012
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BOOST_NUMERIC_CONVERSION_DONT_USE_PREPROCESSED_FILES)

    #include <boost/numeric/conversion/detail/preprocessed/numeric_cast_traits_common.hpp>
	
	#if !defined(BOOST_NO_LONG_LONG)
        #include <boost/numeric/conversion/detail/preprocessed/numeric_cast_traits_long_long.hpp>
	#endif
	
#else
#if !BOOST_PP_IS_ITERATING

    #include <boost/preprocessor/seq/elem.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    
    #if defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/numeric_cast_traits_common.hpp")
    #endif
//
//! Copyright (c) 2011-2012
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
    #if defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif
	
	//! These are the assumed common built in fundamental types (not typedefs/macros.)
	#define BOOST_NUMERIC_CONVERSION_BASE_BUILTIN_TYPES() \
        (char)                                            \
        (signed char)                                     \
        (unsigned char)                                   \
        (short)                                           \
        (unsigned short)                                  \
        (int)                                             \
        (unsigned int)                                    \
        (long)                                            \
        (unsigned long)                                   \
        (float)                                           \
        (double)                                          \
        (long double)                                     \
    /***/
	
    #define BOOST_NUMERIC_CONVERSION_SEQ_A() BOOST_NUMERIC_CONVERSION_BASE_BUILTIN_TYPES()
	#define BOOST_NUMERIC_CONVERSION_SEQ_B() BOOST_NUMERIC_CONVERSION_BASE_BUILTIN_TYPES()

namespace boost { namespace numeric {

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(BOOST_NUMERIC_CONVERSION_SEQ_A())), <boost/numeric/conversion/detail/numeric_cast_traits.hpp>))
    #include BOOST_PP_ITERATE()    

}}//namespace boost::numeric;

    #if defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif   
	
	#if ( defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES) ) || !defined(BOOST_NO_LONG_LONG)
	
	    #undef BOOST_NUMERIC_CONVERSION_SEQ_A
	    #undef BOOST_NUMERIC_CONVERSION_SEQ_B

	    #if defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES)
            #pragma wave option(preserve: 2, line: 0, output: "preprocessed/numeric_cast_traits_long_long.hpp")
        #endif

//
//! Copyright (c) 2011-2012
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
        #if defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES)
            #pragma wave option(preserve: 1)
        #endif

namespace boost { namespace numeric {

    #define BOOST_NUMERIC_CONVERSION_SEQ_A() BOOST_NUMERIC_CONVERSION_BASE_BUILTIN_TYPES()(boost::long_long_type)(boost::ulong_long_type)
	#define BOOST_NUMERIC_CONVERSION_SEQ_B() (boost::long_long_type)(boost::ulong_long_type)
    
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(BOOST_NUMERIC_CONVERSION_SEQ_A())), <boost/numeric/conversion/detail/numeric_cast_traits.hpp>))
    #include BOOST_PP_ITERATE()    

}}//namespace boost::numeric;

        #if defined(__WAVE__) && defined(BOOST_NUMERIC_CONVERSION_CREATE_PREPROCESSED_FILES)
            #pragma wave option(output: null)
        #endif   
	
	#endif
		
    #undef BOOST_NUMERIC_CONVERSION_BASE_BUILTIN_TYPES
	#undef BOOST_NUMERIC_CONVERSION_SEQ_A
	#undef BOOST_NUMERIC_CONVERSION_SEQ_B
    
#elif BOOST_PP_ITERATION_DEPTH() == 1

    #define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(BOOST_NUMERIC_CONVERSION_SEQ_B())), <boost/numeric/conversion/detail/numeric_cast_traits.hpp>))
    #include BOOST_PP_ITERATE()

#elif BOOST_PP_ITERATION_DEPTH() == 2

    //! Generate default traits for the specified source and target.
    #define BOOST_NUMERIC_CONVERSION_A BOOST_PP_FRAME_ITERATION(1)
    #define BOOST_NUMERIC_CONVERSION_B BOOST_PP_FRAME_ITERATION(2)

    template <>
    struct numeric_cast_traits
        <
            BOOST_PP_SEQ_ELEM(BOOST_NUMERIC_CONVERSION_A, BOOST_NUMERIC_CONVERSION_SEQ_A())
          , BOOST_PP_SEQ_ELEM(BOOST_NUMERIC_CONVERSION_B, BOOST_NUMERIC_CONVERSION_SEQ_B())
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<BOOST_PP_SEQ_ELEM(BOOST_NUMERIC_CONVERSION_B, BOOST_NUMERIC_CONVERSION_SEQ_B())> rounding_policy;
    };     

    #undef BOOST_NUMERIC_CONVERSION_A
    #undef BOOST_NUMERIC_CONVERSION_B

#endif//! Depth 2.
#endif// BOOST_NUMERIC_CONVERSION_DONT_USE_PREPROCESSED_FILES

/* numeric_cast_traits.hpp
HxG/T8HTuHh02rH3OkWVF6qFA0jmG8EyoYVrKBaRQ6JRIDckEPDE4N+F6DGit9/PU2iAhZRVq5Ddu+w4qi/EZcDNCS19MK1gWO7Sx/1wHy4zToWz491/MN/pQs36djMTGgdq1jebOwuNgLahBJZFGcXGvjRKJjhyiKH0CKfnsuuB8p/4yjVwq6Pia6x64qiowayIjoqt/ckjgx/8aeS8ZH0JEz/rslL7h0xW6g2v4UZgkw3LHEAxVsQJQlScFHSwCzuQiT14j7/+GfrNKCyagfw2uY8+0JTV3xj0yxe+JrMlSB5xj5LH4XKGFoBiG8YxFGuKJxRD/NFzVIS2Mzfp3ju1GLsc5zEiMcmrM1jsA48zWbpR5zUoRhmzAbrgtED0+yoeeVpf2GtfzTsNUJPPeCh9VBfSpWK90xoFtU824rT90+pdSxjAXEs4vDBaNRpWf7YyWMG5jeNBvQb9OHgQKO0hfy9Jwfi3yuZIymy33OohpifnypMj4gXfYuhl+QjdJ/ebMRF5/frmsBObicnr+1EmwxgCEtnj4mNF9j/M0SL7T2bdsfu2b8KSXPdmQ6SyiYXOQSq7gzqJwE7Ng1YeFM/tbnkLK1wKXFKrV/4eGJJL8cGFJGO//1VEqr7XzHKmPP0VO8GKPPJ/QiZ4Zb2NeQszV2feoZM6xPcmm3i4xGtC+Cl8zsmeruh8c9Fi6emSXE/eGd+DQe8SknP7
*/