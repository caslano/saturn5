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
VHxkA3uvl5HK1MLH9sVwflkTK4bwKr1cOsKqEBXzaBxvdeQjriJQq7BFhbjezylAwh9GdfVABHACTvg1LuPX5aysX1n76P/xwleyNRHRuDnJZrNLodmvIZCfAMxyjWanHVMeK4VFjaW7Ar909GCVMKjjjM/3cd+nzb2U8pZfSuh1oON5qe5X1kyeX/L0PdWwHM77ajABIjmcV+JlITvH9+cKw6Th6MSRSrJpsw+VWNGVsjWz0TGl1Jm5xjFL+g3rR8n28zQGZc//BAvg1tlsZORba/2tCfqUswoKHFJ/oF/K1kFQmlCmmX+X6QBbHjdNXhFx91iUVQWHIs9JsO+XG/9kWUSmDU34o9ms5cm/f7co98xmDfIsIRgtcXBiQJ7b8x4+efyuOQnyegbLWP6Md6dc2mBuEUzb/8mdcAp2sNTUgeb29cZG9a1RMuohufcTvKAyKOiUIlhBoZe+29cdrypNCjvB2UfHGg8HP20Io2YItBQjloAQCErKrBadwH11GbTSY9gXdcu5JAG+MPaoj0JYSAIFry1rhoosDpLiv/1cDvxgCruM37bkbA==
*/