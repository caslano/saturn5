/*!
@file
Defines `boost::hana::detail::operators::adl`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ADL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ADL_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace operators {
    //! @ingroup group-details
    //! Enables [ADL](http://en.cppreference.com/w/cpp/language/adl) in the
    //! `hana::detail::operators` namespace.
    //!
    //! This is used by containers in Hana as a quick way to automatically
    //! define the operators associated to some concepts, in conjunction
    //! with the `detail::xxx_operators` family of metafunctions.
    //!
    //! Note that `adl` can be passed template arguments to make it unique
    //! amongst a set of derived classes. This allows a set of derived classes
    //! not to possess a common base class, which would disable the EBO when
    //! many of these derived classes are stored in a Hana container. If EBO
    //! is not a concern, `adl<>` can simply be used.
    template <typename ...>
    struct adl { };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ADL_HPP

/* adl.hpp
4nLaDSGRv4omSsBEf+J2HwdQVvu62poBXRnaTHVGVKegjfHRlfDmEqDIKEbWFMWZaXOiTrr939TG990jy+uYuZ4PahfovImLhJCe/wfEP551rsE0rt6wCOR5AgK/9rXxqfUjpZGYeFo4aO0L/49CyFlaz5AWLFi0d1oDuM8tRDM5AQ2jNC9JOKnLg8/HvypsmAKSkOwXPk2CsZzbtWTESe7V9qX18Kw7gXeQ+QTCd5KbuV1jrQGyP0/4JAkG0aNddUvGnPROaZgMSsV4BwxnDZNpNhAGMVgw/1cyuDY87lIpebOj9jYd3x02AQkcxN4Jkk/Mzurv/3hin/VP0/uRDNKMG9jxBenzm2P2PLBrgkQZe0+MIe5cj2cy3E3oydT7GTXDlAC6j/eES+G07kFt/6MR6CgNvdlfoG/Q51PHtvsLS/yr9YUSj+sQ0dXQOqZ1a9HQtLmwRPrdLNX6kom0hD+3Blz4J3WvU/Fyh0YtBZXz4FxlfdQd0qlLpcWUib0TPV3WjtL+PpvdUslJxetVa1fQoxfhoYQS4PfUQun8UjzQEMXdRO73vKW4UJq0TEcPw0D4GNtg5aisfr/JVowSYLudVmwdaVpbFtc1NN5eJ6K31+QtNVhObfUXgD5+YOep/kvMuytaS3JaSFGaaBGXmag36lGxXjkLTfqWSIu30sXgqaQmHRg/O2aD+hrJvy5u/6sMr/DAAOnr8CYA
*/