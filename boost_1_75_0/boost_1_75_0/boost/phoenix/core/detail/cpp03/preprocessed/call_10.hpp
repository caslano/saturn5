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

/* call_10.hpp
vAXi41dvDp6/2HnydPO779cePd599hzQXSKJVSrXKaEJw+bIQrRaM77U1sFSW0OU8+z0CF7O0zUY2jhPC9mKDnR5l7LdZHIYjU6jwWFA0TKZWgZ9zrpA6b3F+RSWc3/ZUoPLXoVx02lW1u+SZnohXmp6l4FsMFjNpapXl9VsspLBudMkN7FOm1iHs/HgZTR4EQ7EQoGw3xf2eQNu4La6nUaXS+N0Sx0ensPLcPqPncF9Z3AHqtsW2jmL7JljR6YEw3jOM8bFhrDc67ekQn6bQs7e2Dx+9Zrxfo2zvcPZ2oI/Mtc3GGvr9HfvaW/fATrQw184evES0Ncff7v95Kns6CigVNl1OmKLBHUK5UystGfljDZVUqKc4SFAlvMiNHGc2SbKM2ITInYZ9G69zq3TubVat05rhe+5uXmn9erMl20+RiGOriZeoRxaXcKfCQ2pJCL5eKyWT9/DPVmTR7LxUCoWuoiG4uFgNBiIBPzAHfS4/S6712V1u4xOt8rpljh8XKef7vQfOgN7juCOLbh7Ft4zh09MYZYpLAxFzpJ+j5rFBk3O1rbw4FCwv8/b3eVu77C3t9mbm6z1zUXul6+OXrw6BPEfnq49+paxtuYSS5x4qU62VPjsTNk4KxWL5QwNYLLSJg/bJHaLBYVQNhhceqTs1Wp8GrVPrfarVXDp0Wqk6+v55MVsHZ7H90GFO5Jf2iUtnZSe3zEtbI2D
*/