    ///////////////////////////////////////////////////////////////////////////////
    /// \file pass_through_impl.hpp
    ///
    /// Specializations of pass_through_impl, used in the implementation of the
    /// pass_through transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 1>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list1<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 2>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list2<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 3>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list3<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 4>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list4<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 5>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list5<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d ) , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >()( e.proto_base().child4, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 6>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list6<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >::result_type , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d ) , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >()( e.proto_base().child4, s, d ) , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >()( e.proto_base().child5, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 7>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list7<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >::result_type , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >::result_type , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d ) , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >()( e.proto_base().child4, s, d ) , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >()( e.proto_base().child5, s, d ) , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >()( e.proto_base().child6, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 8>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list8<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >::result_type , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >::result_type , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >::result_type , typename Grammar::proto_child7::template impl< typename result_of::child_c<Expr, 7>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d ) , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >()( e.proto_base().child4, s, d ) , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >()( e.proto_base().child5, s, d ) , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >()( e.proto_base().child6, s, d ) , typename Grammar::proto_child7::template impl< typename result_of::child_c<Expr, 7>::type , State , Data >()( e.proto_base().child7, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 9>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list9<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >::result_type , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >::result_type , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >::result_type , typename Grammar::proto_child7::template impl< typename result_of::child_c<Expr, 7>::type , State , Data >::result_type , typename Grammar::proto_child8::template impl< typename result_of::child_c<Expr, 8>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d ) , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >()( e.proto_base().child4, s, d ) , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >()( e.proto_base().child5, s, d ) , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >()( e.proto_base().child6, s, d ) , typename Grammar::proto_child7::template impl< typename result_of::child_c<Expr, 7>::type , State , Data >()( e.proto_base().child7, s, d ) , typename Grammar::proto_child8::template impl< typename result_of::child_c<Expr, 8>::type , State , Data >()( e.proto_base().child8, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };
    template<typename Grammar, typename Domain, typename Expr, typename State, typename Data>
    struct pass_through_impl<Grammar, Domain, Expr, State, Data, 10>
      : transform_impl<Expr, State, Data>
    {
        typedef typename pass_through_impl::expr unref_expr;
        typedef
            typename mpl::if_c<
                is_same<Domain, deduce_domain>::value
              , typename unref_expr::proto_domain
              , Domain
            >::type
        result_domain;
        typedef
            typename base_expr<
                result_domain
              , typename unref_expr::proto_tag
              , list10<
                    typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >::result_type , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >::result_type , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >::result_type , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >::result_type , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >::result_type , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >::result_type , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >::result_type , typename Grammar::proto_child7::template impl< typename result_of::child_c<Expr, 7>::type , State , Data >::result_type , typename Grammar::proto_child8::template impl< typename result_of::child_c<Expr, 8>::type , State , Data >::result_type , typename Grammar::proto_child9::template impl< typename result_of::child_c<Expr, 9>::type , State , Data >::result_type
                >
            >::type
        expr_type;
        typedef typename result_domain::proto_generator proto_generator;
        typedef typename BOOST_PROTO_RESULT_OF<proto_generator(expr_type)>::type result_type;
        BOOST_FORCEINLINE
        BOOST_PROTO_RETURN_TYPE_STRICT_LOOSE(result_type, result_type const)
        operator ()(
            typename pass_through_impl::expr_param e
          , typename pass_through_impl::state_param s
          , typename pass_through_impl::data_param d
        ) const
        {
            expr_type const that = {
                typename Grammar::proto_child0::template impl< typename result_of::child_c<Expr, 0>::type , State , Data >()( e.proto_base().child0, s, d ) , typename Grammar::proto_child1::template impl< typename result_of::child_c<Expr, 1>::type , State , Data >()( e.proto_base().child1, s, d ) , typename Grammar::proto_child2::template impl< typename result_of::child_c<Expr, 2>::type , State , Data >()( e.proto_base().child2, s, d ) , typename Grammar::proto_child3::template impl< typename result_of::child_c<Expr, 3>::type , State , Data >()( e.proto_base().child3, s, d ) , typename Grammar::proto_child4::template impl< typename result_of::child_c<Expr, 4>::type , State , Data >()( e.proto_base().child4, s, d ) , typename Grammar::proto_child5::template impl< typename result_of::child_c<Expr, 5>::type , State , Data >()( e.proto_base().child5, s, d ) , typename Grammar::proto_child6::template impl< typename result_of::child_c<Expr, 6>::type , State , Data >()( e.proto_base().child6, s, d ) , typename Grammar::proto_child7::template impl< typename result_of::child_c<Expr, 7>::type , State , Data >()( e.proto_base().child7, s, d ) , typename Grammar::proto_child8::template impl< typename result_of::child_c<Expr, 8>::type , State , Data >()( e.proto_base().child8, s, d ) , typename Grammar::proto_child9::template impl< typename result_of::child_c<Expr, 9>::type , State , Data >()( e.proto_base().child9, s, d )
            };
            
            
            
            detail::ignore_unused(&that);
            return proto_generator()(that);
        }
    };

/* pass_through_impl.hpp
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
*/