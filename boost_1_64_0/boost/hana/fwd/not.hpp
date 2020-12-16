/*!
@file
Forward declares `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NOT_HPP
#define BOOST_HANA_FWD_NOT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Negates a `Logical`.
    //! @ingroup group-Logical
    //!
    //! This method returns a `Logical` with the same tag, but whose
    //! truth-value is negated. Specifically, `not_(x)` returns a false-valued
    //! `Logical` if `x` is a true-valued `Logical`, and a true-valued one
    //! otherwise.
    //!
    //!
    //! Example
    //! -------
    //! @include example/not.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto not_ = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct not_impl : not_impl<L, when<true>> { };

    struct not_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr not_t not_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NOT_HPP

/* not.hpp
AcgmxgW74oX8ducBz1cYC26T8TsIv5MMb+yJZHTDL02G00lLocwLgLDq2MqHvkoy+URe0aDlO6+h684gz0uUoPFxCqiHyQ9WgGUVK6O+wWn9St/oQUB9ncNCisRECrVbvwLHDvXQNMmF5DlsznHVr3daX6nfmApPS4TJHC5PCUXYra+wzgi1LqyONslEzkHIKevlpNzr6+tT2Y6DGJk/kyanyG8pyZRKoTRBocXWxvr1qR5hNN5dv8GJ+/vw4GkkbRa5rfs8n8uVAoq1W7+jFuPEKTQDZws3yrwZVLTKC6UN+fRRSLAJWzfxi+8o0sMo/+thPOAb5Nq7ZGWphQ31dQhn+/UkmjRZN1GPw3Y3anq9w/oWzpnAIx/j5qW6IiKTsLjF2kA1JrnE6uLQ+jqCOAjfyfp6iXYnqrK/vtFh3RJGLpp7G83fKLGKRzY2UZ8eiu8VtJbA2dBExvVmMm5RPb4IS24I4x3f8UQ/pN1I5+IEQZg1ciEIYSw3icL1ElpqCHNKCxt5wXeEwbSl7+JKqzD4KrJcchrN++rCYCidGF2yX6R4aO77c+0RYDH3rdndImPp9dTcLbNOpqDs/dnvwz804rhWL3GMijhC1pLqUXlhPIf2OReI5pH63ghmYJz0q+zmSLEzez/SQzBVj0KmUJ0dooqkFnj3e5JMbyKq1w6E9NthhOwgSJvRJ5bHbi29dDfJkUX/dnLkn/WpzUhsOpa9baLyrweMe29tTR/XH4jGpRffvMnO1LZwPt3qYWlozM+Ul+u2jULxanz6YB8jOULs0Zkur/jdq1SUfe/W4+r2bm2gM9Zb+6tGZ7iEH9Vo654inwjIAuz6bmyHOhZAfWKhBOpDBR3i+Hp64SsctCqrcYtt32YKdHR8w4+WZOEsDvHucwei2qLLujgZQOHOA21ekUBJUWc7/VK973kycYsYoYLiffpMV0hYgiNCokvw2JBIMTdsRWfakNlNl2E090JSQttxJHaWvjzvaAod5/UJN1OIKHAyNQw6CFI5UaBPLHmFouj9T5Sa4WzuuKEKn3JfmbzyAqU6ni2ZQJa2YsM/osY9pHdl7+ptwaNqxluGXGyp7B6qSw6tT67eVvlHuu71uLrQJguqhXtidqOO+ia6ZeLlSusEQCsglNjGUY0INSVfcxsk6RH/7EQuqbMlHOULpDApXviYUQwItZMAoabHECfyv4384yxDvJS/Phkgqt9uJ/+Dyd8Y+ScwCTqDpk5/4rcOiucfYVbU88D4DzVxrWXrZYnm/Rq4sNn72YFopLAgkOEVlz5PjzZ6HM+PmfQ4mh8n0+MwPOIilMZrSGJHD94Cvioi9CKnJCJXNJDHIw74j3pE4x8NzgG5cJdV9Cxx/jqQcHdkrM03LnKBbZz4+idH4hrlsZnjIsOhov6Z34oKvJHhBV6xVb5Nxttkr3gFb/q11XyldU44RA+SBycc2lVT6r6REuBk6C4TJ2OfM3FS8JyJk8HPmTg5DY/RM2MoEYNePxANXKitAIf4xMWQGahXJyhN8keP6+G+wBkMg6+wEP0+JfyAjKjhcSL04oFoOAXocwXONAr64g2mMnWmWF3ouoSD0ceeQJ9SIkQ9SExmQ3kpqkvfHT6DdhjyXON6Slycu7nyVLjAXKq/C3LpHyv9rSZ/Eq6MGJgfpQshhkVDzZbKnc3nZNdvLBg8eREuaq06aqQ3UnSZvArkuBy+4QFg0glMpv7xipr8vFb5cYc1qjT0e5aAE9BeJ256euEZZh60tKyiobzsh90qloB/p7FfgS+7gGi6ki6sHAxtEPsuUcpg3q//Yzzpe0PrJOJS5R2SDZoGKkgZCP5ZvdYQmsEdeJsGDvGCnajhJ3o=
*/