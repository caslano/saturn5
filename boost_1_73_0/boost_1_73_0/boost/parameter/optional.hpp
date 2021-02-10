// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_OPTIONAL_HPP
#define BOOST_PARAMETER_OPTIONAL_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    //
    //   - If a keyword k is specified without an optional<...> or
    //     required<...> wrapper, it is treated as though
    //     optional<k> were specified.
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct optional
    {
        typedef Tag key_type;
        typedef Predicate predicate;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_optional
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_optional< ::boost::parameter::optional<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* optional.hpp
G8oMHrQRuiJBivxh3kMVCW5Tw0I+yiVJp4rqShpHVjOReUo6i6aYEH1cEQC9B2pEz9Fb3Nc0qORxEQXmgWQAziA/G9RONw2acRkkKCmME3QhegPztA0ysFRycbWLq0PXWbuqhRnAYzYSJbSwgLdXEJfHZGaHKjliJWZgHyiIo1FRH56JSxwPxxIlD1Te1iYIMFgmw1q/l6zXetgYogaCzoqDbAzLoPsKc4pVuwphwJVEI/wz1VAmJx+C0BXLeoEBQIkL1ubhYoirFsAGFuIi6eAdKGVg6YOzEx1sIUdOQ/0IHTemqolEqqlcxC8awXchbOsU4iJeo0zELJgzA2UgvCQTyJJErEKRFMDSGdOG8BWCqBcaLNNqh9GBLthBxUQMx0RHhFQ2jLPpEEMKs71EVnFlESx+cPG3hTlOPHSZqm+DBTJgRKZ9CWPRCQWBooIcQTMwgcyzUJM963il1pZIRsLeSGaw9Lgd/jrAnYs/a+q5eAECC43U2kgIggXHq1eihB9UiZJLkJVcsfVh/UddIJvDL/j3X+g5kQFyP9iHsKa5xYXNrwOoUqUMuQzKVwgvaucR6vF3o5ZVMv6WNNl/PojtG8WztO9ADJU2ulypKcrrCazOFPn6ajLF1wlBmCuKHVUmMTZR5CzQpnxh
*/