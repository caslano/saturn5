/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_31122005_1642)
#define BOOST_FUSION_AT_IMPL_31122005_1642

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template <>
        struct at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<Sequence, N>::type type;
                
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

/* at_impl.hpp
hk6jlhd9F37VP+y7SHPfVe5jv9LrFyYWXbr4IMDmFV0AOKNJ7B93b9+osE2LD/4IoX0gtAf8E8dxSMMQh5RQRwUtX1/5v/qStZt8ybZdYtxh6X43SCsvWXe80XNdsB2bJpVUW7j66UYL6qRzB3V21bcZVAPoTolvbQEHmh8sS2X/QWWYKYnYH+qaxySLshWQ5B+vzjftbx5by3e+qdzy+761Vosp16Db4dTg4xTvqg7eT2B0qJkmPMZSt/f7SuhtJHxFd1bvfRdn9vs85Yr/pd3Rp7jhOmZxiuE6JhtdZuueZ41mf67S3Ox1xkb5qFBHaMU98F5qA0RYEP54fbYBd4AF7Q7Q3CutmttHb8b+PCFCOUg0OvXvQSWP7hnR34sBlV5eHCZQQ5/AvpuKfZehtj7C+q6O953D1HlfV1gN8HPovE8qrEa+ZEWGPkQCOwwxRdGvTNoCSXdcia7JsYfu3CX6atYu0tzp+g3Xf/o2zsAJjQH8QBSaKGfyspQG+SbW0NWezzVZUeA8S7Pd/D7c03raGDfXYGsigBzXuolErRsm5eYC4ymqrMTtBl/w3odQgzATncVcarehcQqEqLnvxVscOGBZFmlrYC/slJzVsvIYnVfEtX6EqnJFN/lZ7rjAcscFljvCE6awKVwkdO8ylc9kpQdaAYrCei6P1/3ZWbOU2Ykc6/2GTer8mWwAUhs5drI2MbD5gP3CLzI5
*/