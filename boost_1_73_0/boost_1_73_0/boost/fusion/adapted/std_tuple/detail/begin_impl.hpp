/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09242011_1744)
#define BOOST_FUSION_BEGIN_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef std_tuple_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
PAg1bFjTwIqahIymHJOhUc/cJOibBN8NGe5a2OYv6d8dVRoJ4bZBzIaka4HqR8M7A25U5hSopUd0qIRohgNWIWY6tFp5tt/MWdu6JgbCt0iS0tgJA8Eb1Bcsq3DHjYnjMvDPg2R8vLesZp7jmGFAWhRdQUw5sUGw6bjQ/URB/18pbW2sOzqkwO4BUhne0K02i2bKOL0gvIHrC38+zZxoPp26iPddclSf5GqLQ68iXaN721kSZ/FZPE0dE69r2UvtTvCXfz2bBo7HK6evvtXo799og3Gmx1hwVo3N4h7848BL6ZiFbySTYIyj3cCj9wSbkHqFWI8Q6BXmj4obnRP5FVJaSKxHxPgXMjnC7nkOg4OrEnLdR/je+dfxKmYT9D/74dT/GE7DbOH4+McgegFaAZkJ1LWtkChOezoJsnkSwWd/Og+chGocdMpGFeTxFbDqpZk7bM+jqyi+ifLYdoM5iiV3UV7OYD7P8vgivw6u42Rhts2corDBUBhXXVWxgg2N3IJqSUH70o3SIAB/msY4FT4m/zOUBBdBEiQwQtkhSfBSj7st5z9QSwMECgAAAAgALWdKUtaWP1KQBQAAVgwAADAACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1VT
*/