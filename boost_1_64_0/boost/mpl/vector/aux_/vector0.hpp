
#ifndef BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>

#include <boost/mpl/vector/aux_/iterator.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct vector0;

template<> struct vector0<na>
{
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
    typedef aux::vector_tag tag;
    typedef vector0         type;
    typedef long_<32768>    lower_bound_;
    typedef lower_bound_    upper_bound_;
    typedef long_<0>        size;

    static aux::type_wrapper<void_> item_(...);
#else
    typedef aux::vector_tag<0> tag;
    typedef vector0 type;
    typedef void_ item0;
    
    typedef v_iter<vector0<>,0> begin;
    typedef v_iter<vector0<>,0> end;
#endif
};

}}

#endif // BOOST_MPL_VECTOR_AUX_VECTOR0_HPP_INCLUDED

/* vector0.hpp
ewc9donr/om8sS/WboYWT9BOA/Ytn/HuhmcqJk+JfIR2ki/Lpp7GjTyOHv7Rm3VxC+sgjzqCZvLxZvjyG9Fv+IlOvpzD+gT5AeJUcyLx5xT8uuvxw1/DP/yEuuXrkWcvnnMS/Ud9mR39DtbqV+Eb0rB7bgfIz97DekGP6a2IPw4SJ8Kr1vyAvLaxPnh/iU0gvM4g9Aly1jIVO8J7CY59rMceoL8i4efhsbJ4P+iyYOpT8NNKmM9S9Mc+AzybB3YY+etuwq6xrmzLqLdmnBrZF+M3mPx9BusQP7fyWfRQBvy9CV7OlXHnfS9d3xGP4j8nFNAP4g072tGpQ09lUIdHXWLWKPa7fYC9Z371p8jDnFX9PJJJ/U89eXnefxuOXd/3u0mNwzbW2al+8JDwbXfgHxWyPvjeZgDtcoSnqjTAw+B3boWnHc37Qh2pJ9Se8w7ytQv/+0fkbg/tvdOg5AMeshJ+ozMEuxgLT0I8eCSL9whgz5dhz6uGsw9jKvna/tQvw2M28L5//XrykveTP3fT3neO3FSTNzMbOBcRXoV1akteftVE1t0S5OFb+HLOh9DzPjsjfG0ncpN7BP0Qq76Pfqy/krfjyM9C2p/DfowT1O+8it2Ow56Opb3Y0yM3qU+nDaybP9G7FvhVzuy/egp+fSB6ogJ+1hq7UI/8Ec9W2VAnwLgfggcpOoocr0QffsK4fo//cYp2h9JvF+perJEnV/Kj98Aj3oSeLzVzvgrxxwTk4HueNxPe+z141GvhI28dBP+BvW5hftmXGkgepcQSPXwCOwsP3oX/V9RKfvlu/JK/BhGn0b+faSf7OuLwW9e5ML6BxG8H4EGuJT+q5YOM+DOWyBP+Sx3rJ+0v8t2z+f0e9GIevAb6qSQaO/0d42NPnqgav/Fd9pnuxF6/gt7vggeGR7KhPmwfeqhxBPzINYz/TMb1avRoLb/Hrhr9yPtiz2qC4dv+Ji5iv3ixG/ULe7lvE3kjB4PqF/tYTmZSD/AN81WKv3Arflkw+5XuJl5hXr1a4JN82CdFfsbNhvddZ7OPaRPvoa8k/juGHvG15P2WxC9l6FfyKau6ea/MNciHnrygPfr1FfoL3+0wDvswG7/Pgjw/dipnFflTZ97PQT1WBfqitEwHPwOfr+WV3dkvGYe/HcF6o06o7F/wxfB3bvnoE/qdX4benkO+aR1x0kn08Y8mno//Mpq6dF/8p82M90L03yTkQdtf3mFW/99DvRb22cOZ+UC+SrYZOf+UuOcJeMQ06qtPwP9xznCakfclvUa/qCdMh0+PZF+S323oL/yHIurPIzv74T8SD1LXEgwPmDYOO+KDXxjOPvYg+AA3eIci/Jhk7PeN8FTUfyc8ZITHwx+awHxN18HbEtdvRg/XGNV9hhNvavuQ4rCjZvzKYejRCuxhJ+N3kH5EwufdyniOxf6j//PR/6WnkVMv6rl9kaMvyf+1wi904x9NZp1nYM/tiCPe5z1X92PPvsdvHIa/9AXy+Bn9H8381Wp1DtSn3Y993oLdJ85L+xB76Iif+zpxhQfr8hTt2Md76eCxarTz4BzJS85mfHYO4n2sxNHl6E/NX6Q/uZbop1Tqkz7Ef2bc9DPhYeBPasrY//4F+vEoeZ6z5KOwHzYbqfe6h3khzipOYv2cgJ/bAA+7kXgzAX/uY/RqBDwSfmGZJfPJuUY1gznnF7+7Bd7FIQQe4hb8yGeJd34mDnyC+9wBbzDUSD0DfmOCjjwF/vZext2ScwYy0Wv4Myl3Y0fKWB/wPIGx8I+e+GduvDcBe2W1FX7qLfzRUniSfthZe+RnPfWd96LvyHN0NFPfb2beUljXE4zwRvhHT5IXX8p9LfD7nfE=
*/