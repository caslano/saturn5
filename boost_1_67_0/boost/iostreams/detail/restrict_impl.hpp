/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        boost/iostreams/detail/restrict_impl.hpp
 * Date:        Sun Jan 06 12:57:30 MST 2008
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * If included with the macro BOOST_IOSTREAMS_RESTRICT undefined, defines the 
 * class template boost::iostreams::restriction. If included with the macro
 * BOOST_IOSTREAMS_RESTRICT defined as an identifier, defines the overloaded
 * function template boost::iostreams::BOOST_IOSTREAMS_RESTRICT, and object 
 * generator for boost::iostreams::restriction.
 *
 * This design allows <boost/iostreams/restrict.hpp> and 
 * <boost/iostreams/slice.hpp> to share an implementation.
 */

#if !defined(BOOST_IOSTREAMS_RESTRICT_IMPL_HPP_INCLUDED) && \
    !defined(BOOST_IOSTREAMS_RESTRICT)
# define BOOST_IOSTREAMS_RESTRICT_IMPL_HPP_INCLUDED
                    
//------------------Implementation of restriction-----------------------------//

# include <algorithm>          // min.
# include <utility>            // pair.
# include <boost/cstdint.hpp>  // intmax_t.
# include <boost/config.hpp>   // DEDUCED_TYPENAME.
# include <boost/iostreams/categories.hpp>
# include <boost/iostreams/char_traits.hpp>
# include <boost/iostreams/detail/adapter/device_adapter.hpp>
# include <boost/iostreams/detail/adapter/filter_adapter.hpp>
# include <boost/iostreams/detail/call_traits.hpp>
# include <boost/iostreams/detail/enable_if_stream.hpp>
# include <boost/iostreams/detail/error.hpp>
# include <boost/iostreams/detail/ios.hpp>     // failure.
# include <boost/iostreams/detail/select.hpp>
# include <boost/iostreams/operations.hpp>
# include <boost/iostreams/skip.hpp>
# include <boost/iostreams/traits.hpp>         // mode_of, is_direct.
# include <boost/mpl/bool.hpp>
# include <boost/static_assert.hpp>
# include <boost/throw_exception.hpp>
# include <boost/type_traits/is_convertible.hpp>

# include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

//
// Template name: restricted_indirect_device.
// Description: Provides an restricted view of an indirect Device.
// Template parameters:
//      Device - An indirect model of Device that models either Source or
//          SeekableDevice.
//
template<typename Device>
class restricted_indirect_device : public device_adapter<Device> {
private:
    typedef typename detail::param_type<Device>::type  param_type;
public:
    typedef typename char_type_of<Device>::type  char_type;
    typedef typename mode_of<Device>::type       mode;
    BOOST_STATIC_ASSERT(!(is_convertible<mode, detail::two_sequence>::value));
    struct category
        : mode,
          device_tag,
          closable_tag,
          flushable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    restricted_indirect_device( param_type dev, stream_offset off,
                                stream_offset len = -1 );
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek(stream_offset off, BOOST_IOS::seekdir way);
private:
    stream_offset beg_, pos_, end_;
};

//
// Template name: restricted_direct_device.
// Description: Provides an restricted view of a Direct Device.
// Template parameters:
//      Device - A model of Direct and Device.
//
template<typename Device>
class restricted_direct_device : public device_adapter<Device> {
public:
    typedef typename char_type_of<Device>::type  char_type;
    typedef std::pair<char_type*, char_type*>    pair_type;
    typedef typename mode_of<Device>::type       mode;
    BOOST_STATIC_ASSERT(!(is_convertible<mode, detail::two_sequence>::value));
    struct category
        : mode_of<Device>::type,
          device_tag,
          direct_tag,
          closable_tag,
          localizable_tag
        { };
    restricted_direct_device( const Device& dev, stream_offset off,
                              stream_offset len = -1 );
    pair_type input_sequence();
    pair_type output_sequence();
private:
    pair_type sequence(mpl::true_);
    pair_type sequence(mpl::false_);
    char_type *beg_, *end_;
};

