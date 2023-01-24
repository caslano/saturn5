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
zqrRQVcUWho1WwnkOUACL+tLv162FzIO5V1G5Q5sTZocS+o1LFQXw+ktsn5Ev9UosPsLuteIaWNMuKsJkY0y3TDzhUhU9Zlm4GiDXI1KGPlJpaPKiugcty9SuUjRI293Ta6J/thoFOmCZEQg9GUvLS8bArCOx9gZsJ/gfwyYkPB+zjzevhztaTvFVpb9B3aq7aEBFoTghJJ2raB56OEQmPjpfY3BIkTj6UbRx9OCDim83ga4HET1RRsAg3ea9ATxEP09c7QI7CyPkvkg4ZuqdAw/RPEPvV2wwGXDJW//EuSpI8OwDefFQ9fzsBeJos9Bzw5DcubRo7KjK4TVhIKwPCBUI3KXkGWmw14/dv66pkxkeffYzoW+25Y3wP4J9cUPL+GZEjMfif4P6FcKFtnF4f3T8v8D+nT/DfpcHP/IUha2Fk7mJsb/Jr6HvdpQGvLn7BHhX/JeAWsxAkKMSaf/gomJzcJFRBMfTI1JrB2/InoTn82ZnrA1/tl4aGScdO10e5iMx1XFBIv+oNCSnFl7QFanjDvWKopsE6vjiWbIVr38zHhE9INd7cNoNXkj+MLXyfITF1bK3WI7GNZ1gYA9toMRMPeaLTyEwYp2jrDX3hRD/8b3EGeT6uhIVfdxf/uFYDIJ9J6UtrY2Pq8L8Qe/Ufj7baNWsh+Yv18BD2lFGJXeJKN9FKFVQmdB+SWHn2siglOLWooONFzuZ+oH
*/