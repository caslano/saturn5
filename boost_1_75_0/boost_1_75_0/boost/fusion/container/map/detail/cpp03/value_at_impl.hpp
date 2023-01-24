/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::storage_type::types, N>::type type;
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_VALUE_AT_IMPL_HPP

/* value_at_impl.hpp
taoscekwVdjO/dQ3jW0pr4x3P/VtVtlpf7yJoVcmbjx/xUGXbEMWtdKl/KAtoNwyK97FC6cUyFLP6csapa2IrMNMlUtIf2OzJ8xGlqdSgQuhs2ZwXj6ZxB+cxrTSMPF/BqHLaFjE6rZVJzRjgBWTMS0e8iEzpDGtdXEAGZnEy05/H0ao6Dq988p+6F+Sh/1jhxvW0vORLWRW1LGvAkaq8hke3SBGh0hZTuatydBSiMEuUW+tNbTeyhqMEWuF5iAsezgY0r6XnRsFThR0rtEBm7wYCHrysKMbK7IJxDkNF1abMG865S0SN3kC4X9tegpaHba7S+u1Zpu8CyxFxDor8hzGusqsrIFLogiqeUycocu5KjjTbjGte8QzVeIZ3k07Ooj5tY/XKyLWy8fl7mjB5rAneoedZfHR1NwTeFa+jOhtatm0eNoMM4SoejeDePjmyc/fHfj521kOkIPR0ZcJhdYibS726bZZT/2YFXhUa2wLaQ0GYj71k/vI5ihBmJsfwROzyn5wlvnRiK5t/5stwLTCK2lSOsDI8UUqq7KG6PEmmOatnLUQqCnlWxIxB7XO88UfZxlcXfDHcvrht4G2Z7TIKdGyWNAKhcrgXDIhPHgExOWJH8PhR6744YMfPvFjKDp4FT+y4UeG+HFjPjkBHOzJJwcYgzM8Z8J0r7JDjXrrD8T0BmQbzFpoTFYDTdZdORLTxaZvaWy/CuTf
*/