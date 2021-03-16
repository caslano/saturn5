/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOIN_200601222109)
#define FUSION_JOIN_200601222109

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename LhSequence, typename RhSequence>
        struct join
        {
            typedef joint_view<LhSequence, RhSequence> type;
        };
    }

    template<typename LhSequence, typename RhSequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::join<LhSequence const, RhSequence const>::type
    join(LhSequence const& lhs, RhSequence const& rhs)
    {
        return typename result_of::join<LhSequence const, RhSequence const>::type(
            lhs, rhs);
    }
}}

#endif

/* join.hpp
D+K6jGHPQWFffw6Q5xAYeTVAHh+u/H3yRPYcFvZ5eog8R4Q6T6PHnPRnz1Ewl4RVniPkOQbGPH5efrxBNHv+AKNeFz1GnuNCbZ/kvFfrsOcEeY6T5yQYuY+T6+FPqxteYM+fYKK9rXdiniTPKaGWp22nKb7sOS3MMWaW5xR5zoCR1zJlOycO2BTDnv+BGaJZxy1nyHMWjLk+n3zZ8Qh7zoGRpTLLc5Y854VanjPLP3M4TrgAJoOyPp8nz0UwOCs=
*/