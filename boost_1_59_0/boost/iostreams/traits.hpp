// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// 
// Contains metafunctions char_type_of, category_of and mode_of used for
// deducing the i/o category and i/o mode of a model of Filter or Device.
//
// Also contains several utility metafunctions, functions and macros.
//

#ifndef BOOST_IOSTREAMS_IO_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_IO_TRAITS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <iosfwd>            // stream types, char_traits.
#include <boost/config.hpp>  // partial spec, deduced typename.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/bool_trait_def.hpp> 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/is_iterator_range.hpp>    
#include <boost/iostreams/detail/select.hpp>        
#include <boost/iostreams/detail/select_by_size.hpp>      
#include <boost/iostreams/detail/wrap_unwrap.hpp>       
#include <boost/iostreams/traits_fwd.hpp> 
#include <boost/mpl/bool.hpp>   
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>      
#include <boost/mpl/int.hpp>  
#include <boost/mpl/or.hpp>                 
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

//----------Definitions of predicates for streams and stream buffers----------//

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------------------//

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_istream, std::basic_istream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ostream, std::basic_ostream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iostream, std::basic_iostream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_streambuf, std::basic_streambuf, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ifstream, std::basic_ifstream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ofstream, std::basic_ofstream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_fstream, std::basic_fstream, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_filebuf, std::basic_filebuf, 2)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_istringstream, std::basic_istringstream, 3)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ostringstream, std::basic_ostringstream, 3)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_stringstream, std::basic_stringstream, 3)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_stringbuf, std::basic_stringbuf, 3)

#else // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-----------------------//

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_istream, std::istream, 0)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_ostream, std::ostream, 0)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iostream, std::iostream, 0)
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_streambuf, std::streambuf, 0)

#endif // #ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //----------------------//

template<typename T>
struct is_std_io
    : mpl::or_< is_istream<T>, is_ostream<T>, is_streambuf<T> >
    { };

template<typename T>
struct is_std_file_device
    : mpl::or_< 
          is_ifstream<T>, 
          is_ofstream<T>, 
          is_fstream<T>, 
          is_filebuf<T>
      >
    { };

template<typename T>
struct is_std_string_device
    : mpl::or_< 
          is_istringstream<T>, 
          is_ostringstream<T>, 
          is_stringstream<T>, 
          is_stringbuf<T>
      >
    { };

template<typename Device, typename Tr, typename Alloc>
struct stream;

template<typename T, typename Tr, typename Alloc, typename Mode>
class stream_buffer;

template< typename Mode, typename Ch, typename Tr, 
          typename Alloc, typename Access >
class filtering_stream;

template< typename Mode, typename Ch, typename Tr, 
          typename Alloc, typename Access >
class wfiltering_stream;

template< typename Mode, typename Ch, typename Tr, 
          typename Alloc, typename Access >
class filtering_streambuf;

template< typename Mode, typename Ch, typename Tr, 
          typename Alloc, typename Access >
class filtering_wstreambuf;

namespace detail {

template<typename T, typename Tr>
class linked_streambuf;

BOOST_IOSTREAMS_BOOL_TRAIT_DEF( is_boost_stream,
                                boost::iostreams::stream,
                                3 )
BOOST_IOSTREAMS_BOOL_TRAIT_DEF( is_boost_stream_buffer,
                                boost::iostreams::stream_buffer,
                                4 )
BOOST_IOSTREAMS_BOOL_TRAIT_DEF( is_filtering_stream_impl,
                                boost::iostreams::filtering_stream,
                                5 )
BOOST_IOSTREAMS_BOOL_TRAIT_DEF( is_filtering_wstream_impl,
                                boost::iostreams::wfiltering_stream,
                                5 )
BOOST_IOSTREAMS_BOOL_TRAIT_DEF( is_filtering_streambuf_impl,
                                boost::iostreams::filtering_streambuf,
                                5 )
BOOST_IOSTREAMS_BOOL_TRAIT_DEF( is_filtering_wstreambuf_impl,
                                boost::iostreams::filtering_wstreambuf,
                                5 )
BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_linked, linked_streambuf, 2)

template<typename T>
struct is_filtering_stream
    : mpl::or_<
          is_filtering_stream_impl<T>,
          is_filtering_wstream_impl<T>
      >
    { };

template<typename T>
struct is_filtering_streambuf
    : mpl::or_<
          is_filtering_streambuf_impl<T>,
          is_filtering_wstreambuf_impl<T>
      >
    { };

template<typename T>
struct is_boost
    : mpl::or_<
          is_boost_stream<T>, 
          is_boost_stream_buffer<T>, 
          is_filtering_stream<T>, 
          is_filtering_streambuf<T>
      >
    { };

} // End namespace detail.
                    
//------------------Definitions of char_type_of-------------------------------//

namespace detail {

template<typename T>
struct member_char_type { typedef typename T::char_type type; };

} // End namespace detail.

# ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-------------------------------//

template<typename T>
struct char_type_of 
    : detail::member_char_type<
          typename detail::unwrapped_type<T>::type
      > 
    { };

# else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //---------------------//

