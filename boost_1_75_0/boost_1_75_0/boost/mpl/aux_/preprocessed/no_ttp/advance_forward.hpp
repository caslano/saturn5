
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
+v4CGFrEqE0hCqdTPtGGkW8ZxrvGtA8evtjoc/iouWlrzpCLtY4bGe0dDclmcgtQITHOo5woNkOfd3f/jMniKIaKBG5y3Hce6jLDVm9BK6CP4GFJpQuiE754l685b5DZN5LxLr66KuCd3wJIL0rzi4eqhGHvdlCa357EyPbdGqPKBWRoG7S+pQLGBwxvt683k4owVvk4KvbbmPol75QssBkQZ8QFOAjuDrciNeNPA+5Nqgcj+69qSkajbzKSWT5F/rWSD421HUcpoq4Hy+WrGL2+79Qgvwz7buE7dvYDl7QkyXEQRisxBi4lr4+GZv+FQ9x8GPeZ7uRVxICrXeQ+n9b1vp7byUPChWUH8MZLsxfGbX8LlSMKbC8dDmwXZTx23Tl0OvEOvCbYeji76xNPv89JLEGCrJp3atVkOdUhU/3U/ULD4nk50STnWIEgzWbZTpehCl2PlV3VtTZfdLFYBl1z/F8lBqrNYYYYHaybZMEL2YEFW/wAHESUzYfGpyXz/Os/ZSWvZYlpnsjZq2fhR2DZE0RggT9Ll58xtkVVmos8PazRdrEwbco6NlfVvwHVXtw6F4X7H6odGTTqh3DYBNP6x52JWhsFytZPwxQgKp0NGHeD5YWSMzGX9dHPxNUwX7X6buMMe6gt8F70vuxmc5jGm1grQgjbU9qIAr0tpDI2RR0UNLVCAwamFLjUaDPW1GzgGAi9YGGa2L1W
*/