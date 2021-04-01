/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_VIEW_03202006_0015)
#define FUSION_IS_VIEW_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl
        {
            template <typename T>
            struct apply
            {
                typedef typename T::is_view type;
            };
        };

        template <>
        struct is_view_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_view_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_view {};
        };

        template <>
        struct is_view_impl<boost_tuple_tag>;

        template <>
        struct is_view_impl<boost_array_tag>;

        template <>
        struct is_view_impl<mpl_sequence_tag>;

        template <>
        struct is_view_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_view :
            mpl::bool_<
                (bool)extension::is_view_impl<typename fusion::detail::tag_of<T>::type>::
                    template apply<T>::type::value
            >
        {};
    }
}}

#endif

/* is_view.hpp
632MwyvqHZhbzpWUDVDR7gofq76YNqxchC9/Px0bDExlMUrJj1V6j8XifDxGFPUh7D8IJsinsIpQWj3hV6PphxKqTOOKQBFz/8ObC6A3zmJs6hDKd3hkjL3p7e8kvkB2VGQ31nFTWoWNckILBOXkDDX672U+sTe0IxfOj/wEo3ifjwtz+aEiGHMjJ9s57e6d79CA2KnWvCF/VhqNlPlHJ98CAnEQokWQE8W8yGzuqzZTKsyt4LdTig53fzRed1iXO6Xa4xnHdzPbSSFmAJa9uqaGbxuDo1rxV+6USv1wkBdwUOEa/9fSu6uau0ZymaF7W9AlmQfr0p7GnbhlmS4hDHsZtwt+6DqaVVg8GbGrvlS32iZH3+FSzN2QLy0UKvh7GG2nCP9qw8ap0n/PMR6iUqbsCqNmNvgzaX2UYESO++wFI2VvIx5eOWjiueOTSv4nr4IFol4hg96KYGi6Oq8jyXnPG2gVy/Jn55pI1LjbvixvPjCzsIhMyubjpPY4R5rluOeookmoXKt31mKqcxN8fc6167rRY6Ycqk3Y5FtCpr3E2ReVSkmWgid6GA==
*/