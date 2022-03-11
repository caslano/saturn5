
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