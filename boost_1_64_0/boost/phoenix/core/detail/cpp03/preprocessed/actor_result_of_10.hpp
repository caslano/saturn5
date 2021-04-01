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
kU5Te0K12q7FuDlHWyjKDMdvd02iT7HjlKtqugFCBbhI+w+aA1y+fki+2xEH0VslTMcBLO2Fc3fU3r31SZIRhy+dHUpOqtnZOOhL1uAYlIwLIs51nk9tLzxjvcPouzWYer0Nua9V7IZw4ebK4Dkye9rp3BwU/GebkV0JCCbSeDKFZXXflZFm8upUc2G4uyveW1b9vOwNAZ3XTsLiiRTxAPbx4D/0ZQRjH3uevtKtrR/Yhg5iijndqDDDw/O6F+pyMRjGy37wjijQRHQIUOok5zUn65vT8C340rCfpDxOjn8UxDEI4VpAVfnKhVXdrqhvXHxptmW3VKDvSW1ZIRQWb5ruGpf5xVM5YjstQ/KkM+uy2lyu6rZE8TlqrqpoT9XIIwD45OM0KaB5h7+rKIBXVX9ihVg5mPsvFHnw9j7+aVyDS7oo3sz2sEIRwcnze+2uxv3rVEguJt22u/4eQj/ayCB3pF2kBrYaFjHAV9Lm64Hnvl6FppgzGnaHcz5ZOYhi6I6ruTXjzKCv2eiLMBz9iWIbx6ciqrbc0bBpTw7uDRHLex/S0bN6uoG0Ww==
*/