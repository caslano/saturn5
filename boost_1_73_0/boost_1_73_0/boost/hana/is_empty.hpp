/*!
@file
Defines `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_EMPTY_HPP
#define BOOST_HANA_IS_EMPTY_HPP

#include <boost/hana/fwd/is_empty.hpp>

#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto is_empty_t::operator()(Xs const& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using IsEmpty = BOOST_HANA_DISPATCH_IF(is_empty_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::is_empty(xs) requires 'xs' to be an Iterable");
    #endif

        return IsEmpty::apply(xs);
    }
    //! @endcond

    template <typename It, bool condition>
    struct is_empty_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_EMPTY_HPP

/* is_empty.hpp
c9PeSM7vQOk+SPHG4lUBBZbGxqCUd5bB5+tqT9meOdnsLkx9HK6PF27Ar1fAcocvqTrVHfqyzxKQbiIZuaUcy2f28QJXkUz5DT/eHbHaKsB57tzgRxVOtasAH28C+Ng/eCTo0cXw7tA/2AQ4ZzT/ug4OX5klN9yQDzfG4bAChz8VC3tVnN3UaXY10kcbIH20MdJVk/6NkT7eAOnjjZE+/oZIu851lc0KJ72SKzOvZPSgEnn4B5Q6f4efrz9nfe0Rb/V1k8NLgA9hJFXmKr1CIUeeSltufkyVjio+9rFMEDYojv8uxX/MQD/odIXIIp55VfX2rH3evLoYqUC90+V8QZ5IADSaL7kqgyzcICw+eDOEJ8BxTkZuMs1Tcjel4op0uybe2pWKInfugjSCnRDDGsJgDvoVD8vpWb8JK7HGRpyx+wZn4SdBqL25rh9uvn9tvBdmcWfwou0LUdxcnhkgG0iz4gmlIrwfjs180QDbNGIjKYxxnfDoLgrURqknq1QOzVmkUTIFVpmqZIrL5l/9bq/bruQL/MDijT9GneBzg9j9zRvv8OXX0AjafkMabapMID7S8P8NEqt9tUgysr1BU23T+8rrBHRuMW2tEqhxqsRjI/t/GiZJsbo3qoHKfSh7JIEX4xTdWZnjiuW9
*/