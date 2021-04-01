
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
vNLtIWZPL3F+t6Y4uUrj0fkbxk2EqCT2eHsCvCE362QKLoT4TUZADOu0K4LVErgpmL6Y02UEwJXwqhx9Vdj5A1UXaBLliHIptCFGm6jilFY+AC8m//9FXniJa5glX4sYEWHWv0nxtSgk3916zpB1bzb2xLmQp6yDKXtypiBTOPdFlnYIO92wjkocrUJmqXBNo2bmVGU8PaG4jDFIrBilay8Lg4SoLyjFhBDYRYnDTfNCTESE3YIrxpZMrIyuzh/0Oqhbt6vz3eu/1gG0ASPNhvpq7+FOrKxivqM0m+ieJFUHgfOKqMqtV/SzN1kwIBRHumQ1FrKOIb0kyVrSeVawyigBNuntlAk5HrzA3jMtDRc/8BX1FliqTK89LzCuE6UekgtXgDEoKB1GflULkHo17Nyb1atzuqy7R7iSbFZznBZqpvZGQBhQollZ6JvOV8FSiV9R/9Dyvv7/lRyojc+t7Ypaqe1XtUYRuEfM8E2R7fAsq0vVZdsEFN/KRZyuOnLmSX8lN5tXoO6pNkS5FPUij/VpGecpwrnYpqYdsNQ6+Jh0ScD39haS7mEy2Q==
*/