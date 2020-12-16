/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_TAG_OF_27122005_1030)
#define FUSION_SEQUENCE_TAG_OF_27122005_1030

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

#include <cstddef>

namespace boost 
{ 
    template<typename T, std::size_t N>
    class array;
}

namespace boost { namespace fusion 
{
    struct boost_array_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template<typename T, std::size_t N>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<boost::array<T,N>, void >
#else
        struct tag_of<boost::array<T,N> >
#endif
        {
            typedef boost_array_tag type;
        };
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template<typename T, std::size_t N>
    struct sequence_tag<array<T,N> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template<typename T, std::size_t N>
    struct sequence_tag<array<T,N> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
LNL5s/5ynT95AtkjT9R8yFeSO8hryaXe91fCrJ9KLpM93Z8XhRdrvuRp5BT5bM2XvJLcQl5CzpN3PnaX9e7S+nrJT9kR7lFOCjuPkcPd5PpRLkl/aeWycItydg/JR9lxZL+UC1JfUC4KdyqXhEvKnnBZ2Xdk/X6u+Ul9g3KZ+SqnhdPKGeEW5aywq+wKtyp7woFyUbhDOSXrFVbHE+5WzggnfqHjCTcK45D8m5VTwjllR9hXTnP9lJPCoXLgyHopF4TNFs1fuEHZl3xSyoFwszAOmW9OuSz1vnKqjzyvqu13kfkrO8KJxzVf4UbllHBWOS3cppxJyPyUs8Ll6vnCzhNkR/JNKaelvkU53FWuz2p7uX6DanvhTuWkcLdyVji5lewKNyt7wjlln/0rB+xfucD+q+fLeiZLer5wWjkQzipnZL1albPCHVWulftJ2RU2T5I94aSyL+uVVnalv1y1vXBQbS/cpRwIO7/U+XG/lQMZL6Nc5P4rJ2V8TznkeMoZR+annBXuUnb6yPx+pf0JNyoXOb5yieMrl4U9ZdeR8ZU94U5hHHI9lZVD6d95SvsTTik70j6jnBTOKaeE88pZYV85s4fkU+1fuEM5Le3DanvhEhkJyPO+Wr+75PtrzUfqm5VTwjnltHCrsif71Q7m+1lZH2VHuKvav3C3ckq4R9mVfBNP63hS36ScEc4pJ/l8Vs5KfYeyy/GVPY6n7As3PEMOhBuVC8JpZV/ya1EuSn1r9Xyp71AOpb6sXBJOdpPLwi3Kable88oF7r9yUThQLgkXq/0JdwnjkP7Kyi5fj54lp/g8Uy4Kp5VD4ayyJ+d7yiVZ/zZll69Pyr5wqBwIdyuHfD1/jpzh8085K5xS9mW8ZmWXz0PlgtTnlQNh/7mD/yfeL797/J8cZb1e3/zv2/2Xpb5AD+l69Lx42HacKG/PDTtw4w585Q6f75d/Q/pPG/kcvjdwGHm9+VDl/ow38v4VTitnhbPKrrCr7NdW2FcOhIMq71LhgnIpUeFQOSn9lZQL0r6nytJfQ42OJ+0blQPmq5zqU+EW5bSwW62vq3CrsiP1gTAO4WL1fGlfUnaFe5Q94USt5iecBPP9QoWblF3hFuWkjJdXDuT8QDkj9QXlgtSHyiHXT9mR9TV12r+wo+xx/ZTLws3KJeGccnEXya/KUu8rF4QL4L/x/V3Jl/XnkLvJ55ITCeHzyElyK7mJPI7cQp5NzpNz5IC8lFwgryYXyWPJJfJ4sLzNFl6j+ZA9cpq8mJwlTyB75ElknzyZrJ9PcJbmx/oVZP1+1fnkTtZfoPmSLyH3kNeSnV2EZ5Ibya7mT86TM2SfnCMv0HzIS3Q+5BnkgHwxuYO8itxFHqP5kleC5THQ+O7rO46G3WQdGsXf7OC3Dar10cr11Mvy95S9HK/sZy/L7wf0cm3l679erqvsXy8nKvvXy/WV/etl+Xm0U+VdK/PoZfn8pV7evXL/9vIe8raMrN+v7uUBlfu1lw+p5NPLfSvPk16Wv7/v5QMq+e1Z5Q9WGvXygZX8erl/Zf16WX6e08sDK9e/Mq/f9l4+uJJvLzdWnn+9/JHK/dvL8vcSvZyq/PueKsvvc/Xy4ZX8e3lwJX/hnQ9HrFnrk8IZ5ZRwVjnNJG7Tv48WdrU+K+wpu8Ktyp6wr+wLtykHwu3KBeGNykXhonIoHCqXWH8L8ysLF4RxyL8lbe8Il6vz5yrtRe49eDPxomd9jNxAjpOT5BryoeRachO5jtxMTpBbyPXkHHkXcp68K7mVvBu5jeyQ15OT5AL5AHKR/EFySP4QuUQeQC6TjxTEXSb8GV0PclrnTz5K50/+LDlDPprskYeSA/LnyB3kz5M=
*/