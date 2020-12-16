
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
tmXknKYREzHB4pgO7qt8vdeCmezUKm561dGVgBlDqC5M/akJ7p2Wvs6bGdpEStEIIsXZhce6kaffXMWn2i9FTyUB3ffHyOxNmyfc9/dng/t+D5TDnfvkvqs9/AjhnpVS36/HZY8mkGb3D1YNl/7BmdSSU6ElG0vFJtq2Fv8gUpRXhelieYlsxRMVXrApZxOgUZEeOw75fifNEdqItDT98qp6E8yzCEO3MUygo0LnkrW6r4IdhdVsrZL6HSvTZBoGq8Km86SRnnlVnalp7aEFfLD0pvHoomRTTt2tqtE/Hd+446RW/y68JW4+j10neH98+GAwTj66GQ3hDzSAv7iB/JwG8n0N5GdtafL8xOo/N5Bf2EB+Uf1826JxySVyzGRSj9g5R42Zx9tbx8xI0YVwTRKMeV7VSVT+RShPXuqT7eOPk/YEsHiO6nK7xtA46UTjZNocHicP8zj5uM8PHSchqwLEqjPZ1djS8HnpYRdLBuVR+9+aTe0vNF7I0pxUzidi1sxmYh5hYjIEMdHuPIGZM9ukZ7bBvk16ISZ6v98dog70+hum11I+SOUbY0+gO1DhprQn0MT2FDexfE4Ty/uaWD6rieUzm1je28TyhU0sX8TlHc932xydAUPFQAAkuBOncJbo7q2ou++agd39euzuk7i7+2CRFz1pBTFTQLQjiBcFxM1WiK/OERAdccE3nyaLYYpppc7wuprq+TRAz9QhVnpEzCCbWvcj0brJ2LobuHXhc9Qlq8Owgeip4XJ0aAXMa9Vdq9fd4hV37RaGxhSoxZdE2Lz1RmgMLjl2e6NAkmWcDyWx7qYS5Lif7+EQbww9n6hYfQtScStScRtTcTtspWnKFbDO+x9j9Q2g+nrG6pvP9XU4VvW9dBHXN5zq23wz17eA63u89zGqb0SsvqFU3/BYffO4vvObWB/1QBp82vclnjNO4VmPvv+uEAGPweqbEauHmr8ZwfuMjAq1owt3hGATeQ/Hr9yx5X1jJFAApbpDZne8QO3nboEjm/cqZYv11mz5eYk+gD5jCd63g1mbD2adXofMEINz0uuuhfmpOZSRaclwxzK8GRuqLXkJKs+Smoip4jb6ZdhQ6TV0P1Os9Z0fGkO7HQoqRYH1XGB3J1GgvVy0W8IbzD6ADNodQFON7urDnBcQYbMvELdk87aPxJpQ5Waon49O/qGtjFhNM0PjfC86EsphVUF5yFKVHILzPrkPhJQFKgaf+kQH6YaCSoI1utzodUkuI9baOUflbh4mrvkpYmEvYP5Qx7QRx+RDHf+in73/smO1ZyD133rblXAbKO5e4IsnfXyVexFu3JDnM2BRtTHOka7+KqH/B6rxc+1FPH5WYf20jUXcaSU2zuwWwd80Y9oA2qSC75h+UKRn8lovZB007RIwjsB6rPpSdWK1ukmrrqYP7Sogi9OXdEuP6WxB72Xd8ulZIm58IIHOvS/Jd7lxE+zMbialu68MAcutgI8S4G/FFSu0pY7H+6tJbniWW33qqmkxfgygFwXoigC3G5ODOMYMPrJvIk19e4U2BdON2duw4kuHY8cXe0zzsNVEqSIdu/C7f+0GLKBx4DcZSGFEjTMjXjtQN2gaAggDC413y3xEELBY2GWU3k0YWz/8zSfdsFUc8J8GmCGZes/QbnwPzUo3cRfroyGaV3Ul+ecrIuki3LG4mfUeccH/HxP/IxHy9C38P72H4H9/O2raxUbsy1cbB8Lqtr5x4iglaOCdpMVzWQPnCg2ca8bVB95n9kDB5SIncsUum4wNqSmCJRkbkhJ6b+aM4MKklOjzcZpSI0NmeGU37tX48wDRlIToOKd2iPrPiNWfsaEgtUi4Nra6w1j3lryqCcQ=
*/