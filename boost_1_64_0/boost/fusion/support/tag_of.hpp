/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TAG_OF_09232005_0845)
#define FUSION_TAG_OF_09232005_0845

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>
#include <boost/fusion/support/detail/is_mpl_sequence.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/config/no_tr1/utility.hpp>

namespace boost
{
    template <typename T, std::size_t N>
    class array; // forward

    namespace tuples
    {
        struct null_type;

        template <
            class T0, class T1, class T2, class T3, class T4,
            class T5, class T6, class T7, class T8, class T9
        >
        class tuple;

        template <class Head, class Tail>
        struct cons;
    }
}

namespace boost { namespace fusion
{
    struct non_fusion_tag;
    struct mpl_sequence_tag;

    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(fusion_tag)

        template <typename Sequence, typename Active>
        struct tag_of_impl
          : mpl::if_<fusion::detail::is_mpl_sequence<Sequence>,
              mpl::identity<mpl_sequence_tag>,
              mpl::identity<non_fusion_tag> >::type
        {};

        template <typename Sequence>
        struct tag_of_impl<
            Sequence
          , typename boost::enable_if<detail::has_fusion_tag<Sequence> >::type>
        {
            typedef typename Sequence::fusion_tag type;
        };
    }

    namespace traits
    {
        template <typename Sequence, typename Active>
        struct tag_of
            : boost::fusion::detail::tag_of_impl<Sequence, Active>
        {};
    }

    namespace detail
    {
        template<typename T>
        struct tag_of
            : traits::tag_of<typename remove_const<T>::type>
        {};
    }
}}
#endif

/* tag_of.hpp
jhjKXnu0XS22ankb3+J2p5SfjGNzj9v35RCuoLRkY+/1R62d7x3mNMUkbUGGYurdsafrSaqkba7Uzy/Kj/qS8fd/9r+/fulwAO8UB3dqfn81W5f0RVy/mof8ahXbGCYPv/NAV3qykCLMoexkWfLEgecu8Pu88ubd5dcLOjxC/VsX0OS7zmhAdoilMqfp7e76vBZ3m5WDaVeL9Zs5Xf+6MtJcvfuc5mi/6HQr15wG4pRA/q0HtnMyEVejqP730RrqjIR8Lz8r/3y16sZyGOB3clv/e+/rAndHD8D5FCKjznWZ9LOgj1aD71LOPRC/C1gvIoui8vTxBPBdyn1a+ud2UijVmUT6xmA7pEcXWhR7lXUhCrakjjTIxftYUYztk+FOBNq1ituVZRcS9bKy1u6/tDfxJ9ctfSDS1PeuyIG+yD7zU7k2kV2wjspsgefoBu6rHUzfJe6ip6SscNVOYfeoD966WAPv/ozKUNfNWts8duvO08oZEZXPY7f+o/zzlfGNvhDCEz3Y/py85faNvmnSCZoFc5mURq11+0fHL3r25YsXrqxdunDhYsnCttCz4jx6ZY1eWcsbo2w/bOtZZUJmHagicfv4aHNjjHO8Bj7wE9zsUlTapf+Iy5a4atDZtp6iGoYaVvQkjcgrJSDA9Zs3dpcPAUf13w8PyjzCPvn3OcHtEb4TxnT/uT0c9wNp61mzgjsRQ0duLEILyJN+9oz9kBGuK/2gOhad/I+41zZ32vZ/pK2HZeJ17lynQtMPKLgBXCFP+uHHk/Z09drVO/XftIc1byR/aevxRJmaLCHT0hH1Jhle5GCu/6PQo7dMbYRydtb/a5evrPUX0fsQr+ytOEaztdL4EHMjewVdeoX3vC8Y3vYQryKedcwbr07FZbtH03jUuuUPxNtg630yKbbHJa+ZkKWPFFsyrcFdL8LkJLhErYqnQb52Gr/8AOMp6ZRyMZKt8oywtl0c5NY2X9czvRby9E1kzNW6jXfqVMBTZPx2yx9JVFxHmSXI+OxGSIi5PRmTIGnZTJQFzEurFy8/98ra6lpp8SZei3+N8SQTKmbhQcZnj0KONowtD2fExZRF1JF01cNwZURbWepsOfFdWVkEiVzfPm7eOc+9DfVvFjXCOHPNeCbFJnmL7tPyrHouVDCqI68vUq5dLsLN8uFhDJa0SKpTzRjuD+Idsp7nQsvDDOmsKTouWS/fsy9f6YewEbAHBj/J3NYRic2ZdV6GcRxH4WAev6bl8SQ7kbh3S+HqGjAduwOM4ZPoqBHj0PWyYRvawoNjMnBLhQ8T2Soclg7OFTX2aVPHZZeD57FLZF3Ti0P/X1SDPrd4XBHFjbOd12g+XFzOh7eUFxc8SUbMP73iXIOZO62S95Ic7WwA5mXb0/4WYWZivDCMUdvL+KKlmD3qygJ1BReNY/LtVtZVxZwQni8z1a2BwI28d3k73tusjaHgh/9K3kvjnF4t9aDYKNQrpdhS4pcWxtICOYlmb4c1r+UVjJQtOmWv5P8j/5fbup5rO8F4dpqIXv7ZeP8QtTsRz7J2PoXT97RhURjXJbCBKfWgt2wdDGealOCjVXqAtoN+oH63JPJq7MlEK/Oo2BCx9spKRV/h6Dx7/h2tzNlrr7pOLWUuZqZwvhp08xdvbOeD5Tx01HuiA+U97fj2+ORSN7I/V1ozzheCjeOJcLYHHNLyXlaJdYYHQXaub8C6tzvg6EKL7KxdliF2mmQme81dexG/dGXtOZdnPt6veQfeZ3k9bccyluURdq/YnpQug/M55JpCeB0xLEZrYkcOXrvdD9hFemNrAckZB36Io4L4DVFBJa8CJ2F383D/aP91ZZQW+H14paOxDcdD//w=
*/