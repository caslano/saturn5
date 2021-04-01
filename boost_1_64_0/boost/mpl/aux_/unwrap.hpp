
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
/gzB41xfcpzNo6JWkL6QuMouLmhWKcu3s+lNm/+GC9BL4Y1mS1d7QB3lwxrJkheBOnyRJeDYv2a0Wnp8xFgfPf74232//hQo5OnGxxNCnyhjNvfamp5ju7YT/2pRcUQt6PO3abOt17NCBwTIFDeUaJtAHCKzHOvXQlAeEOAa0Q7LMsNnBAdaNeo+eNSDE/Lq480PsFNMHOq0RayzwP0wRO584aCJprz3zt2aV0e6N2XE4lxsV2Xr7ziFogYi0WfHqO0m3T1G92Om5AP7YlgLEXCNB/qJMgfkFZ7UbgpLW9nans0AL48wnqGh9qKf0jAx8v1Xr9Cju/HsTjNnKj47YntI1PFvQZqBwfGrbqjJDgOWuSouX++vukHPWK7DDztDcJBfEjPMUVbKPmKD1ccqANo4IQF8wRWqk94GfEDcGXeFUJsOaxnBJM+oR1p4VzlltTW8hmPa0/udwmAWOzXs+6zykjuuG4LzRQgPn+nt7aSeZNElzSWI1jsjXizXuwNzgqX98Il9PQBZN0+66YD+6YTKpEyKtVziLMZvqDugOa3zQVBIecwFRF+oeA==
*/