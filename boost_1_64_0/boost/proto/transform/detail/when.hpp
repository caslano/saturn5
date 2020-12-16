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
OQiC/0LCU3DthPulT1cO2pXvPsKFN/YDGUm6CtW4+105or2RTqBCUQf+gIDjx+AM/FcE1wdfzK4QFsM1/NdeGclwtBtxKIR0y/8N4XBfDY3QlwwlHH3/1i9zP2JEL1590MFRPfGaDR69dXG/IxxZIZmMg3uIcIkBvHjQmVrScUIqFu1z6vT7MThHjocF/MQOB/4IwfED9MlIqM8xWCrnDw4OPQaNkHRQbvv90cOR+NrECPeo31ZCA8neVF94fdhtx8cIj5ZFF8EcZCMaMxxPurz/5PaTvpBX58cNDBw70SMA035uEfm5f03Sz/E5s57/VwLmzKqN76thT4ntgdIeIPbUnM9Qkxzjp6u6Nmf9Is3WL6a1+ces6UjzMWtGm/Wxmu95Yj17FsMjL8pk63HAH2DxkFHUCfgDGR71Qhl+/nMFfkjgG0le5PN04urylTV02cL4ap6PiP2CNuLb0uhfe0U50Jedt2udH0z1HrvWOE0dApzONxSQb36NfC8Aju8Rtoj1oheSfG2NFK+JtY72RrHGLc4SoC2MHl4k2keW82LgV0/7j4+RZobqHyMTYee1FT5GroNv3sTiDB3x8rGxO7Iq7M2xaWyMh6Ldio2LyQQfv2bTOIv/8AMkfEzUvdxJzzFpOzYe6PCJrQlHAXVoDnLingHXB8xlNIAamRscGFyyk6fRkS/cT/6wydZRj9wG1qxh8HiJhC2/heRZE3byteo0vULu0rQBRm7Q0LTrNHk5l2ZeQHxycEB8ckhA3HGoga3t3h8v7I8X9scLzz1e0LHByRQbvKRtcrGBObdAc8Vu5Z8Tfa1OmXH8o2y/4pg2u/6tcce21VpnSCZSo+XhVG60WMrZxzUllJ9vBX/f+vHLaYxbTOX0jH9+dqRQ2FotiicsxmBq/hYBJNM/qOc9UszSyDNeHcExXamWfYemBbRGmViGdn/CzORkab12V+Ptan5HikHkuziyftuYjEjZewzH2XgN320cd6KI41ZQG51AtvAKaqOTiI7ODNo7LG3iDkub/og7LMQjxHgsFfm6kK6r9+83dlO+cFut89WoKY7o5zbvsi3LIag/1dP+9o8oO9KGj5B5NZW9hmhr2hRXOpLyLZ8ThN1HiXeMeK8Yj3elXBGGZ0FUhtizRhzG47Q6FaeyOqgsjUu2BZ85AdyePYYO1rfZuBMwL+bUIfMzIu7c2Cb3CPW+mtznq1enkTzL8a98i141OOs0pwfIBxj4+dso1cbPzTr2I/fj05YGPJwzV1VBkxE0Y/cL61S2zfaR00V7DlNa56MzK2THNsbm9WxhZ8YWBKypjpCOjjc6orma0KuMy/NtzlytQHkXsfYGvW/vLx+gX8DGnJWtUL22cXp6R4CnrxT7pNcEnMvQPJDPfx7B6h34IF3gd0La/DJuE/30HKSZDKijn16evzhX8JNnJF4v8LJtzmd2kBd2cAHDbRO4N1G7rKV2WQS62fZcrf2INuZzvIuQV3O5mMnI8WeR37yE4fnZ7S7CX0qyweeKPXNL3wMc8L6++w7WXlxu3l6XMT/AaSSvy61vETqQtNPUe3h9A/zA+6Rckgfker/gcZZPpzjjwNoOMP+bRgzXJXAfonZdhX/5OXrZntI/X2PKnaGupfx5MSZp+T5KZeVJxo8J2wQPywv4T1g8cGNt95MCD59vxwrgPyXWRNCXfPSAMzzONXh6AV7o5QYuG9kY53WWsNmbWBsCD1+g09yv4i4G8bya93V+Nrfe+lXQjPFnt4gxCjTePhO3za+C7mjQzWLtKH1u8H2GWerWNn8b5oW/uq3N2h3/3ZF1LDZaxr4PAy/tYg/xAM7wvIPS3yKe17dQGcJv3x7QFrcH2Mk=
*/