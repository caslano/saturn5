/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1340)
#define FUSION_CONVERT_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/convert_impl.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map
        {
            typedef typename
                detail::as_map<
                    result_of::size<Sequence>::value
                  , is_base_of<
                        associative_tag
                      , typename traits::category_of<Sequence>::type>::value
                >
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef typename result_of::as_map<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef typename result_of::as_map<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
ZXJgZk7KUF/ZxcykVLyrVIqEWkDBfgeds+KRo/ALgP97B7xwgOiqu+ffzrK35I8y+uEfC38y4U+yu9/fzvJziZckZmP0UMN1cB+44a01krINKrYrJP3HSLrRoFBb2/StC5M8hvvM43AnmkBJYggzDH/JP0HKCD0ljcXs90D09Xp0Ers82wTRPYwmfIYr4w8hCYai5PcuOAjA7Cr93Uq0PP5YSD/8Q+HP5aWnWxd1ouoLtKpcxviHY/hkh9t+GnpO409sME+rSuGcwyDnizCuyudZyowCZN+t96fCn2T40xH+JGT2W1/UZSXQM40diWHSFq9Rja3oBhXtBgPIYKdS8m5EamMWtKeMztWqHBz9O0RfzmCMMFwvfwPx53L8cMNt87Zocx946YRfBFKbXgRSyeAgHb90E8iqROzIKv/N5KLt9Z5AlH0aJVsBvojbvCy747LUTMtyv5yI5fJHFc/IA/DnRvhzcelpq7O8DFk80bgscUOWK/MUnKGXanpqNqbKxfkTpCYYqTdiqlyfOyD1d6NmD6bKJQrexoI7KRWWKCbKVQruE4NL9MQ0HC5cqLMg5QU9JQlTUO10MqRMNZqjK6lcrvdA6l0iVS7Xn+WY1MkfL/Lg5MCfS8VydZaPR2ZPzEUWJCRHF4iJ0FduJ7wCG+3lYXtytUZD6p+iuFhubmUWrNaen/gTxf8rxP9k8T+m3ydFtBhZsJdLgq3v
*/