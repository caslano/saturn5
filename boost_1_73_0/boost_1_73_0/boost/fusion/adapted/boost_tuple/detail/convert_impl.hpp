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
C5mBqnkqclQBbFAfZGwsc/dpEfEicMZHe8s8GI7AgpD/0wpUErpgAz/jF9hRdO2HZzu+ff+vODagtgyDJgSrUYlDYplE0ErqfsxgIV84r7sqqAmqzzhCJLYUsBwLJwxNmzR6jCE3wsSuyTnTbUOTqqTmxglHNERhMBBKgaqfNWxk86Wvnt4fWkfWcDrn9nwWG958Nus2gtCP/ak/iwy7LMn2ALsPiasbqWUqS9VZOX/ZV8HMMawqN3pldJr+/ZFuRCX0GDUg8jFt7sG/BnwtK9p4kBMuJoy2c5LfMuxdbqVyPRkh0ovujw8ScZCE73J7EPGIJPZdvlsNoK/iacN17403O6TgfEW1rntGduHTkrOqrbev/jOsXHRc259sd2Z/cGduvDDsLOv/x46tt4fWu84gdOJ56MEnezZ3jJCjHHCCU4JO4l+C6AfxoEqauW1dywYbyRyM5t6l5197id81KTmgME2cncYAMo8T/zy5cq78cDHgoeI2jOSm2jwXqcCeg4KzGluNpbzX1ihyHLBnkY+T7EP4zVOCETYNcvYsn1sD439QSwMECgAAAAgALWdKUjIEGkxrAwAAPQcAADMACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RSQUlM
*/