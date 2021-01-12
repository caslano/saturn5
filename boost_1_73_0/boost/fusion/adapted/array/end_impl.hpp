/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , extent<Seq,rank<Seq>::value-1>::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
T+cxPaSoMN+pU5RO4y0q6XimzE1ydN5pjl8Hm6Mz0v1+wD+tt+j8HA3rOnU9HbGVOzK574527bBWFPFxOqYTVVbRVKh7/9Lu4m68R5jVT/5pOpp3X0aaI//8HqZm7b/8pc4kcQ/1XtbE3QsVQa/wSxl1u9jd4t0m1/BrufOLd/jv0g+eFz3vwaSH5H35DVRHA5C5ROziTuYeXNnGZJr4Z98r/OqHHZ+/TF3rUjmf7FVOqFvv
*/