//
// Template name: restricted_filter.
// Description: Provides an restricted view of a Filter.
// Template parameters:
//      Filter - An indirect model of Filter.
//
template<typename Filter>
class restricted_filter : public filter_adapter<Filter> {
public:
    typedef typename char_type_of<Filter>::type char_type;
    typedef typename mode_of<Filter>::type      mode;
    BOOST_STATIC_ASSERT(!(is_convertible<mode, detail::two_sequence>::value));
    struct category
        : mode,
          filter_tag,
          multichar_tag,
          closable_tag,
          localizable_tag,
          optimally_buffered_tag
        { };
    restricted_filter( const Filter& flt, stream_offset off, 
                       stream_offset len = -1 );

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!open_)
            open(src, BOOST_IOS::in);
        std::streamsize amt =
            end_ != -1 ?
                (std::min) (n, static_cast<std::streamsize>(end_ - pos_)) :
                n;
        std::streamsize result = 
            iostreams::read(this->component(), src, s, amt);
        if (result != -1)
            pos_ += result;
        return result;
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        if (!open_)
            open(snk, BOOST_IOS::out);
        if (end_ != -1 && pos_ + n >= end_) {
            if(pos_ < end_)
                pos_ += iostreams::write(this->component(),
                    snk, s, end_ - pos_);
            boost::throw_exception(bad_write());
        }
        std::streamsize result = 
            iostreams::write(this->component(), snk, s, n);
        pos_ += result;
        return result;
    }

    template<typename Device>
    std::streampos seek(Device& dev, stream_offset off, BOOST_IOS::seekdir way)
    {
        stream_offset next;
        if (way == BOOST_IOS::beg) {
            next = beg_ + off;
        } else if (way == BOOST_IOS::cur) {
            next = pos_ + off;
        } else if (end_ != -1) {
            next = end_ + off;
        } else {
            // Restriction is half-open; seek relative to the actual end.
            pos_ = this->component().seek(dev, off, BOOST_IOS::end);
            if (pos_ < beg_)
                boost::throw_exception(bad_seek());
            return offset_to_position(pos_ - beg_);
        }
        if (next < beg_ || (end_ != -1 && next >= end_))
            boost::throw_exception(bad_seek());
        pos_ = this->component().seek(dev, next, BOOST_IOS::cur);
        return offset_to_position(pos_ - beg_);
    }

    template<typename Device>
    void close(Device& dev) 
    { 
        open_ = false;
        detail::close_all(this->component(), dev); 
    }

    template<typename Device>
    void close(Device& dev, BOOST_IOS::openmode which) 
    { 
        open_ = false;
        iostreams::close(this->component(), dev, which); 
    }
private:
    template<typename Device>
    void open(Device& dev, BOOST_IOS::openmode which)
    {
        typedef typename is_convertible<mode, dual_use>::type is_dual_use;
        open_ = true;
        which = is_dual_use() ? which : (BOOST_IOS::in | BOOST_IOS::out);
        iostreams::skip(this->component(), dev, beg_, which);
    }

    stream_offset  beg_, pos_, end_;
    bool           open_;
};

template<typename T>
struct restriction_traits
    : iostreams::select<  // Disambiguation for Tru64.
          is_filter<T>,  restricted_filter<T>,
          is_direct<T>,  restricted_direct_device<T>,
          else_,         restricted_indirect_device<T>
      >
    { };

} // End namespace detail.

template<typename T>
struct restriction : public detail::restriction_traits<T>::type {
    typedef typename detail::param_type<T>::type          param_type;
    typedef typename detail::restriction_traits<T>::type  base_type;
    restriction(param_type t, stream_offset off, stream_offset len = -1)
        : base_type(t, off, len)
        { }
};

