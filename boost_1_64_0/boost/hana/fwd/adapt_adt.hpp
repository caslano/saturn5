/*!
@file
Documents the `BOOST_HANA_ADAPT_ADT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADAPT_ADT_HPP
#define BOOST_HANA_FWD_ADAPT_ADT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines a model of `Struct` with the given accessors.
    //! @ingroup group-Struct
    //!
    //! Using this macro at _global scope_ will define a model of the `Struct`
    //! concept for the given type. This can be used to easily adapt existing
    //! user-defined types in a ad-hoc manner. Unlike `BOOST_HANA_ADAPT_STRUCT`,
    //! this macro requires specifying the way to retrieve each member by
    //! providing a function that does the extraction.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adapt_adt.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_ADAPT_ADT(...) = ;
    #define BOOST_HANA_ADAPT_ADT(Name, ...) see documentation
#else
    // defined in <boost/hana/adapt_adt.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADAPT_ADT_HPP

/* adapt_adt.hpp
hAry+CwzqbVJtcCPKkmyh6cHOHUTf5pHubS5IsfcmtCYAdEbavgLlIUpzxzRIgHRxHGWv8Eq10l90+0xq0o1RlullhpjFX8W2+l6hXScPYuW7AAYB0gsstZsThAqtC2TtA5u4mRGatXLTHvl35OjUXOy4vmPvs65wFJavwvSHQoJ9U9PfbDPB9o8u3XBpfOGtsu/cpOt1taE84f5CbjSddyy8lO1IMuNa1+FoU0TQmn+piWLQIsC9a9DfM+kr5fk5fOEHDsKnsRoCItX7jDm7/su8z69b7F6sHqwhNyDVT1q9FgOT6tWWnLI7qJKKxvV9jZ7IbEEVgTMoRLW8Fftg0dNvXRYkrYV7xh/y6hzzTBtpBO8Johd4XJutdYt0BnVadnjyZdtHhDFmpcuWu2UP6cwb8nvv1v3u8TNEy6lKvrtd2xP9Z844i37KXEeLGU/nYrPg+WvFQZJpdXREesnrDszYb6LzvmON2quDQaPWND4Tc4mcuJF1uCZ8r+nn3tdrMCPnpY8r7xL68a4+SAeLTDS6Mdeh+gZcuOpmqT8k0GGcmtUQ3MXd4/m+Q==
*/