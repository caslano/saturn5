///////////////////////////////////////////////////////////////////////////////
// expr1.hpp
// Contains definition of expr\<\>::operator() overloads.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define N BOOST_PP_ITERATION()

        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        typename result_of::BOOST_PP_CAT(funop, N)<
            expr const
          , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
        {
            return result_of::BOOST_PP_CAT(funop, N)<
                expr const
              , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(*this BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }

        #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        typename result_of::BOOST_PP_CAT(funop, N)<
            expr
          , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a))
        {
            return result_of::BOOST_PP_CAT(funop, N)<
                expr
              , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(*this BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }
        #endif

#undef N

/* expr_funop.hpp
nN5PtMX558rKQH1mokiuSTEHZ1rcTZCx25S+QxIfq6DreCxKOPNBhrLhAayPt7FAW5bgrpVgmy74BnhhJSlHZ8qaWVFCLHjSW6xnBWdPRc03/IYycSwLd9kUNQNu0DAzLUq6YxVL0PG1B27yroKFibXhOHCRck2qjHF8aIYrGC8ZQlEqx2L7VRIEMC4r04Zq2hgSUgMKVCN4jQI8i2tF4tFbkdaFBD+NHTGi6SR8kagp6s5n
*/