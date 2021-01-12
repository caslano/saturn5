/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_07212005_1230)
#define FUSION_REVERSE_07212005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/reverse_view/reverse_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct reverse
        {
            typedef reverse_view<Sequence> type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , reverse_view<Sequence const>
        >::type
    reverse(Sequence const& view)
    {
        return reverse_view<Sequence const>(view);
    }
}}

#endif


/* reverse.hpp
Y1yDT+T85k85vzHR32k047dowXtoxUcYj/oG4oJ50BULohv6ozsGoicGYS4shj8y/KqoT2dtrINtsC62wyhMx4Y4GBvhVGyMczAeF2BTXIrNcRdG4wlshWel+wK2we+wLV7F9mhhPcdgKHbAcIzDNtgZ38J4OQ5z7SxtDbFM5XyuKJFPzueqyXb5BgZhbSyHTTACm8r22BJbYjS+ha0wEVtjV+nuJd1PMB6fSrfVRDd6ot7d
*/