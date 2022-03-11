/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    delgate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_DELGATE_H
#define BOOST_HOF_GUARD_FUNCTION_DELGATE_H

#include <type_traits>
#include <utility>
#include <boost/hof/config.hpp>
#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/using.hpp>
#include <boost/hof/detail/intrinsics.hpp>
#include <boost/hof/detail/noexcept.hpp>


#define BOOST_HOF_ENABLE_IF_CONVERTIBLE(...) \
    class=typename std::enable_if<BOOST_HOF_IS_CONVERTIBLE(__VA_ARGS__)>::type

#define BOOST_HOF_ENABLE_IF_CONVERTIBLE_UNPACK(...) \
    class=typename std::enable_if<BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_CONVERTIBLE(__VA_ARGS__))>::type

#define BOOST_HOF_ENABLE_IF_BASE_OF(...) \
    class=typename std::enable_if<BOOST_HOF_IS_BASE_OF(__VA_ARGS__)>::type

#define BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(...) \
    class=typename std::enable_if<BOOST_HOF_IS_CONSTRUCTIBLE(__VA_ARGS__)>::type

#define BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(...) \
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(__VA_ARGS__))

#define BOOST_HOF_INHERIT_DEFAULT(C, ...) \
    template<bool FitPrivateEnableBool_##__LINE__=true, \
    class=typename std::enable_if<FitPrivateEnableBool_##__LINE__ && boost::hof::detail::is_default_constructible_c<__VA_ARGS__>()>::type> \
    constexpr C() BOOST_HOF_NOEXCEPT(boost::hof::detail::is_nothrow_default_constructible_c<__VA_ARGS__>()) {}

#define BOOST_HOF_INHERIT_DEFAULT_EMPTY(C, ...) \
    template<bool FitPrivateEnableBool_##__LINE__=true, \
    class=typename std::enable_if<FitPrivateEnableBool_##__LINE__ && \
        boost::hof::detail::is_default_constructible_c<__VA_ARGS__>() && BOOST_HOF_IS_EMPTY(__VA_ARGS__) \
    >::type> \
    constexpr C() BOOST_HOF_NOEXCEPT(boost::hof::detail::is_nothrow_default_constructible_c<__VA_ARGS__>()) {}

#if BOOST_HOF_NO_TYPE_PACK_EXPANSION_IN_TEMPLATE

#define BOOST_HOF_DELGATE_PRIMITIVE_CONSTRUCTOR(constexpr_, C, T, var) \
    template<class... FitXs, typename boost::hof::detail::enable_if_constructible<C, T, FitXs...>::type = 0> \
    constexpr_ C(FitXs&&... fit_xs) \
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, FitXs&&...) \
    : var((FitXs&&)boost::hof::forward<FitXs>(fit_xs)...) {}
    
#else
#define BOOST_HOF_DELGATE_PRIMITIVE_CONSTRUCTOR(constexpr_, C, T, var) \
    template<class... FitXs, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, FitXs&&...)> \
    constexpr_ C(FitXs&&... fit_xs) \
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, FitXs&&...) \
    : var(BOOST_HOF_FORWARD(FitXs)(fit_xs)...) {}

#endif

#define BOOST_HOF_DELEGATE_CONSTRUCTOR(C, T, var) BOOST_HOF_DELGATE_PRIMITIVE_CONSTRUCTOR(constexpr, C, T, var)

// Currently its faster to use `BOOST_HOF_DELEGATE_CONSTRUCTOR` than `using
// Base::Base;`
#if 1
#define BOOST_HOF_INHERIT_CONSTRUCTOR(Derived, Base) BOOST_HOF_DELEGATE_CONSTRUCTOR(Derived, Base, Base)
#else
#define BOOST_HOF_INHERIT_CONSTRUCTOR(Derived, Base) \
    using fit_inherit_base = Base; \
    using fit_inherit_base::fit_inherit_base; \
    Derived()=default; \
    template<class FitX, BOOST_HOF_ENABLE_IF_CONVERTIBLE(FitX, Base)> \
    constexpr Derived(FitX&& fit_x) : Base(BOOST_HOF_FORWARD(FitX)(fit_x)) {}
#endif

