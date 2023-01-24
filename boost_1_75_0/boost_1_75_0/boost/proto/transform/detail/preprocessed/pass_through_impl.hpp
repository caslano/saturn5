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
Z5Q2fnBvtD463XeCM/jjyr/HExxeYSUcMqSQ97PMumSJ2itynM6m0gRWBzwRFembYEqRmt7LtyEnXKJFpuUUHPZSFMx8TybSUZ5JMsg6yoHm6CUbJBuM6OAcNP2gJ695kI8hq9ZojHCyiqvNchQst4CD4z1rhvQFV4L1egVq0c3YqJTbUaLnqRzmMaWDWu7mx/0q4CZCUlyJJuKHVwsQe9svFBppkMDKcN0lCRq7raWDwYo/thEdL+HrYHzsjq0l3HZTX+6hx2Dtbqw5BWc11LyKqlZRXw45AF2o21ScUIr0CutR8kz0W7NaaX0lU+hMmKSN3fMPYsgacdBP3fTEtl3JvEtlmmf2Yq78QgYOpSO2o+KwwZaMKCmgzEvIRtNtjjnvwbVYAkZnEYrXmPqIHR6vEz6diPn9eBT/lLhYvo9d+dFlPbPzIWSmT9s0oOb7zcljctcW15h2erv3AeIyh9GXDaWf4H1h+so3FcWfgLjbYPEtMR3fNRb3YTk7K/i8voH44OsSFDvi/1Tys30j6JvCPRfvndgmGWsXTkDayDl65ieRnFGKt2WdN6cL+s6gqPRRfVqmLG5VXRuSGRbfc8g53O2FAnUj/XWiG21S7/6v0+hrji/G2f3wxc1qIfPhm0f/b1LXSsOjYTZH2ylaDWWW3I3Ufq60vM7fwChijoDEWDWatWKXGcAPVW+oCCwOpgqDwLhgVUImV063
*/