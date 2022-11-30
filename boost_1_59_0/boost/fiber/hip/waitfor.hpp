
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
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
*/