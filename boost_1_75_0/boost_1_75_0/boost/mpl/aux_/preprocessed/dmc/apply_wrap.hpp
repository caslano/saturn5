
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
sTib2TZtnVqBMi7VOX0TrzbS/2r1DFR7F6lZU7udjeHyw7dYSDOrknOK0gG2LPXrk67HDeJQr5/Xb0YnxafGyIWTcxHxM3f8/bd8l7m1lRCjev1QMsdq33ZfTsI9f6Rio9Dp1M/Gwr2b6cEG1PF98j1Kuvbh84P2orxt8LBABsr8AiLyHIn6g3GSrpKN9XqTLJcVhkpL7T5QnDG3DqRspVsvsbOCcyhZ/9Xi6t8Kr37dirN0COiwbTyOVf5bVy6i+votWR4kcxfE9go5PNGh9jVv8nBfLRRINuzDdTjphSy4pqs8V7sACWd8wEAEm4qxvgdv4j0f5j5FMU5GmhC33jSY2YcM6QLQNWzDpDaNl59BhRPWjE/hB00MLi7ewk3qcxh2Gr1PAc9zq68gGH/F9cOLg1uT/9mUY/+PuC76zwf9/8rs5kvUzrl/RXZMdDpjah5edGNixYYwLTVlMZXYGq4mnY+exeWhssp7Qg3jtOMvCdbb8t+uW7gs2qvPfHJaZFUXbvI5Xvl0PFPl1N46oEFNnCyCrBxW0UYdvPwoUtdtBoJUIq+DIecbXpP3E/eMB9chioGHv5fDwUDH6XgHmRWZAG/Bj3L8fCPpMokjeORXD458GWoUbKBkYPHMZBjtQKVMrLXURvAYQejXbmYL3ppnImSGv6B1xSP0PhBlFGCWCx9NbWZYGdgRPifswTGUsa8NDByHiV5Z3Ktp
*/