namespace boost { namespace hof {
namespace detail {

template<class... Xs>
constexpr bool is_nothrow_default_constructible_c()
{
    return BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(Xs));
}

template<class... Xs>
constexpr bool is_default_constructible_c()
{
    return BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(Xs));
}

template<class... Xs>
BOOST_HOF_USING(is_default_constructible, std::integral_constant<bool, is_default_constructible_c<Xs...>()>);

template<class C, class X, class... Xs>
struct enable_if_constructible
: std::enable_if<is_constructible<X, Xs&&...>::value, int>
{};

}
}} // namespace boost::hof

#endif

/* delegate.hpp
S70IEgGEAwD33w/E7bCc5KjwfbRgOB09zZOh26BwZ5Wzn+ync/xSPR8VFFFd1Jia+kIw5UknnJy9wY3CqQ39phCLlgcdcQFiZ6j6/MYHyZZE3qPFm+zVVZpNYlpdcheH9z4X7qY3bTNmLBB6+IDDv7h7V3J1c1qi3yatPdelDaPbJ503+o7E2xXH5EVOX7/daVkS3pdAi87i4fvqsIAisnw+LHcELlxEFEV6ICZXb/7XRQFtHiY6BgvCkVoFZ093zJHBL7uu3becqYZ9wWCzznyptKrvaGsYRbTIe41tSwQhLbXgFlm1/F/BPIxmQk1Rp9pZDtzSr3+89V/PsFghdfN7KbnRyTi0Pc416Xz1oQ+PShIEHMPK3ziZGFLbHslb7rUOOXeVe6nREDyH1BS/eSOqBfN0Tv5Dbw5LwMKeKINGztPebT7gGGm82Tgc6QuIxJHyk1f4dhqLJIADFJx10MQcf5kfpr4LjpuEyDQdz/6TpEyZPmi+sjVTpsSGkllaeyAYOUGyc5HkV8MLKOoB2U4fmaGWvk/eBnxnIKp/f4CSFhnLk/96JUqk/d6Cemdv4JQkgGjCS1NnKFWYJdJjZMbt9s065GRdfviWvO1Vm0+ckO5phtkkaHRvhd4rCtv5Aun6DrYb0R4dDMr9YwihDgMcu7M9OGLohsuAMiEp0v1bUMYDaZ3wd7V21skqkAjMMRL2g2Y8PD0ITQbEdtpreGgWSqS8tofyYvdQPBPw0HBghVNJGV6CzgLZ2d9WsjTO5l/BDgz6ciDKxpKk9zMMznm+uH7LB0JITAVqwormI3JXq35YAP6XDRozhOFAyNn+YnpQ7NDD7iNMCtTNImrWbHs5KV+NyXnX7eidRmGh2K7CWqfGVCOUviJW7EI5yJnKfXZiv+wRYzyUvZ17OUDXgal+czXP5F2MiAxsVhVYu4/KF33NKPBp2gZyRyem/CMeBAPy6jEif9bkqtC79t5Kn9dv3v8+YuH6S6Ty/XCBLWixmv+x+EgTbGcTzNZ6tLOpwLtegP14lRIZzKs14M11BibTOLD6UZPYpFdH2vCAOOAhGlS1wgqGYiEIgiEIhbNKVAF0DWwLlYoY5AgAsrRyMGMRE0nk33eG7opDbwiBXEoeZI5MlV804Gbk7qdsTIWfhcPvPPPmlaA/DY9FRZyUAwAmLNnTEQyCcVtdB62JCIQECbOS81WqDmeUg51B9nIANLAuHzL3wZGRdFNGCqlA1K09eXcyKGJkRDXEonxN7+H6X1j3V3p0xWPRV+IJ3KVCycxClqqAjfbmrZ4vZGbs+e3wjplMlkpXGSyEdzlETsWWgySShbhEkWsiniMymWCZgdMUoVYfrxPDHfuJC7Y0Ii3nlUXPqjtIf797Vm01f5B0XLjd46Dw/AcwZY/oOZvLLHftYrABuX7K6ocMIJiWwNDhIC6FPY3YFysUMcgQAXbckDZuVnwtX9j4PPboiapZqMK+Ywycgd1gv40pY7/acvAGMdQNrsw07xN3fNln7yEaVL3KiMJBwFjkJBCIIN8I8SfDmVdULVIjEC5FvOBHP5WhBIFf2VUWMl1e/iUMpDP1s6SSVrHk4c773vPk2xwymAqI42aUpbeosPvHtfirm7Kps6xiJzEoS/aZRA6Nh7yjTlXdewJ55p5bwRMtMzZ9d7C9n65zW/rKhL+v0BAtbslkhOT+UtHHI+o1+pY+/VOGZ5Rkpzkp3yyewiBEJWJ+pJXpisLyu09VyQaNMVGeNYJXS3sGumk4aBfDfT5u0bapZq5WGYNVMyzSpzbtBd3S62m0ntk+QYhZn1/myee28Dt6gvnEyoASslussCWqmeS7o2W/D4YfNpSaSyRglUfR2Jv4UpTxYYuKLTkcLALySidFC1x4mR2TrRfIt1xokTPJeoAmJmFgBEBC5FvOBHP5fBYgGHOx4kfN9/s27g3MJa0c4AArPGJUSg8AAAyQQZoEIUwT2wAAAwAVGZIvbrBuZg0t3e/vLzbw5a0rTnu7oyPJIEl8V4oMjralZPXfGwCrCRz8Bal3js/WN2SkOwzTK3eEsu+3DD5LFarhAZHQ6HP1JBGN4rEKm+C3yvnMcTqnAR4uDhq4AeBNker9A83jPr7POC2YQDcL4YtDT9AZzMx34ivMYEHgLe1Nmrw/THrWJKDTtXhusgAjVvE8cgLCdVSWEqh1dbnIVmw1N3YxDDEJnwLTxLIqSZByx9q6isIW9ahRkNE/ZNFnKWRy88QHIayyLZEHwSOMX0wbDHyv0b++TGMXrpqkeD3gYQjcbLfnXS2Cvy1ce6Z8e36r0zVxqVqnbA+Qsh1xtoa5a1hHqBNCeNHRSvHNOMYIuf8TmCAHibelR7VrDoU3sg0BqaHN8ggXsRM+c14GXH9KNyyLK/mVAgspm0oYcM9rSCwUEChiSqc/le71I5XYR0e7acQ/dhJr/QiE/yogZbFAoB/a02wbeI+bqeeq15dwXyGpW+O/ni4EgACOQzVs4eh9nvqEDx8s8B+bprs/UlZp+J1mJ6VFOS98KWGM1+YCzfI9/YGmoVfpwElPYYeC95p+6nWv50AUzJDEp+4X6OoqXv59BknUW9fsq/XsYaMNTKp2OoSmu5o9gNhM/xaltfbg54ApiEDV+ay3UTRqqwdOoiSKttgaZvs+Z7LzrdDemSxN+GTJmMenkKZ8a+RSDwafIj8b/hBe27FRYC6RMFyandQckkkXK9jbEXf5GvfCyf1KXkyLEqoazbCpd5xZDYjoXFQhebuEv4/P6G5seIwJT3kzQ3f8COeGCE8cAguPBtBX+D6R9QPTaiBdDVwJHs2solfUT9DEJaMOtqjoz3zL7mEr8MWMTuv0GpuCDXUfnr4NqvIXBwM+mvIj4AEmmBU3edJJZADPl51Rv37fvEkDSxYZ4HdgSHwfef1d2Bv7w8LF5Kie0VJ27Ai9x4SuVPuS5qCtqXUVVVT3l5aYSbOLz4Z/ffn7np59ilDLQ988d4xJzV/PmaAPypd82F+UYcN47dHjvWZS6hMSbDvphqfCHHPJXsP8ubztE74brwtENn0oIM2EAPzOTXeg+nGAYKoDHnGVifHKjUbAhIXLm3FlDyhdnDNeJHFXfOFGdCugJhHv8Y+0/9Lb+P7g36sf2cwcgeacszAH51+efkFLO+260qOGFIygPqRU2l3xCgkoruf6q2dg9HOs+1nv+F2EhaiKajg15aEB8UUbLQyXluwadBUjYI5p7xxNcE6cEt9t3fVvy7q5Eh8uUL/3QTNL/kWXwzYq5AixGr9J9HMbcdifTSHG1mq/FUKJmSvCf3NYCwm6io4/GPtwcGXHLkUyjEGoSZ329C40lh6wx+pCe0v3BImX1EZ9WTj8gx8pDvxB0NkYhtTnCU6otIEWqxtzy+90IzXGcVZHmzXPs3C34x8nSmw/8cCCXCohHoB/Yd44sB+pIaEdSFT46WIeOFIO+eTo9b0iUL+xdcyiDr8ondSQKzcuZvm78z+WjBP2sThf7AuX7rWQHKzT/Lqmxn/75fVo/rTlBuGwtbEwhND3xMpwbxK88uE4mWDCpAAqDDrMNapA8amNUNxRK9nk316JpvllAf7DPxOmOBw2vKs3tD98pi6TsaeK+vaHHansxH5crdAik8lXt73/4hx+yTlUC88P2Ra3kagK8bsCfTjK2mVPLxW7PhUMEj5x/PbGAt48RFto+HxU89fOkWvEW/7Ds7iMavPOsWkCj9VIAywc5B5wnMbPyCdreDPOGLA4FvZ209NKdLU83ELetL5RpaORMD1cHTSixE2v7oGkY/ciQxwEvfXhj2U2jPvYZIib6e6niECDfL9nILNgmycNM+8gCCMeVT49PvhBhVCpAP5o8+vCmMj1P6z8bhUPn1Odo4d5ShX6XtX17ry5WcFh7fOxDbLxRBpallPi7vUE1mlT2kpKKpml6AklfeTEaEQPqV4DrCOoTUPkAbsxWv/ozcpMPI3wo3XTCGCiAfXhD+bVja7LLwSaakwy7rxV/aszH9VCc7JMIVxYO1tpFDbD6T4zZ+YIPA8oIaBwBAnkd+8ix0s6HdP2Esk1OD3bSo6P/oMID86cXkCaA1qeje1W5XIofPxImj+hIhSCCJ8/NviptYEsLf65u8XAuN5bmCpvDxKi3Ws/BamsVY6dAT1CO1RnlzsslvrBetBOfaymATLscdagH/WM1mc38SXhIPYX8Or/PjL8ipUXeZXQBGCczV37Ski5cgXE/+fLRXCJRpR7Ebnog4HM4v3TIMpqPl8JQcO6Ruji1Vks/QXAEkjkqk6/Ue0eqPUZUKidRv+DoLT6Uj7q9kbt9+zhMsMomtuOBeQ/6oFjFWa+ms0gS3Zd9MkW8VBePDqNm0CeKlEn9kBfehI3VJyFnGbjssHRTmpmXE7FHLGGFYMUpuVcbTbTYde38jmh2scM1u9wEey+Gx72JN1vzUSOiEMsvd9w8cXD7jsTNTZKaIFn8ltnqTEXO5Tw202GQyuuhbllJ6UMu4l1lqYwSqI5SsNmmycVQJ2FvJgk4xTD578h6Al202PJbDMb/nYf0QijgV3dN+OjM9VaSPUe9Yu5JCnX9OfRdQTtWyzUvc6OeERDaKJJuPLT33J7Uvxhynv/iPsnyAIRtkbbaqezsrcjytSHIVOF/3C53EBhockoXPVEwW6U0VuFDn6OeSKXP4L2p/WnKb/Fgkma3DyZgmoyIyiB3x+Y4qG7CTxu50JbHhPwvJ9XE14WsZHwrllEUC8LW4sCeydC+SWEstPm1nUXLyqZjvx2bgHFvbavcp7VI+mvgWWXkMrXBTHQGmyXA34SXUghzfp4Wv6QNJb1gWZQVsP2VfNy276nJ2Z7urkRstZM+dnWlC9VvnAx3CMPLbAcw9Wnpwrn7qBk5fdL7vwJ+8EVYNGrkxAV8bFAmZKES+wImsD/4+xqsZHKxsIP9sZHBr/9nW7JcAv7W0qfa7hVgNYBpe7cwDj0D6KIzNKa/8mdTWR6hZnwViD76lLTB69iv2eja5MVNAj1SJjoRUTT5ZYkkYg2iWL+bGGgjUdrkcIvT1hrcPtmtpU/TPoTnBl4GaXy9+oTDF0vtt0k1g9CLChejRr3ri2e3vZH1v8Z6VSw8r2Ijpv5IZVW17C3aOJhi6YeUFZPu4QAcr6a6Fb6wkycC+vgzkSuSrFNmZgZ0X4UNT5uWIF0eZjC6UGa6NBg4sTk1dRf3VJJRyKDxkwHuhHGHneT69JDMcpC9owFKKVFurm+nJKAhsr4FaDbdIbmvPSwqTVw7ZPyYFC+N72nM45kGw4h1e0OU4D/hWN9TCU9kTWiYVs31o2veyPP69SLbxOQA6iYbZL/g5PfcUtt+0TTf/m+e263LyJd+OkEanPo35BJauEWWjkkSAQvAMxf3PW8Jukym1LBtZQeF+Q0K9I3NQ9BzauqTxIb3bOmWoj+ae1xNChHSuwH75cDT5YuKllqMgLWOa3MZt40Qaaty8Vk7+ngk3TRNGZv2AlJHwv1dqn2ZSdrsl5/ve1oMUcVojBADxl9YUsLSlIUmTJ27XHyfA/f/WRHYPKtKTki7VICmj6RXlHQXqwhVredYJ6xs2WibgHCmZ3AftctYVmcE0SE9Ow+lxNCbxCXoSgYJxZ/MvKE40j5RkHzIKL5qlqZCyil9RG8sw+znC4v8r/DcEYJrSc4W0c2ZNtB6fcU9leGR6xbX3FJ2ixSfDNuJcfeWK0nwiTJOINkaJ9eVcu1z7/Y9l3dpYRaaf25OGzoOsw5XuI7PqktqAIWRdyoeiJPOXqtM5D92lB9bhxaBlniQTfU+g/+71nBRawt5gb/urR/0ktEDY0slQ2PWnFQnGhBfPKhiq6sEmTwfi1TSZ/mMTWRli8B8pvZzUZ97I4xvLlEVaEVacW7Sazy6euBF3EwPJJxtOVvaUnLRdhMafLP6E+JBGhibHKxpYLQMd3pfTJcjHwZtvoACHqLK09Fy6Y//Y4nHGHR+MFqxYFtdM3Cu+4iLzbG+TzQ3zDtIM9bYYZfRSRZqY/NpQ85ARR030vWeliBAn8ISudGMV5+U88XXoPBtqSK3gNukabBtzfgHWedCz1F5nkhEjtXiSEZY9moZ5PTZ4SS90blzmpeJG98jhecnuxhqVpNoTZqdOxnVgbCX1220U+PB0wO3rVTk8Uzsewax3gsm3vEi3ni6OtShdO9Jth7rcZ+NyQWOqsO5pR3ScUX56LNysyEr7Db+lbStZhQoufBav12EAeoN6N5ugAIaZ8ydKKFrupbLAEHIRpU9b6Qx4KhRCVUW1NoaA6xEqKspAHR63pHmeiURzv4mJVYKplOcdSi3Z5hyo2HQcNStC2CURbSunVzXo769tPlybeMcV/R8t328YfhbjyqTvrBr0jHWwxwDnHeh51GaNZn0Xyte9ebhTYJZodEs9nBA2trPQEnHd/aFmpM+EARyT5vZVFmHVnuxlj5dAslv/49PjnmLdlTE2cUro7dK2alB+wqfwfCXrR2zq2JcYsozE/Ou78eXg2s6TBlITLZ/Z2BbzKZiROomMmCICpKtgpwPp3SxcTcriiVhcBgzaD82xHizlQjvnfqk3z17adW2S2WF5NsRuv0vr/fw/pizJ838AQIY5Lqw7+CE/jld/TgH3YEbsVG3qFqBFb/lHCCXdYeAVWB6bMAx1vedbPl74oOIRpU1ZKigYCzEKIQktWq1uq0NxLIlXi2QFynRiSS4ezJtCRKgiECSzw64r9u6twXQtat1k86n1z/lN0fAPjpRIivbDpTYuFhAWzIBLGAvIoMBBphGF2jDEDxSmry4GNImRVJlqtlLdjNsVnqa0ULLVyrajAVcLJeDByvN7++aaWkTiYON8k7xr6vrkVHSSfPz7zktOd9d0s2S4nJT5Vz4hqv7vDpJPa9d1QndQ8s1pbbpG3V0pj17lKXOMG31d72WxLIY1b5paqJE5aFd9F7W2Pe095j2PlMtxTOCNeMwzsBgmQxiYBDwRXsbOp2AbGZqpHTDKV3p+XNhhKoznZXT2DE+IgQHZl77YAl4WbyGDASMsoALAuU6MSSTBbnJx5dnPjqph6UCHTKbKhGIFOjz1v1/puK+O9dFW22ygQcEpbFuTg3ABjjfbB64Tar/D7faYiBjIV8zDsAAASRAZ4GFaZVvwAArU/Y5wGhsqW4rVPN01jNr83SCfl6KHDrcOKjMOvxFsT9vNsGrC6aDugD86qDflkXrr2RKYW1IBeiV/lKBbf+P0n9TOJGV/5fcW3zTZkJxBIlJAxHQVZlbiJ/ryHCioHBwqMu21hlnmKBPOdIR5p195iaxHAopA6i777Wtu9id7Py/c7PfWx9fp2dj8ZGb/7myhvWoJNebu1+TH/9R0cYabHlaNdxqrvtWr/LjJhu5p8Hk1SCF7WmdrL4u4/4Kg7OiyPD1jcuQhFuae5FA5ZITTb1ii3HH1mICaXGJumsSyntubPuNULowjQvlLkldNHSmtXBj1dkpzb3EpZq8oQIEoHsmTIzueobRfiIC6o9Cb64Hs1X7DzLV1lY3/+JgYUemig9sqb9O8JtZNOj+D1rPVt6n0NTXQqXOrjpaGJsvQAiyjUWowBHvP0eE/9ZnKQiv+7yWEp1XrmN7Fxixl8xHvZEBJql3W3c03SqQ35Lznm6Z+EZPTwWJVfb422CmBFcZHXTLhkaENv0xZ3A+gv+ZQ9oM++dlvT4CmpMEUgBRP4zNaHaLmpx2LvDOPNASqSToEKhQXyRqKFOnzsRPWwbNErJ8ebIAxp0JwYJQ+GryK48XhS/1K8vD4XGmGScxAAPC8HJed+IDhfqHfrNI8hK0C6aXnRtnzeKaozV5zPE399x5aRyvQJQbUNY6Ik5E/zQjBtrEDheb/CRbxzS8fBQ1JkGQVBdYN4t62Sm+D8OtMTNZc+UY5RShJfF7AGtU7751IxGHrImSP25sGaUK6ijnU/LTUI+ij+ss1OwXpiLu0BjrU/ZPFyZ+y1l5k+HWoHLkj6fW5yEb0CrKUgODRWwJwVeYW0VyE3MVPzZwhdWNoG51uZhpe48wd4wOb2awEJM7v0LA0F85ClOlO2ptVzfdETRqIPittTS+IIrceey47SHcCVcCJwRZG+5zRK67TGjMS+MxYOf/EWl3rJB/8q3YI2l9yfOnzQyBZM5VT5ZOjKGo7XtjVs2FyRNweIXGJxSPbggUgcS9Pbt4sL7xU1iSo7BbCk+cHQtDUod5bJE0ojoymNzOdh202swXoYGRGy7Udt7U8RP2wCuOKYI0mCJcgp6ewJTv4zahtID6lOrK2C4JokHHcHHcBiWBMfbV8PE5WFtd44JFuQ6fHYsTHt5aaaGZLIKoUp5rorvuCQODNNoAOKVN0fdGtE/n1Vpi6ZVgwIzWTJGZwksseGNeYKCqzqSG8QUxErelXgDRoGL9VK2C2MCGuRuh8oem4LwwfehgXlpenNWJZvX+jmFuCkWoQ5aGN0dFkSq+tUgS15a/fNPh6XEt/jmHOpVM+laB53AQtwN5ajYEuZpD+7RwSWuI5dc4hMA0siq9Hag+nFEquGp2r6LLUGo5X36ngPDsnxBj5fTwPPQtIyo+NKGNwh8fvasDJ3RqE6zeOeW6VcN6i0Qd2+bw9CA5jOoOOkCdIW1QB7HNZG4BxrBIYvh5jJv7u9zR+BdKcKLjfX+F1uwdcl1321kpZPeOUJfEji7QZU9eosr16MsAr4hGhStlpMMZCGArNLG+KiqtYqxV1iAJimyhFmWCTQmUVefdleh8m886HXmcwfvFagFb/rM41TQhqPqCjRD5WS2hXthsu3tC2m2h093b3ZcA7q9kWiCL9Xw4745FDEqMI26e7xxsMMbQiyeRjyrFPC2VgggrSKgjBQNJoy78e/CMkeoQIgIoToG7nt37pzqwzawYraJJ95ZMU8ds23HTVnUcXWvvnntj+b8+fOXD/mNM+XoieeLikVvceqkmae66ZtgK4S+6TOQpbpsuNZJBSCdVjnRXXktDONhaBr1iUOf59p0U/xdO06l8V8RzFU+9ahZW4EANh/jg2urgh7R+a8Lly0fXV6CCpKWhGi4Ci7O1syZwAsSg0EXgXKfiuvZhdGaV3IHTcs9wo5Ci28/1vXPy0BEiRnFHxmsq9ERRUejrS2WCsoqQWXWSl/X2oWyVPdeWW9vf1yJQ4/p+AvfIAAUvaxlEIU=
*/