
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
UCywcbLjVC/mnDiRhBMxkQqv6iQp0Z5Pe8UEpiabQZ3vfMpQUwVzuSFGdb1JXyfA9mH3/k3hekyUHNjGuOt6uXFrZfVYI1U7DlUrV9SkCGhLSsTYwKSi6N7gPpLp9nAPCedIfSK1ILa3kBdfXqrsHnB/iRh5NOmQUrzKXGhYsYgVQGOQiUdiQ2aK/kOBohN0Cw97WMYrTZNNkHtuqmasNbx4ilHgPuhI6BaIjzTfeoXDxvZOzNYT6v7iQDU+K4w=
*/