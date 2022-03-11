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