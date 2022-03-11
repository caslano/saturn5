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