/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_09232005_1454)
#define FUSION_HAS_KEY_09232005_1454

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    struct void_;

    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : mpl::not_<
                    typename result_of::equal_to<
                        typename result_of::find<Seq, Key>::type
                      , typename result_of::end<Seq>::type
                    >::type
                >::type
            {};
        };

        template <>
        struct has_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template has_key<Sequence, Key> {};
        };

        template <>
        struct has_key_impl<boost_array_tag>;

        template <>
        struct has_key_impl<mpl_sequence_tag>;

        template <>
        struct has_key_impl<std_pair_tag>;
    }
    
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct has_key 
            : extension::has_key_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence, Key>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const&)
    {
        typedef typename result_of::has_key<Sequence, Key>::type result;
        return result();
    }
}}

#endif


/* has_key.hpp
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
*/