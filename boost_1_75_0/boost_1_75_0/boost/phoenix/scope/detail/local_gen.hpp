/*==============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

        template <typename... A>
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
            typename vector_chooser<sizeof...(A)>::template apply<
                typename proto::detail::uncvref<
                    typename proto::result_of::child_c<A, 1>::type
                >::type...
            >::type
          , detail::map_local_index_to_tuple<
                typename proto::detail::uncvref<
                    typename proto::result_of::value<
                        typename proto::result_of::child_c<A, 0>::type
                    >::type
                >::type...
            >
        >
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION(A const&... a) BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST
        {
            typedef
                typename vector_chooser<sizeof...(A)>::template apply<
                    typename proto::detail::uncvref<
                        typename proto::result_of::child_c<A, 1>::type
                    >::type...
                >::type
            locals_type;

            locals_type locals = {proto::child_c<1>(a)...};

            return
                BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
                    locals_type
                  , detail::map_local_index_to_tuple<
                        typename proto::detail::uncvref<
                            typename proto::result_of::value<
                                typename proto::result_of::child_c<A, 0>::type
                            >::type
                        >::type...
                    >
                >(locals);
        }


/* local_gen.hpp
kHrr25b1GKuDoI+pK8sNun4ECXzPxvuNtIq8irX6R2tq0YwTkj3aOcKxf7a/VS97r6//CyIbw+0odaMPIi7CA6I+ooO/e6+fBFovLjqCMKKRP5J/kL+Uv2OvWW+QXRe9TSwBqOW9MM4xyh1ioH9cv5cAKQKYdlsT5Q3vMgwxFmH6j2lEahQA6iPC6/nhkCS9GQ4Fyd6hxJ9TfmaaTYSXDocyL1h9IJphSDBbIGuqavxWnOBbCCOXZzQnvspq1rBdcGem8T3PInIZKSzh4798aKt2MJpsLeGxN/7+ojQwtXo4yiJita7946MNI7YPpBJ/xvReWjiZN/HyS65oilwefZz8APPXYsfV+ik1AUuVGIC9cg7/5vfa7fVfrRZu0r+jsQJNF6NKl3x/qly12dGn1hW1jj7N4bUHdjQUg2sPhpWcjHssRao9CPk5yNI9T/gtGGSnWgkaBmtdlhupVMVsGUa4h9O85n9smp5GaF5jpXSK42tf6HJbphp8HSVXiHAbSEmMoUjsV437Ppodlfk6XDaGFlpZ2pav3kyKrQ8uN71O4Eupw65GbDI+LNjTdwyNzZJTuis9D36P3JdhNsCXZNMvbJ2dthizQH0CmF3BxwiWeX7Nfouv3g6Qou8bMEKTxaG8vIWiPLe/dODcvWyIeCavo1sZCiTvL8d13Ton6VotHpyLzZEo6I65WAF5kzmF0Hqc728apJhlUENl
*/