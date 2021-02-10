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
rKQC1f8JFN1C8aGQRYFBXniUxGnyT4ykUG9tnSMDTDXAdyhX0ykolfkqTe93kBSPj1jTMJE8mUX8VaKLIjlyA/+SV4Y9gW9TyZYqGHS6G95KckTGr+0gTVZEm0lQgiK+jhMK9IRHAmgx0iPY/Z51yLvB0Hv04eP5+Aw53dX8DAuP6R0JgZWgA8PhaSrjbLVESqwWIcXBDxyWuD2teaoaCxB7B7Y24Ikx1nyb5KuSx19Z9baPGj/K9aY+upDAysct3cJqTZFCZ+z7jid3rAblvIwoONdx2Sbj8p5tfSMIHMHDoDlSd3E5Rqr+a3CFUS1oEKQNOgwGB/gZFQwt/F4p4eBRQfcW27yl5VWF22S1D0X7ShvvO6s3ugiq9gtx2EWfS/9+pVxc2350fjwad/V4zOMknXfYDdr9mBVgCV1nJPx18pQ/jVH6Zqd2lUtb98G+o7SWdwm4Sp213WCXBGlCc6xB84fjf5AGeb6uwungzTGIwHOiZFLI+CutfSAoMYz6cx2z2EyIePVKHP2tC8xkLmpm1dgVoAEGl0zJijZ6oN83dUo1p5q84hjA99ByDfKeobYkXKdno+PX54Po8uriH5/qgakdtYRj0IQ0FIht/u3eBAH4Cfu2+KNH6wqulQm08K0ZiMJKe68mSVXu
*/