
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_FCONTEXT_H
#define BOOST_CONTEXT_DETAIL_FCONTEXT_H

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

typedef void*   fcontext_t;

struct transfer_t {
    fcontext_t  fctx;
    void    *   data;
};

extern "C" BOOST_CONTEXT_DECL
transfer_t BOOST_CONTEXT_CALLDECL jump_fcontext( fcontext_t const to, void * vp);
extern "C" BOOST_CONTEXT_DECL
fcontext_t BOOST_CONTEXT_CALLDECL make_fcontext( void * sp, std::size_t size, void (* fn)( transfer_t) );

// based on an idea of Giovanni Derreta
extern "C" BOOST_CONTEXT_DECL
transfer_t BOOST_CONTEXT_CALLDECL ontop_fcontext( fcontext_t const to, void * vp, transfer_t (* fn)( transfer_t) );

}}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_FCONTEXT_H


/* fcontext.hpp
XiVlKU/uOcLcbl4QgwT5vALacmdtfMyWfWJPWmHfJKd7v/NZT0rvOl3Z7Kzl9tPYL5L0Em97G6bX8JvFmuYY4s428ANAuG98uTcZZBC+nh96PdimfZV1SGXLfN6RCMv2jSIvyhPdEVsh+DpeimYf4CrtE8bTvmBc/mGfvJVwkQd7Hu7tzdanie7fvFPkPxPvWOCbKpL/9fmSL/PPX9XLuq2kNf9eT9PB/LWnzPgcSPYWxlO5c1N72guFHMVNC1YcymWWbMM1zeE3oVayXuaLwxfS/XUqtNY9+p8eS8v9dn3Dl1Yw/PQHnH/kZVwV3ibx9z+Ivg3z158aSWfTRClEUZksjyF+j/A2l3njuvpTO10cye5MbsdQoXR/m3nDfG//Vn1LBf18lRnjZUb4qbmAnLJVEUlleHL0reN0YXyHF8gqW6RzuCPULK9fePlIlJdcelt6cqiQyfUptnJRLlvj9Ev9N3H96Xy+qO94af00vUwPTfQUdwy7PtwkPHwswsNaLts+OToABZSLsgjKx6pQH6X4Wb/JwqCLhQq8KFz9GokDUiByRGOL6M8nIvrTNTkylM0XJ0jtRoWE6wrlrjKKnNuM6FBHKlcQBQL9CfI8ldWnov2lOKSlI1SjUZzyGMzNprhx/AT0gRvPnzHj+bPMezqumDfVeNc50Oeap7NXsdJrDt1VKJT6/vNcftRbJ/K8LiLPATrzmMrFWwabV+F9M6Z1bte5UUKRDJTZF0VmLwu/lR96G/NL/jcztZ2WPHS811B6D+ldbg/Hrm3XwY/jL+GlfITUqDMBDOc5jCsL9+WWuLSse6+Tb+iXcf1I2yaG0g6AaN5UukbsDNLUNB9LsCwCyu0GkVvFOtq35VKpSnUgQrSOm6SO2PibBykTR/crU/LeN5TP78rkRmOJl0fAuxZSxxTf7bIVYK7l/xtm/fJG1pXt9IX3dexmPz2k6a9ymvSXAC79dU5nd2n+NzmdoaS/9nEYjftbDnHcf0vGfbeM+29Hxn3ZpsfKdGucHJ/Abzm/+dIcPtt7GBuDkZz6wre5Noi/o/bxu4cop++JnNQ/uD0ipzDXHeOZ9Ejg4pXP55hG+t2T/uVPMn7vCMZP0pJ/KfX/AOs/BD29JlT3iLgEQf29XL/Ap7CjNYEdDfkQt7GNpar990unZV+DM6+jFI92m9cvcZPugHYvF78D6jQtL58flft23/teO+oFchcY8ahy/zHK/RD8+v64cXKIesTvxQT7DfQ33GNqNveYZM52V7PcY5J1lZ8LXix/hyhvR/8epV/hO34vjzWrS0FM+hvqnOyLk+5dI47g5aRL67bd4pveF/VNlVYnhHiKZGjfxH5vnoA5Er+dI+1fNk3f737OzzE1XPN+4BDt2a/Fng2LXv/G6nX0sx9t8NRoLM8tcfJ8guYMTqYPikyHy+mU2jGJTVAyXpL3u2axXUNZ1LXAP5RyfCZH3qb6PcirldvSyThGxSycud5S+e1iVwhmJf4IzzO9KXBEx/4o8tg6dT1xxoRrmhJL6npIfb+p65JJgj5tViZP6O4XuldU6NOFdTF9mvem7NM/NfP3KBCflPmzW+d0foSkH+Y1t3yJtTzHDZO7d9bv5yaY3rfQsvcMwyKIzqzCNvSvxpY/atZu/ya2/O9T+s+lQVuyg7CqURYBx95jAS/8t35v/mV4/Lfw+E/53jwuPP5H8Lqn5nFa/qejWdUSrntGS1g+M1vkXEZLBd09yDmvo1stdK+soLuzWzjeFd9jP9S56i9r+X1/Jw7+ZtxZ6/Q2u13zH5jHcYh4bXmT+FFzWsCPegLmmrE69gSswzh5HiHy3Evy1PZ6OH49kQ/DU7tptI/Sx6JM/s4=
*/