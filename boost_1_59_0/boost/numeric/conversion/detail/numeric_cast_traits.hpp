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
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
*/