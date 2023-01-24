/*!
@file
Forward declares `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DUPLICATE_HPP
#define BOOST_HANA_FWD_DUPLICATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Add an extra layer of comonadic context to a comonadic value.
    //! @ingroup group-Comonad
    //!
    //! Given a value already in a comonadic context, `duplicate` wraps this
    //! value with an additional layer of comonadic context. This can be seen
    //! as the dual operation to `flatten` from the Monad concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W`, the signature is
    //! \f$
    //!     \mathtt{duplicate} : W(T) \to W(W(T))
    //! \f$
    //!
    //! @param w
    //! The value to wrap in an additional level of comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/duplicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto duplicate = [](auto&& w) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct duplicate_impl : duplicate_impl<W, when<true>> { };

    struct duplicate_t {
        template <typename W_>
        constexpr decltype(auto) operator()(W_&& w) const;
    };

    constexpr duplicate_t duplicate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DUPLICATE_HPP

/* duplicate.hpp
7vO+5aeMvz4WtELpc/emxz6vdYboy0xTwudLPXHh/Osj7WqOt2FfpRq2euSFMYmYpIk1ndkhRPRKmrsLHZHEkNVspd9wKGvN0SiKspTN61uwONzn6s4rX2rj/5jVwWBYcbfZiZ6yqfSoPOH+68zUQYYkf3EDY7GuVSNr/licnEgQ2zuFi/W04aNn7zWD25Dg7iL9Sg2mYZPFFuJHi+iOm5puh9Nh9/LCe+hOy0SJ5+tLx1bLHu91qF8lf5Kvk28PT6OP6rEjCEoH7ymovl5QL1vcaeKEGg+9aTeJHtcLs82rR8EY+iTzT3F4poSRyrti0kxSlxVdZZb9eV+Jr5qtkCDOwIphkrp/kW8fBnT3ubrPnvwwvdXWSWz7etqKHmiD0G1KOPD0JTy9Bx8VawvSPLIOfCRapmQd3L/y19vG0Mcz6MuqiDTpjQH2ulw39ApBJFUwgh1U1dDUUeqKYDhZ7WDUtsD7k7+2I9tZoq62c02lzK9J7WX0TbJAFZzifYnucHJtDBM/DxUGVey47KK7I5l+BFbCIcsu0nfHQ4V5XeiZ8542Qq2Xvo3n7olsTU4j/vekHD+hp5fv6EeXvk7kGi5ovjclh7jvmMgVYULNoxqmjp4qr5xmFYb9tWe8gn774fO571gZtFwSg8UB7NPXJrBYNLhra/sGFnfkxVhK/5S4fwVZ0uU9Yshn0Astxp4o90ncA1eP8Xn2W77N
*/