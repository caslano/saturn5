
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

#include <cuda.h>

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
static void trampoline( cudaStream_t st, cudaError_t status, void * vp) {
    Rendezvous * data = static_cast< Rendezvous * >( vp);
    data->notify( st, status);
}

class single_stream_rendezvous {
public:
    single_stream_rendezvous( cudaStream_t st) {
        unsigned int flags = 0;
        cudaError_t status = ::cudaStreamAddCallback( st, trampoline< single_stream_rendezvous >, this, flags);
        if ( cudaSuccess != status) {
            st_ = st;
            status_ = status;
            done_ = true;
        }
    }

    void notify( cudaStream_t st, cudaError_t status) noexcept {
        std::unique_lock< mutex > lk{ mtx_ };
        st_ = st;
        status_ = status;
        done_ = true;
        lk.unlock();
        cv_.notify_one();
    }

    std::tuple< cudaStream_t, cudaError_t > wait() {
        std::unique_lock< mutex > lk{ mtx_ };
        cv_.wait( lk, [this]{ return done_; });
        return std::make_tuple( st_, status_);
    }

private:
    mutex               mtx_{};
    condition_variable  cv_{};
    cudaStream_t        st_{};
    cudaError_t         status_{ cudaErrorUnknown };
    bool                done_{ false };
};

class many_streams_rendezvous {
public:
    many_streams_rendezvous( std::initializer_list< cudaStream_t > l) :
            stx_{ l } {
        results_.reserve( stx_.size() );
        for ( cudaStream_t st : stx_) {
            unsigned int flags = 0;
            cudaError_t status = ::cudaStreamAddCallback( st, trampoline< many_streams_rendezvous >, this, flags);
            if ( cudaSuccess != status) {
                std::unique_lock< mutex > lk{ mtx_ };
                stx_.erase( st);
                results_.push_back( std::make_tuple( st, status) );
            }
        }
    }

    void notify( cudaStream_t st, cudaError_t status) noexcept {
        std::unique_lock< mutex > lk{ mtx_ };
        stx_.erase( st);
        results_.push_back( std::make_tuple( st, status) );
        if ( stx_.empty() ) {
            lk.unlock();
            cv_.notify_one();
        }
    }

    std::vector< std::tuple< cudaStream_t, cudaError_t > > wait() {
        std::unique_lock< mutex > lk{ mtx_ };
        cv_.wait( lk, [this]{ return stx_.empty(); });
        return results_;
    }

private:
    mutex                                                   mtx_{};
    condition_variable                                      cv_{};
    std::set< cudaStream_t >                                stx_;
    std::vector< std::tuple< cudaStream_t, cudaError_t > >  results_;
};

}

void waitfor_all();

inline
std::tuple< cudaStream_t, cudaError_t > waitfor_all( cudaStream_t st) {
    detail::single_stream_rendezvous rendezvous( st);
    return rendezvous.wait();
}

template< typename ... STP >
std::vector< std::tuple< cudaStream_t, cudaError_t > > waitfor_all( cudaStream_t st0, STP ... stx) {
    static_assert( boost::fibers::detail::is_all_same< cudaStream_t, STP ...>::value, "all arguments must be of type `CUstream*`.");
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