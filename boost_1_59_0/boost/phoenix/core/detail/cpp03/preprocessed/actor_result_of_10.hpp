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
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
*/