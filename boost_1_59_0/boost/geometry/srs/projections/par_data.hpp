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
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
*/