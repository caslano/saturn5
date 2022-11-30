/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07202005_0856)
#define FUSION_NEXT_IMPL_07202005_0856

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template <>
        struct next_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename prior_impl<typename first_type::fusion_tag>::
                    template apply<first_type>
                wrapped;
    
                typedef reverse_view_iterator<typename wrapped::type> type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(wrapped::call(i.first));
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
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
*/