/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09222005_1104)
#define FUSION_CONVERT_IMPL_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
nQylv4OG9QhPeiwLii/iko+44KDnb/aWCZL5iuST6l3gWFeLymBXHvMMIj5iRl6aqy4zm5wrxhHbZS7NRq9RSR6JAQB7mclMBlFH4YjIN9iWLUe65Dxb6TxGm9MlOQaJtB2vrjGNtQYp93GXLwFZ8yAGJiUEmQa+HbALyrr/kHyDEoIxOT7kwqwDItwmXEvugR3fmUCRdmHx0s/ay+kcmjv38+gl+tlHCL0dawMRenK2fA1Sqrk2oJseCYgvEH82pgF+oOVsYgcyDp4kFAhBkRiHT1Q6V3DiCxTmY5dGfOVYfKtscGE++SZIL18jtgOLQzZghnPpkWzKfnw0W/4eky5my2kwi9wjzCfVSN6CfRyf770btkg9XY33j0pErrWm3MJIcU4S+P2xnaNRBFuOb0COb2FCodO3sD3KDC7fEJtzaVZ7Z8WQ9s7URRfn2LPOwiZLzFz6SQ6kPB6FPibD2by6fNHaywR42Q9fDmF/VwMaZzSJxgbcRQVHAc8AijUrmejwLvrO8Fizetw+v6XDTTxcqyuDL8HkDE2HG5Yq3qXq75LFu2Tt3Sd4sh4ovux3VcshTlyvvLPujZAjn0bH4RNMuE75ilJTi9iuz7xIkVOT9cipyZhE900YBZwgv2Xi0eHfJkkWs5rtVQpYmxTFmTyRNStdbnKIbrEwmbFzxjUPKZ1a/666ZKtLlDPmW2erl6HFkTW/GBK3NCSO
*/