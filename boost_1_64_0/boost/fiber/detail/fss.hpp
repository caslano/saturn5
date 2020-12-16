
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//          based on tss.hpp from boost.thread

#ifndef BOOST_FIBERS_DETAIL_FSS_H
#define BOOST_FIBERS_DETAIL_FSS_H

#include <atomic>
#include <cstddef>

#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

class fss_cleanup_function {
private:
    std::atomic< std::size_t >  use_count_{ 0 };

public:
    typedef intrusive_ptr< fss_cleanup_function >   ptr_t;

    fss_cleanup_function() noexcept = default;

    virtual ~fss_cleanup_function() = default;

    virtual void operator()( void * data) = 0;

    friend inline
    void intrusive_ptr_add_ref( fss_cleanup_function * p) noexcept {
        p->use_count_.fetch_add( 1, std::memory_order_relaxed);
    }

    friend inline
    void intrusive_ptr_release( fss_cleanup_function * p) noexcept {
        if ( 1 == p->use_count_.fetch_sub( 1, std::memory_order_release) ) {
            std::atomic_thread_fence( std::memory_order_acquire);
            delete p;
        }
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif //  BOOST_FIBERS_DETAIL_FSS_H

/* fss.hpp
g5eXaMRA0KYGeLOpgZpsavliVSl9tFiHlEYvFpZSj8UapaQ4/7hYXVN/XKRHUz9fJK6peYtqo6kPL1LFIGaRDgwuvCOMwa53NGIgaFMt3mxqHU02tfU7qlIKekeHlPYtFJbSuws1Sklx/nGhuqbes1CPpjZYKK6pX79dG01d9rYqBuPe1oHBg28LY3DN2xoxELSpQd5sal1NNjVjgaqUkhbokFKrBcJSMizQKCXF+cf56po6b74eTX12vrimdp1fG02tnqeKwZF5OjBYMk8YgxHzNGIgaFODvdnUepps6sG5qlL6ZK4OKY2ZKyylR+dqlJLi/ONcdU39eY4eTV0/R1xTp82pjaY+MkcVg3ZzdGDwx1vCGJS9pREDQZsa4s2mhmqyqW3eUpVS8Fs6pFQ+W1hKK2ZrlJLi/ONsdU29b7YeTW04W1xTq96sjaYuf1MVg6w3dWDw8JvCGES/qREDQZsa5s2m1tdkUzNnqUrp6Vk6pNR6lrCUTLM0Sklx/nGmuqYumKlHUwfNFNfU22bWRlONM1UxODZDBwbLZghjMGqGRgwEbepl3mxqA0029fAbqlIqeEOHlDLeEJZS4hsapaQ4//iGuqb+Ol2PphZNF9fU6dNro6k9p6ti0GG6DgyqXxfGYO/rGjEQtKnh3mxqQ002te3rqlIKeV2HlA5OE5bSymkapaQ4/zhNXVPvn6ZHUyOmiWuqY2ptNDV/qioGE6bqwOCRqcIYXD9VIwaCNrWRN5saocmmjs9TlVK/PB1SapMnLCVznkYpKc4/TlHX1IVT9Gjq4Cnimho3pTaa6jdFFYOKyTowWD5ZGINXJ2vEQNCmRnqzqY012dSjk1SltGaSDillThKW0mOTNEpJcf5xkrqmns/Vo6nFueKaOiO3NpraK1cVg5tzdWBgzBXGYP9EjRgI2tTLvdnUJppsavuJqlIKm6hDSodzhKW0KkejlBTnH3PUNbV7jh5NbZwjrqnfTqiNpr43QRWDiRN0YNBzgjAGN0zQiIGgTW3qzaY202RTs7NVpfRMtg4ptc0WllJAtkYpKc4/Zqlr6qIsPZo6NEtcU+/Iqo2m+mepYnByvA4M8scLY/DaeI0YCNrU5t5s6hWabOrxcapSWjtOh5TGjxOW0uPjNEpJcf5xnLqmXsjUo6mbMsU1dVZmbTS1d6YqBtZMHRj4ZQpjcGCsRgx85x995x99j+/xPb7H9/ge3+N7fI/v+R8+rkcfO8f+xUcfLX/t0cfgv/boY9hfe/Qx3FZw97iSp6rJA+NPm18RTILkmi04zREOo1C4ot5/9Usd57rOFpxNUx1p70jTMdKelSY80h6ijBrpGtWMxTZAsa0YcQ2GlRmyzfXlpWmZpj73UZ2qZ+5ja6r43MccRVxtJTKSEhG2ADtpEoDAR/CPbE/rgTSCJ7MmEMQnFijgYy25wXnFmDDYf/iPQ7q0Iui7Am5IVQX86HAdgC8dLgz4yOFCgJsEAG83XB3wkOF6AD8wTBzwFcPEADd5BjwMcQsrqgAww4uqEN0wOglSAYCzoHAZ4Jc3vmo8A/zUqaPp7gAPHaYK+DfP6wD80+eFAZ/4vBDgZgHA455XB7zZ83oA/zpFHPDPUsQAN1+SGm4r6NAuPsSdfUfkS7d/dtYd8g1TVJH/YagO5D8fKoz81KFCyAcIIH/3UHXkWw7Vg/y3Q8SRLxoihnzAJanqtoIB/bKaekZ+1uwXK90h32SIKvLnButAvniwMPIzBwshbxFA/v7B6shfN1gP8j8+J478lufEkLdcojq/vSSsk2fk23f8frM75K98ThX5i4N0IL91kDDycwcJIR8kgPzDg9SRbzNID/LnB4ojv32gGPJBl6g=
*/