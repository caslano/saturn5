// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::reversed_range<Geometry> >
#else
struct tag<boost::range_detail::reverse_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_REVERSED_HPP


/* reversed.hpp
L+K1NX4HuBU8Q0sdFTjl0/cFVHfQuEOKLQMj1sECqpUhy640ciyfv1JZRB3xREwICB92psjNRfeuAmkIvjk7wz2matbhp3TXpPvQ6tkMoyUKsO3ppyKaliMU2TkL1ueB5f1gHdETxKVbzNKHpkrLlknq8/VxjvY+rrytmbsKeOP9HiHJ22PcZsmywyFDS0xrrzXlrTK8q8a/UVyztvOP+nJ+ilPb9ro2b6q7/N7ChJxZSsb4BdQZgRMfPcwHr08r+y/X/Nhh7Ip3XDSfmHt0pSM3RZkZwn+s27Aln/8E98+YHFDSvgNQDSFs1G472LNw7OusT0gBgNzM1P0KYXSXmylD0W6VGfNjTO2MB63Or9we7iXwK9fSxWErVk1Ucd27vHaJVa+vE+VHcQCSnJk7mK9Xd056Cv1t8EDbjtMR+ujwQ1bGoun1blxQjj4q3nQNR+yBtlixmuGS/KmEuK3wDCU4g1DPo0Tj/CMJaegKn7ISZeRUhG8UL/LtjhetsvZvN+ax1k0DkheHPOh7oVNcuQurrswF9ILrWQ7bMxkpquo1HAKpt9DREufcryEci2k/5+dmWg+vtBD9Mc00Q3cI408blDHke4XK7t6yTpawkF7s+zgc9WKycWLZ1uXTebru728YvWasYHc9BxxD1fYEqC2o+RibI21JzmCX8LDSLR3Ri3pZ2bdn+cFJQ+LEqG6z7UhR+MK0Bz+0TFmr
*/