    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_gcc_workaround.hpp
    /// Special workaround code to make the make\<\> transform work on certain
    /// versions of gcc.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    template<typename Tag, typename Args, long Arity >
    struct make<proto::expr<Tag, Args, Arity>()>
      : transform<make<proto::expr<Tag, Args, Arity>()> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity >
    struct make<proto::basic_expr<Tag, Args, Arity>()>
      : transform<make<proto::basic_expr<Tag, Args, Arity>()> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0>
    struct make<proto::expr<Tag, Args, Arity>(A0)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A8>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A8>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : transform<make<proto::expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A8>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A9>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };
    template<typename Tag, typename Args, long Arity , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : transform<make<proto::basic_expr<Tag, Args, Arity>(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef proto::basic_expr<Tag, Args, Arity> result_type;
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                return proto::basic_expr<Tag, Args, Arity>::make(
                    detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A8>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A9>::template impl<Expr, State, Data>()(e, s, d) )
                );
            }
        };
    };

/* make_gcc_workaround.hpp
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
*/