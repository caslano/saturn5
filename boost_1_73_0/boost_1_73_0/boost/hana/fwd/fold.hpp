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
B0kmMJSei9RrHkKt7mR4br7tjN6Yo+5ZZwiwf/ubkXF3Et01DE1iY9T/qzcwzNHZYDiGV6/gaVNOa92sFlB2UTdLZLIUMZQIcbPsP69i36jmo8jPYVU/Rj1/Sb+cSCXi+1gF2ykAHhNRCm7H2ZDAidlQxLa8Xch1KJDBQGg5j+eE5fxZJ6zne8hjeMVDMb8rnoo9Hryo53Ldag0IVQMu1UvDfT7Albkg3up+OIPzbJiRiMQyOV8hKLKfF/WkfaOaj0I/ebFf9WPU81fqNzcD8hyvfmoCyQaWlQbKQmkeKJcDwzALq7+LEpiTsbDZbeipZStM1hQmSsPQGikm0wjy8iUfgfFVKMqR5GVUMRLjQYiqIcvNuWrQMpw9AGom9Kx8TMyhNCvlRc81uYnlbaBaeG1Pzdk/16QnoXR6215FgKtqdf8oXNm7ki32LUu5unMpXdm7Fi52H0euOgiVPZVRhNI5Bxgtn5k07d2t3V1sQDi9xHFwmXepGqVoADs4X2zJ42x6COTx/dYMXMEC3kjrB64XXDW3/olO2asnZYlw4VuXVxbIoy/1LhuLgDvNjHHsbmTX9/LwYL8pD90z5l1jj4WdomrrXMYJSNd0TmeWJ2BKBZeH72h6AKe9PyevO6NRbzhuKGBw/ArSgJtr
*/