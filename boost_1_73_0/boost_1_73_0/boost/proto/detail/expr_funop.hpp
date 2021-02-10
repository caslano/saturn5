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
AAAATAE7AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI1NlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJxGCu65wIAAC0JAAAeAAkAAAAAAAEAAAAAADEEOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNTdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS4ca/JwoEAAByDAAAHgAJAAAAAAABAAAAAABdBzsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjU4VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkz4FroEBAAATwwAAB4ACQAAAAAAAQAAAAAArAs7AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI1OVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLHGS6bSwEAACACAAAdAAkAAAAAAAEAAAAAAPUPOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK65NvM0QEAAOACAAAeAAkAAAAAAAEAAAAAAIQROwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNjBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS6u30yk4B
*/