namespace detail {

//--------------Implementation of restricted_indirect_device------------------//

template<typename Device>
restricted_indirect_device<Device>::restricted_indirect_device
    (param_type dev, stream_offset off, stream_offset len)
    : device_adapter<Device>(dev), beg_(off), pos_(off), 
      end_(len != -1 ? off + len : -1)
{
    if (len < -1 || off < 0)
        boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad offset"));
    iostreams::skip(this->component(), off);
}

template<typename Device>
inline std::streamsize restricted_indirect_device<Device>::read
    (char_type* s, std::streamsize n)
{
    using namespace std;
    std::streamsize amt =
        end_ != -1 ?
            (std::min) (n, static_cast<std::streamsize>(end_ - pos_)) :
            n;
    std::streamsize result = iostreams::read(this->component(), s, amt);
    if (result != -1)
        pos_ += result;
    return result;
}

template<typename Device>
inline std::streamsize restricted_indirect_device<Device>::write
    (const char_type* s, std::streamsize n)
{
    if (end_ != -1 && pos_ + n >= end_) {
        if(pos_ < end_)
            pos_ += iostreams::write(this->component(), s, end_ - pos_);
        boost::throw_exception(bad_write());
    }
    std::streamsize result = iostreams::write(this->component(), s, n);
    pos_ += result;
    return result;
}

template<typename Device>
std::streampos restricted_indirect_device<Device>::seek
    (stream_offset off, BOOST_IOS::seekdir way)
{
    stream_offset next;
    if (way == BOOST_IOS::beg) {
        next = beg_ + off;
    } else if (way == BOOST_IOS::cur) {
        next = pos_ + off;
    } else if (end_ != -1) {
        next = end_ + off;
    } else {
        // Restriction is half-open; seek relative to the actual end.
        pos_ = iostreams::seek(this->component(), off, BOOST_IOS::end);
        if (pos_ < beg_)
            boost::throw_exception(bad_seek());
        return offset_to_position(pos_ - beg_);
    }
    if (next < beg_ || (end_ != -1 && next > end_))
        boost::throw_exception(bad_seek());
    pos_ = iostreams::seek(this->component(), next - pos_, BOOST_IOS::cur);
    return offset_to_position(pos_ - beg_);
}

//--------------Implementation of restricted_direct_device--------------------//

template<typename Device>
restricted_direct_device<Device>::restricted_direct_device
    (const Device& dev, stream_offset off, stream_offset len)
    : device_adapter<Device>(dev), beg_(0), end_(0)
{
    std::pair<char_type*, char_type*> seq =
        sequence(is_convertible<category, input>());
    if ( off < 0 || len < -1 || 
         (len != -1 && off + len > seq.second - seq.first) )
    {
        boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad offset"));
    }
    beg_ = seq.first + off;
    end_ = len != -1 ? 
        seq.first + off + len :
        seq.second;
}

template<typename Device>
typename restricted_direct_device<Device>::pair_type
restricted_direct_device<Device>::input_sequence()
{
    BOOST_STATIC_ASSERT((is_convertible<category, input>::value));
    return std::make_pair(beg_, end_);
}

template<typename Device>
typename restricted_direct_device<Device>::pair_type
restricted_direct_device<Device>::output_sequence()
{
    BOOST_STATIC_ASSERT((is_convertible<category, output>::value));
    return std::make_pair(beg_, end_);
}

template<typename Device>
typename restricted_direct_device<Device>::pair_type
restricted_direct_device<Device>::sequence(mpl::true_)
{ return iostreams::input_sequence(this->component()); }

template<typename Device>
typename restricted_direct_device<Device>::pair_type
restricted_direct_device<Device>::sequence(mpl::false_)
{ return iostreams::output_sequence(this->component()); }

//--------------Implementation of restricted_filter---------------------------//

template<typename Filter>
restricted_filter<Filter>::restricted_filter
    (const Filter& flt, stream_offset off, stream_offset len)
    : filter_adapter<Filter>(flt), beg_(off),
      pos_(off), end_(len != -1 ? off + len : -1), open_(false)
{
    if (len < -1 || off < 0)
        boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad offset"));
}

} // End namespace detail.

} } // End namespaces iostreams, boost.

#elif defined(BOOST_IOSTREAMS_RESTRICT)

