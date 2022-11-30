/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
        template <typename Expr
            , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void , typename A19 = void
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

/* actor_result_of_20.hpp
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
*/