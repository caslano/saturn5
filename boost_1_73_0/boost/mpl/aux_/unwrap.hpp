
#ifndef BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED
#define BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

// Copyright Peter Dimov and Multi Media Ltd 2001, 2002
// Copyright David Abrahams 2001
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/ref.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F& unwrap(F& f, long)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F>& f, int)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F> const& f, int)
{
    return f;
}

}}}

#endif // BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

/* unwrap.hpp
Ft6HEdp76cKb1rctO48Gpuq0dfaW1OSkkWOjvW2Q2QKMp5a47Yn9HRvCer8L9cGnwo9R2fk6e9+4me42RPrv1gU560lss3X3/euFS8UnRt8Zy8/cdldiW/2kWuE61sz1swx9nt9kpem4rNtyfbJGBuyc93p2zh8cMz9lW8I1UUL8pIR4p22/3b+d6vuvVPEYuy9rngFhG3+jDgptznDfPM95LOeYzsnHjfKwjnwZIT7r29x0
*/