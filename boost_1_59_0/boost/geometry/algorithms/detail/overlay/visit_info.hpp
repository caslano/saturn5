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
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
*/