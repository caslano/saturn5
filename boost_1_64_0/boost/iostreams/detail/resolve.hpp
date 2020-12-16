// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_RESOLVE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_RESOLVE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp> // partial spec, put size_t in std.
#include <cstddef>          // std::size_t.
#include <boost/detail/is_incrementable.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/adapter/mode_adapter.hpp>
#include <boost/iostreams/detail/adapter/output_iterator_adapter.hpp>
#include <boost/iostreams/detail/adapter/range_adapter.hpp>
#include <boost/iostreams/detail/config/gcc.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/enable_if_stream.hpp>
#include <boost/iostreams/detail/is_dereferenceable.hpp>
#include <boost/iostreams/detail/is_iterator_range.hpp>
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp> // true_.
#include <boost/mpl/if.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_array.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1 C4224.

namespace boost { namespace iostreams { namespace detail {

//------------------Definition of resolve-------------------------------------//

#ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //-------------------------//

template<typename Mode, typename Ch, typename T>
struct resolve_traits {
    typedef typename 
            mpl::if_<
                boost::detail::is_incrementable<T>,
                output_iterator_adapter<Mode, Ch, T>,
                const T&
            >::type type;
};

# ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-------------------------------//

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type
resolve( const T& t 
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)

         // I suspect that the compilers which require this workaround may
         // be correct, but I'm not sure why :(
         #if BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(810)) ||\
             BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205)) || \
             BOOST_WORKAROUND(BOOST_IOSTREAMS_GCC, BOOST_TESTED_AT(400)) ||\
             BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(1110))
             /**/
         , typename disable_if< is_iterator_range<T> >::type* = 0
         #endif
         )
{
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(t);
}

template<typename Mode, typename Ch, typename Tr>
mode_adapter< Mode, std::basic_streambuf<Ch, Tr> > 
resolve(std::basic_streambuf<Ch, Tr>& sb)
{ return mode_adapter< Mode, std::basic_streambuf<Ch, Tr> >(wrap(sb)); }

template<typename Mode, typename Ch, typename Tr>
mode_adapter< Mode, std::basic_istream<Ch, Tr> > 
resolve(std::basic_istream<Ch, Tr>& is)
{ return mode_adapter< Mode, std::basic_istream<Ch, Tr> >(wrap(is)); }

template<typename Mode, typename Ch, typename Tr>
mode_adapter< Mode, std::basic_ostream<Ch, Tr> > 
resolve(std::basic_ostream<Ch, Tr>& os)
{ return mode_adapter< Mode, std::basic_ostream<Ch, Tr> >(wrap(os)); }

template<typename Mode, typename Ch, typename Tr>
mode_adapter< Mode, std::basic_iostream<Ch, Tr> > 
resolve(std::basic_iostream<Ch, Tr>& io)
{ return mode_adapter< Mode, std::basic_iostream<Ch, Tr> >(wrap(io)); }

template<typename Mode, typename Ch, std::size_t N>
array_adapter<Mode, Ch> resolve(Ch (&array)[N])
{ return array_adapter<Mode, Ch>(array); }

template<typename Mode, typename Ch, typename Iter>
range_adapter< Mode, boost::iterator_range<Iter> >
resolve(const boost::iterator_range<Iter>& rng)
{ return range_adapter< Mode, boost::iterator_range<Iter> >(rng); }

# else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //---------------------//

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type
resolve( const T& t 
         BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)
         #if defined(__GNUC__)
         , typename disable_if< is_iterator_range<T> >::type* = 0
         #endif
         )
{
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(t);
}

template<typename Mode, typename Ch>
mode_adapter<Mode, std::streambuf> 
resolve(std::streambuf& sb) 
{ return mode_adapter<Mode, std::streambuf>(wrap(sb)); }

template<typename Mode, typename Ch>
mode_adapter<Mode, std::istream> 
resolve(std::istream& is)
{ return mode_adapter<Mode, std::istream>(wrap(is)); }

template<typename Mode, typename Ch>
mode_adapter<Mode, std::ostream> 
resolve(std::ostream& os)
{ return mode_adapter<Mode, std::ostream>(wrap(os)); }

template<typename Mode, typename Ch>
mode_adapter<Mode, std::iostream> 
resolve(std::iostream& io)
{ return mode_adapter<Mode, std::iostream>(wrap(io)); }

template<typename Mode, typename Ch, std::size_t N>
array_adapter<Mode, Ch> resolve(Ch (&array)[N])
{ return array_adapter<Mode, Ch>(array); }

template<typename Mode, typename Ch, typename Iter>
range_adapter< Mode, boost::iterator_range<Iter> > 
resolve(const boost::iterator_range<Iter>& rng)
{ return range_adapter< Mode, boost::iterator_range<Iter> >(rng); }

# endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------//
#else // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //----------------//

template<typename Mode, typename Ch, typename T>
struct resolve_traits {
    // Note: test for is_iterator_range must come before test for output
    // iterator.
    typedef typename 
            iostreams::select<  // Disambiguation for Tru64.
                is_std_io<T>,
                mode_adapter<Mode, T>,
                is_iterator_range<T>,
                range_adapter<Mode, T>,
                is_dereferenceable<T>,
                output_iterator_adapter<Mode, Ch, T>,
                is_array<T>,
                array_adapter<Mode, T>,
                else_,
                #if !BOOST_WORKAROUND(__BORLANDC__, < 0x600)
                    const T&
                #else
                    T
                #endif
            >::type type;
};

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(const T& t, mpl::true_)
{   // Bad overload resolution.
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(wrap(const_cast<T&>(t)));
}

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(const T& t, mpl::false_)
{ 
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(t);
}

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(const T& t BOOST_IOSTREAMS_DISABLE_IF_STREAM(T))
{ return resolve<Mode, Ch>(t, is_std_io<T>()); }

