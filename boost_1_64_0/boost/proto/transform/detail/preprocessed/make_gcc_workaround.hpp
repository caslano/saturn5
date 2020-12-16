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
/+js2PHeH/3CxGmDvDPvDuTpFOTJ+b2Qfq/S1fdsuquxBqN64/5Ur/aRNxC/V5a4cpxbjDWeql8Bx8+lQvmm/tUY/UeaSr5Pp7ZFmvYrVnvPz1f6ipQddQjeSRtHztPdeZnUia3DPtRhLeqQ66yf+UoZtqg6lbqO4bcq/K3qjGm7qwPoYHvXA89QeuBzkX+pQ8tzSPAIQ35cnZ0tdfYF1K/gY3U2QnV7DvD1ug2E7izUj9RbbG9oXOBoN9qPkX1Wld+wDhoxzu1U6cr+Uqzc0vdsumc7PpKWSkf4vJjwwpvb1eJf4vA2rsaf6+Qf/SP+aVuJl1XH9+vSOFd9hdaJ4b8+piNL+IJpvd/o9MRZHl04qXTH2dD/ujIrjwaN268wa3Q6j3hNjnrK9PIv6cbyL0p7ptNc1aH8i+V5F+e/K71G8C7vMJt/JJ7/1+WYf7S1nM2hjelc8fVqj/ACams+L5S4sTHijZ7x/EK1l3CJ7CU8Pa29BLVXRTAxuOwI9pJyfb/T7R3M9ez35Hn2ufI9+1zz1L7UfM+6oYBg5jZOaMe5QO1X7efZr1ro9qv0Hpbw2xDVRRHywXfSitWeVUlQ7kymE2vC7PtYoHP3CBd51oDlnjVYKqBrCtuxIgzL9ZpQXqsgr2/+B+UVYxPOFPz+pd7q5juhn4p2duLtTvd2tPptIFozYP7k/RLRE9yYemk5j6v5iXcrnfSCMoz3VBbhJXHj88z7KF8N0FfPUfvKH1DlRPm85bxEzcV6f/1Dqp+Oyhj9mmmNcU6WZqm+l1Rr1tlqDT2H+rQe3y7NUV78dnT2WHGUFpEMiM75P1a9p/+aX2OcvExw3E6XS3jltMazXPd74v1zttoz8dWbG9f0mObi5KtxcJ5nD3V+2F4WgX1R1YYLVBvu5/YBMIbhHmxTs2mpdAvm3SK06ydybNfpnXPkWtfPZB+6u71j/bFuH1rqornbvS+ZDxjGcJ43LIjrGjAhR10zrBP1zbAO3n/esILrXMLLw3Ah8B2da2jP2ebSzRVKzko8clbqaUvee74yx7b0+2I05z/LV1h1pyG9NuyoChq9Vf2parfncFW1e/v102r98plq8yk/CdDlPwdaazdAv69SexhfCNf+1fCdgvhfUnS71PrrGtBdCzq/XcTomf3jxxqP0Dt7za4WP23mQ2G8CtdP15W7OelSvD1v1uB6j+Sr1X77J7xONT4YGfZTGHtr11PdfIV+X0e/b8JvPpdiG4SvCZ7npZsRvrHazY+8XrpRtdk3aM34sD3HcvrA/gl8KPMfC4Myf4vWNhIH9Pyf6eckvuPWZLRHpumSie8RHXQAfQ5t6X5AdMDbcgkfS3dDdUD3Q7VWvEGV/TbI0Y2e+enHAuN1443geYfiKXQOLzx/Cp43eHjeSTw5nz9XPIXO4YXnL7AfeD31zXuq4+vle916mfIj92UR9ysU99eqf/1GwnxG+ttqh7tB9b3fEe5Ghfu90nmuEp3n9mnqPLnNL1OsS9Q8OtfNs27+xnVhO6+4cOyu7DyPDlWA8fnBHMdn0w4fo3Z4yCMj27AnvFvpRQ8rvXdVUVxmtD3Vo4b3tM7N4u85z0I9ysKkK74vIBBZfbu6lzDuV3P9c11ibdjCsLwAlmZYvmq7eZFM0LoQ1pWkQ21sh18N1qNa042yROR5XU6cJLH4mhDeDNz8rvUOzPHCzQKxJgQdoFgXRjA6W25pXY84Zerca1HIN90S1V15tIbuaMhEa0HUsYBA5/XrwmvUqoiPWcjqM7MEnZc1dmENHr23xr4gFqu+Vqf62hKPvlPv0Xf2j2Ab2zuR5wM8/jsO9PjPOMjj0+Ngj0+NQzz99TD018dy7K+hb/c=
*/