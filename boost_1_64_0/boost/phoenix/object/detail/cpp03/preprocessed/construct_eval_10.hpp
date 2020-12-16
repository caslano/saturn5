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
W2PtA4ablWR9czE8wrmD+Yiq2TSxAoCxzZPBG+zL3E5WxFvsA1yxWCOGMnwzjUPa8DpHu4CqmDrUZHN8RgCwNNT5gF9fUZhXOSo6kIkrRNL4apYZHox2uzrI5zg6TPNtAqdrq+fzTH3FmLzKcSrdGE53B6Xrj1wal5PT75FqXHuj2M3ZrrddXKTi+BoKR/LG0mJPqqjjpajzpKjzK50L+qRK8VVRs+c8J8ZXr/OoNp9M0LWbtzLPrZiLHeQE53kVxCyBWM4QA1wQkzVEhUCsFL5dnxTEMA1RyhWxWzKNLZ6BvT1TMoNImhoU615ciBlUytx43S5N4IzG0qCHq4ebmgA9Gg/OCGcynpB08rNNHwvrnlnyK+ljX9X4QuaAVUqXUxbX/72p+ienR1Mzh6o0p5lZg4NNwXyJ6Rw7F5HxNQ4N5qFQz5Sz11Du1EEeo0CO3s/yXEGqgSAbpW+N+5AQz6W++r5O9OrzqUS5PHZLypLREO/DL7qOp6mPjoP2v/UhffZ1e1GRaXca30CzZ91/rg95Sf97ufCPovm89vAcUjPYGC8V5t5pNEPMJ6sZN8929uzxywu4LCymtKnXMVdZUg9wmSxtd73ai7mLNwDtm/eiz21JO+fXTR+SxK1Ou/tWB4H9k9U+Opo1wCBjAxncDPh5MHNu3EejZGNudR2568o7aSeM12LYZCYS3FHpvOTTCZQpJDp4N9xyMQCA9e4K56cCwOvexNlUCZsm07NO/LhY1b3QhwaA5hHMq6Sct8xHFtMli22VzsJUFitolrsV9njwqC4lwDzG/o3Q6eH1nGYc0hw3EkflWzkdzTzIdbzkCktLn2OkIW6UnVzQoxnBLrMhoFCUZJSUZFeF43iZDm471lW8eiDjJvfJz0KDL16+kwOWS2YRyQxvxr7FKUOiviZoA4K2GZasJZJzpzkAZW/fz2V3cO6TSEbrqHxasdXGEEfqmyHz6PEcOq7ZofvQeJrxLkpprD5UPMfdPvv9FbPCLcA3pqwaMuOnfmBJVWQZcSTGYHTW097Wwq5b0N6upS9DHBfP7d1Fi9ijAPL4DJlOI3Efhn3j1JC6z0Js3MdoDkRvtIiviGYyEQFzs8hsk1vRA4i7RHZ65GVJoDvQ+fc3HrXuyJHPKX7G3F351I2BubGaYP9eQ/PuT79A7Px2mxb9iHvVusGi8b2rloM5XyNfkQJexyv24iB31Ozty+OZYAWkJ3yf7dcjPgU/inf2e/v2AL8+EsB8PeErbvth5zSuan9fv1LZqlyEuKGBwmEbpVE4QquS8MaeoF/wkMkMFwt9VL4le6q2egaocEoloGFWH1/tex5keHWR/awPLdWOlpI9729F4tLZKluKZwnXLZSaWZD2nDYAUsqGhg4mYewvGDC+qo1JoF/PslCtOAC3JIcN9TbcQuDS9VYv0SY5fYnLWsZ14jOkgxpyIuQG7J2ans4hIdx/VVTnVvuczwg59jxkT+ufPR+Oar/zMIdb9u91omqfLsFRkiSRK1Unr5hydUbDDbeQY7Zz6TNSQQxxnhjtmr34X2+0y9zHTLhW38dkXk1V/Mprce3dIT0JE7HzB9R9hfPUFi6EPh0V2vWmMqbaO5X966elOR+Fl68M/dWXscr9k0ist8/Us8VqVnsF78rOeoYjxWQg3+ENlgpLsSC/IHZFf5ERXKGZDLw/58ZeMoBBb9/KoImRBuJBs+cUiKUKItTyJfQM52ZQaO6cmKwdmxmACTpHgLHhlAl3hSA7xHd0ht+z6hrYT/suzq+69o+0X/Gman+dsDC+vVmzMK4zz4q4ZZPwJh5QsLmcjqWfIaas2GbiQDjWSiHVvU40QreR3HrRHF11I5QUYRI=
*/