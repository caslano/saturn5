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
vmaXqRZmWlNOEkU/VZe3uJnqll5D+7k6f7qp/eDX2B70muq5u9TeBJ5lWpvaE/7DtgNdVwerMHKM7Qj/5roeph1pfW1nV3fVOo/eUjo97D7U1xR+f0omHERmoV+GrOHCz2T56+ylsDyDe3lLp+5GbuPUVF+9dmt9hnqZFlIvpb5666C4J2h7qJJOz33lE2lcbyA5yFPIxcSt4F13vZpTXF4yeb503d66pff//Uj5uYf1Hi1MfTZhGvtsXVfmq/Pf59G3lamu4T+6vrrg3ej7scDzxb8cv3LPqBHdg95+Tfo82Vek+7NXkEfRfQSpbh3anyUc4/7M0O+Y1ifr/uhgaL+j17v6pDbfhfRArkdudt4f3lP1w3l/kfeHKbMqKtUDiLIkHK6MVyp/51itzfd1wo3OdjL6uoz3tnT1P1KON6rzo7jTpRjrCP7N/Y/5nQN9U19p6GuMYZM1KmjjfRt9b1+Kvqt93cp53FgD0cJ038a/ty+cVDKluKIyUK9bwpuVzjCjDXL39ddQxvR4syvdeyxkn8MhInuP9HWT3H1dBPU6GtvOe1sevu+T52bPPdl9n5Y81/bBpU+VvEWXfJC+U/JLdFWayQfcyQfPWtE8WRP7wzj+hmfB69Adulu3iwbfq9vK3p9Kpd8u7mTK9CVkst3C+hIxPqvvNvafer9VkTp/st4vdvHusO9uhBVdX4q+8b2ca6u+Zbo631dfe4r6nWxqQ4QV9r1d732bp3S66PBmSVoM7UyHl0N4K1QeS/ZTxE4RuG3hX6p0e5jaH+F47xcE4Lpf6D1Ico+VvSI67KI9jv8Tpa+zrffV7ztprz/HTfaWyn1Y74sK2vuk6q9+F9qu4jPCjqPvmkrOfYmofW64Ln/fOdeUcF1xqihZILbgVR79UF2/jz0frTQ7Q+l+X9/D9D5utT9N+oz6tFn171KdVDgz7HbcDzch32M4TF/X8Lz2rIp3E6csVRt6Qf3eakvdET/1fdIWdT5XfpNv6neG8r8O/6+p388o/7eofmmqqnz6GwgqL6ZZPzDkz3nWOHWNU+TdYhp07s+fIbipb7SvzPSfux46z3OfyzvJv+AXyJfIv5GvlEi/dwR7l6K9n0c6ftRW+r0V6lqeNuB5NnD3fxv0nnepm+Lu1Ivv62eDwJ7BwenLVH0gsWn+30lOXqvrHhtbl984m5Y7HPc5n6fbybNPOWveppEnPX/Xs/PC27Q0rxuP3tblN82mpXkd/rfL1mVeYFxYxsi3eb7Xd518r28lbAuvh/vhOkfE3wLxl46sEn+5sub9eOiDbeFxsB3sAtvDXrADHAA7wtPgd+BQ2AmOgp3haNgFXgi7wvGwG5wEu8NpsAcshyfC+RKOP30yxgdTDelrKenLlHi2En+rA+NAMqa3zfMdgt/Jdxfvgz3hJtgb3i/xfgAWwAdhMfwzrISPwJ/Ax+Bv4ePwXjn/R4hUvQyfgHvhn2A8138SJsM/S/zqAu/ycKDE7zhkl8Tvecn/F6EaJ4Ct4cuwE9wv5fAqPAm+BofA1+EI+FdJx9/gJfANSc+bsAzWwpvgTrgavgPXwF3wFvge3Ax3wyflek/B9+Ff4QeSPqQqg4h+CHvAf0DyW+nnwY/hAPmNWHQz8l5LnKQ8fUippPsmqaerJZ03wzz4C3gKXC/17C6pV2vhLDl/OfwlXARvhSvh7RJv9GUvgbwnKLfQvQT90WsFB8G+cLDU7xFwJDxF6ulQOBcOg9fDERJ+NzvwHKaerVX4HZFc2UtwLnqnw3HwIngJLIXjJR3L4Y/gBLgMFkg6CuHNcCL8BZwEfwWL4cNwMvwLnCLlMhVaskcgES6HreB0eBwshV3gDCmvcngBrIQ=
*/