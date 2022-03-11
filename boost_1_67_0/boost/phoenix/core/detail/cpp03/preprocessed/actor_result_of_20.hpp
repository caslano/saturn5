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