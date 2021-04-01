/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09242011_1744)
#define BOOST_FUSION_END_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template <>
        struct end_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std::tuple_size<seq_type>::value;
                typedef std_tuple_iterator<Sequence, size> type;

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

/* end_impl.hpp
s9jDNeqiOS/rQB5IOXEwHXAO60oCbTlsgM7l+SGAUUuPP8qdkS93BCD9+/kKgxOcM0E0yd8HAMby8KrG5FQNt2mX+SfoE2O3o0bfl+zRDTUYQLG5S2/YMdR8J9bmzvonI4NxRoGDvgs28FFyv1Gf1NUaBCspYBU4Aks1Z9Km/1yQOgItkgi0nZ0euFdM3aDFcyCsK01cgOETerK4c9JLtVyFwKY5YG2PukgRNL3DJVdGcgV6LEe599GBqI0npU7Q3+stWIMEL/mVp1rp+5c3puGm7s+rkFRarp9mOuEmj+UU7K/RswTtjOZEhXLWn8DwtsfPxDxx6rjv9hM72lioDWg7ik5xxapRV/o54S+z1s77WalFdcdtppZLykjyzOAKNv6prHSmqnXt8mCvCJuGuXSDWdR2n3ANzv0XACL3XWzQi49PKCjE8AbAJx6IbvgkZen209VLosa4wklV63r1dF56gh1go6yeJ6XB6HTy0awZ38s2vB8d6Aat6ea4P4fkY5vVuWSGHcY3AFclcBWSSbohs0GzUHsuxaMxVMVkrHWxkNLToFksSdSmvQ==
*/