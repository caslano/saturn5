/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_20061213_2207)
#define FUSION_CONVERT_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/convert_impl.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
///////////////////////////////////////////////////////////////////////////////
// C++03 (non-variadic) implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/cpp03/build_deque.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/deque/detail/build_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque :
            detail::build_deque<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef result_of::as_deque<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef result_of::as_deque<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }
}}

#endif
#endif

/* convert.hpp
ewqUeFjCyRlLiZw/xNd6BsbFQ5wWZqpk/N0hIGPtW5NKFhmaIJD1SnNug3W6jBNI9zf4Ok0EEpdBlRQFcTz0D31O42U47pav1oerNgZd/t/Bam7bTP453fL/HvKgmoIP+q1B/aBx8u2/4wfl6aPF2pDEP+UHyJjWwAfEStAHUdshL6kOMwgtHXC06xQ3qyKOVQRh6UG+5CRxD6rZB6MMmmcJHMYJHDaW9PbCIq+muC5/E+a2X8R5UXUx3K12n+I4ujdb5zgqypicBZLPBjQxVrZiP1d+DmU3rK6ONYg6P6D/7B5E+s85qP+8rw/pP/HAabzdHrV2jMucvV/Da+Sb15Ai1A54Rl4083uaenZ16tmTRmebStcZuUanktT9ppL1RtImOkWNnt2u8nrO2d/HaSdotIlGR77xca5JBGqBrs8bsfgPDBFgKp3JbyxHuWTysSwwe4ibRd2gATnygZbhMIy88kioQYw0EAHaLWd+rV7rw6/F71Cv9TAS7kDcsax98gb2t3iHCwmK4+W6mWFK72gjrzh0CIsNwYosmqCCUF0k5P7jqfaYcDfgmNjhwvhSveh7iPMdEZnbhPH9A0iSHPPX9rtNdZOKQJUiU7U8v6GT3kOvE1HiprBoK1CZhi7n/SXYfanya8pfSKO2v4hkJ0ADdh7LrzxIHe6nQyYd0nlj7Tk69vhLwxviOI0T7MGnsxT2YM+Qaij7NRI4
*/