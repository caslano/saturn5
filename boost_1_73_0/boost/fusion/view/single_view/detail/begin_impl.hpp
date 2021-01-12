/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305)
#define BOOST_FUSION_SINGLE_VIEW_BEGIN_IMPL_05052005_0305

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct single_view_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef single_view_iterator<Sequence, mpl::int_<0> > type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
UXXfb3+HQR9RyGKXjNJ9B77/Tu/62e8HxPdFqzMedlDCarSV53cFwU7xcg7571a+vhzEUePcCDnQu+/oUG2zTEPnLM0R18boaJa32LfPd7sZweU1nKCFGg26/vs++p43uVVXZF60ZTr4foK71ieeBwimwLOjuQNkudtcnxgOFO7JzZ7mPXez5fVv0EHvSs2+H3Dfe33t6/WlO9mzGVRmSIw5pA63uuXgt+rhXs272Cacm/wa
*/