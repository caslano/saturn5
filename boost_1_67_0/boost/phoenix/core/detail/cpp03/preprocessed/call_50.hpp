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