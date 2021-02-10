
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
WlwDZETCpSc8LMz98QyD30SZ2mCq5CwxZa6kkWTed4r10K4/PSw86NcudjpXjsf08av3TZj9rbd9EWT/IRzl0DqndA2DBq81jpt392i4eTnUKB3TUflijLNOfIJZIMcuHcw/TK+GzemH8d2jwA6u2oFuZ+2rxrX/+qavJtNfTjtuzOTFaLAdv74aLSLeXjR567JYty+LzXlwy9vzb6PjO6YwtoF96Tr2fT3bh388/wJQSwMECgAAAAgALWdKUqmFoVbyBAAAfA4AAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1NDhVVAUAAbZIJGDtV21v2zYQ/i4g/4FNUWDrastvWTtPDkDZbuzOTvzWFN6XgqZoSYkkKiQVRf31u5PsOO1SrF1RDAMqGBZJ3x2Pz3MvtGOENpxpcWo5YbKV8LoWRS6Vp0+t0Wo1K7/I7GK5qkapknfFgyE5X02mhGUmsBz7oOrYlTXrKVkKdStUTYeesBwl0qiAZcdjhlU72M16k3QaLwkFI1KFH5gJZUIW4iYLlfCIzjWPpBZHVmWpS2jKeCBAr11vvSQ/DZjKw+RnMhvN7E69WW8dWTN0rYYGRWJCzozoEjdi/DpmfsiJEiyKe8d+GMeCsCgihVBEt7lqG338GW2m
*/