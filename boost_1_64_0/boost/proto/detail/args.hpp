#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/args.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_CHILD_N(Z, N, DATA)                                              \
        typedef BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(child, N);                                    \
        /**< INTERNAL ONLY */

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_DEFINE_VOID_N(z, n, data)                                               \
        typedef mpl::void_ BOOST_PP_CAT(child, n);                                              \
        /**< INTERNAL ONLY */

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/args.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file args.hpp
    /// Contains definition of \c term\<\>, \c list1\<\>, \c list2\<\>, ...
    /// class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    /// \brief A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    ///
    /// A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    /// The types in the sequence correspond to the children of a node in an expression tree.
    template< typename Arg0 >
    struct term
    {
        static const long arity = 0;
        typedef Arg0 child0;
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_VOID_N, ~)

        /// INTERNAL ONLY
        ///
        typedef Arg0 back_;
    };

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/args.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_VOID_N
    #undef BOOST_PROTO_DEFINE_CHILD_N

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    ///
    /// A type sequence, for use as the 2nd parameter to the \c expr\<\> class template.
    /// The types in the sequence correspond to the children of a node in an expression tree.
    template< BOOST_PP_ENUM_PARAMS(N, typename Arg) >
    struct BOOST_PP_CAT(list, N)
    {
        static const long arity = N;
        BOOST_PP_REPEAT(N, BOOST_PROTO_DEFINE_CHILD_N, ~)
        BOOST_PP_REPEAT_FROM_TO(N, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_VOID_N, ~)

        /// INTERNAL ONLY
        ///
        typedef BOOST_PP_CAT(Arg, BOOST_PP_DEC(N)) back_;
    };

    #undef N

#endif

/* args.hpp
qsykWqDVf3iLIhnqzv48gbPKHygbPt75oF2VKqtEZ5L2ZWTaO7uy1D2zPlSpYPYuj3hXLPu0XZ1mmK8pWVuLhqfPYz2Mi3eB05/StS7yRCux97htiKYy+C4XB+0uKhiErEb9Ct5msY42kTiI617S9GEAIT4xnSVv4Xzm867MU9mWsCecX1mFgfcxNkim/EDUx1RgzsZKdmHOk0kQ1o7EzPf1y1H/Mg2CflnVAqLC4djE++s3o/7VQmVpl+aS8t3QhPHGfceVXuTJm3h83b9E9eY2hwYXlcBK4XIziEfy7jhutE1VDQd7J1h0hqHwz+qN52mk+zS1MW2jKgFKxW3q7jqN6wmOmyqhtJRlIhuuYwVpiytZz3s/jojWirrQpq6M9d8EdFZ8HnD111DHt/Pu6BultqwsfGaYDUHd5u28o3olxlupq4r0VTABJivao3n3Ak57umpqWHMNzjteE7Odf1VUVynyPNUyrxTv47DO4fr6wLvj3AuyzHNduDrpPdzHnx58j8K2ukpKqo/bOkOlcXzhb3La47lucm1VI5q2jtfwdziekkJ2Er6atG6/QH9CEAehbbAd9ufr+p73cBUhT/K13hPfNUsLsmUnByEU//1ZfYTzOFkYqUpVavzuMM0Heuyj74llWalzmbW2FS4iIlsZ3NoOhokWCjv/HhbXaxUcC7bCM9svzUdSvWtRvSAjNFkJIomKYp3+h8XpcwdFY1YLFKHTAaONs+6dEpofVh00w+saIh4ZnI11KhPYrDAoVC9C08tpYBC+25cHbYBtJk0709uRYvwL6MeYA5zoa5uPd2XxXPsp53G8VFmT1qURctHGa/VnUV1KNLLMtGky0W6s7m6Pts9CN4GIV7Hi98/oG3V5USptDMgLAXfO75/v5d/IirRMUmutHvZJJsN+uQ+1uhJ0EEc5LyuMwaTOhbcRxyEFwuCT4+PCPH8Q36Wp2iZprd9LY8p12pMEr28eakutzq0YhDKbOU/rt4n6Cuu3MBomb+tkyI3z423+WL/dD0PwipnS21RxPqkRZZGXWWtSgc/2p+l5YW1jF64P4J6BV0Mf25zLoy+J+JSiUA2G7jCMT9/5CRaXkZ5SOT1pZ7XBlL4jzOK6CapxALV0T/vqXq8rXnExVeEyqOXSzDrBqzEPB4M7is41JgEJ9puWwWGzPr+8v7UDaT49/MxTwj0xafJuTH10xsPPAZzpn3togO8xOCzkjbVxppUQ1/IJnP8SBIRN77+k+zCPpA+/OBUHa/Iut3t093zWwbh4afA8X/CUSMc8GduSvRu8yuHCXgZ5vpLWKbOZn9TrYziMYxj/t3jYbCBmtO8awplt7QcIVquMUXv4xxjcUzPbn69zfTw+O7txwF6iHkf5N/3HwF2e5HJ3U12n7/PtwGMMW8XkuRDvgtsRf4/juDoAcWaL2vFDgnMdVWiLb+9PD8bDb+fxfnEQ3jKqQFgM2YPwwJH0kYjL5s0fDsI9NlZ/eJ5/ObiN6Pc34rFJ/3Ew7s48nGMc98pPPRgXlXOA4uMeX4PjeqvlEcZu3SGcQxynX9TLO6dQAefH8cbTcUBEGaPNE97haXjg1n7O9Xie+nC7aX1gc4734eu7DJcsvXHWgJxJ8+oI54f7hkPwOSHvAXC2P0LY6Nn9rY0APxHDATYLOAF+r0k45hfx+rVv8za6pbdP7RdT+4o4of1ZhANuLiDO8PefJn7nAxxQlDH4D3fDmyGH+xxWYAjHdXSjZZQll3eOzQa7vZ3zQ5wdRMIVMP4et/J7LOL1mkIn1gI85G6ybo8Ah84xTvAric45LYpSY5TVgt4mQNKcfKCAeU+y0Pci+kQoXaQyU4kw230wd1TerYE=
*/