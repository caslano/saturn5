/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM)
#define BOOST_FUSION_NVIEW_DISTANCE_IMPL_SEP_23_2009_0328PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<nview_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : result_of::distance<typename First::first_type, typename Last::first_type>
            {
                typedef typename result_of::distance<
                    typename First::first_type, typename Last::first_type
                >::type type;

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
PPug8okuKtxy2ezokvvkI84AYzJm8dy6yosFxq6XEVofDerIHjXiR4IHaT3PK06tcrxZUhZ2Hy52C5OgeAApXck8odmSfjsPmYEqAHQXtAM76hcj39Cv37YBL//y+tRcGWZ5cEOXaU1bfAY2XHcY9bRrCJmS/0B5qhV1K7p+kfiLSXvdIPllh6KoLEVacF9SB7dJD+8IjVTXayliQZr68cSlmXcHXCz3xMa9kn9Lm4AjN4g1rkiBAKwc7bLAxHymg5gxda7upvH9vrZd14xEGvcsRM4/5R8kLN91xAdMBUqvKZpXxCIhycjbK3tPcmmOGJjoT72yg+OTeaDrm8v4xqmk4zbl1bd5ahOrPSo6oSTL3p8pcW9571OitUJpfYf8Vi1jlEqIAI6c/5R8u9dVvDE0LEwhDA76NVZveZku3vQRWgIxb7B2QKCK376LyBuLcK292XNLZBk4a57Be/FcbEtoujDqWUvUnC5xu4eYp6s/Vbph32GN7JJIwBc63tCC0mVy+m6I+Zy0QRK4rlxrdChBro7Ls5uM9HDuFVr2D5CsVeZit5R2tLTtFr9HqvbvkPqWI8VTGHcT3UO63OC1CsJP5Zbyy2ox56OXLYHJanOZQUBMIusnBCZPJ8LQtPexMeHsPLPnW39BU5uWXTUEgz37092C2uOKwqB8/h2riliTKlf7jsDzFR5x74y4vqlWFsoiHeibIO0gnYCQ
*/