    ///////////////////////////////////////////////////////////////////////////////
    /// \file fold_impl.hpp
    /// Contains definition of fold_impl<> and reverse_fold_impl<> templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 1>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1;
        typedef state1 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d );
            return s1;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 1>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state1;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state1 s1 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 2>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2;
        typedef state2 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d );
            return s2;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 2>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state2;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state2 s2 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 3>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3;
        typedef state3 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d );
            return s3;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 3>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state3;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state3 s3 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 4>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4;
        typedef state4 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d );
            return s4;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 4>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state4;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state4 s4 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 5>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >::result_type state5;
        typedef state5 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >()( proto::child_c< 4>(e) , s4 , d );
            return s5;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 5>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state5;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state5 s5 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >()( proto::child_c<4>(e) , s5 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 6>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >::result_type state6;
        typedef state6 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >()( proto::child_c< 4>(e) , s4 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >()( proto::child_c< 5>(e) , s5 , d );
            return s6;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 6>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state6;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state6 s6 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >()( proto::child_c<5>(e) , s6 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >()( proto::child_c<4>(e) , s5 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 7>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >::result_type state7;
        typedef state7 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >()( proto::child_c< 4>(e) , s4 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >()( proto::child_c< 5>(e) , s5 , d ); state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >()( proto::child_c< 6>(e) , s6 , d );
            return s7;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 7>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state7;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state7 s7 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >()( proto::child_c<6>(e) , s7 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >()( proto::child_c<5>(e) , s6 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >()( proto::child_c<4>(e) , s5 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 8>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >::result_type state7; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 7>::type , state7 , Data >::result_type state8;
        typedef state8 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >()( proto::child_c< 4>(e) , s4 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >()( proto::child_c< 5>(e) , s5 , d ); state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >()( proto::child_c< 6>(e) , s6 , d ); state8 s8 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 7>::type , state7 , Data >()( proto::child_c< 7>(e) , s7 , d );
            return s8;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 8>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state8;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 7 >::type , state8 , Data >::result_type state7; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state8 s8 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 7 >::type , state8 , Data >()( proto::child_c<7>(e) , s8 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >()( proto::child_c<6>(e) , s7 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >()( proto::child_c<5>(e) , s6 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >()( proto::child_c<4>(e) , s5 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 9>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >::result_type state7; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 7>::type , state7 , Data >::result_type state8; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 8>::type , state8 , Data >::result_type state9;
        typedef state9 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >()( proto::child_c< 4>(e) , s4 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >()( proto::child_c< 5>(e) , s5 , d ); state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >()( proto::child_c< 6>(e) , s6 , d ); state8 s8 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 7>::type , state7 , Data >()( proto::child_c< 7>(e) , s7 , d ); state9 s9 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 8>::type , state8 , Data >()( proto::child_c< 8>(e) , s8 , d );
            return s9;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 9>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state9;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 8 >::type , state9 , Data >::result_type state8; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 7 >::type , state8 , Data >::result_type state7; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state9 s9 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state8 s8 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 8 >::type , state9 , Data >()( proto::child_c<8>(e) , s9 , d ); state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 7 >::type , state8 , Data >()( proto::child_c<7>(e) , s8 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >()( proto::child_c<6>(e) , s7 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >()( proto::child_c<5>(e) , s6 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >()( proto::child_c<4>(e) , s5 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct fold_impl<State0, Fun, Expr, State, Data, 10>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state0;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >::result_type state7; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 7>::type , state7 , Data >::result_type state8; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 8>::type , state8 , Data >::result_type state9; typedef typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 9>::type , state9 , Data >::result_type state10;
        typedef state10 result_type;
        result_type operator ()(
            typename fold_impl::expr_param e
          , typename fold_impl::state_param s
          , typename fold_impl::data_param d
        ) const
        {
            state0 s0 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 0>::type , state0 , Data >()( proto::child_c< 0>(e) , s0 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 1>::type , state1 , Data >()( proto::child_c< 1>(e) , s1 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 2>::type , state2 , Data >()( proto::child_c< 2>(e) , s2 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 3>::type , state3 , Data >()( proto::child_c< 3>(e) , s3 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 4>::type , state4 , Data >()( proto::child_c< 4>(e) , s4 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 5>::type , state5 , Data >()( proto::child_c< 5>(e) , s5 , d ); state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 6>::type , state6 , Data >()( proto::child_c< 6>(e) , s6 , d ); state8 s8 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 7>::type , state7 , Data >()( proto::child_c< 7>(e) , s7 , d ); state9 s9 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 8>::type , state8 , Data >()( proto::child_c< 8>(e) , s8 , d ); state10 s10 = typename when<_, Fun>::template impl< typename result_of::child_c<Expr, 9>::type , state9 , Data >()( proto::child_c< 9>(e) , s9 , d );
            return s10;
        }
    };
    template<typename State0, typename Fun, typename Expr, typename State, typename Data>
    struct reverse_fold_impl<State0, Fun, Expr, State, Data, 10>
      : transform_impl<Expr, State, Data>
    {
        typedef typename when<_, State0>::template impl<Expr, State, Data>::result_type state10;
        typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 9 >::type , state10 , Data >::result_type state9; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 8 >::type , state9 , Data >::result_type state8; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 7 >::type , state8 , Data >::result_type state7; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >::result_type state6; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >::result_type state5; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >::result_type state4; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >::result_type state3; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >::result_type state2; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >::result_type state1; typedef typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >::result_type state0;
        typedef state0 result_type;
        result_type operator ()(
            typename reverse_fold_impl::expr_param e
          , typename reverse_fold_impl::state_param s
          , typename reverse_fold_impl::data_param d
        ) const
        {
            state10 s10 =
                typename when<_, State0>::template impl<Expr, State, Data>()(e, s, d);
            state9 s9 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 9 >::type , state10 , Data >()( proto::child_c<9>(e) , s10 , d ); state8 s8 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 8 >::type , state9 , Data >()( proto::child_c<8>(e) , s9 , d ); state7 s7 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 7 >::type , state8 , Data >()( proto::child_c<7>(e) , s8 , d ); state6 s6 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 6 >::type , state7 , Data >()( proto::child_c<6>(e) , s7 , d ); state5 s5 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 5 >::type , state6 , Data >()( proto::child_c<5>(e) , s6 , d ); state4 s4 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 4 >::type , state5 , Data >()( proto::child_c<4>(e) , s5 , d ); state3 s3 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 3 >::type , state4 , Data >()( proto::child_c<3>(e) , s4 , d ); state2 s2 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 2 >::type , state3 , Data >()( proto::child_c<2>(e) , s3 , d ); state1 s1 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 1 >::type , state2 , Data >()( proto::child_c<1>(e) , s2 , d ); state0 s0 = typename when<_, Fun>::template impl< typename result_of::child_c< Expr , 0 >::type , state1 , Data >()( proto::child_c<0>(e) , s1 , d );
            return s0;
        }
    };

/* fold_impl.hpp
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
*/