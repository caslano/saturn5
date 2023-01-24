
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
sTUmb8n3tthN6v4vj7RbS5iDS5W/AelXIuYtyxkh5qGPCZdKvqE3IjlD3ICKU1twY2MPdQ3OysMiaT8Siz47GDqbVhC1qLalubi6tFOxqxFqSCii4YsdoX4kx6H7SrBMasO4kVbMhNCAi9kLoywCGBdZytRdGyIPC6b9ptiZSrGZxQeSyx8eLCIgSjGC0THoHhZ6Ymd1M+6GZn3kQUAu1HZAaIGJBQtLKU3GFoE2zZpP1FsEHndRaKxGj/NXO2NRnxkRZfemH2u9BSZdiV5FCoza1E0WAUcE6CZYKm2iQZL+7q09unoZjgnb1OzGSa6/H9yWxMMXgX43jtYzQmejxfKMwGjFMloSudJ7It+L5cEEcsZNFp70v3tKPll1V/XJdCGtylZ6TKMjHuqMZR2ihJ5pk0f6wKOQlVF7MJxAQcQ3IAAffPz3TEogcYi8irPcPmm5mJQviaWPNC3GlVa6PbqI26DJu+PaGGc8X6ZxBsr5UkB3GYzJdL90Qs3dchTDOYFHZtV7YqtNFFh05mrUuU15vhEnw193xTNnvP8S8sz6JJ7BjTKHehLPPM95RvGW/GyL3a3zy56kEbi+U36Z9mv45dKsX+SXUyjqBJACPDNdCQY5z7wCr7ekE8+wsYEi06NMNy7k+5/wq19korQOmOhA7L9jopCBiTbFMOvLr2Gik62LOBOVxlaYYCh7vGgRGBO9qjGR0o6JLH06
*/