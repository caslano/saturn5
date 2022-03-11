/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    compose.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_COMPOSE_H
#define BOOST_HOF_GUARD_FUNCTION_COMPOSE_H

/// compose
/// =======
/// 
/// Description
/// -----------
/// 
/// The `compose` function adaptor provides function composition. It produces
/// a function object that composes a set of functions, ie the output of one
/// function becomes the input of the second function. So, `compose(f, g)(0)`
/// is equivalent to `f(g(0))`.
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class... Fs>
///     constexpr compose_adaptor<Fs...> compose(Fs... fs);
/// 
/// Semantics
/// ---------
/// 
///     assert(compose(f, g)(xs...) == f(g(xs...)));
/// 
/// Requirements
/// ------------
/// 
/// Fs must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct increment
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x + 1;
///         }
///     };
/// 
///     struct decrement
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x - 1;
///         }
///     };
/// 
///     int main() {
///         int r = compose(increment(), decrement(), increment())(3);
///         assert(r == 4);
///     }
/// 
/// References
/// ----------
/// 
/// * [Function composition](https://en.wikipedia.org/wiki/Function_composition)
/// 
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/join.hpp>
#include <tuple>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/result_type.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

template<class F1, class F2>
struct compose_kernel : detail::compressed_pair<F1, F2>, compose_function_result_type<F1, F2>
{
    typedef detail::compressed_pair<F1, F2> base_type;

    BOOST_HOF_INHERIT_CONSTRUCTOR(compose_kernel, base_type)

    BOOST_HOF_RETURNS_CLASS(compose_kernel);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const F1&, result_of<const F2&, id_<Ts>...>) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const F1&)(BOOST_HOF_CONST_THIS->first(xs...))(
            BOOST_HOF_MANGLE_CAST(const F2&)(BOOST_HOF_CONST_THIS->second(xs...))(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
    );
};
}

template<class F, class... Fs>
struct compose_adaptor 
: detail::compose_kernel<detail::callable_base<F>, BOOST_HOF_JOIN(compose_adaptor, detail::callable_base<Fs>...)>
{
    typedef compose_adaptor fit_rewritable_tag;
    typedef BOOST_HOF_JOIN(compose_adaptor, detail::callable_base<Fs>...) tail;
    typedef detail::compose_kernel<detail::callable_base<F>, tail> base_type;

    BOOST_HOF_INHERIT_DEFAULT(compose_adaptor, base_type)

    template<class X, class... Xs, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(detail::callable_base<F>, X), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(tail, Xs...)
    >
    constexpr compose_adaptor(X&& f1, Xs&& ... fs)
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base_type, X&&, tail) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(tail, Xs&&...))
    : base_type(BOOST_HOF_FORWARD(X)(f1), tail(BOOST_HOF_FORWARD(Xs)(fs)...))
    {}

    template<class X,
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(detail::callable_base<F>, X)
    >
    constexpr compose_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(base_type, X&&)
    : base_type(BOOST_HOF_FORWARD(X)(f1))
    {}
};

template<class F>
struct compose_adaptor<F> : detail::callable_base<F>
{
    typedef compose_adaptor fit_rewritable_tag;

    BOOST_HOF_INHERIT_DEFAULT(compose_adaptor, detail::callable_base<F>)

    template<class X, BOOST_HOF_ENABLE_IF_CONVERTIBLE(X, detail::callable_base<F>)>
    constexpr compose_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(detail::callable_base<F>, X&&)
    : detail::callable_base<F>(BOOST_HOF_FORWARD(X)(f1))
    {}

};

template<class F1, class F2>
struct compose_adaptor<F1, F2>
: detail::compose_kernel<detail::callable_base<F1>, detail::callable_base<F2>>
{
    typedef compose_adaptor fit_rewritable_tag;
    typedef detail::compose_kernel<detail::callable_base<F1>, detail::callable_base<F2>> base_type;

    BOOST_HOF_INHERIT_CONSTRUCTOR(compose_adaptor, base_type)
};

BOOST_HOF_DECLARE_STATIC_VAR(compose, detail::make<compose_adaptor>);

}} // namespace boost::hof

#endif

