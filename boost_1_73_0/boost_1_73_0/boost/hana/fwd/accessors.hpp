/*!
@file
Forward declares `boost::hana::accessors`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ACCESSORS_HPP
#define BOOST_HANA_FWD_ACCESSORS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Sequence` of pairs representing the accessors of the
    //! data structure.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` `S`, `accessors<S>()` is a `Sequence` of `Product`s
    //! where the first element of each pair is the "name" of a member of
    //! the `Struct`, and the second element of each pair is a function that
    //! can be used to access that member when given an object of the proper
    //! data type. As described in the global documentation for `Struct`, the
    //! accessor functions in this sequence must be move-independent.
    //!
    //!
    //! Example
    //! -------
    //! @include example/accessors.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto accessors = []() {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct accessors_impl : accessors_impl<S, when<true>> { };

    template <typename S>
    struct accessors_t;

    template <typename S>
    constexpr accessors_t<S> accessors{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ACCESSORS_HPP

/* accessors.hpp
iPwWqI7FIRBwRZcSppUPoUpbAG5ylOE6AJa2AKCIrsomCJdbIC2+DDuVRUVC2jNgpsjC8BjFcxkps3SaL8DLlwrJyfEyrm4sBv79AHD2pCw4/t4afArebFYh1U4fTNnWaArQcfki8klxCrdGJK9nZQ6ul0OOKdq+U8kSFpwIXQWnV7bwRxAd/TWI6uiv2yODZUKWDhb6vTX4MoFFZxZ9lfcWhS3rdpsab6eufjytMYXlSppJbnXIOt3BVky79tioQ8hUIA2ibCOtPayBxCX9ehXWGvVqWOpVNdrCrakK6xVZS9QqYmG9otYOtapcbCsrvyeZOTVNGQ2HY3paRdE3D5QjoTRAoJymUqPcma+NZ+4cbDy0M6uJ05kt6x6C/DceO1LZBGWhd4WThRVkk+waks15IR8smmWqLFYzjxBLB8uNUu23PrYMCjyuMzhQpcHnQJ0au0MN1bm+vo5mfqBWfQxCiHwJDNXQg/XdBJg+jgboDWubLgF7h6IjOCQUjerAgMC0UiNl4mVPVUANkOnIEMIa+0U9JtsWh7HWnKi3grZa1zGoNKK9V0k2z/dxvv0FHUtbowPtddGKBXyvj0/eD4an0RAk0xDU7CTaubsc+duFriYVOISZ/LVu0+IT6uRLrWgBkELSbzlqiEER
*/