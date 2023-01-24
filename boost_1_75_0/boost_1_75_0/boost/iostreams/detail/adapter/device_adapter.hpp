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
dePqEYLV78ptKYrQ2beQyt5cKBQ6qk0XCl737FmxXWqnC52Mftisc8MLyKIEtXJY3CGPSGcpW4KuGCafGjN1p93URTN4P049e+JTxhTMtF77GvYvYt2Zl3/w4M74Otr/+gqZO7S9P8goC6CZ+OaYiSWn9vjmnfe10ZP9qFG2kXAbj3NPAQSNDcMvPtS/VMSGM1teOIxyi7RWsu3Ti1QueTbwfY4NdUq/FRu+wb1K1GGTJ3fpJ6op0YD0bWNGwZoraWnN0PQ4H+4bAwmbwynccUhd5bst1XYHxRhjVMc0q14PMhEBwAJLdhjbT54eWTF2Lxuyd4iywLhJ8TgY/dbVO8fASnuljxiTVSMF2FOKJ1Vw61maWgL6sqD1rq/ZCaVxELKKEDPfwCE+8eSFGSUjqk6lcNufK1IxvLzhEPO8vwHN8uGdGNmDHTPdeKnb72Eig2EvOqOq7yoFBlZ0KYy23/sBgh52fS3N3537llIuv/zlL/c3EfPPBFeKH6TR93z2xP2/4NAy3BO8y5bfJ6XLg+aPWeZRFRFczXlGqm06XWNldLUciIrFCEzq75Ve3fhutoYIDPqcgW85/ClcvvrsAa607xcqq3h3Xeq5tlzGSh+jHoRAm6InQXHQcmoGsgeQXo/Zrg4Wv/GjYf6G/iig/revd9GgTC4zrtDvi8Q+nTZ3pW0W5NR0RO7xHAfuQJSZx6FjER+8a5d54bbO
*/