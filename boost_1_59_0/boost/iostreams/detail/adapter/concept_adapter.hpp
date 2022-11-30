// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONCEPT_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONCEPT_ADAPTER_HPP_INCLUDED

#include <boost/config.hpp>                             // SFINAE.
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/adapter/non_blocking_adapter.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/streambuf.hpp>        // pubsync.
#include <boost/iostreams/detail/config/unreachable_return.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.


namespace boost { namespace iostreams { namespace detail {

template<typename Category> struct device_wrapper_impl;
template<typename Category> struct flt_wrapper_impl;

template<typename T>
class concept_adapter {
private:
    typedef typename detail::value_type<T>::type       value_type;
    typedef typename dispatch<T, input, output>::type  input_tag;
    typedef typename dispatch<T, output, input>::type  output_tag;
    typedef typename
            mpl::if_<
                is_device<T>,
                device_wrapper_impl<input_tag>,
                flt_wrapper_impl<input_tag>
            >::type                                    input_impl;
    typedef typename
            mpl::if_<
                is_device<T>,
                device_wrapper_impl<output_tag>,
                flt_wrapper_impl<output_tag>
            >::type                                    output_impl;
    typedef typename
            mpl::if_<
                is_device<T>,
                device_wrapper_impl<any_tag>,
                flt_wrapper_impl<any_tag>
            >::type                                    any_impl;
public:
    typedef typename char_type_of<T>::type             char_type;
    typedef typename category_of<T>::type              category;

    explicit concept_adapter(const reference_wrapper<T>& ref) : t_(ref.get())
    { BOOST_STATIC_ASSERT(is_std_io<T>::value); }
    explicit concept_adapter(const T& t) : t_(t)
    { BOOST_STATIC_ASSERT(!is_std_io<T>::value); }

    T& operator*() { return t_; }
    T* operator->() { return &t_; }

    std::streamsize read(char_type* s, std::streamsize n)
    { return this->read(s, n, (basic_null_source<char_type>*) 0); }

    template<typename Source>
    std::streamsize read(char_type* s, std::streamsize n, Source* src)
    { return input_impl::read(t_, src, s, n); }

    std::streamsize write(const char_type* s, std::streamsize n)
    { return this->write(s, n, (basic_null_sink<char_type>*) 0); }

    template<typename Sink>
    std::streamsize write(const char_type* s, std::streamsize n, Sink* snk)
    { return output_impl::write(t_, snk, s, n); }

    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which )
    { 
        return this->seek( off, way, which, 
                           (basic_null_device<char_type, seekable>*) 0); 
    }

    template<typename Device>
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which, Device* dev )
    { return any_impl::seek(t_, dev, off, way, which); }

    void close(BOOST_IOS::openmode which)
    { this->close(which, (basic_null_device<char_type, seekable>*) 0); }

    template<typename Device>
    void close(BOOST_IOS::openmode which, Device* dev)
    { any_impl::close(t_, dev, which); }

    template<typename Device>
    bool flush( Device* dev )
    {
        bool result = any_impl::flush(t_, dev);
        if (dev && dev->BOOST_IOSTREAMS_PUBSYNC() == -1)
            result = false;
        return result;
    }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }

    std::streamsize optimal_buffer_size() const
    { return iostreams::optimal_buffer_size(t_); }
private:
    BOOST_DELETED_FUNCTION(concept_adapter& operator=(const concept_adapter&));
    value_type t_;
};

//------------------Specializations of device_wrapper_impl--------------------//

template<>
struct device_wrapper_impl<any_tag> {
    template<typename Device, typename Dummy>
    static std::streampos 
    seek( Device& dev, Dummy*, stream_offset off, 
          BOOST_IOS::seekdir way, BOOST_IOS::openmode which )
    { 
        typedef typename category_of<Device>::type category;
        return seek(dev, off, way, which, category()); 
    }

    template<typename Device>
    static std::streampos 
    seek( Device&, stream_offset, BOOST_IOS::seekdir, 
          BOOST_IOS::openmode, any_tag )
    { 
        boost::throw_exception(cant_seek());
        BOOST_IOSTREAMS_UNREACHABLE_RETURN(0)
    }

    template<typename Device>
    static std::streampos 
    seek( Device& dev, stream_offset off, 
          BOOST_IOS::seekdir way, BOOST_IOS::openmode which, 
          random_access )
    { 
        return iostreams::seek(dev, off, way, which); 
    }

