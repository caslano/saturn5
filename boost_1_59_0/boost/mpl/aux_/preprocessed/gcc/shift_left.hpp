
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
qNcTpG+/0tnNmccwQCTnHb4TpthKZotyEd5qYRTRcIChDxHn0qtCa9AIHhUwhOsQwBivLTCJ8whKH8C4nYFxWyIwphDTCe/bauNyobPQi1co9crQ+MsNOLfINVVOyhb6QKJG+WTJx3H8wOODcstjN2Lx5dDwYi80ykv2/334CYBb54eFV3OLU+uCyvzXvKwByiAHIsfoSoLwi47gaSEclLtX+SwnoZmrp0ceXaCzd+64sD+cCJ4yJHmYzEL1khuJAXIpgU2SWge5Q4hjSWZBOmumZeKz+nmGeMbeY7TOPGuVzeEbU5c2LVr2Ei1wt1JrlNDf0VEvzwmb3FogbqWK48qjdSjLHXayiqPEHjouPbOX+FqKFMWCJEar/xkqugnbNnIJSy8PQZG4kNV1/PowObCwokniNuXplbCUG7YYuiizgQixRWR3sk15Lnwjqbzfwc0x5IbeTJhjkOXTNCaK3mAWwoQa42N7lMvemo6K7z3wgwj9Axx35ZpfOtXj78vDqukgNJyTED+2rHwJG9lKbr6ex6b7a41BbVxaT5PDCOoj9Y6dOvVrWRZQm3zTKyQFnxZ9HRs1Xm4aIu8G+NewEK+AWiL5atL/evVGvHaLWKgM+eVsPBGcg5Kg0089ClMl4/wajXxQiPFDkODTSz9TSSYoiVFPUgSZTyfs1Jz8BhSaLEe5VVe8BieLkk4RtKAe8jFsiI/tvmDaTRy+zaP258d7dEfoLP12DPhNhe7DUpUzRyMcgGyIcAY1HC8Rq0mN5njGpp5WxGbZLF1qzOSAnRvPX2oOPwxr1I67NrvL7PcFlUeDN+AFLpCsQYCQgvx6pzM8g5XVnz1yxYEVO/Z/H0UCCGByY7DCZ47SLw7tWqCB1HlSaAsrf6k1ch3WEdp50SxAL2/XKPNu5X89Rvza2ajKqe5ktdehTibsEL8xOEhSAsvt+f5Fyq21Qc+z4MkG5O0wpjAMIAAO5SXOAldHeAryQcQPaAgzTwoQmgkZCujceU8YPvF6ypZqxiTeQ7sPZMjtc+20rLwGSZwiR36V025Z/T4nTRzsD6q2io11uNq4voo3N6Z8c7yqr9KtfPDEGTI8sh2zAKKP/gftBJEAbKrMlxP9Ij1si34hhi3RL8aFJ0a/GB8ex3xmwOw+q/QcikWwxSILjJ3uMSuke8yMhIL072g/lH2Gx4dyZ07A5wfAyIH6n0aeOkAB9CTL1dWQyc7OGGRIPWXCSbgMRt0K41Ia+WQuDqULe9dyDdeg1abnfunxK0/eQOZf3rrYjAAkZzOE07EiU8+7yDcqxoFP+gpJbhCaPPyzf5c8fPAi/GRNlHs17WQZQ9rBYvUa+u45liLFPpDKxRzjPP2LNy9SXzrySrQNabWdpPigv0agq6C/B1QG1Yj2GP977YkOOBLb53BZAKoPBtjnXUVmvi4Qg7BebfFGl5phXyGhzorjXe7j1EDEIHCqzikjFAIr9FG86MGlGL4r+gaXMnSE9iVgYEFNbgwQ4DAgwKnXa1bMQvvHiv80KxGfRDC6+LcS8Sh7RC2ss6K4TSp+0eV4IZGjFg6Q/cqRhwCP6xCKcUUXHoeC6JjsCMrJQ5qtqL7lGYaz1M7cN+9TqhJFcH2EahFGzRwMlLHPgZjF0S6ywcd+yW3uKsIbe5RN/xMdbKfGeZQWEPnr/azUprX9/rvul4qvZB7zAqnUhqoI4hj2kKvj04dG8Futenvn9WMaR66tkt3PArHIPlUqb4Dm/2Qzsgh2mSX3s3gFZtn63BbEA6vb4O8TP3mZ+Cobn1i9FV6aKzZB9DaM3oo7Ta2j2f2bgOxu8zZ7Xmyu+B0g4F2wsHffL3k+OfEHHDtZriNe05b3dN5O1yTJi1DLrnU8BE8wykc7rgZCaHntd/3N7t91ul80cpReW+ytnRjPaEdFNs/vWMWLZ3uhtcy9Bu/h/LK7xavIb1+t+ilNY9AuJIR8vDlc9aBFzwVI9WugtbENpWKeTCwxDaXUijpuTssrJm6EA4bqyi7DlrTnDF0FpH1JnFZD75TnDM2eYTaYchp/1sf5nIAqd3BB74w1nL1hZ6vsnNVqYgUCCzpqjV5yb0XybvPQqdhxfBtllPmD6SOYgHz+r9XTw8OG88gfHMaLQmIahOfiNSs3TVYWkGUkrZRf/Fd2YrJ4yPy/Zo/mZFBM0ydjczKM3BXec38EgrFXx7xo6gtPbjoDw4u8HORd6FgWh2//MD62vCeAv6rPdUbHrGge4d9IT+5bYR1KTejUhbltkmwnr1F2qdVKfFqH1CRSlFN6OYtsM+eQKz8nUcAoWqh14TKWhtxhIBbRm1EvtBnl284ZuZvt6BtrOKNzItmYy9OTzmmy7Eh8v2QiXUabPoHA9ivX7ZqOhp6yU0w/hwaXPW/QcuO6CK38AG2D25IBhTvWJeojG7b07tNKCnPouom1Orhl6JTgy1iTjZuc1gdHJnatWqMKKHFX8NkJklfX+N4RvUt6gs9LfPOLd2XCx6dUp/MCnR/2K/+yezo3Td2KIdHHTxsi3yVuIRXmU74Vutrwkgi1eeVWLC5kRi/EyuIiNEhvU90oClSPptykq5b7u082K7cPIC2T/YRbLZNXE1F2gDv1Q0uHeZpPyVXFKOqhwDzeMw5f0sLjc/tOzJmMc9qOPYnPHIhz07nKl7oZvIy7qVEDW0hdEQ6VXyIQDXIVm0x5VQk3Fk8F3f7TGwzqcMjy9i+1jsitNrLNuV/5dReN0OWQIZaIpnJ040+LhJfoY7JIc1mR6ddXrdi7bjDwuFqj7M70KuzNG8iIGnx6MtVscqsB61Us+2/ASr7Bwdyrr9WgG84T75pQ45XGzdIkG4lpQP+xBjgjJRukrPsjFXkFez6H7Lbu0Rd6OumP6xKCgvmsiVYmLVTNVqLXx972BwOaimzmV3qLZ3YsibXSCpdx3SpP/DManMs6cZDfv86sjcvz6328KChJKyKpOv5NagwZLWTvKFe897f4CTRFoS7qSBY5Q3Dmag63M5lsJjh+208x3y0gZdyTP9CQBHqxv4sR0tEcKY5Z75Vaj5wpPboKm6OEHdyTPXLC2R4GB3CvX/Vl34s2CVEqiZEvS1U6Rtnxl1PxE3NJtTtbj18cspyp/74aT+bnyFwm4ryRNhell2klkeXFPyVS+eAs8tQXf4vDOeC7jWg00KFaTJYoCYcvFQYABOGITsIz67tp9q9J4Bh17q+GbSM59xQXXQrzX8U4Zm4iRE3YWIMCP2vFhnh9QT/ZqCO8kLRRhwZ/seAUUFj2EIEC6z2xl1bK4i81a42o5CE34TfetxwC9MtWEcH3JNlh/BeyzPhCsyrUXWuQX8a0Afayg6B41Uq6G6CG+8vYgnoIIplCNKOmFP8WzQnAFjc3+rqdvE3ewfYpO6Y4DdFZTYOrfmowhq9nMnZUudFzHar9X8rIjy3zi0gVHOCRAcXSep06WrzlZJaR5gcKd3Hft9r07+w/haHTx5rVIm1S0VLjDG4bNwEWKsrM1CN6bjtX+VL3fb0s79J/Z2mYSf3+lobIkigYEdOJT/S4wkRa0cq322m7y9NvdxNlDmgQvWnHdMNLkxCr05T7lUOlJJ6OrEmf3ET9G4UIzJBeea/uahVgYe1gUTdCTWPCFHG0/ABNAdWYxIjFORntputhKbcWN35GuwXAFIJNz7bpSMhM44X61Im440Pa7tT+6McDs554L42MXqw8mU5Dkb2NhsKhH4opqvtUiH6+AAks9tNjOje+zudaedOjGwlKNbrpqK5iUd5GgxKUC4YCW3sN1MRRF3tOBY7OXgLjfRp4cLzLxwsoaiDbZ2LXs9ZdT7p/0dfNBM3IaJ/AERx5ia27hRrFU8czNh9TRd9fIM9Y/QDdaRIBG16Y5jfhm6Xpx4Q4yLHuVJaGeMeZwDvoeVuTR06gn2lnCP30LUX0k6ein0uMo9b1NLkVv3H04rHpZGDEBjDoivRb5El4EeM+zoQ29iQt93+h5f5Cy8iF7mNP4uKntQ3vfLk/uZyveqwczVMpC/4VFjq1m5b7UqrjfyNmrjguC/+uLc2s90/FNUxQwbMrWybqsEGBig2uuus6g9SE5VFJ1WmJ1hIMojABeXqkL5+a6eM1hCSm6pHEBRCBM4EIfkHA7VAXnellgjQbXag2H9F8AqCLD+WjP5IOm0Wb4U3HVDhNRRkpVBduUuMFnJ0c/e4zA6oSXx1N7WZry0VTa1MppZabieS6aQTJdfNokgsgiOiel1WSK0ddRbwgvvWENhAFncwlN2GkV5+VvaxSS0ge7VP6Xr8B8NdmiDB0EQohTvrqzTg3rZswF5Gomnx1aBPVkLKeb1En39LCiJmPheVTWQ0NGsXOKfTQ7ZVITCEZBVVv6KLdM0c/rIl27dx5A3wgJcc3XMKGEH7Pf1KmW0fScDl6fA803B6SocIrUnXbhmLl1iFaOfuUP8eolFyvNi3JUnQb937lhxx95SROIDLBZmKe8qBgAmg0EZujoitbCrq6DZMpeT+4WuUVXaJm0ErFmmurtK+8IyRk91U88i0VwKlYQoj+UMsL68jltjAPHV5jPSdLA3IT0pmJ8lTzBrczQ2oB3jHzY+P0hGr0dQx1LFuKTbiW8c1I1prg9YW6Yf61IuD8f3dAJa5HVP9trF6tmJcyKi+vOkl4R79yLEvL7eOz4Ez64iB45dtblBCjUCDRl4sgzdIS4gti5ogdfdaIHd01Yke/Y8SOfqO2knpHLFn1e8ZodJCj/07XzmzJsyKhxweO0oZpSMh1JHgBmWMbYiLOh2IbS/xJkwetefrC9kzk0syu9MwP1xuUB/tOxVEnZlguzVZq+qgpRrm0QPHz9zQ0VNdolhqtUqNNaiyXGiulxiqpcaHUuGhsuywj5SsC7FNl+tdkP6vt/0Oy/b6xrV2gBBd1QJOHLyrORe/gDm4ruSlet8TVWNzwCCsqlIV29AH19jwIqP8LK7Xlxl37w2bkbInkWLvRxkqtWhD3td1o1YZhzxF1dmB43oB3bXJKM5U2+DyfisEI+5zSMxfuT0RkdyJ3rTbUlW6FXsUPjZRDhZMWYkG8DInuQadfJGElFQm6pEaeFGWsBCCcMC2aISsVWIVZmm1jRQIrtvmVyiNACXmsKMDXB0MWgK2KKzr1WmQbqVpZ2WMCyvA1OmTzWsljRmWWL5BGiMtBox/7vsX/WRwvHkrtXtn8inpjD/nmiNCXua7e+t8yN6onJWt41cBr+HfibNmwBh/UkCcLP5PcVqxhLa9hvtGHg+3HGqDEohw/2Wvkqkg2aHWihopMlBjFGu5u6qurcvU2VDJ3JpZcDCUXy7afShVQct0cKHWe0YvTOeyDUqHvgUKfbH5VLRXyFGilbh3LypDNoM2qKv9fKvB5atodtqCZN7qE4PbnLgzmHB5e/fTp88p/wyxJi0WcNLcoLTWzgCDNKcdPn439GNXcyNhVZApx9LcGDYYTFpyzt6KPOwyWlThLbAcrdriK8yxNKG/I7rZFXykkndeVL+IOvTZVHlhMwtjEIEDOkbnXp4g5Y/0wCwLeI4QfZsVWWCU/RgedwdDEe7lgZyQH23eXNYVhjGM028qVFUfJsEOp7G5r7aJag3LHD683EGRa4eOH+EFl1Y5T5VADQuIIHIo9jp7T6t4drRCv3mDgmDynv1sbmYKP/7Of6v1Hj7Ui0VNfRJQix9FyXT86CtUk/mBFoVW5f0xXveAV2fLXzoThDc9iy9FSTn7l6fAtKfLT6NI1zbUzPAdvNp7CNGVl/lpTrbEMr1O9h1oNJ68flcEEGaaWwT99MpgWqnNIaujHdpyzrDw8DkHGCqnN+WufJc3mZwScZbJKcDDhA3Mc4rg9MD8VB/3KT+Zcr94BHExuT9STbOzJ7awZRZglz0G2hnQ5mwnu1uZh0y3blmchK4+5D3r9ZAi2/BBSVCcdarI1mMyvJSsrS6RBLVVAR2SDj5xapDb7KAbhCOENUf53T4cDyOj4/sHQT2lC1X6IAbJ0uGgcWTqENrPlNmoOVFJyiDi4V8Yz1v0nWn94gcZA9CXUsU+grm9+jTW8UKreJVV358bzaxyN2a5z9T9yNToaHmMBO6n0oQCQV8n5FtFkRveuqRXd83L7IEn9wbLaRczd7WWeXT7lO9NuBgxcKQWqWM+kQFVkYldRJekz1lQhkxa31R5WlIeC0R1pWn8v4/0NW7AfJz5K08hQGv6cNFymn+BtU/VRvZTqRJoqzQqOXjDVDOg4qAgHYS/C+fShrKlXKfRS2ymXDW1YwQihLCpEhoaQRHcrXs1hqq3WiGas6EKo8hA//oegicvRlhWFLkTjqr1x91GqD0OqDula0qtvo3r4abonjgcrmMC9oZ/pJ3AKTuBE5VcmPoHuAS9PhdKzCaLYQp26+e1TvIjuJJ/DyrNvofm3kl3a8DfVIc3AUU9ItzZXD58gWw5UQujn+kZM5aVcyRsRxP1mxwEcQRilgXjGIuidmm2dPts0nu2jtGQ2pmaD8aSsIQ6Dl2swuGEkDKa0EaDqxKEv1YEa0cZLsLIJyuO6yq4cu40p42vj2ebybKxiwE9ZP3xr9Fhm0Cjv1mL2JmMu5YWUCjTK2MpbviRXoyfzWSTG0kPPfx85Bmwf89rjB/AmLw9qDx1EyEJE2ZI0MdI+czl6nIocR2fClpXXkwboAKymc+HL2Hi2n3ltUMJ4FBpmXiF+AF0CNPSPHdN/4mOilrb/fS14FVtwYimqZjzPp4ObRdDij1D8vSSt0a4WTYbUUsqWGgZSiweiuT1jBWa9krJuuUDW/tFZH8SsofVjNUgbMrSHipKN1yZzq5dXU9E1lkEg1dl4RjsKVRWZVXZ7LVqF9rPSch+qJuK9KarWnM7d3RSztHaQNfhUG5Sd59PO1OiVCRfQr2N6CsIK2zhRAehr2THr+uRZxjzKPIxm/xzK9+r0NdqFAoNB2TLpZsP59uVPuXVdj8iMIYMVHbEOvIHH9oICoNwBeoYYUaykfsymBuUmjPYyfyFMSI0VeUPR1zDOELaj2qORecvR7PrIIWCllayoCtayAD3KMTYujAYW4WVM0SIvK13oU2ab4QQ21BQP21wNA40WKFcMsj3Kbxddj6CCzZvKm6fVXxA/cGIBQgqvcbQemVZxolGkvPG7CTcbRpyPFtc8fRF7gDBOuP0MoFU+t5UhkyMNcXoBgMRDiM0HpciA62z4WwGoDS04KI8Qq1RklwLszqlEFQ80RkNuFKGc8zc2MgDnqbOwlsfOGAwqH4s3jzgP/WlQ1/7s87RfEzLyAPUz3NdqeCmNTCkejWdshA680T1hLYzz0YRFI6SZutz9JBq8Ly5FlNqkH3K6yHUf9dY6sLdU4mmSDw5/h5QoKqx+mTZ10Uf615xrTOkG+xJuh05emQihiZkG/YK1VtEP+9biQ7ThQIOokQN6e4+QZ6hPE7owJ7z8JTyHn3/1JfRbb764fme6k5+GuVaTs+/raTWp+rl6fanRk/GLrIx/Q0xT0GVcC5X8Cj9RynQZu63tGHlSKyj4VTYEwhsuiEVsMn5xw+wOHK7C86mHfoMMsfRp6qHYB1IM2ge07m61N12zZ1m/BSAxOQcKleYXQFl9ZJaCFL2tv8Bg0pEpIMUF1jGKHSEa9v43+RHxydhZ
*/