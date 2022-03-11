//    boost asinh.hpp header file

//  (C) Copyright Eric Ford 2001 & Hubert Holin.
//  (C) Copyright John Maddock 2008.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ACOSH_HPP
#define BOOST_ACOSH_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>

// This is the inverse of the hyperbolic cosine function.

namespace boost
{
    namespace math
    {
       namespace detail
       {
        template<typename T, typename Policy>
        inline T    acosh_imp(const T x, const Policy& pol)
        {
            BOOST_MATH_STD_USING
            
            if((x < 1) || (boost::math::isnan)(x))
            {
               return policies::raise_domain_error<T>(
                  "boost::math::acosh<%1%>(%1%)",
                  "acosh requires x >= 1, but got x = %1%.", x, pol);
            }
            else if    ((x - 1) >= tools::root_epsilon<T>())
            {
                if    (x > 1 / tools::root_epsilon<T>())
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcCosh/06/01/06/01/0001/
                    // approximation by laurent series in 1/x at 0+ order from -1 to 0
                    return log(x) + constants::ln_two<T>();
                }
                else if(x < 1.5f)
                {
                   // This is just a rearrangement of the standard form below
                   // devised to minimise loss of precision when x ~ 1:
                   T y = x - 1;
                   return boost::math::log1p(y + sqrt(y * y + 2 * y), pol);
                }
                else
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcCosh/02/
                    return( log( x + sqrt(x * x - 1) ) );
                }
            }
            else
            {
                // see http://functions.wolfram.com/ElementaryFunctions/ArcCosh/06/01/04/01/0001/
                T y = x - 1;
                
                // approximation by taylor series in y at 0 up to order 2
                T result = sqrt(2 * y) * (1 - y /12 + 3 * y * y / 160);
                return result;
            }
        }
       }

        template<typename T, typename Policy>
        inline typename tools::promote_args<T>::type acosh(T x, const Policy&)
        {
            typedef typename tools::promote_args<T>::type result_type;
            typedef typename policies::evaluation<result_type, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
           return policies::checked_narrowing_cast<result_type, forwarding_policy>(
              detail::acosh_imp(static_cast<value_type>(x), forwarding_policy()),
              "boost::math::acosh<%1%>(%1%)");
        }
        template<typename T>
        inline typename tools::promote_args<T>::type acosh(T x)
        {
           return boost::math::acosh(x, policies::policy<>());
        }

    }
}

#endif /* BOOST_ACOSH_HPP */



