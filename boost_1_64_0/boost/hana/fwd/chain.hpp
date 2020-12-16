/*!
@file
Forward declares `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CHAIN_HPP
#define BOOST_HANA_FWD_CHAIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Feed a monadic value into a monadic computation.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value and a monadic function, `chain` feeds the
    //! monadic value into the function, thus performing some Monad-specific
    //! effects, and returns the result. An implementation of `chain` must
    //! satisfy
    //! @code
    //!     chain(xs, f) == flatten(transform(xs, f))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! For a monad `M`, given a monadic value of type `M(A)` and a monadic
    //! function @f$ f : A \to M(B) @f$, `chain` has the signature
    //! @f$
    //!     \mathtt{chain} : M(A) \times (A \to M(B)) \to M(B)
    //! @f$.
    //!
    //! @param xs
    //! A monadic value to be fed to the function `f`.
    //!
    //! @param f
    //! A function taking a normal value in the `xs` structure, and returning
    //! a monadic value. This function is called as  `f(x)`, where `x` is an
    //! element of the structure `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/chain.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto chain = [](auto&& xs, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct chain_impl : chain_impl<M, when<true>> { };

    struct chain_t {
        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr chain_t chain{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CHAIN_HPP

/* chain.hpp
n0GTpyEDc+Lu+8EjuKIFCyyBPp6yaJ56Vu/3FOzvPyHYaOMUwejZC/doBwLlIusxrs4R+uHBMGHzKE0Pio7FknGhSfQPCWWeFNPhd7u19UI14cNosnCo3Lv+dtaht4fH0kEX+4pGM2lpqm+90uiIOmsr8UMYU4DQ6jGwZz8HD5JHq4F9zmmVuEQlHuXFt1SeF0eauEKgRrbRf7Y0U8/3p7h8X7yu5vtV53zQlWpOIdnwU38h55BKi9iLkPjyVip4jl46rXutyYBUq/gKPWptXMXXahWf2LliLxifBxjRSZBBNYykEn6uF/MU1XCPKVbDEj1qfVwNWVoNDXs61UDy17fvja+BV/pKvZhnqIaSuBpq9KimuBr+9Ge1Bk/nGpTTwddx2ZDC1sVwonU/rSFRr1sJrKMsNk6wMi7BNiTA5IOtGrmWafwrpWIQhxOIv9ThaCAQydUSkQ9y1ZTyPDnwjqRC4xMY/rwBz2VKXjOEmOW+KMYSVRpIjs8Lzyreiz0UV205lf4HvfQn4lq5+zW1lQve7NzK4nVaK8+UnjoS82/Xcp7bOSefcDlkDoxhmuVVTntcnB/DIR8I2J/V4fgjtZLQhrpkImxELcwBGUUPRXoHDxkDOdyfQ57l/gx+YQYpgPJytu0A/Uy0WeFobJC8SZ0MhyyBMyhNtlvaO595w1yvcssmhhPNeEXapNdNZw8jRdI2PeCxuE5pflVt2vQ3OjVNekPP8EJchhtEBq+ULRieS5sYXuB/pwKg69/iMzpKLjc6nD8zOlbg+R48P3CF0ZGM7wgQBYPRZDJbUlJSjClJKfRJSkpKSUpOFr/b/v/pxkeT51zAbghs+vGhS8iTPklJyEufP5Vkq+aXC3YGToFwBjfa6WPL92o9JcZ2zS59R+AzunkvU/GcNr0HSwdjM0PLURPL8Q3Z9oZXjbT/Aw8dOz++w8jnx4mYhTHB6Az5+3jGKvmU8wAeXPtJ0vkhnqZIB+YI7Hdrfn7xm63+XhTFB79u9XcagRh6mMtQrmzWdtNpLcnEz7saW0GgiQ7BnM0Be/D23v6+bvVsr1t5pV14gHZBF4McjSKHlYjrF+dUIuRpEdKGwmEnhTyXuJXr26JUCXMrd4AI52OBH/Gw8y2kCSSxNzpm0j3K354h5sqDNSlP2fGa2AyjNs4CfUc2ObLzz/WyshJ/CoX7ObY+VNbtE8bHfOiUdIksBkUGczutcXQJQJqr8Xnin4mHiqSx7exf2PGGHKE9sxtL1U7issh3qbyS4QsjHJZGllB42HW1W6qGqve1Rc81V9mwtIWqHMrtyDI2vPhDzlZwK2erfEdqNqh44lVS31XlY+Szhnwhsx3THrw5Roj0VaNR0Yzo4s9ooxJdfIBuUWx3K1c3Cb1m1ZcGf0+ilZtQNX7GBjelazVtlVEo4uDuEbtP8p8DqmunsUvC2AWSns9CZVP4ZB8KzywHcRWlatsexvCTh/Y2eKlLAVQhdcQjd/LyQlIIUhlJrVpzKIuS9QK4xb9rQR7FgXdCGeRAx+0FXKqJayo2zMtfeNV4bBHkf/RHoy8/AirazIHTsPMadm2nA4y9aYBmLbcmDzUYYudwPUrW55oJ4akP8DY4063MXSdWSDLiT+N8Paycp5sOb8X+ZT4WG4KMdtMpyEhMepmXSWBmHAmkKUTbfXk3CKGDCGHPsG00/Cat2M36iqWnS5IxgRKuEXTt4Zc0acd0Lpu37xm1u4RxYc4n5g57DWnj61Ptf2oKNuLOjPSr3OB4sxczx5uOH5rByE3SGrVXqCA9tKjL0Mb4UGmFDtuzMdjqIAPA+fWTDUoKgGQyIGWJtfiltSx8qJhOPRJfbHVcsViXVwWMji8=
*/