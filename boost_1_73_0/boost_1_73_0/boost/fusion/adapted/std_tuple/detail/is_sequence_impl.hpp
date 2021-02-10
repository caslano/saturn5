/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
o8yErmfRZbCK6NpbLr15dEPBBXnzm97eu9n8HNpQ8FqT/FDV0gBFTWpbFUqmB87/10p33OiSzlZLP1hE8SqcLhfX5/SSRi9e0c9tybL+akSjQm047/TKffnK/QIL/FcshXmIjWw4w/iBmAzshZc0966mzrHR9XPWQE2l2Moua8KYna7TXh2sb9GCgLJRiWBr1lZ4Mw8W4Sx0PlNlUrSppDfsvNNh/oNj/SQa68eYxvyGnuXwVUAoR3ggxlzU9IwxVbv05Dvr7Xwani1ni2gWzJ0F8JHot/U1BOxQCDSrFWCWt4xdUNkWxXNWjioFC6DQtwgmlQ3qBzKBMMpbJ9OdwhJdlmiRj6WH9a2wtWlrGWJ6Tb8+MvXb618Hnn5zHeca9IAs9vxO1ugx2tD7r494ox10BFjXqkz1zrACAQoW7xn6U5dwTCUTVKKF9ZQb2yqsCV5P9VYgGPsGT+DAviGWziZIcEybJNBsBiZQ8puGz4gnjJFK7mTj0iyz/lNdft6wha6lqVI1ShRDk3J47SgkzqLJxZ20PSUDsYdszCP/anIUSIIq3ACkjVIxBVxOD5zKg40OB6vb5h/x9s10L9KNfOykgthx8XgCADnH0jRAFmnaJ3ffKEu9L/RzvSuf+/IeI8PXt4hyzhvA7Wox
*/