/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
        template <typename Expr
            , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void , typename A19 = void , typename A20 = void , typename A21 = void , typename A22 = void , typename A23 = void , typename A24 = void , typename A25 = void , typename A26 = void , typename A27 = void , typename A28 = void , typename A29 = void
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
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector12<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector13<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector14<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector15<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector16<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector17<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector18<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector19<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector20<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector21<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector22<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector23<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector24<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector25<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector26<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector27<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector28<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector29<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector30<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };
    
    
    
    
    
    
    
        template <typename Expr, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        struct actor<Expr, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            vector31<const ::boost::phoenix::actor<Expr> *, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

/* actor_result_of_30.hpp
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
*/