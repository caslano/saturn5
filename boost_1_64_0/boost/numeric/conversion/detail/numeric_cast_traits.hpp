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
Mq/3DKpzkH2HyThsKPFuFN/BwyyF5e/ecD77DpNxSKoePJu1FeYkrMrw60ac0zAZ21xFq3flGQiWW9ju5DxO2t9QzDmPHA+eKs+4w3yF6Q7P7ce4w1yFNaml/a25gTAZv4zYNQ/Zd5idsB0Zffw5H2D2wn7kfcrzylqYp7A1+5yZSydhMg4n2hqxRn6ByTF7EnD9K/veKmdsHR5YcU8UApN9P+VzmuPZApZbPm99B/YhEeYsrJnnp87sH0y2JW3UEJ4RUmF5helW93vN3IV5C5tWYs9l5q7yvPtl67Tg/jrGSBcgbPSH09+5NsK8hIVO6ZbI2ML0wmo2H2zKvIbJuFff7jyC72JhzrJ/8+NjOG9hMuff5717ln2HyXEJT3oTxNgqFryrJ89cmTArYa5203vxPQrMX1hSejHG1qV1zr3UnIq9+3IfCZO5+2Vqd+ZZMZhsS4/yXzietWEyd5PnlHrOfIFZyNrjF3yI5xWYg7De02pP4TsrmBzPkm+rB3GsYW7C+o4o04hzRbH9Y4Jac28K0wvzP9T1B/cvMFth5odnT2MNUdrpOblnIeag0vc+r4rE8mzfJmcfGn3K4LgEwuRYX5wX8IbzD5Zf2I0qP1k/O8BchY3MuGnN+QeT/bt8N3cb1laYr7DF1+dV5dqhXFc1tOo+1laYo7DAg1dnMAcVM/vUYzH3UjBPYY97aH/33CU255gdKXbvOMcF5i5srMnSeK45MA9hZY0bOXLeKtb+jX4WazLMW1gBh/nrWZdgMrY9xkTn5n5Xuefrod8qc27CZPyete79hrkECxA2OD2BP3eoa5tzXBIvX+JY+8O8pBX5XoJ9h+UVNmJ482rcY7ZVzg9rLF9wrsD8hA08WF17bwOzEzZuyoCi3GfB5LiUP/M8ne88YK7CSp2Yvpxne5gcF/Of58PZ93bau5k9sHqVMzOZ87CCBtsN6/j8Hs+GXWCmwq4/6RfLvsMKGWwXbGL0An43sUw8bycs5qKXGfsgrtsBC+1z5jb30O21tmyH1XqQep9rByzYYNtgd3yfcW7Gw2ykRXlzriTC7IV1O7qYe+EkmKXBtsIS3bqf0/6WpRaHLbDM3eOyGD+YnbBDDzokM34we2E+hxvzHcsF5Z6X0t435x4a5iysVOOLVVnrFDu7+L4j53SHnOb2v/l5eO7ooI1ZKuxA4kfmWaywzbDAPVWOsGbBTIW5vytajvMW5ivMaYJRe/YdpjP8zNCmP+fw5EBPzoeurHXZVnLSEfZ9Gcxc2OGAXx+4rsCC5XX+r9pxjwIzEea946CONVK5Z9iAfs+5rsBshc1tYrSZezeYpbCIf9tyL2XaTYt7Cqxlu1G8zgVmLaxTgS2PWF+U65rX7RbD9R2mFxZhvI1rRxjMSlj+82W59jdS7jlC986OsYXZCqs/r99nzhXlecnOlZifo2E2wgZtnjKPOQFzEHZN32s1YwSzFxaUtjwv1ziYs7CEU9PiOR9gTsIWt4hyZYxgjsIOP0zS9p9KO6d5TWvLtb97znZe2RG0kXGAyXbme1b7OuMAk/FzNarAtlSAyTgMbZnGPtSGyT7ED34QyTjAXIQt3zrSl2sjzFfY2rir4aw9MDlmazYXNOJ5DOYmbG+9zwc4njAfYafNS97jvkAZF7cTK7ux7vZAzss+1LXuw7yG+Qvb4JlZkeMCk3Fwv22Rn9/xweSYDfM5qOfeFCb7fjp07EW+X4LJMdt8J7Q1cxAm++dlHvqReQZzk+NpXnEc1xxYsME2wiwzih5l33tinywss/O67TyrKTa0QVu+H/SA2RlsPazUjnY8pxaABQu7uLwF50ormKWwliuqH+Z6CzMT5nM2iXkWD7MRVtE=
*/