/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FOR_EACH_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct for_each;
    }

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence& seq, F f);

    template <typename Sequence, typename F>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename enable_if<traits::is_sequence<Sequence> >::type
    for_each(Sequence const& seq, F f);
}}

#endif

/* for_each_fwd.hpp
VrA6M716XLSMI5V1Vo5ZRM8wnTpkSJn6WQlcICdhHlPMbo6ZnY03ejTUC05COrsLSvZRgTZKCzzkl2sdywri2BLYPkorfuOFuZWk6eAx4jJ379J18z+Jh6AZsbkJC8NLu2M9QA2MUDTk3Rko9F5fR5Eur0Fxu3AE3WtGsbERHWSVuCWlJ1hrprEnkxyO7K0GgjWFWzJDyGCnY7qjdnz4Ue9ssHVVW8corQDZtC1mj5GilL9eQjrKYwmLjB/DsvoxncYyMKHSSASkzFFXdU/dyWGErSD3EN82fZCX6IlC07/+J8Ykuo3mMFD7wrMUI70uokLHmfYkXZH4ANdiLij7gijH0ONTbrhIs9ljxHiWZnPooDluLmE2T2LcycWx0j7tJ2M1WDhBjyl7M8ecEc6vLrotUFA8MI6FnqMwd6J3wrjAen+T2St+ZbKzDykiHdutyENFm8KdyLoDaOizLgCGhPLJu7qyx/sLrCKqnItSAgeFKOiY6MBe1FIY/b0p4qZUPJSaqLHwJxJTr3+xZYY+2WIxWKW3OX8Zl+X4lKTxLipjfhOSxfhpoTEdhv0gWmSMyNAyqq+ZMfoDOIF5hr61iFQFiDPdY1IVoFhuB+VCfJ4Ih7xKzQ43PMJ229G3CTCmWdUKNvLyBse6SzOX
*/