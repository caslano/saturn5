
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
c1H5vC6w15vwnPt6d5JyBUu9u0q9u0m9Q6TeoVLv7lLvHpJ+KdEs6W+UeiufP7sl/dEyVhYj9R6Dg3EsTsNxmIrj8UacgNtxIj6Mk/E5nILv41T8GqdhC/KKxZ44Ha/FOJyNMzAL43E9zsTDHt53lf7F/5h7r3p731X6NP+j7r3q7X1Xz66jT/ZmP8N4opm4h3jsZr2fVA960MP/Rris5/9ZaemJluy8gUnm3PRGWv9/QTn/l3ljI+RcO1XOm5KID3TmN8CT6rmKOcu4MsmWfVJqtjHFlG/25vz/F6SVaim0n+NNiOA3EE/Y589LOWqkHIuwJS7AI7y2xmU5LLnZUoamXpbBNo/RstJs1M6ftxDNMk+NUzzmKvJ4kMFtuW3tVy7n/LFS7sl4lPwOHnZTbmUe608oO4WVsss8PHmuICU73yjXUKilDGWUK5bHtWo55PxZWw9NX8bcYOv1GqhX3T7RXL/5Fjk21hOfpDzxT7uoGwv0MwuMXh8XtvPYUF5EevY65VsfK5ceuOixc1bKGSPlHEnc3Zk0XR07mVwJohGPX9sc3KMy93wv7d4Rd+GkCP7xe7UM9uzjk5T+PGv+oA3ur6nJHPl5f7DNka8rm+w3HtddOyLPmFrXhkQeJ9GI6nOB9m2Mabb5ukG27XhO3VDqHiz7hL4F9bWhsl2ObNNB1vbHdFTbx9qs8trDdc+rj3fL3F7bXPVSeZyakW/K0lyPwNSB84mB1v19UJO2ZZlZfa7Edo2FgdaStpVrIsxkDyxLSU1iP6vH/3mOh8Psj4lsW3m07vjfI69nWyUB+/E+SPZhpW0+v7yXl6CyD+P/6LgPU7KXePz+9WgfURi4DPvIp80x2qGCegVSl1zqAS7XzpyV63TQ1vZ2qVWve+L93Fpv+5kKWijPPzx/1bzqq+54cE1pu6ryh+58/n+3n6mx+pO87TfqEqvOGR7R/LFp50p3lYQu+sdnjx7Oct/vdXOQeo2N9Wl3PNTx6ydOtV/8UdmGZ/o1bv/TZIP81sBUYpkybw1HOvXjDMIOOBgH4xCMxaGYhMPwNFYZ5DeD/JYoI3ZS3tuS3tWS3jWSnm2u7XU4GUfhLByD83CspD8OM3A8bsQJeL+mX2MSluFkfAOn4HGcih/hNDyFcViLM/B7jMdA6c8Iwll4Nc7GOEzAOTgXF+ACtM7Nld8YGCv11M7NXST1TMJ2mIzhmIIDMBXHYxpOx3RMxCW4GDNwBWbiGszCTZiNxWjCBzEHn0EzVuJy/BxzZQ5uHnZEC0ZiPo7DApyMK+z9hPK7Qn5vlDn1E94o9SmS/bYaB+Ma2W83YSyuw/W4wZ6u/A7AGG26Lvo3w7Av9sN+GIUROBz740hNv+bhJvLdLt/5SrpDlLmOqIRSmWu7HyPxYSnv7/AaPIhT8FEswMelnQ9JOz+Bd+CTuAefkvY+jI/jEXwNn8a38Pd4HI9iLf4Bz+EfsSVlegbb4jGMxmdxKP4Jp+NzOAtfwnQswyx8GdfjK7gZX8USLMd9+Bq+hK9jOVZgJb6J1fgW/hMr8Qy+jQba610MwuPYGd/DYHwfh+AJHIYf4FT8K8ZiFc7Ej3AefoxpeBLN+AkW4ae4Gf+O9+Ap3IWf2fs55Xsds5T6OvVzfinHxVfYA2vxevwWF+JZLMBzWITf4Xr8Ho/iD/gO/ogfyDVjzihge5mzOwB9cBheiYvwKlyMTXEJNsPCKy7ez5m4gWtCYNl0+uqI54mu+jyz45R+TyKWE6uJFTz2n1HXD1o0o35faAnPPU+09YkGxtM/iGXbfOr1jZbHN9w/mjaT7XEDGpT+UAxAf35oVJOec5+podjHEDzL1neKs9z3n46YTV6YjCU=
*/