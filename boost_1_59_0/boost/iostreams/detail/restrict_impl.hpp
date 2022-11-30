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

# if !BOOST_WORKAROUND(BOOST_BORLANDC, < 0x600) && \
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