    template<typename Device, typename Dummy>
    static void close(Device& dev, Dummy*, BOOST_IOS::openmode which)
    { iostreams::close(dev, which); }

    template<typename Device, typename Dummy>
    static bool flush(Device& dev, Dummy*)
    { return iostreams::flush(dev); }
};


template<>
struct device_wrapper_impl<input> : device_wrapper_impl<any_tag>  {
    template<typename Device, typename Dummy>
    static std::streamsize
    read( Device& dev, Dummy*, typename char_type_of<Device>::type* s,
          std::streamsize n )
    { return iostreams::read(dev, s, n); }

    template<typename Device, typename Dummy>
    static std::streamsize 
    write( Device&, Dummy*, const typename char_type_of<Device>::type*,
           std::streamsize )
    { boost::throw_exception(cant_write());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }
};

template<>
struct device_wrapper_impl<output> {
    template<typename Device, typename Dummy>
    static std::streamsize
    read(Device&, Dummy*, typename char_type_of<Device>::type*, std::streamsize)
    { boost::throw_exception(cant_read());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename Device, typename Dummy>
    static std::streamsize 
    write( Device& dev, Dummy*, const typename char_type_of<Device>::type* s,
           std::streamsize n )
    { return iostreams::write(dev, s, n); }
};

//------------------Specializations of flt_wrapper_impl--------------------//

template<>
struct flt_wrapper_impl<any_tag> {
    template<typename Filter, typename Device>
    static std::streampos
    seek( Filter& f, Device* dev, stream_offset off,
          BOOST_IOS::seekdir way, BOOST_IOS::openmode which )
    {
        typedef typename category_of<Filter>::type category;
        return seek(f, dev, off, way, which, category());
    }

    template<typename Filter, typename Device>
    static std::streampos
    seek( Filter&, Device*, stream_offset,
          BOOST_IOS::seekdir, BOOST_IOS::openmode, any_tag )
    { boost::throw_exception(cant_seek());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename Filter, typename Device>
    static std::streampos
    seek( Filter& f, Device* dev, stream_offset off,
          BOOST_IOS::seekdir way, BOOST_IOS::openmode which,
          random_access tag )
    {
        typedef typename category_of<Filter>::type category;
        return seek(f, dev, off, way, which, tag, category());
    }

    template<typename Filter, typename Device>
    static std::streampos
    seek( Filter& f, Device* dev, stream_offset off,
          BOOST_IOS::seekdir way, BOOST_IOS::openmode,
          random_access, any_tag )
    { return f.seek(*dev, off, way); }

    template<typename Filter, typename Device>
    static std::streampos
    seek( Filter& f, Device* dev, stream_offset off,
          BOOST_IOS::seekdir way, BOOST_IOS::openmode which,
          random_access, two_sequence )
    { return f.seek(*dev, off, way, which);  }

    template<typename Filter, typename Device>
    static void close(Filter& f, Device* dev, BOOST_IOS::openmode which)
    { iostreams::close(f, *dev, which); }

    template<typename Filter, typename Device>
    static bool flush(Filter& f, Device* dev)
    { return iostreams::flush(f, *dev); }
};

template<>
struct flt_wrapper_impl<input> {
    template<typename Filter, typename Source>
    static std::streamsize
    read( Filter& f, Source* src, typename char_type_of<Filter>::type* s,
          std::streamsize n )
    { return iostreams::read(f, *src, s, n); }

    template<typename Filter, typename Sink>
    static std::streamsize 
    write( Filter&, Sink*, const typename char_type_of<Filter>::type*, 
           std::streamsize )
    { boost::throw_exception(cant_write());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }
};

template<>
struct flt_wrapper_impl<output> {
    template<typename Filter, typename Source>
    static std::streamsize
    read(Filter&, Source*, typename char_type_of<Filter>::type*,std::streamsize)
    { boost::throw_exception(cant_read());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename Filter, typename Sink>
    static std::streamsize 
    write( Filter& f, Sink* snk, const typename char_type_of<Filter>::type* s,
           std::streamsize n )
    { return iostreams::write(f, *snk, s, n); }
};

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONCEPT_ADAPTER_HPP_INCLUDED

/* concept_adapter.hpp
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
*/