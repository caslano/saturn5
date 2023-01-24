
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
+ybiGcDHm7Xtiu4xzpDATKxsC7RVlduAN28cx9F4QJKy5F66kBuUmlHLkN7bDGh1TQ8aljd+Cv3AFSg0DLvz4KvaErPyuVDmOmT6laXKzfBadITVtwIGahnvxTmjkpx+8XcPuwIndXpT8CpTHnVHTV7XbIC2DJ4hnZVydMDn4wnLxEf3G2XVB6X7+kT+XKhaX7nWb5XE+FWjFZ6UA8HeH6ePoV7F8uafY81UNMf0RxX59SNdt2GGU1dHI1WfVo7RrMQU3syQwEdk3JfxhLJb19c6zA04inMt6Rr1ZU/qUwS25m0+N8wSvIrDcDceevdK43KkiNb/+i/4Ft4HrjLaPk/WYc5IAj9miSR3uDv8reRH0q2UbkLULcbOl+C9pSN6PRuNaS34Ktz1XvLUCqRRMGR8zQwnP1UqKJOuAP2Oh/mespj0G1999cMU/w2YBswijrAxA/XPkQ8H20hAhDKyYMkdWTCMSpgUi87FtvnQP1bx1Ay1BynyEejVPt6tjxUQsgOe66MJ46tF+rRc+xhJuCXqdsITqn22RZkeQDsPozHo0Cfoo0SblrXqtt47UuLmn/PaW0lqbEzTCVJQuYW2AsumQXLLFdwzBce41s+GFY7zi41N2mA2lxsKOOPAK8TMl9TrJiZHYce5nfmx9KKB+Rt71DOzWlX2fhxPhS7drrRy9+7nPIMErwZTx6I1fb+MG2lJQCNS+ieuEY7E
*/