/* compose.hpp
5Biu0d26ZN7HfQlfHWjUVXjcZ7xLfa1PWrXASts5p6aIBsBmz194bvSZWp6Q0iPVcpfIVh9ECIkWHHu25bKT3V0npepua8DAnwNbODU+d760MuNqMTiLGkgQpGmr2fd/OsgaSfij1jE1cy7+4txxtxwXywq0yjZFPyQ1gudkrMeKAlNU3obvPxruk2YhOItpbt3Zg9fxa4LI8et9lJ/kUiBmzXWSJXHfMR8vx+/DMzatPC7/gH6V6FT28nMPtp09/ejPJBrb9C62DXwo76Siawx7nAKmt1A5ZwYhXYB30QmzXmzcDSo3twoP2/AXFpjr4q+R60ObdST5rl5T2A/+Bj9+13CGzE/4h95w4P7+6Q4TyFrEEP0RGNNRQusCWb+YCIhFoIZcyaoEAS9m6ucyAZbSMGYXy66ray4sv06geJaDCRkdmJn7RCdWCILjAfq4h8A4WIMeJkKsmDbUrtGaHx8jLaW8dEVM8kN0o4boFCAkez6DQ9dpByeT+4Bls7ji1YpIqWLzAN+dXdoo/6mFkNnpzgV1DZ4VtaoDXlCySr81kx0gYkM8e1t/2xQ2Ss+BMpebaAz045ng47uhTAByRCzQ8tYm0D6Mq/XHRjNejIgs4VbeyEX0/sJdAt1DhWntMIiUyzoyQ4AwQznwcxS3msApO15NbgjcHm6l2wVJ1sqRzmDdN1ITQ/AKDzrg78YpeYuIHR2QuRKQ5IbKvozMD3xjpRgvislyaQnSnnTY6mS8h8yxQn84jkRtVGC87fEmySbLMcM85Pcd6AvjqTsp9aXvTszLHNsavJkeCVpwdH5XnuQ+0zkMQq2A1DtZfTX679XVU4e8R/XZbu/8UrUO0dwEk2zr3MpmTxu4QF3SJhKZ8+wi2ccYhu/s/Axy9ju4eby4L+bepmW86lgaI+n6bGuBbGhOU11DrAUuFD/5iVKY0Uv5qUjLDKu8oIguNfG0mWOmSWnZcdj7BJP09w1Vesx9/afmGpvuwCx2BBk9pmaAcvnja0TolcCSkz912QzgiHD/TYZrImVEx1jdY01w9YXDiYsq4pfOiqUonI+8ajLutZiqUNOuDrnegSF9+ebd7dFSgUEIY2fuJf0ew6QPznqTXH3bktedxfFt9f0YD3qXxSh4x8eu9ta92xkOYm9/imW/9/ruTZjN7BNF3YRYteq3lGNOhJXwQAHp3bqjgJVCYcv474f89Nio99bGouTuFdguffBB1k6Q0gTO5plef/clRwSZUJWCWgwEpyZbm9gIJGxciFUWkB/pCnJiwGh6BcV/gOga90jyBrB4EIcWxCuwLELbCKhnvXXjEDWvsSkKAErisqcWNjaOpvFuUbAAyKIeGIYvM7NLaj4pK14bU/d48GH/yoM4GgVRTQnV+AgsSD2yIWmc2WmD4J9c4MvJ7bkYeu6/vW9I8bCR8rlMvs+qgKkFBC+nYX0ZIzs2+v/DSlyo5Z8vlWRE0ngPyoXS3w7cbGeJFjjhbamIATZSezVWrGtO69k2MWcriNCTtaJeFvuX3doTvWRw2oPE65JKypaxkqDaRIwtXOm/GDdQhl+LiqsfPBxkOlNreqg3EHp3khkyFpN5jSFc1oJp0fgtlYMbLLotnYegg2NraPWEib8uDPnMeO/2VNV55M82DVPLUdbKBIgn87L85MFOIlK2LFkFh3s1D3qSyrDQ/deviBY1bTlCOorNlCmKPhGhB76j6RYfVRHJz4AurCjxDG4hC0Q/2s/oY7xsqeb/VNtqiH1IfU8AM/76UTwcrFJ3Xq7Royed8Q3wOuAGdML+Db5zNmeWCYmbynsbD5QxzDqd5NSTOwd/R1uixt6yjHt4X5gYnLarTOIIVnTZk+nTN4a1VYtAL+ZTfVnBtOAqse/QWenN/bCbYkJ8TWJ8DcAroDwA8VA6+/nj/tr4TlCOcF8b30mb6LI8xHN38XK6H9t07fowtx2TDPFqn3+h8/jpnhwYu9xPol2VGvKT5MO38m7yieFWodMyhfqva5VcxGQmON0LF45PZwMUmVkMYAGDjdbL/3A4jTWJoW04+t+eZDlhbwtoEx6WYFFoXc+YNwBKjGr76BWkxSman5Lz/e+5jGt1Vy8gLsaF6i1P5UdVm8Tr/Ao0z2X/TIbql1ek6WyLC9cYtJjPev44H2F4s2FzhyVxYalKjSN9kmE54Zh9AUyFM1cKOA3sxmVmaps9bqgW9tYjQQJjcxsI/GJerqqeaXfz8LSXT+HrA/KC1irchB0Vvhc+PcRAJTDGG3b2QieKo3eYmVC78kbd5bChyF076n7Bhk2aSI5TraWMTmTKtODRUu+XaIPIZBb+Oe5OB3OA/8BFTBmeVi6LlAGgYDqbwKg/943WL90nXW2o56vDxqbJ411s5XU35jya7ktsnlTQFLFTBONCobo3sBkJlAqmZdf3yJJ5l8rVa/rYDMF0CpyF03EZtcPykpAh1No5WdFL6io2XohTSIn177ENqAKDNreIFVDtscYSQPuWbIdEcfp1nCK9ROTJWUVZJVLgcNa3ScwxHsSq+8CF9SgMMf5bQOZ4+1O7SEGMcw/y3pvJXNs6D62mI1h8BuY/CFrmgnPIw3lTd22PWUsW9k7cGUcP81sutUQ/RlGBiRrKjhFkGJsbuL0kS8X6fgrTg5S+t7Cj3AzzZPGOBMz+lh0a5iwVXrl0t0Key+fHIIN/SMO+IXfjM1cvgKrP0N54e8oatWlW3XsxOOqlSMZz1ivivHosxePRvf7pOmX34ck1474rpTIZhzd3WQ2+Aq9mqKqI36Z2aKBGiwuuNpJfxdL3hcP+sdnam3TqfhU2z21kXL7xcXegatdHf7g5uLRZ7lBhOpJW5992o3lcuPTDLQDE/mCbg1SNlylnySpvlMPbdE5oSpDevgA9Jguk1hP5N77WynqVMGfoPiRYjmh1NmfE0m9iRbYY7vVeZWbf8glIkiEHWlr0miwcpkZXK4vu3uKzI9aHR6Bfn2dNLygJHNbLPKWiEOUnZh2A2yLT4qlrMMD0xo+LHOmsy9xrykbqbw1e0GjUiIi+GyUtblSwFLY7OVBD6WCMa3kh1jwMgyhjohYV/yy2zi2+Ccbj8pHjtLTZx27loSJ4PULN/W3OnFJhRDJ0WyOq01lBsq/BB9VywMlxws4tWtfRLxJAAfkLbYa9h59k457ffATvLpgPsOuZRaPjjPV8yp4oEtCaClhcV2PG3BSFGldJGzUBxVZpNHwrjI6mXyUE5CnX2aleA1MMg5UpEJodExEilaWAFcrfuVWW5Igtq0+WkwYHfjMHJFnVz+T8bCngkAoluqp1fSaqeXEN9FAbeo1CZsNTARBQfQuba/39nrueZqtrzOKK8PXJESxx+Xqc9CDHbofCGhVTBWSI+ZcgEK5V0bymaHIDGcz3FDQr0CFV03hDeqYItRBviueBnXCzutDiVGP97hs45dbXck0CNT/fCKV9L5F3EsbHeOsagtMMq1sh/WHdBEHa7Gb9dm/OVyWtBLkbY9mwl9fFU4P2gUrI5pq5RLeg4rySEfKEkIhx1rWk6YW4OKuq4v/eu+P0CFa71LM6f6C2uPHXDFHds/gtbmoMdabfUtNaQ+yyUtwGzauUgS+fLY9arxsBiAkzCJs9WZV7dAfeeNBY3NSdevZhXGweQIjsXpL0I2b8lhovm94AK8UIpqQbGcjIb9lEb+S6HSEUn3JRG6+cL6Og7HmEeCH543t/zlCL0ldilU0bojZDvGSV1ZdkbD07K1qEMbFZwbTPGdUKnMfF9L+87AEVj2YKWlnbDWPBEnbtg39fOnvNBWPIg1fuVr3/XkaWCTYqYxeg9C74rz3Ih2S4QSjLvz79YtYXm7B7cCvFVMijDv55q8u2IREZ6II1igL9Et33mMcRH13hhtBJccMN2UQctuiQ33BsAVAz7DTMgdkxdlh6Nnvf8yuzDZJ2BCZDw5hk9jctGGbZxGdh6UU4mqqegZmfFupqcIdM47Yyd8kID1cC7iGK8lRlMjQ5MXv+RiDDirXuiem9RUWccexPNL9IsLOOFS49Uim3LZiYBzn/m9PS1llHYUnoOpCLu+srkshNVCHHf5/9G5t3ijZ1bkwaLK8enkLT3kyivPNiG668WOcVyJujPo1REENgbngmkc4r3D08bEMNenLRYOCaw7OvluruqQ1bHTmrFnhsfwRrSImIFQVp0oBaPhQEGaYVlVmDvQWmUFPzP46YlKglZFaTUmjDxGjvvBOJwdnaTrTCg44NpgmDOrE6n/BkIZ3CgBzHv92lX2pp+wJULcgZ0wDoW1RAvmZli0oHVKIwASHCnyGFM/rbYGkGneF39dZsiAD0KO4SYtE9MjGDdvTILxvAKKKJDZWZFanlUC4plz25K9RZQ82fsg24zkfHWGq5gajpV1mZSjcJ+yV5KsXLTDQzaWNpl5bGVbw6zzOsz4hrEJuCWWri7sJ7gHv2OjT+WdA1ArzQfOktJKVypHRv8ShwhpURAs5A4rwQLWOl2Bzf0bRxoq2rWKCCTB2G4xs8GBO0F+pa1XvS9qibhNl3ocEkn/MuiCQUvab118sRzwzP68vsEDSjuDMTy9KXe3lZbjfB8prkpUKYsXYVu2x8TVphBZyIzaR1Gqq3R34DQwXKdRR927AO7HnAMft19UWf5bMhhiA6dZx1sFbqP+DNir4Fvg8b4vWkvjGTjZgLhYNUTphqt/tPsUOdBktgZEDyiM/15g6WO/0+kcXcELTUKpieLzooH3nnmB31UF8aAK71ixiefaoOMvh3WDZlk6Rbvhe2IJ+nF5Uq3THh0LmZqHpSQMt7D3P9gjghauSlHosc2fbTlDZ+AzYraWqgWszWzOxjFn5evc/8UT8IT7pc2AkeABYCepBUtjk963mUxiuOCIHg+jZzzXrRkH1IPr89Zq1C8FMI9JlxHA1pyJJHRVz2Fx1BIcIziO6W3Q+f0pVBC5UXAwCczKgwa5nYMC2z2E3fGph/dWJXikHpsEgmNlHJDYJ3kK/1RtP/SU/VM+9PynXNIA5YQPoCj5ryy28Glx4mk8UVeIjWhfgPrlon3kijsmEN5SCisuxWL8x2YOm4MrKOC7Z0tx6yjOvkxFvAx6H0NfHHNGVM10gP5wcWIgl4tGNpuk57pZgETPpiIH58oQwsj4hXL3Uzn4NtVobXT99gGLksLY+2Y0RGomgm43PoOSwWx6/dp5y9RroDt6H93PZITlZ+L6ND8al8i7HCdsQWelMVeIaoNlEimTRE72iHg1cTcOUtsVqIcev6YhqyrqWJ6V7xG9I5QwnAFrs+u5p7DVex0/sQC47nKNRI5kWVny+rMek8jCAAq/6M0NKOhkkWjg3p8kOBAe9BhEXVTOf0x8HtTqPnypPNTuzTfEjc76krV/57c81FzqliOX1GeCBgamO1Bu6hXkme8oO7dDXIyxR/g4oncYA0wHlnC9cRWBu6Y3soQuwYLEN4cXC/1ITZ7Wa33onXrNd5vbcZOEdlOAladHXjXe74bVsOe8cxDqotDywNT2ik+1WaQh2zETNNAWqqlv6D4hhfdBgOlEaGPWMis/aho94InTigV1Ap7DeObADUEOuIo9KI9y6w/5umyNDxzMkTzvL+OnGhzU5Nl8zFRsFkI00+cO+POk9ozMyI0vTNzrIS7WaCf6E8HB2NiUJDKeexkdSyIEPX3opEBWo93v7FshgcuNS4TP7t7uOBaiJhC22+AE4755ugj0S04BBL9V6PwJy99bi7Md2mgt1gRYwtCvEjAL/q4VOlqMThYVDUQKONvosmF7BHZPMyy/HEWKKosdX2zMMvG+5g6kSsUXyZLgdj5LZMWdHINw2KkgwFg6f8x4SEQ+c1Z/uItbN2uuc1TB88ko0Ao7mTqV6ZrmyymxpWPRg/bDICYFUcTO5SyY+cYIBJ8FsOxcSaEPFBVL/E5U2QNeCcpUKsGbplPrpNEoCDqkcfVS/npHDDKUqaJWavHFSBa3AT+4i73/fbaa2kERW2mtZCWjQic9QE9RqDJbq0lKuT98i6BgFbQfTx0qouO6Y57ivcD5Cz1Nhd4MrI502/gMQ4NBUZ3JdZj2BLdkmsrsNaZqANv7PT0BpmrhU/eKxG0BonYUJQGATUcCGXz33rAygLAtx6fb8W9qq0uAAY4wN9xKCfoDfoMT/cAONKO2AF/9IlLXTQPwP5wBnj2ioNT486qEPaJ5ygsC0IIGys5Q+QQ8FKel+0vRh6ZBli8vFlOSoov69eeaYPfQCLYIhGrAb9eM3/EM+bvsVexsEx6x4uuKKtA4EP1T6WBqeJLEl3dt9qTUJlueNQqJdFtHGvIxPkbeoPbHMuMue6eZOFXeFmlACDHUybPfscCIHwPv4f+7PgEgrsbbJk40e1Bd0WxXEngwVU2zBV13LO3UHi1nLd8ztrZkUuHm6dfec54n8CWvv6jLvRsXkg5MLTuwD3WEtEur+4yYl5ZNakj/OrWcjzDbq6SnojeaWtSq4cgq80sELxhgWBysAusYQlx/EWy1ASmvY+BXm/M3Ouag5IzVRVAg21EGUeR2IfCXfVqoQ1VJHC5WbpC05eIfx5smZ5X6dSCZve0NWvBYIPk9ao9bUSn8Q17/ZrWagIfikm4+4tSEz1pE+5M70NH0P+rDcC28n56YCgMSo0wmv5RYLDn/GKAsV9moGqUG3BhXNM3UYIL+sXp74hiPKS7a5jCmOlrPJz2Wd99tFtdW10aLAL5PGfW2d5eZ9hZWiwq6rWa2r481w9DQQWJl9WfZAO9SskDlMUnCaxhVkGd2zj/XAoZkUGwWd8EbtepzFLuYo2uteLJjTreVQ2DVToLCUyppgqSlso3p1KosoBBBzqDcrw3nKelHH1fKHDUAuRe5Nv2feL1IiJrZn0aBA3ge3yplaqzH18gn4uWammQ5jX+GIk4pReMxCQQmjzP7RX7VXvvUj3KaUmwoc/nPCFl6YG4ghmDmvYFTKDj1V+roowF4SUnzuYLTdfhl/xA56wKzK7/wRQa9iHQ+m7QtEkXKFniyn18shcCHkjB9shkHrRghVFUzRitxOdj2Pxo8GNcXUVlWHyHJz4rQNgQgt86WUZNcvV8W89Wb0K8Nm2kQcytifqAjkEN9PS30ZM0qWa59NowO2MAJ4agPY3WDVOcmamVlnt5ieTLsO6UUHl5m9/5jaKVUEZG2hfeb1puvyefekkwz65Znf5omMiKe9kNIsjcaHgVKmbS1Q2HIi8W7Bc29I/VRBDKW67xUNxrHarNyyjuK6np618PS8/1qG14xc4iviOC0zhtK2cnKQhjbOd8s84W1bSUvUvRP2omk8ywMS1FgeKdI9vV7K9k4RXOEJsiSUHYuLGIFLgPnBjBOPXZKYxUn8P8df2RY1YBdMw8J30nVbQS5CbVXrMOZlhEePecpOiRpmrsFjQon+UHLtmlqrUnmyrVjWYp5ZccAspLUwIAFpHm2heb8oJX06g1ZptbvRlOFqr1e1Ygmi3BvOVX2GR/WPmUsx3f0l2bANAwmWWKTlFPg4SuzDGRJ+9FZ7b7R+OsEYxoJKncJt+KDGx5uzIDocOlOEh0BYGCW+E2Y89Zpiwxejg1gJDqfL5ClYukM8SJ+GQp4EPz/3XeUsz0H59UDMLMZc/d3w9EJfkwKhVd0DOmure6+B4XaqwwgAJCNhJVPW90eXbXcZ7kR339BnpoE2Uz6plj1iCsUkpGs6yHUsOEp5S0VOpzPfDK1kIl8sXP+0BGPHy6uuU3ek3BXfQSF6wirDB5VFhGfzVZ+nK0fAyzEhTUP6oFtRGP+/ZjFoSh/lCIxZe74v6xEC+/i/UfpOOjtjV8rWMHpc0n8NJjDQ+mdTnajuTwsWkgX3AYH9PRbKwqvq0DkAKyja/I0R4mXPV6F+j7Z/MnG1F3QjoD2n9W/mueqWxlvPV2uIO5NMDkSLZG6iXCMEthwY6IGPggDk94Xp1yktgICeyHhNIrt5qFK7103uaDSG6Ov1k3NsiI/KW3zgu343hiRQtOQvE9MfU9W1box20kcOEriXGQMMrb/Axp+J31j96WkDqeAB0pDl9u1TjC5VkfQkLc3+/D+PkGc2Q9wTRZHWeSq6z3DBXUsqWr7YMX+3QQ784F9knMztYmCUzU90QgYNAgaaJemMQPQ4IVk+yFeVFU142gwZ5tG63tlZBAaH4CMOycVkbI/39mMh0FxjiAS//R7k7nQHFPh5yD7VFCB6887hLDfxKZuAdo4vQNmNVNhkIMNR30+FTSYyIMCK5lsiwJ7R4naho+UmFmXc0w+0EljdRNTpGcFYzgOAPlHB8rmkJjnfcN80C9DrZIgg3bJuRcvKvqqiqszmMfLwU2KLmNHsV+jNIpgcm60XQI3lLb9INCzYukmMOVeX3EggRAQC3LoN62ZUPsuHi8B1mef1PgEAAe1CeT+xbcXmRE/a61GjujV5cEoy6zxhdrcmRlZujpRDoB0pQumcJRm50aSb5h7wgsgBO+qUi7S0ze7pjr/vbDfTH973LA6s4G4d7AF7QaI+nlo4C2NAzUJ2T1F5L1g1U1pd15vRdWpmyVRmt0qzpd876/YiRH5EzyH2Hvlt8eige8v2JdCONucESaGBJi5Xacxm3TC+2wzgCecHIesAp7Id6maPyp2aT1BHTkYqhaKqsyKrJUmX6ymWHWnutYqCVXCTNQ0eHxADF1ppF5lRm4hwvn2MUOuIiJOUCHfDvJm/plWtCmmeVl+zzhttMMCV07uw6HB7F9gbzK/gDpkI+IglPXRgQCs3YqDButVd3CRU3udblWBp0UQf7Tv2f/SA/qqyGOi1MjHjhiaMPiTaBXvfErFuA63J8ioDYr1YcsuhGzWGAJpzSXhmBil0ARF/hZG/0zkXsNU0SBKvDWD++KRPhAeVSp4N/skPdmcAky7lKVI5z7X8iQSr3+/UnKqlnXAhE8tihNVWynjeShMD92ecMqVEZIhCfMHwAKWAh/S9KAbsg0EfeZ0Y1ahj+A3xpTffKx6nNcKPjwgxj0WgqEL4v7wwm2ktd81gnRZ8KQwjMPikM+3v3nLse8OmI/skgbi9DwGDIJHwIVM8595a10P1VKTCq/dSehSvbzTwgSzi1vPj5HwWfrwQHcWc8F8ky6IXkS310v7N7xmZeTNn+PCpnl92SV3F0UVBdbkhdTBs6Da+4SY9XJIPsFqFgljMJZnEpak8=
*/