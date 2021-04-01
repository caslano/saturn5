
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "or.hpp" header
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
oUDWDj4sFcLOI8vKRywhiRh/pRBjKULw4QQt70rzG6JuioLa/U+d/5BLH9Y4+wrxApuXpQrf7S0r4dUeHesXpWmJHU2dTosqlWm9cgvoqu/i7ziMt7QBb+fwl1uxB5RRaJzlN8wdVbTbj0C4rD9VD1JzsdIn5ncDEh3+aXPZ1guhQuliuMb7SQleYrGM/MJ7M01IKcQkR545cg+F9GlIin483Vs8+CpAcI9j5EacGkc/p2AwhWpAwTUzfkLdLQGeqW07LA5ZY0pHQ2g2oPvYeLDqzlQekYq52ImoMvEgX/3WFnkGHF7UTAVMmIXGfcvrPVoduCz+6P88sJEoHvM8Z0mx7WV8lBYyVcrUtc2KqKEJNidWIoEv5PcjCmOeJb5Qa6q3aggso4YZ7yDOvyi6UsuG4oif4X9JGKryjKhjPNJbHbyClvfrCzPiyqaHg9BVhC+Av+1SB5Rnbosc7sBd5LlsIP2VuMqdoZ1cRo3MwgAgZcfx4Rfmf5NQt9vzlVqJsNUBmOn7x47VuyCgf6wQZS+9LDcaxcGq2FA5kaubuVtPsIRE9ric1U+bJg==
*/