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