/*!
@file
Forward declares `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_APPEND_HPP
#define BOOST_HANA_FWD_APPEND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Append an element to a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given an element `x` and a monadic structure `xs`, `append` returns a
    //! new monadic structure which is the result of lifting `x` into the
    //! monadic structure and then combining that (to the right) with `xs`.
    //! In other words,
    //! @code
    //!     append(xs, x) == concat(xs, lift<Xs>(x))
    //! @endcode
    //! where `Xs` is the tag of `xs`. For sequences, this has the intuitive
    //! behavior of simply appending an element to the end of the sequence,
    //! hence the name.
    //!
    //! > #### Rationale for not calling this `push_back`
    //! > See the rationale for using `prepend` instead of `push_front`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{append} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the left of the element.
    //!
    //! @param x
    //! An element to combine to the right of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/append.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto append = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct append_impl : append_impl<M, when<true>> { };

    struct append_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr append_t append{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_APPEND_HPP

/* append.hpp
2oIc35AKdeiwRNbPeIF54W4cy+eNTWTeQ80HyICoxPNO3qWl4INV+gLGfwWPmjYMDh6fLAcXER342kL+01r2mwHl+JgElHKabIeFs78RXqGGs6ujvwxnRwjReZild1BvV1/7DKtL4ZK0pi87Fn3pyAHzcy3HTMqLLdGJ5hfzVzrsG+fy8IoQvtz8Fj/0TNCdCtOcU9nO6tsYXmDXsxgypZ6fL7K5yNgHj2xQyed6a9nZRepZ6A3IBTshmakw0Xy0WTqlGIv+peh4vnG+GiMt0XTHpljBoajEAn4kkyQAuElhaVg+NOVNlaW4qSBvaZROKbXWbpYy5oE13mk08SlqMj+jcErRBJVWk5oH3oU53XeRQFePDp7sW6a/3cq3sb7V+tuX+Wb13kWtjxmI8r0Ky+PhHLE8kuhxtfd7rKOTZIqdxdYoDoMo3I1l++144SWqVS+sUA8hUpmTAKLj/B9fBAYsJi4ChCGwPjQ3drhI77BCfQSNGGqIRs5mNkOTp2eLJichB/5fUhMPJOqdUGz1jX4Gtss7fmUUG30eF94P+BwwYOXUf4MRgDUX4DsVt2/BI01iXK0GGqFcIRrdYHxDTq6BMGVr3N6MIPy5EzX60GbQUr6X13Ih3tNLRIXQBOMGfEuFM8GtwtmMc9742gtqAyPI9Y/S+7gRXYZ/zSNGMeLvXmO0KVjXqjgBKY1iHaLiF4NoHSOaXB80hXFzKubxYVZsHwAqg2dvtMphwYxnGOPcxv2BGP9mPPabM+PZHvWRmUQwixAgpaq8c7pFPMNMaQB7dzKrcCFJs500gJ3NoFGyI6Uyx+OV461EOGq84cNsyO0hPu5gaabFo9sXu+qEIawQPM7v2ND90xbaaNW3u9jehx5NIecKYfwiBPZ0yNBfT654T3q1/zCP6/bNiU7GY/NmJSOQ0xjpGY8KtvJXJn7hnKa6ZveyWlphtZTS/Gc0+TnClxMCg2KGg73yzMQNIxpuGZLOsyW7URtnxGOJ06gthoZ9Eoth01LiX3128n7toslmpVg+3jC0QerKz3Oz24QL1/W7uDx8+F5Uq8+FGHMLzap0Nhy/eON87zYegBcYY1LvonO6I5lPWSE0Nwo1FyRUzjlEfmkEgFDf5VaDFmbAIb3J6Rvs3X8l7xK8cgzq33pc5dLW4+0bU1kjy9wKSHEwr4MGBMND/69Rm9RBf4g1GcmDeVwx+vFYVsPNwqSmP2JTYiB594rePo/2KPOiImqhxm16jZMlKdLH64eXBTfCN7O83ONL09ZZcX75ImmFPZVodmI15AcRAXGukoERMTyJtejZ4E3Qb8PchFcohrw1pn5n43ADb1A+bjfTlGwW18Ugd05IDfQZesSffJjWyyh5YOwQxt90v+8d3PP9Nz3fyTQW507nHjgUB4XnjayOCBdQ40R38BkNAvDijvp9Mf3iUaOBPrtSMLAPXzlaGOy8HIEWnTevKwt2zuPT8nXIy+PT7HXnBzvtOGt0nokg0s7J/mnBzin+KcHOHL8j2JmL68GdU/1jg53T/KOCnWf58WWN8/wZwc7z/WnBzrly0dONE7fWykV/rN8XuLMStuPBVSuaMnl6iDTR3AXNaVDTSB5jV5xIiNdHJa4n7hVn9VhPtI2udDaTNrgcS4lOs+gaxurOTt94XaN1Wu3RjZtG1R61bxhSe3SIf1Dt0aGBtM2LJVt0UGuhZJuG8HRXzSghSeA3f/JIV+w61ARnc3H+zJrteJwcL30gXrppVOJSAPn9oek6N+thx1wFy0QA/33TPw2Xc2iW4C1Stp/aB+50OJXWSWbscTcNKgm2f1AQmKpcZGHY10Z7uMy0akstNp3AqNqbNfhMas8zBIYEm6U=
*/