# if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) && \
     !defined(__GNUC__) // ---------------------------------------------------//

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(T& t, mpl::true_)
{ 
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(wrap(t));
}

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(T& t, mpl::false_)
{ 
    typedef typename resolve_traits<Mode, Ch, T>::type return_type;
    return return_type(t);
}

template<typename Mode, typename Ch, typename T>
typename resolve_traits<Mode, Ch, T>::type 
resolve(T& t BOOST_IOSTREAMS_ENABLE_IF_STREAM(T))
{ return resolve<Mode, Ch>(t, is_std_io<T>()); }

# endif // Borland 5.x or GCC //--------------------------------//
#endif // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //---------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // VC7.1 4224.

#endif // BOOST_IOSTREAMS_DETAIL_RESOLVE_HPP_INCLUDED

/* resolve.hpp
PwEuhRPhMjgfLoeXwRXwClgKt8CV8KfwEvgQXA1fgJfCFyG6qh50NfwMVvD/EbgWfgmvhT4CuB6mwetgF3i93r9NxtvAJBUP7/3vKuPUqzLomfbJ2xmnXrVDr7/fe/+7/XHq1Tj0lvgi9c516NXGqWcNiU8vJU69zDj1cuLUy61Hr1tSfPvz7aqI3qNv9prIffqKOa5EHPv1kRnZTw0J79k3eq15376Ctd57923g2jbkJSS8j9/RtVy7JrSfXyaM3tMPcj68r9/qayL39tvK8S7kVeQIMmodeoh7z791nHPu97djXeSefzuRtGuJK8ejYQHi3PtvNcebEfcegNs5txHug+69AA9yzrkf4BGYsV7vB6j3ASzg3Gi4GlYiBWNwCx5EZx8M7wuYcV3d3oCjruP8buwPZZ9AVQnZgoT3C9xzXd2egUevq3/fwFEbCDeykeMKGN47cMuG6P0D93NuBzwEj3AueD1h5bg/NO0lmHd9fPsJbkbvVeQQ4txbMO0G/LbdgofhLs4V2OdgJWSfwYT2GKy+IfY+g+/cEHufwZwb6/YaPOtGdJFtSMa56EHTvoM1Nya292CLjaH9B/vDFrOxF+wDy+FGJLwX4U77GL4KTXsSZmzCX5gD93EuH65G3uHvLdC5T+FOjqvgAWjNwVawmuPMmwgHx+Ohc+/Cco6d+xfu4LjF/CQrB8lHKpBtyF7kHSRYwP6ESB5SgmxGqpGDSNoC9iZECpENyA5kH1KLJC9MsvojZyElyBakGjmIpC1iP0RkNnIFsh15CTmCZBayF2Jh0x6HTb+mX2N/39r+f/bMrGO0/9+PMugvkbUjqn0yIQ0Jr2+0xR7vHqRu5dhDLEemhqmJhrg4H6fjXcsHt/Q6ICOVbrmeA7pOXTvFyjbujaTv1XO+DsoahCelJ7oHmKw9IeOnRqpz5ZHraARkwhii+pLse7FFjcsWw8QWMp0/Lhvghh4r9kEHdGXPLVOcnbrlVkiXeQrGsXWi67luw0F1/XTawz49NywXvUGpIRuOTWBumGluInHhHHFxr00nYca+Oq/liMMn6bEY+J1NeJIi7Rs2r716eNHy8tByD3HmNdzS9hihdBetYGKfnvsyR13vZrK73Ct5TcYVlaY2PK+FbTRCnVPhiFjDZ7a8gvMkv01Hsuy5Gx72KFvGM7doQUm8tqh02OJRpcvN5jyHrjsflRVd7MhHW9T1SVjOZ4XnvI6S9T/vD631gJ0al5ceVecIo2u9q/xmlvrNQlojM5C7su2IECbHWmPaQHHah/t1uUQ+5lfinKsna3jinsMOXdU9J7Lait+ZT5QNrpZnKZhg/NvKXLfQs1QSUSYNlk0+9yB+5Ekkk7iXOOJOmbyspLjIGX1J85jjV3Ej/rm70boLSi80j/dF152Xli9cWl43d6xcXX/I6k2MHkTq1h5n6XHHvMjLld5Oqzv/bkfU3HDywsbmrKSNQ8ntLo9au2Aox604fknmnr3SXj3Dan3pFfxdgtjnL4f/NqzH1MIw/+zrZq75Z5JXvecRu8tCbOWac5LRMnpc8gzStaB59JwTNWY9zjTl/si9Ir3HrKPb8DHrpvif6BqDfRhW+LzG4nqPZe33Z/t8++5Fdw6acM3bB955+uPr+2ZedOzGmprH7nqPJTaPlfUeC20eq+w9ptc8Jjnxsbg/GWyfb7s/ecPi3m+N+eTJEY90XDZ5SWhsrSSqem6q4WrkYyQvXMeSOmAO0hwZL/oLuGxzIUyHi+BQWARz4FI4DF4Ix8px+Dtmjbg7Rdx1fsdcJv3LK6AqX2AyLIMnwtVwNLwUngpXwolwFZws5z+Gs8PvbXiS+KPWj3b0A9qcDVPhHJgGL4A=
*/