/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

    // Here is where the magic happens
    template<typename T>
    using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
        function_object<unwrap_reference<T>>,
        function<T>,
        pmf<T>,
        pmd<T>,
        default_callable_traits<T>
    )::traits;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

/* traits.hpp
N4RDq3/DoxIfUiLnlpurmafFTCI+PPKst2MJvoPAhasr2UfnKjczkQfqsBHxL8Pxq/4w7vsSZEP8RFTRzH9p8KyxWOXTf4kqfzilw/HgNWc0qrv+YwUvR1vRTZN8rHDFPu8Rw8Qn/Wk/HoxHo9PBNDjWaEydW/V33BwOdmqPU+ZJFljEiVEfu6EUoW1ntY7dJqubnZpO2FRhIxD3xYYwCd6dbD9l2qiPoSniyt40nYieBqyKzmrePqBvXgScTnVT3OL4gAdJ/Q/HQPUEU41OTwCJQ7CpYr2KKrDKwNzK+2A3pRPRFc/pT2yNgJBs68XPJivMsPj9xxNzc/LGuMa/6JSG14Gfj8tHHa9PBnXXDNYjyrzWV/m7NbRx1wRuNChXt5JtW2sWUr3rN6r+cMDN4f9QSwMECgAAAAgALWdKUvYpv6UDBwAAYREAACgACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3RocmVhZGVkLXNzbC5jVVQFAAG2SCRgrVdrc9s2Fv2uX3HXnaaky0qOmw/b2smsq7iOp4rlseR2PImHQ5GghJYCVAC0ot3kv++5AKmH49jtTOmxSAK4r3Of7O3/c1eH9unJK/X/KS7cPcWl0b+L3D18Ok0/UvgD1XvcnxLSow3JxzSm
*/