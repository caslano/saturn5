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
dGmihcyWylsnHMpMMKNf8lJrcGncz+uwQxpdw0VJbUF3ydPQnA/xEx7TLtueIoVcdZ6diub2AmoMZUGZZSqVVFhqBF073A3i7MLJYnOxEdfoLN8bnqXVMnCfOMiFDQJX1AivFkbq/+iRG06JQKNMd6jJNJ3xL/g69LNmaE3ZPae4RO7q/8zxoj8+JwbWHmuLGza3mnYqqrvUeh2NaAJ3PppZq+E7TTB/kdoVm/7TtROsw59S2B+cF//H5GD/AVBLAwQKAAAACAAtZ0pSRIzN1zUHAABIIAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL3NlcnZlcmhlbHAucG1VVAUAAbZIJGDVWf9T2zYU/z1/xbuUq5MtxIVy3AbtWkZZydpCRrLbemPzKbZCtDmWK8kBVrO/fe9JTuIEM9ourCM9/EV6Xz/viyT3wRer+9UewK2/wP4F+MM7MXSV/J2Hppo4CHJw/5DpFO+3qPBhzpEHTbiVI4eG5QgKHU/oOQhuUXNKhtHFJ8bTgB5xpPYA+fZleqnE2chAY78JG19//RWsw+ajzUcteMESwWPoGZ4MuDprwZPIjjwfsYuLtubftIAbYHHbCuqPhAYth+acKQ74HIuQJ5pHwDREXIdKDPBFJGBGHIYi5rB/3H3bOXrZ
*/