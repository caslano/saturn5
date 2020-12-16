/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0>
        struct result<This(A0 const&)>
            : detail::expression::function_eval<F, A0>
        {};
        template <typename A0>
        typename detail::expression::function_eval<F, A0>::type const
        operator()(A0 const& a0) const
        {
            return detail::expression::function_eval<F, A0>::make(f, a0);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1>
        struct result<This(A0 const& , A1 const&)>
            : detail::expression::function_eval<F, A0 , A1>
        {};
        template <typename A0 , typename A1>
        typename detail::expression::function_eval<F, A0 , A1>::type const
        operator()(A0 const& a0 , A1 const& a1) const
        {
            return detail::expression::function_eval<F, A0 , A1>::make(f, a0 , a1);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2>
        struct result<This(A0 const& , A1 const& , A2 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2>
        {};
        template <typename A0 , typename A1 , typename A2>
        typename detail::expression::function_eval<F, A0 , A1 , A2>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2>::make(f, a0 , a1 , a2);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3>::make(f, a0 , a1 , a2 , a3);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4>::make(f, a0 , a1 , a2 , a3 , a4);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5>::make(f, a0 , a1 , a2 , a3 , a4 , a5);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6>::make(f, a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::make(f, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::make(f, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&)>
            : detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type const
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
        {
            return detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::make(f, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
        }

/* function_operator_10.hpp
1Q85gNXgBb9efdCzfol3Z94innNf2ux3bYk9fdqVX9FnnkUXln5LbNjmxExfwJrf2cSTlYKbiAHjvYo/bKDdv+M9mDGswGNn9tig74nM+oX3fR68Bt4BH/q8HwMIdgbtgF+urfonytaeYyfQEXQDXUBPoMsrvJ/wlwOJWWzPuT6OHHYeckDna+hvJxd6MqE78WFdiTXb09uoHAaQ92QwFRRa93Ef5T0NYnB7nrDxfPR1s5/zZNnDyA6dJ62+1qRNpDtoM1dGY4f0+UJTlpL+0feZbJVxsx08WbNcUu6zt5/OXDOjv7onseRdP9i0+oy+hPHjIGm2LovSie97L7W+5dx7HtBpL/wJHe7oNZvfSOIua3cgzpK4uykXCDGyzevR+k/paze5KfU6s3/LdNDXv/PABUDr4CURenihnyfHyzhe3T+U09pM4tiJc17O2Fv1RPP3/OI27Mgxjdv+ZNPmfl1PbWG5z7D6zzkczwcrgV/Oy/3ygd+B90DXHbkO9AXFQNe1hH/vD/z6VnDcG8Al6z5rx0T9Szn6dd6Po1/vuxgX3KnEwP6+cX1O2/GX2QC7Dc4kn0uS/VS1h+qzK/yyqrZ4lvcuXrye2NojGY+xaz9dg1/Sl3GG9vkQm51+C3l8jT9xL/Gf2O592zAOnoHdG4svRXz+V4yX1+6Pr/UjY+BqV/66jJhv4mcPuRN/jtjhOPHfn59PTHCtKzkEUb0+mndE7tf63PK6U+/oOjdjA4v9mPw3f9n9Qlm3TN8b7nnPffzdkTj0HcP7rtoxbOtLTHtfxvGaHVtWlubq/hzHF4Df7q9wNG3PO1bkCQa0QA9u/Jk49tOwIZfwTh+x1ztn4N9cgE1jfP/qXPraMTwTKyDWeCQyxW5P+ob47Hnocja+Hrb1OuKbfyCuvA3x2hcxnr+VTZzvd5TtW9Lx/tbI+xgnM3gnKJN4YvyMx97Ftp2E3z4Cfwyfehk6MWO916wcXq3GNyU/uy1fpy5rwBvg/R3/OXJ9V8kWudKWSrZGniWWTD/023tr8tk6lOu2XTx56Gf8lgnYCcaHhueQW24nQVCXH5+56zjsXEdixg4gj06J55Bv+c8faYs525PuYWxHF+77jrT+Wn//c7/ZkohVXQK6fc+cnLl6zheJcwtB3gzmA7+lD/I+G1M5KQZ7DGWOdx0nme++MJButUXC1pZM5iTzxhGD8PnWYwdGc90k/r2GGPx0+j/pnmvP3/5z+UWkmcZ1Pehzt/Ju2nbMz9vwzL+Ye1xIzE+930fJjvTFFcz7d2HeyTzklP2Yg9Ffl9KnD8vCtnD+vM7YyH7cD/vYjf7/eBnvFg7GZpBF/ZPMaTbjvuBzh/w5Pu1hX5h2X+FRPpe8wCT25fmYc7idFCzBD/U4xzXVPjanfL482lDezok4/nc4P4L61rehDNtQBiHNlvwt5Me5h4W/t0gczyIPxCgn+CbFHI+iDiLcc1zivQoulSdJ9wS4DFwOrgBMl4I9c652qCO4FlwHrne4H7gR3ARuBrcAxCm3gdvBHeBOcBe42y+DHzML7jXxufeDB8CD4CHwMCgB+4H9QSk4AJSB2aAcVIBKMAfMBfNAFTgQzHcS8loAakAtWAgOAotAHagHi8EScLCTkPEycAg4FBwGWPII9us5EhwFjgZrwFPgafAMWA2eBc8BpijBPjHPgxfAi+Al8DJ4BXQFvv7uALqDHqAn6AUGgj6gL+gH+oMdwU5gZ8D0KnjnYVfwK9Ab7AYGgcFgCNgdpIF0kAEywVAwDGSB4WAEGAlGgdFgDzAGjAV7gnEgG4wHMZAD4mACmAgmgVywF/C7Wh6YAvLBVFAA9gaFoMhJ9NVpYDqYAWaCWWA=
*/