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
xXc1vs/h+zy+L+D7Ir4v4fsyPionX8Hvf3Ou3L45bn7t1mIFCVpDJ1WMInRHiMUeKifuvPcTPO/96mJpD/sxzM6ozc70lOjkzLawBH/EvPhTmu+lqewYTcB2ZetRt7Tv+4yWUfQAT2Qtf7UbhhYw/Of9YQSdxlZR8v1RLRA2jtot+0p6PfxQ55jhtNowI7Pi3DQdNEum4be9awdfIh3MBF1b7OGym2J4x+a7ZPJE092UHtfb
*/