/* acosh.hpp
2/EsJAEV+OdcjJyRkXijGECHDz0W/LsjXnbjKp9eKnK+LtjJcvSdzvREy36uaGdmyJ+a4GNsoU/VSTrOTh4NCBc6kYjICM79+u8j17pcoYhyOcZYN/Q+lXl13dPdJ2NF8ZJNYZr7V83oavGjKf1TY0x7+7wHMyc9L567V+vgLYDty9wiuIojNxb1cgr/iYVIzs7twCkuKH58PwJr2nOAFAZdEv4XJVyf5vrWwAVJSWjiZp8soVLjTVoSMMnekwHM1OfQH46OsBO3YcVhvevxdkTy3POPZon8zfjQtCG5KgHJye/7hyowEBmKqmMVHDY26xYfeG3OIRe9K8ynIViwkLYXV/ytlsL9JcgwehlwPkU64o/h5y1Cg9y7hFUzHm0/WRdA2wrNslgZkSszOXSU7kwrotB8JPm9vPYO0pqCv5hHxtBTG91+1o0+0SfhlmjaZgTtqO2uk2E3hJvHoClJmU30s3jYj/3+44Ru99kue9dRDIBSepObXHJV8eXF75EC0DTuwHLA1yMBMUPEILRGI2Yzk7AuEXE7Z9T7w1GGDZdwWg4KH/v43k8Dg0Vs3zlCeRn/UJdqDenD/Usqooi+tZ9VHNn6t77ZGeoiAJffGpTiDKEZkXrVbuZD8vNjll3+zL8FFsseCIikMD4wkPJo+2sjFT82ApA2H9XEeOY4QBvVsN8k9tmtfvc7ss1mde5vt7Z2gP8eUgi7dYjhtnr1TpWGtkb7pXKGXAmEt3U5NEJVsOTQCQ+JOQfmFjoq3QpHePpBYI+/2T2KM9x8ySWeJS4ffWurniShFfjc52+heEfKJVcmVfLfHvgQ+1jfCwItUxZ3uBK3Vz9Vf8QaqurxxHEC7GWI59iIfO7W5EDnmjUN81DIsHD4TWPlcmjI44NrBi0XPb/dRCGVv98q0spc94qprZCMhYx0LTzhQMlntDoOSCRT/3Id4Lj26Ni8Nvtz8wVCyOaZ7izv6cmP9uuw4s0OY9Nyk2VFzp0tjFDfs0X3IakpgJ7g04yrQx8BOVpEXHWBBLhgWP/ZPCH1bTqt4IxiQLrutm4IXuG2j+653NVCgmtdqeA1V0gf8jNFtVqOXJnGIRIc9LonoWEISMOZnqO5S4u5xW0by8hyifSvOd22jKY//i9UNXs/PIhtqTXx1/bqP/ewrgY+HVNcCRO0PIkxERTm4y4+EcW5H+y4pT/hmWpICXJr1CRC8drd9STdMOYV6Kis9Xw1Rnof8MW7RBzMFHgRYxeJ+/g2lO9CHcETPjKn4iBtn627Q19LY9yK4NnJUXCIDy7s10LllFGI5vUI6PaQb8dp6+LqLeTvn8UO+fPUXuxOAoL4/gl6D9NHHh+pbEwesreIPaUcNYlRAnWZeV5IKC18KlbV95ZlrfRTNXjJn5meVP5V4eF3k7+R84De6UP6QXYi2OYxDO0mUwBYcDFU1h9gvsLbEIvJELwLFufil0mPXPc93K2fMPfnPzzeaYEwQ4nA84ZGqU35lmaaHN0qHQ+7zblm+PSfEz0b7RJvJWvcInBu/TMc0qSCDsYbpmtx5wkU/zwGwC4OLFAO8YNIg2YdtXQZAeskjn8NLXvWsyn3twbBzWTbXWp6PaJ3Fo1q6j0mFlRXDZotGvcjYg+aLO/hwvBtn32nEfj7nzN7Jf2j/56Wzi1+boxxd2r7zJxvImr/jknqreoiBRZCqyNo6l7k/84Hw/LGWZ87++rEN4YIptTBRsqqcmvygzpdvUxEsmxAi/5w75IRRCXwclBfFW5ONnZu7Q8PQau2X8btAP5sbafRi+88359eviXTJk15lzhFMR8jljJY4GX6+P42PlEZcxND6zmWbZemI0pq+fGR0ym9bXO4QtmJB/PDcN7enKqD0DhsBIpbUclnO1pExMlBQcu5H9exiWxQN3qfOfnTJHWJIIB218an+xzl2DJd8bVSTN8P+rK7k+Xs3Ln8UgXW2k0bR9UmMekDl9At2MSXEx0H3+gTREZvYeU0u7+vechYFoJmmKPUNIhzy/x0fMPWFdeSBHICtgTXq/3X8oaKG7aNbRoOrWn47yJ8jBgYpEQiJZbJf0PxhLBvGdcmNQXPin7WURqLryIRyVuWvDzYCsxsY1FE0ASBUOkkLaj+4GaDkH0b5zEGcJY1uEqQXu/A2B82vSZkbJ/yEPLGpRypepUwCPtURNjBtuLaggKnjNuYTGvTSQVECv8JeQpmxqzY4yJLmgFw5hhnMXG/GAE7EqOfsWjba6R3HumoKu2irghxbSJlxFw/bCPKHhgN+Z5ZPzqakRRbPpWbYszTvWyFZ6UHiTEXj1u/KXIhzzNGKLaPVwkJfASLRsYo+c6oDtqcOJ7ZAtFrdfJcntP3ojZiXHtRKX1RWwJf83OSi3h05fRj8w11xF4fhqLIMoeGtpItX8D3cWm4K6xWzQNfWp2VEX/WzuJpfB4Xc5uxrZjnrV9DiKXOXi+/PpsAPhBMtcgpS9iQ56ZvxP3aFv1Cr/Q009XW6D8EBUuDv4Cqo1Vi4v5GCgoek0ZflQshIYa2ZhEKZl2i72HlufJhZxUOKrJepGbAqAiHKoiFPn5WUhBusxypuWlg6YOvKoR9VwTEAjfN1Q+xxfNiNgpdbHlCrmjhDzFJOd1+jMsFlCeCCneaI5MKwM1cZHEX1BLNeOZMje0oqBlGOROIPjQE5sU05DgUgmCfQuOjn3VItJ7fP5GE1TplAmlFkzi9MYJRFIqY1pLpvncMzRaxVZOBRVAHVBncZewj3eEPT7K1AUq5GsxGcDpL8VpE2wlpq4nfgU9Be6RDl6BkeShyhhU8IpVvcNIwfgOtJgfV2IhzGBhGkpbf9PCRHkBVNzyQd/7DDuKnfV2dhr+7GQ6eWmOAG8T/6YJLv+Bfyc8f/VENIISkXu6ZuUudOKorCIoYDF0gWG7ignrYvmjmR3FliWbBTG6fcQUmw3TYrbwYT34FUu5DbbZehnsOqbmio7zpFcwJRXXd9T6/bL+zuBtwOwMYYn41p5QD/VlPyMjmtGev77nnvEii9IQUR6wL9Bny+CehGOGRMnGqBLAN+vslMAjVTEf2xwf1YhARUZ2MOC1pC794u7Ubt1YMvRZ5RZxr9yWhiiVyAuMTmleS20wi1GY2kd3cmrRwcXKIvz21GxYgtAWyxSmzUlfT0RD3dmfGhgp7QVVIoZbn/38LIv3dNFOwbcr2ssVFoWTcYDSw2tCKwt0lk0V0+vs3Sw5/C2pf3mT/9mOvo+3q0ousGq0tRrsaIRVYEzMyK9b8bDBjxvGn3p0YxN1vWExnqWa3/qiPw7A2Np8N60wSL2WnP54sf/6IgssMkxZR6T+1kcoX4edlxpaaEUCB/8/+iD/2LU77xnjRq6Ku9z4i995NM0Q31Xfrn7ic4P9copnkI7ikB+5jscMQ8ErTHtRh09Qq5NtUPU4Fi3fVi7Sb6rpgWz2rIuQI0XK7qneSPr/H25vns2XH9r+8zW/kKlMRphFrdnvpGdtv/Qxq1xnO1t2d79FlX8RzJ8a46XlRe3aQP1jXUziqnCWiWUxbZKOGX/9l+3D+T/+do9EvyheC5UFNyzu+ilGyj8GTKfU0JOiZMAIlYe+jW3Tyy5AsGDJLpbdxA6uj6erXOho7sDseZAaQSvs4EKO7hTlbVOJFjxtZs0SUJ4EvNXWmIYJZqzn5pvtFrHZFTlZGavRYMOhLi/cPb1uzb7OymmgdiFbWN3s41tStZ8LIFN7CFSNYyaArcPJ1VvdwXpiBQuIoAu6xhV3cr449uPNL45jNfoFb5lBdIsltACcBXT/iBLtGsvx/GYAH9yJCMUoMTUr7WTANavD7L3zwECAjf/5+sCju36dRRaaDHx0iEbqkaZgnQiLfun/+8DInOateHOvrYt5eEavVVo1iHeZ04a67lCdRUNKPQ9/TPStuGfGRGYfHxHblFop78gSzZ6RLkbnc8nT5byEdWGnwrp30pmvGkUKCngwVF0hJD1e4uVOnqx1H4de6pu8kTuc5j7HM5bLVb5Lc8F2ldBTISdWkz9MUXLvzrXNhb0WsWADypjFX80UwU726mYJ2ZhXOowBhr7WG4iz3qyedz3k8Mdmit7OLlpkoehxOJc1845TwpMY7nx8N6PSzp8c0s7Tu1p0w0foUPL9NLDTM+A6Snn46RRLPiAI6jPNrQmXrnAUWAkIMIzmH6GrGg2h0yYRniF9bcTb3uryVI+2e5y7mOQjJBh+poeueGBtNVfW3VQ2zqb5ZjFN2asHsfXeNe9JF1FDKACsvCYKHeRp6SjAinHoR1L2vBeOZE64+0evAiLKCWLAhyMBjdIzjs83oINFcisyOsyU5p/PPZWATa3eyVuOff8G6LqHOqjxbQ7e1UrRx5YmrqY9Aw8WqcsMEK5mIyEgOhF77+HGWUnCVZy2Wi5VDlBi99GxwLJx0rslIkN3OHgTf0cUtQYp8dMxo7OHWt/d2/DKW6ML1BzqL3qraluEvXT/cvl/A7t6buc6HaLrPSBqUPuWn5aC7GXx3GEYxCh10btuT9IbbBRQuCm5L6p1a0Nud+q2Tu7H/bTydJO+YQ+Ls7XgfBXVkpRPItn0QwhTapj4iMO2BhSMx7TTVs1jF3mEU/WgMZFUX5hKvKFyrjGqUgYUAp/RoTtlDLcnBPCu881/cb4ZGFFXZOQIrd4G7MwqWsDVPzW/OTNkL6dSiJ2bkz+6yKYvFz1US4LcCByR5ktGgbHvNGlDJSFqloVs+jRQu1kczkkh08eLGJzEeqxDHEtkGTIm2BLs00+qXSpzmDYusXoKLh+7tywewBk+Yr0kxNEtembQLFCUmI+OHBh7kSzz4YIIAR7TafxU/4nUGTwQ3s7M978KH+EwrIvS5UXtJvjPGniwLrm7kkui3NLvkB0A8nLh4vX4WKPXR4ucpjqFf7drJRvyXE9z/vT6Zukmo2W8vggRz0pAopYnSQz4DLan3qJ7Mut4B8LgWKshps4rZKl88H+6lc9eqpn3md2M6sYff0S+yxBIRSBFDka7jJHJECBKhinU72rzKvSjbqEU5Odso6U9QrCIWmomac475R1XEhsTpAXVKehEcxtGceq85xz7Inrn1YPdeSh1d08tuid/vhemx4DrBeN/4uYGiRQ2i8HEax5V3wDcpdWsuIt+/+tA/RL9Fk+hV+gJ/L6Gf8Bx9eb/pP/vsUTv6lP1BPp8oPzpuizcoOOR1YqHWV9O2vUrj0gaffedf8evqY94Qkll6n91oRIfQsITNNDlcPly4f2kZAhpPKS8O8pcbO0P7B7Og4yhhCuOcjRGhDWf+6Adkk2IK8/0YczE962/FGztE9SXLbgyQQyem2PtP+nn/9wjv90Y/6BCYgvFMRMXOkZJe5VThDQQEO3Y5wYYbURWds8S6faUN327FP39TPjt0hzZ71R6dcMKV09sAaTGALTHsWIC2qG52k1Kc+cQUpEizl/4FxEgAnmRPOMt0rZOqh+y/h7s9UAFoA4oT9y/rG8y99NrsX2TKdE8BF3GZd1EslpcI2zbiu3PQ+Reh6qqI4geoHw3ySPvOBd0+qfsz3hcfzi8FD4Yb7uE5w5AuQdnEm9zF3I47EHRV/E+vO8WkLkb5hVpk8h6q7GkEsYDVDHl0wmtlu9C0x9hRbp68TNU5j+a+vT8/mzvO1LckCye0Z5w4sthO0Pt2tr8J6Qkbk71HLm45pBmNW87bgzSGq8Bldf366muFzG/3sRgE3BfTkt5NTP8K8sroK/mzl3MUvIbpkhxWspFFdVTGpro4J0LiMG/BfWkelxqHnhoGm/24VpYfK9jUirOWabL0GBVylOng9W6Pnts+YWtrFDrKlatpXgxTl/dmjNXjNFOcOo52Q5OnNeHH+NSXqPrrrDreLmxjOc5xeRdoQ/GpKcfCqIeSdBlHAAa2qofIOcB4RJ97DyZXuFnxyHZiu4yIXVNy85pZwgXEDEwPMEGEjp+CrcRZXrGV4TlRNz0gd88SxODWrArr5Ur2xtx136Hi/Vfow2GWcYkUu1RVIzqQA8J2N0whGLWEdEGyyK6zjGMLM2+IfJPUl8mgavWBudRuTSFT/O+5zoBHB8eh8YWJ0Ti6+b2IE/4zKlXSb7vUw5yC9C76gn5i/vBCT4kcXr1M4zq+FdNTYdhjb0K62TBBNYNtbYv5WqKAsEMor6atbQJvn7MhAizBbPcUzsfstM2BoKv6hgMIa1QmMlANcUfOy1YvxIYrT4l0jyFCKeaEof6M4t9QI/4/6VhNCqZTIwFn99Zh4BvAgTnt+kius2xYOFBwInCU1nAFGLkrsttqPtmLDiVh7+SOa1UCNI5EFbmTOlne1Yr16o7NBzOOyYC9XEbe/bBOAhob6KoRUwQw0xi3OvBQNrbFZUjMam8yeDxX0gK+fmDSoLhWCpGVkt2BOg5COrjvbSAR9TeRkQn9tV6YsGiKVfnIHcZ851eQTHWPvLLlxEz98r9VH9DX9Ldn95Y+pb/hC7zqgXXaz84S3cWkseaqqMvIomFQv+XoqgKX15QKkb3zESPKu0Tik8O3UKPxnetHR+a5HGca1+5rbob31KYadgh/vn0Wb8RHHLpz6J3JZvFsJTx0VmxNEG3Q6fPrryZN0d2+2/h9yBciDX2cDX6Yqve8y6iH2oG+nI8Ps2j1Nnw/m5P+Z+xjwz4+7OzDDP8P+/uwsw/77wD8jRLwd1SJPvd7l+fUxOPJ6CNC6Mpzw6GPDRaEBwUnXgPexhPD2UdI2AsMkgZdUsGHlcUHslODJRF6m7aEeloIBGoQmThSUb8hy3aDR6Pjb+Lj1t135q/OsaqieMnWrlbO+eX5fHy7i9WDqlzVevRPItMCk4xRKiAffxj9wW5ZBj27ZyvVs5PGWe+Lm/br+Cqg6IU691godjotex9sSg4bT/3DSVHibkenZ5JXluJH+M7y3+mS++lfb1t/VCFbyfxXRYOQRwNTtLIZaXjkPHzfRvhgCPvPW5ue3pszkT6zOgKhuYK1DV2B/4PX5mrwz9zoyjkceqx3vHl7wy4rFPBoi9JYJO31rhxrF/fKpR8zQPzcAz36G+R9HD8XUIPnp/bZwOnLlDv+EzmS6mk8osRWn/rzed489t76I7lNlsM/14O59/J2qNOL0lVzbV7r23KEvV1lkPryn9nzl9l8MnbP+KIORSr3DggM3ct6SuxoFGq+pOll9P8U2NBYsdc/VPQ1+q1/817yD++I5TnPj3qyk5nj0lKLbpzNK+KBrTom8x8hf4Jf9WcPSnyiPP5/WA7FEMsPiPnDTtiT9H0dF1N2/yEGdf8tkWtswEv3U79kwC2hyb7iooxI9pv9TvTOzTrwtTnP67jfHAA/PFBEQ20zgFFtFLx77xMExekfd76XODkbP93b85+7y6NhSHrQu4MAnjH6vvb4zjBQ8HLHiuj6TzMUroWlKmkeuzb1/843ASYk1V6aui+ZlfeVF68iCDjErIXYXN8Jklv+QMGfA+Tl+HyzgzxGPbDDcIy56PvhjbmnqSfG8cdBZHcCaoRUNmwIzDP4Xvdejj7bNhx932Phdy+9qYGNvUwvXGah9xR3YLLSe2Po4EXBhcsoCrz7Kry3Pn8/jgPMyehbyDTGCJQiC10jTkmHYu2P+/9v4GuwWPQK/9k3lsTQn0hh0s32o+Vz4O+Y1CtkZd9FpkT4enJygykTKAl22UEHgT7XPgSVypcW30VAfVSiKmEiqPjGiWqiwWlyKmTEKyDE0AVhn5GmcS8R2wTmmpdDi01AqWTaXOTbcKETnnjr9cQd603Ph5mnMkomar8t3us7T+5jXBovcv/2k/l86fAicId1wyVxdnKbPFwIUBVsESmiYkT0UzT67IR39Ovliv7TmEot4z3EauZckcrVqacoqu/v4QI3xDzqk7ifhSpI80rsjc57OmeQdIFE528mfNXbbvSOLJtIwSApkArmIuhCH5plUvE4sa0k5VBHGMPEZib4nf+pOKMBI0fbgdwesQEcqwjKbdTZK1VMPDRUoWpMhRqKOb89GKYgGq/nEICoX0tZ/VRctt/lvBjklMSu1RE/r+YqpNa/s//td/ax6Qn+4a/7nOcgEO8Lf2dxn9Bd9I796Ddnz/bv90JM/5ChtPsP2LcnFWPR3huXPs/Gv/BardX1Zn/NR/5IJ4wwatk6pdvz1AHCIFKGtHvVpQsHAgKRScH0BxEhlNGLtAsa4ggAF8VKmR4Cjp9ot7KluEe35tPgIX9pGOjR5tDygDkyTNrWiuBGJchvjiZ8bMbOYTu807noqdTzcIX3kJI901gp9wdDyId27VgiYmrS42+Lpl3kowa+h9w+urH7j6/ZDund8fXr8e3zRFL/+twYvNeJLHOGbc1orKPaiKzn0KzIz6tfyNx3gWhzJxiC90Vr6Q/+FGbT2zev+K+siENJHsfmGt0fCK98yK1ShH2ULOYdZGDLQMqIKZNio897EnRNBdbAK0LjN3SxeW7Sk30A2P5ncjNPiRwbru9wKUwSHbWcd/LQQM9mHN9kr9+6L/pDirf5/Bv5bqegp5PPBY7zHTOs96d8vn5nyeHulwBpl0fL89UzNrmxL82x4xF1L+rd/4H5cUcVvXVNdQB3oJ8ieXTBUHzZpn2b9Zsn/1tyOqQ2sTOY/bvhSEx1L8rO5rrsMr5lU7KlTcoLQuGDzxxSL/0A96emfdTgmxaHCWbox/7w9zJbgdTf2iu1oVLyb9Dgbcb5XHE8LZFW1HSzqLkQ4ZF4I5kP8e72yDSsxXgGB/+1dxuhdQ4LVt4Fe+zHP5h0JxwD4Uianvjh93IfquISZ1sxg86n+ZUDXH/7BfnToeG7JUylbFMHloYvSjJWvvOH+5pXK919muCf98V//GizhKxMciKS/LdZjmULnvmfP5ZPkoYGyQmeW9TTj4oOnaAcHSS7xHIS2MEzqolL4B9vVigwmyMGE/obd3UVIivng47YA/LomWgSQobImO6cTYqahnz0CT9jyvdOVw3VmIhDvMKO5ciwHxjqq9E/zEOvbpvch/yYBUnXNmPN8VmfR/UXBeOiQSej51Fzv99Vg7mQx0P7UVuAxMHhvXLPru/lJoq8q2BZUJdgkiyyIpFbv2XMHgRc9bpv3YDklSN7A5U2uQpSueWpk2Psxhmnzw9gleQnT0CiK+TXzg5YNPa/E6K/uf+Vv3nVCwApR+Kv5V/za8qUV89XdpVAipkbg+Y=
*/