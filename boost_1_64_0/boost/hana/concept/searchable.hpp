/*!
@file
Defines `boost::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_CONCEPT_SEARCHABLE_HPP

#include <boost/hana/fwd/concept/searchable.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Searchable
        : hana::integral_constant<bool,
            !is_default<any_of_impl<typename tag_of<S>::type>>::value &&
            !is_default<find_if_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
XTI8fRTwy8Ls60Bwk6oTDNNEqOYFThrv9lFCIhm2+SEeHQjAjXYuwHVZd8anvkrgBqcqctP4jZEKY9pdV+C15vJiDGXXDxflHlCh8cNEenOQkusZfuiz1L5cu6NrCp9linJXqNMTxIJKFiivSE7bH5FKr3NDiCLScF363xQ0eBJTlTbc9yfHlcVFakXETsz0cXo5x04ZjKa5BPGxdJ3/jlDi4vR1yanWfNqIWT6gWnON0Mqv6qrEqVAVGgXC+jNuo0f3HjLIF9MkFfnbpN0wyUtENN9XhGqhlC4u7L+nH3TWjNJpA74UCkflMPy26FwM1WFiFlhhfy7JWHcr3iStx2CKns4LbIWvrXfGmedsic7JepFP7jM1nuAKRrtq01j6n+goBOSDiuNvTOTnxGnwY7Pwo8vGpa+HJHzohsBq+OkWwcHpZh26ZNgjWE2O8vtKhhTA6kikK4QkMbnvbrlUfTC1Z7Zya0KwIYqUq+ZLjq8q8ltWylbgVksTHipFw9qrkE81LVV1STqpXmHu+XcG85du2Uuikhr7dMijNzrcTr9T+0D0qE7hOMb51A==
*/