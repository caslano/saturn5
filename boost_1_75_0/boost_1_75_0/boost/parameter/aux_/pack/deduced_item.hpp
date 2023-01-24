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
a5RnIzkb1twX/iN77YMHxnNBhBlRMlGy8Wgzw4GcONeuGk4CmzK7MrHCFXvqYwgfjC3T5tCM/aByCdSoeGWiAzO6GMk6KGFcTlVMqqGSHM69lYyiky8B30l1fnZa5awHf/wCl22U2kTpkKzBF4g/+GAToc+egRGu15xo+PrZrYI9csqFlD7XMl0fo8sSLGp2GMm9+rNH/nCEmzPFv2qGQVecbli8k0TQY7Qwkye/VpNpppw/Qf10gRfSnUrfKauq3LPe6yP8OOp7RVEJncvmNuw/pC90QqkbVXeXAL58IqoSCWNW2EIWVTnl2CEsuyTsUz1VLVat7P6sW3yJOyi1RXtOespxLF58SZ70yrv/ukP9aRbDm9bdtFIk1i6yK9OciZptchHkKH5zkPm5vUdq0qOe+iy+UD6r2wqDSqg0Q/r0d9gVMe56rDWDo0/3hLiIK3ptsX1QlrS6FnX49OVvZKcPJcfQPqlSIUFhCgX9ioQFTO24pCtRyHqvqii+xGFOWAcPkZ5kZp3dc54MgyMj3Z/EfLJ49fSM5W8d9I7Wjc+jZ3n8Rpd+zCjxt9/Z1ybpscl6tmrEw8cfz9f+fmiJCNUhmz5DMLOKiGMnhDhwTrTAKy22TCgI6rdE0aL8iGn6IZOYByjTY0nTSh3qZJgg8Aj04hjbnGzYHg0CiJJcTKsYtX0iFwezT0mlvgF369e+Ed5iyYgx1OBcsYyq
*/