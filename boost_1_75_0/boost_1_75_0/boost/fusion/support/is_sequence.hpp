/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEQUENCE_05052005_1002)
#define FUSION_IS_SEQUENCE_05052005_1002

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename T>
        struct is_sequence_impl
        {
            template <typename Sequence>
            struct apply
              : is_convertible<Sequence, fusion::detail::from_sequence_convertible_type>
            {};
        };

        template <>
        struct is_sequence_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_sequence_impl<boost_tuple_tag>;

        template <>
        struct is_sequence_impl<boost_array_tag>;

        template <>
        struct is_sequence_impl<mpl_sequence_tag>;

        template <>
        struct is_sequence_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_sequence
          : mpl::bool_<
                (bool)extension::is_sequence_impl<
                    typename fusion::detail::tag_of<T>::type
                >::template apply<T>::type::value
            >
        {};

        using detail::is_native_fusion_sequence;
    }
}}

#endif

/* is_sequence.hpp
2+2BKqPyGWOUhPMsKcFUIynvPlrdXY1YMTASkl+uMBCSOAE+6O8cWRmrvMDVmKFsVjXay9fDfYrqxTfH7xq1S7OjzCiJ7NRimntjzLafBe5j5nosW6cqnOZ8QWqRT7nl8qBcI0XZVbGZ1Ljr7ZRBOUkZlB9YmOiqWwIbK95awjdWfPEu31jx7jQMyklaPWJQHN9a/V1n9arIl5+auDGmyGfYuzK/ryxW+N1L/LZW8au6US2Y+J1kAb9nUji/pWR+f41X3aimy+9zGn49zfG7fZnM71fJCr9niN95bRV+Vyv8rijykPg9yEDkrY7M78BlnN8WnN/V7vid3EnN76Cdpvh9vFTWMcswftncRWL5CrF8TqUZpyks/1bIWH6GsUxLSq8sZjqm5C7yWbuUdEwWMm0qeJci0ChsbzxgCtvWT+Q97Nl8D3vWPVlbGwpt7bCzOSi/PdPWDrXn2trLn+jt7dpqMbm3q+m7xdOp9i9R6QLvx5EuECVlbMN9WRfwoSlGUmtFF9j0hJXeGQbiq02ToQv8eBe6wLAlXBewTeGbNqV4e94nXYB2WnB14LysDgwjdaCVj6gOfL5H5wqtsgrLgcKtycRymBT1zXsyy+2I5YutFJb/KmAs1yKWA4U3F2Hm5s9Z/iiFWA4U5r/GbX9SvP+5B5bTwHKAlMRwqlPrBbAe3Er6/taMqtL3b77U4bt/iorv1mq+Wyl8DyW+
*/