
#ifndef BOOST_MPL_BASE_HPP_INCLUDED
#define BOOST_MPL_BASE_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct base
{
    typedef typename T::base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,base,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, base)

}}

#endif // BOOST_MPL_BASE_HPP_INCLUDED

/* base.hpp
KvKcKHwJG+NObI4vYwfcjZG4B7vhXuyF+3Ao7sckfA1T8QD+Cd/Ew3gYT+Hb+CMWo5KZd7A6/gUD8T1siu9jDJ5EG57CZfgBvoof4ln8CJVrqKexA36Mj+AnOAk/xSfxM5yLZ/EbZf1+0m8Um8v+EUTsl/qYJPUxWepjCt6FU7EtTseOOAtjcA4+gnOl/PPwUZyPY3ARTsLFmI/5uAWX4cu4HF/HlfgerpL6Wo0f4zr8Ctfj
*/