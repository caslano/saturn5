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
iIiK5307+Xcz72Veinpey+rPlzc7Mzvl39nZKf9WH9XHf93xK73/T56Tm/eLvP8/aK8lddb/ewLfIePEvmnhHuf9X5k1rdBGF/71NfXYM614Tr88W+L8UEdzxIM0Exv9RVq6Zk3PziBzE3KmTAlpi22r8t/IbCswKM23lm8v7dxQ62L1dHfzWeoYizjftUwm8ftN6c4OvWb/Y+V/JGv9PKa0E1/g2ngPa+ON9gQ1v/Ww3eunXIuRh7hIdEz0OeHemEgyrJeBst/r/M6vhA05e7yh815nvKH8tcMLlZtKa4B9tXd8Zj0csdcpt0BbgtcF21dT/iJNZUUcP80mnG5Xd32Ylj5hHv5y3fSpT+UzTMY4nbpxrQB7dWzQMKaN8G49flZH+Z2Tk2WuR91vihr3ysuxjPsuXL/G+6IWzFPnI0zjZW7Y2m76cydm2Bor10rQ/CfY/itZvoHjUKpMXL0g77ipvLu2J8kjbuRRwsYH6VQSbglufJJG2VdzhUoTNo+aBX3PIsJcj4Vl6zEzuwr1WFiFeiysQj0WVlCPq8upx8Iq1mPhf2A93hGiHlOjzPVYpNXjPFraye7tWLl6LKpCPRZVoR6LKqjHLeXUY1EV67HoP7AenwxRjydqmOuxOLgeuR2rUo/FVajH4irUY3EF9fhGOfVYXMV6LP4PrMf3Q9RjTE2ZR+JkMrwN7j2dfTh7ddu583Ld3k8I+7nJsF2xHeZCj6lejzhl6PZ72AFpdye0+ZcflZ9VnnqksDZFFOmEI3VeT5Ze97iH3mNYF9ZRaVmA1Zww5afp6fKdBPFTC3Z41fbTyjoNP85+uQgVbplHn/+JlTmk9upcmnYu203nmercKE9963b6juPwr+1Dk+8mFAkfhgXIJuFmxNn3tQVx9nxtrevu+3JtffsrmD+a8Gr5/bkkvT+n1YH+HY0NohMNHPuT0qezXivViem/yazw3cJ67Zd5t3D21iZIyNeUP+bV7LShz6kl6SrZa53ntjv5udLnvEylMcOURgnr0fyV7n0cqs5NMrQ9pnCzTe0O/gz9fe09Z7I6f72p3dHDom+B+psAz1Lnn7YeJSdl9rbK3tUrlJ+Fxj2pSfBBdb6Bu3f2kPpd0907u0L9ztXDp+rhX1TnG5rCq/spT/1eJvOlwfsyzfsk28MO8v4SU55te/Sd64m+l+rOZWK7Xmzd81v75oD7e7a0odq7jT4v+m+0rWyeZws1Xxp6fnK5mneNGfnNgq9e97+Qu3DNwT2zj66v+vzqLzWPWtX5T/O8btXnRas6T2ue/6z6PKpu+/ghsX3cw7V9LGMvMN5gm7GOrPNPgHEwEdrh+iBFEq65hAtT858cMr/pkfnNmprNyF6wGewNXVuUEs9Ygy3KsyWeATAGngNbwUHwTDgY9oLD4FA4Ap4PR8JR8nuM/JZ08z4v+TWku7PktwuMhF1hlPyOk9+Orc5cJx6Drc5WEo9u07ewHP9Nxf/pmv+icvyniv/2mv/icvw3FP+nOf490neRPpdjD7uBjOflyvz4PNgAzoct4SbYGl4K28HLYGe4EPaAl8NB8AqYDq+EmXAxnAWvgovgEoioPZt3w2XwXrgKPgevh9/Cm6CXNK2F4fAWGA1vhfFwHawP74Dt4V2wF7wHDoYb4BR4H8yBD8B8uBEuhH+ES+GDcAV8CN4IH4a3wU1Q7hPpR1BGhvskWcr3FFgf1pNw693nJ8ElnHrvlnAXSDmPgbEwDbaFF8HucDzsDS+Gg+ElcBycAC+Bk+A8mAEL4RQpx+lwG5wJn4az4AswC74EL4R75HeuV9lGrXDtQfWe0nL3lIpN0v+MNQj/jj2lixqzxwvZhryDHEESmmDrExk=
*/