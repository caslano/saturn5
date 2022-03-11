/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PREV_IMPL_13122005_2110)
#define FUSION_PREV_IMPL_13122005_2110

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion 
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template<typename Tag>
        struct prior_impl;

        // Unary Version
        template<>
        struct prior_impl<transform_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::prior<first_type>::type prior_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<prior_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct prior_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::prior<first1_type>::type prior1_type;
                typedef typename result_of::prior<first2_type>::type prior2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<prior1_type, prior2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first1), fusion::prior(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
wkihGIyd4LS2d0o1cYPNxUm2kPkGZfDalx9aDDeo/rYpc+l5viIAS9vaKo6DpI9djgr4idqXdP88/ofy8ruWGpiZ9nOEcWljZiZIa/91nxvwrtZXDPuyTTu2Rp98/MIQlgfir1d/OWEhd51j/cSuR0lHtlsuCProFjPYnCQ98Cqtx+LS2a6U4OR+AX5bbH3thK9fd/650qPS9cld3+XttLi18rxy9qBG0K1Zmrw2Q78Pto0uW2hqM48oju+0DedXnhqh++UNiRb2CTLY/XK3+HP1wwZXgBnbsOR7/d1aNSExtWHv626r0yT2GRJWfOJOCbiKho9V4lq319KI+w4jWkbhSTgt4GHBQ6Nm2Hs8M2lyIuDcEDKI2+pd/X3At7510vJVz9SlkteJiuId9DPzy4fChZpDZ10eB2IPHio26NB9k/Orejgfl+IIh4/X8wBhGis7mleqjMZPjXkHXUPKpxHYlGX0CDSr0r6uemxpBm3iQbH2ejTCoWii+qzEIjYYoBv43Oh+kRK9dqNb9LSR1AALHhjDHM5GXiBtFyIbQ80bbS9uXHTz0L93NeutvbTy0NxScQW6P0ZDVXfkjaGxm7xJk/cncXe5XRjBMcRvucNWtWuCHmP4BIQqCbZ1doy6Vm0CX66qaA3yLu1YvQQU4h02nEDVdeNW2PNdfpGGjldupyf0169w3jEtY4E8KVA1ZiChbnHmQYkUec1lkpx0u86aswZd+je3qd+zvehNnbok5dWIR9xguFlFkFjKcHHYzBfANFscY0d5+3cJB+3G7nk6O4ph3qI69aN8+TzLCv9tO7kuQF3mmSjYecHxPWZep9KBZsvbEl7xLBtP0GxcKq82DmQrip6rAHkDUw8xGzeZ9DanWqiZsTYwrHpiqNls15n3fnP/UzA3js+xf95DltAT7TJ2jnHdWzESTd2G+W+uopOdNfO3qATC9Xscxb4ylnZeUs3r7reW342MZr1W7apt9+L+l68alc5pef6KbG/fhuRxsBkcwsZ3OOSDs/lhqB+bYdeWUxitUsi9yACEX+sEsr8Kl0OlnrtAG/frx7v3BsRvrXMf1p7iWaG1xii8ZCeMpW6qO8hy07dfT3J3Siu9Q1ZMoigUNx5ogl66GmY1fFHKxpcK1SrAVkHPJDdfdLPJ0Aks2FtAFj1klAH4cQNQWW+qEwU/acABRnRaDiUvSnPdjTFb5YtOtTOYshEOWAESyaj5dCSvD1IE4mwgKKXGyQ7HKFItFgfCT64X76vAxsiDG+WBcO/IXCesInow7dtpAjY3tOukxAjWPIj8lJ0n1TNPGFWJkK+P7gGuMdfUxJYdCqLPlgWNVbQEKy1qLywQoTDc/OFiZU+gmU2Cn2zLx6EzbpI4ctbbahKGJgjTNE16ie8zHXrqIUiStqwh/Dg5JMShMDihcoTK+svIsRa04QwyrHOQUXZjPtKd4PCg0jEedKPQ2FjKf/os62yEte++SYDHtcuTguPpAaPXkqXmmQ/X1rs80Xo9KRN+TqqloqTcIX5Z7GAYRHgG+VvK7ffTO8Fy3ipovo5DAMQTuikZFFTCRQVbjqpNVv5KD3GlMaAWt5GbWh3poIfCStrxpQaLLMQrqj6JO5mCqOg0ki0lGk/3nDgZUK6XlOsgqZn/t9QPMgOd/makm9opNfA3MWs685U/hdY+sjDb8hWbqCu77PQkLs7jv/OBCbF5+2Ip4W0+TxJ8c2IwLgp8XJrbKC2zqIdRue8DvXlfFdg/bMYeyyL+TIbIBji6E1XzAzdZlA6erqTQRdga23cN1l2RwZD/cv3y2bBnfQzqZVrr5G/hBC1OjsQhtiVKNQXwqUlE+6wAZdL8ABbk2KgEBN1/aSA4o8bg0mfxVNBnsDXB1Ui/jbf09kRK3n0ic1cwqLpLNu4UWfqiBCyliAIIk/sHuMlpVTJBfhxToSmmnlBdcoh5jYmn40joWhYXPqxvgcfxnKFWo9HtLMHy9KJ/ISt+4uhSpAe8U/kl87vyH3aixqHMlZfTSwnJ2xOhzxd55m3tvSo0WAnL780V/SlF4HboD4eUICZq2JYiMwykf6TQ05CTjWj70K8gt2iEwHoRTjNGRz+VFYpM7B7bHzAk4kOTYncKBzOrinb8Scs4LuyOMP+eSSwrYc/XTqghgzCca6Hg4+tCU92trYFcix7DZky9Ag/8LBSXjmcPys1o5E/MkIs6BZ0MgvXf6kBwtUTFABGKTDSptAqZOt5kYRKcMQcY8jmIo47q72+it9P2twhrc1MsbnaPz1+ms5ANwxcK5mElizJCDPAp69PTI9njifmJPcFdXBkBaLBhnQLLRPw8WMP8MUkQhZMuEQz6DREPBd0T2ZObJ3k3CeZVEzkJYV0GneZ5f6ZypJ3VEsSB994qD8Fewl/JljgITmr6VakrhWIBpJbVYWt/HRKGNP9OTkfCXEFPGG1o8DjezTAK4G00O8oeO/tIZGvy6LnY1HkEFKRzyXpVd3NoFI0EyQXLicQ141OgkBOGUUjB5rSwMUGpqkVT0qApaoxMoeLQeEXfwnoZXptYOCmgyeeznVpM+uXdTY+gR49ebFvqujo0sHk6LyQU0ZgIhjXQOS7ikmk61UwEK9OMaVRFpFkNN8tNeZBpmJJSDhMnF1+r8r/CZLGJNItrbMtUapESRT7Qd38/xXZZeu249Y9ffFtJaKZFpDzAHfiYxABzGfW+8/2VJ9VThHnziFMINR1Rg86phS7qgucYwChjuyXKjGEnBw4y/P4J/mWmHiDcyMkfu5k+sOXv4bG6vi6Mpw6gKc3KpjGvK7Sn/Rd31MhLUCN5/nNJm9M840IuGU167Ons3ymurU9+l1E4/yw02HyB6iIet3uYVH4g8dlS0NS98EKb52vefUmG/yoWsXOpokU3wfuZ8JSkaDSqOvqJbFdG/lsGzkqKUsOtV6XZyDlw9xZP9UPTTHTp+tF/TVkaKZSwD+J0i7tvMo3oJLqCKDFQ/M3ty9Zi7EeH0MwcAJD67v+u04GzS/0pyyf5k9uZmNjTk1WXUleSVUcQFJqIHJQXUhfVmcYM2G9LqrOsLvUMn31sfqSmxjjJIDerCYSULiTGPo/AVZQQhw6jxpHI7I9/qSCSFgNH96FjhCen/MsIe42EYAv+hDtCYiQsZ2ikNTIy1mdRdCyzNnX/5PFIeyu9Iup+RCdGRG4bzbVEhCm47izMV9o7sFCUBBTl8Q+wROUFkJqWoBQdYTEj769E5ORkVyIVQwH+tUGDwZylTFyZDMAAhbmw5NZAH+BAL1yiLTKCn0Qh7nxGoNMBb+JBX81L4+ggXoWAXmnRELBAPnqhhO1XT5T9DGD2DQz4vBypGNhkDBRyIXYEDNh0B0C9hRaFFMAOCaiOWkaGMozDHCAusiZFrLSBeJohHmIDEBuBwAcMBdOAFOYDepmNjTmFlHgA6k/6aZ/xXZD3oRdEZYt4HVvSXGJf7CRW1yRq6ud31ObkTJXKv5+DnlnfziG3lwKALxYS6z6ZoICHw4Vvo8+7Yw4wA1bWYdwl0AZZn124b1FTQ8c7PzYdqzEkwBXv+3TA0jyn8btT0OfvAKxE/ZDs84F/3P1i2WzEd5xgD7McakRX36J4SV8dL8/PJcPD7BMkwvJAGPVbhyWQHYEVxhpOopu5jIre/H7y7/5W4KiQwStkOWFZjJM5WmEwfFu8yaiAjpG/gBNWVDg5/OZKpRLSN/HWGLSFGP8XAyUsllwhPqXeG/NHt+wjyFD3FGhlyz7EQ2wF/RIHuFc6qaSay8XnJyhg22PzhVFZKPgtC+Jmrut7+84v6jgJ9EuOHPUKBEBghMpTFiXRpywFEOKaK6hWAHw2EaWUI+FXENnWEJ2oJrBLJZpaCiErI2+OI40JJzTTCiWSmnYhZsgk+EcRZXTeJvyWKibg2wl0xuNLIBjqFjBVEBTPEESvHMAmjxY4kMBOFA7FdYInl/C++2XUz0XtTA4z6Il9QURa5YnpJBEGTQFq5rTtQwhlGK9EvxDvWc88cBs4l8jA/Jf8J1yQT7ZxRuTazFZLuBiCyUVCIRan6cwrywVRXotPufadyiXNHBqvqUekBN6vIhNZTlQD3pUsJPj5ik0pKjzlWUy9MY1My41WnTjvQDG85bm+cPyb1E+ptrA+GPzDE/TQetG62ebQDJyLfFoKT8lWiVg4AHI8CnWqNHucJ3E3nAnBnzW8OmoJuYF4rHiezDscBqEpiTgCDkjpkACWXsmooi2kj6zXqEwsUEIzZ4o5RqqAv8fUbBu4L1VMUkgIJzAtgM9nyjMiQN6zFjrLsd/O6K3+JVvEZETyfgl9H/kOvc113R7obBQ+5P67DxVVtjbc0M0/RuS6YJ4F3fwUPv5cyBWm6vAi+J84HSt8C9bjpmoFYum1Kd/GMvdK2ARr09KyaqKkplYH8p+BBSbVaIOsTOTM8n5dZpulUll/eolvXHVjQ5MeKV5pSal2dY0S66IHkZiCQIV0OUrZv+XFmrQN1FXrVYHK/kr5atH0a8pP9Sjq5ip81BHaMlVq9ePp/UojGmz0p7RwdUz0LeqHvx6Uf2ChNIlSCVPRaD9SNBt85tlFACZvNQtx4fOo9SwjGwVmkbX+3jtTYdWs13DtrMkVxXwFopHSydKtygckE6FIh8Qz3+xT0pgXocVsz4NUxlDP4Q+MFO4wLa68JU3pZuIy1tHaZZ7HBTJNMfar2TWLV8n2SQrPSAGeQcrSzvTOzEvrOI1XaKNuo9cqZyquOISzFbhdsFPGV18KRmv6OYuXf3IJCfrxrbYWCV5vUjzwHT4YyxgvXxepmLXY7yS0UO/k13HkbowwfXTsdT8WZroFRTZDvkRGPyY+qj6F768ft8OmiheKoZVPyLShyKFWyVbJwkz3TUNNVVhOWdZwYFmuKVIpdBd1F0uWVJcgln6d02Xxxdb0K7Iosmiyeug8s22zWWpPam/GUuAissssN+h02Qazcy3HrKSy/8ETr2mpkdbkqeGVTZLZMkMz++WiIQd1eaP9V2dSJ2CFoC7IYfWPVrvnZQ6uYWYb4hq8PpU7lbeHp2TAvdBAWP2w5qH1/gcXB3ehc7Xjjem0qd6jF5Jgee5CTvUM6Ww9M8GfQjkVxCyLX+YM0VnGmW28kAKh4uGyEHKLZQ+LZsYJtgluRDI8/Bs2tz50fGYWHOaIuml2q/ot+jkGEfbHCsynKieVrNyzCPEw10Du7NOQCXnzxu26hyS05EdOOwGScs7SBM06/Tobevc6z4X+wX2/E7dx/n3+ffOt996Set7R1TWeVR4aTsucEryeX/9kv0yeju5ZkaifySBYIGBese7WwL89n+9Ir+IOjrbZ/O21+lEjJ22whNAiESoRuS4aKNnwumNrKH25pXOiCpgjkNJfufWyQuYFVxPwn4IokBARNBAOYprgVIezLeTMnPL2UJ23MfyxFFB2J9jMUo8qy9JMiw7rClv2dw0vDW/28YpYlQu0NaY0UhqThw4KS6qNWpsuNoA93tDAHCDWyQAaWZy/3NYsf4D5PnMHem8uYlY4a5gBj1w6/7kGIKkanj/6iXA0jQ1y0w/gMZAa6Z/vJmArLxUDq/iinyvzl+yApS9mNM80syrzpJI/soevXhZXwZs3hRWKfzhs4IMTyYLTxFDEN7fXEKJIzjjmvPO8KWrKNM3Jcfi1Ud70F78+y0iHmYkuRiYPvWuM4URVMuQoLYZYSFVTtfSt6xu4pIwZ4vPTitrRiDm+zqr8zRzGA+DBX0TWKTKVlr5+08kjDUISrL33k/IJBBfbLRLWE8NDRwwu7blZ9zjN2jpOkTMrIrasX+FHTCiANfEYIpblSbnxdXT1Iq0tF7f3w77l20eKg4NR21MM4YJSgjb7Fnc0fQvFvfJazOFDQ0XV61ipe6F2Inhi4x7RLp7SV0b8wom2B2H7QwJtu15maWWpZZzS74Jt1NzCMEbJx4jRQyfD6fxtmg2rQCVpsWSxG/Xyeci95fuiZuaLvc1ijfXx+KHcfG0K69ZzrpwlsXm6eaL5PmJE8gjOQN5zdMNmMqLVvbW2FbhCPQ46jgXO7Dtl/bnIcgOakCxyBfschv1F7T/n8RL3ix7/V66z6+q4gTGv0etwC1blDhYf1yxCBvVctV+kuC+WrqquN9xg7Cf8gtxoLJI82AxiJ83ue9ojQYJik7xvKJ25vZvHBFSZ02NcS+Co2NLnRuXVP1sHoq52+t6ZYMw5tOEsPTjwrRxEsQogRFLBOFo9Qz1O3SdHxWf4DBn6CsdKrLaC3qVLhcvN7Yh458Js7Wxstjv91ItNwo25YkoG6xV+W9b1mP0r71NB2jE+Yv71DRTSVsZBRoXekx0R1END1sSsm+bD5QVDJ8OO5PevILei63kzgZnbutYceoMYgbWeiHf6Jqy7/YGN27cKLXCSxvWn9QnkjsQYfHd9xPh+X0QDi4IykRaJFlNu7D2IvRR27LMngYYprBrWR6vH96rXqqjeVf1Rg1M/rH5rTklIiTvvvzuZ2G6E6gL1H3rtuk4OsB4o/xB7oX1p/Kd3LwrQT2UEUQMoKL8Dg0v5fXFZFr6pDmMHlHSFIQF3xBCAL1CQwPaCgH4LQCArGMCxHgrgWA4CwG6D6RouBgBgr35Cf+tZz2kkx/MEvOb6rN/IVRWhdxS5z0iTRiOF/nabmQiWBfyGAgZCN6IaBcvoUjZYNkbAIYsJV1X4gUIIyZxV3V5D5BCHiSclPYfAor8JFyH//o536nf6Tch4dpWoqu7mf94XZaSRz1Lusg3Mdri+z/XKcUpT1xAHufLcdW0BcQMBk2pMuqJ5mS8pID7z0f9p65t13HHNkuwkqss50bZQBkvQJ7RACD/8zHXvvbt2232yffj2FRDr3/9tk4wC2NR1wO8lPB01JyVuwV+r16Xeje8WHf4IBDJ9EaFnwhzaCaiHvjaLVq21oc3TN/+ShLDgY6S/OBr6yI7L+nNx8oL/DfRoyn8tmY9C8mS+LB+Lhosv5j2X6HXC9qIvkAsX5EenlHFju5lW6XYm7rp2kuEO5DO7PMbmf3/vsExEHjeEBzHXbbYhJ/fFYzodogsybBv/gSv1PWw8gjmHQoDzPvI7HNhL9z5SQm1OR0Rms/erUB6iLKQkBbAh3xegUuOhVGeicDgOUYeIcLRbgJwXcE5OMdEeqNIS8CaeSeOVaMbiu/WaQkkKJWIjynIAKijNK+fookRaxKhprXGxCxbyMot9qK/vsTHUFcNF8GInvk67p8tx4rtJ0W/9LEXovqz6bfzqq9tA2gAA0P8C+y/w/4L4L8j/gvov6P+C+S/Y/4L7L/j/QvgvxP9C+i/k/0L5L9T/Qvsv9P/C+C/M/8L6L+z/wkHfFnUlhoWHmN/8/7jGr+phvfW/PnpltFd4+U3ukGKg1d8YcPA1BAx7hfvBGmQcMhDrjwxI+iIFir/EfGGNMk4aqPVXBix8FQPFX2O+sYYZ/xrI9WcGNH0ZA0dfYoBYY4yzBrr9HQH3X4fA0deYn4wBxkEDkf7QgKgvVCDFi+xXxgjjhIFKf2nAxFcykOJV9jtjiHHUQKY/NaDqSwVY9iILzPjLOGOg3f8n4PxrEVj2KvuTMcg4bCDRHxuQ9cUCNHuZ+soYZZwy0OivDdj4agaavU59Zwwzjhko9OcGdH45A49fpoAZY4xzBvr9PQHvXw/A49epH819xuJXR9LErEQizBjzMDJOyGcayv3877vwNSzmDcJgfdKryROFtVglFAIJjjhXrIFCAo6AI+ZFzokrsW7xo+UPYliEUrpeDvyVp+Jh6tE2qgTmB9suigiB8MM8NFewpaTSQvw086d5fUoPV8PTOd0xqZESHhdM48vHcw0dJV0TCbdt+ALFW9bMbzhGLhuvKHjWS9B59HZHxYb0lISG7wyH/rcrGkh3c9PiqhDjfqkuaPyiZiyHhTBzA0lJMd/p7ZAGiSyKCjjO0CozY+IIpKEUpJmgmR7gQobuK4Xidl8KXX83w09jBeMc6xhHRDmVDMfZDcUaw+xGRVusKM2sTHNO91Z/mkxrOVKP363zmtwag61Xw7DFcdAI+8grGtQlx/Qi77BnkGFOhySzjAU0MmU+ck49M7Hm6vDsTAJvX/BCO+y1vEH9ws7IKMMQ5EXb/Jhr6iXc+x+x9vHVNmmcwzsA5f5ZpF9vQMeCXqeLejhKav09sU9sVCS926uB327zMCifa9e5AWqSbmRagXGeBCBoLsh9GDvbViucFFbDonxzVtReAKx6uYQEXfJ6PI7wY0JV6HEei8oco0VR8nQVj4UTis6Xb5jyDuk1Ub+58wLtwBEM01ONOp/O3gpLNNp9S0GVgYVuFY+9zwnpJ132ptn4yuTvLJ49qg1JUB5yJYH1iaOdTViVKqbJ6FzGb4LEi2nopmENFcqfCaTqG/Wqsu95eSL1E9vJJCTlC5eJSUfgFCoRhAW3NfHgVmkSPuwYSaVvMcyOLX+FO3gOJn5HBnhO0wAn5bfJpDk/6HMg6qGFusKNcGmHJmV5EHbwaxZXMjnOvjuGQ0NoV8M4u4yl1WoFRTlNu3/iooWkLDFENHe1Uwe2GONgpZ4GWq9YUWCB7WVoD0KykS55a9WRBUZEpVY2Z26xQQjWHYfM3CD4ak0ozKpqk5psq+fxkeOxB9n8WTurS60h/s7TNgIgag/Jl/0571wQfXi3Q57t6uvEguuyFsGX4vMcjJPh/DGI/uGUIKxWFN0pBvcs628X2SlRz4JO+5/a2tpjTihubBvhuROzJp3Pl0sKJSh7lUlmSATVGKqEYqvioT8zI2/rWTx91x8tBZYDOUbDOg7HD17wOe7PnaZQvtnreN3cD3z/AQAs/9NAfaMnWAa92lU1W3ZY7v2UoemRydBrBe4UG/Zq/1W+6pfObhU7dCW5oGRAWiACaXolcRM7rBatYa/EuZoR20UfBheormscoraelVkM22yNVaNBwCeOroBiBQqtwYEjQVXcn/IydNC0P/R8jH/MONLLy1ZAZNMRALVkb4uWglnvP4kt3xlGh99orYWxMwma/hpP3S7RD+BqRU66cUnVTt2yejHgkOczCPgWt+nPki/lwQ/TRjMzs9YOO1V1aXUlzx9lAYzpNcqKEOZ/3YHkOskIcvS8pDq1enM13Rd5C61ekYZefXY2PMisNfiYxtbFGuor6TprYYnpPGFAyX9xVcph2i3tcHI=
*/