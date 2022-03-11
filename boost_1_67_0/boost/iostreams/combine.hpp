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