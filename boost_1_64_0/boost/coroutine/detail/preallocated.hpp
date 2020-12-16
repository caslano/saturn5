
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PREALLOCATED_H
#define BOOST_COROUTINES_DETAIL_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct BOOST_COROUTINES_DECL preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated() BOOST_NOEXCEPT :
        sp( 0), size( 0), sctx() {
    }

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) BOOST_NOEXCEPT :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PREALLOCATED_H

/* preallocated.hpp
4oQ7GK/ADsCzkbHwrzWYBt886Hl4Dm+XIRtzka8+rLuLWGDSS8RX+Lt28WCCRPSGuT4xHruKTL6M/OUNVEQ/2n72uCp+nUo7jOOqaGJG/NP8+ap4cQu4HPPXM5y53Q6eYiwf7GYeyMecarwngrjk0Bzk5ENVvAEmvoQ1u+NL6qYTO2Cvs3dobG6q4qYs7Pzv2Cdw3TOMN/Mk8k+evzlzajSHGMcNRmMMH6A3b7SAR7dSh3jl7B5FtKwJFurA3Dzg6pnIyXx84g2Y5G/AUp2I3TqBhfdjv9vxfQfW6LsnVPEdmH8Y/nJ5FzBwDM8HMIcs8EgU8cNnG1nfL9D5vYw9jbXfD74eoYn7ie0XO9HJTOzmbOS8GnYwjnigDr/deE9/W/jxNTh2HH2Bp8pKsOX0eVU7rlGuprSlJFNGUkZRrqeMo1RLUPH3irgH/1oHHJQKbT1yPmIb+BC9ii8iruqDLv+C/buEdx0uV8Si2MC9BehI1mLWNBe/EY9tY74bL1fF9PtVcc0TyDHy+QkxyYO79RhL/84aMb4LW70ZjO5ER5lrGP6wqg+9ngSW+1YRHxBnXF4P+/aJIua/yjOMYIeUu8DMzxG3HEY24fXEb4h/sIfTwFl/oY14sMy1HmQSGU1Yit3y4ndoYxRx7PeTFVFnJ7LHeIuRobJaYC5kq3c/8Bc+6td5rAf9bm+HnjyGTMK7gQnII/G2C0yxZ5kmTsZwfYTqzz85emHHaGsrZbO+F0T5gPJRO8ZM2U/5jLIK+fr4pCLaZpM7Yb1PIVv5N3GOnfjrIHFW65lgeuSu4zjwKXFJxm5sKDmCbMZfIw/8hs2trgZ8dvRDitibg49kvd/DXsSoyKKTHMSjrCPY7W1yTcvJBTQmXnoav/r8t+AOsHTn4cRVB4g5kOf6C2ifeW9ugN0gVg9fiX4hK081VsTu58kt/KKJR9M0UVCNOHsyusZ4bwcDfmXHDj/AfOeCd+BDtRLCcuxhO2K9RMoIyrwz+EH4lewklmDNpuI3u+biX8H3AxhH6iryUOQAjvbGD+FTPryJcTOvd/FrTU5jUwaCR99Ax7DZ7Z+lHeTdTrt3XIld7ove+sA69cAT+OfwFfh18MWWl5G7eHThbXI36LiD+ulPYRvwU/UGY1uJBetGgfN02cfHuvCtLZHlBsQS3z+DH6J+DPHbX+4ipqafQ3eQEyF2c2NU7KOIX5Dxy37V15GYFh43JD5+7WNs5o/IbG9krwW+DR/07O/EFXmsfxK2uDW+9DNFdP9Z//4hMfBx8BBtbV4GdjmIbSQGL3OCcckBrgI7LUokp4UNuQH9j7kEn7pIE0nJmriKMc1k8XdRbzC47tgKbA12pxo2rTY8rJ4M3kWGollzLrGGPFf/M9isH7aWe75vAc+w3z8Qx955qX5GE1kg31bvZnKTXbB32PGMt1TxcFP81/vYhS3wk/inFjHKbjBZ4XfEUteQL6QUNWEt30X3wYtPRYNrybkJ1vsUPu2xnWA9wZgHqSLrL8QBdcAzy+AttjJK/2apLhuMy90MPh6lL+Twvmpgn6uIj/6KLHGQN5rxDcFe9l2HD8/FVsCn1wcoImou8Rv3dyTf4O6PjpeA88FbD54EC8Pz36EtthH3ESc6yI+1fAJbuBbdY90aTOc03WqwwZ8U2sM2wueR6HFj7GQG2OkkMl5C3utT2h9NvLkNLH8Cfg+uDc/TiePuRGcyifd/RuY7KKLGW/jmD7BTZ4lx0Lt222nrLvjVEr2i1KVcQUmaTq46Df+DfKSiV1Ps6Pnb4Jb78bNc70DsdBW/OchO8mzy2Pytt7GG/OZPMeCJqnp8iE/CDnyeg705jC3KJA76BL2MDfCwGHk=
*/