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