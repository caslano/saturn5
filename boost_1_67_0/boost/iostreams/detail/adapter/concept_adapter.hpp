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
tVMxMra8+uht1YSHfYRK6CuSNDUPFwczq3iNj7pYvYSiV2jabetQdD/iVXftzSIb5oVm8aL64N5SbQ1M9edwbkAvZZrjst0jeaFX9UCu7LQuVmy2a6Df3LjyibrBMU/EradgrV0lEyygtDBXk1gz4C+RQjws9YVMoAmWOBw7wxcU5x1dN0ypipe++9nBtHnRwNqwVsLDWTGqSt60pdHZX5Y091auuA2fZm+1VYMzbN45PiGsYXsacC7eVqipqKeqIgXhxrvkyMdojOnNZsTz9cI5ZKkC15ulhclVCovReNKjE7g8VRqLAUrW2uc6QbsySV13aIGWT7HsU+RXpVsCloSKMyuVl2qBv1utDjePdTR14YO/WnezaPi8ITd0J0eGa2YEZMMCmnTIPZPg8siekNhhsdvVlL+aY3zOuqmVeXYqS9GR2W2nPURpTHHZQPkDFVscDY3hizNSg1lxPgoi+dsND5m5NsAsxtotkjCebv/jIfe+yFydLr50szm6l/1k2A9Ewt7PywNasscnvYUGUBMFN3WffYBojZsQccdDtN7umRlxYWJ5E+ckqSDh5/ZVmQlClOAy0dBcMmzzm5TSsmIemGpJOj3N3VgjvCyXCSjTYrtUC0Xt5Xk1rRuvQcFwiHjU384h4ia+m27iCdjbTHGSIqTqci7TGqvC8XcTng5Hs11HSOghwhWPBobzxnCIYbTyeiki8eMy28Wp6VwUsuY6t4jdNePZ8XaxdKdSCeQ2HwOm9OVz15xH245+nc8XbO6lZDPAbTN36zHig/1x0PYNs+NP497oZsHRQSS213HKZoItwvmDBEFXa+kzcpitIsGcsmcmdV2F0qdsimYn6ZsXG9AcEw+YEsPT/KlmhB898JBk8pbGcCC9lLnBabbUgXSIqkc1sKRTgBrwrlCNJjhM8JuFFBt/Ixaj6XMLaAaqFjZhI2GjInAXQTGjSMqQ35JlcPE+iagO9wUcxmLioHWNm/Jl1pVVinUS7JGKYlD5CAPdhe5pY4974C8yuY+nHs2m4IJhVjUkB0ceryJufjaPKw7YjZD9OuEeb6DsyMoxVoAh+IkA8My6UmovNBAlwZas101eE7bHG4I5w9SUdnTb4SAp9p71GrookllymLpW982jT9zGUjrsnk9Ci4lCjAR3AlMXpCZiNX55AalW6x7YPUbHbs89t1SzoHG9vLY62yaGwVuxjGfdgqlQVpUrYzlOJkbxyg5lDGVeTsAuI/waUnIlO+PjoJkNPNFgJ+B6AuaPitR1VNC2OSk+8aud5fMsRTKvboxEVFjRh7YUKLy3Gr9bRK98RTqPNmKnjlXdIztnzgmOKSks8er6O7b8cFfJMYbfZ4SWjVZxZvLR6D6qPwwFUpsReiLTS1PFRTuyfQvavoaLDwMPQCnUROHwf1625U7X2LZOt+QMQCzZN9CJkHzd8UmfZbxLYvccm05aTpDPr9TClkfC8K9333IAcynralMqumB2cet2XdLTJQYaFNcacDXlqS5YF63c04IrtFJAvF1nV3dmJ0UlhcILsZe/j+Ly/z4CYyiEhnW5nSMLbJZZBip7Xu9ASs3rkvs6kBIRr9avVrPGg7OxC3NcutUVmCwkfJPewA1Hend5R35QhGk+zkZ3l9JJ8A6Mpak0yANn9f0lRu27hR4+RssLA4ZUClBX2VjL+89bgPQXbyRFwRhr3sIgJPEntL2bJWNrnh/MPKrFKq1StYtGqdk+BIilBw7msrcl1/sTiBoGplglZpr+KFA/omnd4d7vo2FXdFpmC7uw480Z3mNoQJZgnl323Ls9JjpLTE+ET7GrpMSDwMiVQouonzowj46ye5b9TEV9VDXOCmvQg9yVEP1i0Ldc8zH48lAdsxBvzTuqV/ULY946vLzZFQ79pfolyMZni5fCpSCn8+0l23LkuvH+UVoYOMuVeQvAB+TrM//bT3mSPiKMiMsJm8yKtQZ+WpVHEWrK3HGICrExJrjrNNbMRar0htYKHlRXK5ifb7yBWb/I4WsCPe4s0eMtdTrE62WXd4NSJHfn5W+qXPudCAGTZUsfVViyXpOZScXp7akWJ0zcsGcjdPdy1GbE3ufDbV6mYkGqheN1+udD0RpCzk7VPEMfuNdpvuDG3gnO/BWLGXAlszT/gQ9LuFpjUh1ucYXKAoPfTV1o8wlAoRwSLUL3uIlMSqIklR0pQMxPR/03vMRGUA8QoIye97cNXl/IfboW/emfz026nfQ8BmCY3DQ/QwzQ4+v/j9Lcg//v+XUA/LTmn79iLByg8GM8CBiz4d1fKXqEHmJfA48WZpTwh1l+a/7LcdZ8hMJ+fAr9JiqMVxLp0ke4UylzbtdKT24RjvpNkgcHZFkXqi0GyX2VsG/q+dl+xrX7zi6IKFNupVMUKJEBTrhJplMGwYu7glCqVL0b7f4KTjJVZO9iSOPvFsUhEfVMNmuBKdRg8duWlZeytqtkvWW+7iCnnSxLwxZaAZsOCZYgOaMejA+DgpPrc8JZsad5AzyYwhIaYtMdoUQJEzyt/RLDGxSn1NSVfxc3x9YqNZjeKcuoyhfFiCd66bnsmoLID+UM2EqpOtr0NBMvW6ZLbWg3hBOOc3UVe/w6LqT4DvGIWfukfbZMbimZXpw2o45mulzugp2U0MqE3vL9KLIQTioJ8ELScBeAv2olTQppGx0VFkOsogY3PZBjnHVfpPI6BmuQQO/X/Qx4KPs1Hg2Vr+N4gVptVjXmPjQG8LmwIOQ0um2qeJOQevPNxpBDqDlehRov/ATzwCKixkALvtaC3gxfqm+1SlDqclwlCUkTfYUoJbdTavAtYH24NnHggT+7v/gtfPUueYQU9KfKhBgJiWTuQkd9/rlfkAnrOIsP8hrumu7K24dHoTASMZXzHvIA7mB3Ir4gfZROESy/Ays+aBL/8U8JqiK40hp+/9/L14CHqLJqiXuWFAItBwcCa8gT6E9u0VPXhf929o1CWzfhgB5f+FbL4a0VTm+HNvmZyK2q+yt7+ENiJH4i7IiQ2N7nWfHPcUJvXdlWeK2AGNk+8Ot0ej8hfuKC9DFgk4dQfX82tufCGMtheV8/+nvhKvEBzVu9GwbUaLJJEk/eqO+Uyx/EkM8N11hwWEmJzkTylr5yJvnf7oobUuzR+uj0Cglx+j29JAOTx0FrMp2qSiUj9GW00V+FeEElIqOtNLw4t7wtSptTIs2crj4N1WV9bz2FUOUG12y/i1/nHLbtX8T4TfN4ecTGkhUJcP4ZL7hTqYSzC9x1AADjjPJM0aJ3C/8ABs0/X3tl+P37HmHp9wa4xMJfgR3geXOuq/fe9c1WViN61pY3bSYfKbhPxF0bKoAVfRzrCuvG1olwD9sLdiq8Zg0mu665ACiZelD6/KBvmzlouxqX9GyAhNHevhOugWymxJhD0xNHByNBjViDhMWfePnfChNJ8wmJYk0P8Qg/0812+849iEDuvHPcDHC9mK5w+n7/mMl3Mb/8+u2L0oH8DAbDqDuoaGcv5NrGM/tPYdzxiBzk+7MrF0sSWHFOJjBOZZ22wrYNP98xCgSR2zvDspHvFn4fHT3xlb1zfH+025dhG7MPFV9VN5QfH5BdtPg13VGPQyeBusIzuw5+9pjvaWw7p31Ru+HKTNBt75WuSDY2ZSYEYWEnC3fhIdhjZ+NkJJjkEmND411CR693Wi+T9EaVWbSON78m5Qavt7yGwV2Dc0WkPJqWuvR/vdgUz6GBaakZNhxigeaVSKvkum10jpGWWkq7BaQlHnRScoFejM513TKGwbbaXQkQ2fYpFp5UwIbN0yM1OGF44MQJCa9Mc1Mbna1+hftZr7Npb5+OhsnRsCoQzQbcNEV3CSNoLNR1r9DspH6yPxqXn35cAzGF4a4ZTFzAUK2dTGWl9skP1YK99doHjntD8RH42qJuh/pEv1zJlfyeFBOXwNwreG2S6tN26Zb5CNk9zc5ehIYEcr2RLn6Y8Z4qjS9+jJxZKplaWlbct+ytZxddRaOmV0jme6UXCIpUgSZTW06k0kBrwvp+ohcqRDvQbimgSdy0Q2OoYYSJX9fg/ii/E3ni78Ye4vCk0hfwGqtz3sW32CCZa9BWyh7HDVS43FQC4sLc2r7W8aIjL9K3G4A1ZpJw0WmY2s9TOPioX61kq+VqxbX2hRtglTqZ4mPYmw2MbO9d7NQdE7OrOB7GSn0tO5fYlE35vRoQZ8GYObEjHrayW8GIHFhf6qpQEWycnk1nyHcTavxoB2zcVUEeHtiBMAT042h6uWa5EB6Hu50ItZXrhAcMC+m1OLSVXtUL3Bml//FlsP/ZwPkYXy72vaFtGGVYRsTNtXYTURLv+lDCfSMNGLa/ZWBEivY6vgx6XPxyftiCRk/Non8C7LrAAAazRPd5Ay/fT0fCxx4/pJIkWU7wOhmVdbZJg9Zoc7Cdz5qhr3cQEj3nCkESaS2GbglYhGOM8wXSIf+NUJtN7p/m0o6BcaK7XFogX6ysDvG5nSlSuyxLSIbNFkjoMYsUp8CShKxRWtnKE4l9/Uv7M3t2X4SDk5SdyXL7YatZygvPSM2FZjihc1iEMJ4NZHp81wQBoBGCT8TlkaV7TwAIyAyie02tpyce4JTvywGXMJldS5Qrxb5Dreor93VaNZjxjnboohG8hVFlFIQNM+4XL/Xn9nr3HUS1AEV38nw3D8mMXtjfiYtjgbFFKcv1OsrWydab7ENEdaU137W9EwSGJzqBwgXhhax1O+2hxqYbebnKRIhs6LtcJ5keoxNefuhHo7/BCdjn9iMutRZtnguKxMFEhOIA9DNS94IoLJBhMr0kuhGEldN7H8FNC8TEnhITjK6zhFg/Sj1e9zWeniozK65nS9fHzdKmutQcqiT4R2KhwOy7iYtNc3mp2IU69j14BHl2yAcFS4dtl3Zm6Td+rXSFIsJPbKHqZ5bCpQqq+oPxc6XHLewUc2EFYColiJidVnJCIYfOkyXRsFhAX1Bfbq+GyfbO9+kgqjDTgUqaLkF0YerdnS21+9xeIY3xJA3WB8QF2l8R9r0348r3TUXTUatbkykv0o2CBTBLDV5JAuNUlazmdiP0MQs1CjdIaraUaHjptyku0JtQEEmqxyoqGFZdfIKi1ZyUVHtR1t/vtrxdXDmrss0nXSbW2+bUhPzl6yXLSjpRm0F6v4XKf2Z0G85ttI/WGqZAIvemQg4SNmHUvXiKj7PNh4jZWavtuG3sAAqD8MYcG1UvvosuXAALLPTTXmT6kiMndwP7OZGxERElVvuXQrEZhiQRw4RVA/5EpDMHvhSiTcP8ZmynymmQzwTwT4ZphErgje+SG92KlqChFffMyjbYRpQgsDv71KIVpUZrWozHVIPy0EMgGeCmA/Tzt+PjyCe+bDfIEqErvWGQkr4iXa+avbNrTDRAObArk2fS4Yx1cOq13IFGivKZqRZ5NZF/L4zii7KhumG4z/avEmrnY5nuwwT2CZfaaJt0gbT6dOZi55dVvmXM9AM2sIJoOg/wmG3ewYNzD68f0MnSB6AH1ygG+nzA6xJ+XH6gf8jl0oYx50/Dg9X5eUCGWmcSAcLHZm9LZxSyVRRq3mLINvjrVpScIwBmL3UyU2rmMcpOwuRP3DGpWHDxpbDL02jlJWQZl2SypjonX1NlXtdhFNO5V9Mq4Cpdh305P133DvQgCECydxbDDNJdecrN98utzSoVWuQmJuguHUvI91lqW7B03ILwznYdKgxcPT6VanlTmOTiPPlzFTr3Wy23hF6gEDoWPaCG9T1e7Dz9a2c4fa+SfMWkSEo1mTI1cHkJ7NQKQKT165/QWDtxZ7p+t6rZOLlE6o37yZlnh6ZXscsQGNj6bi3+ShZEch6crmIcz+Sko+z1zfS2ErVIyD1coM+xdVM8jL4rS2kzEsuUCmoCokmyhjl4cm9zA2CNtPmZ+up1/cv6SOT89N06zrdz/YVVr+a8u1Ol2Dw5l3+HBQWMFTgSbdU2bdG1YCAQEAAABAACAAAUAAAyAJLCEJarsBZaD4IPymshVli1sA+tqlR+0IIWghbQD0t9WlrCD7DWPLTx95kZo5oAOAAABzi63t7bB4hIeJ9CXsTEv1/4+cCHgAH11ScvAgiotZ5uwUHMUXvdM01ss2+tqQna+0u00d73hY4EXWiMtKTj7Ol0UBLc7OZUR4ApZoKOE2oURJS19qNirtHm7YXwYsA2ABAAAEQCYGZgBN/7974tz3ez3G3NzUzglbE2MyQyQigRpUycJVGtnBK6ahdf4n6J3AVXukcibpD8Xct6G8D7GRPNkTa3+zxAxr8xFOuPfXcZhHjpqJDS+sgNvoZF3QgSZhbvxKMMldoAjgGUgLxbVyAiP27iZ2BCwJ+BcElXS3sf1s5bVT+qUQI5q0CeF2Sxv2grYHEOZomm8+som0bhKMqKZeqP579KStwPR5eDUjbZ6A0DMXsedAx/lmqtD2jejAYlNwbYNJgoXgTuvFGLvBhoyz47ZJ3ZUAZ5NjU6tPze2I+fxMPcnaTzIhNHNQhUDvMixKBU5UvTwGqxIjsuOspk6rV3hChEEhApj28+a4QJWGu0XXKmf6W9bk4bmc3BIw035ZVyg85LSYbrHQ/pI1uutjiILms66WqB+MmCgZ+v78H8dNsTivZbfRkGNH1E0ZmmiVjgrq7a9qjahWZAqV1u1tte6gM27ZRpExH1pF1KdPFd9rRT9zF37oJ5E4XGo3GMw3xXXIXdXL1IRe0+e/0GQK2nWe1HnGtuDyI+XCfWoau5MqgP38QvCBHHi7zRCdHMPzQdiKdUjuZ0468j5ZJjxxexRuXdBSfQptD4UqGSEfVSUh7JbS49bpJj9wZtKleVnX5WK51/MJkbSdB5kfDrdgWFPDpgzAxMdax1iMwrx9JgslKl2MuxbEtP30YRGgX447LAmwVH/sF1u2tkKRXlXWnRgN7ELzYrNmzb8A6Lx/eNCuzMV8Mefuh1Ri5YRgSv80h09jcDQX3fiA1YgwFN55l2/D7LK+Iif1Qy6kdsw3YjB/ac2L0CYPbeOZKojz2eX89eshVtO89qvbGQrOPPQXUrXKS1Kc8GYreRegS7PH+rlxyPPnZI55nIpjLXvUzTzr1gN00MRE2JrRORnxpNzVznGec6sQxaihIKC8iKHbwwdqE/lNpNW1+GPnA/dpZkGh9A+GwWuasB8Mdi00H/G1py7+fLahiEpVwh3NCt6JvdcDQk2NCHZElJ0atWbbtK6kVD0RziycHyyCslTHjSRQpu0embrQEsgZK2atnN8BPZThs6HE0b2oT7+UzSUcFCy/x0tFQ6rxW0SzZsHsB7LQeXJwpQ8nx8OIJxxY6uo4m/PFQs40o27G5u4+n7Bk9NvYzqygnCrEtS1HXCQ25BNa3APvRI6mQrOLxhtykFqtaDna1krID+rjlMhBWWuAyJuUeiXZZTCT+l2KCUt0djY38IJqej/Y7Y4VRu3zfTvp/poT133VA6tIHDoiryC8l5Hrlp2btkEGW1rXNR/YveGffSNmXyrfriLj5tfmkCmUvJ7wj2Qs8rm6+kTGy9z5f0naOjzN8ArWAusTfhVtdaikHYn3RwIySrOifvI0+CLhW341lqCp1e63wYp81EhDvNtXAl8v5T7uUNmaQulC0a+dEXyustSgv05skqCBTp4CjisjiuHevIGLeT/8EBzTzHO/OSrvs8kkFyCfDjZKz/V5wzuoc8lZ5QsieI/EjLtaqQ3rtfrdF+lGpGylhBuOwjdmaiHdBCaPTOMGFbPpB1ghVDN1FOpOHoR3fF+bfR932liXdbDyki2gEc9z9PPEbkRtK+xD+Zwedg37Y6DCDaAvXkPRtAqp7w4spmkt4Y67uXYzZvQ60QDI6B23j4sAHxfAyKUovUjBts4i8YL6y6KC+pEWle7OvoHXYxXgiZJnDfDsKjLYbNC1fVD3vFPQxazyW1V7doug6dq0/gLd0Oz6zmfh1ruE0V58NMTSeLCqHlRk9ArXZdfGgUUh+fmzkM8gEr31Qq2ykzyDNZrd2xkjyPWkdefTvzHMWKWgqowLUjKXB3O8TVA/lAptBIkWRSrQmH+Me8FGtZ/zrhQk6aS1LOLnrs6TZ9vgvLVB7RhTvXbIjZR0jnnB4EtCtAk1Z/oxPk7CZaayhzpf2WFo+o4izU2vSZez8yzASzRJB9yoO8Sd81lVK6p9GwaFxzdlpWms58yXJ1WEvMn5rKrtasfBrbY0Wy8OQn6XAypebps6xA3JOGMnyb0n6/DqI1dt+RecpcvcUFxYq5JW6W9T0RiA0eSvYm/kZ3O5rV/0iXQp2z9W09rk3muvETIluEM+FRCrc+Jw34g2S+4PJgCLdU0H7vh/B1WUdXEFa8E5r+Cefebbc03ecmCtH4aq56MfCh/CI92qoDnUx/t5a36K2/eSeZzXd3XIs22+vh9HTCC2Q+w0i5OBab4XTeKt15bnHN0y1x0Hgo0QWkJRS5A93iHhWrfOQ9dK8cbJytjYYZoTwrwtLpXPqd5d1cykhfKfqkvidKnp5mijxYwksatwZK+xWguFL8MvTASNMvJZGUEE4VEY82d1/yJqA2wLqRw/4v1WGDRzVn3FYOkkn25WevW5lpqDq+ikQJjImf1VZFebPBaVIpixr5esR8qVlTXj7KtHLHS/9IT+tBMI1wTX6TNXwdW1ZYiBzYRzdFXK6p6UlmEREHKsixB4uocJ6LwWfYbhQxbSthaHNiiyhgFIOTvokK9BwfXnmFZFQFvsHPe+m7za2s1DtrrI82FszdbfNkEsyVJMsria0NlN9hVz2w1vK9qKjretRjrnSvjLoI8A0rN7+7F7F3NmCBpcR2IqiOVVL4/967GRlxA4Wgr8euwGQhbnYqPuA+GFXheMTImH48kaDdhF/QSBOdRgV6b49C9AGocGYWl8bcazeb53tIzEKvhbR5mGz1UXdnRbAMR7SXZEorGPQzAvwXlHorPorVAuOKP6pyLuy9XJ6/t2rVeFaT3EwyduY6WQH5tqn6uvcrMS7WEYAb7ztE0ixmaNelpi01Uyy8+mbSWnaZ+DhaENpG+s2gsm0skhsN9RF5orA9nldTavdOngVb/ByTOgWfPliF/KKSw7/AwBgqRyZplSQsDtMkqUTKQlvhUlo5xeXdVBqFxvoYRtNEH4bGdJuHfqJWxUp1w5o/A2UwhYhJWGiliH/ksyPntfY=
*/