    ///////////////////////////////////////////////////////////////////////////////
    /// \file default_function_impl.hpp
    /// Contains definition of the default_function_impl, the implementation of the
    /// _default transform for function-like nodes.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 3>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 4>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 5>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3; typedef typename result_of::child_c< Expr, 4>::type e4; typedef typename Grammar::template impl<e4, State, Data>::result_type r4;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3 , r4)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 6>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3; typedef typename result_of::child_c< Expr, 4>::type e4; typedef typename Grammar::template impl<e4, State, Data>::result_type r4; typedef typename result_of::child_c< Expr, 5>::type e5; typedef typename Grammar::template impl<e5, State, Data>::result_type r5;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3 , r4 , r5)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 7>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3; typedef typename result_of::child_c< Expr, 4>::type e4; typedef typename Grammar::template impl<e4, State, Data>::result_type r4; typedef typename result_of::child_c< Expr, 5>::type e5; typedef typename Grammar::template impl<e5, State, Data>::result_type r5; typedef typename result_of::child_c< Expr, 6>::type e6; typedef typename Grammar::template impl<e6, State, Data>::result_type r6;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3 , r4 , r5 , r6)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 8>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3; typedef typename result_of::child_c< Expr, 4>::type e4; typedef typename Grammar::template impl<e4, State, Data>::result_type r4; typedef typename result_of::child_c< Expr, 5>::type e5; typedef typename Grammar::template impl<e5, State, Data>::result_type r5; typedef typename result_of::child_c< Expr, 6>::type e6; typedef typename Grammar::template impl<e6, State, Data>::result_type r6; typedef typename result_of::child_c< Expr, 7>::type e7; typedef typename Grammar::template impl<e7, State, Data>::result_type r7;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3 , r4 , r5 , r6 , r7)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ) , typename Grammar::template impl<e7, State, Data>()( proto::child_c< 7>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ) , typename Grammar::template impl<e7, State, Data>()( proto::child_c< 7>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 9>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3; typedef typename result_of::child_c< Expr, 4>::type e4; typedef typename Grammar::template impl<e4, State, Data>::result_type r4; typedef typename result_of::child_c< Expr, 5>::type e5; typedef typename Grammar::template impl<e5, State, Data>::result_type r5; typedef typename result_of::child_c< Expr, 6>::type e6; typedef typename Grammar::template impl<e6, State, Data>::result_type r6; typedef typename result_of::child_c< Expr, 7>::type e7; typedef typename Grammar::template impl<e7, State, Data>::result_type r7; typedef typename result_of::child_c< Expr, 8>::type e8; typedef typename Grammar::template impl<e8, State, Data>::result_type r8;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ) , typename Grammar::template impl<e7, State, Data>()( proto::child_c< 7>( e), s, d ) , typename Grammar::template impl<e8, State, Data>()( proto::child_c< 8>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ) , typename Grammar::template impl<e7, State, Data>()( proto::child_c< 7>( e), s, d ) , typename Grammar::template impl<e8, State, Data>()( proto::child_c< 8>( e), s, d ));
        }
    };
    template<typename Grammar, typename Expr, typename State, typename Data>
    struct default_function_impl<Grammar, Expr, State, Data, 10>
      : transform_impl<Expr, State, Data>
    {
        typedef typename result_of::child_c< Expr, 0>::type e0; typedef typename Grammar::template impl<e0, State, Data>::result_type r0; typedef typename result_of::child_c< Expr, 1>::type e1; typedef typename Grammar::template impl<e1, State, Data>::result_type r1; typedef typename result_of::child_c< Expr, 2>::type e2; typedef typename Grammar::template impl<e2, State, Data>::result_type r2; typedef typename result_of::child_c< Expr, 3>::type e3; typedef typename Grammar::template impl<e3, State, Data>::result_type r3; typedef typename result_of::child_c< Expr, 4>::type e4; typedef typename Grammar::template impl<e4, State, Data>::result_type r4; typedef typename result_of::child_c< Expr, 5>::type e5; typedef typename Grammar::template impl<e5, State, Data>::result_type r5; typedef typename result_of::child_c< Expr, 6>::type e6; typedef typename Grammar::template impl<e6, State, Data>::result_type r6; typedef typename result_of::child_c< Expr, 7>::type e7; typedef typename Grammar::template impl<e7, State, Data>::result_type r7; typedef typename result_of::child_c< Expr, 8>::type e8; typedef typename Grammar::template impl<e8, State, Data>::result_type r8; typedef typename result_of::child_c< Expr, 9>::type e9; typedef typename Grammar::template impl<e9, State, Data>::result_type r9;
        typedef
            typename proto::detail::result_of_fixup<r0>::type
        function_type;
        typedef
            typename BOOST_PROTO_RESULT_OF<
                function_type(r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8 , r9)
            >::type
        result_type;
        result_type operator ()(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
        ) const
        {
            return this->invoke(e, s, d, is_member_function_pointer<function_type>());
        }
    private:
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::false_
        ) const
        {
            return typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )(
                typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ) , typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ) , typename Grammar::template impl<e7, State, Data>()( proto::child_c< 7>( e), s, d ) , typename Grammar::template impl<e8, State, Data>()( proto::child_c< 8>( e), s, d ) , typename Grammar::template impl<e9, State, Data>()( proto::child_c< 9>( e), s, d )
            );
        }
        result_type invoke(
            typename default_function_impl::expr_param e
          , typename default_function_impl::state_param s
          , typename default_function_impl::data_param d
          , mpl::true_
        ) const
        {
            BOOST_PROTO_USE_GET_POINTER();
            typedef typename detail::class_member_traits<function_type>::class_type class_type;
            return (
                BOOST_PROTO_GET_POINTER(class_type, (typename Grammar::template impl<e1, State, Data>()( proto::child_c< 1>( e), s, d ))) ->* 
                typename Grammar::template impl<e0, State, Data>()( proto::child_c< 0>( e), s, d )
            )(typename Grammar::template impl<e2, State, Data>()( proto::child_c< 2>( e), s, d ) , typename Grammar::template impl<e3, State, Data>()( proto::child_c< 3>( e), s, d ) , typename Grammar::template impl<e4, State, Data>()( proto::child_c< 4>( e), s, d ) , typename Grammar::template impl<e5, State, Data>()( proto::child_c< 5>( e), s, d ) , typename Grammar::template impl<e6, State, Data>()( proto::child_c< 6>( e), s, d ) , typename Grammar::template impl<e7, State, Data>()( proto::child_c< 7>( e), s, d ) , typename Grammar::template impl<e8, State, Data>()( proto::child_c< 8>( e), s, d ) , typename Grammar::template impl<e9, State, Data>()( proto::child_c< 9>( e), s, d ));
        }
    };

/* default_function_impl.hpp
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
*/