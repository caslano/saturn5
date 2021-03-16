/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEGMENTED_03202006_0015)
#define FUSION_IS_SEGMENTED_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion 
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template <>
        struct is_segmented_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_segmented {};
        };

        template <>
        struct is_segmented_impl<iterator_range_tag>;
    }

    namespace traits
    {
        template <typename Sequence>
        struct is_segmented
          : mpl::bool_<
                (bool)extension::is_segmented_impl<typename traits::tag_of<Sequence>::type>::
                    template apply<Sequence>::type::value
            >
        {
        };
    }
}}

#endif

/* is_segmented.hpp
xvWGcRpr0PjeME5jTf1KDh8V61dyTYEudg2jNNYkjN914jTWxA+KeciNHw+bmdDOcbZudkLrxum62fFi46fweMkj+QntkBihkSKhDRJjNFIknHSJMRopEhoiMUYjRbxCo7+9iFdpTJFwptWJ0liD7qgaxmmsQXdWDeM01gSVU/f3N0GQ+vlhAOb3PAECKbQAkc9HpyZKc3QyxYT3C/epwtwkpFBpJIVehnGS9wtcLyl45SLKnKI6ao7XuewQ+d8=
*/