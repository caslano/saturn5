/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_key_impl;

        template <>
        struct at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply
            {
                typedef
                    decltype(boost::declval<Sequence>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };

            template <typename Sequence, typename Key>
            struct apply<Sequence const, Key>
            {
                typedef
                    decltype(boost::declval<Sequence const>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };
        };
    }
}}

#endif

/* at_key_impl.hpp
eCp82cW9cD0TGxlFQ1BmHyp6fDYQG1Rc+biZ4qiVi0erJDEcBSEkBk7hP/eGkBg/3itJjNQmFP8m0swQK+rBXkRi4IZs1ozQqYwXSoHeR28bM0tZ/6uU+B+lkWyfV6M6sq3v9+10Sc1YIJcO4sILgqBqIutNd7ST/IwPpFlBv7R3HTiJFfe2lGg25nFJtEXa7xuRnOtVtqiVV9kt0outs6y9SO+9210rHXBXxYjlVXatAyMtMhJENR4Mj4Tn4ltF5AqyO4xOK8swmnAahEQ8AUO7O8WD2tiID9QQSWHAYKcI9O0tyJ0yjHeWnYsv8K4rf22tt6W5toptKgssJBZ1QA3UrVkgoYTap77E4Ld4Uko7A1vVtndLcbBr8Sk+fSkmOcveAGxi04cQTsNVn2Wyav6pVlVtlXRRTBQAugXa0s0csEbD9oU2vjmDqJMh3JSkw+bWhieGunqRLTY1zOEsu9YK3Rx/T5wleIWVjGiiZ989aDAzMdhJRPY+4pE1BGxvP034mAeyLgUZFX6SiS1Qd04/hLY4h1npok02Flq37RSPMwU2dqX1NZgB8FYA2S/G7GY3Q4/WgCTsDpKEdVpRErbQqhuLQHnAu2fFEtXhU68DPjmPrddkB0YKeynsB8KXRjbcdaVR3VKlLgy7KOwuP3JsU685YUMpFtIVY82m3FkGNpYk+TZcQjKwsZFMt/81VRohUacCwuLPb6Yi
*/