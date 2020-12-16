#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_AS_CHILD_TYPE(Z, N, DATA)                                                   \
        typename proto::result_of::as_child<BOOST_PP_CAT(A, N), Domain>::type                       \
        /**/

    #define BOOST_PROTO_AS_CHILD(Z, N, DATA)                                                        \
        proto::as_child<Domain>(BOOST_PP_CAT(a, N))                                                 \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // funop.hpp
    // Contains definition of funop[n]\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY), <boost/proto/detail/funop.hpp>))
    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_AS_CHILD
    #undef BOOST_PROTO_AS_CHILD_TYPE

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    /// \brief A helper metafunction for computing the
    /// return type of \c proto::expr\<\>::operator().
    template<typename Expr, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
    struct BOOST_PP_CAT(funop, BOOST_PP_ITERATION())
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , BOOST_PP_CAT(list, BOOST_PP_INC(BOOST_PP_ITERATION()))<
                Expr &
                BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), BOOST_PROTO_AS_CHILD_TYPE, ~)
            >
        >::type type;

        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, &a)
        )
        {
            type that = {
                e
                BOOST_PP_ENUM_TRAILING(BOOST_PP_ITERATION(), BOOST_PROTO_AS_CHILD, ~)
            };
            return that;
        }
    };

    /// \brief A helper metafunction for computing the
    /// return type of \c proto::expr\<\>::operator().
    template<typename Expr BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A), typename This, typename Domain>
    struct funop<Expr(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), A)), This, Domain>
      : BOOST_PP_CAT(funop, BOOST_PP_ITERATION())<
            typename detail::same_cv<Expr, This>::type
          , Domain
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
                BOOST_PP_ITERATION()
              , typename remove_reference<A
              , >::type BOOST_PP_INTERCEPT
            )
        >
    {};

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* funop.hpp
8yp9dUSrbVzLu4aSeu6/I5XvkqJ/cQ47I3UrCkKFWQa5puI6LmxYb/ncUmcjIwdirSNziIhLB2z20OjwXihoVayVKkDYLDZaSasQBmCS4v3CHoLnbVRs0tyXzyzoKeak8J7XmD4tqzYpcTyaaX7S11E6Pet6qUPrenacr97aIX+VY7xSHAgzJlUttZxFABT7u9EbJt7QKb0FHFwtNJ8LkjEeYrYcDXP2TaSHPkZtJ03k2eLYEFF/799I+isC78OfUloPF5XshDNse28u6fNsa1HANcAjyBDhrs7hno1nHoVTgZna1MG64V0U2xjbh1J7uyi0I3StG/ck4OWQV22fV9pcS61N70yf6cemx9fm5XLqHhGrp4PO+FUjmkq1nTW+JjSvnkcTiihN1F98kdK0imnDg2ycXpB9sb2lmmGQdLF2tvIkpP2qA9rewLzsuDWhWSpXA2eQb8JUIV4OB8moJv5LcigejOyLQleptu0YUXWcnRxCq9JMxTaSmCh7Dv0KKB0umdc6qKrj/6VMsTfnU1WOmVW0KzDRgVd2JRbl8XMvmwnI4yrK2x+4BcgmqY7nj2L3tndHn5zIIsxj8d589h3fVC/Of+Nb6urKrTG/y3UiPxbp0jj3e9dL34iontfIH54zzt3ZQ1wq9Z9jbcKH6C2CITOJ1OPwLJ6U53orbQhV287mcUCNf6PdObqdk8gVJD+FKOhp1hjZ9VzTh1UkkL0JdqDTwJ2wFY10Dgo6ijWdj1d9t5TM/ixy4MkORF6ZxbaMdBzmqZ2M8ssa07RcNnHscsoYruchiCAeaBz52JLBpH4bltfQv+9NSp6h6ztRCyOH+MNHiWyyb4z9SlHmo73cbN9nm4hJyRPVIa781kq2Hu15sWsoLywk4h3o3OVKuX+C6CvfxfnDDKrArmC2faSXdSgkbyKlc7lrBQSb6uJ1ldKoLsRx7K+MfDisEa6p5Ln10n5QHw5K51Hcau1Nq1hGHdupvupKOW7e9nXVCDfzi8AVhdjz7U67sIY8VtH+ijltWqm4Z8lxNhIr00cEaUEKw1iUJFLLikPdytevjM5EWXey8xV9aEvuf2fPPx7l1P1hgauYbhwPqleIC2s83iYxk1Nq1zgO2y23Sr2Ocs5oiC21u388jdG04/DvnCTmo+Dr7k3xRM+cFVWwSkEczeMzWHKtrTgObDa/AN+T7bmfyRNq1Mtsjd9ZeqHbmvG5ie7eZLoHWANBoFXK+a+jNB5eV4IbyDL4/MlW2e43bY3yZ6u47J2RWBlUkmZuxjYe7kC0tsnJ/sG1qUeM2Gd+htK65A0PPoga6jzCkBcc6/18US/kvQ7GtVyySJNkzlj0qYuur9FndzZeOZZ5MfYt81I4pa2ax9A9oy+YV/dfuHMIjtjg9pc+zmihvPquIdbGdB6K3aGs+9EhHoUVm3zjqZvPB/8JhfrMzw7lKWE9nEEqLraDwe/hC2OYtM8hMkb2ffnycpgZpVh8hnqErw1t3YWmYB2/G/DD3HNiM07CzFYEcY+/tQIw20cx+irYMV7Edbxd8Nug1G8a0zL9hAuemhpT36xrtss9w5umr3rfsZ3TydHhyf50b/tg6+x4d77ZdhzecRSPtxD7WPVak0QZxFAaziI4OYaE1Ecp0B6JUbFd6pCaLnihhGfu6LyzDKSt7KQHfcqy43Z5nzd1F+oQalif81hZ6yk3O9oIzUMCXomZ+IEUiSH0HUrrMtdxabrQM0Cjydb2HcoI26Xuk9vaBdM5qJtsiBzGGKLyoq0+J7YeeCbecqf08W91pZuW5vw4PV2WVgLx7z/Cr62qnalbxJ/+B3xW4DdMcOEjwz9Cx8t66IBBH9GdUe42o4I1FeI=
*/