namespace boost { namespace iostreams {

//--------------Implementation of restrict/slice------------------------------//

// Note: The following workarounds are patterned after resolve.hpp. It has not
// yet been confirmed that they are necessary.

# ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //------------------------//
#  ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //------------------------------//

template<typename T>
restriction<T> 
BOOST_IOSTREAMS_RESTRICT( const T& t, stream_offset off, stream_offset len = -1
                          BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return restriction<T>(t, off, len); }

template<typename Ch, typename Tr>
restriction< std::basic_streambuf<Ch, Tr> >
BOOST_IOSTREAMS_RESTRICT( std::basic_streambuf<Ch, Tr>& sb, stream_offset off, 
                          stream_offset len = -1 )
{ return restriction< std::basic_streambuf<Ch, Tr> >(sb, off, len); }

template<typename Ch, typename Tr>
restriction< std::basic_istream<Ch, Tr> >
BOOST_IOSTREAMS_RESTRICT
    (std::basic_istream<Ch, Tr>& is, stream_offset off, stream_offset len = -1)
{ return restriction< std::basic_istream<Ch, Tr> >(is, off, len); }

template<typename Ch, typename Tr>
restriction< std::basic_ostream<Ch, Tr> >
BOOST_IOSTREAMS_RESTRICT
    (std::basic_ostream<Ch, Tr>& os, stream_offset off, stream_offset len = -1)
{ return restriction< std::basic_ostream<Ch, Tr> >(os, off, len); }

template<typename Ch, typename Tr>
restriction< std::basic_iostream<Ch, Tr> >
BOOST_IOSTREAMS_RESTRICT
    (std::basic_iostream<Ch, Tr>& io, stream_offset off, stream_offset len = -1)
{ return restriction< std::basic_iostream<Ch, Tr> >(io, off, len); }

#  else // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------//

template<typename T>
restriction<T> 
BOOST_IOSTREAMS_RESTRICT( const T& t, stream_offset off, stream_offset len = -1
                          BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return restriction<T>(t, off, len); }

restriction<std::streambuf> 
BOOST_IOSTREAMS_RESTRICT
    (std::streambuf& sb, stream_offset off, stream_offset len = -1)
{ return restriction<std::streambuf>(sb, off, len); }

restriction<std::istream> 
BOOST_IOSTREAMS_RESTRICT
    (std::istream<Ch, Tr>& is, stream_offset off, stream_offset len = -1)
{ return restriction<std::istream>(is, off, len); }

restriction<std::ostream> 
BOOST_IOSTREAMS_RESTRICT
    (std::ostream<Ch, Tr>& os, stream_offset off, stream_offset len = -1)
{ return restriction<std::ostream>(os, off, len); }

restriction<std::iostream> 
BOOST_IOSTREAMS_RESTRICT
    (std::iostream<Ch, Tr>& io, stream_offset off, stream_offset len = -1)
{ return restriction<std::iostream>(io, off, len); }

#  endif // # ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-------------------//
# else // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //---------------//

template<typename T>
restriction<T> 
BOOST_IOSTREAMS_RESTRICT
    (const T& t, stream_offset off, stream_offset len, mpl::true_)
{   // Bad overload resolution.
    return restriction<T>(const_cast<T&>(t, off, len));
}

template<typename T>
restriction<T> 
BOOST_IOSTREAMS_RESTRICT
    (const T& t, stream_offset off, stream_offset len, mpl::false_)
{ return restriction<T>(t, off, len); }

template<typename T>
restriction<T> 
BOOST_IOSTREAMS_RESTRICT( const T& t, stream_offset off, stream_offset len = -1
                          BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) )
{ return BOOST_IOSTREAMS_RESTRICT(t, off, len, is_std_io<T>()); }

# if !BOOST_WORKAROUND(__BORLANDC__, < 0x600) && \
     !defined(__GNUC__) // ---------------------------------------------------//

template<typename T>
restriction<T>
BOOST_IOSTREAMS_RESTRICT(T& t, stream_offset off, stream_offset len = -1)
{ return restriction<T>(t, off, len); }

#  endif // Borland 5.x or GCC //-------------------------------//
# endif // #ifndef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION //--------------//

} } // End namespaces iostreams, boost.

# include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #if !defined(BOOST_IOSTREAMS_RESTRICT_IMPL_HPP_INCLUDED) ...

/* restrict_impl.hpp
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
*/