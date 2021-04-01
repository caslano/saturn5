
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
MUDYyvPgkCK543CTW0JLxGfZ9J0hM3AWZ5Ebsbw49deOZ30+1mEQGw3qu9sKC3xQrjn3kn+1N47iKMzmQcZu6y4+3ek6uGrjafpNzC3RxM8mgHlOO3OfFlQ/c57qkHxrH5mWvmuJR9nbxY3nxrkf5e1oLq5LVmtuelizBjOTjLlmf3CKSbpsDUGlRJMrQVLs7HG5tyTGR7HfO8elDKNOih4tV3xI1kRlh/qWc6cCJ/LWJwhG4RnZ/eS5j6n0D0dL44k9CXsksyvHxNwSuUp+PrJNwrW/ZJU6dLN4PXASesyEmoxzEUmJv6QbneQEPN5r9p+CL8O9nRdQothR4vl2SU/WMoIQmdqezaWm43zyBv+lf83AsLNGJdPLsiohEp/V8OYkzrGYo4m4Ixt47iVxyV4tHGGIVH/GIm1xjm/AIlRrCRK58XEPIlo8UGlAPgszplXabvuuzm4m9qDqGcaTwKH57CMB2+5Sz/tzWhgTWPSzYumUfI7faY47VxtgSaELtmkwTH6AK6FFy62e61GKyGA1KluoVuJs169Y6vsI80n9veJNrnbM5nI78Q==
*/