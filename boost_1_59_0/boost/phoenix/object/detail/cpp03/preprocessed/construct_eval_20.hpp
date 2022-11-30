/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1, typename Context>
        struct result<This(A0 , A1, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2, typename Context>
        struct result<This(A0 , A1 , A2, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        struct result<This(A0 , A1 , A2 , A3, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx)
                );
        }

/* construct_eval_20.hpp
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
*/