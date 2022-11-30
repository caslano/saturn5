/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_31122005_1209)
#define BOOST_FUSION_BEGIN_IMPL_31122005_1209

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {
    
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename mpl::begin<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
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
*/