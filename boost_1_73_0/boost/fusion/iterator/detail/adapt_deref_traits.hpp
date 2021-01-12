/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_DEREF_TRAITS_05062005_0900)
#define FUSION_ADAPT_DEREF_TRAITS_05062005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_deref_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::deref<typename Iterator::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return *i.first;
            }
        };
    };
}}}

#endif



/* adapt_deref_traits.hpp
z+ff49ZHGT+HHLf53p91xu77Hcdh9yuTfC7rurcnYP+8aV6523labL68wLr5RM/verp1vB5wn7syzftyPs6ybvmw3vb5vGXzS46fcTH968ZvnOvJMdt3tXnR7+971Tz7rPn0cesb66FJ5s3NrznOmx2/RdZ53zTe1jpvXKe2tDlPF9hf7lt3je9/dkZ5X/Zfovktztdzjde08fXD+XeacX/A8Qybp6PNJ1n2y7D79vddD3we
*/