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