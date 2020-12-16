
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PUSH_CONTROL_BLOCK_HPP
#define BOOST_COROUTINES2_DETAIL_PUSH_CONTROL_BLOCK_HPP

#include <exception>

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
struct push_coroutine< T >::control_block {
    boost::context::fiber                           c;
    typename pull_coroutine< T >::control_block *   other;
    state_t                                         state;
    std::exception_ptr                              except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename pull_coroutine< T >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume( T const&);

    void resume( T &&);

    bool valid() const noexcept;
};

template< typename T >
struct push_coroutine< T & >::control_block {
    boost::context::fiber                               c;
    typename pull_coroutine< T & >::control_block   *   other;
    state_t                                             state;
    std::exception_ptr                                  except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename pull_coroutine< T & >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume( T &);

    bool valid() const noexcept;
};

struct push_coroutine< void >::control_block {
    boost::context::fiber                       c;
    pull_coroutine< void >::control_block  *    other;
    state_t                                     state;
    std::exception_ptr                          except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( pull_coroutine< void >::control_block *, boost::context::fiber &) noexcept;

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

#endif // BOOST_COROUTINES2_DETAIL_PUSH_CONTROL_BLOCK_HPP

/* push_control_block_cc.hpp
Sh3iaqhaIwfyZk3TeVWxKl7yb+id4FW1UVWv1bs6B4CnhnqlyL8m4m/KO6zfDFknJ0x/fd/46SZJkxo6v2m3L6tDV/s3kldeksL1UfZGbXLpFUCuXZsg5h51926w+PP9zEfp4NxIkv31KyOPNYXedqXuiyqyh2Q8vZOJ+NKImLvcn6U+CU83/U9LkdfhGQOpgYn8Q3kpbfyO2LnHoLRM0vsD3Q8GWJM3Pp5YU3mK7k+GLukYsY5C2XhI51Ub/f7BQL1Hqij/UCPdR9VEmNyyvedVkD+sVIDuA7zQn5ATC+v+7TwTNiofAJHhOi+kEXsQS7Bmri36G+Sm+1D9HsU2nY8ayH81VPfx+lrnRiutL1/h3qm07n9DHcGrSY0DObqv1ZfF7ro7zqOPWezF37Ua0D0cRN0GGmZh72WfVtB+qVeiXvpq9UhJnT9Wk7dKXTZKSdPd+h5spPzjSh4cr+8rFKtdX+fz73ovugmoomNJTpmMgP5nLBkv2vg+bSYI6IK8Ax5a0b8Osg/6MIZ89GMOzcwCmW/1ZD8v1fz1RUNm63U+1w86ziiGIhZ/0Pr3jmCnHELmDzX+5H469QdE2LqThgKPUPqzvwvjZYsd/B1Bp76/13mrAuJX0xx8XQ7kEzLKF09ErOQuep84GIAaiXrPugjiAWLjinaIDX9k70qgoqrC8AwMMiDEkEjYis1UlFYYVJhUUFRTUVFR0o6pZWGpBWU7Bpo4UVZWtmv74inbDG0DtbRdbdGyEs1iEE3LUjNi+r735m3z3jxAW8+5/znM3PX7l/vfe/9333tDCvBStoLRpdxJqrjqNXL+DpoSA/l6OyEfTZf/GPBe4zK8ZBcYLHkgUnns22sdKnZv5vX5cu6XB6F2RS/An8DVpzdVncZ7VIEhkOpdOtIdfA/j+hJ83DsJ8u3ogJkO59q5rApQOcNQ8fFKCLQvZfbNgBgv0Ne2NkHBuN15PV0B+OUJjIfmcjx4sDVjTzTZKY32YzSczNfDsobAQhu/ycT41lO+JRBj2P2wwSkDeT7+NBofw9vQmXOQrWBFj8MhQWE7r4/m8nq63QF9ibJ/GdqNZYjjPR8ft/FCcd8g48mDeX+GFWtY8UQ9UMq5vS/nWcaTvPIawhD26wPQbnMMPlbNQW396fS/SnzM46FERxPXlz69oO8g3l89kOclI3l++hTf1ziF8d87YDnhBjTuux5laxlvLDiNv38wmfHzuciOuJfyBQB18kgA1I2FLK98itrbeV9tzo3cf5/l8z68Ozcog8+v3Un5HoRh2/cF81vu3wF469DjIa4+Uwk1dCvKjliLvpcwvvIt4/nQFuJRqs/35P23n1D7+sPIzjqZ4/sm48mH4awXt8JCe8ZhLJN50ubmnerTZ+4OPBgHzxfz+nwT9w8yv38psuMfA14zL6p32RsVZx6KsiZa6NybAXrovj2wHpzC8/ulMKK/yQl/3qkv8Kj5JUnIllYnAm/ELpCvCh/Dj+V634vrcxD6pt+1G/ZLTpKRQ3j/l6N6VA+kLlsCG2Ql+eAvax3AeyiR+y+yr/DuzZFcUN7nGXJVFiR1lCP1XAAs7ylFti/d50M+PbHTkUC+cBBAz2OP4EbwzbkbUJdThYHT0K6UTweOqoBoz7ajxzHHJUO+PVD2+tno9sUSfAz4bif+HiOf51rO8xem1vFj6l0Yj1gOzwF0299W94F89L/beUYx6Z5UyHcQsosYRJ9DI05Yx/NJBnwjD0O2he/srfrEDfle5f47He1e5lK1uwvZ+1p4/4g3XtdP4Pk9r6x/DUEFD1f533fkfONEXHwFatvpIC0MOpb8iLL9jwB8Fo87jh6XCrxByCbwpt6UiQC9ifc=
*/