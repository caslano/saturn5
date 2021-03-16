/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09242011_1744)
#define BOOST_FUSION_VALUE_AT_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : std::tuple_element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
hVJbWlOKX4Jwp9SWy1cqB0rlQKkcKJUDpXKgVI5rpezvzbys8VRVqZU6n6hUQ311eqnU8F9dqzWnzkjmtrg/pY1CqgDntwLUqpkz2qJsJyjbSShWBjYNrA6sEewdsCNgbtReZ1N7t5b4lpJV7U8T1G4sr2moSl+G43PnzK+U47VyLQe3dhe5kxslXMnNB+fZ4+LjB/Mtu6ZT2w+1/UKxKWDTwerBmsDeATsC5kbtX9vUfp7+QmnULixQVKg9qaw=
*/