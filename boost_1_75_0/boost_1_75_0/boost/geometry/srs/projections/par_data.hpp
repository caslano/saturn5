// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_PAR_DATA_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_PAR_DATA_HPP

#include <string>
#include <vector>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>

namespace boost { namespace geometry { namespace srs
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct nadgrids
    : std::vector<std::string>
{
    typedef std::vector<std::string> base_t;

    nadgrids()
    {}

    template <typename It>
    nadgrids(It first, It last)
        : base_t(first, last)
    {}

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    nadgrids(std::initializer_list<std::string> l)
        : base_t(l)
    {}
#endif

    nadgrids(std::string const& g0)
        : base_t(1)
    {
        base_t& d = *this;
        d[0] = g0;
    }
    nadgrids(std::string const& g0, std::string const& g1)
        : base_t(2)
    {
        base_t& d = *this;
        d[0] = g0; d[1] = g1;
    }
    nadgrids(std::string const& g0, std::string const& g1, std::string const& g2)
        : base_t(3)
    {
        base_t& d = *this;
        d[0] = g0; d[1] = g1; d[2] = g2;
    }
    nadgrids(std::string const& g0, std::string const& g1, std::string const& g2, std::string const& g3)
        : base_t(4)
    {
        base_t& d = *this;
        d[0] = g0; d[1] = g1; d[2] = g2; d[3] = g3;
    }
    nadgrids(std::string const& g0, std::string const& g1, std::string const& g2, std::string const& g3, std::string const& g4)
        : base_t(5)
    {
        base_t& d = *this;
        d[0] = g0; d[1] = g1; d[2] = g2; d[3] = g3; d[4] = g4;
    }
};

template <typename T = double>
struct towgs84
{
    static const std::size_t static_capacity = 7;

    typedef std::size_t size_type;
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;

    towgs84()
        : m_size(0)
#ifdef BOOST_GEOMETRY_CXX11_ARRAY_UNIFIED_INITIALIZATION
        , m_data{0, 0, 0, 0, 0, 0, 0}
    {}
#else
    {
        std::fill(m_data, m_data + 7, T(0));
    }
#endif

    template <typename It>
    towgs84(It first, It last)
    {
        assign(first, last);
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    towgs84(std::initializer_list<T> l)
    {
        assign(l.begin(), l.end());
    }
#endif

    towgs84(T const& v0, T const& v1, T const& v2)
        : m_size(3)
    {
        m_data[0] = v0;
        m_data[1] = v1;
        m_data[2] = v2;
    }

    towgs84(T const& v0, T const& v1, T const& v2, T const& v3, T const& v4, T const& v5, T const& v6)
        : m_size(7)
    {
        m_data[0] = v0;
        m_data[1] = v1;
        m_data[2] = v2;
        m_data[3] = v3;
        m_data[4] = v4;
        m_data[5] = v5;
        m_data[6] = v6;
    }

    void push_back(T const& v)
    {
        BOOST_GEOMETRY_ASSERT(m_size < static_capacity);
        m_data[m_size] = v;
        ++m_size;
    }

    template <typename It>
    void assign(It first, It last)
    {
        for (m_size = 0 ; first != last && m_size < 7 ; ++first, ++m_size)
            m_data[m_size] = *first;
    }

#ifndef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
    void assign(std::initializer_list<T> l)
    {
        assign(l.begin(), l.end());
    }
#endif

    const_reference operator[](size_type i) const
    {
        BOOST_GEOMETRY_ASSERT(i < m_size);
        return m_data[i];
    }

    reference operator[](size_type i)
    {
        BOOST_GEOMETRY_ASSERT(i < m_size);
        return m_data[i];
    }

    size_type size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0;
    }

    void clear()
    {
        m_size = 0;
    }

    iterator begin() { return m_data; }
    iterator end() { return m_data + m_size; }
    const_iterator begin() const { return m_data; }
    const_iterator end() const { return m_data + m_size; }

private:
    size_type m_size;
    T m_data[7];
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}}} // namespace boost::geometry::srs


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_SPAR_HPP

/* par_data.hpp
qEBjSWHUiWuUwTaFPmApSPrp+TEy/oFE0k7j+tyDXqOJF4WZINOQyGG71EgrJZg1zAJe3JarKqt1aSdW7blYoyD5zFl7wkNWtIKuYyxK1ABnH42tZna8qmoYj9aVERFFEeh/e3bm6WHggSoQwnnzstq/7+bL9QOoGHH3w9JiTOGy0fHATd5MEHdPXuGqI8zQ0Fq7mjdIIwdXfyN2GaGz0zmjjFkwu/R8meg+4Ev5GKp6EGqbCqebDtD20+s65p9PdUtL+UuWipdWPSF6MwzsRlXGQPqtfalRtRlqqhIH3cSb9kgnqt82XD2hn+1bD/Ga7WZXFxzefZnzr1KmbJ+0KytIFKZ/NenOx+ihDvtF2JLJ0m1K4zykLPtHequEDlJXM7hqYu9f11p9gOFeiKsIg/xgjGCCcmCCHAeJJv0sIY5UYMd7kw6EqeybjhBorV3th3qXmW3G48yHdoFMzVpvhI9ta5US88eqCXXIlzNl9iLUUq5GzwlkkqrHGjjeHAvo5ZKWOQlzY63s9oZhd43MkmcY00ZwnwD3T/u6Zssokip8+csnow+PjXheGIATwB5NR/wehmd93dPQaV2D8wp1U+txJsJm9UH6VDnnoQKtWUsQvBbejV70eOX1unzM2VI3BGlRY5xVinsQvqtY8XtZoGoM5F93Q54dt+rmHn9cZDHvFzrdn/G/5HYTfmxUWol4ZalumP/i4UmJj/l6
*/