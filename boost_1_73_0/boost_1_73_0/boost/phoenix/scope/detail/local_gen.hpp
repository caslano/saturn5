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
w6a2YWzep4E74c+7IO+7DhyzBLj+Jnxq2nvIDxFPM5E/bIZ8rs8DxoeM1gKTDcd4RmPcxZBPeBBDP5kDXYU8zkOvGiBOVj8LX9IfmAF55mMTgYmQ88Z8qtFr4Sq99zZi8pOwc+SDne9o9EkK8mLkqhnIge6DzbwOHNMTeeEXsBVfI2BlxOZtyPOKwg4G1AGmgc9JQ04a+gP7/UOlct3AD2DW744TPQv+9gyCbSOvKY2Y+dlqYCNghbVfEO0DJvg=
*/