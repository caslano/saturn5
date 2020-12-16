// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_VISIT_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_VISIT_INFO_HPP


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

class visit_info
{
private :
    static const int NONE = 0;
    static const int STARTED = 1;
    static const int VISITED = 2;
    static const int FINISHED = 3;
    static const int REJECTED = 4;

    int m_visit_code;
    bool m_rejected;
    bool m_final;

public:
    inline visit_info()
        : m_visit_code(0)
        , m_rejected(false)
        , m_final(false)
    {}

    inline void set_visited() { m_visit_code = VISITED; }
    inline void set_started() { m_visit_code = STARTED; }
    inline void set_finished() { m_visit_code = FINISHED; }
    inline void set_rejected()
    {
        m_visit_code = REJECTED;
        m_rejected = true;
    }

    inline bool none() const { return m_visit_code == NONE; }
    inline bool visited() const { return m_visit_code == VISITED; }
    inline bool started() const { return m_visit_code == STARTED; }
    inline bool finished() const { return m_visit_code == FINISHED; }
    inline bool rejected() const { return m_rejected; }
    inline bool finalized() const { return m_final; }

    inline void clear()
    {
        if (! m_rejected && ! m_final)
        {
            m_visit_code = NONE;
        }
    }

    inline void reset()
    {
        *this = visit_info();
    }

    inline void finalize()
    {
        if (visited() || started() || finished() )
        {
            m_final = true;
        }
    }

#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    friend std::ostream& operator<<(std::ostream &os, visit_info const& v)
    {
        if (v.m_visit_code != 0)
        {
            os << " VIS: " << int(v.m_visit_code);
        }
        return os;
    }
#endif

};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_VISIT_INFO_HPP

/* visit_info.hpp
i9lMR2hQtCrn4xu3oMNsZbLDtrPDxsb4EhuFUbppiYizQ0ZUGfIs9R+rbSabEkOmFI00BjxVvd3Np01HzXXCjT73lQUe05+bSimSadJkeBajtK2IuFW/GxFYFaQ0hBSkC00T0iyZH1Aqbkyw7NQazWnL1YKZSRRK1e++UfbPAvxyVnTjVU1mIJK0Tjjwz59pL006Hu9rufCUdeqk5UGuGpbdOzJQTobI711iaqwY6nEYTbhRVvEeFMm1aM8U1vsmGViMQI7QFwhk14vBmCH3x0sRV36+MHLk66efx1Yxa4wIizr4fm/px1gvhn9k7D8g2bGIt0G9a27FzcLJU6SZd/iX3BozLu+0MVUXRlYPcdGzYohn/9tP/Pt3HxplIvPwUezmfJf+01Spvomwizk3ozz86Z9NNY8AHj0f4XDQk4riT4zi00IOn3cUBDTPlqfic2T5ee7Fn+A2Dvy9r1CVvFkVRScT0WjKYEVEYg5X5fKIVMpF/xTpCycb52TfBReOlXaoxuF9ekziCZx+E4NcWr2nXe9x38I3u9ChIGGmIDvcIe71Lf2cCFg2FOJyXd6wie1V12/AYhIEm9GwM/ElwuuPZ98j6aAILwa+FgbGMvO1d/Q8QBP0OIJ+azFq0QmQrKucUa7JcoUKuhcP90QrKUySn7P+hlTzvc7IoHXe0kF2kCoIv3Grt/QG8C6cuNFcF4icWBOY/U0oCZ3zM6knwhEdUEu2UENbuTCOC3JLMPriQDaDg/h41X2u1GO+h6SSshqGYazDdzM6GCTs7qKT+C5zqRy/w2gu+lYxfmswflfo20LGUSkgL1+lKBwe0n5JXAEHcD/MnRLiuaVDkuAf/1EgZ4d79kC4fcV7nZP7Ivf5c2TuaSL32LoqFJpvD3GG1M1zMMHPdpFgikpwbKMEq5jgQpngIlJZs74J3RjQ7P7TJnimYAeyYQTWBrR2Ndy4s/RnAcl3kHO2hX6HXI9WuQ5olGsFc3XJXNtIVs/OWyToiY1AawRT8gYB+pE46TzbWz49/mxvKW7/TRGV1Ber9L8x+7Ogi2/JaqZ+VKa+z878TuP5lNQ59Z+RZqnA982TDDKxqD1zybHTBrlIkMv5WprB9f8WJ1zj7Nix/aUTHPrTN3DzH+piqq4k6847Qi6geUzdmgWR+fsOl/bX7ibsRZ7MD9CDRddwS5kIGVSOpDw6oB/X5M36zD2Lt57h3faigF9bAeIMYBST1edyleGWYhdEkx/hOW+4Z+5g+r5v8AJrNrCSM8Dhnr2OoZSmRfVSwZFy6e+hgSRRZwTN93AZDlqjCjEBDY95unynrZty3KS+1Ez1nbZmypGTwN9q7V58liOoBVyo3xvcjVy5We1SJrfCDv7Rja8xCz9f73lPrLeo3uz7UT32xZmHq5fa7Rb8n+3E2Jj4P0lM9KDGwdCMUeVM1+RMj0MBjZ3wMHq8jmsqS/i6O4dnpdq0prHPo/DEum0uepezd4rqOU6GWM+9Zum5hSJGwZ8CeHNI53SX2Z/P7B9gB2P5ESvNW5vnJxd1MlMVsmp30Gp99kWeog76pOu5EQz1ICdYj9TuJpTkyF6FGPbUpQA299zrJNtka9jaQ19MdMSq9d0keXb4IRU1WY609OipMvnv7MKAuGWtfcrISX9sIqe/sHKBN1dRd9kI919XRc5Jr7sJwcT/sBKWbYR+r4kelDlctPd/0u78ofpI/tVN7zSY7z0/i5nQRP/LEn9LgvjBlnhbqGl8D0v8mATpG96OxZ8wsWn8h5b4569rGv+aJX5mgviHLfF/TJD/TZb4cQnSj7XEpyeIH2yJ75Igvoe1fYna/1Ys/u1rE7TfEv98gvjXLPEzE8Q/bIk=
*/