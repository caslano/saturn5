// Boost.Geometry

// Copyright (c) 2021 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_PROMOTION_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_PROMOTION_HPP

#include <boost/geometry/core/coordinate_type.hpp>

// TODO: move this to a future headerfile implementing traits for these types
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace boost { namespace geometry
{

namespace traits
{

// todo

} // namespace traits

/*!
    \brief Meta-function converting, if necessary, to "a floating point" type
    \details
        - if input type is integer, type is double
        - else type is input type
    \ingroup utility
 */
// TODO: replace with, or call, promoted_to_floating_point
template <typename T, typename PromoteIntegerTo = double>
struct promote_floating_point
{
    typedef std::conditional_t
        <
            std::is_integral<T>::value,
            PromoteIntegerTo,
            T
        > type;
};

// TODO: replace with promoted_to_floating_point
template <typename Geometry>
struct fp_coordinate_type
{
    typedef typename promote_floating_point
        <
            typename coordinate_type<Geometry>::type
        >::type type;
};

namespace detail
{

// Promote any integral type to double. Floating point
// and other user defined types stay as they are, unless specialized.
// TODO: we shold add a coordinate_promotion traits for promotion to
// floating point or (larger) integer types.
template <typename Type>
struct promoted_to_floating_point
{
    using type = std::conditional_t
        <
            std::is_integral<Type>::value, double, Type
        >;
};

// Boost.Rational goes to double
template <typename T>
struct promoted_to_floating_point<boost::rational<T>>
{
    using type = double;
};

// Any Boost.Multiprecision goes to double (for example int128_t),
// unless specialized
template <typename Backend>
struct promoted_to_floating_point<boost::multiprecision::number<Backend>>
{
    using type = double;
};

// Boost.Multiprecision binary floating point numbers are used as FP.
template <unsigned Digits>
struct promoted_to_floating_point
    <
        boost::multiprecision::number
            <
                boost::multiprecision::cpp_bin_float<Digits>
            >
    >
{
    using type = boost::multiprecision::number
        <
            boost::multiprecision::cpp_bin_float<Digits>
        >;
};

}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_COORDINATE_PROMOTION_HPP

/* coordinate_promotion.hpp
MAnPQ/H8DT5vAnFXRGl4xJ9/TkDHu7Z5xVaQAwONuIl5xFbgmQKNdm7gEtyPSvmzciHGPQ7e/6rLWiFSf/7hAJ30KFCtuyLCQKa+lE4MNOa2N6mrIvOAmPQw4AMUh/1Jcfd0qKtCPoGY7PI2rJvadAWf7PqWAwSyEJNcb6t666J2kmFVZC5w8e6fggSMtvgohI8v8oAgF4EQMJagsS5ucqGT6xqE9FZWQMbbFdA4BzbeGzRVkM3WdaKru1Lx5DpHZl30Lg0Q+NpPdH3XyqS39l4muX8alFaRhbAb7+ScJT0PaZVObVZmNeS09VM8vpgAavCcJngCFGXSR38OkrxBrQWMue9r5NZF54iUVpAhQgB18fkNOWzMSi+IbqETgOmU/W86yYDpAIIxeEAgDQjWMCkfXwTzG2L3nMqmNn1hk71BW4PGu7od066I3MilTq4DB4xw7ZTSpjbJgsZ5AlQHjXZ6/ssqPuHVZ7SdhUy8tInJgCbGekENMv/MVYC9Bx/EtKXXivTVr8MUzRTPkE7sJw1ikd/3iuXR+uKTb3vz/7C7B9EcGIb3wqT12RMDFDTuH0DQhkbim6ET+ORZBr0Bzf657IbdlBD8Svxz/Y0vuANKY7st0dhrGbH36kx4dkt4xEUnNObeok566v7KyD7Lc4TwYP4A5oD1jnYuCU6N7IveIfWl/cV4yRlDBnO61CTlc7jeLBX5m+DinSk52fSNb876MrPkJ2YeuB8fNY9CYU1P8dDbi/w6TvVQs5R8m/91zyPX8cydpGj+oGm3+3Tpy0kT8ExatyO1ovnAe/F9UvxbxapT+RrtVM7K+e07qsiLN+4mV/XJuvJ9Sl7+eUN+/qojv+AbKzL+5kMqMfIaKc/YoxubcP8tkxR1+1pY9YoBX4r9MiFqfuvbDtOrbuFeCOtuG3Pyql7Q/HYKnnlqzkSSUZ8IyIiCb46ZWf9Khux3Ms0vlE4DdiO9ewCXqE5Eiw9drgV5p2lUlmAvRswhxvmiPcNCqaJh1XeackhDgGHTN2+6CW9DjrOt4ban2mtr1ecoBqYs6/CEmwU+1WG5ZlUUWa0apqygYfWt20uvv4fpsER3j9F/mCK0scke2lWtYR6Il9UErEMTbDt4lt6r1LyLdbokMh9lhlnMMx5GmDvykYsvvhgP4KPj7EIj96wPbOaLAwAdbJW8uCENMfdqs+ajG1Z158izbBD3Cr/kF4eHxT+ph9UfmibYBsFDmqfc83GtKpOda3Gvdl1N8+Fu1r+B/Sc1x1+0cw7X33SB024bUitWHEdauybjDjQ//gS2gSmrm3Gv5LHHSS7U5eCZtFRv0bGoC6HeY/5HdagaX4U4j86sscc0hNdG5JiSJXHrRpDqgjUkrQmcqmqvsTftq7yluipmu7z/jrz/8k/cJuZF/2o9us+UZLsC93Im/F3Ny3YivfuEgTzQRUIeqm1HetOWWJBeIVH7KZbO0bdqvEGu+oRx928igdqMw0Wq9gwelHs5DI+aTSrr/jWvUxfIBMuQLvUSvLoWuv6WFdy51th5D+miSSiy3iBhsDFOeBoNFD/I/CAR74UhEU1EHjM/ymx6lWn4GDYu6/wn7vnb2TcXKt5Vm+iZWHUaYQrbgpswPEKk/vlT2H/iviE1b3UBwyKZ0PyGHtLVTt37L/3TrryWgFem5StMNH+f227jq9elyhbD6kZa/ysapdzXDupQJe5wjILCgXsm78clAlWVal5OlD8CR9U9wlkrFYblU6GK5UrXaE0ze8K1S+G9O03JUkqKdW1Gannnl+EIVjL5MUz6f+GaVck0nAO+exBXtsXzLZig+mvtkaei0WmyxteigWDUffLGZ2xI1z5VMfehCiMLx+WkxjgGNFW1IS1LkrNU5WsAQa1oBtpv6VAdK2P0LVqp+f0sLIt9k/iiFQ4JK0vqdraL8xf887UH6q/hecb07/103AkSTY8oZK+v8sPuaVXvY5pGseUuLznzkIsEeub8+QJv4sJxRlY87fejTccy7yGscXFDlVX1j1DgtMvG1YpVBgxL72JJcuRuo4v5fe8kzGwErc9sH4k3vWIjrk2d8zxLbotNapMy7rMzbWX1F6zx99HCQS7Gg8tk3AM+IT4pPomo0di3g1TIy7emYDoi5sZj7SaCq+Tk5TULb6r2kX3zVNKPuazL+JF7HAjjMQ89V+LlU/oDDku4V/K7ienER7BuSdUsmNEEhzc55qzXeXqDjG4axeXTMiDopVVcOec17tlOX3GF0w5xvE0aXtNTj8pPLvb+Ldiy651d2PllPdLOIBltiZIidGyo4l7thDHGWb54LKOfYm94jx6yuuzAtq7DTK0e/mU6el5+MMF+ODGWxE6Nb1530K6eRsNvItEceYUruR1vySnOhDXWLZHexDnv5XRsuu1VxjpQPLnr4dv0NWtphG1xZ994x37wmfSYietNqHao7rFlSWLgUI38lTcOu06aVHNud9Dxb1/YiQcQb9f4ghdUz2zyIIJxp7Nwv4RxDz0af7tKLR3m/bfWJY3N6wCJKSQSD2nEkS6aEt98pOEA3R64JYhHGHuqfnmMt2zyu8aTO6t15G1E94D4wAB4kKVmJ9iN4Gys2UC4zWXBTyAwQkmPs3123sUSpHbZsCJwjfMcEzyyf4B4OPW6fN/ZlRv1BrOC/v+fze97APuENaYrmA41+oMpTBp3Dqbx1bpxmdoezMI5xg3IYAdeHwO3w2miM7KIExgmogCS/GVWTVjjbpWxV1X1FPzJj7K5B4LsC5jbyPoojZT68jmO1HLwzcambrHNzAgM28qxCt4duRE/QgpDs/iXn9R+EzTrE3OW1hVsA4450l6xmOaGsEejazVRrIm2IUYNNElMVxRN62P6tRhqtE3TyGpDHdM6dTWr95nHkK5zjZ2bSpjD1NGGwNN6Xc7Ye/DNFhIDT9PwNReyzxS167N/Sfcsk3eF1d1Br4TVUaSCmLAkGl+34IJeMiuvtUg0P/H9JzcK1++t++AHEckP2/0KPZxqE64QkscdObqUs0ySksfvrB1KOb6LEsftrW1KPrbqypS9nlY0yae728UrH5WX4DGFxulRl5rjMkfcRvANdOxpODom75c70au2maxmTKlZsrSkuEZC6ceKRDDGKskMNcrpLT/mde81Up4/6tZutgvVw74MR94j066BWwuptW3FdKbtxXTogBRkeyGVwebS59+q3ItGSvdw9TAv81rWfMx3AmDftyftdmvFfO87sL/oHztcGU4er5UmTdb/dmuN5Mu2Rw3CTza/9VrC1Eepq2q3P72WOEzGDmFb+RZeT6NqsdbUWWXCtgiaMRUIzNjDPKNTUv/aX2oMOgJZ8xhhTlIWZSdQFWU/ANIKgBVVMc7r2rqaxPAQjg2VB9dbiY8JCZ/MHoULDBUK56jqJA5SVY3Dsgk5F5RJGb11durOhgWLQLhLmPp79RHxlHumybb2iPr7yirT+PGQBhFlhhoD1ENKFYYawsmHygPPH2WHmsmKIu7EyqoXJ8yLtQGOHiNcUbVRzJX7TJcumlVsH8nqFZ/ff0fZStNtEssrzJ1reodF0v/S1ayjbVv7XbitW5Qn3W9qUh65NGhO3VsydjGqWr4uKQTT4VfvvkexfD7LQnZ5KuIZdav3W2MtqhhFbdp80sWZtWr10m+wrj9Y13L27rOq531+N/V6ere1qZx3ZD0SQMbyj8gf2B+EH1AfbI94LZp3f1l0ftMMzRKFTOLAjNjVZWtql31+mZK8G1Ku5Su3f2FYXpfDpWs5rl97pUOcv/5fevICp4eb77wweu+8haxMdjiiTXZo4pyttZq7NO7c3SpzQzZ6UfUZ/gu7tFqvc3Ep8VJWOlvkE2x4UdwDuVRr59LNJfou1ztQ56EuGlWd+jx45LH+myKOtjzJYYD6TLWlQ3cZ1lmuuw//3LD7Cuws7JxjUXsLKYgPo2b8zL94cnnqbYxqaFGT8JLbGsEgp6ru8xOQH8VR3bOPj30DWXVLfPmZ3sSs9jzNkjTf6V+fhjXkIhR4jB4B29KIdbSRLkq7YCXrZYXHe17FmevciV3UvVLXRfog+fDXPYtLUIdY8x/Ur5QLYWc897goVvVz3o4mzG6PxdLHbtxqzXG33phm3vF1/fOHuyuLg6534ctnan/JswXNTzTBbWJlsfZI1crBLobVyfyIbiO7RR3Fcsy4YSaBzZQF+2kg4OYEc9ndtuHhg2FNfunPvPEjKrhDobEjIrgD39xFVpP4GvtNFttXeuK53tXYZZWdwWUdi//SRRlryTZiUJ96bVaTOt0+uNjyluHEuvBJ2G0bk1rt3llafX5ZubhK0M27YGrkua5B2D3NqlrKSuRNv2A6+LMyy2XdWSPOG/UARiy50zQavwPybCv88UWkWprL/2FXJCv0fmr/Bahs5Q43RShS3f8qIfw+Yz7HzVHq1fRc58j7okzyvch4upGteEaj00S+6ta35fRw9vAtihX90Gva3zGRzTzMeIoXyy2bwT+ncfXY2Fot6oz7AV/YzPsxWOo9/98wTYm6EZ9n+b6lV4tqBT+0ijj1drG/G3UlWb8f++6fgrjgMCHSwdNBIP2EBLQu3Ags/07HDcY9xrHkem5w8aR65PD8/QLres0rrb7mn4fYY+jmLUI+chlDjjMl8Cb4/otL0Ba6ISrY9beuoVI1yc62zjUEJogLBhO0n3vZBxv01ZfTqxB3NQW31HqUezHmswL31YjTq7ObBnS1E/fV5hPfkRRn8f07p8WHS0TZdkKa5RPSjumIWUxWjG5MG2Er8lr7731cJwH3X3j+DgGvv43qrrZ4iRCxzUSzj3A5lw7NzjGjFTHmGBdRx/bGAg1/MS9+3zzRiLETQMb93g5uneM8cmotiLig1zUftzQetnQ2Ts09oR94iIETwDEhMf+cg7Y3rS66wDRANwApANlfJ7u8/VDJbuqMcYiBEWM3ACPBpEOng2LCnUOeg5oDvf/kYoDEiYjxECMdwKdDYoKcQ5wDm0Oyx368CrYIWJn9GjhL7dGKERFjI8FC+k2FdIG6Yy149uLsUrykImdBpoPen+5q2Gc16ffuDri8I29WgHweSr+Imr6Ik7Voe77sc4WxGtEb9UDB9rt0o//QYBuuQd4Hd4FjQmACYf4xD/CCaAdtv44rraYzAjVCMmIxoiBGVQB6h3GAWgA3rjlwrreD34A7CGgjyOXr8c8KbBL4nXpHWiUwgimCL+I8oh3jFruExgRKh3JHX0Dz5e2FXiU5MhSjIMZsQDmAdYd9QJu4htgBMYduvwPz+nvkCJgG/kHQVLBUaFQgTNAWWHuQ5Rfo0e7VlncUyql33/2pzosEzoWB1J9iFPUxfjsHCm5FAe1N/duXnTtcK5vUVA3a0aubq227RqbD9PXDOuoIhIgqFIJIwiMkaIJUjSQNtJIaYUgRUMQIhIKl/D/y6ASr9dQXbGkdoMgSn945pia7/5X7qop8nJnkuJ+knx6/cjHlrB/hxBz856KHbNXl9++Yrl9Lavg6sglT1Q4ttB5+k96fsEEtInhNitNF368hZ4SLS+QDZSvfm/UOcWbvr86gwkb9ua6Tb4uQI1FM5Li8llTEyCf2vFvlbiqCYKg9IucPjQ5Z6FQ87Sbs1OlU9HyOLVb+1rXKryWDAqNJ20TdZIlMHAUV12L59Px1kiSlZNPvd8O5rRUbmfFGCSWreqeuZwp1cf2SxY9Fun24fXdCAMIt8yDeJAuTSc/37+8vcP1//4EAgAKAAYADQAD8AYAEgAKABoABgAWAA4AHQABABEACQAZAAUAFQANAB8AAwATAAsAGwAHABcADwAf4C0AAQAhABEAMQAJACkAGQA5AAUAJQAVADUADQAtAB0APwADACMAE8A+AGYAFgBWADYAdgAOAE4ALgBuAB4AXgA+AH0AAQBBACEAYQARAFEAMQBxAAkASQApAGkAGQBZADkAeQAFAEUAJQBlABUAVQA1AHUADQBNAC0AbQAdAF0APQB/AAMAQwAjAGMAEwBTADMAcwALAEsAKwBrABsAWwA7AHsABwBHACcAZwAXAFcANwB3AA8ATwAvAG8AHwA/gf2t/pZnPIW50k6ii6fneS3sJ33Ai1LZQ/2DD/1Pb26G1DfQtg4Alo0Man8IcUM/fuHSY2ezuManCr9M5ee1aNcdodUmieKuowyzMg/5R0zpxRzMI2Wm1eKdcXhElNZa7AFVau+riGKItLouZP298JDq9cUlmvTkd2cE1PtCGmuZdo03v3T4EP18twldPFGjST5m65Lu+XsKjP+c0QcE09pmC3tHDM+Bz1omNDbd+zzwm7wrpLDOCwdpYU9NxoVg4Z4zNHwcpWfHdAQGx9aV2OjIHY6EpOlww0flOGNg4UH4SecGxhxWMt0uznLyrCKUKXpK7fTbeMv5hv+YgYjSyk/xdDrcsK+RfMRax5cGEf1FfGSP9KnSo1pYT9VHjL+UrgTaUH/+jZB3RE1bTGpUJk20YtdW78l6f33B4dsXcrGgs/C3yrEX2j3qUWqlCDRM3XR3O3HrD7zhqm44bGSs/uXcXMZ20sKc+qWozTQN30qIXmjmxYD9BeLlpUaWdbSvXNRtVeHn+gZvEcbIKxtf4SbDx3xnHSlpEullPWsy55jtt61E7ENm423L3AoK3bIUT8yF2hwn/s5j26hnTR6AbKJ7855WyaaSVj2E0B03pHKrMmUolS5mMRxFtCVVxOtFRRKHcUPe8sabODPOXgHPUpaLHlQP9RtwKvlOy967TxQPLDCyuKNE3P4oz93JThhqK/RE81vxDnIMijhji6UcajgCuzTZy/jmn1BDZsoQZ2NXKCS7j6DZD488Vm+73UMI5o613hZX69cDq8QSJY7Ei3NSAX/JjuovFQFytfvgVfMI7l2WqrZJKSZUtm7+06xJ+fvE8+eWkSXTWRcoGG074SkuDqea7WTGKfU5IsdA2WVrKYQn+hfeKJjvM+F+4+wwdjH+BfPDCZYdj0upAj/35pPKsa/ZNZZsF56cFaJdvmMSdWd3H5MkzO38v51KfumSIaHVLojJatrn7p6mUWrs2vL1jp56EXbt9Ss8uOHOk9Amjg2tWC9GvesiZrYMKLQRKwc3EFGCEzjFnp5igOFjjBzoOOCy8ryujy6V0S29t/kzhra6qJzYYHYyzPljwy7nqa8iTG51XceVLo0yyTJglEJ2VV4xQWEBNgirbpi8IcoEWXkCHERUm8TPgnFjqBI9J7MpMrOuyjziPKhkwSye3DyTCikX8WHRkUTe/L4HI5u6jKG0tnURAVRUZGzVQy7q4+Wp34A3SfpCJSl/MnjtsM0xWcRa+9pTPI0tsNBsFnNXgzcdbLC/LbUMUMufVTF/w623VWTGjXmWkXPQpWV9Acn9PKZ87K4RIjZIvFwtRxR075lxWhpIm1x7F7CZSZlak1o8QdcNzEXaq694ienO3KhmQFxSeO2CoiqQi3T537JBbxvVkj5M7ey8ncmRHjcdx2tBmUHE0e1AQfAh4nxM8DjdgBjkXbl1/1uQ2LHtrnhCFFFp5P7WdQ4izMz6IjThBNZOMNd10FIVoyW+NKTErJKdLXP5xC1mEp7SOuiSCpz4tb+q5hl2/NLTs+/Mnts8xO68Da0wdHRSNIV+VlP1b
*/