/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_02122005_1839)
#define FUSION_FILTER_02122005_1839

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct filter
        {
            typedef filter_view<Sequence, is_same<mpl::_, T> > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter<Sequence const, T>::type
    filter(Sequence const& seq)
    {
        return filter_view<const Sequence, is_same<mpl::_, T> >(seq);
    }
}}

#endif


/* filter.hpp
b48S81YWn3n9CfmfMcnfhfx9HeYvg5rwwEdUOcY3cLj8VQx1L20/1HH+c+Ksj4hERd5L/Rev+1OSf1+pgx6Sf5qj/Luo215Z7pmS/sZh3kEmz9lXpO4LHOWtdDf3uN0V511glzeSd5HjvKOjImaSedmf83O0zgNNxuqvTN7uq0vMW93gI+9+2YvzLzDJvwr5e5WcvzT8u89/RPF6r2qef2DJ+evG7r/7Mmjrv6phu5cyWByWQfb197DNaeu/mnmfn+44b+nylfZ/9/n3l/yPSv61JH93opoy7rzD/DlsjE+463yLl3uYm3m+BSXnqz7Geg/1rvV1kn9X+V6uI3Gfss07zj95Km+QCbvLvs54n61xOwipbl4fXhmOy2NRHnhOkk3xz6iT6vbbYlVlW3RYBkLpBe8h7+L2EFzDPu9q5G0pKW857LmXfV9x/qdM8ncj/3RH+ctgJNbNsBzP5zpcfjI29gPVyT+71PwTYhP/jOWv6WB7dJg/TwXcOfy46/y1/b+7+X6gyFH+cifyvax7rf+3y5sgb/dnS857akT4XefdR/K+IM/yryTjZrgc3cnbyzTvmLiYpNLHSqjBeX72evU8n15Tzn/t+6NgvNFUfR43PiFKO69+V33fE1kznTwj+i/rZ9bDPenfdGOuyLn6CWrifC313XstlPx1/V6/etZ5amN0eJv0hfp6CaktYx8R1eUeJGVGXhvN6kV5Oqb0epFyO9wGouV5+GfIwAOfwvvJM9s0T3l2vXjQpTLmb1wPDW2e1WWgJN0D9vVkfRiflZd1on9GXJZNV6eyTkKpx0iWK4ffL220XycybqH9tQ+piweIqkQDoi6JMjeZ1UUi5yJKT1T6e6tMtgdtnILfaxmfh5X33MmXho2lLI2I+sp5ueOyRIbFlf4eq5LK0so6TpQyG9u+wl2eie8l35t3Ix5Q+ilHZZHz47s9R5J1ZXx2QjtuyJLy9CaqSrkaKeesmx2WR7psHt8Pi5h5t/2n1BP9gqwzw7bkU8/QfqRc6ebl+lPOZR2USaurE1Imf1l3vlKmbIdlUjv6GCrL2vPd4zr8l4P2HVLfvq4eJIF7pnm57uXYX8a6oI+3f3/a5fqG7UzK4WVejj/lXMRYHv22li7P3o8g6st6a0p5Qh2WRwaaK8f4Ysb1NAwN48bJ81Pm4581lmfjO8p5RBvCQ+mbSigjZzD31I4M4/BoZcmSsijcRzSQsji9YFqWezqXsx0TiPkYt/+GZmUhzMvyp5zflTZOUaGUyUfadk+iudJXmpfpP3LOJ+1OxglRZm4YE7GRfXvyVPpNB2WUgZTuqXyGcZSkvqQj4KezlKUd0ZIEBY7KIscu5RlzV1ceh2MD6etno5Spm6zDTkRrErlvcVSmpJjyjHlWSv3I+xVtxwrS3vX9oHl9BToomwwUdE9l0x8D6tdd7oP2+5S2JEg3L8s9n0/Vk22P7674TJuXTZkCm9iXqT1lyjYv0z2fZxWXqaaUSeZle/1LytRCzr2bEAdq08Z1ZeLxXG1PR2sq19hXfdTzJl4Oavue3D3y3Hl6JdYLJmNHZYVutc1Xn1+OISPjuIOZWDzuYJ4+b6mLo3i/OqaPzNkw1o9uXKZgvKw+W0x69TMLxtxv/Z54zrRpXY3f61p/H6z9PoPfbcaIsJbBQ3feOItDKr48l3FMit8rHD9tGqveSfJcapNnF+s5TT4rKYQZTVfOD5X6kvOoYdq8+d59KmMZTWcHIH8LuPO3sGT5m7RPbZ7ZMs983TwDS5hnkON52rT75c1kjFRnGSMVOysV8/KddT3d2nuGz4ySZ6sZCCOh+LpOcCntLFT7Xt5CetNzdtN15a1bV7JfkvnM5Jw=
*/