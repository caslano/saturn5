
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H
#define BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/push_coroutine_impl.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class push_coroutine_synthesized : public push_coroutine_impl< R >
{
private:
    typedef push_coroutine_impl< R >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    void destroy() {}
};

template< typename R >
class push_coroutine_synthesized< R & > : public push_coroutine_impl< R & >
{
private:
    typedef push_coroutine_impl< R & >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    void destroy() {}
};

template<>
class push_coroutine_synthesized< void > : public push_coroutine_impl< void >
{
private:
    typedef push_coroutine_impl< void >                                    impl_t;

public:
    push_coroutine_synthesized( coroutine_context * caller,
                                coroutine_context * callee,
                                bool unwind) :
        impl_t( caller, callee, unwind)
    {}

    inline void destroy() {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_SYNTHESIZED_H

/* push_coroutine_synthesized.hpp
ZiKWmgf6cEFtPCN/W3QCPl7JDz+Ta3tWz1vENe56Md68zzSm8vT38+LjPfhDNwydbE6s3/Z6gy6jcYc1gpMV4M08ee2H5rEarLHvau9jxjBHrIwXv1ca05e4SC04O8GaJs2cai6axOOFgMPV+o/Bgc/prXbie/cQPr5TPzrJqayNTP8U5qWJa1gW1FVm4ZHuA9V52sC6z+X/r+Mo2HHdVXDWZ73prQ8vgC2f0b8T1aLE+e198N0n7hHUvGiOsaPY5Tn5wlH4wD57tI811B8a2Qw3R8IDGrEefdjHemavIdaQ2GZ9a3a37nAbLXMvnilcTk1HzpavNC65hu9MhWHHrMmK1yJV1HDfYuO3aCPY1aizXP5mWMSvnqQTD8OUiq77Dm5sVY+az7eSfhaHt8irH8SFnfWDDtzCD2biwWb89QrPiz0g3xTjTe9Vg1STa9qR/8K5mTT+tFXiZYN9gZXENQ5ZzG/z72Iv+DN+sPoDP6oiFg7eJa/7gL83tQ/PYI/ymZo/0gNywwfGWj/DZz1o/U1qW0PcO1XtvLtxzXS8/Zvyk7vVpx6SMwZ7AEJqtWPFNPutuNQ6Ld5emq5e/xFeoz8fvsn4n+G3ZfhINukwV36/kP8Zw+pv1RrhzmT1uUS2mNpFnxbAvFG4Z4Mxs/dF1+CuJLgywH3kO4N20v37YXRNtphm/vhgCptF8rGTUXjaHDQojV8K2SdfwVhn0uWeOTDYD2Ht5s5JsGctfTZf7f11eNzTHImtMdbeTox0fhz7LoAht8CXV0KhSLb8revaTaT3ceBd7VwX4V0JsXr7brV/Oe+wIB9Rxw+z89f0YLI8IlofdsxT5+wJF8fzP/PY3HO+uIGPf8UXtsLpo7SfcU/fx9f57zt+b98d9tNkW11fuI2ceK/1Qedd5zkPP+e6YnBSTp8EZ67kHy87d6D1rlE0UJQaxfhb9fkj+9QCe+p/6wJ8ll2K0Rk33kqPnxIj6kW3wLUnH6YX+ekVP5vLMiH7V9VzktQslsLzxMjT7xpMHB2yj1KOBsviYMdFzuu9zVzguifVn0fuNV/N6atg37f64/HucsJVdLG+VMcvaw7qp72Lz6nFj4jkY4+pF5jXWyvxs/xyCf3YVsk9xfD8sLlppS4xGlY1Nmd72ADGf6WGdxntd5iPltgOMxvA1GIwltaf0SjSHtJItXnH6Zc0NemMB61vwdNrMq0H01wT2ouTAnwPdz9De6xXH7goMeddmQjz1jFsnkZbR5fzvsxm214XlzeIIxqoDe1RqQRdgzPyfy4nL60mQ7suHevdhQi5t/vvuIQ2aK9u/Rns2cEHe6IPGP0oHTKAbSNi2TULLrp/nsl44AW1n/HWGPHFygy8Tz+tm82eYqjR19b54eMf5eINjO+P9NkFuKIwvy8sDlvTJG2flg8/S3v0okmDdy7SzOMmTZxci1OriKkV++X2V6g9GHOZTvz2AvgsJn8TvI/0BZ+sCLtqqR/0xMGTQ2LVuL6DG0vohevp1RjapxtfYfMCQd6/yN6yFvRvWbgSjTv555aF4t99LrkHnuOxS3x2Cf+YZM7zb2Hv5eJ0gtp8RX55L5/oS9M1MC7nr9zL1rTCRQuMoZ/8XY6XTpNPtF7WOfBlXPl4e3w6yfjKq/e4b2WthtZDS9D6aQO0gdogbZjWXeulJVprvwrGNaGfa47F+Q3E7E4809jezdHmiuZZtINvz2DjNHjEdzJaqv/kM68wpIWa4gb7gPrPVDvVv5dx0aS28GaoufkTThhnL8zb4lkOf7Kz68XogrricZRa6SPm3ufTaNXj+j5dXx5JplnFbQN6tRXuy+vZMfywG/z5HuZEz7ffaj7eqg8z18l7+dw=
*/