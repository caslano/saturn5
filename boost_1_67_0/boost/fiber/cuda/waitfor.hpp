
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