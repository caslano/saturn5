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
PTKc0kgFm897EhdYNEhvR0Wknzvf2DVHcHenVLchc99IpW26AZS23J4WAI/wpNSXV5WDPueSJqtpfZ/L1qNbNPRcr84A9UU2u29/g+qlopWnO05PyXbTrmjU1/fROeH45qpe0l5nFGhlskBj1SZgjQjvdQcfjRh67+tTqwyFNEcjGj3+eRXg8K41V4lfnqdUz1P+MWXG7O+zNCXiw3lZozQc509GcETzt5VSiIHufd1QYzZXsG4CLwbU7T58TQGV8qdbai4BJ0lvOCq2jhYCkUTsWlS8KnOlHJbSgqvh1yB0pLfwmod0oIWvJVcp8mUdCUJjRUflfH5yJUd0I0s0iNemmzAVIv0AJ+pZcp+sy0Wo5nZSY7tZQtavI7xLzYlNCHagZblKFbsaxRAY/6bnSMtOsztcgc6rz3no+hIED0KEdl1xCId/uwOASXoKJYqo9eR4Iz1eqIkP9dX/RxKpYaT8xSmKLbN00ltadQhMMZIHv/5qJ+sIdN0v7ePd9ORfigV1qQ90fbUK0+bsIjBwedNall6kHT/8tR02voepX3A4UfS8Xo5vc6578g==
*/