
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
ryEJl9dAuITXsFuUFz/+qwr/3b8iCfnzzspr9v5Lpzb483a3tm9focSOL9+W2D0Cu7OnlMRrTD8eMiE6ND8bXGEqHKHTzEhmIO6ymJYdmKxHSxJLJZfPDvQdFeH13+JC7qnu2TygGWZXU3bIFWXUAyzx9RTmg1pVPQrXIe6rw3aTyV6jazo/By6V7zNUGqdNo1cRhVwU9dJ+RsIPyWDyNvo4F71zEsZ17Bx6AVGsY8+lHeKb51Z96Lgemj7kb6Y3TqLa5rPazsPani1re1ga0xsDilJUehjrEoY6hVCbfomolTrqO6kHFoqj2fnfYbb6nKzP5dlmfZpoA5nJ6jMf6zNX1mf6QarPt93180g8Yo7Bx1Qq8Qau313dn/Yg7wB6bEFabrqgK5h8YPNK/sxrAeo5J0ql9CqXZqHAqSEdUj9KxS1zSasvr/A754VsCNiUcaQoI3oDwfXpcQieVLGuCo91k4tahdFzt/CFwZ3dTsGVTjIbOG+DYvEQ8e9GfxuzvLfhN05m4hhw4Gz6ffg3MZT2lh2P5J0Wzz4is3If9+Y7AsjwtMi+5qS/YwLLUlc0Lfq4WA2gjkV87n9A+terV+AQPBuH4DlyCL6ULDxMdn4QieHCcQhWAcbqk+tWOFHh6yosDON6mBYG4cyEf4mXZfJg9CxQroW7ZYUmv/se8dzqTHashgUTBdMLg+G9QxvqY5Dz5T2k9qfgH6cY2H+B/1n6kh74J3lp5+AcJAzy3T4fFOzezBzEWJDVyOXpDvbLnCWer2P4OlBvM+WVFHnpXobCLXeaAdmy4IZomEZO0El/S6T/Wgnr6hLALPEurcSalMCzTFlQmzFQm3BHp2k5//CdSAzFXvPJ0pFufEqFxbU4zkPTLYiUVTK7v8FGzXB6CfAJBLyCcQIAHL4nStxVMOmz8W2ufWmc2q0AhGOmjpat367CMXMejplKOWZuxPNH8m3IkE5llYxrpyAh/CVDFxRC6p1ARSp9lVx9yPwdpJbinonvcsL3+mRmli1EsfkJEpv7rBJic6dB4nJ8lZM0+h19mUaPg+r0gzxeD/bH1t5WgyaX4s5iNhR2k7OhIotmw+os6WysX4cpk0uTNJdtc4ifG8yftBtNQLsS2XgA2ylRapn3/+1O1ejGvAGfBk9xOAKf3oe82b2Ib/XXc3L/xFocH8twfFwlx8clLlBPJzuFShRMUixCSz1Ng6lEZqOia+PyF9DyuljP9wfCUPbc16nuG8y6b6C683qkUj32XUYWZq0eXzqhHpvx2wupNhFHfYT6pB1qHaKiP5iyyk40IuSldaFpH6MrItiTp/ZVWrmsZ3AOC5bRQEB0T/pjjj8k+gTserIt4SzKb9zH87Pp9wUg/ZOJ/SRKOA0SRFdhP2V+GYGpkkcM23tpOnU/z3wfLLmCr7aDg2ZTBbePXdabzaaa/0r7WLP4Px3ErNrVWQYMKKN4UmTPqZGPzm1HhH+1l8EA/CgY0VvWIFWJkAKU8mJBvLjzuHSe9Dn3Gg/BmOFpCyFNjZ3kqPV3rJ4qfsg4A1wxWDuRSfSDKV8Kljik+P2fGh5qIsmBgMlYhWha00J8E0tUswy782FQmQ6dhaHZ+Xd7LZQxin62/vXV02lFuukzzqmjTR/IOkij5pqXqgJ/ZzMi/nN8+dGbyXE/g5XUCEkDGdBA5EYY/h6Q3KgMpduyRdOKbKKa6UIbdflbn3Ch7URoCE/7FtKkShc0Pv0mEqt3wBoyoDS/KLZ99OZlKDig2Eb5L0F+GLKSGsObAasIxTJWRFH0KlxYiorrdtIG6VpGIZXHvaqt0XQN5WXaw99cKhe4eXKB+/t3kRiU2aA0Rd599DdvVBpvlG8dBjY=
*/