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
olCbxK19BifonrhBPOPYTCXF+F9co9vUBuMD0iOGBk136XcPUSU/nMXoZbuYnregAAjIGousK4BTobQLLsS3Kf4QUNWUrv3rKV2e2ImxppW7LsSkHH9IrdwvQNALCMCAQOQj+g7wYZZoRtZFj46FkO+5EGVzkPVv1XfUV3OeUCV+wH7mF/hSW2E/xtSR6fULBwof0W/sAiDjNs1Iy7jpsZDjBUDg9BFN/eAPsav+pdtQ+oCar/sbuIBwIY7K+0PGDe9S8wsCABVTgIongAoR4Bs2k7oNCd8BQRUgeAkIdAAVYYCK0vdI19Pn9d4ryi7Enf/rLP0ICLD13g8bgJGuLsQMH2qbRd+fX5PVAkFR1w4XK/ec6onkIp9mdxRHlLNE2jrFt5ONODRywHIUjR5zuXSoU0+ZI1Cwa6f6eyOUZvw5PcqUrurnFuQ//fGxEAKgcUhtQlc1kjDWtKXvQmTd8ofoCcENRJTObLcLUnDCntm8G/G81fivnc+LHsc/PnDUtlYYJT4on1X6iLZzb0JuFwZRoffx9ZWztf8XNCO3ld4ji/7H1HVGNbFt4WeDqzQRpSgEKzwfEUR6C3ZE2lVUeihBitQQwYQEuIqAGCBArtIi0esFVHqTYgApISAhAUFCCS2JREkoMaRAKC9vrbfWez+SWbPPN2fmzNpnZu9v77PndiDnh6iwkvknLVxrC9wUi/vVKkUckyJmamLX
*/