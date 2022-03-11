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
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
*/