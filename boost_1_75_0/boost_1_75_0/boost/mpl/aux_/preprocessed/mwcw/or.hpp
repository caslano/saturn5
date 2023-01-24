
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
U6GXuNUHJDsmV9I2XO7hbCi20i8qjL1r2OG3Stee81zi/KWwRGsVzJQ1t5AU8CFQzrLUPimP0lCwj488njn4iBsjJF2g846Eeo1STjDy069PZfKSQmOXn0qR1A7khR6UrUqwUaeCK4aOgoTxMxsT7MlFZoLqUzJyAseLWcLUZIRyEM6kLQmfosHHaHYfXui+OCokNyOvqHByeRKJtNP764ZiGlMdx056GI1PCTPADF5pMkM+9sn9PlXQly1azFj60GFZwExWkb5lQTS+RlGWLmJR6oGN90HLgHbWpgcbMnD/zUmYMIeHwZgs7O912BJJ3DTRfUWl+VcVbAbWZVrMpSRJDllm9NWj1fPyjmNs1OU+HinM5+XGqsZrsw9zJmc/TbbVVs18j4GYEad/Mk4WebjjlnQt4htIF5J2rTAE8woiF171vqEcBX8S7saZF9G3Gz3Fg1KKSBeOuNwLwJDva9jns5uoRRRNS13NR5/IfTIqG/VeQKDBpBsgFAFFfjWXNAUdUCgh3c5me78MXpIi3Ei9mKv5wQzVawcumqKvhPJPd7PpceEEZ342pUm2woKg9eqD0l5B7Dgwv53yqNLDqd/pZzL2go8OL1pZwD5+BrGQMfYW0EYuXVJmM4dGumoinjCnwqh023a7mMldt9yQlbtuDscu/6y+Vb4jC0cWSfywBICJye0+4HQ0ptSlLF59lZo4MbF15FOFDQch
*/