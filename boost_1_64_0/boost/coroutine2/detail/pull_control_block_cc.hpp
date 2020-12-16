
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PULL_CONTROL_BLOCK_HPP
#define BOOST_COROUTINES2_DETAIL_PULL_CONTROL_BLOCK_HPP

#include <exception>
#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/fiber.hpp>

#include <boost/coroutine2/detail/state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
struct pull_coroutine< T >::control_block {
    boost::context::fiber                                           c;
    typename push_coroutine< T >::control_block                 *   other;
    state_t                                                         state;
    std::exception_ptr                                              except;
    bool                                                            bvalid;
    typename std::aligned_storage< sizeof( T), alignof( T) >::type  storage;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename push_coroutine< T >::control_block *, boost::context::fiber &) noexcept;

    ~control_block();

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume();

    void set( T const&);
    void set( T &&);

    T & get() noexcept;

    bool valid() const noexcept;
};

template< typename T >
struct pull_coroutine< T & >::control_block {
    struct holder {
        T   &   t;

        holder( T & t_) :
            t{ t_ } {
        }
    };

    boost::context::fiber                                                       c;
    typename push_coroutine< T & >::control_block                           *   other;
    state_t                                                                     state;
    std::exception_ptr                                                          except;
    bool                                                                        bvalid;
    typename std::aligned_storage< sizeof( holder), alignof( holder) >::type    storage;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename push_coroutine< T & >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume();

    void set( T &);

    T & get() noexcept;

    bool valid() const noexcept;
};

struct pull_coroutine< void >::control_block {
    boost::context::fiber                       c;
    push_coroutine< void >::control_block  *    other;
    state_t                                     state;
    std::exception_ptr                          except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( push_coroutine< void >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume();

    bool valid() const noexcept;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_PULL_CONTROL_BLOCK_HPP

/* pull_control_block_cc.hpp
yP+st8k5XvBcUlZahfYkp+lrp2hdUKypSzI1Xe9P3xALKUKTY0NBHmFO0LCD/Acyen9bD8n+WrrvGUtDTRvoe7pISiNrAjraQueFXIC2WQVrv89LsClL90cNiHWW63SxDqiDdXds00jfO78EdIhAb86z1PmXvAWfYDcpixFR+Ji+39LOueccBUVq6r3jIOjObg3QfZkNeLVp3LGcEfPNXfZaS0f42+Og96wwWVZfMrTXKN7dlzbKPbTV97/eyBut+4Axuk/2BaWbUW7w6tPGlDTE2reaIPwTrKWU0Xvvy9QdMB91Ht3EnH63nKBYBQr6XqLg/SWdj6zk3ygQyPw9TZ7RQZp8lij7T2764mPyMp4nUPDbPb1HEn+rrPV9XiNKL5RxYf7qWNBxPCQLG5I38JXwloASukbn1er6nr2bsd4jkXxzR/41NyO915P/T9/OtTpA3a26mr7QCB20TpN/siXBxtZ6v2Gv9SqB2KJAYmf9Zd9X1u8VVCM2MRq6cUO1ny/QeSaNoJ7MjwSd8wJ1Wde6OsknqlH1s9aDP8Ckx0t4yX9N/li9+2+hufrxgxvyDiJ2w0nn6SYo8a061DsNKS0eWYOXR9+nFNL3xCft4K+Zhd5fkexkQRu9ZB+c1fkjLBuAxrv1Ped0xKqrsTtV1tyQhjpf5oBcaLQl8tbSe1Frd/D6yX5W56U/Ia/2LKp9mE+wN1D+drVboC/deG5NHvCMCVyb0Pj6xwbGS1tky25DEKgg6Tjtumsp7fnaif7oLH/TTkTIkkOogb4pHJuj99nXCfadlL12gqCJzr8lTOR/kWvtaIK+t6pCgc8rX93vy/8S5Im8GYi6XR/ALjqi7/e1l3XuK39sGwLjDDfdh/ro/k3no9rkreojey1Q81emkM8YkL/c1+8B5KLJ+lpBlpeC0w4PyfOzJjZDU630c8aG/280bnNB99OrUdP5hcAHGaGImh31HkRd27q4P3h6VjtZw7tNV/KKlJD/5RxNhqjudY2m6r/T9786Q8ysr/fy0tX81gRBChJ2UbohTd9jl0Nhy6KJ5YmUP7aeG3hD4bRasN47mmo9lfP7kisC7mul3wdx0vlDk71RHVizDWbOuH0g6LFT5yPtv5Zh+n5hiTt4D2SvFaVD8xbQffw5fT+jzWtKX71f02FgpqXe03jLXzKMdmcd1ve/Mxgb9+3BW63PGZY9Ioj7ru/3ZVN//T0Fea8TcziPvHXUAR9//f5GvL638gL0sr3mr76CHa/37TUN8mdL8shxev+nS5DoRmj81XsYH6M97w9bafysuB/bCjoXBcnpeo/UWPe/nfU92AVf5F2h89EYks4ijsyTi/X+mvyxWpaCE7ReaRxs0qm3bRixOtrfpvz6/kNPAG68lL2rvIDf2+i+DMZHBej736oaLzcoaKbSB066Tz4J3vTxFGRp9lRSaeeagF6qRzX/dMQPH0dpGTkq5qvaqjMw/llqH+rp+Wf/ULO76o8J+j5Fftvan6mWNdoH/sIJTixC2b1jhPdA6986f+R1pyCiut4n6qlFTSeS73QZm6bAUsGDZ9rf4tHz9nbSX1uSd4oSO9GJvEe6+Dp3GFFbyuXjuoYab+1Z1l80IFhaXvM3nVhaG63PmsR5JEJFeQispsuerKnfk6nkgv66AFWgmr/e70IyrjC6Sgl3Q95M3c9UQ6yEwsRKBlLj1iftv2PtwOtAXteGej+kS++87nDV4KjOW8502WY9unU8r/c5R2j8yFjqzr9AbJYeyG+dRmzDLZ2ndUHrriZ7jtLvPRxFxZ0u+4B3UPcVy8Dz1EcgvV8gzDydiWc66vsjMRTxBLoXv/bz0rr/nQpxBTv5O0O90F8YAGs=
*/