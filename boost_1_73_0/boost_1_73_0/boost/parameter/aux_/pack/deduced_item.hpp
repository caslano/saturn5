// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_DEDUCED_ITEM_HPP
#define BOOST_PARAMETER_AUX_PACK_DEDUCED_ITEM_HPP

#include <boost/parameter/aux_/void.hpp>

namespace boost { namespace parameter { namespace aux {

    // A typelist that stored deduced parameter specs.
    template <
        typename ParameterSpec
      , typename Tail = ::boost::parameter::void_
    >
    struct deduced_item
    {
        typedef ParameterSpec spec;
        typedef Tail tail;
    };

    // Evaluate Tail and construct deduced_item list.
    template <typename Spec, typename Tail>
    struct make_deduced_item
    {
        typedef ::boost::parameter::aux
        ::deduced_item<Spec,typename Tail::type> type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* deduced_item.hpp
2b+dcaV1XiNtZHm/vgYL0Z5bLXcIMRxCP0Pwd8oNku58fLhxZKnx8d8+UMeNELgfZX7mYVzcaa7oK8X9Xtb/O3b12hliL/COO0lAz2BMc0cCBlTe98AUr2imF2uNQTZUOmxQZ1L5L7R9OB9X4Ry36/N3neJ8ZgHLeu5g9eUUBBel3f8YFpOQ84WG/IQBv+fQ/gVQSwMECgAAAAgALWdKUk6bKY92CwAAdS4AAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9tZW1hbmFseXplLnBsVVQFAAG2SCRg7Vp5U9tKEv+fT9EIv7cS2PjgeMQEKhRHllqOlCFJpXCeS5ZGWIsseSUZ7Jewn327Z0a3fIRkK5uqdSpYnqOv6f5NT4/WVuvjwK/3bbfO3EcYMd9ZWVv/cZ+VNVj46fH/PfzgN01453v/ZEZYPrjX+wriH07q4vcCFnVIZnztabBwxldQ+Yye5PGannu9BWy6JBj9qdPEbo8esWVlDecde6Opb98PQlCPNWi+erUHNWg1Wo0qnOiuzRy4CZnbZ/59FV6bvOXNQJ9MNgN2WAUWgu5sckK3AzuAwLPCJ91ngM+ObTA3YCboAZgsMHy7jz9sF8IBA8t2GBxfv/t0fvW2Ck8D2xggjak3hmDgjR0TBvojA58Z
*/