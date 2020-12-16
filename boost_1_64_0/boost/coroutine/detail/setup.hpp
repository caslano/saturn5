
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SETUP_H
#define BOOST_COROUTINES_DETAIL_SETUP_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/coroutine/attributes.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Fn >
struct setup
{
    struct dummy {};

    Fn                      fn;
    coroutine_context   *   caller;
    coroutine_context   *   callee;
    attributes              attr;

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
    setup( Fn fn_,
           coroutine_context * caller_,
           coroutine_context * callee_,
           attributes const& attr_) :
        fn( boost::forward< Fn >( fn_) ),
        caller( caller_),
        callee( callee_),
        attr( attr_)
    {}
#endif
    setup( BOOST_RV_REF( Fn) fn_,
           coroutine_context * caller_,
           coroutine_context * callee_,
           attributes const& attr_,
           typename disable_if<
               is_same< typename decay< Fn >::type, setup >,
               dummy*
           >::type = 0) :
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn( fn_),
#else
        fn( boost::forward< Fn >( fn_) ),
#endif
        caller( caller_),
        callee( callee_),
        attr( attr_)
    {}
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SETUP_H

/* setup.hpp
vsrszOaD3qN55TGXX8+mznuJpvqxjThyftGX8P5TdBFcfwbmFStDu2bZwyQ/Ghj4Ki5+Xy1qbwnauaVYGmJc9muE9eX6dLoOnnfxnP2b4Ti7tV8tDjviTbYo0Akv3eYe+rAneBfR5z/Aho249JZX6J21fGW3PNqz2rWhg0fCuGfZig6817k3XSA2R9IL+KWlvcYF6bpOV3r+G3jb5w9qW433Yj7Rgc65gr3nNYXNxYwxmu7lQ2VpsBQ8Mpiea7YeLrumHL09Tnz/DrYPUyu7IgonZcrXjb3tW/RzPL0mVg449/6K5tpYl5SSx60LhVpuFksn5KcXh+Ebfz+pjoiDH8+rBiPP324ch+5wDnybMJmmiOfj7rNRG0Lr1e9ljumMdda9h4vnkf3FoXzoSDNYE4Er7Bks/Y4x3UBH03Jv4dAx08LyCdzWkkbwnDz61NE9ivGrB7PhUVWahx92MDd5PTdpJe0Zra+N5ac0dDDmPVretjgONq6sR4uWMH+RuFAOuAFvB+/PbWrF//fTHbjitV3GbG7nG2PT2DDdABNb5bxfW5jNrrvZXuv3+cprcBrGFnespPaZmuWQk9Yezd3d1pguHqn2yK8rFIKnvWF5olhWUy3v3EpaS+NrGseHvecxxfrpARrg3ufhTj17izaZNzE86Avc+ZK1dzq7qGu2H4f3f1Kbce6VtFIJx4rF00zqK41S+WImOwzm1wOszwb7auFoz/siT69h1pNvXBWm99QY3vXsHvvxaXP9YY99dfDDMmttU9QM3bO9vzddao4+VttvBLsS2P0reLDV3tuOYuyI+JqmBhIlV9e3ehfin4XuI76myROfYedmahNTf6teuEUtO4gZuj94J6tkDXHTUWzjihtWqH+UYYN5dPQm8/cl7elYO9w6g/6NdW1VGFR+Pz+LpP/Z/XIcskxfhurnhx3gTZa8l/5NQZKlk63PVpevwONNdOUDp2jkFuy7iw6zBpXdDh86d8VmNqDhO+/gy7Vocxqo6rsw7Hl1pRZwdBOOTeNvl6mLHcSRd8KcA+JgjvWWA7jYs5+JCvanq6O536nGOJROf2oav6S/5vl8g3H0K4xv4NEif8epx1zWQz46R39w9oQ/qF0UM0f3WGvAGyuckw7XyhTjs8vVfI3lkwu9X+p4tSJsXE1ssPXGe+nZG/BnHT6RZq5GmAsxPuBbcz0CN/LVtjdar4qUM6bBhxp8ONhbr155v3sN6WvvpvEcqWEOPqfFYs114Fvau1qJ1+DQs/zuMCxTh8lTni56Up/g4Y/f03ZwKrMhPu4jx8myP4DPrqMzNhemfWjrSGsroy8VtyfFcy3nyEeqwe7qtWlqOdCHcrZtWfKsaniHhtm+Xpzukfttp1fxR5r75K9k3PdbO/ijuie9GEernBD/S/FiF7p2NL9eW5Qf0Q+vBzVudaIxNERducVkfrdhBt+g17pM4FvN8Lc4HpXAdwfzjx8j2UUtxvkD76LT1aJ+dv0pY9iZaP8kjru/jrxmlzr2bbS7+Kl2g7xiBj9uiofaweZdIfvHxOcCNt0qt7oIn8zGyxXwZowYhCuDxOm6JvKaD2k/eq+3fO1NOFj2O3NMA2ylN+45ybfpu9XmqIKc7Oo/4nRjHfMDHKcLO5dTI+Jvhzax5UH3bCleisMUXDqmttqe+mmaGlQILu7ux6+a42JaMupu+PExvaGecFkHe7p6ehZMeEzcFRNTkys7n90+UUuaWkDtKtWz5OTvxOB1c/uNukD7wrBuIr4O3v2apEY2nO75lNZjz9Zz6MCS7IvLPrP2l/GQuLrbuqh1nHkf0AFd+Y7+DSsuh9bmHFKrt7YefjXSXOsfPbMzeH9LzDcVoz0=
*/