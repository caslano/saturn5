/*
 [auto_generated]
 boost/numeric/odeint/external/compute/compute_resize.hpp

 [begin_description]
 Enable resizing for Boost.Compute vector
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_RESIZE_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_RESIZE_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class T, class A >
struct is_resizeable< boost::compute::vector< T , A > >
{
    struct type : public boost::true_type { };
    const static bool value = type::value;
};

template< class T, class A >
struct same_size_impl< boost::compute::vector< T, A > , boost::compute::vector< T, A > >
{
    static bool same_size( const boost::compute::vector< T, A > &x , const boost::compute::vector< T, A > &y )
    {
        return x.size() == y.size();
    }
};

template< class T, class A >
struct resize_impl< boost::compute::vector< T, A > , boost::compute::vector< T, A > >
{
    static void resize( boost::compute::vector< T, A > &x , const boost::compute::vector< T, A > &y )
    {
        x.resize( y.size() );
    }
};


template< class Container1, class T, class A >
struct copy_impl< Container1 , boost::compute::vector< T, A > >
{
    static void copy( const Container1 &from , boost::compute::vector< T, A > &to )
    {
        boost::compute::copy( boost::begin( from ) , boost::end( from ) , boost::begin( to ) );
    }
};

template< class T, class A, class Container2 >
struct copy_impl< boost::compute::vector< T, A > , Container2 >
{
    static void copy( const boost::compute::vector< T, A > &from , Container2 &to )
    {
        boost::compute::copy( boost::begin( from ) , boost::end( from ) , boost::begin( to ) );
    }
};

template< class T, class A >
struct copy_impl< boost::compute::vector< T, A > , boost::compute::vector< T, A > >
{
    static void copy( const boost::compute::vector< T, A > &from , boost::compute::vector< T, A > &to )
    {
        boost::compute::copy( boost::begin( from ) , boost::end( from ) , boost::begin( to ) );
    }
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_RESIZE_HPP_DEFINED

/* compute_resize.hpp
0cPz9X/8DYy/+u2b5+/0Ju4PAXxE+70M/MS+/z7f/lO8DfkTfTyfP/A1+v6lfP1nfQfjJ51/GfgSGnw/4K/BPl1fZH+H3izE7GLadH2Hwb/5npX5hv+mfGXgq6Aiy43Qb4+/r8aHm4+4v2f9APatLv4N+PEa/fAy8Fl19y/wfTTyFXyI+Xfd+BX4HH9T/2l69y/wJXX+a+DvCfR/I8ovPtaXvwR8dg2+PvD1Ne1zFnDt/Crw5f+mf5wsxa8GPqzfjr01a627gM83hD8GvFeiDw3n/8hw/u8M5y99gv5Fc33KwJfUyO9dn+vl73ED/rIB/1DimvkzAy6+0J3//7////7/+//v/7////7/+y/+/fHtH9/CFhJL3Yc3sfGae3cCrx11uqHjqcOouXyt6zfd5SdWmFihXF/+4KhSnlitjx26+qrLRw079NzlXa/W3b+HN/2aEx4WxJ1tNnZXCL3o3zq169WFs+beQdjZP7Rbpbrf9KLSUqAuvfchftvtHBKVDvTjaO+J8t5+22l2XQ+HK5RXmFh5pTVWWqG8d7eVpGvHKzT+0WlUOfc+JKqgQIWdyw/+wdlWKa8qK+iE8d5OJ/TwWT0k9lveuCecpHjAbNcNcS737y5seknTM/R/3rvZsKNGMQVo+W0kRwNxy+CF4bglGGzTIptyVUpbKqHvnQmfsRe27ab6HTfFPywM7gTVpDU7GrtieaEb+876W/mNYtfvFHLG+LCgkFoWV6K0jvKEVafTrvv7r8AU7ciue1FsOweOW6BMFqB+Yifwg3HPNGkbhX57/yLO1GukltdygsOqURHnbNnNZscp4kx9Mf1nFZ5UOyAtNFbHqB6GZaE2vlhOWoBEH8SRuwJNPbnNZsv22ys4vNJKdkEFRuvbTX//Ns622M7l0mJeLSitgw8/KOF7aeXSsqV98QN+lz+kXyL1ZXWg65T+UTGUTbG/649bnUnuncMiVMguRI3GTsMupO87pKgT9e8Y6Lt/LK9od3AdL4riRujZbmQHvklqW9He3aDptw9cwfmneWddJ+SotEJo7+TZodNIRS8vaZBDfOXdJnbUnliBqQiCA51oNS7p0FXKa3A53sEBl5JkUz24fhiX1zVeWK+9PxRntLdXDWwX+v1ArkZKinbwSv9cJJFOKrcVmFVUFViBXE0H0s6tI+66sccXk+pcmik+aWmriSXukHoVdTH2PnglOmXITk5lzW8bL8RwltVu3FyB2bC1br3usbvs5O7mFy9uRvUVaG2SkaJD217MZx3oHcYmBd0w4JNCowmR57TsIOKzDuzyObhxxsjJ8e1xSETOkMArcRpL4NtjVS8ZgjpjW1ylxSorya8TldLypX3VLyurX1Yt4RdjXzlcIFSdL+F+u94ppBZjF9pehV3o/b02/27xDo3HkHyv3W2xSU7YdHmkwDlsLMl1gk6TL7kQd74GraFX5MtXbaxby458ZgMmpCa/eDYUPF9H2eN0C3B5UbvyAaGIQ8/js9oddwxWy2b2WwFI0IJ8kmvHzFYHCzaU0+BUa+9Dq8kHJ6eUwmOE3kE8QtCt0SUo181h2MHUFcoUbDpNFqfatlvM5oaO9TiaGRQnNBqbkxLsOA7NMjdsanacyDhYG8qnySsY3uBj5TUY3qLgQKrB0+eEEcuWlW/si4k3Z4x8qgcHxg4zJ9KubR755TLCMLoIy2WVCtdwUdljrMxtmvhQfnPGIaf7VJxxLhtXiUlO5VA2p1M7gM1pcuw2RfHGaGr6WDvjuB7Hkko5FTbFaXG6ZvkGRclqgpjd88VcoYm52r52WBUOGpbeAsX1jddxuHs4pBE2g06H2kGmycELqu7+ZLN4kFZLfHRF6K9KpTw=
*/