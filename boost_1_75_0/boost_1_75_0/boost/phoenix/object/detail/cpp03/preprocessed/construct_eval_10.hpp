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

/* construct_eval_10.hpp
Fyf7o++qPSku+kphRyAa5t4kaDRiCgDvA75D8HW1U+C7xT8lSe2mDPLD4OrsCMqiAXHwIT/0VrS/i9k3ASeAAP6Botp4FWqFlKYRYhGn4Y5g4G7fkhARbvoyfHJLeebSe9a6+3zRdAVhJVpuL9ou/u3r1rdvXrH618g7xUF31D6xAm5Nbgz4MoFFA49HPwHaI+ANAHEmFP+KzDBgXIK86Nr8mPaoju2xYwAs/G7goCorAviftgIKiCakaoDjzQzHA0k6biKCsxw4zXsLsYghZDJ04wUJVTkx4qzRGpDkerQLRz3jUlDAq0PHTm27gXbVyAVeXViWJc6aWIIN3XgVGbLRtc5bRXtovBPz4V1OoWFJXPwcaLcSKdwAdE12JFdm1QEBv43fDaTQddS5xz2uT6arnlRNXmwp8u10Z96J3Ky+JJWM2gRreJmYsnTatWAyxS+SjrO1ZuYMNBDB6azhsty6zuRmXWENnBv4VsUytA7jxpZYkRHaRdDAxsG5B96qHLwV/Vd0hDWgJsiLA7iraRl458Zc4G0roXXjiwskiLYm7iDrlppCnKR1cczVFUw4LHbBqMlzJisCvA9XDaRjAu+AjZqeN3aCNVBlZgTIx1hF8k7UUqrzYjHr+uLUrrBuQVsrANPG/ev/ddaJpSnAiPzqOhimxVUN/YNfLUcNpGMCg2vwPhI/ksQiLQfu6pwYkKrV5sVymHYRHXeb
*/