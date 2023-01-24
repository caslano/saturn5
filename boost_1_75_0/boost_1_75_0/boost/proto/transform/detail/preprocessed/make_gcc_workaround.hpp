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
IKas+cbYVd31nXJ0uyCijL8jnNEbZR3NGPwgmM9vHiGdvhS6x8oNxH9u9tmzU58Ml3xQLZ2oMxabKHeqLA/taemPZnzwyB+EuXbW3ua07B4Jy9p3+4gfAbv6BgkSCPvq3UdcXxWO/OV79ipsZEa2FvsiM4px536Cdy6FhyN4ExdgaDZmOeMsxPtJbCjSiyKWjHc+Q79IJBX4yWevMN8DoVCaEnWf2bSd5baf2Qli8EFiBsbmzCS27NrUnzsHxgVDc0eEPXkqs1SGj9nH2Md+JAtQO2//2TqJqaIhoPzIurz4rrZ89NhHPSe31Jafb/V1Dbj5zX3M7zp4prg9RYBmjsk2yN6yvzmyHvdUaxdslHAflzPMd4LjUzvl7vGGa9I2cbHMQ/RwYFhAa0sgxGcj+C8bAGS+rCMw64eSoQT+qsAqxR7GKYC+fTqVFqiprr3wwSK5q8+13bLNPJSAdC2eqQNfYXrwL/fU111TEUCZc+Jrj8iIv68b+YSRJNHvVi4UNxEkFdLNJuWig5xcyVFfppzM88ADATi83qhT0gEaTBVcRKDptV9ldhqtTqFNTBU1StWAwew/yb+6BnH0Yoj0+A6+xPFDP5P4pfwll4TBhyc28lP/k8fWLUlISsjYq0uv1q8LkhtkuKb2qjSlvjRIaaeyN7NGz5K65U0cg/YPSOmqvPp416rim+D8TzhHyX9BJInrtP3FxLAUUtXb
*/