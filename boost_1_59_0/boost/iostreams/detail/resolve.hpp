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
                #if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600)
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

# if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600) && \
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
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
*/