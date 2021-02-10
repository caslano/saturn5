/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_KEY_05052005_0229)
#define FUSION_VALUE_AT_KEY_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct value_at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : result_of::value_of_data<
                    typename result_of::find<Seq, Key>::type
                >
            {};
        };

        template <>
        struct value_at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template value_at_key<Sequence, Key> {};
        };

        template <>
        struct value_at_key_impl<boost_array_tag>;

        template <>
        struct value_at_key_impl<mpl_sequence_tag>;

        template <>
        struct value_at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, N>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_key_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at_key
            : detail::value_at_key_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};
    }
}}

#endif


/* value_at_key.hpp
a01bgZ/cmod8CxjNyWArmeJ4uoWFcNJFuDieHZ2ez3CRTCbJeDbH6Sck43kI9vV4POStl0xmQTe1JcfkFnJVK0nFmvPlRsyHHyOXi7oVl+umbsEXBEjnvCV6GdoqlKSXruuGstF56A3HLeRZPQhoum7bQymTi1B5Bwi5j89PTiDLIARZywaTc59YrgbgBHoLYxRS7pxMukZzxWS5KfuNdnKpOVJeCRZA77zr9Ug3K7Cnpfa2+NkDJqMvo3SWjZNhgvfYjx5M6Wxy8tfy22hy2vvFQcLlx4VRx8lPQWHZ54wbDtpaSbhbDArhRYiweeQsgO+yG3TVRnDyB2UeivTSV/+BtqCBeQQbGAY+jXpUfe6tCqJsk+aDA97ITbd7kPg3UEsDBAoAAAAIAC1nSlImzcx4/xIAAAQ8AAAWAAkAY3VybC1tYXN0ZXIvbGliL2ZpbGUuY1VUBQABtkgkYNVbfXvbxpH/n59izTy2CJkvkpP2UtFySlNUorNE6kiqri72gwckFiIqAMtiQdFK7e9+M7MvAEhQspw8vTu1jsjFzsvOzM7+ZrDq7P9xPzW2zx79cemfCz/wmyguU/EPPs+qZ7vuZ6b+B1Qf4PdjQjosJ/nsOuxxks+sQSSulvIaP7vuY4I+oG74nw5SfnDx
*/