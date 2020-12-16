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
sfSfbPDuc52Jwxqnuu/Af/cUw+FbErYC72E409/K+4F16m9iEritP8R/earhtM8Qlo432Gpn2b7/NMNbeZ+fZjjL++QHTayd9u8+BLyzXm58WOP86A74T55lOBKAzZHT4Jc3uvQSewxned8TmBiixnnOrZBwKXOSrPvmsJa5vN96v9V1yiJIHtjOAG/UmfH5mcgL14u96v9dZNJXT9XPF8QIfw/2Q2os8InC3wneyjHcOcG9GYbjmgR/d4pzWjbfOzhu3zmZ38lx+87Jyq4GL/wh9uBt3Mrj7T2co6seeL7PxGFPDvy/HIctOcrwEMNxZwj3q1gbKUQQ1XGSZeWDthHsp9KdRJke7hXBvzF/m5xz2j6OX7M5bd/FWNt/eesQrlbme7CPO4w3v9p0yanmWzyMC7vF5sVQ482PbVzG8luMuCe2D+P1eNymz9+WTNvXsBjv4vQ6dXZwZzfX1tk/u3lMZ3hvbhfnWv6CUf4bu4fx2rp9fyOzZ5gMd9oOv9d7O/moi/fgPfJhPDh5R77rh4Zxe+18N3csHzF96niuU+ZB4grZm449e0pai+vLSeDfNfmnMi92sjSJNZ92qrTAezT/iNl/Tyael2eVX4v+Q1d9rtNwjzNuHCW5W6SSq17EAncwNp8a1R1f33la0e/u9fTbeE28X33IiPe4F9SFm5au8IPTZ5vigftNxq2SIqrzLBV0oQPcJzX3FZN7zCudTJYtpHgVFbzvcp5Tu5EfqDgVD2nfZGlnXh1meV5SfMda+fwF49Z5kEdlFFOc4A7u35vcQqRZRJdU+xk9FfiB/MNzLX9bd7lMHDthEVeZyvQpaXIj/5g7b8lMTDC/bXWUxEFa+Ejn2CAhyBzkMpGXhoHnFEjn2CAhtMHalDnlV04YBG5IIpItpzeN38dGVysTrE7jOC+KshaJHzi4999wNxjXywPXq7JYkLEkuE29fpNxk8opnbIQp4PA5/X/ygSvf9dPHM8Tz3lTVjthvDyJiiitC/KKxct/w+Q9XUS1l9elq3in5JKuySfKf2uC9cEwdqMsi/v8k8d5G7zDuJWXplJbZZ97fJLn957JnSrDxE/jwhFuqPXf8P7LeHESZHWYeOL8ouY15Rp5mI1Fhe/Wue+I8/JO/6K889gq1+Mm/3geOrlbppkg84yGKxruIcaNUxl3XXmCDBfAbfIxyfKR5Hnp52Haj/eUXPZpAeRbML6feHkVO5GKm/GbNr9k8gvhp6VXFbFySyarz2jCRn9/0ZQ5WSZeFXlBKpzgNGp8reFe5Vy3rmK3ilX04E41bYnnpXCKJKujXJFPTXXn5RaL36vSIAo9j/JCIjwvr3FuHARxlBRN9Dwv93hewiwLM6/2iCwX4t15OfCIGX/ohnEdZQXlhUR4Xg5ybpLEVeggep4XYXILUflVljllIJozfmjSGGdrLhM4QekEsQOXb10yl7mMG4ZOFuc10oGWDJkXuUwe1bHjuznS6ZK5wWWiLPX9wHeRDjRgyNzkMkXqB6mThkjHlDG/y9P8uwyT/+a7jLnEPrPfhE5cu5kjx5oFGff5lQXEXTbjw0N8vVinsV9l1QO/uZ3q+KbN+PxQBEGW5mlVizNL0qHIFzeXyR3I+XXlbWZx9bJ8Umvzwho5KlFeLk8oP9a0X/71N8k+p8pCE67VeblG/8KI3i8nzE2qmSI4E1d+P+wrMuz88qrUxuLqjLYre+g9fV6V4V4x7qI+PUrI4oxWDHuH9Mgo4Xj/DeGvqXDl0kSmM+Bf2ToIX93cQPjINgpfWZUOSb6kzidw1krhq1+YmZP1eH5WSqn5N+TO7GhwCjbej9ylw/V6UIZjzUnhemmA8Gf26HB6MsF8f3U=
*/