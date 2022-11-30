/*!
@file
Forward declares `boost::hana::Group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_GROUP_HPP
#define BOOST_HANA_FWD_CONCEPT_GROUP_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    //! @ingroup group-concepts
    //! @defgroup group-Group Group
    //! The `Group` concept represents `Monoid`s where all objects have
    //! an inverse w.r.t. the `Monoid`'s binary operation.
    //!
    //! A [Group][1] is an algebraic structure built on top of a `Monoid`
    //! which adds the ability to invert the action of the `Monoid`'s binary
    //! operation on any element of the set. Specifically, a `Group` is a
    //! `Monoid` `(S, +)` such that every element `s` in `S` has an inverse
    //! (say `s'`) which is such that
    //! @code
    //!     s + s' == s' + s == identity of the Monoid
    //! @endcode
    //!
    //! There are many examples of `Group`s, one of which would be the
    //! additive `Monoid` on integers, where the inverse of any integer
    //! `n` is the integer `-n`. The method names used here refer to
    //! exactly this model.
    //!
    //!
    //! Minimal complete definitions
    //! ----------------------------
    //! 1. `minus`\n
    //! When `minus` is specified, the `negate` method is defaulted by setting
    //! @code
    //!     negate(x) = minus(zero<G>(), x)
    //! @endcode
    //!
    //! 2. `negate`\n
    //! When `negate` is specified, the `minus` method is defaulted by setting
    //! @code
    //!     minus(x, y) = plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x` of a `Group` `G`, the following laws must be
    //! satisfied:
    //! @code
    //!     plus(x, negate(x)) == zero<G>() // right inverse
    //!     plus(negate(x), x) == zero<G>() // left inverse
    //! @endcode
    //!
    //!
    //! Refined concept
    //! ---------------
    //! `Monoid`
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Free model for non-boolean arithmetic data types
    //! ------------------------------------------------
    //! A data type `T` is arithmetic if `std::is_arithmetic<T>::%value` is
    //! true. For a non-boolean arithmetic data type `T`, a model of `Group`
    //! is automatically defined by setting
    //! @code
    //!     minus(x, y) = (x - y)
    //!     negate(x) = -x
    //! @endcode
    //!
    //! @note
    //! The rationale for not providing a Group model for `bool` is the same
    //! as for not providing a `Monoid` model.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Group`s. A function `f : A -> B` is said to
    //! be a [Group morphism][2] if it preserves the group structure between
    //! `A` and `B`. Rigorously, for all objects `x, y` of data type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //! @endcode
    //! Because of the `Group` structure, it is easy to prove that the
    //! following will then also be satisfied:
    //! @code
    //!     f(negate(x)) == negate(f(x))
    //!     f(zero<A>()) == zero<B>()
    //! @endcode
    //! Functions with these properties interact nicely with `Group`s, which
    //! is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Group_(mathematics)
    //! [2]: http://en.wikipedia.org/wiki/Group_homomorphism
    template <typename G>
    struct Group;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_GROUP_HPP

/* group.hpp
UVWaze2FZbzM4twPl2phhsIS3yqaOJMQ2r/EGIHlHu1bi1AIYid6d7JMGXGzNn1XwnjYZUnjD8MxE9r8PeM3cfTDtYG3CS9ov+xLLN5X4dJJSnhxPKotq5RTqJCImW5cwaJfQK+pH8h5+Cos2f4CVSLalVQSfFH3iVXM+EIC33MVzr8nrz0P39NLau70EUoEcTWX9zxFV82t+CNO85Ci9R5tzVr6GnnwWUqUtYZSEMC9ka3PGpsR2g9K6byObGsZ357oGM+/h1h9Hr9ax2hthWOJ3btfoDS3/oXfowSXe5uxu8CFtuoII69gmI91Qlic8arJimftImsQ2A7XkVfovdx07tH2FfIH8+T2+lwfU3sy8ZI013XEtS+yNWiURfejUh5E6/ShwmVm6SVi/b8z2kWYsk0AgENLnX0NXFTnlTczc4ErTLijmShJqCGtbW2wGxPcRhhjQJwBxYEZxpkxVcB2LUusTY3M+NEIgpdRHp5cYzfRJLtp2m7T9+1uuzVtWsiXykAKaqxR4yYm2q2JNr1maEoMi4Oi855znjt8qO323eTHeO9zn+/Pc85zzv94gnp+sjKws1dILT3YYB8wpMvFrVKyBWQv+cIEvHsfutpEWWVTff4pX5CFH2OElc6ew4L095zGitiJKtR3paE4s9lbr7+AbXVTV1rxiw2+vOL+KjLKO7FpdQX+ZiUygMqWnc6tUMPvTsjofbRv0DZCOd76EcrLNJYXIgDVcfr6SoXTuO+FhHWOQ0okivtHZwT9zimd7q2WqCfIqtv0eydkv5XK3bWZIlHcvKNVQf0/HhwfqRoiBfV/c6HQ80CQuVv179EzYmTVwfSp5Img3k4dK70iN2OOXcE6xwUgmaQizRpBCa6pMlf/x2QqCVKFD8em8ZP6zVAdHsyFsLzgDHRjwZxtQf1PVD5Eg33y+3Rp35aitO6iFvXwA988uN5RKSnbW01CbxyGIs1xcjPamaaN2Zl++1bBl0EmbU+hUjUNl+bfWVWPB7pH74OeZERccOdOYyo+QorbbZp1uSa1w2hYFiZ7Ar8ifsdqa1DXlo0PnY32NJ3h1qAewdZUP6Z0HuUq5XvkrQ+CzKZ/y4ktnxC4E70pqKW5sp6CshD6AnXQu0eQe9rJPz3fBfP9FY8TZzcM5y8tozPk2yXjR2e/Baea7q2307L6wGCkxMd/hY8tjTrmEn7wFZSywnzrD1e8dIamnnMgXPJyJoW6L4TnsumwhobqHP6PG2bh5Xt9GWX5+GiW2NpKoYbucJ8OfcZV5wh/vO7E6NZI/X5xmsFz+8/BVOpeML6rpmBlnb/y1NdTzn8/Ief/Jl3jc0qnv5u522DSdlmOserWyHFlxy/gU/5BHJiFh2zQBWsm5PoaXmxpy2iRtFHGp4PjM34WMyaPEfDGKkjj4RwhRmtzbIEgo0/s1+hMQp8yIeev05XZ88n6RiZk6zTjkLh/CRV+ARgrcjMROajsQE/k+Qe1hUewpt3FE9pPNV05rqb3TsjyAs7oyCqjps9fHVfTHBtsOvRJf3hCnmgWpDlfT9bx/cD4DH9Ia8Z9HOp4FOu41qjjZ406voF1nD4hPzQe1DTPuDrumJBlBXpao4qgcZsSuYpaYnux92WYcDjBdy2FF4u/DYa/p2h81jdj1u4nvfVPU75fmZDvUIqwkwo/5pgaXs41Wq3OnR5arV79VhT7HhArle1oFQqdEfIL6n8yz3/a4j/HJnOxnN1PszZcX+JVf3iY1hTGx/dEGtfIWUmnH/olfLSYGa8HEflKeQx9w3KaDVwLiXgwxtUvQLyQEe8tjHcb2Ym34nyFbLqKGT4beXjJQ9ljiGimtJ6GNV3glhVt+WViIBQgOuHbVT2Mlt6w2JMaKq/ZDVHSKP/LWkkjzlsPPLDSseihvEPFo0zw9fhfbmveYlt+l2OxvcGiFZsm4n3RZVsWkdxBxPvKP+U4tCGjlk2t0UpMy9FXrKPS3mC1HKOgYgyqZdMFi2zgpQJ1+vkA37BKf43ck+YC5f51l8Ew5pJcqJRgl2tu6J8zW0CqNqxCiPAgf4OFR/Qn4oYICtUMMtD64BQ6y9tE1lVhWn1WMQMC+rQAGVLj+NN2id5qfmomqXKfheRRMq+UxMjr37mIY057+t/RvoJ4N7f5+pxWPCL0PLq3tQrXDqTf3oZrnQ/zF4lueFTqK5HRNreOB1bVOQJ14XQIQDPb5qZASkhSy62ml3KJInF9dR2+mrl/RHNb0f+WSSi53PewcbFgTeFx9miuEkF4tL4SklzVAS1Rx0rNdbxiaZ2lYmUdU5RO12JicCSls6KCueN1kYMowY2XEX1UsQTfU18WbwdXl3k9eC/ywzugFPJszUqtEGsl0K9IH0SbbuH+wSqIxiqt+qN3GPI1yNsZh25aXebx6t8YTUvIV6xUbm5a4U4aPvsHWLUetr0s8Ef6H/7Wuq/VMXR8LG7T6st+CcTlvz5iON6lru5BLLCSGSGZl8zkMitfoXS46pWOwEN5R9VuM/PZuCvEmxBrloaC9Ix/cOWaochDAxzsSi1oAmYid6moOhGe2JnhlXwH0m2WilAQKPUTnzOn8N34sVealiLIVR7VPCZM5Bf+ftttRcDKDuehHNFa5UW3nyNBvKt/Yg3uKkwkwkpkIzyIT8+8tlKs3M7LrX0l2SiIHoqaQ3eiD9Os2hoIikNHGDwCvKH4nN4wgo2Cnk0GoTPxv6CfI5jhdP5CK7mv9ej1M5FocHloSmTjyCqdAU/eMYMn7nTV/WWGOInfj+46cwVT/BLtjC7b/44rvvtGXLHSWbkSKO9cKMmjFyThta7jhc9cf6Fs8MM8BdlhmAhCPz+cIbDuKYM2rC8CiuMO+l2DWd4IzHJE3LVbKmOS0rFpteAVCryST3kSpnFrFzAI2tIpkrLnHaUjfvH3tyfUP05X+9Zb3uEv/4A205xCbWmhuU7Z951EXfSPsrI/kXmZNSEY1+1KxwKL0vEdM7nHgQfhJwd+YpnwyVQHT0DcKh1TMrsdxXLDvahgVLWK13hE3mpPevSyhfllVrNU6fSuRK59z1uWo5Z4r6vG5PDK66xJ/A4DTAi3N2C66W4aFqS02tjisplrGe5vPyKKXo6caprBK5ZY3nQMNyg4n6e12SyupaWO4XWD0PvlRRRny2m+7Vlx+9tXJNGyda0S8I2wVwTqDYaZV3iIH84G9hfYYIMDrvDwQD2E42vFzD4X7ecI/VCxRHDE2Z+/KpZE0hFd7dhoLa81EPMm8KcBMZlRAqf2Si9/EZ4//fH1wptReZCnfiNuKX/OvZE/CsIbgTPrU6W1lMSjCNYG3NgqR09oEvDrtQIZg058oGkOPYASJeT+vEGDRevEoN2PobwSgvCT/jwGbdtJSdhz+En/LiV80kiIn/QmSohCGkxIDp++SQl/YhIJ8ZO+jBLiFo8J8ZPuFCUiB/N6EabFr/rdolAjLX7Vcyhts5EWP+mTKG2rUSh+0ofmY8I1RkL8pJ+FIPYcBvEd/ZRcP4qxds8yi4T9dD8+nySp7DkMZc/NxN8aO6vJHuff18ArrJd+jPC138yDTFD6AXPhBgOWjJ/Gd9IwIHRNlf4F0prB3YC5ZunL7hJKhX21NX95vyudxe/z6F++i6Y9342ZQUbf+kJS83Aq34Fh/JFlaq9V7bO+nC4m0Q3wbsbl97svTczvt5//X+Qn2lcxSzTRq3avqdJXzTfEB6GbuWuWRw8Reyj1uWYZmojXpK+Q8rsKipdyhlkA+eVdynb/QMQkbxn6Ex5DmUEe/TBevvMDIn1/TvS5NK6KAb0QCGu0U4CNIseAdXHNhG5nrtnMNYe51jDXWuYKMddG5tqMCOAuGJSlsKsw1wrmWkmw4KuYq56RxESwwWxbG/0+Rr8ogmauMuaay1zzboiPD6e8xMtWBviLP6Blvmmm/g/EXNkFgpB6SK7i3lm80uPhKkYxDAzpZhL3qScwUFuXrT2aTcDjn/6YL57LyufyxfNY+Ty+uIyVl/HFa1j5Gr54LStfyxeHWHmIL97IyjfyxZtZ+Wa+eAkrX8IXe1i5hy9eysqX8sXLWPkyvngFUB988UpWvpIvXsXKV/HF9ay8nrdTczmZkbRTozkdjO3UdE6oCv9EHfDEY2TlkaR/vUhgl0m+qvxTPvTxa/IFEkeBJWsqYzUeVrOkrWap/p/5wgeS8LaI6VdPDuq1SWEphIa/w4O5Wsnkl/WOLBu/zXFr2K7qkhqV8Lo7LjX0t08qzAgB0TeCspygfraMdDHyT+HVaU94ni+or80fl12eusWewmulcAkPypZpUJ/AEqhPr2upSd+eP07n0Z9/qrlpaQosANcSOHdg6v2kMKkGArVfPnoejXh8Xv1niwWzRc5tKpbAwulCKdnnS8e0LsI/h3LgcOABD7DpCCvAAnLykKeipmFRFTbEPy008E+X0K1SIDuQOP7g+Ck1Lzc0bd6k0M3zbgop8zJCmfOsoXQ4jxHclsTBN/ZXPRHMzDNHQLhbNPc57+o0D8F0PMMH8i/kXQjUwy5o0X9zCwHEwxAB6b2w5SqCGoTKuPNcwKP/2y2kRhDwMuc5/Vl88fcHqphT1x+/Rai7Ogch2laKFsdog3r4FmzXzJcxn1gaGXMPoMrYU78yCYPox8nvrnuQPfUahfRHh23sKWwSe/x1+jSCQFDbEQqoNv+3NforadcrE0zAg2zTSX8OebkamQdyggF0ouYegNbOxzlyeV1WbZ/LOnah2p6udBxQz89WhzOUrbje0A0IXS8FJzveavjSalt9bidw4+NtDu0k2e5rXgtljV5waZWK4w2In1Vvuz6+H+NvxfjSaPzSKYjH9zDsCKsn1490TEyjRPxkG4LpWjDdqHCdB2xAtuNF2rzl4ZtfJWfrpSZYcnj3xNJiWbxiRgD3EXK6dRL6IIBDjVZNBWmKajYLjBihMiCU/szsmRCemqxmmf5DVPJ1y6ylmRQL4oYO4AEy/IlXeXzAGwyimuDGZMTWCRG/TwM5wDOQu9JcKyC+SZhhCpWLLShZOVVQPbL+i+PuX4kSWS3Xl91ps1GixLES2Akd1SPrzmILDK1naEg1NWS6opLiw/x2pXl4VfizWqnF0dNwe/MW0zfCtzRvMdeFlfYU/TcjJCiKnCLXI9VKa4wI3Kiqz0aXftObGxW6e88V/YU6AkrkfUKNImAiJQU4Nf8gcHqxKdwFvXqUV+SgCh4ZivP5zQ/cHV6uBc0wT5YicKhzpAFWdG5pgM0flyGhjU5HUA9qZd7vNZ+pKuiBZortnrlwjnyLB0IYx7o14RzslTJToKVi7ER7t9qIJZfFrCN2fn6SmXDKap/lBh9KbxwfCrye31D75xoQ8KU2XinzYE7+qfyhIHOeQV+/1UdZuL+tOgEDkE4IyecUtdqCt7ZFLL15eLkh9wzmBBPH4dh1niSHOycEUhA2IF1Rv2wRGm5kb2flJuY83U7OdqZbyGdOk5cvyk0cE2yluhG77rOYJCXPeZq7+8ueyevGGcj9J7zH4p4qcppyBpnUj6uNDSg5B/9gJm6Vu0+vNiE69SDZVvn7vVUeXjQLbQxgJBHK4rD6up25TyAb/DWlo0vMi4YAqvkoEQ65QJVmGGtpEPVmVSNnTy7un26q6Sas6Q6zcDRiYv5+2OLyjjr8g8pjZQT8MKgttJmYCSqAIA1FlMVg82ZbIiWczQ+0vI/4eptSF6kHrxaj42iEucTCWqeSVJe5UQV4x1uo8pOR1GeGQpwnVT0lpJSF1pUprWhmREBoauOAtcHebp+Mc+lxpG7b7DKBoPHt/WSRtwzYwrLU6FnJ8i4taFSq/TT6oQQEX2A1uvKAwe5zniT1oSdXQM9SurHORQfVBeGBhttQf9Kvt9vNohwoEIuahutbzIDT6mXz5rWiXK386rHzatdtxZp9EvMfUDo8V6EqiegHcuZbSke28e8yU/JBUbst6gcjJgQ59WQlQ23Jh8n0kIxzGhjxReGf8uqj3HnA0dM4R9TIApzo0mi2tjCaDU2mrI/Bg1npKLLQC/4cFZlYLsBssbhPohaO5RORnixje7SAqSp6RlK7rJ7VJi/0DN0idSKajx5afm3/hNdg39SSvWB/u1XmTyX7xopGugNwhBbDiDrcMDu+clWAT3py6DA+J+ZTgUnZihJRPix8fDnjsdsTpthtyTc+HMscfW60slIraaXZaE6cQf/p91wdd+t+jf3/uPMRmNoaG7qHCSCmBqoskGoqnixQHeEuSVHP4CpPGT0jG27ngRliU8LdjRFzqES6EenvO/PmKZEXcMm6cmHHJhUZ3PqNffA5/AL7JyzxNFpRA5h/swX3/6nt5nl3oysmOSbNmx/6LOYwLuk/jCbFDpq/7s0YgjQhptPuneTiqWC+on4FI20T2M5xPpln+DzaNoQ6oW2WztRsi7C2yeCUzlelbXuSdHPFETV2ywLpfdq2EbIP9XDz6Nd3zKIizClDM6ZjH/1eUdFOpj2zefgbcBCVWBx9cBA9anoYDqJHzavoIJo3JA6iW3GpD89XWslOJpA71pFwMKL6oONucQCVYLbfwMLm42FNWkR5lxF/1yeqLHytEKtQgtG2/cy4HrDu7JWUFERWn28EWne+hMdqe3bhrYbHkGWmwgfHdFhOTdRhSWd+IiWMoQrM4PMDYj7IaDujviluFfP6YACLPHwbHsxBbR92tC+IHUWV+jnGqszm9mdglEp6JVsKq5YdJC9omMobB43cjR7cug+WAp63iKJAQ6O0/qNptFlz+ZuiCX+bGo7Smk8MP93+T+bbZpKQQNtHw5kyVscMinXOiIVXflzWnsOGVPHgLO9qU3C0j3+fMpohEFX2Fr7jZxQNnkpnVa02j2X6a4xTnmNEK88ejWMZi4NO4nhlDpRamo2gef4RrxhVOp+MaOGHMYpXwjhlEi+ZRfGqfMnPlfRZps+QB00RI5vVKcnZEf4SL83hZVYezOYLrF5ePgsdjxpcZjhJBojtZBxVgPxckG+U1URGeArC9FTBgelC2RY5HIT6qOfNoexFoVT8V27pRh4xltXSjehKsbSW7udJQD6iJuRQjpqYFJrGA0WrSe9pxOuhWW8XOQUW3ihY8C+Idwu7lJYjAxWfhiCoNbJhu5OkitQfCn/HQIq5RN9rpbciWf3v2A031c/rvJaspr4nis+gjOcjh9cYd1xu+HbzA98M52ilqUBK3rI6tX7ONYlDs64hFclIaDQXZC72wtbBss5fQj2oyw3TxTbGA3OR56L2WdXGfks4lafh7k1x0boGCEmhJkTEpKKeJ1k0EpKNA0BLjm2EvyRQEH4SiMjyhDpsV7Y/RjZtI4qqokV7/YtZhOZrixwPfaM9vdAcruWHtGKgtQbbTcWtXeHhPPeg493wIv4G6mrfnqQn0h3m8L3qeWKz+yR1GDjtyMGQt91cmB6+DYiS9a72BabCUlP4JnXYvL6gfbG5sNIcuoc3DuDB1zUDyrx/LrAwmyMI3+/KEZs3kq1fI4em1lFSNQ5LnPBCBNn7x9iRCftg+K1Y1+HDwXq0W8lPBAP67Zmkgcj20UbftIw11bN9J0jjkcAWegx7ck5iGfTxrVWs8FLxfFtcBFm13bSqjdDXk6FCjGmEzjIl446MxtV9A4lETc+o
*/