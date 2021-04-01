
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
V7RhJaiHX43PCjubf7w/iKpgVRiJaBuIuOlGc122gkAOL2BvlZwvc5CXOjxGKNSmD+Yu5WADOoQDqLregJlg1eXd3TaXl0KLIQWjx0lw7GHkLsAL/L1ESp4fkIkkSYXQr0kpiogmHm3Wm/GePNDd7isDHL9yis026rKjyZBYwW+0niVFGKOi6E7qcmJm/tn83Q4Tq5rQNPtAmgi9Gu8lsnmOFlDMfEPuTkdqauZo+LwVzS9O6QR4bRjCCe5upH3Epv+ksFNLONVx0pHZ+gA14D4nPsAXB9Na2RwMhkakw4JDh+ntP01QprrtwguVpzKuWUrzvg31L1E8b/4jpfyCb5D7adQxNS7bdTOmNcShIKhzdhbDpWrriFLFO7gB1bDD7PYJ9wo7fTL/Ug8UBQCZzjTg6dWekTgMFIusL/43aqLRq89ahCe2MFGqCMY531TYGxZGZxzbK5ZX5S+BnhveId5POejhb1235RdAsw3wIzApq2/KofF3F2d29mHIRNh0bon21px+aOzALCYXzARNjIO7k/FWY4r3pVMujA2OlDkTDjPa8c0sT2gWOA==
*/