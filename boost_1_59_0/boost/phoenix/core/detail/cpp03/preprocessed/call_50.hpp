/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 1>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0;
            typedef
                typename boost::result_of<
                    Fun(A0, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 2>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 3>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 4>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 5>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 6>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 7>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 8>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 9>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 10>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 11>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 12>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 13>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 14>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 15>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 16>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 17>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 18>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 19>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 20>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 21>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 22>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 23>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 24>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 25>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 26>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 27>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 28>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 29>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 30>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 31>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 32>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 33>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 34>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 35>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 36>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 37>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 38>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 39>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 40>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 41>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 42>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 43>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 44>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 45>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43; typedef typename proto::result_of::child_c<Expr, 44>::type A44;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e) , proto::child_c< 44>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 46>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43; typedef typename proto::result_of::child_c<Expr, 44>::type A44; typedef typename proto::result_of::child_c<Expr, 45>::type A45;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e) , proto::child_c< 44>(e) , proto::child_c< 45>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 47>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43; typedef typename proto::result_of::child_c<Expr, 44>::type A44; typedef typename proto::result_of::child_c<Expr, 45>::type A45; typedef typename proto::result_of::child_c<Expr, 46>::type A46;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e) , proto::child_c< 44>(e) , proto::child_c< 45>(e) , proto::child_c< 46>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 48>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43; typedef typename proto::result_of::child_c<Expr, 44>::type A44; typedef typename proto::result_of::child_c<Expr, 45>::type A45; typedef typename proto::result_of::child_c<Expr, 46>::type A46; typedef typename proto::result_of::child_c<Expr, 47>::type A47;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e) , proto::child_c< 44>(e) , proto::child_c< 45>(e) , proto::child_c< 46>(e) , proto::child_c< 47>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 49>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43; typedef typename proto::result_of::child_c<Expr, 44>::type A44; typedef typename proto::result_of::child_c<Expr, 45>::type A45; typedef typename proto::result_of::child_c<Expr, 46>::type A46; typedef typename proto::result_of::child_c<Expr, 47>::type A47; typedef typename proto::result_of::child_c<Expr, 48>::type A48;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e) , proto::child_c< 44>(e) , proto::child_c< 45>(e) , proto::child_c< 46>(e) , proto::child_c< 47>(e) , proto::child_c< 48>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };
    
    
    
    
    
    
    
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, 50>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;
            typedef typename proto::result_of::child_c<Expr, 0>::type A0; typedef typename proto::result_of::child_c<Expr, 1>::type A1; typedef typename proto::result_of::child_c<Expr, 2>::type A2; typedef typename proto::result_of::child_c<Expr, 3>::type A3; typedef typename proto::result_of::child_c<Expr, 4>::type A4; typedef typename proto::result_of::child_c<Expr, 5>::type A5; typedef typename proto::result_of::child_c<Expr, 6>::type A6; typedef typename proto::result_of::child_c<Expr, 7>::type A7; typedef typename proto::result_of::child_c<Expr, 8>::type A8; typedef typename proto::result_of::child_c<Expr, 9>::type A9; typedef typename proto::result_of::child_c<Expr, 10>::type A10; typedef typename proto::result_of::child_c<Expr, 11>::type A11; typedef typename proto::result_of::child_c<Expr, 12>::type A12; typedef typename proto::result_of::child_c<Expr, 13>::type A13; typedef typename proto::result_of::child_c<Expr, 14>::type A14; typedef typename proto::result_of::child_c<Expr, 15>::type A15; typedef typename proto::result_of::child_c<Expr, 16>::type A16; typedef typename proto::result_of::child_c<Expr, 17>::type A17; typedef typename proto::result_of::child_c<Expr, 18>::type A18; typedef typename proto::result_of::child_c<Expr, 19>::type A19; typedef typename proto::result_of::child_c<Expr, 20>::type A20; typedef typename proto::result_of::child_c<Expr, 21>::type A21; typedef typename proto::result_of::child_c<Expr, 22>::type A22; typedef typename proto::result_of::child_c<Expr, 23>::type A23; typedef typename proto::result_of::child_c<Expr, 24>::type A24; typedef typename proto::result_of::child_c<Expr, 25>::type A25; typedef typename proto::result_of::child_c<Expr, 26>::type A26; typedef typename proto::result_of::child_c<Expr, 27>::type A27; typedef typename proto::result_of::child_c<Expr, 28>::type A28; typedef typename proto::result_of::child_c<Expr, 29>::type A29; typedef typename proto::result_of::child_c<Expr, 30>::type A30; typedef typename proto::result_of::child_c<Expr, 31>::type A31; typedef typename proto::result_of::child_c<Expr, 32>::type A32; typedef typename proto::result_of::child_c<Expr, 33>::type A33; typedef typename proto::result_of::child_c<Expr, 34>::type A34; typedef typename proto::result_of::child_c<Expr, 35>::type A35; typedef typename proto::result_of::child_c<Expr, 36>::type A36; typedef typename proto::result_of::child_c<Expr, 37>::type A37; typedef typename proto::result_of::child_c<Expr, 38>::type A38; typedef typename proto::result_of::child_c<Expr, 39>::type A39; typedef typename proto::result_of::child_c<Expr, 40>::type A40; typedef typename proto::result_of::child_c<Expr, 41>::type A41; typedef typename proto::result_of::child_c<Expr, 42>::type A42; typedef typename proto::result_of::child_c<Expr, 43>::type A43; typedef typename proto::result_of::child_c<Expr, 44>::type A44; typedef typename proto::result_of::child_c<Expr, 45>::type A45; typedef typename proto::result_of::child_c<Expr, 46>::type A46; typedef typename proto::result_of::child_c<Expr, 47>::type A47; typedef typename proto::result_of::child_c<Expr, 48>::type A48; typedef typename proto::result_of::child_c<Expr, 49>::type A49;
            typedef
                typename boost::result_of<
                    Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49, context_type)
                >::type
                result_type;
            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        proto::child_c< 0>(e) , proto::child_c< 1>(e) , proto::child_c< 2>(e) , proto::child_c< 3>(e) , proto::child_c< 4>(e) , proto::child_c< 5>(e) , proto::child_c< 6>(e) , proto::child_c< 7>(e) , proto::child_c< 8>(e) , proto::child_c< 9>(e) , proto::child_c< 10>(e) , proto::child_c< 11>(e) , proto::child_c< 12>(e) , proto::child_c< 13>(e) , proto::child_c< 14>(e) , proto::child_c< 15>(e) , proto::child_c< 16>(e) , proto::child_c< 17>(e) , proto::child_c< 18>(e) , proto::child_c< 19>(e) , proto::child_c< 20>(e) , proto::child_c< 21>(e) , proto::child_c< 22>(e) , proto::child_c< 23>(e) , proto::child_c< 24>(e) , proto::child_c< 25>(e) , proto::child_c< 26>(e) , proto::child_c< 27>(e) , proto::child_c< 28>(e) , proto::child_c< 29>(e) , proto::child_c< 30>(e) , proto::child_c< 31>(e) , proto::child_c< 32>(e) , proto::child_c< 33>(e) , proto::child_c< 34>(e) , proto::child_c< 35>(e) , proto::child_c< 36>(e) , proto::child_c< 37>(e) , proto::child_c< 38>(e) , proto::child_c< 39>(e) , proto::child_c< 40>(e) , proto::child_c< 41>(e) , proto::child_c< 42>(e) , proto::child_c< 43>(e) , proto::child_c< 44>(e) , proto::child_c< 45>(e) , proto::child_c< 46>(e) , proto::child_c< 47>(e) , proto::child_c< 48>(e) , proto::child_c< 49>(e)
                      , boost::phoenix::context(s, d)
                    );
            }
        };

/* call_50.hpp
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
*/