/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0
    >::type const
    bind(F f, A0 const& a0)
    {
        return
            detail::expression::function_eval<F, A0>::make(
                f
              , a0
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1)
    {
        return
            detail::expression::function_eval<F, A0 , A1>::make(
                f
              , a0 , a1
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2>::make(
                f
              , a0 , a1 , a2
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3>::make(
                f
              , a0 , a1 , a2 , a3
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4>::make(
                f
              , a0 , a1 , a2 , a3 , a4
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5 , A6
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5 , a6
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8
            );
    }

/* bind_function_object_10.hpp
L3LeyIfHYOnLxZYU0CYj/fMBsx/I9vwyycM0J/xdoZQtXEktBQjAVrydtpUu8nVLq6LIQkJNAbD8HlyxcFdVVYapnxi4sdzS55MU4dwOYOGG10AIJXJ7nwi14JhzfVat3esX+RsUlE3kRqFGL/UDqL9jfjbt1wusfwh9cOTiJfU57lHrbGzLJRcX+b4pXRdiSWLM+1DcZXAI5SZqzU8vctmujqIqLYuQcJMNh4UiO+QXsHtg2R5gQnGT3Jh/8t2WLzqj4QGsfyEcGFzYRvOxNDAzEtFwko0RgS8va2hbK0mDsmFvgRJjCYiX2R5wO3STREVQlGNJwCBzglefAyGmf8Rr7HlIwcoU5jx0ue3xvshYNT4PH2E04N5Kq9L3wE9BvpNehsoXfuvUYyEjDMWmwJiGLemX1lyGQVglWWTMQ1d7thV0horP53TsOG3tCQ8G4CTQZAiRZBwdpk30wGnrrYrTGMxJ5Iy3ai4o3ImFO4pcWI9DOgvdVhqzHwn3yMJdBg0Yizxwxgs1pHs/bd1hWR24SVRbuMfuQ3WW38zG8PDdBdjyPOa4h8hZpPse0et/mu/BIPPD0o0qC//YTTijeBRzjNKp86iBUSpwtPUQAeIS8brq82ezD8Qh+H+6Udw4PIqG8187zvB30ktDD34CNSGC0VioFpTgNuT37Z4zlu3by/ImqP0O6dbySv/G3aPmyTnDeQsw/BBhk9QRgZat4LY4nCdlBnk/GWf1MdYYsajDlpfyo/HAiT1t2Dptv4xzrH+B9zYJYWVpiIbBwgQq6L6waEhhDHOzopsDAS4WfVoW+dPdiVe5cMaSH7wyE/naiQb4F/UNRXqvfP8M91ODPiKKYB4wiywo/zqtlz3DZY4ySvBfn1CaLk303QzvriWGt27KLHXx2WbhB4l3Q+HdvcTnygs82NrdykA8YbbpbDpL1jubBHClAZ9gVlWQ823bZE6wvqWwQTRhEQQOLJBHZketnLQIBv5oo1476TBlyatPWbLkXS+pkywPcbmOSZnHz8zLlyw/i7ys0iY29v1oFW+c1DBbthzWt8KdCB1qItdaoJ18ubna/2+Jn1moCly3igoLPza+pED2V3N4yezvu+hfNXWMSfgf4XiKR9U+K8uWn0KTBFWByo5r62y3D8nVs+c7M7tsvZPwdoOrU+NQaB4ZhlCnDyrunjx3YtnivZo6S7KqsukQ6gOxMW0by8j6DpiWGiivUpMG4G0fjrkhvRja72nZ4lm9wk3dbAx+7Gsrt/9bzb6H4ZXolkEsOA2ZfNGWIT+wbOlKxOZr4ONj3vAHLQchQz755jJf+xLlNcU7IzB2VQJx140JgLB1JpctOsAnenGcxCYdnR8xPp7WfVH74D2W3T1ZUEB77PuSjCpCyJzqdFrxE3sfa/ETTZyF0P4bOKUplq/vAx5rvZEuLEAlDPHjq71oWvX+Yv1jpyihYcu8Gni1Xkiq8M3JWtRxHWb/2Qg+s2DMC/Gpplp0alO/aQxfhu8MoM+s5LmipTHn1z4Tr2Fj5JBlcDar7npD1p4JVxz53V4w+4cx3lUYKyLoKprBoPVEe8Kgu2+H7dfH9bHjxl4nXclNHsftnhkcibBNKkmIkUaf37H3fJz1RmQpNEN+gTnQs0yfz/sGj7N0kV5cF0HYyvCtLnhVRJVKnb7FDz3Gohesf4mSbN3cbwzg3KOzUAxt/cy22RdqwBRT3viu/lR6TkkH/TyGL3WKMAwzr4pafHJ52kvcvrzAC2i51xoD7LIP/WWkEQ95qiX7LF9g/RM4TsYNxBVxlsnFunerUP/vW/ibJITnbpmY+PsHjPbazhVuB4Brbe2nmcv7i3Mm1Xq4icmuQ/fwATY=
*/