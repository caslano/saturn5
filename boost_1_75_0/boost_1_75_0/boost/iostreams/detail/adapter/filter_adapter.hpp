/*
 * Defines the class template boost::iostreams::detail::filter_adapter,
 * a convenience base class for filter adapters.
 *
 * File:        boost/iostreams/detail/adapter/filter_adapter.hpp
 * Date:        Mon Nov 26 14:35:48 MST 2007
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FILTER_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FILTER_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class filter_adapter {
private:
    typedef typename detail::value_type<T>::type value_type;
    typedef typename detail::param_type<T>::type param_type;
public:
    explicit filter_adapter(param_type t) : t_(t) { }
    T& component() { return t_; }

    template<typename Device>
    void close(Device& dev) 
    { 
        detail::close_all(t_, dev); 
    }

    template<typename Device>
    void close(Device& dev, BOOST_IOS::openmode which) 
    { 
        iostreams::close(t_, dev, which); 
    }

    template<typename Device>
    void flush(Device& dev) 
    { 
        return iostreams::flush(t_, dev); 
    }

    template<typename Locale> // Avoid dependency on <locale>
    void imbue(const Locale& loc) { iostreams::imbue(t_, loc); }

    std::streamsize optimal_buffer_size() const 
    { return iostreams::optimal_buffer_size(t_); }
public:
    value_type t_;
};

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FILTER_ADAPTER_HPP_INCLUDED

/* filter_adapter.hpp
PdceIDsrRDA7KzgI5x51LynbLDgI25/yCmVPIHs1JAjdH/+K0I7BjnjPfpwn21ZqLNgmdOdLEK4/9RXSHm42iRRH8POrewl/Z+3poeymbH3JS0nwW4Fx4DjSeGl2WLZstkSoKTIExxDLH/mKZDwtGxoCQ2oKhaFBkP1Jrqj3XLKhoTD0wBf36Hsy4xJSNMHiaG5SypLUb9Xf4NYS1mLVUnajl78oR/ELbpVCin1T+/oKQwHl4mWEVFu2ulRQ9sxb0Dj5uOG4bbZX9pjUoRTFXj3mOu03Dy6aQSIZg62/DFwGHoxWHWYMp4zgwuR3KVIaSFQeyxyVXR/Bj3RJ+/kn8imtIp+2gDn6ME78/BPZ8ciCcTq8DPpvz5j7z7C/ANoTGUZ3B2pT0pfkC7kePEjQmsXazGdb+4z1G+tGzMQQEWHxpyLrP9OKs7Aiu/R32Y0R1bssNTtPQZFw4caYVLmYXZ0DgMdjZtW9WZB9PxxV4O4xDQwafALMLf0+vze7Tjvdrt9Qf91gIMCFhiuNGPgYNyW0cB9Bk+7V9Ps5aXEHcbFzkOWOwMhaPi1GmM7ZmqZcHkw72DSiHwBgKkD/ajhBRdroSfynt5Y+6Gm7ZyB3icY0thu5Z/UTOG5w2/Gfo7bZDmIrUODaL7dtEDFguwyg3D1DDCFGse8odrDBAqeBOTHJLGuXgg6NwJdH/hhPjUjs6HFJru/nlNdOR86v
*/