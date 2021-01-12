/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_IF_07172005_0818)
#define FUSION_FILTER_IF_07172005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct filter_if
        {
            typedef filter_view<Sequence, Pred> type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter_if<Sequence const, Pred>::type
    filter_if(Sequence const& seq)
    {
        return filter_view<Sequence const, Pred>(seq);
    }
}}

#endif


/* filter_if.hpp
xrmLcV7Rwkjj9EjKiUBjeBGOygn1m19RNXyWlDzbOFG660h3mkwzZy5q/7zP58MkzKTbyxT6ye2oyKSU33a7xu2eEsGtdO2zYD3d2sZjSJ2655aUyn3lQOwN39u896jSL+wNdo549L651k+eR9ZtqX6Weprd9fSB3h/v3fuuf7tTC3tsvFKqI2dQTUP09MkPd+9ObBj4fY07b2/Nk39CMs8xq/TMXGMXRnw4/7pzkXr3F54c
*/