/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_algebra.hpp

 [begin_description]
 An algebra for thrusts device_vectors.
 [end_description]

 Copyright 2010-2013 Mario Mulansky
 Copyright 2010-2011 Karsten Ahnert
 Copyright 2013 Kyle Lutz

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED


#include <thrust/device_vector.h>
#include <thrust/for_each.h>
#include <thrust/iterator/zip_iterator.h>

#include <boost/range.hpp>

namespace boost {
namespace numeric {
namespace odeint {

namespace detail {

    // to use in thrust::reduce
    template< class Value >
    struct maximum
    {
        template< class Fac1 , class Fac2 >
        __host__ __device__
        Value operator()( const Fac1 t1 , const Fac2 t2 ) const
        {
            return ( abs( t1 ) < abs( t2 ) ) ? t2 : t1 ;
        }

        typedef Value result_type;
    };

}




/** ToDO extend until for_each14 for rk78 */

/*
 * The const versions are needed for boost.range to work, i.e.
 * it allows you to do
 * for_each1( make_pair( vec1.begin() , vec1.begin() + 10 ) , op );
 */

struct thrust_algebra
{
    template< class StateType , class Operation >
    static void for_each1( StateType &s , Operation op )
    {
        thrust::for_each( boost::begin(s) , boost::end(s) , op );
    }

