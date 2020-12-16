// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_MODE_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_MODE_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

// Contains the definition of the class template mode_adapter, which allows
// a filter or device to function as if it has a different i/o mode than that
// deduced by the metafunction mode_of.

#include <boost/config.hpp>                // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode, seekdir, int types. 
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp> 
#include <boost/mpl/if.hpp> 

namespace boost { namespace iostreams { namespace detail {

template<typename Mode, typename T>
class mode_adapter {
private:
    struct empty_base { };
public:
    typedef typename wrapped_type<T>::type  component_type;
    typedef typename char_type_of<T>::type  char_type;
    struct category 
        : Mode, 
          device_tag,
          mpl::if_<is_filter<T>, filter_tag, device_tag>,
          mpl::if_<is_filter<T>, multichar_tag, empty_base>,
          closable_tag,
          localizable_tag
        { };
    explicit mode_adapter(const component_type& t) : t_(t) { }

        // Device member functions.

    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which = 
                             BOOST_IOS::in | BOOST_IOS::out );
    void close();
    void close(BOOST_IOS::openmode which);

        // Filter member functions.

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    { return iostreams::read(t_, src, s, n); }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    { return iostreams::write(t_, snk, s, n); }

    template<typename Device>
    std::streampos seek(Device& dev, stream_offset off, BOOST_IOS::seekdir way)
    { return iostreams::seek(t_, dev, off, way); }

    template<typename Device>
    std::streampos seek( Device& dev, stream_offset off, 
                         BOOST_IOS::seekdir way, BOOST_IOS::openmode which  )
    { return iostreams::seek(t_, dev, off, way, which); }

    template<typename Device>
    void close(Device& dev)
    { detail::close_all(t_, dev); }

    template<typename Device>
    void close(Device& dev, BOOST_IOS::openmode which)
    { iostreams::close(t_, dev, which); }

    template<typename Locale>
    void imbue(const Locale& loc)
    { iostreams::imbue(t_, loc); }
private:
    component_type t_;
};
                    
//------------------Implementation of mode_adapter----------------------------//

template<typename Mode, typename T>
std::streamsize mode_adapter<Mode, T>::read
    (char_type* s, std::streamsize n)
{ return boost::iostreams::read(t_, s, n); }

template<typename Mode, typename T>
std::streamsize mode_adapter<Mode, T>::write
    (const char_type* s, std::streamsize n)
{ return boost::iostreams::write(t_, s, n); }

template<typename Mode, typename T>
std::streampos mode_adapter<Mode, T>::seek
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return boost::iostreams::seek(t_, off, way, which); }

template<typename Mode, typename T>
void mode_adapter<Mode, T>::close()
{ detail::close_all(t_); }

template<typename Mode, typename T>
void mode_adapter<Mode, T>::close(BOOST_IOS::openmode which)
{ iostreams::close(t_, which); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_MODE_ADAPTER_HPP_INCLUDED //-----//

/* mode_adapter.hpp
l5WXVbaO/78u2v9f43ctpxNkHr51n/2ta+P4v+RtOfrTJk0uKW3iG1fHGDUvkWzBKvCH9m2QoWROsrrx7wmE7vQ3tWV/qvQ3VaQE18zJg/bvtMyW11yz+31PW+nu95V+G1Xe/3efzWjVZ3Ns6llLpj9w1wVDt8mafeTsuFe9PpuNuc+mLnQ+yfnZ4PIh3lm+nUmFiTANbgHTYU/pm+kFM+G2sCscDDeFe8AesAD2hPvDzWAxzILTYB/pO+kLT5H0ToW94WnyO897F27Vd2HPx/D/6714tfc+7G3e5m3e5m3e9q/b/r73/5LS8VNa5/0/gxeCIfL+Pz/OUtv9Mq/oXsJoe/7/s2Hv/5WlkyiAKlRhSb8y3rdlvTqfxYJgk6eY+gIkDZ+S/WmT4Dwcyzx3CFmTb0nj3CFkjfOSzHOH3OUQv5CVjnkzb6jjaWouXBctn6vTkH2uOUUnjKuaYJhT5JKNC+j5PHq+5I7P2cfzHPN3mZvi8M2Yro4X6nk8HWTtUnpGdBkbVB5nig4kDcfaoWsd685mSr/KyVT2Dhiac6f8mEaxFrFa+03aOeR/iPZkH+0pcomGeT/JTcz76QJpB/bTDu65PEqvbl/Ooh+Jiy7sNO08VD2D8aT+2heizKG3FSDrzSfacnAP7HvxcxH2XdavpLC0XNk4ecn6z83YN2lEb9+Ln4vevhc/F5t9I++0N/7iMmGeG4ds9HasZbWdltlF0HPgE5+3j+9l25G2Ve0vWNo2NH/2WZXWL1YfWmcy4RmClEGlS+10/2CKSvcuug/jrFMJA7Bj9KL7A4fZ1H832vdC+X2H/O2er9bO0GdY83xkn+GAlNa3d9qF/bRLVPaOnl3rux8s67ufL3ZcC5fZ/bQvhK3TMq60UBmw+/qsr3VjlfwmJnsmrej9+ya/EKPf8hfc6zBTR7M9O2UlbW0fSpfXquNn0C/VyZpGMNm5M41fVH7Kf7TWw7wX1TcPBrt31S0Qihs+f3Kmir+ZYa6oqfyl5dw9jXNFnbJdujV+q9A95GNdHT/B14vz4FjCvQS/L84qIDjm9uvzz31P6S7nX5ZK5xTfNljVVMJyQgcf/RcEwz1E6+k0VU9kRPfbqt8HW7s6fIXXqH0BfiOjfyfotVW7yvm5Kezm+HszAvPJ9e8swkLH781dvwkR53Si4Zy+4EV9TpvuYevlgxeblfPSPR9V2aY+p7E1vfZAWmg+aiC0rzHN7FB8sY0kOf8lzf/1WMWpaqxizSdXps0t3nunxLHXFW96YeK73ljFxjxWUaOfe4N6aSAkEWbKyTlW5ukdBneCR8BRsBDuA6vgGFgMD4LlsApOhjNhBTwDHgfPhlPg1XAqvBNWwnslnTVwdej5RZ79GuTa/pzD71giPAV2gXPh5vA0Kd8lMA9eCvPhZXAEPAMeDM+EpfAsOEvkTxP5M0V+HjwH3gpr4SPwPLha5N8T+Y9E/hM4H34t/sp+FT9kKZT/YpjqQ07qV+CTe4c8EzTALQn5Mp67qdSvG0yCWVDdc2Am3AJuC0dKffeEu8K9ZYyoNyyEObBS5GaJ3GyRmwO3hTfC7eBDIveUyD0nci/AHeDHsD/8Dg6ACb6gfBdoy2dAW74r3AVmwV1hfzgIDoVD4CESb5zEmyDxjobDYQUcBqfBfDgD7g6r4Qh4qsSfJ/Fr7fjevM5WH8v6t4xjefM613/8Kv/ceGsiYf653jiWt3mbt3mbt3mbt3mbt3mbt/23t79v/H/8lMpW8v+3Raalx5Uek++sryIkEi4nPGmPKz3qHFcqLikpZKk5GRd9PLhOpFos0TCORFz3ujgqrvaBk62Oz7OON/oS0/Ed4xL4NSkrUZ3nznEO1hQ=
*/