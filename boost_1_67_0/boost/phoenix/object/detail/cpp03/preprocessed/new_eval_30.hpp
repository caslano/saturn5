/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1, typename Context>
        struct result<This(A0 , A1, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1, typename Context>
        typename result<new_eval(A0 const& , A1 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2, typename Context>
        struct result<This(A0 , A1 , A2, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        struct result<This(A0 , A1 , A2 , A3, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx) , boost::phoenix::eval(a24, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx) , boost::phoenix::eval(a24, ctx) , boost::phoenix::eval(a25, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx) , boost::phoenix::eval(a24, ctx) , boost::phoenix::eval(a25, ctx) , boost::phoenix::eval(a26, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx) , boost::phoenix::eval(a24, ctx) , boost::phoenix::eval(a25, ctx) , boost::phoenix::eval(a26, ctx) , boost::phoenix::eval(a27, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx) , boost::phoenix::eval(a24, ctx) , boost::phoenix::eval(a25, ctx) , boost::phoenix::eval(a26, ctx) , boost::phoenix::eval(a27, ctx) , boost::phoenix::eval(a28, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx) , boost::phoenix::eval(a20, ctx) , boost::phoenix::eval(a21, ctx) , boost::phoenix::eval(a22, ctx) , boost::phoenix::eval(a23, ctx) , boost::phoenix::eval(a24, ctx) , boost::phoenix::eval(a25, ctx) , boost::phoenix::eval(a26, ctx) , boost::phoenix::eval(a27, ctx) , boost::phoenix::eval(a28, ctx) , boost::phoenix::eval(a29, ctx)
                );
        }

/* new_eval_30.hpp
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
*/