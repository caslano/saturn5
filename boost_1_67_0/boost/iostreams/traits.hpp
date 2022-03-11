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
sejOxqWZmqYQGoc2YgXEaxY7krxQ6wm4s244Rm1Y6QULD866bre/LHz5wj7gGzJa9rRuGtvK3lCM5wJlC/UZJQ7pIc4kP9ju7S9edKyhAaouWuXkDXf5VJzGmyuzk3J0SWlevocNxxaGehPaf0fZptwqKtTe4d5aNlKblcwQ3NzuLZmj0EDkRHoMb+sA1L3VuJIKlDl2p5R4dRNTinSH471p2Nxg2G5Q/d1Y/U5nFx6ZTfYE3uO41B8r4/GTHCIrATMMiEBr0qQp+s9BFIedEqpTcWHJVXavyWx/vA7SZHmWCxJ75iijh6LevTR1+XP/Oic4W9Ki3JnXSGIcKlmaeUOmuNEsdhUK0owAQZXOhVThL51WxVwlwC+A5A6pONhMLF8rLRvdFS4ppNOoaOLDWgt594nJLzUn2AeEeJdr3cBKQ9ibzJCh92EZKx4pLB2KPWuQcUsGKqqmoDHODVsG3iF8sbuXf0tgRUFa0NWXXC5Yv4YjdsSsEbtHGI+LjFxT/JzaMmcebzVlQT4ht8NjB1XmQ2lhrYr8hbNYof1QqDx0SuXWtcXohpdILeMDvSacpzr2Hvps8+XBNTblXu1H1wJ2ODGx4pQuiuTNE5Y/stpG1hAWn4NsEfyQP9R3M3ztmxTNq/TZM3m0M8t4s7MHetLt6XPS95Mv2Orh99nd5EuF2tefJY+dgffWtSkdeuXtq125rNYnkMvrkxPauOQXwnMJk+7TkIUtm8mCCkZ07nVPMZyr58jjWo8ZgXd+e6itC23L5RJ3P8H5xG0Ax74vJTZFnTGWVqUu/1HE8ad41ePmHEQMibpkwgscFaI+eJ7mByZfi8o3MFuHoKNtadd723Wr6L6KIO+sHKdnZCdzKzHmuve8+1GlRGJeSdvDNZ/1foWqO6WKcSBB6Xi+Z3/dkJl8FxEqixp1zaZfFmPOt+lWVS/mzpjNFFex/zXwYExb5ytbUpNrkWOh4mtraa2bR8J7Cvj12sZ5UfD9uTl0toXftAO8qdgi6cNzwf4ZSKLLMnYr2DqRfiGZl4MaC47+gIPYlZMpLRScp90A+sbihvSifZ1Y7EHCQqaBm78VvfaqO4fGjlFExqHbQm7v83p+YuEssrhINfhrlbatWt+kp/UhD6SzifHeBw4iRZqSKqJyK2COmlwE+tYHk3oijaeim9o/OPWS0MZ0jEZbyhOZUyAHlLqJ6VBHKjedWZaYxbb2bVv48znM+qElJ61T8wSsMVrr9z7FKQR8AGGgxBO5IXdFM+XzjJun23jQPHwm606pSvPOce3TyqRwmX2rEs+hQ/HsrppFyGr/syvKnedA49XjUppsQPuIm9UquTtUU0Mm0Xd2K7hU88RC6rYgF+QYYya3nxYaAspR9hBkmEHA4rGavRXdjPXA+XToKQswR05zzPMmVWPZA4nUBupLCQzcipEM1bDt2VAC7Yne8MrjpWJYS39DphHHVLk5WC1NpkCnQtiDwPZVB6XpWgEeRmIinUNFlWtcfYfBYoRAklI7qty5hmtYmggP89kwGCd6MoNwzMIaWEFtzhXm2mhJarfPg3ogpFdbW1IL3ILXRxWJJ9BcLY9PjmnleCchfneClycM48m6zQHV5DdI0++UJtZlh1gfXBcXhbIgJUxEJcJ75K74zBt5dg1ytvK8lmO2VOlnL8oavHRmVdyjwrF3pqeRWOcqrErL3a/poi6hy1XqxOy+px2ZBF0bznzJK0p3rav7yvotRvdgQwh7ceYLEa0SRc3Whaam9qBbFW2z6cphhH6IYdqXG8Me0fFx67JpBCbucoNaL6xcMCa2+uaeVTTcQAiRi+K6pyiAl3/WqIuy6Pa7QNPsdI/6PJ6pkWOwicnTMDB81SpdhTZMaavm0dLFdqnsPUKpC8OTg22liAxa9ZWdskzaJ7Wfs9jghsn1qTnyDO29ME7UrP4VpBfe1xyccQtjJ6G4M86GK3EDc5RInz22aK3Y81ZXd169+VQ83GzncTe0ND4PnKuf80l5u6NiunHfhcsdbPssgusgd/bEin/VYloNN+fNh36U4kZTSUD25d7kquuVVnDlgfrbSbTo45wyKFt5SfE0Zy/EazNTHLz3qfJjt7/sLMp/9M7vOfMywV11hNj3EH8dArAcUxSBi1HHbRdsOLcjtAMZ6/F5V/M9UIeNNCylBMOocDc2lrT7+76qL9TucTNyFPi/WTKPh5Y0IW29NkLqviT3Tskk6wldW4TpNdvhuvEt/ToWk1LrPJ6Wsohpqfcv/an3SZyaOBO2M5KUzcZhYXmXw6AXxoVJxJetTl+Iexr9F//Z1H4I7rOJBR3ziZ5viz4c6v4hCY1Uxl/K2n9t0QYo49Ji4WquOFTDzZJWEW36/tEIvjn/qAMvHTavGPcoyFaC8h+t/fjinQcBgQ0rHhZ7HkuALs373F0nijH308kpJPAev/dGzaoHKIkoHFB7mzfcdvaDc6zbq239UG9LwvuXUe/YIX8OECKxB7s6gdheWifJMIGMKpSSKUIMNQZnToxGIfCHp4M79BFHS3rRQgDPJ9snQkseaU0cisArr0NPnhY1RQBLQ/5JomhcKF6/6gu9BUZ+hhIDtWLDQuS1zlG//GQ9f3g5dQLMsv0GfpOVTwb3kq2noS16DjJgv7yK5Y8ybFbJLAFFFowv0sQh34Dl5W5Cp1911XzC4OpQNTjjA8y5zttzuvnYjuuXf/YcvCk+G3obHbrPRpKq76wARIydMjSqlhBgMp0Op0ivpAM6u9JjwmwU4b3MC6aPzuVvvPJ7y9hnds/dSqCSD4wa8tK8Dt6LItgadFTsBwV+r5hBFLUXVsIhbASte+MSvdCqpJQHL9KMfyLcqUdf/NxjGsCR2vTv7JuzT63vAvHGUMvx1YppJEWMBjQ/9yB+yxvrbXSHkjf72dnGfVu8otOUkjJ6HclJjtS+n/P4vaS4P+Bp5CTl/jgkk1bwUFTjmgHFk6t5RKnnnmuywTT1yEEZfacHeBUtUbmJDe5szIsa0Mg7pqmj+lomWSElYxbUeqzs7DyrOGeNrbLe9THI7T+W3KI7BQX3+nvRM23pfxBQctzt6BnWFM5v1akc17tvW9yZ1qevdci3dg/vrxrGLDK4YVdaabI2qjIEvvw0bJ8DnLl7rrGUa03ded74ZpLOyeDUsZpEqNspZyh1Q9OCK7+IsM6ot4rA9IVMX3DwMGpT1/1GP/Q/oeNc1KN5YG+oWo4YdJypOi8+cpHAQrZGAtoKa6ssAKtgJLbIkXyAedFBdbevIEuJwk+oVtQfx3m23GuQVfpM8b3fvGiLbcjWi3X2Lt5jIl4J6r+1B9E+HwYv9Cx7GjBV22BUliam5nvWH2wTpvBRFZooM6V36zf2h12ZSrQQbOC9DL3m9xg2Dar2lc1V8JI/jPAjeKR0+QasUDE6o+CahHqW3Cf9fH2PvZV5pwlK57j2Y+Tnt21/dtVC33vUBZiXT8qfeBXZuPAo+1jfgJwKAFK4kK62WuHzmq6khAxH+HxWRt7mZaeWD8mfxG3lp30xnyfqgJBnpBHabkjUjHLziw5THglNzqUcFSKPxHC8gCDwAV5FBq2bb2eM6xjlY8/+kyg7JiATAZKrO0R0kV00lT6pkmtJJSxpViUgTFO9iOtbiLsBQXENvkBwbUyYqnD5+njS3/UGgiYWAneUAb7QdhM4V3YCnbmnJ8cfKG2nMWG4LZc9UlPGZCOf0TCgQA70es7ypgjHfEnnPrVseUMqhYqF3MR/5VLkEpmxprltnHT24XhNf7bjuRbeL9xOtJi79tH1YVQG1lwyLUytuVsbnrhFuraqKXPGQ/fl0onfKtiEVhWKEY2/RkYQlBUNPJmr2jsJ6lI0UbJ/c5sOGI3RLR+RNtRQ9RktPVZ/Sdx1dYLDRRhsz7nz5+ibC1cXj9o6kjAzALOcfXK9VDM4tM3INqGoNGyoNtJwdAD28mHPKR1w6HranOYuSbDB1p38RHprGmDOp8381n3Z6qFFuC5GQwsEGj7ZyhxqbFJ1GuJOuXreJTlpEMFU7MhmUd8wQH2mPkhjZIO5erZJfLwa+7SsPfDG4vzg+scvC5Wn1KsBKNoTQ07Ixu1WqNi/XaDQI/Jh/Yandp+dAIZ/VbVhMayZwJ7vX9umQM/gnHqLc5TXeIc+d37yTmPZOVaruPZEDa5xLmk+SqlIV7n1ESZeRdLmWwEu39nlMFAzcrX5vi7FbgFVpKwftM0YijNfpDflx5EEqS6xkpN0KcsiH3hW7+5wmlZ4Ad3KG5UtzRa7q/FIskdpW7Jn5vHwxrCA3Xy1KANIQ2MO828+sFZ1v4by47d2WozDo/wJlYs7O1k2W79im4B+vasoyUd8JZ1F+Pbu8F0k+rIj8/7B4rnwmTeqIS8GZDaeIf1mdheO3V7DiLzsqnp/2fSjxM2Xy3rxxRVtJrZBdnU5dKmTvj3EAbOTdoo0eoePRgimrBuALyQIAjI1NxEO/aZosR2TrnGsfv6RaWGDtQAsOdks8gLqDHK1p7+xEewZkyUQAeJzVnIzCyxW1oG7el9aIDLRW7eU4Ytm+585H3q2+bl0697xtGu+HKXVi4ZaPD9yumppVgxbmlxUL415IMnr2QUcz9sGB7Cbb6yA9evonvdtVz93dynfWBu4fi7QJ29vWeSpNnTFDSBfGt3raa79qTfataxvheeQZNO7MLH1yi7J0htgyK7dDsqiPW9vsMQnS13CR9OD8u7i7dAP0DKEmxrP3AyQPJFXdRXUe92TWn/bvOGosru80yjp4g9zTNJLDFrMh0KM3BsCKwD5ARVVp1HMoQaUMvFklqHke3j/Ek045niHNXjXoD/dgJ0vGtFy82CT3356VufBjWAvClrp7sa4uZND+3juaJfDbRBeS64XYRScgs5zZ2wiYezL9Qxd8FDFScRm4rwn2o53XL4B+GBp7iKvF1ZoPU3Iwl7cgrG4ddJwVDqZXaRi/hPlzhAMAabM4JRhNMTYrDe6s0tkB26ldGDGDfFv8T+XORe7+0N1lKgD/jJ8egg+vX0EP9qCAJkTEslfbUhH0SSTnIy9wC8nnHByL1S3aWQ3hVxV7Xi8Dtc5w3lLBiHSCBXXcadFskWuI5KpqkQCHW8ClL7tW8Q288iLGdzt1hhh3l2QhVq6Oi1WXy5cEuCpCCxCoADGmHxdD/X/tOsSyku2Xwlrhc5C/HrD3KreL+49wO1R5PFKM3S9hUBgxO7M3mWiXktpC3xC+0wwx+icoeoPINORTNSnatammnyGT5EFgxKp7U0OXFwXbsJUL2xl+VWUg44JviE568jC2GI6Y3g0b9ZVRVFAJwNnN/EIyWLjPV/30MOM3Z5CDRZiek0XB+7dSrUUd7t+ns7k+1sfkC9b3wq7f9fThJocTogy3O3mFXLCqokJIaCtIsBXneF9rK/58+mQgiHVhUegkeaSXdyb2CWSRB3wKDeThb4IR5bX/zvneoc9zgmVpqPQaa09nsCBde1bWG/SEkRxDADgfjaUrQLCD7soHrP9RQ3TKVn2vCGx7az/SqpqD6txpQzcE0B8dKKXK1w0SB9IOKwbUnwkE+37YGdPqSBV4m1rdUAztiPQ7eGl7TFpb5krHeWaO2Hz6lY31VamBehA784iw+S4A66gabh+Sl8I+FHlxLIPx22h5qH9r/2gsVEtDNtAJfZZwYpYBJdFjwL/ktYGmc+Dg4zUCaerYpegkAR7vLlF9HeTtT4HyjigUJdaGtcktheA2PWpTZx+udJ23FQz6/bTD/EzsXmCeiC8NzRGGclSHDSaZZGJCZZf8WkdD2C2aBVAEjPHQ0+Nvzb+iP1Snl5phPgZmiNWAv7Y0d5sXI8E4qwnjctO0IbkKoBO6oktbAqha/2BYOW+ZkUXqSxsSOZ9sDXedZjdASf5YBB1a1uxeZXtLZMo5CD2WCKmFj+nhC+GqqmmZVx2rQYSt0pFKSE5/o1sRvrWakGTh3fRhujGFcwkrlMSI5wN06lIJbUmfN3CX1+TqZJoFUnMVwwTi15FIdveFgkglHP1tJduvm5YIcnIk400AfN10Gfn2brqtePhvxzB2VjOwTe94jM5DawJKSmPWz5t7kEwV4iylE3xEFQQGDudi07FnRAFXuRq8e38b1/647ScvUNBVup5nuCTxkRbj8cuAx0OR4JLbYhs5XVmW+6KnCKCti62WreXukcx5fDXPlJdt6/5HCH13Pl1VXOVf5dAP49kjM+DpUf5drYWszNQ+fA2bwo6rNBqtp2KHvPDQkTNPS5pr+23S20XDfmIe8Vv00aTKt06Kjtex/UV4/RsKX19KN/x4PryfHpYcyoGGU88dCh9qou01xG5dwkw+5vvgB1uBwq5C1XY5uw8anWyFORD9MSl9nma26r6b5K47aPRryEuBHJHstUNUhWJVRVdXmDkk6rkZw9r5s4gpm5D73rJPCNXJuQ0IZUXyJRah8QB64R2775HEXuPLEUk5MWchwKMua7wDmQbnquh59ZaKH1EW6FhJLeRsfUO8tKylCbdPyO0Psq7Tlp6GE7rO+lwlsysm/yQ24DX433kv9ycFjv9gJRFspKgVMLK1bbNjNuc5t1Dy6Bk3DW3cpmC6kvZeRKL6gvbbFfZ7VH7kYyVvrhngL8NQs0sLBfHDjcXWUT4spFw9rokMsiGaQaRusxU6TDM+rGHWIDxtsuH5aptOE0FaunC/XNVMwDhzraDXVe57MzwAALer9ZLo4uAwP9Ou6YRTBrecxSyZ7qDNN8/N5iWr7b0jto9gdpau15AIu9Ib/PuwCFqZ+QZ03fCWTyXy+QTRaIgtMEbp3Sl3vpZrgVRen80Xrq3WJfDj6UeKxymzPemCDq0Nqmuxkc2OhAUIKyDnfLfiPyQCeDgUhvzHYF2iS5aD2OembQioBqUWovGlzE5bj0YpvBB9fvFLlkkfgkHnZLe+L/+HrNL8CXIX3lgYXuq7l3Zt1utSOFeG7TrBe7vvnZIcVSXS1Gbmkyav6GEv+5sOQvTCQYXAZGY3M/AddWie38jq5NZQ7/7Ui9rzQ8ckg1RLMJer9v72bGYOJK7rRlLzDWJ/su5r9+f8vH7vYw/7NP+mHSKw8laFrccy3ZzhQXZibObJqUZBoVSIMv2LBtp8yrm77ZydGbS/mkSAmKU2PcpKagurCp2musFk/Nz8EKf5fDff+kKMmAC0uQLBqAOREu4R9Buoe/lB1djMjSTW9DPBpaGpORllMqYiAFqs0NX9qP8qBZpw4xvH2Mx1q60FyVjXUM0UXVLkDnMm+z328rA1Rz4CwQIqwK344WsuKnAdElZ2/3Nobs3fpO020tjTPsnu+dw9KaXAVac92jlVAi9sEzuz5+jKnX/ULBKzRBiJXSeYjqt6BKZ3EgRZIBxZrBNXxu1fIHBJ5cxM8lc+4ST3GoLx5xRDblk2Ix69wJPthyIhTJXTmelBBLf0yG1XGM40lrmAgk2mb4CO/J8bWirRcpaTdyZ3Y/SHzXM50LN5AueirUqZPHnKK7EsvAZK0x42EICI5/EOfCQwskURL3Kfd3P9OPc0bcn5G1qNA1z9rnDuBo0kJ9MbtlxjqmcLS3kD/HnP0TW2zSeyALGFIcMaS9ZZhb7G1KmRQz0zkqeGBPfEKzVWonQv9Ye2zvuD02Rlx4siuqFIgr+k7/QZL9PcdhPeq2uU3m2aUqgVBZVrPiFWBUAMDq1OWk9FGfd1c+rsyUOHi9jnBF/Hy5MCDdCvWy5B8n/fAnznhmHuJcqBM7m8s0pEJl6qRIJdU9d4DfCDGyA4igut2m5AWicSmJ1RCe5kabIF7my+gGgCIMek6ifSv3KSsA1Vrkff2lXJKhs5W50zToYxx3Oxz07uX52T/ONadDWCEBQcOBUH+exDr3cxe+LBRTtP31+XRWRKqQOk919WjyO7ff0eQIruwuH4Kbe5ql4ghC/DFKp68HCb35hk+X9PSdAvq+BRroTUiV9+2wtQs3eWJwuWWWzA7yOxtmgn6Ui1b4n4Rw5S8I1FLW9w8A+2C89/KrhI6938JHHtrYdpVItfYSATHtvBTl4fuITAyWxufHCNvS/U/8Kg3ts6W8dG0nFi9Wwsh0nDDiP5cE9/az+LblY/iD4wHT2hD6/HehM+5UmQm4MHuie0LuGANM5AAQs+9Ou9fOT4mkDIQFzWdJ+GGFXzb4RWB/eflaudv5H3jps31tC23uTBaMWAGUZ2ny9aOIFhUu/u+WqGiG9+4E20Ww2sCJ8dBT3H2U/3ZwdODUNhXZGFapBjCHHYHVZFZvHx1RQ/AlRo/a5kHUD/a7RHCWGNztNorw4yWEX+Ql7C4IwzAAkzJXrk7yv3zAlGglZvjIjk2Iwis7W2LJNgEdIPMldPPXqgxuUdai7ezqukbigRxvddMfxdnu7Ozo+h2LtFm1VSuLjLmA1M/ENJOf5z1CfRAjWgNlQufslYqMJlD2hjeT4QDmnwOzLe/sb53x3+nfdhqTXt1cgEKFq1zp3zovF94ChzYl/fIs1e23Q2C+Jn/ZtebV0EwNyRSl4XNTcjsnC9eyc7LfB4egBc1MmdwnrUZPpNoaf87bLQbe/c8/0OW7u628gEd8HQrZV5EBRL9XtueFOz3gLZd7dipsKjWKwOCo5hX1ep4hOAHfdmsxwoKK9CIEKL6Jwe2y3Z2B6jKddNfGjrQK+pcTAvv+HRZbRxaLTcB6ZBuB9cY8UcWAaffGDWWVGRj0Xz1aRiLJSCI0Sy6vCoSC7k4Opi1IAhrF+WogZhRZ9QROOgHAfqOig4yTmsMgc32LjG4neKjIdb0VNzmrHXB86zUV2cQYkRvf4keQxHFYlavTIVQ6eJy3qYDwEc8evYECxHild3x2oxfkGppW8/+FN6hPsqMZ4V7w9UEQEVvx2rohAE+IFQul3PBa1iyFaEtbd7PMVpeaHU5YPBogo6wlJ3TbeFHOhmBP+ncBbPpZL5dFKMPr11w9IctCSm7lOEmrDsmNjcr1g8WBXFwZ0xMYAbVc1AE1xsvacErf/i87cTehTdYK7yKWVeVtjyVZW2dyLXzIBQSIhtBsrz8V1F17uPLud8n/HPrHT9owo6xUxLD8TJ90llV8ejf+OE5ahEYDB6yydBHItVPozu8fknKXFKXQCGeEU5ipm9WRVF7lkWTEKLMdR+di5L7vuZISKPCLg+EEMr4ht+IBitoaklweXlxDKPXw=
*/