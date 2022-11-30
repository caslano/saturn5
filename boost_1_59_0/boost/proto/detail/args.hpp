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
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
*/