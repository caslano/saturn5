/*=============================================================================
    Copyright (c) 2012-2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CONVERT_IMPL_10172012_0120)
#define BOOST_FUSION_CONVERT_IMPL_10172012_0120

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple/detail/build_cons.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::build_tuple_cons<
                        typename result_of::begin<Sequence>::type
                      , typename result_of::end<Sequence>::type
                    >
                build_tuple_cons;

                typedef typename build_tuple_cons::type type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return build_tuple_cons::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
Sd5y2Lgx+vK2HWvfGrN/aIR2Gdw7MN54K83xuJ+uQpYRAJLsbcOBhALceC8O1vnvefK7/eO4MPpUjZpBkOM+aJhJaKQR8Lqcum6bwQyPj9xAHQdbnU0ypcR8bcAZKBZBpyKxaxWXu3/quKvuQZ8ktFgt4l1ri4f5aFJ3ErRadWV1W5+mmMXnr/kGXKj4jfbF9tdrGIOyPtZuQMHrRkMhJsHiPC0IJqfgoWGZtpRwSIYy31iKLL24fGvGrkTpm3xnFf+0C+72v8Vr3F8d5WjuvNE983zP/75l5EuJUulGptScVyqpsAQzrwFtBYAo20ppxvGCOzxJz8C3FjP9/6XD5eQHJIDAa3TTgP+Ln5aAp492ck9ZLHOll8sgyc/E0UAqzl3TE4GX9wZkC0Ccb00mIyeVihsKXda3yk07ngcp8d65/xBCmRlXBhITy+MqwxmimpVv9bSRDBlrLLCq+2w4kYpid539Ei/bERVPwVqgP29Y+p3z7IM0XD3dS05X4EWycdEjUrhLTpxd4DiAz9hxYefEIpyyu4CAMwN8kU7Fz8297oErVPiHPsvqbw==
*/