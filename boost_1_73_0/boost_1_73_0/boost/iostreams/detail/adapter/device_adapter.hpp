/*
 * Defines the class template boost::iostreams::detail::device_adapter,
 * a convenience base class for device adapters.
 *
 * File:        boost/iostreams/detail/adapter/filter_adapter.hpp
 * Date:        Mon Nov 26 14:35:48 MST 2007
 * 
 * Copyright:   2007-2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_DEVICE_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DEVICE_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
class device_adapter {
private:
    typedef typename detail::value_type<T>::type value_type;
    typedef typename detail::param_type<T>::type param_type;
public:
    explicit device_adapter(param_type t) : t_(t) { }
    T& component() { return t_; }

    void close() 
    {
        detail::close_all(t_);
    }

    void close(BOOST_IOS::openmode which) 
    { 
        iostreams::close(t_, which); 
    }

    bool flush() 
    { 
        return iostreams::flush(t_); 
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

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DEVICE_ADAPTER_HPP_INCLUDED

/* device_adapter.hpp
JTzc43xPPmWnX+JJGs3jJJtGS/gDxo82x85p9BTw8e7YWYTLmT2z69hpCSbzs8UstJh/wNlpNAvj4CwkaGa7ZcfQgWzbak11cpzJLAxie5TQfn/QReMSppPBdRwmxFDInInRAZ0+w9OI2pgqjO2g1cLha5gs50lijaIZtZvzYox5KaEXz9NoEo7gGiFn1SsDl1ihYjQWf+nyBy/U6VhBrqTWQ7vLBa8uX/YcFBrhCIigkubf5yOioZOX1PHawHALvf7AFtLtvbO9X8E+BmlHijTaRcArbUi4hymQBW5p9k7e0aQ4L/Z+SDGt8oIr13+AhuHQFpeOjayzVcNF0YII3F4m/UH4LQy/pS4BaUyJzGb7AfpjByu6MKzI3aU4hMq2/X4hmdt0f9R5H8WwYIbtR+X/6HiXxGGatT84+0y3TrawGU/DJKU/7m7cHlxL7k+hj6+wFhvFSRrMZtk0SAP3mVfBf/H7z3DxFG93T3dl4z/rjtoV929QSwMECgAAAAgALWdKUrMIsc2RBgAAkBAAACEACQBjdXJsLW1hc3Rlci9zY3JpcHRzL2NvbXBsZXRpb24ucGxVVAUAAbZIJGCtF2tP20jwu3/F1KCzDU4M/dQ6BIpor4euB6gBVQhTd2NvYp/8qncNocD99ptZ
*/