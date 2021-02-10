/*!
@file
Forward declares `boost::hana::size`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SIZE_HPP
#define BOOST_HANA_FWD_SIZE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/length.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `length`; provided for consistency with the
    //! standard library.
    //! @ingroup group-Foldable
    //!
    //! This method is an alias to `length` provided for convenience and
    //! consistency with the standard library. As an alias, `size` is not
    //! tag-dispatched on its own and `length` should be customized instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/size.cpp
    constexpr auto size = hana::length;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SIZE_HPP

/* size.hpp
vX+75UyMWKtWo7fCBajuw+1tQszhb8fnDOybdri8rMaM8jihvcnlRIsBPgd3ufMDooFWpxyTrm3+IvRVqzSD9zjMaFikyYPLWVEOZgURYKbPFtmXR+v3eJQwHA1G1wMO+oCrMrj8+X4+uy8EXr0if0mL4Qjmf2Iwkn08/ibk7A53dPj6be/4ht1tml18SnOks3HNDa7GW1vp4sb71ipVo4heZqqG3LblUnbLkiX04PUNG5asj+MLpF2Z3gazsrZWalXWc3vPoSOItqlox21SJmS36OnJ0U0T0/lsiuWlVGuDOWlLK7Um7VerwrW30hVDDdqJVivUAwR0TYtuX6Aydlfo987/893pDTtDkZb/upoj3YFrbnAI3tpqOSnrW68kRhHPDkVDbrtyKYdlD98e7930NC+yT/kQO9G55ibLstZWa1nWt15JjCLesqIhj2WZlMOyLBq6actW4QvKskxzk2VZa6u1rDGG1OPHYMuKhjyWZVIOy5LA4+SmDUtigxnWrlRvk1lpW6u1Ku1Zr8NHEG9T3o7HpFTIaVHC8W/epITk421KNDcblbS2aquSvttmZaPowq6sIa9hiZTLsmeHx29v3LKLLP+0VqyjjUuVNxqXNrhi49K+W8al/TprtPphVTpJx4nOk7pJn2tQ
*/