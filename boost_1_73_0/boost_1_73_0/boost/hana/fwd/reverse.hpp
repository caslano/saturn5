/*!
@file
Forward declares `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REVERSE_HPP
#define BOOST_HANA_FWD_REVERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Reverse a sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `reverse(xs)` is a new sequence containing the same
    //! elements as `xs`, except in reverse order.
    //!
    //!
    //! @param xs
    //! The sequence to reverse.
    //!
    //!
    //! Example
    //! -------
    //! @include example/reverse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct reverse_impl : reverse_impl<S, when<true>> { };

    struct reverse_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr reverse_t reverse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REVERSE_HPP

/* reverse.hpp
JGle4MHvKed8eN1CMcjgJchgbIwHPL7zXFArpXjxkZU4ePxIBoFWyskTCkj5xb6l7JaxvWG3jePeQZaB2NhOFMpL3CIFzraZaZB4PksJcdFEfgIsImblHowFC7pYSTeMeYsb0yDhaYoVjbB4AhMSoq6DkWqgXT/XdRda61OcoqYjmwjQJw2YvbFyAVZqW87zom+4ITDWp7ikSzy0Mv8MQC931Lr3Aje8j/nNrgdxvsYdUjljKzBVT+LUliJ5ExtaK16nlTSLA8yjfFkgsXj1REs6Mq8atc6nfz2fLUdDVl9ujf62HM1lxr5DShz4244IPy6HmUWiWWywnMbOpklkKekDny2YGZawBOsURxOGI5us4EV/pMER7Qua03CMoXd/0h7OMFLY1UBHzOJLjQJBzTh9Ivu9OD9ZLNsmTerjJ3lF9DvQ6gLvR4ij5Uxv3CzyvY6opoFNJEcF8LkQf14goOB2MZI4GHzxk1nb/XsK7rcB/4wFcDAq5fxA8Jf3RORlDkMsll2E5X764sB8IF+2WsTSpmNjFI5P7cCSlT1gv/JrS3k9Gcq34lvh5fiEvYEP/phurqmL99j5UXoWTDESCfRWlAYsefHH9t79Y5fOYtV6rgfR98sdoiM2fkZUuBpavONZLA7TqAYb5Xop
*/