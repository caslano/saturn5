
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
vVFVMXgRCFVRW4N9TemmXnEidgQNBtGa8tTKnDfEvBkXxZhC937FsoHkTXxZctOaMh97j7YhZ0pZS8n7iuw1NoIKQjjXGW6fClI2Pxxzy7ynocdlIzRNkJS4zhZ2eCAR8Ic3xT3/G5SP7UrvLl6df50YxKULonZGIcpauHPYFK2FCL4VxOe+k/FL/DJLiB5W2CUThqLoxJl1HHc/5u3FxBn/hxRVFfgJGiPtK551wGoim5HgeKXKxG868FZikkyA5EjuGnlM1cmkgCsh4psyDZ7VU4QP97QVCt5w2rIH64L5gHiCscqnt9FYHii9crKHlBHSY7IFFVwLmccy4uy731f9XOVMPll50hXU5VfTjedL/JKk1JTrK/hS7Jo64UEe1BNETDEFywJpd8U+W08VP13QbkfadJMYyXASQ8OEzLqsxG9Iz79K2YHTFcjRaH6XzJsYfCJQ0SXO9eFPw9yvX3+P+W6hdxKLet12YOtNMwvRoRKK33hAvvdvPCEo2oBSsRTUdkjtim1Zdnc1gP80RtL8NtI+rg/vl/P9oae9saaLTCnPx+JH8YtgZ2dZZR6muQQi9EzAL8ckDH5xlkt3GfP6OTz5PviX4yQDvG1KCAWHMGl3Ahf38/zejbJ1QO87tZcGKx4r73LB6Cf3Uh5ijEveRvRhjb+hXr3Tv5ptKkU+Mb/m8v8L6qXYLmHdKZMuBOqaNzKBXjf6dhyR
*/