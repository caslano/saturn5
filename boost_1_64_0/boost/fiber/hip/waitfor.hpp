
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CUDA_WAITFOR_H
#define BOOST_FIBERS_CUDA_WAITFOR_H

#include <initializer_list>
#include <mutex>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <hip/hip_runtime.h>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/is_all_same.hpp>
#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace cuda {
namespace detail {

template< typename Rendezvous >
static void trampoline( hipStream_t st, hipError_t status, void * vp) {
    Rendezvous * data = static_cast< Rendezvous * >( vp);
    data->notify( st, status);
}

class single_stream_rendezvous {
public:
    single_stream_rendezvous( hipStream_t st) {
        unsigned int flags = 0;
        hipError_t status = ::hipStreamAddCallback( st, trampoline< single_stream_rendezvous >, this, flags);
        if ( hipSuccess != status) {
            st_ = st;
            status_ = status;
            done_ = true;
        }
    }

    void notify( hipStream_t st, hipError_t status) noexcept {
        std::unique_lock< mutex > lk{ mtx_ };
        st_ = st;
        status_ = status;
        done_ = true;
        lk.unlock();
        cv_.notify_one();
    }

    std::tuple< hipStream_t, hipError_t > wait() {
        std::unique_lock< mutex > lk{ mtx_ };
        cv_.wait( lk, [this]{ return done_; });
        return std::make_tuple( st_, status_);
    }

private:
    mutex               mtx_{};
    condition_variable  cv_{};
    hipStream_t        st_{};
    hipError_t         status_{ hipErrorUnknown };
    bool                done_{ false };
};

class many_streams_rendezvous {
public:
    many_streams_rendezvous( std::initializer_list< hipStream_t > l) :
            stx_{ l } {
        results_.reserve( stx_.size() );
        for ( hipStream_t st : stx_) {
            unsigned int flags = 0;
            hipError_t status = ::hipStreamAddCallback( st, trampoline< many_streams_rendezvous >, this, flags);
            if ( hipSuccess != status) {
                std::unique_lock< mutex > lk{ mtx_ };
                stx_.erase( st);
                results_.push_back( std::make_tuple( st, status) );
            }
        }
    }

    void notify( hipStream_t st, hipError_t status) noexcept {
        std::unique_lock< mutex > lk{ mtx_ };
        stx_.erase( st);
        results_.push_back( std::make_tuple( st, status) );
        if ( stx_.empty() ) {
            lk.unlock();
            cv_.notify_one();
        }
    }

    std::vector< std::tuple< hipStream_t, hipError_t > > wait() {
        std::unique_lock< mutex > lk{ mtx_ };
        cv_.wait( lk, [this]{ return stx_.empty(); });
        return results_;
    }

private:
    mutex                                                   mtx_{};
    condition_variable                                      cv_{};
    std::set< hipStream_t >                                stx_;
    std::vector< std::tuple< hipStream_t, hipError_t > >  results_;
};

}

void waitfor_all();

inline
std::tuple< hipStream_t, hipError_t > waitfor_all( hipStream_t st) {
    detail::single_stream_rendezvous rendezvous( st);
    return rendezvous.wait();
}

template< typename ... STP >
std::vector< std::tuple< hipStream_t, hipError_t > > waitfor_all( hipStream_t st0, STP ... stx) {
    static_assert( boost::fibers::detail::is_all_same< hipStream_t, STP ...>::value, "all arguments must be of type `CUstream*`.");
    detail::many_streams_rendezvous rendezvous{ st0, stx ... };
    return rendezvous.wait();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CUDA_WAITFOR_H

/* waitfor.hpp
UK+vo4i1GFt1taKnl8PpN3PfxI/AD8dFrHiK0auuuuVKOTKsudys3M99cwitWdEGIF89AisNQOZShKlqscqayn3i2+kqZ9u4Hx4eTFsz3jTl1KZ0Pd2Z+jo/fZtFYRywAcdMKXzGZBeMswxRLJ5qvHJl2DRrBCYDXUWCKhM4X5vdDq0ePfqo93Kf6VYSlcNvDHi+CTBdXs8yyIS9AIc36IidSN6ZfwicaF54Ym/0e1i+V0w6xznTIfWCOdMpHR7d0XVbmdcu8gfo0bb5gWyu/MeT0zoSePvIatDc1AY/IbxBHLCxUC/oElOSc43puhXq3FCk+P+kvWqiyg4EAouHqOUTwtl/auf+24uJZT8LAkxVMT3CREYplqhbUfvkBFOkzxeUVrcZRDz+YkEtaaqZPfJSrKRUgZ8nLjdV+1R9FTmuPk2H20NuQEkMswB/Zwj4t1AAOZb1MdP7QAiaywkUsYo5dB+rguWZ+HlMW0Eg+bhLIXgSJF0m/d3FdzkNh/bZbIBv657vln91mdyip4IqK5IrlxoT6Qoan8/l/XTsNTZaJCQ07p8xZ5tWAw==
*/