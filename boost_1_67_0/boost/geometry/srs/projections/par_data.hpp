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