/*!
@file
Forward declares `boost::hana::Comonad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_COMONAD_HPP
#define BOOST_HANA_FWD_CONCEPT_COMONAD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: We use a multiline C++ comment because there's a double backslash
    // symbol in the documentation (for LaTeX), which triggers
    //      warning: multi-line comment [-Wcomment]
    // on GCC.

    /*!
    @ingroup group-concepts
    @defgroup group-Comonad Comonad
    The `Comonad` concept represents context-sensitive computations and
    data.

    Formally, the Comonad concept is dual to the Monad concept.
    But unless you're a mathematician, you don't care about that and it's
    fine. So intuitively, a Comonad represents context sensitive values
    and computations. First, Comonads make it possible to extract
    context-sensitive values from their context with `extract`.
    In contrast, Monads make it possible to wrap raw values into
    a given context with `lift` (from Applicative).

    Secondly, Comonads make it possible to apply context-sensitive values
    to functions accepting those, and to return the result as a
    context-sensitive value using `extend`. In contrast, Monads make
    it possible to apply a monadic value to a function accepting a normal
    value and returning a monadic value, and to return the result as a
    monadic value (with `chain`).

    Finally, Comonads make it possible to wrap a context-sensitive value
    into an extra layer of context using `duplicate`, while Monads make
    it possible to take a value with an extra layer of context and to
    strip it with `flatten`.

    Whereas `lift`, `chain` and `flatten` from Applicative and Monad have
    signatures
    \f{align*}{
        \mathtt{lift}_M &: T \to M(T) \\
        \mathtt{chain} &: M(T) \times (T \to M(U)) \to M(U) \\
        \mathtt{flatten} &: M(M(T)) \to M(T)
    \f}

    `extract`, `extend` and `duplicate` from Comonad have signatures
    \f{align*}{
        \mathtt{extract} &: W(T) \to T \\
        \mathtt{extend} &: W(T) \times (W(T) \to U) \to W(U) \\
        \mathtt{duplicate} &: W(T) \to W(W(T))
    \f}

    Notice how the "arrows" are reversed. This symmetry is essentially
    what we mean by Comonad being the _dual_ of Monad.

    @note
    The [Typeclassopedia][1] is a nice Haskell-oriented resource for further
    reading about Comonads.


    Minimal complete definition
    ---------------------------
    `extract` and (`extend` or `duplicate`) satisfying the laws below.
    A `Comonad` must also be a `Functor`.


    Laws
    ----
    For all Comonads `w`, the following laws must be satisfied:
    @code
        extract(duplicate(w)) == w
        transform(duplicate(w), extract) == w
        duplicate(duplicate(w)) == transform(duplicate(w), duplicate)
    @endcode

    @note
    There are several equivalent ways of defining Comonads, and this one
    is just one that was picked arbitrarily for simplicity.


    Refined concept
    ---------------
    1. Functor\n
    Every Comonad is also required to be a Functor. At first, one might think
    that it should instead be some imaginary concept CoFunctor. However, it
    turns out that a CoFunctor is the same as a `Functor`, hence the
    requirement that a `Comonad` also is a `Functor`.


    Concrete models
    ---------------
    `hana::lazy`

    [1]: https://wiki.haskell.org/Typeclassopedia#Comonad

    */
    template <typename W>
    struct Comonad;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_COMONAD_HPP

