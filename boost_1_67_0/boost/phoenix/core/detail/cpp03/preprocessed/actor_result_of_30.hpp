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