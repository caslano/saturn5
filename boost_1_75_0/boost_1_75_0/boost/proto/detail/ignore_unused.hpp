///////////////////////////////////////////////////////////////////////////////
/// \file ignore_unused.hpp
/// Definintion of ignore_unused, a dummy function for suppressing compiler
/// warnings
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_IGNORE_UNUSED_HPP_EAN_03_03_2008
#define BOOST_PROTO_DETAIL_IGNORE_UNUSED_HPP_EAN_03_03_2008

#include <boost/config.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE void ignore_unused(T const &)
        {}
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* ignore_unused.hpp
AZznxanQW7bj/wSH3RM7XhQ9mwffz5EPmxSzJZtLdAClVWs/IISs7ZdmPpMaouV+Ncc1/RKgdy4h2+2KO7NZyU2ZG5eQsfgJYCWR4ysPLmg5Bh091PYI5+9/TBdH5OTGoN8CrdtCdBqqjdDjZlkmWk1PFTtMsSiyBM8FztNtsqskf6jMRBzOORc/Od8QT9plZ2XEPDtBsBTaTJOeqM3SzdIVibAEIx44LoSl4sRPSo4ZAKKct1/IC/acUX08IrNDL8rrHIXEp8SsFJgMM7QE1wZhWk7GwJACh3ZuUT52ia/Kw7tqn0vRkol/onumTM5Y3bJ6kv9ckVozYHR4kj3B+CPv/CU8zI7QmVffyPXQWFDykU50DaVCVMi74HM+qRbRMMquAbA5M3Lgk9PYQZ2rJz7h2F93vY7DzFe0822EC3LmhFXD2WbZj1JvmWHcuvlbhdHXgrUFro3Cshk4lryluPOv6v3dW3EIHpbqYBWGrB04jRqfOcdt9C+ce8s8hfi5c3j6xfSJQOscDXvRb0dKPKQc9wgb9t62MN68bSG3kGX7QZLFKLDTN8ctz/AH/jJaci+sipcBsfgiezVD13z2ftA1gtvlR2W6Y5UQ+2L/gzmt9ohczEJu6EKtsTftWsxjCn/+Lsuz0FbalufteAeyyawTNkYvdxx7x47EB0N3tJ668Le4Keg96O+4RgRLISZfu+SugaduX6CNlmmd
*/