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
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
*/