/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_BEGIN_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template<>
        struct begin_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, 0> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
C8DOJHSlP9LYc3J8pq2p6l0I64lNg8ilkbF/InnXoUIuqHoQ7+75gaBV6x3FuA9L1YsQbBg9m1CpGXTcca+fuFGEs2ixTFEArJjjmsl4ti9kYl/l2bXlsHV7zO2bKLTXQbMArTNiXtLv09Gns97+wYcjkNZMkKxk02BCvRGrUR2o7EZuy/VczaEs1B7KBmDdrqcLPIpdz2MG8s1IwHTPYIUenP1dF/5p4Pq4RB1ue7DEJDB18VoR/HSjmzycbFXMhZMup3Q9FmCdAUtwSz8AEo/2D8SEEmtgMkY+UYOgwCizA98hsbC8ZHtXGNz7r0/dw7P82uZfZmBqMQS1bL3KrgLOQgBTNPqcAgBcfZqqEEswWXXLxv/46fD8QO1N3SczL4ZNk4u2Yh2C+seVFqA2cGM0IFMUDv7RO35/dJwoYgEDjROwwCL3dw7/pFQkGpVnGvXo5PTg6Py9viaT7v4U1m88TMXyqId7Ym7a1Em69gL7pqDq0FLGB+7QrKXb3a8nvf3e+7Pz00975yne8QNYMXwIBIvllLTeP9Y0pGzdZbh6E06BxMV3HNgEFimas0UVQjA+/3JwqPF7DpSsO0GD/Tdjeu9/9g67H0kXyelDQJ+zLVqsI34PK2NikV6bWOEN+hklYvzx5PxX5GtK
*/