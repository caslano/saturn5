#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/callable_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_CHILD_N_TYPE(Z, N, Expr)                                                    \
        typedef typename proto::result_of::child_c<Expr const &, N>::type BOOST_PP_CAT(child, N);   \
        /**/

    #define BOOST_PROTO_CHILD_N(Z, N, expr)                                                         \
        proto::child_c<N>(expr)                                                                     \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/callable_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file callable_eval.hpp
    /// Contains specializations of the callable_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/callable_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_CHILD_N_TYPE
    #undef BOOST_PROTO_CHILD_N

#else

    #define N BOOST_PP_ITERATION()

    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, N>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;

            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_CHILD_N, sexpr_)
                        ), 0)
                    )
                );

            typedef mpl::bool_<value> type;
        };
    }

    namespace context
    {
        /// \brief A BinaryFunction that accepts a Proto expression and a
        /// callable context and calls the context with the expression tag
        /// and children as arguments, effectively fanning the expression
        /// out.
        ///
        /// <tt>callable_eval\<\></tt> requires that \c Context is a
        /// PolymorphicFunctionObject that can be invoked with \c Expr's
        /// tag and children as expressions, as follows:
        ///
        /// \code
        /// context(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr), ...)
        /// \endcode
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, N>
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_CHILD_N_TYPE, Expr)

            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        BOOST_PP_ENUM_TRAILING_PARAMS(N, child)
                    )
                >::type
            result_type;

            /// \param expr The current expression
            /// \param context The callable evaluation context
            /// \return <tt>context(Expr::proto_tag(), child_c\<0\>(expr), child_c\<1\>(expr), ...)</tt>
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_CHILD_N, expr)
                );
            }
        };
    }

    #undef N

#endif

/* callable_eval.hpp
kLm2bAj+3bDtJEXaFSKySXJngOS8s1IoSIAS42IeQ+yABMsQSsncOGQWZ2+V9mV+fzi2Ed2rNqI6lMjzvCux3mfuVTv46nTmnNraesT6mnmRYDF3nvGlSbwUtDQve2GAETEpz25suC+j3ZqPvjvOOGzBvawh3+1CMTPFrGBfPTWXensZkm7feteXJncVCKj5gMPItdmFVY5hRG/uY1pw+sNFNeAmhjXVN5Nz4Gu83HyllUw6SAe6hzezK+ztBnnZ4xVh/aVdDyxXu5fGW2h40/olp8P1UsmuT/MEhItnx8M5JdrJm+KXo3tJkuTZ0LlmMd99V8eleflOSCjMkkYWYlQL4FDnnrS1e5fhNFlG8SP7qjQW9P7a7O2undpmfvHswx4+omTxt6TjX47nTKKqUrUZBdeDoLpqeVH9wc6h/PJEb1PKIutkLjqoe9AAgykSoNy4LeWDIlop6karlsGc8Cv79Hza5rStyLE/tbrKPC0E2Bmax8X9q9KSML9kqM+hBDIMy6dHbRyErHC/LKTCjjKFnCOQ+3U88Jlun6PB8n2W3gcj4leJtE7aptO5mHLDM8UMH4bp9b6ITys05OkSCzzwwQiQrELS0HkWoS3Mu8TH+ol4aYGtQqbY9B0vNzIHc/O8oOyftKstco09eP89BNpEL6liA7H3Ra+LiXjloq9U28g69TqdU6OEYMPygN1kXzjK6Y8qcmhMIGaEQJeYRm6vuTsve7iTUhLsEu53VJJhMQiU4zJ6mZR6aLPKjVVAKTgBQTzsbBDet9BQPOWRIB/6uD3pY1dnqpBpIQwI3uk1WNGQbtgxmq6hp0X0mciKbigyCOajEZR7/D7Cd5wkdXJhRFvSt+qgMq0sLYml7tliZmPM3Z0q4lGJoa3TCmqlqH6vPZ6RcVc8HuikLW3VFmSEa+0VnD50siMw/fG0L13dSCUrMapTicFS8s/o/zKhl1UzEIpnoFdqP3of4+qrkYyNTaJuaFYcpX9NWeXkq2vzsiikIco1aT+woNd2q47/iiUv+xeFB181OIvuuwrOH1MpbfJMt33q8bBDzMLpF7m5G4+TEQ/S7/Yyz1UpuPMcp57aGEb0Elf1LFc5YXLPYLLM6hk4LSgyaFt0SYLu7mkT22y2ZtfuZ0T15iJvag1ViRZ6PzwYT57c191JInotmmZou7L02MdkZOAiiLpmZBO5OGN3OI91FvFtBCFxpUPd/xt8PUNu5/vdiF8tsFqUqsvK8TNvZEYC2NqE+7M/Q/w3huAU2+4Vsq3bku659mEqIPOHj8TuF1fn9K2QRdGlVVuK+5rJ5STd3amO/Mac7kiZJxVEKbuDcox8t7ZuzssflkNTJ50yJ+bqjK0JL9uJrK2HNq2ZkgfaHVPJLG77UU57Iu1wrRzKBNrNrc3zZ7bOun5IV5fg5bF6oUEeak22xszObDIKHgMrHrumHVLCq3O07J4Q4x4/6GsTv4hUlgQOB8IQOXjfXga5+uo34eNfZbjcdkkrzjujPVfu2rzc4QZ3qZaeQjadsZn3n+JtOoZ7fy0Vro0zi5T88p9P/u53IZ91b94yRsads770L7oqGjr6tJtLwrKxtJq7qfXBvzLPcxIXjOGRNfJ/Afi/2PD3r9gkHjj+L0T+D8f83V3v8bBr60bejY9TXngC37V0L0belU9QnnPzCW1+CfKeQXnkD712zhNS3kuRd3LEIRhFcBM3yProvwJ5pD9TJwlXxKR95VpIW1qoNIAvkmrB+1s/7qKUb21Xdk0gGBOX6Rbmm16c8kl7TM/eozEOf4f2PukXvySVgxiC6DSjaEnjZvOWLk15hIdApkWe3NO+/rKUbwL80sM69yu/+RWQR/76pIM=
*/