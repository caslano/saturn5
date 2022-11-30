//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_EXTENTS_HPP
#define BOOST_COMPUTE_UTILITY_EXTENTS_HPP

#include <functional>
#include <numeric>

#include <boost/compute/config.hpp>

#ifndef BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
#include <initializer_list>
#endif

#include <boost/array.hpp>

namespace boost {
namespace compute {

/// The extents class contains an array of n-dimensional extents.
///
/// \see dim()
template<size_t N>
class extents
{
public:
    typedef size_t size_type;
    static const size_type static_size = N;
    typedef boost::array<size_t, N> array_type;
    typedef typename array_type::iterator iterator;
    typedef typename array_type::const_iterator const_iterator;

    /// Creates an extents object with each component set to zero.
    ///
    /// For example:
    /// \code
    /// extents<3> exts(); // (0, 0, 0)
    /// \endcode
    extents()
    {
        m_extents.fill(0);
    }

    /// Creates an extents object with each component set to \p value.
    ///
    /// For example:
    /// \code
    /// extents<3> exts(1); // (1, 1, 1)
    /// \endcode
    explicit extents(size_t value)
    {
        m_extents.fill(value);
    }

    #ifndef BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST
    /// Creates an extents object with \p values.
    extents(std::initializer_list<size_t> values)
    {
        BOOST_ASSERT(values.size() == N);

        std::copy(values.begin(), values.end(), m_extents.begin());
    }
    #endif // BOOST_COMPUTE_NO_HDR_INITIALIZER_LIST

    /// Returns the size (i.e. dimensionality) of the extents array.
    size_type size() const
    {
        return N;
    }

    /// Returns the linear size of the extents. This is equivalent to the
    /// product of each extent in each dimension.
    size_type linear() const
    {
        return std::accumulate(
            m_extents.begin(), m_extents.end(), 1, std::multiplies<size_type>()
        );
    }

    /// Returns a pointer to the extents data array.
    ///
    /// This is useful for passing the extents data to OpenCL APIs which
    /// expect an array of \c size_t.
    size_t* data()
    {
        return m_extents.data();
    }

    /// \overload
    const size_t* data() const
    {
        return m_extents.data();
    }

    iterator begin()
    {
        return m_extents.begin();
    }

    const_iterator begin() const
    {
        return m_extents.begin();
    }

    const_iterator cbegin() const
    {
        return m_extents.cbegin();
    }

    iterator end()
    {
        return m_extents.end();
    }

    const_iterator end() const
    {
        return m_extents.end();
    }

    const_iterator cend() const
    {
        return m_extents.cend();
    }

    /// Returns a reference to the extent at \p index.
    size_t& operator[](size_t index)
    {
        return m_extents[index];
    }

    /// \overload
    const size_t& operator[](size_t index) const
    {
        return m_extents[index];
    }

    /// Returns \c true if the extents in \c *this are the same as \p other.
    bool operator==(const extents &other) const
    {
        return m_extents == other.m_extents;
    }

    /// Returns \c true if the extents in \c *this are not the same as \p other.
    bool operator!=(const extents &other) const
    {
        return m_extents != other.m_extents;
    }

private:
    array_type m_extents;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_UTILITY_EXTENTS_HPP

/* extents.hpp
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
*/