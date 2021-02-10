/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<single_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : mpl::minus<typename Last::position, typename First::position>
            {
                typedef typename mpl::minus<typename Last::position,
                    typename First::position>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
rEJeNrcf6sm42wJDfgHz+P3c00c1AHELMXWWp7ioMfYpmUPS/CRFUqDlo1ohUaVpROPZunnBgqlgwouLfJRer8MUiAKuYqnbIzaCUAA0qAG2N0UKXLWUMgGjJq/Luy49WcdHuIRgR8uPcximzMXvkMqQK4MeAJMTOR/gNJpTC1BQZnFNswDr5JcglELTqQuLBA7N7Rqd1/FbsPIPEN/YORW7YnMHfgFbKpNdein+QbIdv8Nb/NHfi9Iwlx/qHXqTPnmCXz7BfyUvOt1Z+aT3cWDUDuTYelUgX6q6QA4bCfNSACpVcLaasTyFVav2ONI18MBcm35rUboGiHM9Q0RjOQTtQK0yfIzGN6bi1WykxAuNBb9W6d/h8V2NR5peO6xNnatezAjsP+C3xOlgQoksajQC/AGkkpNpfccnTOe4YLNLDyAFuxDUTrEOw/ZWllnhuOKw1mvnUzsc/vjqp/2Li+H5ZVe/wNOA72833/Fxwq8VqEvxuBuldHYs1vlkY0Bnsf+cjIptddbeeqsifo/LDQGS61X0HYypNsSoG6hBsc3OfPc0pzdiPZ3iT+z+GEbp71XqDfchOggINkaV9pfba0yrxkPNYtQT7t5h98AW3jNSKntjeLL/4/GQ9J7Gprfu2/UWbnvrs7e95e17
*/