template<typename T>
struct char_type_of {
    typedef typename detail::unwrapped_type<T>::type U;
    typedef typename 
            mpl::eval_if<
                is_std_io<U>,
                mpl::identity<char>,
                detail::member_char_type<U>
            >::type type;
};

# endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------//

template<typename Iter>
struct char_type_of< iterator_range<Iter> > {
    typedef typename iterator_value<Iter>::type type;
};


//------------------Definitions of category_of--------------------------------//

namespace detail {

template<typename T>
struct member_category { typedef typename T::category type; };

} // End namespace detail.

template<typename T>
struct category_of {
    template<typename U>
    struct member_category { 
        typedef typename U::category type; 
    };
    typedef typename detail::unwrapped_type<T>::type U;
    typedef typename  
            mpl::eval_if<
                mpl::and_<
                    is_std_io<U>,
                    mpl::not_< detail::is_boost<U> >
                >,
                iostreams::select<  // Disambiguation for Tru64
                    is_filebuf<U>,        filebuf_tag,
                    is_ifstream<U>,       ifstream_tag,
                    is_ofstream<U>,       ofstream_tag,
                    is_fstream<U>,        fstream_tag,
                    is_stringbuf<U>,      stringbuf_tag,
                    is_istringstream<U>,  istringstream_tag,
                    is_ostringstream<U>,  ostringstream_tag,
                    is_stringstream<U>,   stringstream_tag,
                    is_streambuf<U>,      generic_streambuf_tag,
                    is_iostream<U>,       generic_iostream_tag,
                    is_istream<U>,        generic_istream_tag, 
                    is_ostream<U>,        generic_ostream_tag
                >,
                detail::member_category<U>
            >::type type;
};

// Partial specialization for reference wrappers

template<typename T>
struct category_of< reference_wrapper<T> >
    : category_of<T>
    { };


//------------------Definition of get_category--------------------------------//

// 
// Returns an object of type category_of<T>::type.
// 
template<typename T>
inline typename category_of<T>::type get_category(const T&) 
{ typedef typename category_of<T>::type category; return category(); }

//------------------Definition of int_type_of---------------------------------//

template<typename T>
struct int_type_of { 
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
    typedef std::char_traits<
                BOOST_DEDUCED_TYPENAME char_type_of<T>::type
            > traits_type;      
    typedef typename traits_type::int_type type; 
#else  
    typedef int                            type; 
#endif
};

//------------------Definition of mode_of-------------------------------------//

namespace detail {

template<int N> struct io_mode_impl;

#define BOOST_IOSTREAMS_MODE_HELPER(tag_, id_) \
    case_<id_> io_mode_impl_helper(tag_); \
    template<> struct io_mode_impl<id_> { typedef tag_ type; }; \
    /**/
BOOST_IOSTREAMS_MODE_HELPER(input, 1)
BOOST_IOSTREAMS_MODE_HELPER(output, 2)
BOOST_IOSTREAMS_MODE_HELPER(bidirectional, 3)
BOOST_IOSTREAMS_MODE_HELPER(input_seekable, 4)
BOOST_IOSTREAMS_MODE_HELPER(output_seekable, 5)
BOOST_IOSTREAMS_MODE_HELPER(seekable, 6)
BOOST_IOSTREAMS_MODE_HELPER(dual_seekable, 7)
BOOST_IOSTREAMS_MODE_HELPER(bidirectional_seekable, 8)
BOOST_IOSTREAMS_MODE_HELPER(dual_use, 9)
#undef BOOST_IOSTREAMS_MODE_HELPER

template<typename T>
struct io_mode_id {
    typedef typename category_of<T>::type category;
    BOOST_SELECT_BY_SIZE(int, value, detail::io_mode_impl_helper(category()));
};

} // End namespace detail.

template<typename T> // Borland 5.6.4 requires this circumlocution.
struct mode_of : detail::io_mode_impl< detail::io_mode_id<T>::value > { };

// Partial specialization for reference wrappers

template<typename T>
struct mode_of< reference_wrapper<T> >
    : mode_of<T>
    { };

                    
//------------------Definition of is_device, is_filter and is_direct----------//

namespace detail {

template<typename T, typename Tag>
struct has_trait_impl {
    typedef typename category_of<T>::type category;
    BOOST_STATIC_CONSTANT(bool, value = (is_convertible<category, Tag>::value));
};

template<typename T, typename Tag>
struct has_trait 
    : mpl::bool_<has_trait_impl<T, Tag>::value>
    { }; 

} // End namespace detail.

template<typename T>
struct is_device : detail::has_trait<T, device_tag> { };

template<typename T>
struct is_filter : detail::has_trait<T, filter_tag> { };

template<typename T>
struct is_direct : detail::has_trait<T, direct_tag> { };
                    
//------------------Definition of BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS----------//

#define BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
    typedef Tr                              traits_type; \
    typedef typename traits_type::int_type  int_type; \
    typedef typename traits_type::off_type  off_type; \
    typedef typename traits_type::pos_type  pos_type; \
    /**/

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_IO_TRAITS_HPP_INCLUDED

/* traits.hpp
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
*/