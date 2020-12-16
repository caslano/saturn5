/*!
@file
Forward declares `boost::hana::fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_HPP
#define BOOST_HANA_FWD_FOLD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/fold_left.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `fold_left`; provided for convenience.
    //! @ingroup group-Foldable
    //!
    //! `fold` is equivalent to `fold_left`. However, it is not tag-dispatched
    //! on its own because it is just an alias to `fold_left`. Also note that
    //! `fold` can be called with or without an initial state, just like
    //! `fold_left`:
    //!
    //! @code
    //!     fold(xs, state, f) == fold_left(xs, state, f)
    //!     fold(xs, f) == fold_left(xs, f)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold.cpp
    constexpr auto fold = fold_left;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_HPP

/* fold.hpp
KkDFJuJKq8spP+0fLvBz2RpaBa9yZ+BvFAO1xiCZw9V5tIJSPcqDTPZyiBEYOH8wtvUFHVIXtH9tPI53pljSkEtMgmHnnrT8nl4YB8MECBtwpZ9Zw7kmrHJMmI76k9ftioUfDaT1396v6u1t5fbaDKLlA8Ju00mwu8MQa/eNqODzC/qH3TbRcpva8sLhnmLKt4YB+efjG75QtPyRWMs547ULTkPLY+uJxLbC1ZZIotua5M6NxPbXiXOPRxPx6yHlmUnxbUluZ5I7O8nt0N3Y3c5Hlrq7FWVEl1WE2gtqiGoYvkajGprJIEM7EBiL0f6N/uk+XdnXoqoDnl9oTPmaJo85bmI0x/D6uLE2nzTWv48b65swJG98KjYkC+c36GNtTRxrnuX6WIfixhqJeKxfjI01Z/zFuIwHN9d90k/ZSQrjPkEKlZW1a+nz4Vl0AYM8+KaatJYx784U+LNPQhE8vq3lUFYGSH7GtIHse8wFVJGWdZscUhtyUayf5TzJbkNLyjb4BM7x5UhbxA7TiEZtu5obBZrv1RFRI/WGl7TtGE6n36sXIDG0R+XXVAAsnppcl+9SLoevZf1xdnJ9dXpVEv6Wk+TOHgC/1OfnAPifjm8OiK/6LhD9kKc8s1jbijPYcLxVX4b6L3H9aMfxAcJzBgnPHiQ8d5DwzEHCHYOE2wYJt/Ybroz9FGsExxzpV4O4kpIUDo3h+NTjCPv5RC9dOP84cWoxL4mvGThH7JdQi/oiq9G08uJGiP9NfXsGTfX2fEFT3dGg7puDrMFYeW99aoDyFn9QeWOdory6UyxvMH73sROD8ruFVKitWmNqB3KnhJhuulnolrz/HaabLsGrruhgZyojklemMsVSMUzlpR6uzwkvzFTZwJ46pQXB8FaZsCSGSGfSV1QVCUDgGiCi1hrMDO0kbDlT+gbzsHcwJ/riy3GONHo9ZBZFXDFW5BrBtMqREbkkDVJ+39USuJXjM1U9xZ2VTMeWIyiSRN4nSA+KWEJ+57eIJ31f8/EqlzF5JRs0i/BCm1p1srcwNDTHatXd5kBWtGmJ8ux8wScLLtFDcBVkGRGP0xqIIhIhT76yYG+5Gt6hRmsvomq+Bj+ytenZNtq0QFICgfIbZKiIywm7suHO7kxNIYQyXOmQIwijBGtxTBpBYrZAR1NkV3bYKNdniyzwD8w+5mRztENqF2eq0V+XXWUN9Uig9ose0Cm7KuICTHrAj2TXorgAsx7wZdklxQVYAuuJNxR0ibsjisF/AdnNyYLdHHtLI29Yj9EAct3wbdG+5XqL1vyFDvWLra+JNmsu0JioX+NFJIoOCqkJoh+/+qbJUYhZeRmea/Bci8fylsmR+TZ0TuLx4smCO4h3NcI8ajxDBv+ImmwxZ/xjfimpGWnWeI8h/D9dOIba9v6P/Bjf8s3nJedbFhOJjuKncg6VHddqO+HYzjILnR5ghIx5lq7cTjh1RqNjEGNYyfhdKOgwAMPL9bvkqmzcdvGTQtdo1hMQKImuyBbXADuruCi1Sl6lBEVgMuuMTq6iWu+GwSlxGv1nre96FfA4lAWVAGiSDodmw0mgc8ckePtU7zJlIsX6rOqsUC4k5xLVuUjJ5qN4me8G1UdSUuFDkOmTXkS8kb09yrsVTHY7dTxRHxplGpNBbHy4ThyG+Mw80j6gL8pjN8VowudFaYgNviaPcoVXI/la6ITpUe7xMGgYeMTaKLtI8v6JfVN2JY9YkzZiLjFiVTnRwXFi9f7Dp2L2EiFLIKdWh/pS7LctFFeSsrG7beg1OWi6BNJDwUwc/Vik+ztIq4/PV2aol8K0Iep0lfH0XUsBD8YCFnW6KjhgEQX8IBYgdboWccAVM6g=
*/