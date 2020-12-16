/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
        template <typename Expr
            , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void
            , typename Dummy = void>
        struct actor;
        template <typename Expr>
        struct nullary_actor_result
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        vector1<const ::boost::phoenix::actor<Expr> *> &
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0>
        struct actor<Expr, A0>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector2<const ::boost::phoenix::actor<Expr> *, A0> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1>
        struct actor<Expr, A0 , A1>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector3<const ::boost::phoenix::actor<Expr> *, A0 , A1> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2>
        struct actor<Expr, A0 , A1 , A2>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector4<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3>
        struct actor<Expr, A0 , A1 , A2 , A3>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector5<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector6<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector7<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector8<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector9<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector10<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector11<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

/* actor_result_of_10.hpp
6c8/VmplljmT/sJO7j+Z/fko9C0Hfd59ddCBTZkS+tACvSjCPj0yJ/qJufk6+Oo4ohrX6aC/C+BPFdh8o/VnAvQrcRjGbyFddgbG/1aaHztB13+i9WGeqdFH1HtyHej+jLCpWGO2n0OIfWEntsS8vWZ5jNW0QpyDNWr6VWDLFgH/kMsiWI9uhMxmnh02BnJ9FetlFrxcgefb22CfQX9fzImlMd+vw3xf7CTQOAW0TrfpvrKB5u1WzJWPZmVynKlWdtthns6wpvD0sy/6NDXs9jI7QL9nrS1fIIY+pjHnj8E4mTZsj7kgN+jdbPvCdpCevgdb9EKRzXGM74mkG7dBJnOvWo33EaxDk+Sgp0sTzq112TLbQ+c2FuIQ8HTk9NDxJdBvzNd1p4R+QsaHQ5brY83aAeNQaMH8Ohz4MphTkNcWoPkFZF9uhR+C37WXgyzA19aYq5MeA1t/JOkE2k+yZzVPZy5s/50VYzD7IOZnHHqPMb4G+heTOoOxnhift0G7Zw+gtazTLTHwPBHm4LH6+bMdyPbOhnVpNcytvTBuh9a2uxnztgNr9S/4zc4OG4/5vRjm61Av7Bbk+yb0+sK5wQ/sfSvs/VZg6jdpt/shG+h+Cu3PQR8TB6JvLRhb9PvRPaDDbcDZCr3IQX6Yl8kR2M6VoYuHgP/jMG/OAL+wvb9vg7k1OWxpO3jGGCy+GOQm0A5jsQVo9kAPv54YPAB3y/z4jPXtg10xXpD/q6D77onkk8HXmWUKjHuyun8fYE6Z6FsvbMgA6M06LdqBwD7L1NfNgWUxhpDZM9tCf8D3lwuDxqAuPxA4vsOvEFjXi7C90EsDdvWALaA74P/pFPhw+QE9E5DNYfDfwO+B6Nt85MeuuCLmKuS97bZujsADxn+XdcHXftBZyG79syAf2MdfY+L/n/9//v/5/+f/n//+T8t0rWIOMbBBv9E/YPT3GWuss9pGa/eIbyR8TgZfa92N1u1fp2dN8d23Vtlcqmxzo7+nv39dnCwOrLvG+j0DaIvyuVn5Gj19+Duw2sCm/UKWzcPKOL15GZzTW11MPN18YLUMfheJwxXr79/AQLs1+9dZbf0eC3OPWHyV1Tbvrley6qoSR59onRo0gKGvZ7U1UYISYx187OmzeIpx+Oobr7mlsPvZwuG9G4O53r6N10CHUb44+GolvhaLK8yKG3pWPJykeNiwf21jrQ023tzYdCP0cwDdtHjQ8J6+vo37HFm3aHhfz0Y9a288sK6kYZW1sjKQW3ejtW34BBq+ed+6Awo+oYJrES+NfkxE/VgirrnjfVEw1p+F0Z8pgHNqe9M4auDkV8IJBh4Aq0igrDvhdC2gsWSchb+EPDAYTWQkiU3pM1DLunCWWqo1dZelOpZDhNGqS59Rd1LREu8CzknhEnbWbWeOFozCjuauTlv1rNovRe2Xrtse8cjkjqhsbAGiFoYqCOFYhnDkSCbdcYdnYcljaTxPIArF9Cii96DuyGnZOOQARxUxbyGf54TbNrlAjsOoWZQnRk69CrDFGdzImLnh8ojF84SQ63JMrtMK+XKbqk4zAHqN8dhN6eLmG/etX61vMQum9ANDvnGvU9biKltj442gXJv2OOWtKEf5hhv39Rir0RyagMFWp3kzIenbCuBblnJdo2elZxuBV0cGQsiML+vb7vOVckkQHDR2LqbLpipgcoN8c5WskcBJmQ1fGTJrBf2VtMwgcys53WnvyM0NtGS3Xj09ofZFE6lsuVI2LWtjqBkWdxFwwSZQ3+a05xAO9mx9mdvqE7LP5UAL9MWyuegLdGAnPFMd8D1UTAwb+aEh3S5uwayGSgbTinTJSCaVXFZB32cUpcSomarlGXU=
*/