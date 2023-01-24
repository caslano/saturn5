/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type 
                call(Sequence& seq)
                {
                    return seq.val;
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
0246UWf9l3xYo8rPq/vbXfwNcBhoA27UGtRvka9UfDTrT3jvRDG9bHZxOX+5fOOz5askxXr48uxcLf+glT5tola2dtGJL9LtxT8YL/KhUUbt75rOUxHOt7dxU3yFPsUDqpWhxc7u2fnjTJCRatIbmsP4jTadk1s6kYX8jTnpjzV5KXgQy+X8dWlfW3l26Jf6Ff9+k474pPtL/nhSBWmUrtujl/0dlBOcg8pjl36uVpSyBjii/P31h2+wS99P0nXN4eUO6cySXRiSHsWnrcLZyFO+JX0K+nYOKrJtuD5T6H5QF6T+UQRV1C39f5vOYy4fsvVRHxpkl37u0m+gr4yPIEK1HW6TFTv3d0+WutYqXdrfJYxv6tM+Yt+oRuIbj+mWl9KUeX0aVNgSVCDwd9t0W+73t5G39N33F2+4StaZCtGkfIKRU/g0YPrQtpPizlaeXpXZc04+0a2rULNi00+DD5vT/cC+4mUM6eZj30bZFDwI8Dlbusn4KVX6nDU7L2OKLUrF6dST2yilTxvdwTG9AbTPlt4wKEeirSKLpx/fQpf2rle8yt2zftmils42npAIZk1/06cnny/3FyTAogjllu6psRDX/Ev1Bu9vCXKNXbhCWWqvc+TKkNbFWpEnaZPfyJsqs+flX6dkpTgv3IQ9jEcyXhQMwRyug4LIo9axZOdvSk9cpXNIvnhNVoX92GQ/XLPmdvby88G/7Fm+
*/