/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_fold_fwd.hpp
WM2bG3G8Ae/BZpiFwTgdO+O92AVnYDRm41i8D8fj/TgDc/jf/fgAPoCzcCXOxpfwQXwZH8I3cZ69nbu815T3nXNd2rmHSDv3zhiGoThc5hpJkblGUrEb3o3d8T7sIfcRPZ3b8Zut+6nvpn1vodnD9sJmD9sL3+XY3mGX9dY4txeW9eq7Wc/s4fbyZL3WbtYr9nA9/3RJr+F60i9L1uslx9O5v9Nsub49KPcdc/Anyb9C+d5p+V4NnCXfmyrfS5PrYoa0g87EO6V/cTzegw9iFj6G03EH3ou7pP/xO9L/+F3pf3wQ78evMQdP4gMSr2KTvMvAvVLfKfdjB536pzXD03I/9T32wDPYD89iMv6IZjyHs6Ud9xI8j/n4q1yvL+B+add9CC/KfdTvaLkeodI/6jLWxyvYBv/ATmhS2v+iF45Eb5yOPvgwVsSl6IuvYVV7vS7vKzBCp15/R87DA9JfsEjm9vlA7uM/xHg8KPXkx7gKP5H68DD+IPezZ/GIlJejWFv6O9bFz6XfRTG2lP6OQfgV9sYTUl9+Ld8nHvJOgXtLibdy/uyReNeSclNbyk19KTcNpNw0lHLTCOdhY1yFTfAzbIo/oj+ex2b4OzbHLtIfeRgG4AhsgaPwFrwHA+U+oKXcL7XGhdhG7mvb4Rq8FfMxCE0VrXMT7Tvpvs12UinmJSqfk+jf0w67tG2wy+fqLp+r+89qQ13nGs4/FMSkKiMIKYQFhALCHkIx4RKh8QBvU3dCAmEWoYBwgHCO0IAOzGGEBMJcQgFhH+E0ofqg8nbN5Z/yT/mn/FP+Kf/8mZ+/aP7/uCmJ0+P+rPn/p9dXOs9b5uUbOSJi6LABI8bEDOo3ZkC4Y/4+S1+Bhk59BSJ15v+/wAsH8yjlWVGzoVLNnXO2vnbu/z0Gc/8X6u6vdHPoFNc0nnsoQGfu/99I527d/Xo+l45t+7t05v2/xPbPjnKM/a7eh/vt2/LxYtfSjwFvi1eYzpz/V9he2Gjb+N5ljxfH12Ccb8/GybzWv+f/Wb/b/7ePh/lnjXtZ2t/tS9ve4d/1O/8Hlt/5Z/c018zqOz3umSYX/uHb8cDasv3O70+g7jScW72+8/vzUcZzq9d1Hk9G1mvqZntnZb0eJa4n5z52MFjvgIdzfu8a5M37ntK9Wyuf8/vq3q/9O9+thW/673i/9meOY1CWMQzK+r6t/F3b1b9rO0Gd5Msgf20IUYTMyPJ3ZOWf8k/5p3Sfv6r/P8//Vz3/v/JMX7udyd4vJsU29rQ8i14k/Mwzn99QW78412e+sveLU5ZHOJ4FSU6yLHfuG0d/2pTkDKc5AqWPgNKlT92np9hLv6+aeeS166uWVEG/r1reyL+2r9rRCvp91YpHXru+amHe+n3V/Eb9eX3V9nnr99MKGvXX9NOyxSNb+uDX85H+cnietEZFSV8Lg3c0c00l97doNULd3yLXZNBPVmfsgjxUz9ki547BOdXeMS6B9JKXuVGk37ayXLqYS/8ebZ/2JJlLk3gkpmca9HlSz6XJPpznZU6WOOn3i5U51WTdDGbhVHqS6PcTkeMoabJstvzdUfm7o/+ad0eVQ5XlLXrUXxdXuVuA76z5P/Wf+1HFsr07yjHJNVqu3Xkuc6y0lLZlrfEWbCNtttviOGyHmRiEOdhexvINxmexg/QJCcHPsSP+gp3xIoY6t50c6Wg7mUUwarOZJ+u1dLOeXMNkrFqjtpNy3cH6btYLkvVaG69H2z2p26XOV/Kzp7VtoOVzm+Rnf7wZB8qcCYMwFCOxNw7GgTgEh+NwafM8ApfhSNyAo2Ts6NH4CUbjURwj+XsH/oF3Stu9sdhS2ji3ljbOQzEGkzEWzRiP0zA=
*/