/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    implicit.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_IMPLICIT_H
#define BOOST_HOF_GUARD_FUNCTION_IMPLICIT_H

/// implicit
/// ========
/// 
/// Description
/// -----------
/// 
/// The `implicit` adaptor is a static function adaptor that uses the type
/// that the return value can be converted to, in order to determine the type
/// of the template parameter. In essence, it will deduce the type for the
/// template parameter using the type of variable the result is assigned to.
/// Since it is a static function adaptor, the function must be default
/// constructible.
/// 
/// Synopsis
/// --------
/// 
///     template<template <class...> class F>
///     class implicit<F>;
/// 
/// Semantics
/// ---------
/// 
///     assert(T(implicit<F>()(xs...)) == F<T>()(xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be a template class, that is a:
/// 
/// * [ConstFunctionObject](ConstFunctionObject)
/// * DefaultConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     template<class T>
///     struct auto_caster
///     {
///         template<class U>
///         T operator()(U x)
///         {
///             return T(x);
///         }
///     };
/// 
///     static constexpr implicit<auto_caster> auto_cast = {};
/// 
///     struct auto_caster_foo
///     {
///         int i;
///         explicit auto_caster_foo(int i_) : i(i_) {}
/// 
///     };
/// 
///     int main() {
///         float f = 1.5;
///         int i = auto_cast(f);
///         auto_caster_foo x = auto_cast(1);
///         assert(1 == i);
///         assert(1 == x.i);
///     }
/// 

#include <boost/hof/pack.hpp>
#include <boost/hof/detail/result_of.hpp>

namespace boost { namespace hof { namespace detail {

template<class F, class Pack, class X, class=void>
struct is_implicit_callable
: std::false_type
{};

#if BOOST_HOF_NO_EXPRESSION_SFINAE
template<class F, class Pack, class X>
struct is_implicit_callable<F, Pack, X, typename std::enable_if<
    std::is_convertible<typename result_of<Pack, id_<F>>::type, X>::value
>::type>
: std::true_type
{};
#else
template<class F, class Pack, class X>
struct is_implicit_callable<F, Pack, X, typename std::enable_if<
    std::is_convertible<decltype(std::declval<Pack>()(std::declval<F>())), X>::value
>::type>
: std::true_type
{};
#endif

}


template<template <class...> class F>
struct implicit
{
    template<class Pack>
    struct invoker
    {
        Pack p;

        constexpr invoker(Pack pp) BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Pack, Pack&&)
        : p(boost::hof::move(pp))
        {}

        template<class X, class=typename std::enable_if<detail::is_implicit_callable<F<X>, Pack, X>::value>::type>
        constexpr operator X() const BOOST_HOF_NOEXCEPT(noexcept(p(F<X>())))
        {
            return p(F<X>());
        }

#if !(defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)
        invoker (const invoker&) = delete;
        invoker& operator= (const invoker&) = delete;

    private:
        friend struct implicit;
        invoker (invoker&&) = default;
#endif
    };

