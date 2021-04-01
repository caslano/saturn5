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
1L3msS277vv32jwNlqvDQBubv1y+ga/Lm4a5bx3qUK6mK73ibZQ0ySXZ+18BgrLXgyZHhNM6m719Ox73Qf2OujA5k6F1nVRKiDT1xP9GARvfxYlR9vQHUDOrVpS4ZG+ihJt31P4/JnrphqLYl2Hmm/wtGXMsFbnYxk7tsik0izw99cq5VvqXM+9ZJCWBVegR5SWAplKjk//DcZiqwmg744n+EJHqjkyX9Fcs95YMqYjDNOLPWtmvw7eyxraY4ms3VPizyGdNjDFP5FAQOcghqgsa8/mjhBRVDM85m9ECYilLj9J5nHVZSp9CZ0iveFRD9xon1cNIghQOQJzcYNDXDcozeDPjQG/XuvNBjGPcieqLXw8mm2+0BkPEIKKsSH82Pv2esAMdE9dF2Mg4yNsp3qXPApPd3j/0F0e1G6KmRSBVpqrXS86Y23JomBIcCW/XaISEQ4arSbJJPaLT/3h1DPx0zzupQNgkj+SMI3yh2f5aq4+TJdy+mJ5FBrJlOSW6AxrvXe3NA2ov8Tj8BUZIEz0EZMgKP1PowyZzBW3yq5IUxlpJuA3Qyc+SCQ==
*/