/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_begin_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_begin( seq )
    //{
    //    return make_segmented_iterator( segmented_begin_impl( seq, nil_ ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_begin
    {
        typedef
            segmented_iterator<
                typename segmented_begin_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq)
        {
            return type(
                segmented_begin_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_begin.hpp
2E9vIi0e07R6Q2vwfWyHpjUbWX3XNnE9QbPzspyrny8vYks0DWH5Iu0e78Sp19PyunHqNdCmbvf1O3EqswWR+cYa2/W1oOUM3P4b2DhdSV32BRtHd4iGzIkbDsLSuNFnbZzeDRq4W+zqxlFbWJD3EXPMcFZFURq6/jXb4Wz24YdpeZ/6CI2hB0t3wBOYh+f68GF0ru9ebRE9v7ld62bcI3v9Emy0juW5nLnQTqgtL4uCKM3cbnmQy3SAvNvCOHvadUNDwfT0bDI9fSw4OjsNCgonH2poe/fV4zR4CJ8tfBzCzd38aeCbmZ4tpqPZpODQijMNzwMIDw7pWr/6RFlWHSQh8etx/rJaTpM/6o7w70dJfoTpgmv5i0S+mHp0nf42KWRJJYuIMDbUyFyxZSKjoD/JpmPFMWeL0BePgHQZKq5VDuK+PixxSJ3GNAx9A7cw0sYdF1d7eKmCc7yNU6kPELMwamMw96aqVwdmqaXLz8dsDAxLrPOnbLp4Nyu/R7yjE6feDXFfHIBbWqnPlYjb3tmJk9lytD5k6HoCZ8drxzPGJfOMEYdxVZQBRPuFxM1gOU33FH+61Lo/5yWvsihX6IeCjwloXdW+ckTtgyc+bOagd4vYTZ3cYRvC6cLI5dxHm3MTf3+34HkQQHGPn1vatHQB+wFL7F8rx6tKJ2Y6a8ZD5zZWFR/uc2LCF7M0TGEKilODD3zPMEc0xm5WdVww+Q+laZwmTuCLKHLOsiyqVO+/bmJzlpRQTlgFAixt1Ok54IyJr1gRuGXppbHAC5/QcG1jZU6ybGIMMuAhZ0zfKxLX50wkr4Q3cU7D5Kejwh1BX8gWX+KEmetFjrDFn5/vrcNn5UYg6iMYf4zwBaz0cifkWWjwodF9O27s11u8XMQfDcJUBPUWjnR2dXWMoau0bTKHe0lUcbGv3eythGb8uZ6yh/jl2l7QQcNWA5LXCduPUtlptNa00ivKJMqu2aZQrWnoz/vsYXJvEpZp4IWeNBNQO+7r0D4aY5yb9SiZnzquW1Wx3jLrCKfs7qrfE1+LJHZjqDno/vbL74T9nKyLXuNzwr0AkGi30BTQN22UD+I5m/A7rMhjr/Bit+YXdpp13DMwUkZu7We7bfJW0LV4mZXQjxWbKNX0dxJ7/AVYr648v9av92cb4KwQL+QJ+l+APvECSZf1ry8o5Pp8Vq6n00lUwjamXryU7eRLm3XV8bxjRx3vYfX6+OLm2fSMM3NsWtoWiDX4jFqDp3nN+4Lm3zPTMzUI5+E/wc/1RyRS3To0Kdb7PboG2jj0YDLuuUc7cJtg4b5q5PEYExg45GIqTJje6tVU7+su1xhxE7nZt2Vp3J6dgEM/qGMz4eHu/eT5QTi078Pc3YCjO4e279X5Dkxbzp5xiYmCMjjq5E1kH2qb/tIujBSE73d9ieGZN31/0S0AathE30vVaTAO70fx7vkGgMU1leY/eSmhQRHmWnxDpHXmTjlL6HWxyLtrl6Bt9mXUIbkd6CP9Fjci9NU1uOzpG2VfQDrNP6VtLglddCoV+wfb8vY3MTGk48kzuMRNEJwcxWKQasziTRUGdp3g3qXeyGznqzeTGHGuqovRtPFbGDRZT4x5oWgwPOgcYvSvW0kMyV0pY1YpXyyJMcPWmv4gF839kFeJu5nCq7JrToAq1w+ynx4fMWao+gXAzGdjjeSuus9wN255eYngXteJ6/fgBofk6r3FSBvX7yz3YzaOlot7bxuny6UxcsZxroO60a6Ce/AzFq6exHDOvGrT+5tSCObN22Fi+u2yUNbETorTsrTu7x01hq4azc0xXZAwHtH1BuBlHcg3G4SVPRi/2biNM14L3+dVEocrl04pQ/I=
*/