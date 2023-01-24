/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<nview_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
63zVBnlfGun60FwdNR51DfldvZDYasQ0Xdv13jhrt1lADeBGfpYVDqa99OnwWoSvIFJG5tL3a33agUAnFt1G9KuYK5cjlLNU3dsgT8YzU5hxoJb5aTh07SCcup0QR9SskeJ5x2hmbXP9bYBGCG8D9nem7gX4qWSJ7ijDKQMFybMrT7Kh7EXDlEcGAi2VzGEl5lXINN6O9zZ3rzLjPLmPU/ppFtWnu4sGpTrpkScdjqOcUjcZZzva8m9jh56hTtXJhctYFVrHnXusDYqDikJT4/s/Krqm/vE1X7JVo1eV1CSgCYCdXau+r+HR7WXPkSisVW443F/A+qDqS66QZIk1xGPy1jKqnaDjNilByo/hR5vDECxIOKKuTZDdC+PI/yUKE97ts7lduQ4OMYAwK6AziXpTjha3jDvJ0N5Gc1Vj57ciUAljUBq1DnQF8nm/z+JS93O8h2TzkzN9eQ50Y6l9YWHuyv5iDUyulbTPfRl2QmD+StYM4ytI7FcDNhYIbO7j952lXn6Sq6BhOoAzs65xF2bdcGTJlyjmTdXIgBMtQjEhdvD0/q5gssZSE7e4kWgHfMbc/jdyCqoBO9Mz7ILtSvBE6tOaykNtsbzikLt5vBHSni33hYbP+qO2/ZHWq2mW2d/Xge9y+IIUeDHws3OfjX6K3XosriOwjG5XnmIImBKhH1Er4T5pVjAAcBG+wXDLOnD6OIUnlZXi6ao2
*/