/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_operations.hpp

 [begin_description]
 Operations of thrust zipped iterators. Is the counterpart of the thrust_algebra.
 [end_description]

 Copyright 2010-2013 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

#include <thrust/tuple.h>
#include <thrust/iterator/zip_iterator.h>

/**ToDo extend to scale_sum13 for rk78 */

struct thrust_operations
{
    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) + m_alpha2 * thrust::get<2>(t);
        }
    };

    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum_swap2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum_swap2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            typename thrust::tuple_element<0,Tuple>::type tmp = thrust::get<0>(t);
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) + m_alpha2 * thrust::get<2>(t);
            thrust::get<1>(t) = tmp;
        }
    };

    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 >
    struct scale_sum3
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;

        scale_sum3( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 >
    struct scale_sum4
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;

        scale_sum4( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ){ }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 ,
            class Fac4 = Fac3 , class Fac5 = Fac4 >
    struct scale_sum5
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;

        scale_sum5( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t) +
                    m_alpha5 * thrust::get<5>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 ,
            class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 >
    struct scale_sum6
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;

        scale_sum6( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 , const Fac6 alpha6 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t) +
                    m_alpha5 * thrust::get<5>(t) +
                    m_alpha6 * thrust::get<6>(t);
        }
    };


    template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 ,
            class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 >
    struct scale_sum7
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;
        const Fac6 m_alpha6;
        const Fac7 m_alpha7;

        scale_sum7( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 ,
                const Fac4 alpha4 , const Fac5 alpha5 , const Fac6 alpha6 , const Fac7 alpha7 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) ,
          m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) +
                    m_alpha2 * thrust::get<2>(t) +
                    m_alpha3 * thrust::get<3>(t) +
                    m_alpha4 * thrust::get<4>(t) +
                    m_alpha5 * thrust::get<5>(t) +
                    m_alpha6 * thrust::get<6>(t) +
                    m_alpha7 * thrust::get<7>(t) ;
        }
    };




    template< class Fac1 = double >
    struct rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error( const Fac1 eps_abs , const Fac1 eps_rel , const Fac1 a_x , const Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }


        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            using std::abs;
            thrust::get< 0 >( t ) = abs( thrust::get< 0 >( t ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( thrust::get< 1 >( t ) + m_a_dxdt * abs( thrust::get< 2 >( t ) ) ) ) );
        }

        typedef void result_type;
    };


};

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED

