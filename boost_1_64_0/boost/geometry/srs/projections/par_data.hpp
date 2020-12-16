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
RX0JekiZ3tQEuVz+ZEuqA7pBFtaGrE8dUX5wDfTBM2SYvz0f3+Rnz2BbblG2hE3hM0JOwpMs5vpSlD1CNma2aZKyQQ7yxxFlyzWqP0AXGmOhM/kcdKG2vH6BvtXeNH/f0n41qdqd9yPg+DiKclQnk4nW1iT335bJuo+w9bchA+SFDjR+436BNji5bOE2wL259uH6Qw623sKzaYfXkQxG/UwfPmb9lM/BC9h3nIm5htcLvsTveipj6lR97CjBBm2yDdg6QtvQ0IlsubC2b1pg28PnSQbwBm7uOVa3/9eX1jYOoU5md27H+dX/qjNc/3zboH3pwtrg8qUL94PblixMBtTP+yO3DcpIOcAbPKl+4mGuU766xJxHII8aP1AXrZ0gO8l1PpMX9VHdqNMci2k+F3WY/bcJdaMu4o86ITuteSGrnAchL+Y2qp/rjjn6zK2/TzX+a9ffZ2I8nH1+Vf3MCjKQDT6K61e42qR8NH7+lGyhfQJ44xyt2lpoyyqcaSBQ8yVcdbh/E64XtmCfi+slzYhL4/oDrgZc6ZXeshcJGK5Ro6ymf0VM0MnfX5T3RMPL3wtlwYPofo3r/HMk3fdW1U4nfo+q+6/jalC0/eda1vPuKOkXrQQvxef150hel+D3DcBfBNxFhh66/hWr59a3Wt1PXkDdwKEM9CJdZR3XthJ/1Adeqk7Qm/WAr+T1fdCsPre6jJfccf4yngb8TuA9gOtprdX5f2QBNtD2f8087X+f8+Zft5/9y+fUbn9xXbz6zPn0fHU6B/Bvra7IkAth14wxVjzUQrlzw48Dlvte02i+YOecfLmYtOWtk7nvWDmdSd13Q8eGjvXj9512Nq7fcCHhZrZsvq8zmSjaqfsW7YydcGxdIpMeQ4FLd3QUbef2YZyyx61UNcaK5Wg6l8yUUzZ+l+xiLpEZTSVydsdkOCIFHp25//qL4tPjh2qlSzi5DaBJbhstFPMTxUS2bTydsZ229pmtW+45ejCdS+UPOm1T6ZIzumG9psZtx/qODfdfv2VTx/rRcrJYGs0mMpl8cr6cNm+6SHCSlhRl7WIxX6xVF1wLFKCcHT3obCwlC+lCrZWLBlhg7Up9SJAuwGtqlSBZqpUiM5lwJucisuN558woNobuUXJSc1UoJCtlnLhTLHQka1PIKdbcboWppHNhrUR2sWbnHEvnO0IojiuOjpTpqJF9snioUMrPt514T3ZKxXRu4kxwSuaLNn7Hs3Y2WTgUn7cXVeN5cGFiUn8X5XI1dxwnMW47pURyqiNEkxZQzi6JVl3o8KT6EVRPZNITufly89izdKhgnwlGTimVPiP+Ry18xjm6DOPJfG48PW/H4XxL6ewZMR1pDIZzTvzu6LghXrRz9kRHMlRZLEU6ahxIxWw2vamjxm4B09Y8a+WTzpxjttLDnil1hNPYziXDlEQXLtlZ9QvzzXSxI6SdaK0GlUGeK8VF24UauWdVHKZ9ZhOlMEXWTpXM5Oa0odlC5XTNKnWEEQwzXSlci4qiYBy+rO2Esw3KFp1E2KLZZG48bNmwbYqi6Vw6tGZ2cU4XVUUxzoWXNpkuTIYuaxdDi+vuLmp0N0Ez54TsVrApnnVCjYHOptDtsSn02LEpnhwLVbJoY4BPidtNcXlfK9VYeXzcDtXwigq/4pnEIbsYdzbNiyw1Z7MxMjEUbYiPpUvZxJwrdkFWeGTZLtthSmbt0mQ+FaovpzZgAC+Fqj+1IazjpEJNnmp5H8dvFB3fNppKjdozcoJIFNKOXgqIVYCTmhIez9ZwimA6WcrnM84oFgK4x2hXLJUL2NAkR7NpJzmayKa2bB5NFsrxVNopVK+mnEuPp+0UOIgqZi+VQ4oGkNg=
*/