/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<po_array_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                add_reference<
                    typename remove_extent<typename It::seq_type>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return (*it.seq)[It::index::value];
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
Favu2ssrUfKpXlhTA8eclnX3PH1BuaeF5yXR3fu3T3ef2F7d/dz/Nd1dJbZllJO3LX9k1PePM9i8/0kGb3z8aQZvTPCZUef/lMFxL3A80ByjvD83avxuacu7U606w1iVYAsEWyQYlHfGih2LtaTGx9SPxtfqw4bJNpe9b/hq/TkuFd3JIRX9BsesGS15bJ+9j92N3a2jjwqOHvQiNe+S5kklo5tLnOMbInzH17B81Se6PS5penKATynXglWUdEw=
*/