/* thrust_operations.hpp
TyALtm+8METKIHGvVuZR78voQ0QGJEnBncY8rTx9gY5ZjeTkb2dUT9tK3sbl3D7BP9+QeGvECIA9u5EEQ/c2tgXlwewtB6hV6Cplq3//yk1Q8us1QM13HKBhbaZYYg5xu7mqAJw2dsnULwTgABfcGhBf/zprMA6xsItfnJschuu1pQkwXB2b98ol0bH5NTl5fd+KYwAJoZISqZSgb0ICQJDIb4nlpwuIzy/Gkoj5/lPWrsucN/hdWZkWPm8WaZ2Wmm71lIU8Y5ZZFwWhuL2ATqYDy3/FYimyIOpXCH/QM5S34DgldrXW0kMHBsSW8vGlnLwtfzSAmNZ7iFge50//h9PSX1Jj4W/lot95uWdfHN1TjDA6twAULOvTBuCxbdu2Z76xbdu2bdu2bVt7bNu2eeY/SZ+srOumWX1v2tkRXqmjfFvbM4f9fomcMMr8HTMCtqdiCOXofnIno26ZDMJwl6MIRSn3xjWC9o9hsnO3BtEGXpPwJ3LiNHgmyWOwIHTOCrwfLEv2E3mhN+g3L88zyK8eG75lXx66qMemeh1DaF359xuMFLNTQoLKVT7lEFH4wTklJvO8gefxj73y2ky9B8WTRCpnH37S0FJFPokMLqP3qYwPpe8TIoNqKrtij+zYcfoW1SgeQvHUkRtXBJjoAbZSjCE+TrXYO5e1JgypGPI3JjEyjrwYnd0Q0ra9m4oHKWluObTNgAFWyn6TZ0org2Y9bVCvUBk94N8fNHyAplcoOBtpg21Q/ME+sXWOTcIGeJvbJqPKO4AGYDfavovA2kWmy5lpnJGbBWmBrL7OeH/0udU68gPWlthmfAM9KGiksAuH+gfFlupklfVlSe7BA/fshBjh8OP92GyDl9H6Ym3fGulGX9WUWtXSw4bZpIGJMguVpuVGC8Aa69ZoOsiKXARqvXpNWq25/f8wt3uDd6I4a+p/t+YKDSWH81l1xZ6CmURpg0LLTUYSPNWvnqcO/TF9YXp8p8JRcgehu+pxE3lR7j7fPjJIdrZgPwv8QD0xwA7GbtEDyPtA/SZwWFX/KQ/wEt3ZQCjzTmaUYdRI2oYvbQagu7lfkfBJj9YrwyiNCmAkIMbhDgA98o5gkxFc2RX7dpTYFrJ0nt0Va4m9KPTm1fVm/6SFqkAFx4le4KKZ+EjTsPCMuxf3uMS2C/Y0hcpzzIbDhq/xd4jwscDnM2wJgkyfu7wZHmQiSIIjwZKKMj/UyD505+wg042EeXqIzfVB4jhshvb9It8ic/NYnd1daYSBtE2M9T1u0u8pf8w7syAFO1GG4zutz2aSyEMLekHYWz/hm0Xte/aP1w2YjtQSieMJ1yckuvC12IZzVyyB0TzDpHrSXanTel/i0Zlz3gbH+JYG4hI7NfHk/N4hFJYs04uQh/1+lNE/Ab3GK2JUwGrwZ1fnmELqedWOW8DKIUXnq2P5YPhWrzcg5UKDomTv3r18i5JC2HNr69bo4zd2rai8+2veu3w2+JSVjXji4nVlvtiTeiFnqd2JlUTjlj14uGE332Qb6tTWhPW1tO1/ejZ/OI2nzhSlynYpY0/i/VPt0Xwz5sH55uAh8ztmOZ5drjLyfYMb243TLfJcmQTyN06tMVNq/cYRX1H3hp3xHjn6UbSHe0wUnUwRL9NNKRviC+wp8kBTHOFr2QmYHb28tvSJ1cyrVS3ijdfMKVlJq3xG4Jaq0SOQl1v+ULH8xmrxzdHs061Re9B8jK1WrVqtXOZnUC03oa66xQ/wY/LaQV2D5qQf3dFDQpVkAHPUiWCUT/wV/kbnawfx3R2ir30f8Z0cYoDfhQ/xbdhNXEIQsL2u+Pq5hIzHb8yDzAlDK1L4qTG/uojOe3yiBGaQhe+LPobbLSlsnd87NfZSm2Gez1Ip4nMVwK4DbFY7Vpo7ncqq4XPWyODFZ1ca0Aigs0uvCazuTvrdjFlIRd0Xd32wE5oIHKr35OqA7wqRQ4emo6q40pzuScJjIQoEIvGGehiYaCw8r9Yx7Lo5+jc8l3DSHXZPeZh5efhSuvqO38S/x/8UzpSrUYBCQxzBeW/QDPSTSmkEwPzSF2RaU7t/TBq92nRyr8lAtYPT2/nK9cCn2qNT2cXcx4WSC1H1Gmyp8v3C9wQX4g2T09qhnoALOL3VIyn7A3w+ofxi7jCgsUa4n8sXTH5hT5zfURK3eKv7sQ3dBwlE3ccllPHfxBWoWACsVzysVyQ0nJ09qe/q8en5+7JVstV72CXo2jZAR8sNGWWZX7e/8fLW9hRgzIBotEIPb7/kfYOULvUV8xpK/X50SQaaDuT7o+yR2oykVX/BOHyp1C/QXMGxq+n8lciZe8QXXsVOQFuNO07mQlQqq9FOrjF6cHcY2pdEn32Z2GUfFONzetvimJ9rNbNvMAelW3GWGXHjOX/rKwsL+YEGYyoipv4OXgSuegfTwoVwmu+Nbs2SiUpPjw9EUJYeJKx3hmsX9U6UGejPcdMSwqtEnjUE3NWPC6Ozip75YkydejlibQe9hqVtaR54aY8xpI0/hNOEeuGAXH53hTvuYux2hPePTLERz297t5QZmhZ4BxyGkcsQgtZ2D7FnxI5UPfAFiUsFb0dfIz49C/Av+QHnbJfip0tzgSYpv9E8OOZ55QicrIDXXd1pZsw8Ncsr31D21yHmwsEN1loxpWcboi8+VM+q+TxCAT5OUj4FyjKIBlX90unJwWL06y9WGaGT7RRLVjH7VPzt+su92Mko+0H5Hjc/gKoespybDwI+ZiuZHFc/Opwcl+GX44ke5M8DMBya60mOPvrSHnQ1iY7LreHfXKTqGdoOJt8LFCIoLF0ZhNR5ZnuWM6j49AUKqJjlR/mIsq4MkXM4LwTjht5R0gYNG5RVPYa4Y9f7BUo5y/SCHy+ihbjpBA9dN4prjlHp2eSnUQmarkbKwywSk1v24X9urRx4aQ5tU6Bpr5/huH4V1ze4d2TpG3aGDJI9/QnA82bVWMDypWILcMta3oR5loctywfbZ5WBhbvjLZS/pXyhGbxcLhYG067smrw6bdB486gmunqohfoG+VXgUTpFNevUMbU0nc0l656m636TiiRex5sMCUNQPe8f475ZXVPPL6FpB69rmszWbLACigdY3s5Z++xGKXp1Gs9QJK+PwlmDS5Efpszywq4cpsY9qgIZDSAWdgaNFZ6W0LnlFsPL1CYAfCjztReOY/knw5FxyL2V44yh7p9wJ1DA/D6UXCqgbwGVfHza+42eb6Mz6EcRiOCaQL5CzJGy8/K1lFv2qpVs920gzf71He+39PpfhdP1iJxuUl4nIJq0OxFdxJ4u4+03+0naZkCVZxbGXOQeHkcnmjPz6059T74MZhQf2fb112KmARfB093ijRiHkptVP7m5LfK/ekd5M2QDBKIw6wQ2rWKETUDoZp0K7J1UlwRB6yiRdzpo9gEDIRd2xtdc67h6Yl+clJAkURCh/1plzbXYhEFeI5KRHzRrblzNZX5Z1L0rvfLCy8QxDYKo5thTHVcXTDhWCw/vIWOoS6sfIM3649KXK0SCuACFZhzaZgTK5GvkNQ8iVExLXFbOjW7ohNpIo9xvZwRyRE8xfo2RvmjYGeNGyk+7MgcSoWnIlv4hsMUOzhz7rJpqwngLTW8ejx1CVksfGqeqMUs56noCTHbXvR8hT048K8tuxa7sgedMjXpHfWNg0rcvKjMgjtnLubZrPbaSUXcOBkyEsibpNaIEa+3zyFl8RoWyJ+FxFUO4FeDeoAe7uqa2y8aTbl/yi9CnDg/WNF44xStLxPA8De4axsQCV0/IgrQx3tJN+8Zo5u78ywV1Y1wzUTn/z30zVntgM1viquiMI+zldB+mtiO06qB2hht80nY+0exFa8+ePbYvJXbBgtTvPbRuT39k4YyQAOjj0IdLXIBC971KHgwJvp/6fZsVneA4iFgxFyu1cXSwqij9qRVRIkwU5WP5lbFkURzzJ0VYg9/L7Ere+JBK6k2ChVcX2EtSYlqvGe31Pf1rTDLl8nGIzkQbmu7wJyKI1B6qeeCDlEP65gvP+hLG+2GGDChGuCJQnyQAYUfI+QuPIFIWkBgSForCgmYwgjZ+pHlykOj6RG7gF+sk6wjcWYwJC7raiQj9KxFXzS3vB8xBvve9qdZDm++eiexenTjo6L+T2xBLU9wLwt4yC2AUM+0cwH3Ygg/5xZk94CyAX3eu6cfuTEhWVdrIAL6EsVkrkaXlDdcvOIzl4SX0RvNADhQ737sPyCIr21E9kmFUNX5rj1QWhn8T0GRETFJPRiWBW43uEkOKTNUZlAy9Z3MZzmEK0Q/zP8l95/Nijab57esSpv9hkthGjtlU4eKS1lorw6QUa/FvYAnDSFJTJUku6IyyI9Btvi2fP3GDfjOllW3OW7l+kD1s1MtTZ4BKNzoyHiSm0gqQaWgMs2Rj5V04PZjllFqZ4dnN7Rt72T9sSU+Gv2KBwKE3UmDax7+OfBlIE8xXDxwK210uEx9XfD/Sh4Fb+LN1WQjo+IekrtizKq5arcttGBlOuT6ANsJxPF+/SzUli3xxksv4yhazQdM3TKzeTyMMphbh16IXg8eKG8wvRqx6V09kuBk/5tlzsP+i/or0oHR+je+D90a1Vzc5IGsZZmEYksH/OFx0TOe1tLReZO2GODQ9lUXEy2SxFSTt3tH0ZjQWgt9IggCOV2YgpGkyQVC4YkmH58UbztbTPRN669ttEFhrhxikPcDgE3+HkA/IhhZqbGOmhtmhJRhKHXjzJARFB3ZK31LzGb/WVlUDAXli0/dQKXEMskGUx/0+eSbP4GfzF1f+jnar4qtRlEuDlYyMX6p4q2S6d1bRCKHe98BxvKm9v0/Tw50nuKJXR0srQlAvSDA4woXjmQlTyx4+c0ycPB35kuhS99rp2nP6lHvTToThsQxnJ40CV2Cpts7MwvuFg6THsIs/R4531Uo2XYxYlut2noa7ZZSapd+LNaXO5xnyDzVIj2PNkmVDhW/9x4Txo4um/Z8Xd9qcBml3WxYueablt2CLb4Nmn3ANveHY0geq5bdkrwHBCw/fOTW3Rd7XDP8W3zv8y+QGuZ2OPeiL5xC2NJgXJGytbrkqvWpVWvny2t4FquWzpG8zfgM503iHRecFJWhkfmrBrWzLwszvC6do55ySCfOG8/sZBf3OHRcUHPXx+3LJvtdD1fUEi2pr9yhWR35Y2WBkb+TSKxp6xe3naX3jAVQ3kv27zxc4US3GwYcOX6+k948XFhltb3dOOkZcE7T0V+M50k9S4CJJSJXT/Eg7O++e0uRKYdEeRe+KInzhpc3Pen4sHvxYYW3TLqCZlGouIHJtzfBoOLGRMyipHugvGo7awuPl9T6LfhbgzzC0vXu0IUcRUQawj6jna0LVMNkTJmRY7V7A1wfrxPOX2zKZTrxqZdE+cmUQWRW4VIU3fmOkeQVFmfj4XRAv34rpl2CKf3BEGFd+YENla+rbJBaN/qdnoRmvoF5eGfLgvPgIFGnsueqRmuNzJGWFuTqNeSqnb3p+pl5eLY+54lewmvBFQLLnIir33IAX0TMmGmkWnZ0hV5O51bVLdGiAOIrglqisD7JFy/rM62R490qwPHZy2AiVUoDQ9vjW9PqND9U+fyOFrE6xi/WvdDhWmAJu/Fb2oA8AVmIgPF2W8kIuA9RsaQTa2g9KtoxIT90iiPDF4jyxSFNM/l3HBRnuwdBJ7I4YLVZUosEadBhAgEAYRK0rBrqikAy75Gj6OHrrsTJbyiq0Tsp1/rgYmLUI0co2ckWWqQJPQieMVDvEszg2yYQvnp+zyle3l1KxPOEPN61ie66vtszBJIcUOKr0zi1Z+G56AJFAP21BYNpDx31j/pFFFcxHr3f1PUBq6RiU8Mq2FXccbmCq1PIGzrwkB6W3p99V+o5AT0vipOy9lnYaJ3ehyMMhKkrdYJIuYYQVUCtJzb4vz+PqYR3k+MyE/n46utTGShPF2BxYKEvePLit0DCW4o1xMzVGgdN6YTu19ZjN7RBn6nytalBOqyztGpZ8j470kDWqu+XvSX3t6zcxqsjhkL1sZzLS9rZJbY5HlzVILeMDzlShep0eNa7ZMzMsttoAODrMxXGCWKciEjrPZqyRAXd7KhRSREU7/5U4zJjRvLueCugu+Ah/kL3z8Pi8si922iDXuQih3AUrEbiF8WLho1GQu5I1Qt0ImDTj0eauRI34rwJntdCJwTcRX7UkIkw1zkSQoX0EHxJURo2WS14rrlgN7MdKPLGmGxQrhxf8QP6Pkre8Awc4UpjTnh9Tttfpoj1ccXwoEasi+KfNli+lNV7HEsaYmBqaqBAPAr4hPYrNRp+SQ18ZKw0Os3QEL/J37SBX3C3RCKXvYsG9pZGcTLgdp68h6RVJIHwRMjXSmeSDl1NLZK1ZKi1ZGV6oqXYzhBkqZ1t+zqe6DrKnGSSefE8ZwuJMTKWgCel8Mn8xgso3RCrpiQi1676JoPcjpeOjTCF30In1LFTWHhVbsWEZhndXlgkCyvYvCOL5BaJw59MIAoOwQPiYpCdZq0Yb6xoxWTSoV/MBSvkvir2fJZzoS2y4c+M1BhKnsVpQmfBjo7hU5JAt8Va9btUni4yEbrFvjMh/x5YqiniW9lL4RLq5D5ByrAmDvMJAl3vdQq1hUDRAA4Crl2DGoE/nuSQ0jj5AUdr4ZglZovXj7gs/VaBCT9gBxlYNOvY4+SxrQ/6zcZHrYZ3q3Ib578GzvN05nBKnrlNn5LcMPnWFlSgn3Bz9gT2t8OrY0ogz3nfN9lLIzyMZqD/ev4Ofni8OWthT+NWX1ger64MiMZAWewgwlENSRLLb/hEYLaelvUWoQfekHCeo0WJHBPOfzWX3DanZMc2hfqXwmQnNZ/T3ulWoz06V2OXjEgPKJWYWG72TQEjb6xQaQEslwXOcSCfJ9j5XFP8+RMmjneFRxRQzOvL93fVT5MNlBn9HnMEpGUM0Ew9WIw6ENJwz3KAMV6IwGIm6UQ5ZE4HTuKxXOMKKKMdv9EMwk/SIjk914PJ+AuAhc9SHv3IKMI1rYBWT9X4BZvs3XhQ1ru0IYnNu8SfDa6EfLIXiAnR8MbJQhaljH/SiJ5NxW0ANAruAMN5QQERdRhRA+/woKsXPEQK3vhv7Cn3/sfDGOlDEtDuqC3TXOe6ZZpBnHPVSOYChRaY9N2wNjxVxB8NG2MXs0zJKcvNMFlqDYO6hEiU/vmOj1lfBL/SXDAgIeppRkrdoclYsTyjUhBKvrvtxRwiKxLtFkmbP4jOfynQ465oazOYzlTcS1T6nEFkjnUoUp3vwCFGYNtKovfD1pe7ycRz+4sfBTPxOtvux5PUlGQFuGlj3obiKMVTGUABENEHVr0Tw/ZSdzqWS0XpKkxg8Y5JVfVx//rf0RnbCB7xkJxqIuh6uZKUsZ7VGdeOAbFNhODEiJrommCJBIWEB3WIcTLu0RZQnGp9NpkWhN+V+nRgqXxS4Ku4DXQGCkHw6qGulCXxBamgPaFeQoz7wGcfVtGkdNq/7W/HIDDMOENbiyVaA4W4apnOP/oPqjVvKOAdmyOlznz0z77iTyXLKKipbM1HiiZug6gUwU5S7/jXjRbInIEj4y8pBDHhLoDrTMKAOfVXUor+r34hmHXU6hUl7WiTh9KPDY/Zh
*/