/* comonad.hpp
YHnyLxatrNWmHvmmqjdP1BjeXprsb54KdmzTPNI7YvCjzMdL5Y2NiYwDbTtVaQjNQrgv5cdzZmR0D7HCRn07awCTfKyPkPG0mJHm2zHl+t+fvdlr/d5pcVGLd8ogAvKcFhYUPARIkeNDY1Iz0BaeTrXCCm2z7LBPVIjsJeaPBV39o18uLuCHmd7VuaOPaPx4YI0x/ua3LlvWv4y43Ybaq4DM8YJC3Mo529iAHaqBubasmj3b2wdpmO/a2g0/dx6Za6CtZZbtY9gxxnOt5Oq6YXifVsFM8DF6J/a0tXV04T/vxu8ODr/ToiCYCROdmaZJrbRr94Z/zf+1FBKCxwXkDjflOJgDzs/ZvwzuYaUdHLAimtboTzZmUXqcg6MpKpkVCorh+/RlCDP32jIZymQIcwn2mJwNRaZlczc3EyBvnW1IvTE+oy9vHO0CoHFHZxQNifI3mtUvGCk3gtusvu7YJ6hbwH7BTE2yVvPxkKmoiNZfJf9SnoW0SNWAPmc7Kvxhtx31/5nF6hSIKW79+fy0F3wubiNT773ceqo6cl4J3hpco+1JFPsVHVwDnSHgvkdKxJ3u37bJYR/zP0CfLXNA/91QzKEKHEzjXVvNlFmcyFSIYt0G4YBenHjPZLXIYdBnB8S67VJJNwrL9R1hSbi0bzYNnxVz4XxsKcjnA1YDCcMib821OsXlofCgT1lxmDobBf8VpOaquhN7FHWR2ItYzpZDEMjyOABAJni+MAjMW3hhmgIdJZ+MthyICbWIx6HA5TXcfSVAq+1lID6UXBXBVSddd0hnJWD4IJV7+9MSMKUaJlZf0rPJVQkxkAVjlNEbd9S0rxPv0eZrXnFgqoN3eMfSNfcwv4IcLtpgjLnjr4yQrQNCJDJGwUQ3Y0shHZ45Hdu20pxfh+70Pe3v6shdC0PSjN8P1GG9wFrHH7oyyO/epb9rMAuEkluRjp7Ixqv83anB28FiMZAA5iIGzxK23gRjC+7naDx5IsTrM8EXJtzi8Hy3q5lEQ5ETCzZGq1I7SCvA6Oi48ujN6AT8z9gJi/g9/5L/GfP3FhX7qEg3pPpIK05Uz+4rBxQnKPaXJQkN5H/7ASWh6QqJJuejdJ06aGAUmRvgYEflP2eAx5baRJ2/nuiGhVS42tkgGVYrHywMWZNMwcOCX/A+sMl5bi5S4wWwt7q6wi0mqZcd7vxB6B2/lrOmQtuhRunkZQzKNZBfI+A16zslz56m1DxbGq8ynwJvWK4AToQjU7Ram006Jjm7pzog6Xj3Is/SxnmeLowmkgN7H3hdhlHw3Djd6OWC1BUyrAJF3v3lrDjB/+QE5iRUMn+nDOvjiNM92xxNhegchJ1wSseQy0fwOKIhGPphjDdox6yBQ4aMJ9nGseCeTvSkrHcfb4boXN2tqOXxfuX9x3fk96eUsPkUxyKHJnA6icylDnX8C8941KnJ2pmgFF5741m5vaYKyY323Ve8CvE5piyXcw+Zyi5pr0DOAHQO5IYPFU6gVHigmFOAvMXD0UVi0iS5cuhlEIfO1m5ZfkdJinlrBk33soGLwvrBU+8dOoQ8tvqMHZmhPsujUguTpjikLTqb+XbBXqIU4q/rj4mkkU6i9l8l4Fk1ZaPOHE5cIVqW5bYoorR/YV0V1EeOKi6/IH2hjtk4gxMRCraCPcGif5t3hnaeW56U2R0fbnymfWFccgERXrF7EsDo5I4GHg5jXrYJxHXmGePouIF+vAQs0JIuJIng2DVrwKXnpMSl8SvJ46q8csA3F/4XxAnuOacKOW5/0mRwzIkFD7fULZBHOn+q0j8qVFu+uJz1FdJd+F6tuL7TPRnE5E+slL5ZhfjxQWPVX8JIga0V8ZW8xuJBnngfqnjV7z/r6DRquaDVqAi3yOaUq0KhmSNpXZ1HMJ9ezEQsVvvtREGcacO188Eu31tyS33NMnpyJxRwHhUmKwMwU3O4sQuJlPT/0d535Lorymf6fDEAXLEzJUi8r2Guyg7+BfDcZ4PWPwRGrESRIqCIU0JReR9YHIxk3NkGlIIXQdrM2b/XHziJUdazV0BlrmsMx1kxITMT8oytyhw7LqvMC0QqG+F8IQGw2q4AmFovKblTVhbXAoanpyb3yxJ/+zjvdZrIkxEIYonKckQyiLWUitBZSsHpSZMKsv1HC1ZfFIx0F5kE7oItoTEjwwkTvUzCFSRZkSXJ4IZDqV5sukQR8BORpz+AB2hhA4yITa/2Pg31TAtW3aTp4+74PguAgpIiB2wai9v/VfIGY4LQUN1/jsVsQGl876XYnJ40i8yH6qQGXXYVkas6ZFLC8AEUuDTlzENYXqRX4lJyORJZxTSMJogKCqaTRpzA3UnBD532hVgXLzQRhGbDUJiIEalO4JEyf7FbAAIs/dP3VYSc5ldpRcFr3+GZTw2cg3/U3lvkD6fuklTsU8aneBsYZX/B4sKfGzqHde7FYbniqbVGwupwpasYAukdOTD/5XeyhzcqYf5e1gCdCLtu9G59bHyofgSZI7Oq0GKTnq1cPn/CmUb7k/ryKMkaqZ/Qi3HKFrWaE+PE6IfuxXuKOifKDgDrG9uywecHIWUa979dZ2J/HTLPp/poY8ANHnoAEUkeoHgogd+yTTF7vWYt4aA/PFxC/amIOUg2TW0oYAJlO2YTrUU61vZMEJCEXGGYaxVPzoR8Yl1w/kfkcrqr8Q3LrK2ICEtwr69iJRL2EoO7QH1UzUbx1JYpKqj5Q9UIzc8o7ykPHbxsakee4RaIpDRaKpiOo5ksWSWV82IPE9oHc/gLvA5W3rbu9QcDLEBxxBshnQdG9HgwoFUbUdoHPh9+OF7ZiDWCGT4cGCIMJ35SfW0ohScqHlQofrhEyj94wU0Zya9eq8ExW7jIbs88C9ugABzc4RvfYAedddZHWCV2d5933lmNIXIm8dTD4Bq783fIltBcbCr+RC8KVenU3LnssQH+lxF4OnfeYlq/77a3ZNMCwkIr7Q7HiHNZrdkCstVgmm2gKM7A1citv8GJVrjmPqA2N17n4fqWDUJeWlsX/PAP8Lu0EOTKRA7ATgqXlntSC5PSDTkCjdNSw8nmmAvjKdeWOkO0UXX197jB9GXjgAu1RTPggoE8R6/MFApQb4iclwhUj3uCCdqnNe7zOjSZ/GvNZQ1mbuPVuUxtxUwX9upnJz8ozpNQ7CjZPkhy9jJGalTSuuo/sZgFEYybHNgcjQuQV5fVtlETrNooIkHCBUX7oTb5F5bWQ1x+/Bw+u5arxi2nOK1kYBkNJcqlwlBbGZcu07nqGF0mcaNQFFIwKPb1OO3EZXPw/cJsHo3jyP6N1kxJMoOHQ0o8Uz/41RXHleYlcmhQcxXtu25NbMl+PBBMV/ISXZ9MfvFXRtJ5wAQuC758x7WTwbMMiSD+ATaf7jcz5dR3U38LmOn/ANsVVpAHgACAQ0sBAID/f0GkRespacxMvSoEwIJHiVP7GjJx0HksC+IRRBahn+l+zzGsnW/taV2n5gv5clSK3HJ8uzS4ei9v5brCt/BQYPEbk9it7o0KX2oPIL/7ePKuRNQAZDbD0V9UEomWPwxJyfgUtEbZz4cMPPqp53trg6ykSaqRHfGgpInpOubzV49Bvg/BgIy1hMib55S105MdNiQnsBDORkpM0nqLSWMtvhkLCrIj1Slapgbsn0O1FnMwZuhQ95VZwjlC3BZHeRYTdAW1xShACIaU9b1094ecJH2ltUEkzDSZIxk1gmBqoKwgvkNGz2m1+nU6Pjohh9MkpgTejzU/kr75ewL40RVaXPV3hjrzPWiwVqi8KdOZWObZ+qJWBnXAprS/ZJ3ZPhQcB5X0+/12mmaLXiy1+LpGZezkLKqyTl2ThhChKGOxD0G6/6WSqnZT/TNyrlgnpviSrhMTEKzrWDwTNrCk2b9JThBmuodxpiI6yEmbBJ8zgQLPiFRHdx4qYi3GQHewbG6rMaqLugzY7bOGOwqZsyi8MqxqMBQvha+4K2X1dnJVHUVK59tEnirl62mio3zuIHkwnXnooOeeaa/4D5//pL1uP15GwBagusxRwyz558/XdNIFox1yDySiq35j2MJWk4J7s8D3Sd116EfP32sUkrUhtL3XcYthVuUOZNuZnDRq/f//fbnkJhxYbgAOaNg7DCHnckWIkDXzwNT1iOQjadhdUJ9ewU9urksAng5P1qOhuWxxu8ZMWpRKhOeoQPWQ6LUwlnlhJIjf8v40cPVOhhnIN+fki5sb7M8dvxCSAVP4pB10cZjbydLEEz8S4zOVVhybrGhMXuaip/amqNFeW/amt/k0J1b/MR97juqXf8JCNOtmrAdQjoAdgd861ho+lZKyQmTcrtBeJQsUb1d7cnXv9QDRM0ztwE3goqyj/3TM4Zgpf3J7ARoJqljPOpyGQb+BOAjfvgUs04ZB/9UvihtW4F4Mlo9gGMwLAeV8gv3qtArBjSY+3JgYX03CPwA4XMJ770Vx4Lv5ds+YFgtjmSHGsT1Ya04KkeanEWv1mkYhb3P/zTTaAcf5zDZnPQm5JuVcLOSlY7X5PEZYeBu6aYnbvvFr+AgaO9Nm8P6qyygQAvVSYT/LW4co4Qp0jvsYvPBgaJH92vJiTnr3SzBvJVhaiuKLgO9XBjCgajhmeBjTpUrTAE3VC+LmzEKwVUr4yrARnwBBxETkSJgKpynKq2uy0QQmMtuwoBG4iNVmSt7XK/vwSz/BwfXAx+5I8XKH1/bXZBNCUPZY/QCuP9mkcplOdQBButN7mRBsHsqzaqNUviYFdDbNedQ189eWZGpYW2fTPybJMbnfzFRDMsQD95kinrXwonbACfpi27UTQLocNUCLpSFkIuKcNmp7Xs/uMKlBHN85xeiqq4phr6M+R5BCa/KIlJpabNCJz0vpqN3lVHQodJ+OY0e6mQoYiv3RL761W/ERGXZcWYgdmmZvNx1tlkYZcaPDe6SJbREM1ZpUjgiq4sqP5Y0BDkZzKqSUXvvktnwHJDIPhmQS6ylvbQgnr13RsogP3bjFS67XP6TEGu/5MqwHKrY85oXD18xR7tKB2YRIqKcDAhmK3vTs3jGrxSdICmhXIRDUVDVeXsTniqIGjcDHEvA94tE6Mljp58KSNyek6VYAUD/IvHK4PRfoG+IiogRB7nwQ0gaAdZr4cPKNw3tv0KgftlPopTlNEF5go/Ssb8ZhxqYKmUGwUVBxppogPiFyl1Nos2xAGaj2xZ+26HVoOSNZF1cfK+vSVNEPadOIPz23a73WK9KR7aTyLSFOinFrJ9Iv6fq5YETGJnGwEVt9Ss8hbZUp2aObihlLxeiAo0JV+TfAbwBESjpKEo6qLESINg/sGJWtDM/ysqAs28Kcq/09fcBB6OEs3tg3FUC9n3mPUgNmXyFW5VyJg1Lr1lGEvLovLM7Ktt4SZEDmmC/XVw562wtdhEISe9cXG43J3vNQqESutlxKpLZ4xTxHWccfcEn3RfN3ty1fMfF6I2eggteaLkLReeFuWBp93inyhb24sBg8Izz+Tpnd+QoDsX2YYpelkca2JU1XQVyU7GkFfIML2UoJvMwoVHqWV+Ze1Pgh9yRq/n4AQOuOow7+v+hnq8VTwjYJ3xBuRJJZUidho7BcQMIt4ROmCGXaT+M1HTvx/jZqdka8kj03OZDquBN9z1tHxPAaAExP+cExFX+oNt7uox8uJfZ62A4qgrKx7i2XJCoa3iOYpGlRSnQjyAd38CyebS9v0G7uEfEytua3K7S2JTk40pehHae36I1AbHYXa9UzPmCxVyQj1T66mqMa4ekzyfxQ/OCQSOgNIM9F1twQHjTp7po/MLYIlTskNuTuJLOXK0q4olpwqDGld5jX8aM9/3EeLIiE+8fv6/VU0GyP4qarrqvLNdYB+FE7Bocwwnqp/v6dp6Vv77uGkO1hKro2zwmiIdb/318yuKiQBVjI5dJEvjyUvg5zSW7Q59PmqGTxlusfbSPKzZil3KW4P4CjfwkHsQdQ+oONYkCokbbDMO2Nv3h1PTGoEh7b10KglU/idY6SXrtqae0Ckzw8aiDkYAJ0mUw/fMvUkfFMriK2jnwINeuAJ4vSG0hEJzp2OjgoqeCV2Iykws4/YLIUcYyutCMDFOI//Fqk5TjCAf4yGfLq6q7FNbw4OtqxP25XKibsXyla1HzBBun/em8M4jW0cmwWEekVOl93tdMLOaIBPEXTd99k9MuXAm3z9qWyc9MXMaThQGtjJSBzE0z86gzKYH856JtOrG645pbKKZSnCnMbTcMIcfDXnlK2n7pwc70AXg0TK10HgukNIlE19XHCckTjunTATZ32LhOli/aevaOdXYTgzkOCbhA4sk5UBS0jJzJi/Uze2qfBNC968KfdMFS1J91LDg7/S2rLs/p5DSf3AUdYPZTpNVL+8nr5HLaVrZKL6KBxkHIyg0IqgPup/1xn8JBjIOVQCriHeX7IlASdolRJDadx7DHJWldgd1j5pmV4pid9RSy+o1U4efmbhz1Ay+Rbm/QZjHbfkBpTeJSTLNZU2lh9qOJ9IA2iEUzZPVPj3IbsOlxGIFpYndpTkysubriz4VKfPQq/bg8A7HCPibio/3frNLtv19cgRJLH4WDD13P7vVt+wkCLtIJmoLQCTlndIrw9yuAgeJ8kuWtyssIhnSfFekyTnnR6lpRvZNvCoanzMVQAVqXi/eBETCa+USJPYT6XB2IhyZO6KJYx4hbZPznAH49WqUp7r0j5tGYwco36hnr8PRV7+QVxPxWjJ/FYSHn3/Dk8culzVAh3a90oxNv5sOXxrbyuuu/kPxOjkLZI0Uwh3HSFNsi7yDp2V0tEP+9f9MIuUNLX2z93owZgb+qISQeXdwztN4POebc3Qmnap1W9dsKuSiUBeConcaWgaLz5aLNtz+1UX3UWmzYNRtVmL8e5RuvYu6/AGnlrHdBld1cVX8+DEr1RD9QfsxIzvvwWJbpIbnFriWuhbIstALOvHozNAwEVTfYEJg/3kwPN69JrLGcKOdHhnKBdReywQFnTAkbLwPkEtGCrnr0yWveyQCG5B1gVI9D0krz7J3RMcljhY/ZZo9Cva8kxqIAUnj6htRaGpYsUBzksiOmXtS8MpxuSm33zYUQLs/bXYFEHfnwYOPD4TYeeKzupDhyoNhxITNlTcChduCbg2La9Y9u2bdt2dmzbtp3s2LZt2/bkn5lTdar6uejLfnu9q75ePcHkj4yDQFstDzXkZQtx++AWbo5VbxBeyMks1Ole0O0kvW57AEE2q1RlcpGCzfKED6ixndkkc95J9rWPmr9l3RVakfMYDV2TBMcRytVCB1od+Y6497fKYeIncaRrUOrbREifkRVPAiJKiYVIcJpuWBaR2/gDsAkhLf+GkLoeaGtpa0o+k1e6kyPDYa8efFXipAwY31nXN7xBOsU8BHGQ4CZjYFXGx3RLWW/4KKmN3B/P4ACnclIqNBolYbdEpRCxpvGTAlpaexxw+vTrEGThj3azKCvaSbHniLkWSM8EJpFNtWsBBWTV86RnMaOaC0iRrWvQxZnljsdt1HBWqmn/WUZjALxroLBtgYztn7BLZE94RPIOX/ydXpP3KjVhZF/homR7ITC4wKMQBzDz3QuVRwrgirgTfcPKj57juQE8gvZqWXhSGW4jDFREevTn5fUrpQiuO7pBYyP7tHp7RfvB1yXjJr0iDjHevzM0pPW069z7OgxuOk+Cq1MlDPjbRUH0DGP0lG984brD9T2l+lJJEaJTHx+T8d9H2YklkgocZDk6IOy9/EhLJ5BnHJRtHZQ/xso7kzqYJCNueFkb+rKD7O2ATtfgr+CXvErhzsXitsxcREm77M5riT6WA2xyBz7UDJhu4jtTlX9vK0S5GYlJUD16Ntf3YoSjz3pnBkO59+jGSNi1rTGO45eEE6axj3jGDU0rm3N16W+jTZanALQqC5eTdAFRCI7ovNRHxI7irmBzbOaIiRvDfdeOFUD2AeeI+FJHRLu6c/cK2qDU66wKT9n7UqvDqhey7sGqkl4kSFI3mq/oUeudexBCyVETTRkU00/VTjodW4Q9aQSTzpHdxEvM77CS4KvK8c66BzJpes11z656QKlZ3IpwdtHf80u+m5Uia16itUbEiRfbmsRtyGlSp4BRAobNZV42xCZF24s5E+eIvmxVhLjA478EHd8HdLvpMJc4RP7cBM//KSNI7itOzdHSXEbXTX3lmrE07rVliNom3ZwvuhitPQe9Wk6MXl0sNLFdKgirapzPSVKhq2fOevVNcczW6xSN8Vmh/SfLzBERqf5EW+0SLCpb1qGxg8Z51QaE7R/TZfSIo/wYd2fUinvzZ2kZ4H60x0ZQI7tEj1SMKJochZmDbe0rbs5h96Ci/JBp6/ULjoXsjvMvNcc06JCeWMv3vO0k2505rXOYZIpJNSviU1yKhgueKc5agLH8uH501liJNcIqDANdj0fjPkHIXQh4q5lQ253/TGLQNbUCrpeukM6QEIFfxJos4gw0eI+yvE1q0jq7+M7sVrfrSf1hH/XY7Q6x3ViKxmS3E4rMx0uQ84JAM0yKp4oSe8O/i+PMYY+zVh1N9RC0JozXyDMRsi/AeKXiMOMQjgdk+fuSBt8pm718mvyp3en1H+yqWgANcZNoEH7nGDiKWj21VPLwm4+xh7Rb53qJz8hEhLzoEB71oYAmj90EnwZohdfSf9/hYtNWP+PlN/ue3myCAdUUjr7zDON4WSMREDkrgME9rbSWqvRpAecFTIux1yIIKWb92jv4OQ/RrViEks7tdGeSMTlK5UgtLqn8LI5dK01f/utj89INpbul86Yjnz9lm/CZwilc0zxb7wabDcvrzkCQgx3K//bFke2ei8SwwJ4v3Rnc3shHS+OlJFwqHPF1oFCIpDev40gpyknUrhnSJC6KJoPMXEnvaYIn8TJScBmR81zCNVGonwA1aNtg8IVY3edu8NuttDJIcqCr3pDX58P6uygp/c91/2kQYLrgP1/5ANWGh/BCSKMY6n6MMRekELq5O1d8FRR4qQYT4WAO+70zl9xqAdWrltOm+yArXjSNOA6+2X2CbPpv+QR3cPOdUf4goEoZiLsTNPLMHBt+00PtzDd00LzVIqqW3A7EUotFW820NlOzisbUQNP5iTSun9OtGSAqRV7MvjkyetAfidrZ1xNdugHFxjsyG0GCs9NgaVSmXVssIjM=
*/