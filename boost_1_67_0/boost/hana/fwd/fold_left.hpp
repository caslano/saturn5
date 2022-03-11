/*!
@file
Forward declares `boost::hana::fold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_LEFT_HPP
#define BOOST_HANA_FWD_FOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Left-fold of a structure using a binary operation and an optional
    //! initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! `fold_left` is a left-associative fold using a binary operation.
    //! Given a structure containing `x1, ..., xn`, a function `f` and
    //! an optional initial state, `fold_left` applies `f` as follows
    //! @code
    //!     f(... f(f(f(x1, x2), x3), x4) ..., xn) // without state
    //!     f(... f(f(f(f(state, x1), x2), x3), x4) ..., xn) // with state
    //! @endcode
    //!
    //! When the structure is empty, two things may arise. If an initial
    //! state was provided, it is returned as-is. Otherwise, if the no-state
    //! version of the function was used, an error is triggered. When the
    //! stucture contains a single element and the no-state version of the
    //! function was used, that single element is returned as is.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Foldable` `F` and an optional initial state of tag `S`,
    //! the signatures for `fold_left` are
    //! \f[
    //!     \mathtt{fold\_left} : F(T) \times S \times (S \times T \to S) \to S
    //! \f]
    //!
    //! for the variant with an initial state, and
    //! \f[
    //!     \mathtt{fold\_left} : F(T) \times (T \times T \to T) \to T
    //! \f]
    //!
    //! for the variant without an initial state.
    //!
    //! @param xs
    //! The structure to fold.
    //!
    //! @param state
    //! The initial value used for folding.
    //!
    //! @param f
    //! A binary function called as `f(state, x)`, where `state` is the
    //! result accumulated so far and `x` is an element in the structure.
    //! For left folds without an initial state, the function is called as
    //! `f(x1, x2)`, where `x1` and `x2` are elements of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fold_left = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct fold_left_impl : fold_left_impl<T, when<true>> { };

    struct fold_left_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr fold_left_t fold_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_LEFT_HPP

/* fold_left.hpp
tT4eE23B1COJRCd0kgzpjSUOVUlaKbl0XSB+CellocNuUmlu5fM6TFvvJY/XMBakvIxjeHJ7lH1DdMyO/UCzCo8lo48sgpU5PJGcw41kTz8/bYaAoQXq8wsJ8WwljaU+BmG0pbR1ejp97AcIgvlQM1w7NkwiIrSCkjU7cErymzU+axvXIzZXzIHtbePtbpHW2byWiufckiG1ikVSw6evQg+lI9Q1ZDoxl4lpbCR2GECWqapszUvx4XL8XGkX317qXxfgS7yVIqZn5tvU7Dr40TosDyhkMS/NNGh/V3ITo6rgu6dVmEZ4HxsGCB4P8RJyZT5ruET8mfQSWhywon23NxmmhymfwP1GDNe3KcPM29urCqEeRO74WCkKE1ngN1oMOZkWDH60Gqb6h4WFlAGI+D7H3AWViY8PLiL76fN67h4YNMeAG/hhACV7l/H79ADuE2mfzYAP1cNjzc+sk6vaI68Ed/NWnFMgy0kCmloFssNSC6AKYrpQf3leTXNPfGx5g3sDCJFQntNp0WXspVGR+mXio5nysEdebOiXQukoRdhbDU9lpQCRen9VD3neuK9Y/R+NWVaq9VeSY00yFFlAL2+UyVg2OVXsgr8I/EOm8rCjmM/vLm1bwu6vfeidh57FmgC8tsguHsT3jK6yIHxsYL3P5L50wwc7bW9turCcxy6du5iYWQp/lTwr7PNLNCy4bFsflBtgC8hCd+ZnxrgYGsMHCGZw+3uSPifdhqa/AeLg5kb/AQMexUnO6OFYta+nn+rQOFWvoq5jQO0Y3iSGu9iVMfpGx5gvBx9mfaaVlXvpVGc/k9HeCRrl/z4Jn3Wl9ZK9fU8tM6QLFP4ZrHVElf43IrYksS8iv+mxTN3aN1Lh60vydJcjYKrsEGi5A++wJ0yqOWj1IxybqBqf7V+zhcobePqoLqFGynj8EFsHtZvAOtHal6W4vekKRROIp8a7sZ12LhwzeymPV8tEPhvN7Ks4I6IExLBWepLwdlmjPfDktnIvkfN1Ael/eGvonTY4jH0AZryoqEzIvr0G6bHpcbtLMyWKA8kSti5LxOZ09OovjKFSagHQYz9nMytWVKaeNj6EsPen+lA0coKnCdZEUusPMCnp+eiEn86MnpI2VxNiPAbXSTclrn8VAWsLDdVddqKaGXfkfDJjWLltu4svNgW2NqBRIHSXdyJ8VURlqQ4dxO5r7B/qS7GIxpYFikwNXm4hsabuKaKER8cLIqO1ZF08DgMkh2wVXj/PpBCN2Qi+L+1R0ZxXvqE7E5ho+M3px4mBdP2iMkx1gLj8I/dPZk7j7ZFSTwdL37NvpEHNYrNI6qwz7rnkekJS6fugXSxgpktPyeRXqDyEBKzOCFMdbLcSl9sPdk1z44JRH/gXXslVjdLkXGW07xk9xRoNwa6QwW0imtw462z48sl9oBc5Ho3qHUO3W3ktnVJKu+z+aGnJEgzxhXxiagu9Cs2s/iale0GJ3UmBMOzFrLieMcjO7t1j//kh28qe8RyGweR/FQf+Mfiu1tiTE3j23X2EgZT0dlSpX2Ppfu8BPQ4HsKtBt7v2MZq8ZPPdVprC6nZnmakRI6CYo0YoMPYWKLuOR+rq4dIgJW97S+qgyszn+u//zFeXrpZpsg9NzrO/AGdXPCpntvQ5vBoWJFLU/G06d8A7Orx55rGTYnDB1l37Mnu/wwA5K8hNshXY5yZrS7iz64o1dhjaZap7hg91g2LsBc1sutSCS/wONWl28o5HG/RHz1P6YYZX1Eqwl5haWwT/+iXhqaY7QEg3ogfSJXFsEV1LvcmHUpd2VujGTmmoRyE7gFsSkvB4NVGy7YroFjyvZ2aBnut6v25AiyXsZEU1XWK4xdCl0AVPOE5bXU7XGwd3usgvVT00loxOdbSVO76NfUmL1htQPjLTosZhM7ZDgmJLR6QAIbUsQJcMhqHVI0QXqBp9RqvBNdAXo3UzqPtvgShCos/V0j6JKrLCLKnyExbrXrWdOWHD/HWmRQXWbn7dciJ6LrthGJxvDircvOkDFO0hZWQtAZJ7EXJX7SykC4Yc06I5Kc4eDOYzC9PW0Cdco5vVu0A0W3J4Oi6TkJ9bB4hxtQu10Q5gTPnHKKCed7/CbAIV/UHT+zMvhxlqJztwxyLTtC+i7yT5lO7Gdxo8wgqY6j4XmC3xtOatP5b2MumrkysOr0xwRi6eE646el//kvdqUrYzE+B45tzPwWK/cB6kbjjkZ1NhbLLvpk64Fxkdv+7UF36UvU3tchty7W+rlHNW33mdPWhPn3bczjL7MuBzB9sn5zYfYzqth8kmbCyLjyPeW5ApKvvmemf4L7OEQDFy4y3ARqs08X7cu6muAWeod1VqaS8s4XswpTb94Cek2w5j2V6DNNfBIaoZnvDGyehjhCEXmyBMfs13BLwKqV76nWu23wBCWfxo3IaOZJZ2BesTBJJD6+k2IEPzRMf+W/b8XwkaK8Xh0h128JiI9CbnYH/Bx4tAPbO2fv52oO2RSuiTv6jJQ17LjLeG39osiEJs1ZBc2VGSDemKTPVRpo7VUgHxfjvMAEAleWmSDSc3VM72ITi4hCFoMp8WDoAOwAM/QYXApaNw3Z6H1KKULlNS69P1rB7Eoumku9yBLf3H+ccOzjU0M0xn//6PLOwOiD62m3QEdgrG8F4Kz3NybefOw9j6Jihc7oGlEMX2jNSg9cy/C415KajeZ3nQerah1Z9WIjjOXsafH6Flp24cthP++ilJtSWOBVxXEF6lL12H/J4c4NgsgzH/P9IEmiLlBTGd2lVgKPmAe7Ggkf12L1smgbaMndv4mbvZu1Mpw2KT+mQeSQ788OKLtB+p3/UR07RgMFEN4rQVtWIFmU7wMEUeezEEfPRuK3twrgM9lPa9XJkLYNGAPPqWEzHwiXth7a6QAU3CnRddKhMSs1B93NB9ke/nSnISuW/pM9a9cWxktPS9027bagE0aRR+L26D4Dg5cI4vVjBRFZufNxe62BgtUkrKKnjCdXewU83IDhSi7jjU5uXMm/XExgm0HBCv06KWZneZvT8ggZgxrR8Q1KlmLfshnZQCIqxPJ3zN5Q8ezSzPXG+5k87LihLOtK65vh7HKT8rM4gY//7oHLvbqu5sartZign6Mb8mI2ZcqnY1n9A8ez1L9S99TmXIZGmE2LpYd/NNfs1xHig6j6L+I80JJZ2O1bwHFxzbKu7iSUdn69IbbiU8CcmLm/PeG+74hlgREfe0SmmPZh7A8cyYMlN4wI5elcpJGlxr81NObuuOc5bL3DfFXHOJ5y+8rH/y4ONtaScdnXpNA1PbJg7mFiiftQk15f2kzr8//buZ0QgQJkjfOq4FFTNAhEvfOU4EWNdHwNg5OqXld5UpD5xFpzb5qWZilnwBVB/FerimsFS5oJ3ba1tP4XbOT++twMf0LE2hbl7LraqRs3Y8NYqPrp7LE/gNmeNZEyG8kERKZSxWswxXJLH1dOy9JM1VJs6WhigRoXDzQlc4PADB2FJbyp/p36CvUaGrCn45a+On+b7/ZjVgEhaNIH12LrTs79WS243Lj2eCkMWhBFqFT+IJXYB1gGudL3bE+KeJ5KzbzbDli+hgnVGJ6144ANQbGE7626iwI0puO131uYJGeR6gr+uRK/hJiGR0wH6gok+XfcylhGB745xer0l39xR6+T7OB7MOJarhdsZEXjEwZ9JCs5X1EzJbwpQZzwtfWbMZ92DsztCRw3575M86mQsnIJ4Qb4HrHKcTOd8bmV1MWkBGgnub1DgvR8YffOGl1A7/46HLyAW3V+AqSVORhz+kpxKZ8yR2oZXGdX0xxIvxzgbkZlNzviXr1VN9fWF0F7ge7qSxCBQRIM2HHnFCpzTVFsQMqdleiEsD2p3tOZfgAUOZ6wnVdQWdoIj5RX+NqkADgV1dodDlMH/sypvAB6CaIhiIlMO9p3iG6lcqZhxy4JL2Te3dmOjeY4wK0U20CAsx/qwC0ALzM43vFKCvt5LDiLcO2b7pwCc6Jpilpw8LUf1Amhm1Wc1J7DTFsZTebLLeeNxwmvMRcmRnAwk3WqsPJ6HdEmKh1FRmjqPkOx7qnqJ0UdAhKQMaXnAqqHl4EfmhrhNJ0UVYl21xYsN0axTC1ACZUaQoLGcjplFOV9RvQnhULjefwMmXWmlAmffvVFMd4JreYKwqMNFUV8KVOEeglkw4f8IJ8gXIcQpyMQRDtx+P4qpG5ZqB2m0fQ5yW6FJ7VXjUE9DFq8KkWxknGoSW44hC3LKXVMUyQ67ai14hLWrFhsK7631jfNvnPAsoMS2ecVMaavkr3+R2Mb528YAS2n4y2kdfy4rdBZf8C5pK2MWzlipbwr0SIe4UkZjRFgeovhR1gJABhdyhKacRFpoCd5NH5TDhG/NdTPBeGITW3VlPZB67MXuEOxihHdW8M5TnqYjo5etW/TTUh4hmuFxhEHGjqnEejEiRCBCUJApvD2YB0auo9we3aK8F0FOPKJASe9/9Hb+UytRhYSiBPrj4qXk0usB+nJ5pzouJMlft6Bxjr9qpOc9Oehl5h4aEz963oBX0RjD/o3jxPC5MFqMuDgBoynfcRLUMmxfxHFDMkSta++oSUA+JGkvnQnKtVmmxm3kqFU2NuyfTx5C/Gy9K6uIJjFVomIaTQ22pT/wSdoPXXZdEH0qyTZRBf0QfOuN4W4Xl/iry8wLmErbLUnJN+bpWrDK0H6mWSLqGtjSap0yN1/4TacO43/rELJmFOph3u1JHCE4S4gE1NyYC3SfktjDTpAmSRtDAOBv7U+v4SBNiShKnPXuUmuHHxmFTN/+9Tw0WluIrBP5vvSqb76ZdteQd2xiji+qe/Q9BlQJKZqlrrW7WmUiDRZGfEW5GQmz4HCBA5LDMrXWAeTgooZxkFzRirYpFnMHMuETr43+nihb8r4ex2s+MTQ+pWp4Hb3mpzQeDk7RSn3HNGui4rO2RDXgSCk4himAFt+30c/JANFuwfAYYAj2u7aix6Rc01yJ0X2h71b7qcnVRrASG1dc4AmsLVPmeRXNNsd2byP29TZDgudBLFYQAXFESvXGmmAk6uNGsxWSaoXo/xOJRuATEoNvAdNWwVg4WDc3fYLYIJnlzb2HBCCUyZ+cIkp23Qose7Po6ra1Cb82JY5WN3lE8JiELpeXEhHJTCG8Tew8PtQmET6WNymNdD7P1aBqyz+twbZQx7OGoHi8zQadzwZKxpkS/puKP6h+xmygMgO44cSUil4dxdGfkl7omH6d8ylWHwcOXllaFPjvunt2pxK57NsXaTScyYZF3EDwo6WxNGgMOQCtp3cfjNvPjFOYBFfq7luPTDDroUvCH6pmRw+SzefURVp5c+iWqF2O3H/6sTWYVoaMqWW82ULlKeHP/CCfVxseMYQXnGhurbp4GsSDS9N0FvPGgjKGvXFAUL5Ts5wbSpTxuhn3UJCA01h56ll64FFM0uBZxNG5rXXtPyr9KBBVrmSNF5F7f1LpinPCQbHO3kfim0/3ZZ4KyKsl5mBcgoUHCWh0gnsKDZbEocAt6MeeegwSzHUshSKg87atoqEoBQ4fC+rRBd9cKB8qk9ouIEUCUzzlCEQF1dl8iOJn8l5GBzZwIubDHEh3wfUY4W+n4JxkfEGTMZ7Kei0qTurOAX4AonwsGD0DaBnoFSjSv4fVEbj7Z4aihy7PmsA/N4QjoFjNVIpezS0hadqVIh3TNQcM5j84Jse0tfxleBCilBTRQab1A1n+yONoyM0cbJCSAHQZ6/TMLfOmIVegG7KBxt1tCw18H/crGyGeXAnd+bPI6UaQxQQa5Vg0r4pBQ/G+pIl0Dgi5gI5asEER87t2g1J88x0frJa7mjK+VLj49GS8IOqOiuAFCKxm+kHRKRWoFH0DHM58ZRIa2GjJIU1gRafUYOf6Q2w+2h/eZg8pvgnox+Wea1ifXYqcFuUzGihtbccAsRf4jcX09H91/dLyxygU1zDpmt7WSIw8LuPqhnX7FKW6ERzeLZD1pAf/3bhyE52AJnKLR83402DP/McdPso62ctmLHRZbeI8DPC7gXsk+TjFfxkCo1K/UXVeSCvyaNVYyyFogjolBgBCK8fdnQ/CPOroUtbzAXf/tTvEooxmgcyyI3Win2V/5loH4JzZnU90pieHMAJmn83fB5Y1pih94cP4EBqg705QnzOogv0HMzJX9tqOdFuql+fI6ghkgNbLgqha0GzBPdOXnrGJK/U3NTXYNxN3S0fs39FthfrEyar2+AXbWEM1OfT7v2J16GtKq6zMkZ2JsEHTjrvgMetZPEEPO48VsXc4m8hIEao45UTSNTmxi0pQYlDjAZP0GnXpti4LHJKnjKtQrwPfEhHXDt2DaFRJcx6kvIwtHFYSxEBYscdb+/OxaT8klM03rynJCj945mH8Ts0TtEkrU0xyUBMJm3G9rj+WxF9SObZnNcOX6I6N0ZW8DQD34uIgmy4XFj2AZ3R+qkHi0/2Dyk9rXJli8jgyWJFRitwQlDRnCH+tsiGDcg7ONvUfNuiq1eMVK702T3zMmoiRRJwAALP/TuncqWNrbPDVTgsEiiFYV0mjjG/IRYnntfuJgjxVr7ZRMCwVrgJQjWtgvnbKoeCnkIwTGJk4lfAdCRepgWCsAKWHANwhXzstptyGZ8Sc/2EzUfr7ydkRpeLMV6VfWKUXp3YbhMT70ohS0ko91wfX1XtO67xd0TZX2H9o+x22pMgTXH8yhSLCMsVf5lJg1p6NqnIcTrtVI0cZf5u6sUpIl5MXg7b2oXgB1EhToluj9EoSWpG+fyf1+/BfsR2H0035CrKPOvDQzihH00Z/oJhU/3XEcP9VDqMdcMrwYlDDtWA+Fn1iIL9iRUZjxt2MhIoBj4gUFBQ0uof/SGLwDkZb25c66LuDzY2Cft/UOl6zYH6YaRxLadhI7QQh/CIb4o1HwqbbVoelnNhRXLTe/8vPpPxWCGdUBz5iEU4RD1kJxcQrTZxy6x7q7XgFKwXlbrDQrOmZMB8VM+kAjIB1b5QpE0P7jUuXdo7arUHXPHLAylHisS70jzv7kzIw7fBSkjofBqpXWColO0IhRKRvZ7HB8t3a7f23vWfs+bKyqurxWcZI7qpA1bvi333l6ECgZPbeprcu4AgK2RpNRfP8a5EK2B35Dt7YcMSosIY/85Acv/hjAuSTvDpugRtYtpjL/ehzTQJ7lcgxGhedDElBexjagC+D1j40j2Kmwarh71kB2abivCfLqj3tdqmk/yHcqW7qU/KLrW8KK2Ahe2a0K7gorUMJUs2MilddUTiK9huLDuw6t1Rug12Vhp06Z3j97HBNFtuHM02DrBX74Hnjj+LCA8xGhKX16k9YpKYdjYONZf/SEzblc54JDBMMEe2zklJSIervSBzWxWc19Z/jvsN5kU9/MsWtrX15aEKqXBorhYZVVfBvBiCDFMCdaz+WPR0WTmdmIcTaZ7LlDYipBbiOY+lWRxshK8QJ0dhT+mU/mo9yhR+V172KCcPg8rmTaEJXpiYThrBItS4NAyt0KsZJUHz0u6s5ZbC75wNxZdIaFn9ufP6WGkta9y/xWMlaAG9XQl215BESrmxruPc7NIURV/WkAYCLnKdib/8zLR5CF4btq+KTN8uFVW/RYkwNY9/L93cdpeMsgZ8SrbSakHHsQkHzR6rYgwRG8YVxfnhEUBGmGJKK+U4P/LMYSLgmUpULlHh1qkuPyA3SIbkSMipI2ybjjky5QvcTQc7zv2Imspv7REEVGD4XV368dTOLeavA9pqBTTI2rgs5XP5UWIDPpSh77VztG4G8OnZEzG/Hkd8JndMET8M6BYLG0o1YEnYeXUPFHmxd6+jIqVyw1gSXYZzI/uwZip4CROJyBVc7egPVD2Dey6SZI8QADBrFMtUYnRXA3rV4vqfT9D2zwOj4G0uidJrZuXxqiWj3jtqvhiwCFU2MFTKUxAbFaOJnCT3BjpifMYGgz9DIS0sSPqN+hagwpy9J2tIYWPo3bmP6/NSoxTJR92WsIl80J5XM7s6dJxLB70YZAgQxUuHjyyIuRJFZtGToLsjo0adkFUoN5gkZ6hNWz9Qdh8DIsUtn+LNj9hTiuFvV6NpIUBBoKlUsDNKFGc1uLnhA2D3SdYn1KItSuxkdY/rjGrkZSfbNkI44c2/MgkXYe2NBNTJjU5Z+B9zsbffcnVbnpcq16AsHWe8PYWXVquMIwOx90w6NHTvrc1grfLSFw49HKWd2/fWA/gA4hw+a7FM3+M7MbHB5rV3vlxHoa11JU97kpI09YyeK5by4SedWAN8ngYifPBYtmS8BD+xLZ6xggwPI1gHlSrldXQTQQofhZza8SPnp+m/n3/unGgp83Xj3XLZJ5K9Gv7ctN31HR76Yz27W1hUFVfJ7canQdd+kF6UfTs3mNfD2lNsa8prBvihy8MErgPvVvVsP4qpXc9bJNHHQecukagrFCl7HPzztM7sY/njyZMB3J/rQxyvhm/8yWpNA4/x5LXAvOn8IUi96WCMxB+8bD06dMRj8oDpE1fDdJFQs9C6gNJiwXMvt+A7/i+UL+myi4+uNVKUzXp0QedfhWybbJ1brp6hBVD/Xwnk0iN/FJcvNj07fmHQl6nELmC0Gc6rjGa4edi21xlq50VSz9sAXCdjgGevKYbprpU0QilueLh/ND97vf46vQt+58k8RzWimK7ia1KY3onuoHpmla74bxa2WXMiUD8Cu80M7d6z4FKh/tsQ9HzCt46z2XPV5uUidA+kSf0Lio5VyD23cxvTn/sNn9Nxl6qvXK0d+jJ90n5BhG60wo60PP1BxVWV7DCKpYQzvMpf3qU2/ObwRHcx1cWyg0eZ8Jvr0Aj7AABnnMRI+ttYCPg2bMlesUI3cUD9zVDx+nbHftOmes2SdHvOVWPfhscCq7sCH/kuvKwJZHKVlHdyyxgO+0Djix0M7UTqvEgu2zV42CdUcwhaxO1Sy6NBYzwJT6xwH6g9wuXtqbSYEyrOetDfyYUgga9UmI33nnZGtM9sA/HouZvMamavejuaO03Liv+/iDvVev3SoZQ/JHL06X8C1ejBc6am9xmxekhakpeioQfBjJfFognrOnvpz8VRV+x0RALfqbVDNtLjQDQWPTDzN3c0w6QI1D8qTV8E9QgKBH75UGHrc+6zAWNyBJxN57T2mBVfaAW4CPRs7Xrgc=
*/