    ///////////////////////////////////////////////////////////////////////////////
    /// \file lazy.hpp
    /// Contains definition of the lazy<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    
    
    
    
    
    template<typename Object >
    struct lazy<Object()>
      : transform<lazy<Object()> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                ()
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0>
    struct lazy<Object(A0)>
      : transform<lazy<Object(A0)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0>
    struct lazy<Object(A0...)>
      : transform<lazy<Object(A0...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A0
                  , detail::expand_pattern_rest_0<
                        Object
                        
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1>
    struct lazy<Object(A0 , A1)>
      : transform<lazy<Object(A0 , A1)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1>
    struct lazy<Object(A0 , A1...)>
      : transform<lazy<Object(A0 , A1...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A1
                  , detail::expand_pattern_rest_1<
                        Object
                        , A0
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2>
    struct lazy<Object(A0 , A1 , A2)>
      : transform<lazy<Object(A0 , A1 , A2)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2>
    struct lazy<Object(A0 , A1 , A2...)>
      : transform<lazy<Object(A0 , A1 , A2...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A2
                  , detail::expand_pattern_rest_2<
                        Object
                        , A0 , A1
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3>
    struct lazy<Object(A0 , A1 , A2 , A3)>
      : transform<lazy<Object(A0 , A1 , A2 , A3)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3>
    struct lazy<Object(A0 , A1 , A2 , A3...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A3
                  , detail::expand_pattern_rest_3<
                        Object
                        , A0 , A1 , A2
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3 , A4)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A4
                  , detail::expand_pattern_rest_4<
                        Object
                        , A0 , A1 , A2 , A3
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3 , A4 , A5)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A5
                  , detail::expand_pattern_rest_5<
                        Object
                        , A0 , A1 , A2 , A3 , A4
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3 , A4 , A5 , A6)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A6
                  , detail::expand_pattern_rest_6<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A7
                  , detail::expand_pattern_rest_7<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A8
                  , detail::expand_pattern_rest_8<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)
            >::template impl<Expr, State, Data>
        {};
    };
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)>
      : transform<lazy<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A9
                  , detail::expand_pattern_rest_9<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };

/* lazy.hpp
G6qjPDZURysbqmOUDdVKZUO1ymNDdazHhuo4ZUN1vMdu9QRlt3piFrvVZ3vsQ1d77EOfk8U+9KQs9qFpZVvbANu0cPQysMYsNp1NHpvOjMemc00Wm861WWw612Wx72pW9l0nZ7EhXh/Kcmd31IYtfjs02OKJ3Fk7MWeL57MPa5/CPqwj4N/aTeP5KcqGsHMKW8GuLLaC3XFbwX22SPtskfbZIv0P2yLNLNtna/r/bmv6PQtbI2LdkJaRrrFrA8b9+ZhbW5uitvqBhVnZT9gx34ab0m0Zo9CkZVUgoy/q+IcW1xi13Y/AL6y724BvaV/by3P67YpnZ2eTGGsHcX7scJmM8LKVBpu6D8DG7enK3Gzq1kQ2dVaXk66bbmmWpAyV2Oq3yvjfHLbFDA9NKAfDZF8nCr97qW9AjIAOn4r36iBn/0AEk+8bonxbfaW3fc2ahM0jwqIVRO09E7CO9o6jQtgswJpb0xFdErA1EtWEZyPcnWlpy4TrTMBkFRnFm0swdEobPw9w1uvyw3Q7G+393Hmos5lVKElje0usxRRQym7ttpak3Nt3fM/ypHzxOR+zk+xqlxHeqGq96aYm6ehdidWS7gykO6cqoDIGL/bN9djVYA0P7j2uzME+ydk9BlcO+Y2bvCqyd3wGtiUHIX27z61tLW0eZAcENk5GJudRenk52Fe6vSV1zpbc0/aioAr+nKqCPZT4HVC5vWieuB8cTrh7oAILrkhSHe0Y36bs1EyB3D3Qvh2jhC+VOh0LHh3avQL2TAupjCmThjjWiLxXueAU9kHGv5RyKMEgxC1G+YKzYGuGJXmYY+RpTrHkIamkadIw6lYw4XT8lD63RsYGojwwaCr/H5uHe7cNDPdvDiNSWGLZvTbVprPU2yWL0JblaEslBzj39MtBBeJWIq753ah8F1YLTu8X1yBeLeKhbwmdwe/sC+0XDa8k+WZbLPR5CbkXK1a10reid1rrdN/qE+vJgaHAENgFbT3afCTj/hbrq+i8wp2PqbNW2SNBvg+s4jK6t9l5D/ngKvLnlYjvLR4qOK7nhr3YOj0L6Rapc5XDBU72FBZv7UoETmfHkjf/Hfwjq5Bnd15v90mLqtw+6VFRG029H9vYbWubAdE7WccQv5XgZ+ClBD/WwWXP3sGPt3BXlydImOvyRAmjHQTnyrgLe/CrqR1WqbgnUdxVFLcSe7wNoN9cTDYSOEfgsMS14bMRPg7heqFjm4oa8o1QXeHO9YU+1iebEd4f+by8mPfyJZ6StRbQHx3lw5VZYLE8tCvZEzh8hSg7BMjeKUJv517YxdySSNh2Ef8ukAvMu/Yu/+DwwAT0JhueHB48OwjPRPjM4ZEXmrlyDfkg6NlDdwp5KT1JIeP3I+wNg147a4b77ICJteeweE5MBPkYn+zvF+tloWmjPGzcIw/Ej7Lhxwc6gqm3gjL/GZPAY2PgaUoWvwof7J2Qd477PIFxez8f48FSHrdA+wKB6XPWPoHx2e+kUVcFlgpp8Z/Pfvs5f/CJw3kaVWP6VtALHLaSOJP1lGdQ8T4j1Cc8Z4NDinYHh9mnDMkz048KPePvLo3jxwS/gv2x5DiXm/xOqPq3Z2cCm6xSb+cjLP0W/dnFOSPLm0svkjjs819od3N4joRdfbuzw5faPIGXevPoPMFpf0pbhE8xvZOVfFkyMUNgOHvH/GE/Oz8Vq7P3V0b1izNJJeevRtl3ufd58FaY9tOk4kouzodclFWR3RboDI3h+XrB8Zz2BsqPSUPn50LBo2zAu0/4xcp2kZs7BKdsYaqoHBhzuT1ercbZugR9njeg3iH0fh1van3G1M+7uH5Ips7E2M718x6h5bf0L1Fv669T4WM=
*/