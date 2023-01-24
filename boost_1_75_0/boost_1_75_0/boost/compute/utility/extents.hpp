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
SIfTbqXVyqQr4MSsjcTDDLj0gKhBS7yhd646dUeTOmXTfHXy+JA6OVNUJ1ctU5X6x2XdJPO6NPIMqvSno+p8KiscQWhG1xxa2nZuSL1YLTpF7souo4I0ZjHWRLLCdT8e7g9dEzI9ZL+SXca+sdmHD6cNz7vfWgotwgEYl5a6D/PV/PAWDW1BXQgwC0y9uS0GU1iTUIcOafOq/cd+c42F/+scdOP+6ItRSxdLw9RvVRr+VNqQ6cb/XibTG/Q2urnp3F/0hqxHwu2RXKw9nqtfljxIU9EebY7kwg26sbWps7m15dvJST2cfKytddEIl/Pbbmy9vKW5qbOxM/yQNdb6ePv5uqP9O52ljtbOESrnd+xqP+L9vf1FnaoNDezSqYHly1ct26D1iqWjqX2tywa26uXDhb3LV6UeTR/O0t+zyzOr0otSy7JbdWY4ty2zOrWyuCVVo63lS7bojiXn6tZv6ZbOpmaC2+ncZ71fusVq3aPvbf2BXqqWWVclh9s7O2Kp2ED9svqBWIFq2ZZcrBhb0tkaKzW3dsJf3sdDzOSTuaPHFwNwDd18rQf6zht6gm5KNaFItbZGdadh3GKeHTo+I9821cN07AWqRIiYt2YMjfV5KUFOmjJ75/iT2InQhZt19ZRhJl0+QGLanqI5nF3TfmXIesJZbueslvA6a2Pkdh3bGW2PdFqr9HpirEpOs0tmo7FY84f592zJ+Hia
*/