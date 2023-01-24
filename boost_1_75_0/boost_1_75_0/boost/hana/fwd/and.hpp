/*!
@file
Forward declares `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AND_HPP
#define BOOST_HANA_FWD_AND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether all the arguments are true-valued.
    //! @ingroup group-Logical
    //!
    //! `and_` can be called with one argument or more. When called with
    //! two arguments, `and_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     and_(x) == x
    //!     and_(x, y, ...z) == and_(and_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/and.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto and_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct and_impl : and_impl<L, when<true>> { };

    struct and_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr and_t and_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AND_HPP

/* and.hpp
CfSDEcm6XVM8TRswg0QCQSBtVhVWJ1MMZQWZqLgEIkuxwxg0FjNdsaRV0p4SkkGiMz89B2+kXbEz41U7ZVtvjkbtxDv2yoma0sA/JhH18t7kwA+EcnU2Do6OcKLrXGgHJbyH5TtIRB2CNWKXcJ4AtOZJec14hb+ktRhPDQ7gGc0oVre02LHPGv4drjWqddbt+mLHHmv50zp0rA4NUMIhccDNSlpZXXHo3AjApVYX+5H/hsVoJc3EBqCb6UEQc2MgE57jAn3gOSFg9mdTgt4CJuQFMuyGolkJlwraQQQc7+bzB6F1knaIX4KFDGJ4Q/BhcUOhR0aOEkNxyHFT8HYIxrKn6YO9gRNqDJKzDYJiAO38tQitrQe0Lx+6MjSu8et9zbAUcPN7J6hGDCyhamOtk2tgfRKbgK4SeG5gVIgbA9l4GSswKMQHodKgIdiPUuk0MRO9aBXCvf8TdJmYx3tVOfasXRf4WYjPDTzoty0dtyfQD/6K4G/+jQ2yRhNwj9sTDEDlQ6VdmkCOvKZLERzjIVlbgqZTmLPdEd+oY3HmbIPqGx3xDfChRfK1tqA/NyWzNdyIZ1/G5bEP/brl2BT/uHE11CLwiijolCj+MPz9C/7qEav4f6ydFZgc4s7ALYTXuBDvG7gbOhXa9dMGhuBdgufen6clv8FQPjuvh9rsaXkUes77eGU/9nWIPxi4Ds0hFiQuGczFz/QQ11vD
*/