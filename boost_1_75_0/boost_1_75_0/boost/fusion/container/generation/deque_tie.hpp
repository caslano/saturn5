/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_TIE_01272013_1401)
#define FUSION_DEQUE_TIE_01272013_1401

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/deque.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/generation/detail/pp_deque_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 variadic interface
///////////////////////////////////////////////////////////////////////////////

#include <boost/fusion/support/detail/as_fusion_element.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename ...T>
        struct deque_tie
        {
            typedef deque<T&...> type;
        };
    }

    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T&...>
    deque_tie(T&... arg)
    {
        return deque<T&...>(arg...);
    }
 }}

#endif
#endif


/* deque_tie.hpp
3/HwMA+vgxZ28x/beLiJymw4QrIavKaVPHwNctmU3erLPMLNi5VSsScpmMFjp/Hwfh7eA6VodVd/jTlH8HoyeA4b/32LaGge5ZtNwWNfU/LDPGypVziecki8gjMwNfjGUW1fRza0w72ciAXnemtSB6SSoHvC0I3WtS43S/5G69BWHdBPgjp+rVtv1swks1RlyFRuV68x9683pQgPrP2+R2JgC9068l6DdeQEjl1MYY2gdeQbEFkfnqsO/Qk4RxXJy0A2zdEi34WCjtvnw8+QwKbmMrGn0byneZb1WAS+C4K6ijX1Fh1d8F1TOlrxMe/oszhDC4WdDmCpkaDRk5oxsaUfmzVjYsvFN5vRxR+bG3cFK0zqhD1B4sd4IJVsg7U2uIK9aX8k2SNOFB+d9iPsbDsYabD3jzJYttFcSoXDy84kDV6IkghOYO2uUevszntWgDjdCpR//Mhs8M2YJ4HuMkNuR8KtTS7f2b/FEjdvyE33JaoTHj7jBe35tSGUD4TIJoApWtQ3K9RNE7e+srfY4o/w+goT9gaJLEEeFo8hCoxChB1Na9o2bg5412+RktEccK/32ZVyTw2ZA/6aQODCYiJ/gantLGWbnzngUWVkDvijJG4k94ZPUJgPtE5sfXlcPMY5BnCDeDbXkKlUd68Xo4wWZBd9aNatfVrmbUB18HtYZO0aMtU7rRevcfsGrLGLLRlh37HOsp7qzrfR
*/