    template< class StateType1 , class StateType2 , class Operation >
    static void for_each2( StateType1 &s1 , StateType2 &s2 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class Operation >
    static void for_each3( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class Operation >
    static void for_each4( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 ,
    class StateType4 , class StateType5 ,class Operation >
    static void for_each5( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 ,
    class StateType4 , class StateType5 , class StateType6 , class Operation >
    static void for_each6( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ,
                                boost::end(s6) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class StateType5 , class StateType6 , class StateType7 , class Operation >
    static void for_each7( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , StateType7 &s7 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ,
                        boost::begin(s7) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ,
                                boost::end(s6) ,
                                boost::end(s7) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class StateType5 , class StateType6 , class StateType7 , class StateType8 , class Operation >
    static void for_each8( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , StateType7 &s7 , StateType8 &s8 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ,
                        boost::begin(s7) ,
                        boost::begin(s8) ) ) ,
                thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                        boost::end(s2) ,
                        boost::end(s3) ,
                        boost::end(s4) ,
                        boost::end(s5) ,
                        boost::end(s6) ,
                        boost::end(s7) ,
                        boost::end(s8) ) ) ,
                op);
    }

    template< class S >
    static typename S::value_type norm_inf( const S &s )
    {
        typedef typename S::value_type value_type;
        return thrust::reduce( boost::begin( s ) , boost::end( s ) ,
                               static_cast<value_type>(0) ,
                               detail::maximum<value_type>() );
    }

};


} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED

/* thrust_algebra.hpp
uHYZw8+gfvgMj6MpYgTTbxxmiC+WpqVPPkJt9rYWkcQyRuWbInBUu98qArp2v00E+rX77YALaRUWsQGDUwj+Ih4aX6LYO5oZddHTGcPZ6tvb69P1f7c0D/MXZTLqf7AjknNYa0R8WS6niDgqD3POPNx1zgOOyksh0pIAkZhAAh1Q2xDpubfZHdUgqZH6QEE6KCl/jqyUG22OMDPoFVrFtAdJdNwl1tpk4kLSoKiS6ZYt2Zy0rjVmkoQML7XR3B7wkDjxDuizT+HMHPWJ+C8WSzJFUZaYP1Msj6HnO9kUrEiRtabdXbgHyTQecs6zOzb/GAmah3NLj8v0OVpVV56Ibvn6wY0Z1EzGxPy6mFxUJDoKRIs5JyUBpx0IqtBtv4QdDetZP5jtMFAx9t2TaOA5y8x1ZYAvZrRJrRbt0Rqz8P/SIZZs91EVKhL5UHK1xq8WtUw1e9hReQC6wl1ZFvGATVwQdh+H7jP7i1j7LxElmYhdyZ8p1s/SvOzWdetODiipGCO8QxoHBkZcQ6HD/pfpRfM/j7ZVNRMMzluGlGCW7wdXXK0H3mR+DQ0AByz409ECWQGpnT170lwBkqQlWWIhVyA6AEYF3ENadXwF9n12Fv2KNCqab++WhAX3489+mGgJvsLumJYgFxEByuYzmDjCzjTFEmS+LwXzyz0oEnIiGoDYBnPX2tfdKealhyLlP3aW2wKrgVcz52Uy3BYwXp6Nndy3naFWvCJbkS2KM8WCLHHrTLFmFrYTV7/mHnD+hlsxnrpR3Ag0Ba4HtWmhc629opYRxqrEAf3j41GSRZtFF+szgJorvS4HlNflgP4zC1MEB2fLgMcgUwWXW41TmYjvVnEfCB8/992g3LLw9+45HavkJWJBprg1SxRzJZmxh5aDquQYmuWyfujqiP958HGZ6zVCf2BnsIxTuzW4LtPiW2R42xC8UlLE7rad+SpC4jIp3i9SyCuig5oF3JexGzIsfACIQDf9syP0xuWj47Hz+3CXxbEZ8SLG20oEXy2TJ7pv5oOcNHBP7Fvp9zsMjuJB46pC+5D1W4SzKf9YGu3L6clLFvaNCUXWZTgH11+QP7yUSWSra4wzI9FmoLAeOyMP9YbjaRt4vv5UBXXLmtyYE3kcL+j/B8jcJLTulZHPIgrhVP/0l5HIilH7m/Q1YdbX5p4Vj17/6Js4leHzp9J0zdXgdNv8F0o6CqfX7j+XFqTjRPOPrAg6zGnqPcgmhy+LWW0vVPAUDP+UrI1GSWvKlPEVwcnbOuxqNXc2H2ME2vU8UjoWaa791MGkRayFDhaY+BL1WuTz5gRHiGMZXNDpnXv9Nucbjso/K1C49dgg9tJe+AbthXZ6lBmU72barnaaBSv503765KVPnzen+y4Pu9iIODhJOkvBCy3tBY2PYDQ+ROmdAZy15pn+nBPNUKP9OZ835zkqP2Ea4/3wT3pb4fEvBEKDKnHJXyKR3l4ca/MjvivDbhukwHf5Tb5M4d3P3svWQg9pQSVFYa8N62/im2civc/TY5WH1y5XB4C+2UIdiulXzzgTKSlj4F1Xk77wDTDPN3n0B8slzbW833+ISdnAZV1QiPjrsoQi9fbfvk+1KpK1QpTvRcOqgfrLigjceZm8E0BtldZRWptgtLYUd59SaWNngZ02jjMr38QeI9vzvUxqj+iW2ALlnWciRfoL98W15e1eDo2TZbptmptHXZ1+nkdjPMk4szOGTB5L8mzWqk0v9k1XLx3IOBPx6LfGv+evZen6D+5Tx6PAx3IPOff6JoPbjuFOoXG3S1UOGeuGpcslevSfTxnPgVRQ3H1fy61Fmb7pJjqhv6+VdELuVhoYjUqxocV/vxZpfk1SzfFN12o5iZDDJrVaTjDknb/3/ASjC6DTpqHHX5lDRkYiIkDwjLPZOIJ0HqgYB1IhG95mfwiwUK9i6WicT5XLB53+a3K5z/xfRyV+TCVFS5ko2+C35y6zr0vFqXiCfIuVQykGzVWYG62CLVqFobgqeKgKD6MKWrWd347n/fm5HLbuX8i+8Ru/OB1Z5NH7clALVdDXVC2m0/cXrSRpIKrxTfk4UqgCOJMX1o3yzXaO8+AQJhmxVIUopnBjOhuZnUB6wZlVF0JfepjAoibJAF615ZZOFNOBr6I5EABVYkVobT4zH5XYySBEvBLwhgB4Ugw4FsZGkdmilf+DQ09lRn9ljXSD/uJq8MU1yH3juJGoABJCJ8DqaxQQ+iE+7Z0piZjE/EzNfRTIhD3wUBUzUv78WQA47JfoL7QbOmHsbmXgvo7o4zKXbeEojy80Px6FI5siqL0Lac8vkvE6toNnAEpGG08T0w8tKheeimBTOaxcxBgflTHGIECLxhjL/kK39KBb+lLUBbR+6tUKeGImoizbY1GWU82ZbhItjQzSAnQmHw4rtBsFyA2IGjTw3BhYGvt1dsoahNp8S6S/JzXq7PliDYdQThSTNtfQTXmZxWUWAyyQKuagiSpuEN2Y7T/B5yeAOyRPts5KFPiDrdJsSbdE92d7sB+IJuUT88Uxx0OXkFh0Nu5KBgbJ+dg3qnbgaI76FueqQ/paC2MNK2Qi0a0vI507uxvQe/U4Wa3dY8OwrFucc0hEnNUoKHA9KZkPvYVtrFoW3MYrfyeWXUX6RJwI3Z5uS+BHxU3p9gQual5wX5azo+IV6HEFE7VtDbZYzQAeJqpRQNgaEUs3WsPXbdS2NdkYoVSr2o8P+SQ6W/GhJF3b1s5fTdWqOvmraVp1F3+VSa3a1m1DDKBxsmwbcbI8JD+TNqm5/hcTtyOMazsAgENLvD1/eFRVdjPJAAMMZMAEshAJ1gjxC65sY7dgtERgEtSdMD+YGQSSgGBIB7pinQHsRyI6BHm9+1ZKgcXdrnbBbam639IKbnApBoJOWFAC8mlYoM23Rnv5kpWw/EhYQ6bnnHvfmzeTSQjf9it/kHn33Xd/nHvuPT/vOTbgYYOLXPLtInjbbbA7W6XdGVnPHnY3WnOBWKHlCaS5zWSABtLippKdwkS+k8AmDNWbhTFzMwIivVkLVrZzO405UyE7dkYduemJyZLFfB7QcytF7Qe2XJopo5u7rYLZ1w2Wlddv9TFYstexGTRb3u/lZSGZNP3uotffhOIXs1iUzVKBJQOIcNPve2NzYGN9AU3NvUTOuJJVb31ehic8eembzoQMkIBfAXZTi40HTFYl6eodVhBR1lgokl82K7Gy7wYpYeitnxIXYZ5TdyPMEYbPWZJqvH3dUKOCNS6uTM63B/xhg5E//F5Kf7Jz/IqNrohk9nX4sJiCI1TnXp4L4JByBRYc43/13K0YZisBzCYJevR11HHWeknPQpkT4fjAZJhD6AUcGDUdBTVthTdKYT9MZI42aMSt+vaqtqEeTL5ccaQ3VlLUteFL5uucLZr89bVbsaLmDb9Qfcc8qmMv5iWt78VoEwC1zmhEc6MLjaUowTYUkOwylLJIInKMN62hYQuN9V6u5MB+/SjVLLX4nPtQYx+aFjm8gc6le/l7DxpU7plEzvb04q0e4CXfOFLBjjQCK98Yh3dnAj+e2n1PXpfISnIuExiE4D3Ef/m3CfBu4Z88K+AN+w7TLIkEcp/wqQ29Me0ZHnfdQvjYTKwb5yDSb9wrwkPmsCwt/YZHpt+Ibl4qYSjg1cJ3PWuA1yH+FMZSj6YYZHy+u578sTZfd5+5gsAbNW//eo+W+oRvez4hAVGyvQDa29uzS28vlTVECXfyijW5JmLfMHp6yfroUOwCOK55FuTe5pE4rpSFlJ1bKKjUjHV6EqQ+5grDhpH5we5DIcRhNYeG+/movyFukX2UQvyU4/30yV3xfK6HBsjnejOgqo8gDKask1nBznEgNhdz8rwBte4RkWh1K//qP6/SOqvhN2eW/1M4nYV3sXFs9vTqs6ie1bRFdTOwpcNAEylWcqs7KcfQZEqjtIXiKITwpjuGkPJgLiI/ub/T98wznfSaW8p7sOd3Gq7qay9G+vLa1OmiClWim4nXD07+DEO5kXgbysOLDrzoWSLZ4yMfrY+nsQKo/uOemzGAatL1Bdx/4m6EDMNqJ45j/fcpguMbpFaruOQNa8fryfqey8n6RViPeXmG/be0X3kYj1LSUIwlSd8WtPDR0JPIAlWGINv6jrgxjzSgmuKHPo0OX9uJz5dbkxYFy04ipAjd4GOA83agnQB1FKsI6rFmL1b7+dpcSiSvQSM0Tt9s2/n2F9BQd+mKWSSOhQN+0ve19EV4/AVBSsZ1lrlslPILUcfefPSU2710LHBIS5aNJbBhJAyRFmsNau1Hg7jX7PEGp4tgdwwT3LawRzEPc1FT7YiCI14XHtXtYynJe3NRU40ow2F+Tvd/Loh6Li8OC+u1McdZvR7aBz5HkI1hL6NsTezg3RRwdqy4YMT3r6Y1PA+H06VeGY227jO8+LzgtYMmLXNTaIo3aK82vYj3mLI2ItNHcdB4J5wZLllz74O7TbIvPEM/2KIZWybwRz88Lu+mbhwiC4fAe6AVk4S7DM6oGupvrA79ZK/WdTbmYfIudQVkopFNq0gGbiWwc6VkPXN0KGUblJ1oaVc2Y2C5rii6sIQeRIY2rXoj+Qa4Dtb//UETf+0/rsbax4klC2ah+cTtQQA8DgCga1Bvrco1GZb8Z3AU9Mudfqwk3pLyE9Zqp3l8n4yhfeJahTCuuLQWGhc769L5ngT+o/6dzhT7Zcb7tz9vzxy4rBGj6NCOzj39nqaNfc/HQbQvFKiwRAAvUqNuuzjI/hJ0YqI/vnbXbeiRoUE+r/VybAB6RPGlWY2NYkxv+PfLdMmnknRx0VL7NOkLx2XWNHU+rsy46u6reySqyhCKWL+6I1WpEV6XFidmDK9vSrVe6+PnW7/r9We9sTj8bNfuaL0G0b5B4Z092J5grpK+G9pPvT6GZng+pQAdcH1Y2OZ38fm9xMEOEWtTYn9AC+WUkP8T+h/x5U/6759ScfDSZ6SOqDN+v2E4a+IneoQyRJtj0rgk/xC+FecfPl4xMP+Awia7Qolfya8goGxeQzezQmiuWNVAJ9q2+jR56Q1NpJQKI52qgRilbrCOYJvn0UMPHNNon/vhI/i4sxj/fw8bUh9aA4BKP5X+WSWqpSwJ69FipJdzB7D3X1FrNwQUx8l4DvosBNZHHxgHuU8MchjmykAn+lZWasOEgDQhEAoYDbzrnLurhSiM4uPCuMzKMaNlOtTw7ZuT/imUv1ZwFC/R7MO/vv2nb57uLmgi83j6aXK4wWbJQI7RfilG7za8sEG28pOoPS1vjZ2JnIhFDjcQtz0rcngv/RjDx36gkQq8+tOewc16QR5di4w1owZsFCpCx7jY7BnAM7XgtQAL6lZehBnVQ9eRIxbZNiaUxkTN9aGHI48uffUg5tnVesvibx429oaNt4/jr+qF2eiL3NyeDoKTyFC8bRdMwxXM030BDpFmsoF8AU4q64HlXS3cYDHa1EgcpJm5ZniFIv6CSXeHANoF4zzEfA0ojTcHe1HRpTgx1bdScyGWhSxAsBcJIzILuApy9Mx3MvSAR3U2cevvr2r7Gz/GorpvX4uLCE18KNRoH0229ma0tWejPiYFNYu9nHznV+Df8PsM+Dc5pXyKyAcYie49PeyHDRSgMIfVZKOuz2fHJJDOTGUzlTsmqzlj2KeAeAXRgtNocvO1FTXXTlAt32LlHQKlGuGPQKf0c+25QOvTo/iiG/AP38TgTTf7vOA0YiEgJXpfb+vBJWGOPJfhntx6i7LQyso7AeOku7Td7MgEMnZLdWZKgLKi6jx0xPZlAjhtsaw8YDdc9AsZDxcrXUM3wgGPaV46XG0pM0QC+PJMieeHjVyWMTmVie6jFZ7H3MFJiDABn9v0Zz3JUw8meeph39ABpJR3z9yMrv7hIYqju70Av+Hxb8hPuTXe5khM9yQTUSW/ijquUX6qbzA/1TW+59eA6y36GIrkXTvm60bnxGKA6zWXuLLos+vwzSTPimzNs8LKftRAa3BCz4aUwn+Jbjw/hN05JyOOzKBmdd8TO/meZJLvSTb6nvjg+G1ir2zB6zPoR1t+NCdZfzIIejG+MjW9eLJ7MPTiy+44vfhpxe3ohQ1vdd9EVXELiSdyvYfJ9T4l13uYhPUpsd6Hab3Dcr2v4uvWePWRWj6xq5RPDN/y+MffSqptgWqYG6x9mFxm3niQ1lfrs5C8tXB9r2nr2z2I9d15bJDru+Dgna7vD1Kub31OVwr+arbxPLKmvn+JakvVaY1lLYQ9SqI8PeHmLmqsLVLXxwJUsHriblNVpHtJOB+eO91U1vkdSnFrFg1gwlsSvzu1LLo5CDPV13Hfb2OdMc+QWaYMk8tLdUlUKbNTChL7bpNSYlEqbEqFtagxXMgohZAJivUjxCpa7Ocil6VPxVQ3HVPZr4UwFUQwiMHkQK8U92n7URhTtISu30VLyD2ygh3VWxHwfbn6x3H42lLC92bkxRxTRt0Z4dfNSu3qOjsCj8wdCHLd4VUCva6h9hF1YcybCPT7vejp2Q/QhcJLQl11cJe/8Ly3GqHt9RrAPRonmInQLrUolTalEqE9NRl06hxzKtihY9i4wYP5DvCv3MpK7Gqt3auWZRNUUKzw9o+Ss+a5CH6dBvAUMETJ/iGUAi0JJwN9cDIjFUreP2hERDCNv2NslPoiO5xIo10S9UvshHONCf4htTmkbK8QynY8E4IWVOMHLcgV2aAJVIfaEYmFw6hAYotAYgsh8RHJL0degMaGFjYId3xsyGFzscfs2JbWCp15ferbqL5Vq5/ep77NlGK8KHuyqOpKQ3+tKmaNNKRV1R0PX4dtARyL3366W51rSkPrP6Z2Fu2xUzAB9YW0rVVsTOQI1D8Tvl5w6vTNx5Qym5xhJUzMHJ9Ywvn3fBz/XurYKDzx+8ppz3Rqu/RlwbYQNUQvCFQb71qVa3rXDAiEoeztImDRIZeqhlCku7g8FzEtDU0aY9Q6LHMxjzV2Rr6/uSiXcE88HVieS03OQvVGC/56EH911t0I37MFvTgP8exVuSnRBZZoGHBH6BVxirmKUZWn1HT4Y1nzxu9GKiuOgEO8JajrZJJ03VozTs6LFuuV6k9mrEO6geehmRXPKI+1psY3m0ilaoWFwstjARcuu7ZMGrLV2mC5cEHStQXR/NB1+VB19AANtZIIWGZH5w3M0AGjsZB6G89fvFDs7MH957fCOlcA3b4LyC46uaSJjfelSLBtUJoIfsLY/rWk9q0Dtn/RcQ3avzhh4PbhS8CgwvPYiRc4FzjNYR5ejws4DfRWFM3jelYzzLIRWqY4rhW7+FsLiRVSnT1uNt9Opkg4z7s9fo3k0Dd3z3T0rM3G9KvyDOSr4TtWfg0+bZ/MkI9uegCLffHi4XoxcKDKOjrXA9bChsq6GxUZ2xsWG+4DkvIHjplT/MBf5xIxGspcoYCM1J+kwMH7dpjalZXbkEejM8aEN5uj6UQRTZowM99OGVbis0AXQpj5LMyRq6TxXwbk1G1uF36vpIuvEqaO2bs8vFZUFT3gdYd1lmipVWagmW9LnFTSBQex39817vct/e93pCloW2BmRBAMmsvQi6h4A5lUM1PtG1heL20/qKw69/NXVtLON3vFoWBWHfvhUFiN27ypMuFQWK0fClEH
*/