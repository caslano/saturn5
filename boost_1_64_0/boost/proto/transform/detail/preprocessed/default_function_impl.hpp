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
VOkUqjIWIZ3iCvJ7rPaVS1WcMsRZhDgYC2QP1u3xObsv0ZNB/7jjK79dXVSpPFYjvUrURQ3i11Ien1R5rEOcUsRZgjj1VP+zqP4PqHB94cAK9U6VhOWL9YWDwe8Q0CLf7n6X4vGsCvOp+13gcTjlaSHl6Qjid6Tit1zCyxW/FeB3FOXpAFWXxyBOEvWyEnFWKbpK1cbHge544n2EinMi4hSC97MRZzXojs8qs+NiESed0oktg9w7blQfaVUfDRJuUPXRiPSbVD7zVdnWgG4tle0kxZ/vNzULzvA/GfEqLK2b3y4UgW8RmMxv0gfiNo+tiNOs4hjadoGR/iE0uM9U4fIusNjbpZ0SRn8TnP8suDuIL2VysrVBlc/mVdXfJuKdKQlo6vSZitAwj2bF43Sua+QX+yjRWdfqad3/l3m3za2dZ3nWwUk1f89W94DmeHxhztVrYMz7Wj/PT2g9PtobyWwE//lYu8v6iu4PNfSsxTprAe/L8H6IXZjwXohcFT/KhrEHsnHjRugbxdA3XlCRm75xcuyu5paBUbFEcjZjZ00ODkxE4Tzc/0ZY8j82IJeHhnstWNoPto6bK9jWEe7aRkbNdBtZ4Wio9G7eKxMR0fcMtm6RKWxyeCKxO7QzSxpY39hY34uEFvrFAKWdnCH48YEgQftT2Zjp8YdNghHU95uCZc3ETmEW2NoCljSwSQEKbZiX7TFdxzxDLQZ4ljl+Z7UN3zw4ovwhxiAS77BsZaD8711PjKfhIE5POJPGwm1qXt8hYaPzDaNvS9iOBSMYZ86gceYsxDV0Y/Jbn4MIzPkMklgT0Vin+AtuJ+EEFr/vVMH5w1pF2bC9OBqbEAf5PZPy+1I1V5yr4pwnYX8beGQOPF8Ont54fvmw+Xol5etVlodbw5n8vKLCfa+mfM6VEe41mGdea+Mpn0p1wT2OIeJ/AbXT6z3tJDCLG0ZbvJHGfQPTZxZvEhjmNuD9dh5vVnyiNzDA560Kr9+ne7trd8HjLrKao94pcNSb0Ggf2Movmcu35TOZCGgTap36XiVvvjuD71c0Pl+GF1P5dnjq8YNKznc6ekv7XFUfH0G7XxqtEzC3Jhqa23tb2tvX94h1eUuz2QWycyrDxUuNzEIyNs2145jh+THhIxShS9aJF41iRlFAM6egrFG9al3hcuTt46QP+sfAvi1bxthJpoLZcXAO4nIc0He7sNBGdpcTyT3b/hMVykchRu1PIq9X0Dh4FX7ru+WXVTh+n66I7418BmPMFdTXPqfGmM+rMWYXyeAEf0oGvwjeVxLvq6kfX1Ph+HHbGLiWwy/T2HqVkrmvoi5MOtqO53oPrxuov+k61/3tJqT1ecor6wMXyT3HLG9Biz9iWb97lg9eDOa1W1CG1VG/sDvlLT3GCTx0rRkRzPyHrhnC7Ma58TcxV6BBH/lmBbigG3Wf2pEJOomGSiZEd4D+G51LDsd8XGwfkWLsRlhaebRvYrsLiw+TkTHBO11sctwWVfIUwgrtnCL3VwhWavSxzSPjAwJrgE+Z71SwT5mJoXG5wBQ4QSZ9SIFZt/D73NnQkO7KhLEJ4ObD77mxicotGyWDwwkT/r7gk4md0T2ihfYOp5RzLGHStfX+A8q73GcfGx0f2ynm3TvChAliU755wXTWGL53C46mt5BW0ltI6cZGOciKn7l2tHd2x9/xad6EvUSEW+SYLn4Hug2MAtg8tUZw6wr7UGHvBoUrUHuSWGfQOghrDMgz1hjqnSBaa2ByMLurdOYKfnZz1cKK1dqqxHPmWBqdkwZxykI+OKeJv2PQtM7eekLc8gAWJWpgKQez4YogLIm6fFUGMJuoCVdFNAG+OghTJnDuSufXYb4=
*/