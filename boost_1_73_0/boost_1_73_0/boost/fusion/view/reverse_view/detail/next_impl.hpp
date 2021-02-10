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
Cg7D6eX1ePJPCJtcJDkJ2aoKTK6qIoWc3XDQPOHixssombagMmRH4akwFgVWVijZR90cLNdrQzJIPSuMAnbDRMGWqIhZyK0tzasoSipdoPVRqhITJTv3+7ldN55coxFrtgVVWrAKKsNDIMoQ1ioVGf1iQHCxrJaFMHm4twZVyTRSGgwvCpKFfIIbbzaHeR2ekMigRIuFpR+jpCFVm1ytW4QYR5KSVVqiIowDEqUKwxxCJVOuHbHzfKeijqkL8IOp2dubgpJoDBwN5jCeH8GSGWFC+DhenE+vFvBxMJsNJotrmL6FweSahL0bT84w9QKVaeBfSs0NKtcg1mUheFrrfLorCoLnQiZFlXI4ouzFhtuq7OdHQRA9kQ7yayqLLWToyLISRWow7UKusO62Msm1kqoyINmaStKo4oabp3IyQveylGcwvJpdzEbzeDC/ngzPg93y+eDDKJ6MFmO84/EkPt+H47XkVuAdCdnP3wTPucTyvM139vdtlnT5APVgdjmInZ5DDqZLFpGau1xx/OH9/IC0tuPgu8XVUnY5mw5H83lLValVguXUZtnlHlOfMsso8ftFg2RZeylXxory1hoz+S3GHM/CrSWrudZKt1cJL1oLrgbXfK30ljainoOfghkLDZGDtxrIlvwVuCzv
*/