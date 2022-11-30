// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// To do: add support for random-access.

#ifndef BOOST_IOSTREAMS_COMBINE_HPP_INCLUDED
#define BOOST_IOSTREAMS_COMBINE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp> // NO_STD_LOCALE, DEDUCED_TYPENAME.
#ifndef BOOST_NO_STD_LOCALE
# include <locale>
#endif
#include <boost/iostreams/detail/ios.hpp>   
#include <boost/iostreams/detail/wrap_unwrap.hpp>       
#include <boost/iostreams/traits.hpp>         
#include <boost/iostreams/operations.hpp>        
#include <boost/mpl/if.hpp>    
#include <boost/static_assert.hpp>  
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp> 

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

//
// Template name: combined_device.
// Description: Model of Device defined in terms of a Source/Sink pair.
// Template parameters:
//      Source - A model of Source, with the same char_type and traits_type
//          as Sink.
//      Sink - A model of Sink, with the same char_type and traits_type
//          as Source.
//
template<typename Source, typename Sink>
class combined_device {
private:
    typedef typename category_of<Source>::type  in_category;
    typedef typename category_of<Sink>::type    out_category;
    typedef typename char_type_of<Sink>::type   sink_char_type;
public:
    typedef typename char_type_of<Source>::type char_type;
    struct category
        : bidirectional, 
          device_tag, 
          closable_tag, 
          localizable_tag
        { };
    BOOST_STATIC_ASSERT(is_device<Source>::value);
    BOOST_STATIC_ASSERT(is_device<Sink>::value);
    BOOST_STATIC_ASSERT((is_convertible<in_category, input>::value));
    BOOST_STATIC_ASSERT((is_convertible<out_category, output>::value));
    BOOST_STATIC_ASSERT((is_same<char_type, sink_char_type>::value));
    combined_device(const Source& src, const Sink& snk);
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    void close(BOOST_IOS::openmode);
    #ifndef BOOST_NO_STD_LOCALE
        void imbue(const std::locale& loc);
    #endif
private:
    Source  src_;
    Sink    sink_;
};

//
// Template name: combined_filter.
// Description: Model of Device defined in terms of a Source/Sink pair.
// Template parameters:
//      InputFilter - A model of InputFilter, with the same char_type as 
//          OutputFilter.
//      OutputFilter - A model of OutputFilter, with the same char_type as 
//          InputFilter.
//
template<typename InputFilter, typename OutputFilter>
class combined_filter {
private:
    typedef typename category_of<InputFilter>::type    in_category;
    typedef typename category_of<OutputFilter>::type   out_category;
    typedef typename char_type_of<OutputFilter>::type  output_char_type;
public:
    typedef typename char_type_of<InputFilter>::type   char_type;
    struct category 
        : multichar_bidirectional_filter_tag,
          closable_tag, 
          localizable_tag
        { };
    BOOST_STATIC_ASSERT(is_filter<InputFilter>::value);
    BOOST_STATIC_ASSERT(is_filter<OutputFilter>::value);
    BOOST_STATIC_ASSERT((is_convertible<in_category, input>::value));
    BOOST_STATIC_ASSERT((is_convertible<out_category, output>::value));
    BOOST_STATIC_ASSERT((is_same<char_type, output_char_type>::value));
    combined_filter(const InputFilter& in, const OutputFilter& out);

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    { return boost::iostreams::read(in_, src, s, n); }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    { return boost::iostreams::write(out_, snk, s, n); }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::in) {
            if (is_convertible<in_category, dual_use>::value) {
                iostreams::close(in_, snk, BOOST_IOS::in);
            } else {
                detail::close_all(in_, snk);
            }
        }
        if (which == BOOST_IOS::out) {
            if (is_convertible<out_category, dual_use>::value) {
                iostreams::close(out_, snk, BOOST_IOS::out);
            } else {
                detail::close_all(out_, snk);
            }
        }
    }
    #ifndef BOOST_NO_STD_LOCALE
        void imbue(const std::locale& loc);
    #endif
private:
    InputFilter   in_;
    OutputFilter  out_;
};

template<typename In, typename Out>
struct combination_traits 
    : mpl::if_<
          is_device<In>,
          combined_device<
              typename wrapped_type<In>::type,
              typename wrapped_type<Out>::type
          >,
          combined_filter<
              typename wrapped_type<In>::type,
              typename wrapped_type<Out>::type
          >
      >
    { };

} // End namespace detail.

template<typename In, typename Out>
struct combination : detail::combination_traits<In, Out>::type {
    typedef typename detail::combination_traits<In, Out>::type  base_type;
    typedef typename detail::wrapped_type<In>::type          in_type;
    typedef typename detail::wrapped_type<Out>::type         out_type;
    combination(const in_type& in, const out_type& out)
        : base_type(in, out) { }
};

namespace detail {

// Workaround for VC6 ETI bug.
template<typename In, typename Out>
struct combine_traits {
    typedef combination<
                BOOST_DEDUCED_TYPENAME detail::unwrapped_type<In>::type, 
                BOOST_DEDUCED_TYPENAME detail::unwrapped_type<Out>::type
            > type;
};

} // End namespace detail.

//
// Template name: combine.
// Description: Takes a Source/Sink pair or InputFilter/OutputFilter pair and
//      returns a Source or Filter which performs input using the first member
//      of the pair and output using the second member of the pair.
// Template parameters:
//      In - A model of Source or InputFilter, with the same char_type as Out.
//      Out - A model of Sink or OutputFilter, with the same char_type as In.
//
template<typename In, typename Out>
typename detail::combine_traits<In, Out>::type
combine(const In& in, const Out& out) 
{ 
    typedef typename detail::combine_traits<In, Out>::type return_type;
    return return_type(in, out); 
}

//----------------------------------------------------------------------------//

namespace detail {

//--------------Implementation of combined_device-----------------------------//

template<typename Source, typename Sink>
inline combined_device<Source, Sink>::combined_device
    (const Source& src, const Sink& snk)
    : src_(src), sink_(snk) { }

template<typename Source, typename Sink>
inline std::streamsize
combined_device<Source, Sink>::read(char_type* s, std::streamsize n)
{ return iostreams::read(src_, s, n); }

template<typename Source, typename Sink>
inline std::streamsize
combined_device<Source, Sink>::write(const char_type* s, std::streamsize n)
{ return iostreams::write(sink_, s, n); }

template<typename Source, typename Sink>
inline void
combined_device<Source, Sink>::close(BOOST_IOS::openmode which)
{ 
    if (which == BOOST_IOS::in)
        detail::close_all(src_); 
    if (which == BOOST_IOS::out)
        detail::close_all(sink_); 
}

#ifndef BOOST_NO_STD_LOCALE
    template<typename Source, typename Sink>
    void combined_device<Source, Sink>::imbue(const std::locale& loc)
    {
        iostreams::imbue(src_, loc);
        iostreams::imbue(sink_, loc);
    }
#endif

//--------------Implementation of filter_pair---------------------------------//

template<typename InputFilter, typename OutputFilter>
inline combined_filter<InputFilter, OutputFilter>::combined_filter
    (const InputFilter& in, const OutputFilter& out) : in_(in), out_(out)
    { }

#ifndef BOOST_NO_STD_LOCALE
    template<typename InputFilter, typename OutputFilter>
    void combined_filter<InputFilter, OutputFilter>::imbue
        (const std::locale& loc)
    {
        iostreams::imbue(in_, loc);
        iostreams::imbue(out_, loc);
    }
#endif


} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_COMBINE_HPP_INCLUDED

/* combine.hpp
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
*/