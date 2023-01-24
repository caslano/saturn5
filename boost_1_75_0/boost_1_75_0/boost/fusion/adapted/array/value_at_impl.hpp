/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<po_array_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : remove_extent<Seq>
        {};
    };
}}}

#endif

/* value_at_impl.hpp
DgZh2t1t7vONeaFYHfAAzQvF0FKI7nl+EYTQdqr5EiBwOJKQk0XOTtKomnxiSJCoHXtArNiEscIsRktYREvkkNXET/EkiHBDxVi+H5dG6NICpwxKtykeoVP0Cfvho3+DSuPX+gHCuQ+eZIIkjcaiVLoWPBOwN/RbWPpWnP41dKP6yUM8MXZqyb2wbduA2/80orboKhD41JNwJARLNhDSz5LQto8eCKiZdY7KfRYO5LZNfa6JRLQ9nmrdaNFrTT93GHNgJE/TwOXwIkMOE95gJU+4P46mwgZ9shRgW+ADGCaiF/hEJJsnIvYVepSxfxQVBlbuW10c4DeLoDL/fZBoVeLAPQ9MRZmAQNJ+PiJkbUL+MuWAS0n11+ZY3jmuOKqFAAhjck8am+BXwUaxPIjqjnJ+TIKl6Xg33iuwCAn/DLbjaUWDCqSSnRHUOm1GC7ZZzCNof6x5qoPdiwn8T3ei8FkstV2tue3azG33PG+7LNF2iABArEDNd9zCmy8T3NNg2yXxfr491q/tHOuh5VAjun3z1WLzUQ7Udqt5+yfHntbV5SEnX7yLSmIwYkdyp0LgcFd53DTFXF4YT5q2eaCo1o+JxkXHe/C46wvjLSKqKEH2bNFkrTo/7RLZ3Vq6xT2Ug5hwQfnqRk1zKHVyGsLS5LkTMsrId26zxDHCMss+xgBHSV2R3QwE11MMAXFpz77PSKWvxVFpsC4Jzc6O
*/