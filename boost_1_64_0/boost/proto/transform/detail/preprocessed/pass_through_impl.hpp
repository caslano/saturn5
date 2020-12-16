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
HpTlXuT5PXOnM4bLHj/Zys1SPr/d2N0T+eefrd4KmENvBbhxGZqt5IbtbvR6Kx+wNviGn4cwQHwvMdPVYRDO53uBg9vrik18fhSR8vmRwLokX+LoXnIWZMOdJbk4QOkzJSh5FlZE9M4ONX62FCnVfC/LaqZS690yoQFeGtKLjiuevOl+VkO6iXTbReoctDy8e0SwlKsTA8T9LNDhzK0yonFr4arIflOyFXs/YEPsLKcmokMR+J4W6i3AuPta+jyoznNutMRzHlQfPzeKzqHgt7S5W9YFkmB72O4H0DsGvem1GTqTQp5FTBLq3hbZeB0c1YuVfTqTcukfasJYmYXxDlPvWTxLwvr+2FLsPTTh3PVw1EGIXxaUtTWUryPC/PVkovXLkQGNvaxmwssDmqDRQLMigJmC2vBRQTjWVkcHsNaw3o7BuJBusjT7/LHvW3PvW3M/wzW3gT0kML7/uQlrj1/luKcX8zswO7H75OzvNW/uGx/s977arFE425z63Wi+W6pg0MUK4TdvzdTnde1ilWDrCe9n+xDR2d39NXF7ud9J+FbY7pn/v5cwnwk84PQoi7ukRL0XJTDmNZrMzushhD+IPY1Ti+J6+bOL7dmtfPyWr7wbFe4BII27U3vapj+q9so/o961/KzyETCh9hker3H0eh9jdbmsZcHvCfD7K+WpthzrNaaRPD0tNHbPGD5dpT2Fl6kb+eiu5OZid/dTPpW3Akkg0EF/i7bjclbBt8tMoYHOjzrGu3iLXB1/kN4bLUkyXTIxp5bfR6Y84Owtr5baRNI9oRRr0cK4PD0l8PlCK//l0/IyO1Hg0rE4LU/71bozJCmT4FEnyD8+G+dsm7e5iUKh4/Qnki4PjYXx9IuJVuLjrpn/nnEp5VXyIvUSz+uiWth5Aq/bVN/hTNUG67zf0jqvUmB8Zl6Fel6Ceq6mPEwgHfgEtnmorUVc4HjdW4ew9EPto8Le+xwujveB/YmXxInxOhAyKPG0T2X7HSx47o+HSJj7W5Gqu8Nq+R1td0bIPJa6+hWavdfvMuIpaUocTSN6ndBw/9lQru7rc39CmPuFwGPlOKbW9S/BSb6Cc2J9j3OVk2vJm5Onu0uDupZo8sXfxT0O8nI/ycsJSl5OVOV5dljvwAmc+q28s+3rX0n7SX/Bp85o066M6H/Irypjo9DxmPsmetuQ/Y3K/XuMMSzLcxJrIGP3YZzTvq45zrpa+FSmNheY1x/WeqqTdZ5+3Ep4GaeFJo5vp36xTvWxUyQc0yFkr3jztPZ5u0W1PyUh4an8YlldZw50ne7a3HSd0F4vOB+2byPA32To33I8sQF2aRtq2S6tbWBivL9vdKDXEA1uHezvmxAtZ+CsyYHhILWeKSkk8Q0+HeafwNfIy6ZaNy+eSvMgjz8Cj9sVQNYMXMva8wRGduhCg3vuTg6En7IvkPDHp9XuR1Gbr8G94SnuB7ENt7JvneuxKc3Tvpton35zjvJzF+RnEvqn+N7caXgZ2BJbQwIbHB5h2BwD2zGyJfT5WWTlSWDDQ4PDZyYi2DwDmxzcInEjWIGBbQMM6RYa2JgkDH5mDCo1MHNkAJgZ6lIG1jcxuGMgEcHqbF7isEMMrD+AHQSfqVtI9o8UfN9EqFfjzQYvXa/Brzx68KgVltoFbRztx+X1yqfjNidbwDlfEoOQNYHH3jfYLnCeiw1+SGDaZ+AOxD+/LPRJ7sLaZ4GBTeCetvbBfBbLPPL14LRkPpDrvd9fcHLs7iHyfqg1KbWbWaH808GXO6dS94bzw7vwNnrAb57a95uv+w3bjeTYb8L2ORl2b9q+YyfNr0yj7/Wc7eY6wfv9P7xYaC6cVptoXwcYR/Z6X9E=
*/