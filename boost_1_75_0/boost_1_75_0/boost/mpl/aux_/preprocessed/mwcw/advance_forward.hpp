
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
q8Pprgo6CTb1TixPsLuTlz57cGFz2Et1GvqwZffKXN/x2t2yvnL7h/dE37x89upS0mmCUB8FK9WafOdR86IWqMlFU24qGmB6U+AmVwpn4KcnTUjdAaz/LFGQ7qAZOCTHW43cAEBiAr4KsMumTrgViaRyiwTdym+WX8VMjJX+/KBMzFSSdNl/kvqnnkYTgQE8JNLfo41FhI9lS0uqyfTLahoB018zgwkQaw2ByRkpdsUfqvUH/BRTrO84+RxTxY4le+l6zXs1e6VEUKkXFZvosM6bHtZYAz9MoHEmRuBkxS/+/sZm/DNwCNEBe6YsT70T161aIrN20fpBN6RFRq9w8w/a6C+EiLytARd/OiJA443Xj0zr5rPuIHhGRkJY1tUp1pVuoEkn1uPTRBnz3zFEJHmcDRDJDT7VXDVBkC77doUr0yWhV7OJZLeg26Sx9ifiO4tqnU4Vs8y6CUyCYOY1NsSqhY/2yCd7brhOlDsL+F7SCDFoXgyBTWeonPa1K+j69XtsUclTmulTAceJ5yMuj2byPTl09cJKigLohgKJ3oeonpiL/hd2fNV6b5FsN/6S2V/Bis9Ch8eyW+UCcreYh4hjnWnKiV3xL4RjgHQUxa0hu6WDTXntxCc2CKc32KWVHmwdZ3UbcGSieCtcOwbJis7omvf+SwPyTxRlmrd/U3s6rRWsJDjSYtS5ajDDOZbYWElGx5LZWr/unhAF
*/