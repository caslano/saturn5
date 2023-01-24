/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_20070527_0943)
#define BOOST_FUSION_FOR_EACH_20070527_0943

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/detail/for_each.hpp>
#include <boost/fusion/algorithm/iteration/detail/segmented_for_each.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each
        {
            typedef void type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f)
    {
        detail::for_each(seq, f, typename traits::is_segmented<Sequence>::type());
    }
}}

#endif

/* for_each.hpp
c3PDiNIxWdkMFtpPROtxvkiLVLvvqozWAmBlkP2V7Er1UNmVEv68kLtSKLrywOEU6coHu1KodaVQ7wpwklAxJpOXnp5E5wj8SDQAxIMiWsOy6x4ypod1wnxEwmABdQaSUBy2niJsRbOCraSyPuNQZkVgIQFWhq73pUe38cW64VqRNFy7KpOs1iQ6emQIheR7kiGzCBHnw9xgAY8cXLilvtsJR862eLbq69DShCgMt0/6ufmitAt/qV39cZYouoSLdNOG37IUUohLdAoxLkrvGQVUKzIQAi3Cj2m+wmAc35up3Vpju7Xh7Vbr7SJ5ogU3Aq/8+cpoBzLpuNt2AQ0DC6W6/j4GaJ00xvNRaZ+aj8v3j/CAAjPYYrPp7dVmIo9xA511CRM/Ur0Xw4ot0wgco1W/Ve+wzFpizFoSkiXjlNlC45SF+V1rGZmOhXIhftkMcdBqdI9IhHbcms2vEe2QuxDUfzuZjAQRIJVIBNHacUACrbmBbT/w19v861V4aotawBKqrerDNyBl8+A4KvYA/Zw2TtqfbLjWIK8LxW1OkttMe1fDbehsTBxmzW4cJaAoWJnFmYTaylBug6itjJw5oYOIC/Kag+RUAp3bPHotiXEySYyTq1yniXGmp4VOuRFF46nR9CIyqvZB+2m3OtW3b00iRzVoOpZi6eMi42BwWZGc5uouPVYQ30XawdlkLOzU0cF9UK3m9Emyagja
*/