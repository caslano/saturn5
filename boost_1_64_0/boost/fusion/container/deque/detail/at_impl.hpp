/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_AT_IMPL_09122006_2017)
#define BOOST_FUSION_DEQUE_AT_IMPL_09122006_2017

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                element_type;

                typedef typename
                    add_reference<
                      typename mpl::eval_if<
                      is_const<Sequence>,
                      add_const<element_type>,
                      mpl::identity<element_type> >::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return seq.get(adjusted_index());
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
0eZ1bb/M5/8SBuAzGKPs9xjDfqsTXslz1RuY+2hGnP3+VbD8Nj+752DLHM8y9wtK/aIc9OPl+Blz+Ewzn4dsl6cv47kDTnVEm9hAPnt6eUkZo1oXCpyfrb6Q93bz5uv1cWW7uud3B9gdh8KFC61q1uW46p8fTiH2Zd5a5rmfKXVtKo5WPi8TDWWuTerV4PwISpmXxTvNNyVlznS7kp8Sk3qWqGpf5kn6sgI579nPSx+iv18s8wDp5Sjz5NZfhtF18ev1IUZfZiu0oUlZy/E3KVMZz7+xhfn8PuGTf535fdr7OM9rEKucs7X083JSpyVOmDpzZkLtpAJZ2XnZtmy35xQwnLf0+vyOdjzt8rHRx3l+iXHko8ZVPvgaaczcBno+HPe/pfP+x5Gu32Xm6cqp9JzStfsulf0fJ/moaGl+HBJd5YOqX5Sbvexcy6C+YxHWyjkvE8lL+WUyx4Sel8Tag8G3o/v5+HCI8zwTXQzzXRjzsrOVc72IJy/VrvLS4HzkrvNiPB6tL3aeU2VyFP+bYpaucWaVhtM27t+ai533r1UEa7pOpzi/EcfcJ8J8fhW/1ubHONE8XZnVxP10G3OMt7V2ntOkNfkuN8+LzGzi/jnIJ8L9eU3M57dw1dZ24drOjnVXlpdunGP5XcT7uQ/8/sSUPTtXJl+4eVDM29Rcz3diPj9K49vyGjtPifm8Mq7nRzGfp8TVvCmNnwflKbVt8asV73WYZLli0pA5k0Of2bR7jKv5Tuqf1+Ssl1wzYqWS3kXa5/2U1Nqt/DkEt+MAvBOH4w6Mxd9hCt6NObgTC/FevBrvw7txFz6Bu/E1vB9fxz34N9yL3+EDMu7tQQzB32M/rMSB+DCOw0dwKu7DZHwUU/APmI77sQQfxxvxCbwXn8Q9eEAf3yLXgnKN6OcwvqWTjKPrikEYgl2xO/bHHjgFQzELe+Jq7I23Yx+8H/viURyIp3CQjJ8Lx1Y4GPvjELwcI3AaRqIFo/B2HIpP4DA8gMPxIxyBJ3EkfoOj5Bn6o2WcQglBriG5ttT2szXmEbxkvEcnXId98HqMxPUYjRtxGt6Ac3ATZuKNuAhvwivxZlyLt+BG3Iza/BZy/QcZUs7G+S2+kCmpv8QY/Apn4RnchF9jOX6DD+G3+DiexefxO6lP3+MH+AOewJ/wUxmH4dsEsAdehCnYFK9Ab1yJzfAObI7b0Qd/hy3xcWyFT+LF+Dz64uvYFj9DP/wZ22G0cs8BR+AlOBsvxfnYARdgIKr18CL9OpHrR6185mrzE+jjVgOQQP1je+yNgTgIg3AYdsIx2AXjMQTnYTdMxe64zDA+tSfuwF64E3vjw9gHn8a+eAj74Snsj//AMBxKZgfgSByIZTgIr8VwvBcH4wEcgocxAo9gFH6CQ/FHHIbeF1Gf8WIcgYE4EgdhDEbiaJyIY3AFxuI1OBZvw3F4J47HKozD53ECfowT8WuchG35nonHALwM++MUnI8JmIaXYw5OwyJMxLU4HW/EGbgXZ+I+TMJncTa+jMn4Js7Fd3EensT5+HdMwZ/wCryE+yapGIJpOADTcRBmYAJm4nRciCW4CO/CHLwXc/FJXIxHcAl+jnn4Lebjd1iIralnFuyBS3EEFmEM2nAsFuMUXIYzsARTcAVm4UoswivxBizFXXgVPo2r8Rksqx0P2aT22pwyk/OAUo/j5DzwtJwHqqSeP4t98DkMx+dxHP4JJ+ELOBdfxCx8Ca/Dl3E7HsJ78BV8Dl/FI/gafoXV+DW+Lt87h7EjHsHeeBQn45uYgm9hFr6NFnwHi/BdXI3HcTO+h3/E9/Fp/EDqfQ2+jR/i5/gXbKqMV8ZueAJ74McYgX/FaPwEY/E=
*/