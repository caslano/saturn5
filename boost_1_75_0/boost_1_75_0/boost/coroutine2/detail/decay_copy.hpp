
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DECAY_COPY_H
#define BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
LVlftxXW0cVa1KlhuVmN+IYjw/mOddiSUTjc/Q13hg7SjrEGhDOZrDdmsbOqGkRQne1jEY8ELSfLOVywBDpN4+5NxMnlZqRrSTL2W0LkS8FwkhOo/TSe6xDyy8u0fEG/XMYkwW9gY3ZY11t/8ay8Jz5D4GplnzDIvPfPMlYKYwlth3uEA5gAG/heSl5KVReORVUUBqUxe5QFk63N1ARuSveEZI/h+PIiOAxyaRAZE0DF84L7OZxpUGfW1YzOGNGHsa3vYPriEQbd75KR9WLw10AV1TFwqqSK6mjGFkeAL/9UCcOa456ZT0Z23laRpdpAw6JCT5wW6AtY1NMB8E0L+RP5l1kO++oZ77j9wNsrtpsSc/gj2GFOEUT4jA+XAOKMgWRBMfXCs1vT128R6HWqTy03LPB3/qHdiiB5UFyGFhxnAvvej7T7BIo1uhZ1IwQXs9IvdpyWmlW6Ub2B3PCyBJyMTytwNqqHdVN/OJJ0QvwFgWOGILSz0vfUOJrgd51IvAVfgzn3o68tql+ERzcdCVzMm+E+i/Ls+B03WFf+1PgGPnp3d/p2HFndM8889bSDCzfn9fnu6zJ+pz/3+qkbmuVo4pPx7immWnglKbl7T6PhvqWI16fZYMy16TxmVd/4FaTE/dTujd6vTK5jK0aiyFQ8H31QM4O3PQ5oWqsaaPRL2sKraVhXQ/0DRA3y6c3Sz8QD03Rwiodggjgg
*/