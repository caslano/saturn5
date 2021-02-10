
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_DATA_H
#define BOOST_FIBERS_DETAIL_DATA_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class context;

namespace detail {

struct data_t {
    spinlock_lock   *   lk{ nullptr };
    context         *   ctx{ nullptr };
    context         *   from;

    explicit data_t( context * from_) noexcept :
        from{ from_ } {
    }

    explicit data_t( spinlock_lock * lk_,
                     context * from_) noexcept :
        lk{ lk_ },
        from{ from_ } {
    }

    explicit data_t( context * ctx_,
                     context * from_) noexcept :
        ctx{ ctx_ },
        from{ from_ } {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_DATA_H

/* data.hpp
7bjGKDoQu7YRvLzj/Id2uuNnJzBbLRdxkuXJMv68ztN0cRqu4SW4x68gUpek7VcuuI3YUvHhtf/TC/85LtBbzpne55obKjP+UFEajaYnEAVnofOg5c0z0C0vUAPQduKSYb2/8L3VdYU5Z4vUVhVP47663kOBHEgDBe+MNZ2uozhJ56nzRMii6UsObymWQZv1O8e6LRSu3w9xQjvwtEb7DYrnofBQpTXr4OkY0tGv1uWHMJ0t50k2jyMnYVgcBq0S0pBssFNA9k3zjMQjJCMNkBrkxdh5bMdxa+i0cWPs0y13/u1picdIedjG3W1iqHVKy0yhpMTpSnh0SsCTLEvSgSVr3il5xfrG0PEddi0q003CM9cSWqAqt5zSkxdo8QrV5myq+UMkZOsknLw82lSJ7zgTEQ8VOWMF4ONnVHizPxqaYKg5ORIXUnU0pypLO1xh8tteYDDsggmpjZNy3OCQdUzqVnXGh/srpH3MUNvkbnOA+W5pLHWclXuH+oMUMY5EPIBJ4QtylJzO0ifHLwZKkTCD65YwPEcCEpUo0CimRdVgLfYXvlMKpcL5IpUZhic6/MJ5a3GHYnYKBwWwiqqOehoKgSQ4Awn+qJSPwWqROdFqsbALyGsWz+JF6gQ0zXAl/BycJYvQ8WXlDIK0
*/