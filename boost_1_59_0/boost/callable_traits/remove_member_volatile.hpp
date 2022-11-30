/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_volatile_hpp
/*`
[section:ref_remove_member_volatile remove_member_volatile]
[heading Header]
``#include <boost/callable_traits/remove_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_volatile_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_volatile_impl {};

    template<typename T>
    struct remove_member_volatile_impl <T, typename std::is_same<
        remove_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = remove_member_volatile_t<T>;
    };
}

//->

template<typename T>
struct remove_member_volatile : detail::remove_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `volatile` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_volatile_t<T>`]]
    [[`int() volatile`]                 [`int()`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() volatile &`]       [`int(foo::*)() &`]]
    [[`int(foo::*)() volatile &&`]      [`int(foo::*)() &&`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() const`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_volatile.cpp]
[remove_member_volatile]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

/* remove_member_volatile.hpp
iSK2WTtO4f8+tUYMwFbbithrmHvzxx4fJzm/vHaWN1OAA+sO2BBwZgwHfQ6iuh86xZFkeOWBJCPjZu1XukaQ56a+qw7OV9pLLwySW7paIbOixpbe37ABCxZazQJwRghZbUVdt4Dct7gR6Ws0j7yDEkTC6kYJDSYvdBL2sNk6Z/fwIKqgHN6ovc1zA3FIQCC297nqWL58gRUDDh64tQ06x54xkwO0Mh5lQhCvAUij4MIow8qNnk+EuLuEdMIktPKDpWy4BwiFDHKU1eZfcT/5fP+RPihwBo4+4LgPw/P3gIpDX9EHVqZjztCUEI/2wXGw1qbccPfxHGwAEX7yVzU24hjN9xQue4UXDN4adZOESxPFexzCxH9CQ35sbGxhKC1sOnzaUnZViiEGAEGpSAbkR1LBJAvbz8E5kRROhE4QRm1LErnE5phnHMs1rsWtyRJnC2ZwbJkS3s9IZoGJ0NWaAKULQBeGAXShrBU7WCi8Is37fo1yfYjrtLdzzHUgX/ld9dxecnx4vOccZT1MUuf+cOAROPlN+KxzJIjL2g25oBRrkKqQIPoEDwPE8weFANIwnUAxt9AkZLK5lcb3bADJ3OU/IYbwMx0hqL1IugS/x8XBOMa5oF7DGS6TDRFGkEqYSdxuMUVXGrEYEhCxe0NCk0sIDgyso0Sgi/tFV468cC14anl4NOijG9t1SUnqnKmNYjCw1MUhHYW5lXhi82JAgbdyD0RFvTD6RmKblP64bc564GR4wiDeKdhanezl9Zyl0VQcGNBMGu8cu99Th7qg3xQQW1tact6+OapsXwr0lHHiXt34IXWBDY3ql2UKhx45THD5PXrxVb+4clhpq8X3Xu9Yo0sgSSIoEI2l7vYFzMGdP8XZrFz8awC5ftw6qsEEHnllStcUETipocm3SY6D8d8Z/YOpyWL956yX6L2A+yjAZV/XlnBGS9yCn0SARCN426FPBt07J4nk8Ls1dFnjRq89M0PzmH5CkqG6IDskdAHWHG/WRfi7APjbCp77edjUyo9Xl0lq5oZSpqX3bwreZuAPyJTUiATAhCww4xD3eeufoI7F+Ddb3Nkczrgt09aFdFZOTihU7kvZ/Gk88zI62QwAiTtQ/fZDmO7GDLiZT0dzcTyMJEc7AEBReksgUFZ/Gpqs+qJxpKjMqbRIVlX3/AoqDkMFB46exJ/ZZLLrv7XFCttHAxcM688LPjgKdMyLr956DPitdaAX65NQJFXamBeyF7vXRhBmumMgNJ+AsAc9t/45moTQWMOBU+rdzW1rEpgzanPxFZt9Ny7p521Gq/WLq88XFhPNDFgXnYCThz13VxA28OHZT8/IJh03U4YBopXF82dPjuWgx7PUvRQKKOh6sQxZ3JAJTJmfTh0Ow81dpS+4eVo73jr2fnnCSPG1TQx1/DliNHejTMzs5DgFVkwOYYXSL279/FeApsPmdgJ+903yo6gwgRbB+rrJd1ev4Nof9E36vj+w+twiHQBEgYaeyQhpiMRYG56ZKz7NHk37lBEWJ9gsJCJIZOqvocEpe514Dq1b9BLY5+QVnWnsG9nXTu7TbR+MW09AMdsNXlB8e+dUmDFmexZqqJ9oFJSbjvjMExYjNhPP+I1rLCHGUGvFUgT7R/ZRiuDuH4aVWzuffy9Q97S6vciHU8nxNKsP7/vsUEEmNdrQiGB3mlhKsIBgxKu9IemDwOrHVrXDxvESCInpkmkBJn1uSiQX47/9UGAOyb2K8W2I6vxaWFGs8/h3y95S3sDzpAkhlaTWNq5CU2LaXOHbFYoLJMAmpBm3gHARxUfv4Ej9ex5lWy/6cBZXJu5B87WXxOgmCLhWJIEpTpU5feJJdtzbQIjua79uWGo4b9l1dgVQZg0kUnSSZTuayaRsgTRvBXRg2KCAr8Jg1xpOdc7gfpaTu0FnkrtXrNZX8km/9JQhUbosfpg8x1o7aKJuuhc9CAiAaIAYTOJAWr+JovG5MywK2Er6SBRAFhFfrom1LIj9psSIYhTjevHppUGCr4DQRpuDSRbYbYoCqLmApq5feczwXrGwbfDfFNYj/taGWdc8x8Kfzysb+aubrtm5lBaZ/q3wqqsLFL7XEq4VT6d5H43jeVLl4v6JWpI7dCzmBY9iOzQim7VPaa5/ROfuJSRE9/PRSF8zRqt0WTMJRhE2TsdDk8Ws5B9zlpogusB7uU/eHa5Ue1veqSFFPx7Uj7cNmgSKcq7bNoWc3JdPreyue5aHYbx6gvRg9ypM29qaU4Ax+cQ0QBCIG7XiwkHQp/09Z1ICCpB+KPLFBWyuwYwPiFOGQODI+bOIS76OzIrzbExAkaGmHRmiDNqo2HF3AaGgaBNAQrjWeznYixt3Lxl24+44Hq+WnOUP0VDNTCutKU6B2A2UEnrL8jyE5dgO8lvPOxo8BAgrVVAWT55s1dLEMclUgi9rGCyC+NCXgCTF+OEbOo5VWdc/K3BaXqnT2R04pY70db0I5/sp/qAdj74gynwAoxQwDH0H2mXIn1Ywk4PdVwRAZIY3RqCbSJpg6A4PAWZYcIBAY2hA3+ZbG7Opi+1/GSY25hokO/4OSXYelUo6MVsgGHDxD0wh1WF/Y1n74dfC+sLcuX2DVLnn4Gnx2TFPN7DrikdMqIlFHHaQTvLMIlSojpLb0FZTxTi4+MfDTDiPoWQTECvY1l63Yfe0VOfENibR3nyhXXRAdAo32oSeiyg3e0HQaHgiQCJgplN4NB5xFClLBlpoG++zJcwFqwj3iGoLAAXXhVl3+2HuUipvhBUqu0Op2L7pVGvonabft7GsT1Z4Lw6R5K8ICNoGBm+zeUjZlznV28E2PNnsvAGpcjtM4AVFJRZnxSGpNyNnkplHjZgBhlkZS5k0LI7Y89abw9/o6RnzE0kSm3BK/5FfeUocGTZV/31LEkMGX3H7/P7U7N3R4w691k554B/U2HHUuHU/qH2vNtiIkH0cbyxlmxSYiCSPPiuEfjmlV5S6JC/WUFfkuwJvyLojKU/LRdf005wnAsLgkMkjpIxhSFeVi7PvO7CjS+0t4yG4IsXCb3vAvglXaU9XmAzQab5tFUEvDl7n5OQk3ryx8WtII99/Qto/7IG/3pSq9L7zIz7X1NQ0b8iUzJtt4E7Pa6ytLUX26A9pj0MimI+h8BcoEw7S6n3dv+z3netyFwHOrBBSOaUHXzMgipeDaGJ9d/WqmVJmJypMtFvMyaxiKN8FBo//OYZDQJACiAZFpwBkKITvicO4557iAS8e0G5PaZ1o7s6nNrDPCRD2gbjXaQ3LKtWn8xPIm1U8e3z3zFeWRmKg8BeFRc22/hJn5rwkXkmPv4Yb6v0+TTQC7ILaYhKqU3igYEj+OmltdZ+ww5koTLy7ee5lnnZqRdtCkUomq5HxVTS3mPVhPUVnYZxSNsrczZTJ5cP7NM2sQKTBj+7zs9WnZiMWc+ZFjyqeX8ySkWQBYhBP11dQ57RND6l0e7Q9Rrm7H8+HOXDVBMOszCOmTWD4F479U7W0dzWBgbmLMFm+1nPnq15y3vHkm9pgmWFJxf7ZBcEack9JGL+IRLPC0voBoPgMULjZbkt7efUAbFdZWVleXVVV4Zg2dcSkRlkHkBA+HgeLytXXzwz9ULsUlAahvJjxE9TTrgqSJR5yt5rwgNylINUpv0RbsVXr5qVUgx51tTWilz6OxS9+e5boQpaKw56CjwHK557GU5eXbNsBJb5DMt4sqXjGgoqGlpJkKi8DQrkISASavz7NUI2+Sv0p836rCgaByqLfD4omMcAUEIwEduS40XoBe7Kw3rIlhDng6YM2+OcL4WITPBb7Epsum4jiy6qFowrk7Dd6nSwcWsENNfg7kTOb8dPsbP9eSlD82ZKVAf5zsdmXg0LOFds0dUSJREmUIZXEb3hs0hwZSppfI++DYSpclygcvmuTF2ABQsEvTK1t3pu29e8fO+/Z6Uezhw2sUaYuzIprVjFOqH/cKkc2/ITNWxddKd+6L/jzLn7r1hTrfXqIfu7GflK69bNn6swJ9HxePoBwUpRAoQ80GFN+kdO/8iZ2nYm6MZuSQ+hUwaCJI0/XLjHMv586CUR4EVxwIVaIH0pdc2qhXeJBP9eGA1/Fg8PBHdRPWlbAPcP2M7q/ZdgBPDkq3RhtB9c+39eha44GVz6DME34J5cgTeCAJiBkolvK0jDeFKNkyGF6HxAWTHbP+E/cj4Qgg9K3Saf/9ciOW8r7W2h4flBlGQYD4pam304CGNwm1urUtXkQp4a5SS6TNINkRn+sGc0KpT/wTWF4jQ9KNGiWfcCXJ49Stq1Sx9bVe6RFORA5ZLy4EB0rhkRBUPqpQlngIAiRKatFVFhbsuY3m4SZJfhDBYplB4fZRQajBNI9ONK4ZaSTg1PQyN7DA2hSFv4brXF4oYivA4/19AxtfAC8T6LaGxFp8GE6trNYKd8GtlUZ44pJsqt1BeoPNG9FrTlbZr6k49ihM5sRDHnUsznp6AsDXcQmGHJz3jwcXtwbgQpZcEAgvfGt6T4B4SPDnbQ7Jti/iU6Qv5j6t08bRMVpJ3AUjiKRlvak70SEva1yqpPg4sR8Of64I8NZJcn+QNZw+3gH80aHnHpqJXLiGvLCbtj0Wro6NvvKSoC7AKSDjEoz73Iff2crtOFgqsKII3oHN6DdR0q5IOySGuXJtGrko6SOD2k9LgKzNzPY3OSDjJsTNMHEIUnqpT1Oe1O9CBP0xDIBpISRhbEwPhq28ovVO9kuH4LoCOx7J+/EqPM0tbAwrfMILDYESAzQObqlInu0lV3nTHGRh5HU8kgGsoBBfMgUxfl51ni9vjYC8R9zzfglysUUa9cISOY6hr/+fJhFecYsWo9iuQjFNpXy6u+IL6RcHRuNT6GIOvhJ39yG3IPagQTbQ+7oYG5jE97AGGU0XI3I6BMOM4+6QBcuwfT+xQiNao6PBTTTBkz67dovmGaN/vgH0TxpsmQ2RBUGNBV6Hb9sX68cCaXnoqh+5lQrPYuosBm9PlEqYtMNN4oWM2al4WDzj8Lm7cixjcJ2jFV4sAXQan74nUIlJOORNGL96KU6vPiDn0Z2NDyseZW2l7+YF7vMVWTiyMvU18eAyfcTIgT3CyC1QEAgescRYyDyJ5wqobz7ZkkoIbwD4J3FWy6wxrf/jDiLLl1YsMpkdj2tbHu5XZs2buVcuy2vk/5E/nFcsythTp8yY/66Nv6bzZ4d5gD3jrgXmg09+spLWoO4Zw8HwI46mwmn2XqZF6TAd7rxElTw7DcWYPn04UuZ0pGnJyQcjnFnZ7Ce+WIG/FPZUmnjH0Ui+S08pAcTdqlDewZZ/drDA3ct1K1u64d9/MajVPwaqzwCND09nYDkhVMU4kBiMfLVd+uNsxvULb0SB8Ad3gpPt7y83N2loaH+yBdZ8AJU3MmGLIXAXwx12rFDgR+y5y76dxxx27x1Eu4S2HtKlFjhLB1ugMopYFBestOJwdBgDGTkeFBN9uq4kpq6CURd3pulHqyFjY11Lznlp80bIC+UzlpSAwsPZUOxxLp3ccdhPlhClYsZmHEgJGr56bNTMKlgEKcXZsFXg9IwRhDumodPGR2PqFNgLFTRjoux34GPyLwYYJNtMAh9UEMsqO2WopQWGY5KBLi/Fm0Syho6cKUkFRWCYqJKxbA4UtkNovjsZ9lBiyOrjgklOSWyhM6VkgB1NCU0JIyeVRkOBiYvT1u+iL2izuRF2AeF4dB4KfTFv6d/iMHd6B1+JOvbDeMYxvEQIIRYQ7xAmRguiRirjMlSfvHz/Pz8/vjYdFDQwJBBXrwLgEwAtIxQeM7XutQchSeFJjVE/t2OL3Pgdo9tuREFXp1NGupseBuPDx4YGFjagowmkmc02hMJD1T6HHK3nc2IHJ6UYhqcCEdiAgBsGWVuhoCla0ZywIiAPQdMPR/dfjRm6l0CVtQSoT68tfVFMepovtMEG9rABguFKPm0zXOb6HLGvm2v1CSekO3FjBMFCM3635Yjz2JemGpa8S6qcKSEiFaml4hPFw8Io7QCcoB5JPjNy0bcT2rz90qJp5wSIPMh2Mohfk+OPuA4rGCOlx/9JjVcG0iRdIOKmtmJKSDYFU9HXAjEXptivyOl34SD0KpkV2ybHByppo8Q5FGViJuZeP73LGlnDVUKlSZ5qK06oczt9DScvaitdQBuwGEx9XdLSx/+42GebZQnnRligDmapDLx9G7QHyA8nYl0RZCg+QaCYrRSRf9Ca9GUsDKgMqNZBSpAaWaRVclwPet6Nlg9iCNIj2piDek3v5FBNzQylV2hH6xheVC/rq2t7HhQ5Zs+2g9gv5++CM/5RZ1KLRviQNGW3TyMVKoRYWQm/m7ig/39aYrBf0vyluUEUNUCsk2lCJAxKf5q/eq0E60mZYGCtgdV8yBBA3tZOzra+kB3L0GMLbBfmErSYGJfxboHlERVHtVirt/oDVueLKBj7Xo2dLWt2H8iGVXF4zPYm6ikhRF4b9ramyacWA/h0bgqritML09E1NcP/YUAITHYBNWb4EMWt2z/tlZG7vKdnAecewOKsJ7rPBFdQ5eV/LRDj2M+YsB4ze3zNVnJYeO3Pzf+0BCmYsBUEsNU2CvOznIP2K5FojzMRO5hKD971+vSsg7GQTmGCyQKWtL9XflgPjWUufjG0CEExd7XjdQQoo8ZdOJ6b2uI3LVsXsbGuRha7udfIMaYW3qzZvtzLQiKXRliLmzQIkYtcgq11owUXCyfkYvG+i+WCmm9s36X7t/p2xzhGVcdOK9bpG/sA42Y3qfA92F3sOZ+o2WF9pHYhm4tJsXzVvwRUhMgE7i3B13mVg60zcpyAb4wt2H3GKJSDEuBUts4JTdAEJT6cyeVBa8rrlnyZmr3iQZkjk1dYOAQD7sffOOWOam0el7NgcdPto1NgmPnexMAYSQi33PiZkFPtd5yr2zjlD6B+LTpmIX7D2gJHnCJpoWubnvadVjkrgav9L3pRlwEetbLPb8rnZAZc+3w+uEJdlPVNCeMtGu5A4yX1see/j4H4BeG/IvCOfgELZWEfjRmy2oEdvGiX7Wsm1n2JcrEtnPU8hd4uQBfJwS5UGgUzke1prg93gCf4CXwfoYIGMrZmTVd7sybM1asiIA57NbxP8HyfAX1NIYgIo+PVuyFi0Umj4cdBIlM2kqSpVvbv+mgTF90y3FNw2IukxRS8pFDIq2iVCQKTML3e6Y4m4odQoXFsWrSJmyFDJJvIh/xl8gkHsvHlSb8oWIObiiojwqEMZLjVg3ceuBUj2J47d1yxOySf+pIPffmyI3GHdgbvPchxApoM14VPrAE/jmhnFrw4qTRo1hDJ2TPWcaU2IRmUSPGcPZAmaCYYGSixzqoHKJMt3+dYPUMkft+bDd2ifFFd+2cM9F4P3YyGXJJR7C9gurAS8hMMRnyl+c3AOGhEln+y8XZIB0gleoWSyCtdQoj/cmeSVDLgAvuPfSiQbmb9j7pr/Pe4TaxIIT8J4SFDLKt8aO3EgBvrZx41AoVGR9G18nao1Vn7apI5q0m/3KjzJtdJHBQ16r5EvHFPeB6Aal2ZyPioK1a5DRpwWXIkCTPqJyPe/A8lv9amnqJp8Yq/deLFtsEBoq2nz5DIoKFEmSldoEDU8pWuWE0oA74
*/