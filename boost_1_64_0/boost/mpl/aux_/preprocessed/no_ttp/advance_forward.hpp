
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
hunlMXbrNT7QlidpuKM8Rlue0BEO8khZbcnTKEI3T/ceUlZ7ZQpHWvOMHTxoqDXkQOMY/mbNk+Uoj9GSpxN5inTzGIOt4+mEWaMc5JHxdFXiGa2Xp0fACBmPEVc5yDNGlSc40kEeKas7eQr08jC7rGUFY/atOnlYxqx5+mDoGJ08VDN5zMt6CHqOteaZEBUxNjrYwKeJTHO2/d96Wf82QBkuSv03akuWyTD+diTKrtxB4QPGGJkv3az1EIbh4xzkkXoYqoxHN0+3QMZjyzNxvH4e9bw7N95uPZI8PbqNMJTkyZqgN54etpi7YvWJ+uMZKOMZTp7VE/XG08s2nuE4cZKDPBLzSGUdmVy6LFYjS8yyrhXo5yGekvHk3qZTFqujdTmJxOwpeuMJtpU1Vln3b9fNYytrvJJnqk6eoIBe1vFMIk9OtH4e63imKMtWrE6e7j0DreOJJk9+nH4exmNb17Yn2G9nbDOMYK15IhMd5THa8hQ7yiPbtDhlvzBNN09Ptmm27XDoHbp5egWq8hQ7yqPanuckOcgj8SQq8yJZL48xIHhCyfbcd7pOHs02v1gvj2abnz/DQR6JJ0mZFym6eXoaJZ4ZyvZzpl6ebgFBkidVyZOqm6e7NeY7le1Gmm6eHtZpNynTla6XJ0jZuNi2jZEZ9ts4Ax+lLeAc/pdn+9uwyLH8G9i9e/SwsG6G5rIND8/U/D1Y+XsQ5VuGP2f7e1xGbHJqelpaSiS7gQz+ZMuTbtLNQ/gl+4pivTy9jBnqPKtn6eaxjEe258GzS+dhd5KhzlOkn8c2nj7KfJ6jk6d7jwx1nqws3Ty28cxT6m9u6TzdjNSPOs883Ty28SxU8szXyRMs0yV5shbo5rGNJ1uZroWl83QPlHqWPMF36+WhnmW/uURZNrOVPJY7LSkcYVrbjyZ7G2x9HeXVlGfMSfJsieFBZXn41UNzz0bTy2UF7tuo+7ksVt2HUfdBmKzp2y5UOqcKl7jCSPe0J66rEpeEwniNqUxbRfolk3jKLP+QR+k+kxc3YPujLZ+yCcCp9wB6SfnKzSqpQt0YQiSGlFrSL5LEcC/pYWXbfk1iMPfxqpzTmJJT5fShIn17PcS4MlDdxx+vcE2cmamNS/qkku8zk1MlzjrmOIOlH7lZVYgT78S/KeuwJc7EeEvfe+ZlaFpG2szohFhTrMQZimX1lfWloXRfWQ8wbvPUSlxFqr6yvCROpX+n9NiMWGVaGshyZzLIb0rvSTJsgfSjlSX1cJrvKxi/OUTJc0r61IqU7+dlmHT5fky+z5XvhzR9dZ2Q75mJiQnmoiVfoQwXJ2XLPUpVP4P0Eyd5YiVPvvm79OUlv+Wp72VKP02jryt1z7Ou0gfgiBv23xfL99UB6nufju9B6t/bc3Sv7vd7n6P+PTzH9w717+39fu9nrOi9Yf17qxXvr6mi95Id3Ru+mqT8PnuDX/2BXzVftrX+g+f2tb84peL9UF2kiFUG2U/I/qOA/9TBpbIS1/aQ55bRG72wCdbDllgfe2EDHI4NcQk2wmXYGO9FH7wfm+IubIZPoy++hn54AFuh5fl72U9guMSlfv4+UuIag21wLAZhFIbiOByI4zEMJ6jGmy/jjdIZ72QZ7xQZ7+0yvqkYgdE4CmMwEmPRcg9ZtumyrS/Q3ENuK+Ntj42xA/piJ+yDXXAcdsXpGIDZGIiLsZvUY5CU519Zts2yzVbKU6a3qbTf2FKT8nAreuM29MHt6Ic7MAJ34Vh8Fifhc3g3Po/34wu4HV/Ep/BlfA5fwX24D1/Hf+A7+Cp+iAewOzEdxEg8hOPwDbwNj2Asvolr8Si+gMfwFXwb8/AdPIrv4nnMx2pM43H0wPc=
*/