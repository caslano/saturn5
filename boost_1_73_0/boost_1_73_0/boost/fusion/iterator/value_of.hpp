/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_05052005_1126)
#define FUSION_VALUE_OF_05052005_1126

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct value_of_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template value_of<Iterator> {};
        };

        template <>
        struct value_of_impl<boost_array_iterator_tag>;

        template <>
        struct value_of_impl<mpl_iterator_tag>;

        template <>
        struct value_of_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct value_of
            : extension::value_of_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }
}}

#endif

/* value_of.hpp
K4MyNoE6bJ/Z4eStgy2a/2Dvdd9PYgWTyLVldrEwm+1E2ORQe2ZADnjAVJnb86KurP0yziwoUcRzAc9sn/Km7F4PrNuXmIsw9j3i/yeDIN6bwKJwr+V2ZkjpztucTOBaPDp/6uhQ5wPmOKd50Wl02+e/N5zfq1b8EhPOEimaF7fPMvuUJj9Lca3ZoeJI7iNFEyz6hJsIYNi/aTigH3vQU61e7zi/P7taNHLMIMAkBKdWMYSuFOsCgL0QDDdIpejcvuTKUHpmN1QljmxAyGeFhKz+bEJW1yAkvP4v0nJ++Rm1tN7mckYAFO0xg9IooQjlnB769EpkCdnl8t1dPV05HWjoj7Wu9lGXmE1pqhq7Q0ladF74ZYaXZovoncb4xp/+hVOickXyCeu4D6c2oFZuG5m2pGP8YCC/KiWThcq5Myyj1IApTWrEiZQl1RSTM43dkUsgU/tA4Fe8bfDsqoQc4t9PCsKVle7Gjx+Jg6/eQRkza/iDledGhoHaG6mYVC/cBMHcMxT8fZmxvRaifWTQXgNxIUzDE3Gky/qwWm9yvkl2DMWEyWXWLaIr/GNo6xPYwjJtzplsnDegAC5NUjKMQLmD4lomh1XQdEuYD3mJemZOUpBLWUDlEg7zE9W7Eq9eiRd48NEU4YjRTC/A
*/