    struct make_invoker
    {
        template<class Pack>
        constexpr invoker<Pack> operator()(Pack p) const BOOST_HOF_NOEXCEPT(noexcept(invoker<Pack>(boost::hof::move(p))))
        {
            return invoker<Pack>(boost::hof::move(p));
        }

    };

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const 
    BOOST_HOF_RETURNS
    (
        BOOST_HOF_RETURNS_CONSTRUCT(make_invoker)()(boost::hof::pack_basic(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};

}} // namespace boost::hof

#endif

/* implicit.hpp
HqnVX0n3O9yJppVZEbQFLb23+oYko7JdCagFzOfqdxpHFSHL6WMRLc5NbBmVz/R/HYF18qJ7CIlanU0KRPpI7Szh/DXd/VjTEsV3l7NGMVyQlglAbKTJ7CxtPHNGLFNlBKR2l7kGbw4RW5NZ+aOySPY0TWsl7V2R76oDjbwsM9B22h/dF2oTSVyLoScDSmwLYfsjQJp041JxWspelyNzVvY1k9EWv9whdzJEXlWqroPLNFB33odU0rG0qpG7UR1p/mrlJLa9fTw0TnkS6gy1lPwGd7Yxx8G8d1+hLywduOoiBiKIkyrNWf3lahJjnDHlaqA+3DWdcfjC1wGpWVwBuHNLnTcot4kUdibQtgVwPFMMot4oZ1GTMtBsWVY29Oin2gKT2m/YjemTp4ckk/sedWfmnhIJefLmaSYJnflgz2307wnuWBBK0mhec5rL/edo/jLFz9C60JghJ2M4Rp7KBGGDx8hSJIGev4OCXAw6ssONTxHIXQcQ/5FRqwA+QjPna8OD383TCvSlBO5+Dn/xRdblpC7ayEbcXtm31EzeSk91fl1fs724bRLdCvq3RfhGWIfokFDQbH9KrDvzBhxsfEpuPIEOkSO10G/V9FoFuDFJNgV3VOSOI7yZqNeCC+lysV+rGQvmciGyI6m3ANIR7CtodGqNGbodo1e5U9hkwRG6XYIY9rgVq4Ho0UGuIYig1nNL+/H8t4IoFaSLm07Q9g6eRmPpwtRXk1bfdiFqVTNna2K5taq2pc1qgLWa8OkICa05HnoheipNln5FKnzg+rL3R8N5VbMpJIN5VRMbbPXZpClB5V1dxRfS80IfPsd8iKifqX/boGdcgDVwarxk7z4A8C3Nsi2q6yoONgs4gDe91HB82qDHSrm2xZxpG2/RwFYZl3dRzzZ8xI07lrm2XfCHR24qHds3kl6rsQDlsmzhMzi4oS8AzVcGjXjAVpTz6HmfZcAWB+nzOd0Hoke6LvPSuiK4y3uQ6soSF4yJTxlUcKdUx/3+52mlkY8Pa4Sfvbh83FEDCKA+Wou71YfTWPDpMmuDVAY/9K++003EzepCnMqaPnw0TAgSPwPo64F/bn1+X5KQg13imI+ZUvLBXUOH3pTozjZLKnKYk2nxbWmctu/mXFegQv2ac1qClu/m0pe3hLiJetrfzu/WDk7kZ/n1WzN36odkBdajgBpIE/1tLUoOHZOlSTURehGTKjV9GFE3F2phg0s9CqilqU9rk1pm/vdnwi4539Qeb5A190Ci9fiRHCvUEhihNTj5cT4X8BI2+ebjsMRuyuT71g48JEy3GjNylpTgYzUI1opGyT3Siv6tLlmyLG2T2xF27cVV4qZh0ssFyBY69fdnVCNTcGZrg78p3NEURPJsIhREa7n0xoRQI5UOhB14ikjyrcdi+2NyMBzQmJcwttHxVqcm+6d/d0/lAmKIdGvVVV4cPZXt/o1M/DWKAZtrKWiAajGm5ETjGKg/Tg/UUWYb2BmluGLVH3cwfSViP7JkP6JhPxKUaFv6s01buig/jjN9m+gwziIByT5wcZgknVTfus/joSEr26KatLBA6aGhYA/NTXNypIoyt0DoIVGZJiI7NN9B7UEZlxMyt8D82FhAmJwjInaDdHam4KGBsX+81x5eSfyJA8TNeqGsgVYVr6wxn8cYd+BNnLx++qGTr5OMA3k6TyG9r7cS3dlWP2PLZBJW+DhyBGObIqayIfoIv0fTeZ83mkMjH9WmmU6u+QBU3ihETQMnsUDOkbtNs0jOcSBSI1Vz2sfqwGwn/FJaCppQcHBq3lZ06kiiZJxQ0FNYWpxQwFtauiNp4CPXL7kXYUO+V2wn3CMg2wO9p625AnvZA6g+XW8zVMDr+vTvZCa84IEgFiJCt0DRC+FlNuDBeAuvfOXMJz7ywge+v9lG7wVUSVi/Er1VYyT/m4Ny6BHqQ2q61woZ2Bla+K47fe/m+iJ0Gzs7jn1RjoI0aLsKxTNYB9oXvX1pdJU0ApCckUV5ZhUQIyEKL8+yQS/nk1+hq0b/G5QnTGfiwkK614ysgW1DFk2zzvtnQ0Ri5pTcunxBXsJV4vk8WTLQ3DtnFgtM8zI3ZEWSNZjwucSGZcyrKH9yOKaXdb51ZXABYmH5oEFFi9hrSj+sArjugK0LGm7OcWQv+/OZn/RCufTiL5744haGZf1KLxnZh07xu6axVKjvTfnAv4cPOMA9qyfM6+2GfRl9jpdxDpzsRm2ix0MddejIN5i32FlDUdcCVp5rPDmXQddweipQE0x28wS67pSiqPZM1RvtIe4C5iEkpXqG4/cIV3f2YLnpThFCi1xgRfBOdSEd3dRYuBqngEWdUmre4W/YY45yl80q1WrKHuBD2d7yR0wjMZLSzH8g0g/J44ru88ZMnaNx4Bdr5qeS/6BOqhoVis9rfJHyu9wbuaJekJnV2FPL2HbJdTr9hv6+/LyyMreIggKNGHFmKXcwwc0qrF3Jzr9zi7ROC7dt+RD6GTu2WGL2dpy+QE21lh81losKuv1MoWmbkPk2epOqeqvZu7zy49EiL6y1F5LVwnYQxLZwfnyLXxtVU7OoAUFz0oGeTBvMLBPasDH9gbcZRwogyZeHIC9RvXitpCKPetvh4SCI4e8BA71/RFj+ftCzaU1Rid0OGU/O0Vq5B4kzCcrFiSGYWLexdV9xw9uniKQwzBY8+KTtDZRcmIKwPQwnQukxMMuiEUSBE7rm3lnEqW6vS/gk/vsyciJE18FVxiZWZImcb0TH2YyBjtJa4w1KtNvERuh567s3+cp7zD6AEdTowOqazJbSIeGlxlDfFVE5aEaq4PsOuzbZn47CbWhm65TqFkiEZHzrxRbVI3oy6bqM9hJhNUsKmt20sE+kb63A7pVW9mMH6nU67/2qei1gr5FwvdGTQDUGfMkbOJubz9iJ1lUtU9yr4nh7eQUwXGFijTF9Mo0yNmHlxPrMystLhuKpZ/0y/iEnM+wTQzfl87Ht099IIDCpQcBq0r9I4Z6YrY93VX/3pPNINLqJwQPSw/KM4NT2aeupNgiwmq/jb8DyaGCxL480ojo5bXJLiveNqSytZWioAVFcsx1ofghQmFBwGf+yAFtKz5HfkraVS8nO6xwCvkvJuAlDtxzi2mfLFJWe0X/TS7fus2hJ5ltG6ZNycitSyFnbbsHDSQDVkRvO78rPIK/PKPPGconPAdhO8+B09Kducnqnt5674TwKo41KJC0EdyU8wqkOcGjwAmo0KPbpcthzQrT8kIJBgF/DOJvoI29cDZlhio5+l7X5aA3jyfMziKLhnlT1EYVDhge2oRDyTbGoFPaViaNRD5K72r+0Vm1O+jTNywHwU1sdnUhIPFbJMp6yPYAgzqLQiLqshRl9Tvx6DMJLXvpJUTnUBCGDUu6rzuWUKPPe3qm+CQVS30pmU9bB8BpGU5EWNC510zqloGNKW1TiVgGuifOtQ8lGeN1K2okRkpPCfx3dP7XUYScrGWwnyzdszovOdz164x6y1vj1Zk9yl9f70Tof8MUihOPwdYMyx+cu8pjWKHmft0GtLGxmFR3A8t+9krjee3IO9eZ2P6zKawfEdzK+W87GG1YOZve/+InvJ9Iry8M1c/jKELRTa9jWf3VY0oSNAMM3f0CEuUaR3hvDD95qMnvv9hpb/H1np2X4ulU6Xf0bmxD3NbHWYKfBZW5Bm1Ofq3LQE81MDwTdTYn8NGElV69jNe9U7rw6laPY/YujG8NrvdCkPU4kuVxMeX2EOLFMr/FGXGHhKLzVu6S31nqv9J93sin/mnFaV02GSx+jSK72dBMcesjb6yfZpteN2M5qUcvcgUZAf1Eb+ne2+bfnTUVj7lc6lsTQcWK981c64GoKrgjabCxQmuRCpr8uvncS8ohmvHq1if6N4TjjYTmOlHkDEsLVtCMVD8hwxBCH3TpU3d2ui73gr+BQXl8NH2ErClXNAltq+GMLIvZRqSUnHFKKVzpltpxTNPBvd0IN//P7JtzukYH7eIPvNQYa8dpc2m31wAldP9kDXb/4V7gDOv/4jV7ulc3QmXBE7tLTirbQq4GrpaqOrD14OfYNIUxpB4T6PA1Ip8b5/m/MMtX7+wByQhPi8e/ZAXJZXglLQ8A+RBFuEt+5ve9y4KIzh0PtBcttA0J5ftkIQSYzOpDTb2R1xCwn8dr4LtcVSSM7brYTYg/B8h9/F7rFY07JeVdL8jbOZTHs5o95pXqOW/TPQga0WkbglubAV9EZ5aefEFtfxq2bzCsPdH84h/Ayd82IMJbZhmXrAV02ofG6jKXwdTmBcAmbJXQJu6vHg5ESvIeP/G5xjaHp2vE2UidTsPdnQ7o8ev6iktTgpbdHXKP/0r5odBWcvPqV4ZRFwriF/yClqBTWXb91FwrxJX3wElPwEjGwwfuO51OYOXDlDLeBEbOwMfNaxtIGbvHCbjUvydmm7dJsNAhc9vRnvSJ4NoscjidBhXd1+fcrhOrs3qbUybQWo8CrWVZBKjH09PsfhP5YplN+Cqy3pTwO3DrgMiN1hTbJ4vonUcbkbzBKIp9IiRiSZB7KZHM0pU0wymjbL7BkLUnKGXYUyhHZzHIYern0HWbUQqyOvn/N+8sCEkmcxf7BTvr2WSgTRS97lO0nwX/e1tt4D2kd6xSgcWkJXW0wP327cOWsaysL4f98lBJY/DjVOf88noS2aUPqqGkbXcL7uu1Q53uFRalGJa+g5vszgYb83L8hy3gIApOpsgwb9XTdJ6ZEWjCoSjrQHFuE/xvSouG2YEBPrZ+h0iIDxPNklgfnuPmJCArbPlqcIitZh30IN9xQAufcGOub7tdNKIuohMb+c3X1BMXCtRIGi97DSqX6TJoBtpRl0h9CV7lgOABbodO9vRq0sEjqFe6MjPsWF9URscbfWokCK7c5AUZ6GkNozdnIZ69MMyTSxMRNV2mMUz40YpIlm+C37+udLouHQH1t2mN0ij8h2705vhWJBFVpABAsdmcOcBCPC6Lr4u/c/Zat7p+KGRIc3uTR28pvnFiAjoEGplF5qaWksgZOJ07ZkExzVw/TRYzXRZw/MuZZLIL0h18Hq1Bs3mOcWjyDP2E20wOkjT8hwhk97vCvpbiIKKTdLTj0uclJYbUnh/O0KOzjBkj7QVphrhqsPJlKYJW7mw/O3a1iZDp4A/q8QzK4yRxACuRweHbIt57lu2p1YbxjG+gXlRL5S/oMCjZoGwEzwnVZCk46aB5er2oE0fwUpmjR8Ftu3p3weYp3/Li2Cy3QBtEnssvGswpIgN6Yy5lnMS8I8KFuij74NcVzvW/xBNtlfsRSfqgCuge5M4XfJdPlyJhgeWbemrloBFdbRei81pig+a5mg0UIUo7S09nbmA1skbrCBEKg77yAPMoTdDi6bp58yVdRei/9vdp5AndKCUH8UUfyOllscYhEK6ODPxr9ZjuUiHLiUzA1G4Z+fXeuzsqBNuyjr44n4Luq+oIvAWG0E+hDME+/g6iI9tVwaR/Y7frbzM8hYpbFPVfh6r61V9l9HaKqpVydJEEbx06wp7PvmQzP4t/iRHve6qedga5Hrhmvf4csKOw4Y4SJ64P1iPMH5M/gJfE8TBqOigJRUWRy6BL0GndqraOMQCmjuClBF70LNHWzl30ec6GE7jRW+/3G81NvtRgOEF8Tl/2eBgmXTfQ4XXzfuvqqeJuD9kOyzVEgGDuglwa90UOHCpHr1VsZzWCZKAF1Y1EGMvXxiX1+pcVjygclyISBG5iClJDUdOdMyGQLIPMepHFOpOmkU/TOf+MG8RZZkmKDTMCMEVASUP6N2AgCt+4/vG9fb4nXJz/CX3i5et647Fx3eXfctPSAUiQo1LSlFzWV2kklR/dCO27+WGfc8Y234l0q8wpqpxrY6zLS67Z3l/vOKIkSse6ZedF1Fcovj93pFpYAYXxXZlYfjOozrof9rCf2+kqXO1qzgssXu7GWPqaeX7ANk1Jjb47o6cIsj8kHOv4xIdSkEU/7+166pSsfEfFYfHulH/0aPbEgWTfZk3Z6wSVoWvKGHLkjUjkcr68I9Ry9hT2TZTaJitugN7HAeizr0uCFop3zzaD8fiMIu5tQNltn/uaWz6qvveC1ShdSQrkWL+eg7JHt5q7z/OXooaPCp4PJRmWEmT0pflhMFj0Qh5xRgS4qQAdftDJxhxAbT95o+4qW2wBd8pe3uRayY6MTnjCK87GSzOiTEdVDQbZbdTszQByaVH9epc/OCYqUhn5vUVCxNR8L6LVf5Q/PZjEaMRrVw4zppU6m3UjnPbKS3oH6iR/x4j/fF8ba3eh4UgwhJxSUH80b33ar1qaC1+2wzBi7UTyM+Kqat+wHlRWRqmJ/N33PqMZRpDUCGGOoUa9NEmdUFxzd75dlz8CRT92BrwMWzVX2DV0rjBf0SJIbOhWMNX1fcFT7p93jaKyoLO7n4K+fnx8gAEAA4F8gv0B/gf0C/wXxC/IX1C/oXzC/YH/B/YL/hfAL8RfSL+RfKL9Qf6H9Qv+F8evPL8xfWL+wf+H8wv2F9wv/F8Evwl9Ev4h/kfwi/UX2i/wXxS/KX1S/qH/R/KL9RfeL/hfDr7+/GH8x/WL+xfKL9RfbL/ZfHL84f3H94v7F84v3F98v/l8CvwR/Cf0S/iXyS/SX2C/xXxK/JH9J/ZL+JfNL9pfcL/lfCr8Ufyn9Uv6l8kv1l9ov9V8avzR/af3S/qXzS/eX3i/9Xwa/DH8Z/TL+ZfLL9JfZL/NfFr8sf1n9sv5l88v2l90v+18Ovxx/Of1y/uXyy/WX2y/3Xx6/PH95/fL+5fPL79f/ax/PaKXuVvgJMsHhnO5a22l7gNnWp9TNGg7DLLL++OZjTjLcEudT75a2l9EZEarDQ19hbYLiJaarqghqXEHqjNqau4dk48H7TqTWg1m26G0sDvYGpIVTo8/fKB3oj/WnmkV4gipeguShQFZxLLd0BHoD9l4CBzVMj4PLY4zAxepRvZ8/ZPYeEoznT0j4ENMHmT0NQu6chqiFA7D9RjNm7nHDmZ3Fuwj8Y+1o4+Az9znDrdxctzzNLO0/YZ94G26DyQArSW4nrBto75Skl6RZYM19aqN/4X2aadA09dMG+IzmNJ2l8dxycW6olVG2JA70g3Sms6JvF5JpZH6Qe1tRQ6ekN+H4RFM8le+jB8UJofEydbP6yLTD/jJlArFyHKDt90fyzYBbs5h9f3UAnVcuM/PXi29O7UdJNUaRXtEJV5rPgdxtOBg8pE+w6/cMBdPRRsdTzDP8WGYLXiLtsNzDHlcogbwALd56Jr+4zu+BWYvEQp0rk1eHGUdvayhLd+kCLYdB7+hUSgV0M829sNn9Y7zMLcHe9FVdzE8ulyyBXKE2dgCXyl+9iWWzAlw05Tqg+XSDBh5YyPycaNtw5J0yeXKpuLwbF4SsBT7eCaWJiSjTPssuuo4Sw+aEyAH+LNxfOkoWjxNkRep1fD+vguZ/01d0Ib47CVk0D9TBRtRATWhUDoRi1MjAsOzn0Y2XH0iePmXrHeIez5mXhq4NEUyHWDAYrrWSB+nfm93UCJ0TK1QGSHT8pB6KhycmNRFZ/gm3zKkQEdb1x96eQYAd4HpoF/70C+983ia3NJuVzkJwY/Uv6mxRj8TydkUhKGQ4
*/