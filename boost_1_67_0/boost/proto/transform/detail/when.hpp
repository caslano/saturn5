#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/when.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/when.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file when.hpp
    /// Definition of when transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/when.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A grammar element and a PrimitiveTransform that associates
    /// a transform with the grammar.
    ///
    /// Use <tt>when\<\></tt> to override a grammar's default transform
    /// with a custom transform. It is for used when composing larger
    /// transforms by associating smaller transforms with individual
    /// rules in your grammar, as in the following transform which
    /// counts the number of terminals in an expression.
    ///
    /// \code
    /// // Count the terminals in an expression tree.
    /// // Must be invoked with initial state == mpl::int_<0>().
    /// struct CountLeaves
    ///   : or_<
    ///         when<terminal<_>, mpl::next<_state>()>
    ///       , otherwise<fold<_, _state, CountLeaves> >
    ///     >
    /// {};
    /// \endcode
    ///
    /// The <tt>when\<G, R(A0,A1,...)\></tt> form accepts either a
    /// CallableTransform or an ObjectTransform as its second parameter.
    /// <tt>when\<\></tt> uses <tt>is_callable\<R\>::value</tt> to
    /// distinguish between the two, and uses <tt>call\<\></tt> to
    /// evaluate CallableTransforms and <tt>make\<\></tt> to evaluate
    /// ObjectTransforms.
    template<typename Grammar, typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct when<Grammar, R(BOOST_PP_ENUM_PARAMS(N, A))>
      : detail::when_impl<Grammar, R, R(BOOST_PP_ENUM_PARAMS(N, A))>
    {};

    #if N > 0
    /// \brief A grammar element and a PrimitiveTransform that associates
    /// a transform with the grammar.
    ///
    /// Use <tt>when\<\></tt> to override a grammar's default transform
    /// with a custom transform. It is for used when composing larger
    /// transforms by associating smaller transforms with individual
    /// rules in your grammar, as in the following transform which
    /// counts the number of terminals in an expression.
    ///
    /// \code
    /// // Count the terminals in an expression tree.
    /// // Must be invoked with initial state == mpl::int_<0>().
    /// struct CountLeaves
    ///   : or_<
    ///         when<terminal<_>, mpl::next<_state>()>
    ///       , otherwise<fold<_, _state, CountLeaves> >
    ///     >
    /// {};
    /// \endcode
    ///
    /// The <tt>when\<G, R(A0,A1,...)\></tt> form accepts either a
    /// CallableTransform or an ObjectTransform as its second parameter.
    /// <tt>when\<\></tt> uses <tt>is_callable\<R\>::value</tt> to
    /// distinguish between the two, and uses <tt>call\<\></tt> to
    /// evaluate CallableTransforms and <tt>make\<\></tt> to evaluate
    /// ObjectTransforms.
    template<typename Grammar, typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct when<Grammar, R(BOOST_PP_ENUM_PARAMS(N, A)...)>
      : detail::when_impl<Grammar, R, R(BOOST_PP_ENUM_PARAMS(N, A)...)>
    {};
    #endif

    #undef N

#endif

/* when.hpp
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
*/