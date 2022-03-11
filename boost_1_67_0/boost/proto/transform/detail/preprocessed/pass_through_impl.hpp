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