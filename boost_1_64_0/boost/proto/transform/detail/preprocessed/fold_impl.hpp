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
psc1HXd8VOwNBlRkACHb/CYXvz1SjM+dW4ofDLTbX9FufIanbWCepjO7jRVOBpaVBPhEpcObuA0l8fgzBa/8qSFvcduipNDZMiAfR5TE76wLXexsak4lv7XmP8PMI54Nih/+x3jOc2XBmWe8LAWCP3lqncEuB6zu3yV6HGsNGge9Yb9Kd0b3ONstunM2oXFnZMWV8fO3Egnz+VupK4PgXJ0Uor0Wgf7WQmcTwHe2n3CfuoM9O1FRSbaXlcrHAeGKFK4G4eEKl6Yp1zY6+6tT5VqCOHeVBnHqqb0/LrBvSdxdOD/eYcsme8uqbKMliANfJJuK7GdpLkGcgxHHlEfb/huY0AVlwRuEh5E875jCNmBpmF/wMfWv5XNZJfxdg0b7uT6XbNGlTq11xJHUvgam+9sK1S8MTb1K92jiMYw+z+f2K4nHuVns8o5V9RDeg55Q9n/HE6/2oF9LmGlk77cSttmQec7basFx3p4D2hPkv6ZNK9oG0K7y0DYp2oyE2c5EQLsN/nqyJ+Gx4Xo1TjaD3zmuX0GWQUv9oSWsf9SvvlPbRvjvwy4E7zhYfEclyRrSQn0izO2n/dvDrhI86igOv7u+RNlG7tD2lSxnwGv5Pk3JkbS986MJmtMryaYXdk2webA868iOhcdtbfPQi7a+h2wI+iqdbwnB2bC2W+0XGOxWKU4ysYXlm/Ku/a5sFTqulw+qehtWfWtQ8ZVyoYwB3ST4ngk67WtmIhEfZ3ZEdeza4IEyphHbNkXj689nkfzCHw6XQ744fkLoGf+UKudOhR9NxvFn09g3QR90BMy/HGdu4sVo43O4P4P2Jao/v5TS3166Zx87j+UX+dPy+3KiYd2B5feVEY0bu3Xdvhr5fg3N9Y/RXP+AGve2SMPdrmyjLkD5BBd7Q+91nnlLYEqe5A1Okiee52+viMvzRTSPn6/m8bcQ7nUK9zaU8XzVNobvO1Qfeafj43Dg825qt0nY3/Bbtu8FvdQPfM2TXOIuO4/zD6tx62I197kyov+qMcv3nsiHUdaPeOaVSxW/j6r0JhNx/GUKX6p883+c8iN4KxtaTq8IadAud5cGtEzzSdffYEfIn+KL/nYVyrkN5eR8fEZgs9RY/lnQz/XQf95Dv4vkoE/J0xclzHaPfCdR22FdjXS3e9rjWtUeXwbtkIf2q4r2OlX3Jr0rS+NluEHR+MbWm9T461tL34x8fd2Tr1tUvr4B2jEP7bcU7bdV/nzzw3cR5/uYgz+jxp4OJaN6XXSrnoOSmkbOoJDn2zx5vl2NDz+WcEMO6yxzKIUllgZH+0s/QXqG/09JH+D0f6rq7E7Sr1h/uIvG7zvKwJf0uEvL4+8a36PWk8Nshyz4X6pyX7go4P1ryvNo0ulFvD6eVSYf+cwbVevj+1Ta2jb5fh5nYY/NPtQeIPwsz5vgD6o29/WNh1T5Pkv3aGeRXqf9Jz2y9/aXg3AcxbIAMBzr60fdulJ+u/XmY2q9+Rc1Dz3uyi84l8c6tN2ToP9zpdOfx6ZlpxfY5M0im7xkQNfeRXd/2B5vjucOkd9Gb1NrR4fjk++xx5un7OvmK/u6giz2dQtgX9HVJZeQyTYPsOg8baHH3q7QYwtWNIUtWHEWW7ASZRsEG73OzKbm6IyvTNkXLVL2ReXKvisV2snAcgBmlJa2QtmeVHrsvqqy2H1VK7uvmix2X7V72n3BTm9jzNaqTtluLfHYbtV77ED3V/ZcB0xhz3VgDvZcBwU069o3Bqe0Bnawx0buEGX3dWhkk9XcJNUs/IM6PUzZZT2LbbAAWxrCjGUkYIeHMEmjU4oc2icui+AtkrRlYuFHRPBWsU1Y29ne0xHV95HKVmp5FtusFR4=
*/