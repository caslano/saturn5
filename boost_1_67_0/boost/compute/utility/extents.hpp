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