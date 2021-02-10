/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/operations_lockfree.hpp
 *
 * This header defines lockfree atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/platform.hpp>

#if !defined(BOOST_ATOMIC_EMULATED)
#include BOOST_ATOMIC_DETAIL_BACKEND_HEADER(boost/atomic/detail/ops_)
#else
#include <boost/atomic/detail/operations_fwd.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_OPERATIONS_LOCKFREE_HPP_INCLUDED_

/* operations_lockfree.hpp
ZVOB9aK2n3j7FDx2TuFC+pqR3f3n+Bc+zclXL7z6xe4B25Yoa9vpzvq+nkoyBR65ZcvwhCOA0p53eM2nSTC9nIxHnzwWHTP0ToKQfr/F7zUqhtwI8ghdwneT4DrNMlifOs14pxWYrk0Vx06XjfMyUwuRBbzPFr3g7Wjyc38U9Ecjbx+9sNvJla3deaC1YqTQGyfEIoXTeNkVLitjDQgib+ZG4m64rdn7JZm37ySiHWDYtLJ8G9nJ9TxgJl/djC/maLv+w2T06trCCnl0dp5lnW4oer6Cy/6877tajYz7Pon2ROs6mq6z/EX0qN7z0Q5+03H2xBfCzgU1W9wNoTAYJup+/KihobqvMVT/FfV/ZpzM7c2g7TyGtt2mjvPlSgpM49yw1xg1MG5zT+d5xHum7pvr0aSPGfl4tO/MQoa4OxDaD/MMW90lAF2RZ1BhHJs5x+sLkO38zezmZpmmyuRihaThhqpy7n4Y6HFTgu821IGf+BYVCobuhqa3mKWcnfrZNjA+pvbOAkbLo5GbmPeS24mu07GZoSljQ3eVQDfYwSBMwEautDPb3vOWMseYlzWnKeYLhXlurMdXw9FgNvz3IBih6g/8vWK899kv+Nu60tUmYHh7dhpmWTNfIJ/Zk5zLu7GuvrBisjWOwdht
*/