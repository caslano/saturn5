/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_const_member_hpp
/*`[section:ref_is_const_member is_const_member]
[heading Header]
``#include <boost/callable_traits/is_const_member.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_const_member;

//<-
template<typename T>
struct is_const_member
    : detail::traits<detail::shallow_decay<T>>::is_const_member {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_const_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_const_member_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_const_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_const_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_const_member<T>::value` is `true` when either:
  * `T` is a function type with a `const` member qualifier
  * `T` is a pointer to a member function with a `const` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `const` member qualifier
* On compilers that support variable templates, `is_const_member_v<T>` is equivalent to `is_const_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_const_member_v<T>`]]
    [[`int() const`]                    [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const & transaction_safe`] [`true`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*&)() const`]           [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int(foo::* const)() const`]      [`true`]]
    [[`int()`]                          [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_const_member.cpp]
[is_const_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP

/* is_const_member.hpp
W1bxFt6p9YqAZjlfnS93k5iWrQYiacQCfXW2iybZRBGFYc9E8CrdWLb+N1BxxejlJ6SoU1JJcROcpbZRovvEQOQfgt4e9/LgyyjDDL8yIvHwtFzN1//Fp2IWd3H0ZPal5Hc4UDKEZDfJaFJS9lhmqNxfGQVy0DyXVcYCaScr1CkqxftH2aw9QgZNVDpomjIAe7xhmYDmpw9xCZ8vyU2OPV7X76bnZZu/g6IEj+P0sK6PNBVDG65MDalJCSu0IFQ5SUFlPAweF+JVFsRIkwIEi0buUv/Oug87rEWCq0p7Q0ND7Sy4bbPM1mAbziVOPrRY4UZq30Qc10hcF60cbBlKSnHTMgZHPWwvQzZ8pTes2qOVHXHr7suGv46ymufJ/m/S2MlDNym4/AcCVI68VAZIORgaaUwQkm5ZiOyWoiVH7AJWOQnDYxGp7/q5HQ7+b+SQykLsVPQHJkdUcdrigK67Mrt9h2Qow7ktgnQw1HQqqbS8ebW9JFS3Opst6vF1V0WST95aHq96D305LmetGLNkHVQOu01OwRzTV5Y/oIW11jjKSIwBmlmQ93RXV1c/5GXyNQZ9/DrR7UnDMInuzpH3C+7dU9SZal4erHjt1xAHJpMLVNeNW2feV0jGMZBZFIGNPDLJrBFM69gGKfKvSBDHj1DO/p1bF8IIJJXhLM0EJZaY7PwDjN0m1bf3DZF+hF6/tMxCWjvdmBlg/XAzQ+wNDw7lMY44pOtXInn1V4a49Qez0yaQk118QeSwyrc2zxSk7Z+aaUp/A3LVGEcxS5nIGttFjWS5Dtti8UtB4349MxUpcOc/Z/fpqHDpHutK4f33NtsavoSd2a/X+B9O2PUwWRGYfeHEX4RR9ydNqOv0F+nm69rD0M6nnvcOI/XdGmNJGtYDdR291LFX/i7OWD4R6VXKx8eGzEEV/CEmyuLkSAJvtGXU8PAWe1rv44R7QeLLRLox7CV6OUzQbXaDJ8665q6VmsfPDbyPrIL3z0w9CxPAy+yye92cxSheMeanmR1k0bkgCSaSJFDWSKeRVuOL6S/e2oOFmHjBLw/fXDDER4LMBYseULHtZjH6huetr8P5dzrbNYNanaSxZjGOWuuHEkUJu6mtpzSBE44o4ExOhmuHWnfXL+HPqeXQvncV1/cnSJlL6yaq5YKcNlOP58loixV7jNZDYYNYVCWhG6Z9gONerSzP01IG3zNjqCKKQUbdFeYZPj6jGYkfUt7nY46wZ/NGVa2/hGE9Bn1ENbotzKyz+RqpS3ZRKx+kanAv4hMFTXMOlVJhNm98lFFTC1q6SQGWXu+tUew474jh3+GEcHuf0bK73UR47nynfExW72w9v1DlMbrZ0+OtIhI5Yx016dwH9dWi9Wjnq6MQzrYSjPSmWJaXbIVF1C3thoev2PTpwxPhEUPeJq2LCTgp4yEG+1VFaPq6rOxhSWz3j8nI7zXZy4f2JUl4RUusUH5M9RMalwW5Rl3BdNtAso3nIhGkAnUefUfMbt6POp+KrxvBef/o/5+5AE67vVetGwjIdZmzJ4+GCW9eQ2F+RUQHQUFBLqcsg8oJAskf/STxvMz9X1r8KSNz0DND4F507vO4/rxwVSfG82xlepFKdEgvnx+uavk8YQ1MV4ZyMC0ZUtFAzBGLILQVDrVGExMcmfRTCg3fmhTNUhk8ppCsM0USpRal5UveoPBaN7ETHJ+ro3P0OY/jkUGkpLhXc3vs0BEk1l2LvM3gF4hlIldJTcBbazKZKQKoXr5ohXW+nTmFeoOZso3E/ErkrGUAZxqXJoTKjUVoea1szffHsbngRTxsUX+sUEUot7rRv7NN6ksSPI94tsQ5d5F9MDNZxydHE1+Nlx24a4ekneJxFKYCIOAsTCw4QoKyA9RQZGtkEP7y8A8yHDs+D0JXMLSxsHUcUQnXLlfCvLc9OsJaEpJZ2i0NGvXM7b4WnB6LtUZ7U3WTirEvTxTXMZkeRnZZpDD1OPvWJRPMx/cHYhldrFkttX1UcPjrGKOPWQ1Plr9yxGUXfltHFelXmwRjnJ5HYQshncZsiyOxJYRRnNvKvUMQ9TxpfBPB/VkMV12an07R15mKGD3m+xBuO7UNVj2hctG8iRdBvn5GBuvtx1nQGCH7NGad6BVVSyGfzKabXDtCk1ZBIGqrTE3xH2Ho43G5aB32gug0MRvwP4jlIBA0Xyr0FysO76XnYWEhAXccLQVXPh0rJWVYb7FeGbE863S96PRZDYvxmEykqHbdK3IYpfih5v085ghZjpLHXJvDHQS2/XCr08Pn/qNponVpSDI9gjWncN4SpsR4ZRbYcUvri6OXGjZOyfcHg02zCwGQ2/nLEyrXltzhwLUsuiA2li3BUoxKXF4LD8Fuy84al6Kv85PzpIQHuXb45lBuVL6zf21SVj1OJY1+QVJ2dspONcaI2ZdO43l/tcrMSBZmoeqS2CDsgBlkMN/jqFAR9kBiFE3MDpZEDUc+TtWoTLbjPkrUbS9XMpXHE4kSHJm+LolggbvuSmsWpnr7BxjdPkVz/o1wP+bnPEdXirXrbAWKuejPZ11b39cV4eyJ1bDAP4OE8Ee5nAdBwF/8UHszFY9nsVlzo1u0BGgSihmXOuL1h3oN9gpbWOV9byhUOtVONNBCXL+/1IerCfyoFIbqM3XhxeEJX/FKZ6bKViZVFL2S+mZRFdIOCiWTOxYUc9ja28LCyuuZbkSzutOtF5aNa4pQGbvcfc7VU2EMikPTc6t5JhWhp3BVFVU/lPSiJQRv1Vxv581tbNuRQBaP2cA9jf7hcY0k4D1/8AREikOLVHtEOkbpUzmYX0BPMWaOpRRwyxXJTJLy1vGmDHiJBIehhzux9DSJdQyK/+WKdWsOffg5txdx9pbQflYFmmWqwxKcsaHe+bp2RySq1vb+XPyrGxvK2g3h6EIORExJx1nzuZT/05fltDWc7tiCxQ3lOMzVmNeLofuw0YfJTd9LqhUfIdRKMF/k85L+s7hMYpJlPKBrUjPwl26uwWn4zcFENdxG2hyuDHKhFmsKw/pXCXgDbbFU+DOvhfGEyHZdaM++kPIq6de9SoQO6gipnDCqy1GN2G2yuIe+UEin8x5vrCaq+rHsacyiMANnhTexzVwGRuTQJFrfVm5isoJECNwZfJlApXtTT9UDWbRTS0/S4rddOFuL9ouEAAos9dM/XufjXr72/cEevT2Cfc/TcrA2T5x12sNM/tdafu6zYtG8zi2LCXgjdTQwJTBGMdGlCe32Te/HtR+9R4Ak1KxIvSxc9vr6kGf+1wljo6EQ1rKcH+2k4VzAH6urjufswC10bpoatiw25So8xu2MfObNBU3BLQfcBedXPIWTBTKbIfzG0KjWt57KhpJH5AytQSc3ZidmI/7YN4riDYyKGK4CTLxcGUyNRUg+efvz1lYHHFFxOjNKOEx6FRQHGML2S6xIvIlOEi3nuW8RExKjiewdnLSeNwq5NOPMyK06JKa/getN8l4NtTzUa5+SOfw3YUle5uowIMIwwlSMNH5HubisMV/RETnt3+8XiJbag3SuWiOSIu/aZV/Ni4Nc/g9riuoksZZGNgrrIyUinQrWihqf41Tm9xR4jFyhYbO4sI+ZG7xpy37dNgO09aFkr02s926/vEpBtZyNN5D1i6lKx07Lpps3KTMqRm2jRLDXT16moWv/dogsDibxY9s+DugWU5HBCQpKez9ZKueMLsrvSykmcCghJMY5jb//jlNSiWPS23FW4nwwyS+YyyJPo8L0uRrPhKt6yEuQ9Tu3tffeSMuCwongJAa/Qw5xUu978f9uRTtmxycj2IP2rplvbPIQu3eYX1oJaen7CJ+gJCYfYMSwKuZ+7++g6/0IiFKtSVzIykyYsk0YJeENXTYnSHvUZZXuYZV7jzO46JafiWwRzQHdYO/joZq1vGtSIZadK7DHYK8M2bPLXWGjaFY2WEa7in7CmzyVO3PKw87Vh9w/rUDpTTJlVjgnF/x5NrkK/telEZJATCZShnGLrete6S03/xLeyerYzf9hY7WyTU1P7hZgsHDfdBwj2vr7x/E5e+ftj/uf00LA3+OZGowzT9LrlaIv1IVdBr+fjx2B7l9LVc9HU+kbk5OYF6p120XuS/XdFClt9vAKP/k/dKPNkYXn1pbg1/ALeFoHScdbMAlNq3K4aDlMO7z3oGZNtyVtkzhT+wv5tLb7N5pNgmaVqcfjzU9FAH1J/BJ4UqZKJ7Q0/UVd/C7LeVcOL8sDJgk4njRauKMeL7L1V1oXcQFehS2IZHZJj6yYS3HlVk4NXmDaXmPeKIvHCku1P2EgkwN/dO67RWa5S/AOcvH39hm+vU/nXk4vsE2hD3IZFO27EKSE3jPWLH89UTzdc+BwXCCHgORIMsjCPm/4Vv33UqDrkz8qCx5kUfce+uEWfo8KQ0UrP5pYh+NhIa6qBwzOymV6rbGZrbGvWewECZusEIqjocoJpmp3JUS91P+OiNe1EM3Urkxj1+oi0k2/yYmKxiIWSyYBRWf3z0liny1CuYb+TRzZA4mfkMWk4KRCLvZPU7uov3GvhZVQgf86kRKCOfDZuFBX1FYMwdD6H3z1KNjvs4fCF63Z1ssWP93rALsWKdbvlnpfW3/ulveKVteb6lR/8j2JEoAYeK3nDwPT0jvETbSu+5brRw8IQvT9sBEZ3efs11QfNJ9GLwDubIY9xUQUw2zAVkGrOiVkU4qEdE5b7g/IUUMJgULrOB3eFax3s3MZkV+cTbJbd/ZTT0pJTgVtjpo6gWWl9YNnM/TcFpNFs1fuBpsZTWPsyaNZ95f/lR58TsqIZ37PV3fPDSK/U0AR1D5kRWKUNtQvVnLFL2S2RtssUX5lORLyLCjo1mXtZKxiYxuUZJTK1iwcUWKkOsvI1HeZlNWKPnWZGogIGOldhOvgjZ6trq3vH5ab3zwvTQbuXVOOdxDH5tueFhbHuZ7fD7yzPtxPIw44GltMWWcxOVDvfJ/cObZCTNhX4flN+GwrAVPgEWASaNVA8m/bv9QE3PPk+XcICykc22zWFkaVaCLUs+t6ntch7796517IIKFYwiqe1AJMKdjHJJialqgIjbo6YE6hwVwUULI8IQRB5IOizBiGyCBxKGsseS+YXGZGM7Os4HLpccZY0/D/vDRwR9Sh5hs1bAPUqcOJloHxSpsHsqRz1aJeM+v/bBxaD8oldE9eat/lQmWJpLZ3b3ZhVqDPJ3g22SRxfMKNq8Zzb8KjDLFBIchjKaebdmUmShe7DzNRol5E00gjmPD7kbGMW9ngoAiIvosg1Xvo7dpLenOhYh1ONQGBFS0LjQe0FfZLyQLcHFblhmn90GLb1yYvqmvVWL5dc+/lskqKtDeFR5xCYD/XHFDU2UmJ9d4soZJpdYEhQVczuDnGlrCzafX2Cs0py1VVZWzYkK1BWEaMuFpGiglmjDxhW16xQAwWoFSB58joGRarbaqkjpIhQKvlzpP19QLr3o+8qUh00ZYdEFimZp+ZjZ078b2JyGS778yXmiyp/mkdYg6GVUKFF4m71evL8xRHanltnfHgsEx+JFu1m24GDOU8VrHM3sDD9yjjC3aJCLlfaiY+mohYJpB8d5B3gW2dr4ruUNyj6RQHE6/CML+flmjSMh5KqPJ2EumNg0SFycD8vtYur3sl3L1/qhYpSsOD749FA5YQHtCfMoaURG9dhjiLURZt63cB7Pga3NuUwqWpUGdxz5SjaWFzvlzJoPcc42p9ntO3iLmRsDHUpMJiSwEI1AwVKzio16ohr28n28AsHwxVt8FxeoxjByKLhB6wN/l7XvoXUfqQCldQsxfVXr8VBTD/DmUm+nHwqi/efGr+u3CCooJFp42aMK41fKGephOxghHAlKrQOsM3NTipEjIGUTJPj6srgKXRxgWd3oNHznMhiEaGoZGhDwhRIs9leAhzvEcHwavK3icwo3RGKiobq8ES9tSqryhW7ci13w0/vSmq5jtrjwgiZ+oPqO6AAN5v1mFAS9B38aAz0Cwr83m4rrFlYA08VG42XkSyigIVKmicWdFz33LHrv9bVgNkZESEug3y3IYLySdKZIefgoiWGO2IlTYFRiGvbNHyrav2J6NSqOgJWZ1djF57S+aunwOFZ6AMlU1Ker1y1MXJCScv9hLWqJ014ovWbBfAfzlY1U/cj4YEp7aXaYZXNDL7qSmrFXfPLEdas9CJOhURtC9QzQYP8WXYOwB94q1NfeAVtokc/iRJugENjxbtCCtUn/Xp7n7qyfDNmo68XkDDKiJAXrJB22PiWcca5anhFiBIyAW0dstAReJEFSVL3DR3fxfqgMKQVjTt06S2lCMwtkda4+CEIuE4dhsRU12s50JyZgbPTXKCCJ1ElwsCCUqpb1RSKaBPkB1BE6VlxZjxqQKc9ZrT4OMnBXYHQhTDmlo9LckxzG3k6eJrVsehh3cc1lNwMLoWBtDatm3btm3btm3rtP1r27Zt27bN27kzWZM8ZpL97WTB2TeUR3hy/MOuqht4iIN81iWqknr2Q+RMPX/690HsKAIBZIQW8Pzlk89Ebad4N4+/X+4Csr+WrRCSBUQ7Yg4513O3j/Ck+5Dk1mDKtRD8DQAWBFRxm/T2W8WbUugmeA0u049f6LWpCZOED/5kAkL8bjhK5W5NY1UXsDJKRyFjdLJqyyj95Y2KdA3Gc6KNBcxm+2brKnsQGN/i6hXYNDrgQualK5FM6/2lPIb7+7MPDw0BRFBa9IkE23FwbKdPdVQT9qDulivyWQlMFhcO6tTK8Pb0W6XGbOjNvugFZfGdhOmfLQspttQH34ELnRUBscH76nippoFS3Ga+m+8a8lLp5h6imSdRX9/uSNVpbbF+pg1ThYWuBJkGEXWAEGYnEeHBWqKYO4jusbThv2A+HR4ODtdbygcu0UVu8ykSNy3ED4txjBu/xzaP5lZiLnMK7cT3EAViedOPHI7vgmhScGsPkBCeGSJVnto6UzqKkMW2CqrrLb3Og4p4Toc7A0RpxG1rutpT1ui4BJ3zVqL63NJNCy3aGkxSBQpAhHN4iNzlg9XtQab2q+fq/J4MCMN+wRmTz9yGqln0V6oqFD4r/FqUBdIJ1Q+rLYvzG16nOokIihWzRCg/7C702fdcFdLtwBMOJytEaU9zmLw8AWHjrHn3cHHiepIuL03jglDyQTc4GnYIGvRuSDga8Mk2AYBxJncUc39AMzfEnmh2BNvZcwaI0C4kaG59y/8GO/xr+QKX6BGvg4QwqefYCBltcbPJNekmF1mYwrjkHX97OJr1ACFd+sxhllO6zUgK4HG8Lqw6CyVbnE1McDXsvVTyAwI1txQoVT2v5SBrK8lY9/FQStizIyXNC6ogFk9MqSFJmDTx0varQirN05to3zqA5mq/FYXGYN4DwtMJZva/aDkhKfJ67W7FXxOWg0AWLRHERzsT0O8/lz3PEgJeOfcWDLcfLtm7CI3+yzMqDCzULxxtXsqyJ9xWV5ta4DeJSc3JKdvyX0ffG7KGcMnwyZW4MZ9Ri7+50wW20zxqvhWb0z/dc3Zo3rhqscNhRwhXValbB63ngCCtBOEwNfvgbnptkqOiWG8Wx3I7P6BqltzCWUzVBBQfETRoOdaZK1dS5ApdiApak48wVRd6YScPtFXjuMlNq6+zRejQAP7srpw6/2cOzgahccyHyjN5/kiTsqDTT4IKpohrrldI4/ofqM+qJbZ/sdq+PHgF22/xOuegAjUAJ3jj5WtpNLq5Dd7Ncb3LT67B02kLMmYc7i1k6hU0McIh0FYEmzBcLztkelt02+r8FnoPQA+1hhhKsVh4tyAZJyfnXldYYHHPifforA6vp/vN502y/W0xD6s7Vpgpyh1YRFn+xXRxcr77h3XdaUE/nmdVtliqD7hxHrztwtwnnPZYjnM4QpmAeBf4yGoP5hu9Fc95S6wu6oT8VObk4/BRKdav6IfyYnt52N6AXn7PyiAoB2JUYX3YbG+Iq5S3+fEoc9JWQTaBQ6mG5kxrgeRd25XHN2ADQWfldXw6N+9me1jnY2ACOS43+c4BUjtNslTA2mTrXT5vY4a65EJJAA5DACpgeLZdiCKsbakj2ZT6KIvJtrySao33fsfpXOQGbDwvrGHG123Je5IuEIOEiPO4r2bsqsgyWMrr3R1ZLpfqv/C2i1CxdE5LDikbDNFha8G78iy6j4z0Mm9T/5t0cr4z4WhDKxkpGpDwfaOS4rchqhI39s/QcT5WF2HANs3GJA0HHgQSchCvbsZ0jBcHc+zt1y90nz0O3cqnx2owcpLefTvMqApSGXx5F5BeN5SnYBlA/97gTkYhIRjP/aefkHH+BArTf9+oyJs77BP4fvF5TQMOI0OQmUXMQoTjFVg7FUx1wvbLr5pJmcezN2LVX+vIexh1dZkRNLGhbMK7SJSrziL3wYlBAohwDHISdFmdGJrjAHrvXGStWTS5qFZ8oOqKRjYI2MOcYLoK5ltlLZqHTTc6gHPI0zXigZf25wxKaSC/1J+7vEspHubkjDhpAvbOxOA1fSHbtctdA6VQc4DzMN3XYrfx5tLZIlOIHfmAhImznVPJ2jguVLy6dgRFnUddP3VD52O9o//hsFGCz9InVVC9/7cEjRRUW6PkxWDxfCZq7zutiJ9Ljb3sQd/JN0mHMS8TKKEYQ9APCqp+cgYORqsj0nuyJnbuvaTNtumabRxaPB0kqoMiIOT22Xv3XEf2HsYJuIl0zsYLv4IL7dDlrtvxDN+tnCCxTk7uxNo0di00d4IcDQbWPQrt63cXALcbfawlQdRa6rNqSqvOoMCFtS6PQDK6W85isFYb7gS1rB+hn8R7w78kTa09nGslhsgwJ5BPIpP1EHL3tgKvWk30IW0AWjX5STeTDGZy9XEYl0G13/VmZ1PF1xlP4aC+VXPxOXQaHiWt2jtKAMuLVegQp/P52a2ah1DQ5Mv6bMYXEU7jZD3ea15TcfNLx7cRLqc5Z2BHMdJXCAJaKkvLTgdSjUKNiPnUo/bwhrgbKr//SchA7Na98MP22/IMLnknKNN9wBVhWM71b0YH5Chk7hCMbtB4TmTExj865Pe6oketJ+q00mv/B4Pkov54DWqmy5nYR8av9kH7+AuZXTXN2CIWARxuIYLBA3O2xR6CubunXpJo9KEEyGn0J64NnA1HZTXqv7xdGgWCrm6svjfFCI+gA7g=
*/