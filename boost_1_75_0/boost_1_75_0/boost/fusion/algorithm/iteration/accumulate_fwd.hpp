/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED)
#define BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate;
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f);

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f);
}}

#endif


/* accumulate_fwd.hpp
usUQYwXTHkpg44WP3ulc35yUXP8HtTihVih6HpkNVPQzSeO1OSlgWo3eH87Z3hF1E1KgubKrAza6wdQKa5L3t0e2x+x8UEfd/YZT3tychgRGhLv3Mzca8XGY4wq3aBAuGegEzFD+cCuj5S1lz5FwEzc+VV6HdxA/UmSHw27IIWNhrcav+ZbS1FBZLUMrztk86g+vpFGXRsDyG7VRX5rSyr03xQST4Y/JoMQyYIN2R5qKKXwBhAq0JdBq/pXEt5Ugbt8FZ1EJGWLjleUNxceD0vgafRmPdaB2FOpfbUHjsmjdZnaz7sB5RRxqnq3ADUqqH3hZqkjljhPZ3U22uoa5n5ogGFi9bVSDoDKqfVilZd4VpJDqZCOLXni4rE5bbUKHPUVwE1tEehT+Skzla1nS8ZKhbF3+q2I1Ta9HRYMQegz6V5rgGrLRVtVHtAZXsMFPfOwt26l6BiULpvSY3gLoMLVdc5aoGQigXWjPNiodZMqf3ptkUrRKN11AOlGrYv9p/6O1VnYM6673vCy2Zc8/uKCdPdfrvH8Y9fx86rkTem4L6Xky97zjP+55jNZKN2PPt1pa9vzEwHb2XK9zwxXU8yoL9jwTej5mqrHn1wyknpdY/mnPo7RWxl9h6Hm/CD2/or091+tM5J7vQ33JUW7o+VNTjD1/IoN6vibmH/U8xz89zqXs0hp63mXo/IyYlp2vyoDOHzR2vjRC5w1V
*/