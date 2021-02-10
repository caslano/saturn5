/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_31122005_1621)
#define BOOST_FUSION_VALUE_AT_IMPL_31122005_1621

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply : mpl::at<Sequence, N> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
ENH7YhMvnl6d7eXWf1BLAwQKAAAACAAtZ0pSgzobo6kEAADGCgAAOgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVVBLRUVQX0lOVEVSVkFMX01TLjNVVAUAAbZIJGCtVttu4zYQfddXDNyXONDKuQDpXtJF3cTbCHFsw1Y2DWBAoKVRxC4lCiRlx2367x1ScpxrNwVWgSOZ4pwzHJ4zdDDvwO4Pu7zAwsF3r9h9YrrovgmaKPknJublgDi+g+aPAud0fwNVD7ZRd3EX3hR1BzsuKm65ju1zHL+Bbm6TtP96Nnge20caaSLb+BNZrRW/yQ3snHRh/8OH9/AODvb23/twykqOAmYGywWqGx+OUzfya85ubwONn31AA0wEjwCjnGvQMjMrphDoWfAES40pMA0p6kTxBX3hJZgcIeMC4WQ8uQ5Hv/uwynmStzhrWYPOZS1SyNkSQWGCfNnAVEwZkBkhEH7KtSHM2nBZBkSPYFAVuoWxSTChJbAl44ItiI4ZyI2p9MdeL6mVoJX0UpnoXrIpRZCb4smqrimbgq1BVgaMhFqjD3a+D4VMeWbvVCIarOqF4Dr3t2kRYZn2pAKNQrRwFMpRN0tAmLXV8u1MqCh7buxNy1JbtlUui0cT
*/