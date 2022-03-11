/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_cv_hpp
/*`
[section:ref_add_member_cv add_member_cv]
[heading Header]
``#include <boost/callable_traits/add_member_cv.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_cv_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_cv,

        detail::fail_when_same<typename detail::traits<T>::add_member_cv,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_cv,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_cv,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_cv_impl {};

    template<typename T>
    struct add_member_cv_impl <T, typename std::is_same<
        add_member_cv_t<T>, detail::dummy>::type>
    {
        using type = add_member_cv_t<T>;
    };
}

//->

template<typename T>
struct add_member_cv : detail::add_member_cv_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds member `const` and `volatile` qualifiers to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_cv_t<T>`]]
    [[`int()`]                          [`int() const volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_cv.cpp]
[add_member_cv]
[endsect]
*/
//]

#endif

/* add_member_cv.hpp
bnE/B9PUQ1+i2NVgyuRVztDEGb1JCETFMOVnIm/pH14ucuM67rSZFl5Fn4+0cHQ3LENyCzxJWLpjQXy0IFsJRPlvWl8VkPTO7RcNLL3GRdsjauquIMHbPAyEQz50aS/xyK6UbVyxOskrwM/IvIiQ/EEkmuHkSJK+xcKaaqEix7Ev/1By5vZ6NCZulrSvMyV4PfMGjAJ9eGO8yjb64gcoQFQi2plz0fw44PtNewb4RpJ00xizW6wyoIrS4kxZlUJoVP9Nso2kOQ1FNMbKeS0dt+x3sZVhoo6cKmp3RoXKKU6sMqJ8H8zVROsSL/ByYGEVEByuySxfzYaISCTKnMxNA1fzV6UFcI04MxVVz4RBBBJP26krrOeBQ8bxq3BIw0cV+SDtSEzlqpG6hoMhArjrvw8QaHiuwElRWNsQpeVTZVfE9rvl+lGRC4Q1wtxamDWtPpWOTyOUGOkJqYvQkK6OMYYvucmwTYLfKFapZitxGdiI0lhEZQRupYF3Ck/70X3SDXyxzk+DFAzEJ/GjOxDy+allovSpCXwBfcYxum3oRtvHFWgHt38i0J8GiFYDcrJxmAWUwgdaTWPilqY4NGIVjOUFNia5pl7ZTptGoctWK8RbzEI9uleCpl9BluytldnLBr0XAEeU68il+/J1OTZUOXF0YRzu8JBMWftPVIHCvkbSZqACKcHJN9iubZLjShniOFOSXbCXysbi9w5HVe3DGgwum6vq8M5OnQCwnqXvDMvIuKVY0U850WSaWiBc2/cQUnfuk0yyUHdm5J+o2nwOaMEUyo4pOyRdHFfT3wSAc2v5Uv1EzeSP+08uYOGb6Gvr084fKO6GdUy3t7vNIpksfnxNNgt1ZOEPk6CDIFokkDcWouoWTeVWm8ByKhnm5J4gIgbQmWtvNZie4LX9eHSB+0xk+aZNETqT7JwZJb3M/WT1GUzi1whO4zefOyL4RV4IMapWi7PleXHIw9ydO3ErRMW4XdhFMOWFK+AxE9hZjhE6+D4xdGvD5M+sC/X1PUP0X7dlsrllJ5z0++m9B12VT+hCJM/xaAMAyQjAjKShOGGDKt9aU5KopVUQnm3ZZY/gcC4paJLf2/+gkIwwHp3uFH+/OqekciYO/flbgaOYzTxkgH+M2yAMeHKYKcEZdRvzzCPa4SMqVZNRIkyjsIasFEnZaOrRNOzbdoPx3ZVZpzNlQHyPYLRmyP/NJ1jyEqHmC+AvJFX85eRcItD4B2qkJZurxWZjenB48HdoseFClrUmR94YS1/72Npxmv7w/clyeddNtXRRc1H7am/31FnZ+oIrDN5rbwN710XSspFVIdVZxVDbAhCKVkdPAvii9mvIG0GS2sOGOkjSAnwaI2wI/vMB33UyKZRNqyVWkwMkJSk/596DI0Z25TodXioMMQ/iGSoS15hjBPLsb0wkLv9hojo6B0YmI3Q7B0zLAp7oUXmEUUeYkVvEgSoOSmp1G3lhMg+hVg52JI+L6lzeblQH4MPvdah/K7PaIlhIw4wKbp5PTMcNKxQofsAfyVFkaSVsTBHjZVqn0R0dYeDll1W8mGfFzTUGdUJA/bCj/vknW2t5aBE7YDpEI7iLTGFodLNkp7Emx48h2dvHIb/8hh1yGvHdbIJohsWqOQ0yI86Ij8sDqzJ258zXLWFYdKDYek4K2g7kitaS5s55PjhiDOprtFnOV4zLDAMmPDwEhMQ6yceH1EZcGCPztKiQy/+b4UxGJlIFLRHUG3K9kAC7AFNEDgJ6Lfp5Ji21A0Udxsrr2XHVWfZ4JQjeUDXQA+8wwXk7gQMGxR2ywXPtL7SSlGS2kI9kYsLfwYgZ957dwkAgybLMf9/q1RS90dTVTrCYWXukXEpX3BQk3DUlOKhu+aSsp+9Xg1hFumfqgkgSb8Dm1S5JvGWNhPUItiK5xi32RXWOSh1FLRU33F1VkTmgWzcY57eWxVD1xEWt4Bo8+bfGtbUC/YUiLCdkV9jDeptbA47yhw/Mm0hj+npeOiuXqwuhdOwUDOwRLJNtUM3Cppyt+zNJzWqmKV6gTD16F9W1ISbDM84k89PO3EgYTXY7AwoQkvcACybeScFzfCJRKaFJgBkxOHiTnBVFgxTwtXuGp4TRBg9JDotwwCRSs3zWtO+JEBGwMnWG+DFGHJw94aqSSqCb52ZRNl7uGJ+ef1PDpns/rElgqU1ljmrw1biDo3nLpRXtwdAp3WSv5t/YMixA7aPyJDmMKz/fAk9OovhnFkR8Aoep1rXMlZLJKPlUEA8vBCE7fTOtzxwXZoxnN5IHNSpEKLxSBsGhiE4cjbaGrKPUrTIWwYjAM+0RpbcDIKZG/P3FGJzSX5kgFwv/2QhBRospaTCUS1y8CeChm+GDJb5QZsSz84JzjI21dq51DwJ8GcQApag15CXwVLBFfNlve4XcxENiWkWurHOLBncGG3aHtQrVsy3KUiJpSteT5hQiddg69AD5bB41XhzATCTWjAZaiw/KLSKi6Lf0n8EF+MMhKxpGh3cq0xgP65V95ikJA9UjmLpYlrU2iZewI5lOhF+ijCvXtONRP15zIcwVUg0LW+N7VgSw0IPH/auUnqLd920Qxcxr/sk2HYSSqs9SazHpzYbVjnCjAP0jR7OALb4YNoqPSmXCtcCA+EWFRhmjQcvBPoaGrFhUJp+qU6A6QgAV2i91uZJCIjAnDV4cP/SUeIi0/BoeD/zjf9frDbMPIbe4JmyDASUHA/cM2j52OS9j8TgDzhuz0H+wQDQstSjhLGeggDmgF+WKyTV6XzOgGEQ4j29HCaSgtmytO2Pjcf3pL+O/zM5Fi1BTJgM3So0bkaAVnZd27987PfcjQdxuU+HYAlbup2ssxkdYIMEuYkE3BNiDSN+FsIwykn0BHJe7Z7eN5ILv30HMmFASa2jHFQwGaS7ULxZBI4KuOiIi4DqRh6N8znCUBXg7sJ1TNy/N/cl6TXJPT5MpQzoWENYrKNpxknQkIdjIUtrWFaNlWAJqzGagvdNbSVLMJeqs+5oZhnuTFwEXY2zJp1JVsPDVZ6Fc3eegFT129j12ibuaUBAf/++7sJXACYobHnpcRvWMom4MHhrv+J954PdbWRWdSnB3TvmoyExRA9KwDQLLeZnG0hI9T5W7L0bAx/Mdv5h8dlCYuNVzHadyxaq77tFmbz1YggPB7m8LsclzZKLaUqZTQpDYB7ncKlox0mR7K0E2fZl4amq+41sEK+BZTvDBWrojzCGScKum8deFB7sOA9Syg5M53l2MBPDYJ5Wvvp4v+pWAX48chdMW3iOIwSTbpW2nHSJ9eXBIMAOZ8NRMWTeFR34S0kg2AK517ifLA+XUxRYYxIcYD7lFJcsLauPFbvsP/uywc8AibYC7RDftobB3Ud0Yqi80r0MMottCRX8kMWAfM+FDH+Hqt3l7kL6+VL5A4FgvLi7fYI343kuLTyVDKvMG/+pFI6FGCeVM4K1E7NhfZ018eyDfihuHXOFT0WRCcQTxeDuJY4rV283U9sIiu8YnBIlCdsVzFc4uf6jogfG78+p/stv8JOEWItuOyq3cnKieD+1DYSd+eOKOFTYLh1fdWEFNywKWcISIvDr7JnJXBzWHLB6gUdj37VY9ap2AdmFbtYEq3IcZHDXofMfX4n//RVkov56PcCnLowrugqGfCxpNn9lRPI0t0oeqrJMokvUySymVc056oyvGBb9HwHyh6fLB0zhazyCiolHda3M5/kT95WjgZsi5lQ+hWTxove8UIf9ajVfn2l7sgk+JdGkvMGFMWGO89sHT6nRS30xteBUFMjqqcVKukbN3E6nAZUC0RCS9JZCeMZjT2ef4e3GNhEaqXItOmWLmmZ0nz72bnoMIk6jYAARydK8oB0F1hdS6A8cOq7DxRfqss6yqpM3JmFwABVCUXIBcL/iP8HEDwTQ/1+iWvw6TCf7kVWDRSo5TJNiizwRrwUbjSgYLoYuusr+roxfhiKUKSd90l1KVROdcdp0dt5Wh78PFgNv1xosjzrU9lAYENuRR9I0dnSkXvgfMxWI3WwdZdYufCqmHKwysTJjphZ5SjjhnzT94ua2EyU6UdjSBnhk28Ey2M4sSvgk88f6vPp4CXjGcNXzSY4+wttPLC3h/io1h9pZTkn5VepPun0TPyGX+QyhimzPWyOU6Sc8k1OqppbcWKH8hdNpCvncnNNChjtO6P63YhitbvLr56zUaKeAXsnyFV/I969a1KLnGCae+OZKFNhRDhIhiBFon1s0NW8CFEJX+YRTaceexAhr9Mf9GsLwmsK6cJ+gurWjicVZpD3tg+wML6Q/FqUaDwWxHJ3yMSL45zz9bUirCSXZmv4OsT+J0Ecvx9RjkK4Q5SOFmjdFUMiB6CRPQxYaPSq+I3/rmv5Yz/aLcdoDggw74qgO08nRXEeiGfe7JC2n++oh/BBp5BAbGrOOHfadp9BnmvMriHkX21xuQqX6CMtlAV0oLSS5qvJzRznIhofCTiUEWQZUGFwn5rblZLB+h9vtolb6fBTW+eNVIZsOfjO2SvYcl3IbJAy5AU2/AYBJZLpQmXwQQlH9WmmNJvAZsgWagFiDjEBV4tGkDegOtR7V0Uf5LaYqvkCDOhb81jFRcjc6q/igZu8q5lC1irUzJrktxYyQxFN9dP0fxIpzKUaAmGeJwy3iLbgKZn4MXyRIvd65ZmiZuGqVI3U7QRxrFyj1eJKIAiQZzKSbUXR5tt07/E7W0sE/H1YL5nYonPMe+Qz37DOGjuRp8Xsqgx6GuPK/d2zJuG/njq/RusCHEPg7wbrAADcMIM/rei7P2NJOZ7mmii7FwWRsIVIBpJdU18I8YKPcImgiJlZClpEgJjDnJa9KhCy+pqTp7ohmJlVdlQ7Pne9+Ed22UGNAKczPxK1+CArwA4bnGu+/4EsKveapjops4vAhxWZgcHoO7zSESYpwr/irEFehsatXr3Z2LXoTSrC6Q8umLD3VWp93ZiIP//dPDzjhmwKF6VQm8VBBbIEWUZ0kF/QANSdwfYgk3wqCsJY70nzpBP3jgPwEDAL7g0BxFfRJFiGXIpv0N6BQ4nvMJObxKLlEySJ43QcrbdVXtrQklCHHxlHUcNeNpSQAoAAQs+9N04sJ96qTb/IUIGCEOGCd9rPwSzGIoQVnVP0VbAxTtrcVlFhhGSJWgadPYmXhUZ9Jj8ASnr/7TxNRdNpWtybQPTBn+/Hme+wUShEF/4I+vYvnGVwWv/e/eCK50xZztRbdYeDxfIk8nUVs+DSbdTpPysJcWdtq0TM+Ogw8GZML1yHerjrY7aOlnVS6TJDs4t/aZ3PN+TOK2QP+ZLOC1f5aZ5VtRjamKSByIolny/QMFvY3EgZVjKC5sA1GkIeTZ3+zZYjPgkkjxztGvXpd+S/gXr8QFkcUSKH5mtG95aJNEyhGSuLR0uP5n7AFOa42BrHm8biH4nqD4TG6Mw3acCI8TsAbmVRf0jyn2zniru32kPaoHjdAYL/Xe8t+lvkK8dfV9ISROSOHzCOtYXudvYU0GOb6Kqcn5CeWvSzuI2MMNm4UdAR1ZYeanLuFggvIEq4jDbTpBuqJHKJFGi5mMKYZGevm2rZicN/9/hBxQkg4I9kIZdcb11IWkmrTrYkvac7RDc28Qib5YzLkbeq7dMsu+GEl7w5WXclkZRyZ/tluANwtWQZyHasykd6mW7NughS6/jxknUmK0wi7igF97MDWxUdrgFduBVEXnyvsCLHHW4bvCR0qFQ8E0Kw4JLkuOaUyGEf3K5RLeaPNXBcNHJsaPzMMsAm9M0DZ8IenbZZmgI9oaUU/xUZY1xx7PUJn47EBzb2eu+J5/oIr9j6qhj3vjzmytw6SSDENv6/b8YjjOIZn+pnW7mvtBGh9ShkSKPSr7C4VDLVOysMqN72e802aKyINSMFCRB/uY8/4Lpo2lQ0VpkNVNHEaJTzQtHwxB5K0+8NpPEmgPgiszXyYtthCE2LXw/iOzfr1pOFMF1RoRqniX/qA9VCDKSeF++JZrB7jq8CLCfXc2tDK+i3vdUMzs2Hx1PR2fttSbXHj6V2HxDEbuYloOE93sA0QHW83GV1iBfzujLbWiqZHQliMBPWzT+KLvYSTntkOz1MZBV6aGlRAL4eBb9KNLQNbCjZzmARRiPiNtf5AEhwOr4C9zocz5Ri56F66kBW1otiX2h8yusc6Vuq9C+QHIKL4GAa/nWUIGfjFUrur9473mpLJgjhoXzexxPfC275fP3nLZGqNMLqP5WLJzSN3CYC3+OIU+4qycEDrrO9cjR+HGN2gUkDV3xtOFajgnWu+n1SwacZCURT3ngA9hN4SgX4PfwLuBK/9o+H1B2vNslKQ+8f3eE8wXSzFkfbqSnypbM67ou5ISUGKkJV8MsqugY4pJ0rDvn2KdMZ4sYlvz3GhcZGZaO8NjBB+FSR2V0dTFBpte4oqV0ruzRfb7WLK1+7u3uzmDVgJBYIvLEhgsDG0q5WJNDlP9yXWqWKluDhd3eq9B4Vq+loA1HgX0zJuB0vEf/Y+sP3og5MBdGO9V8eUuUcl+hL89C9t7CfuMT+Li1DPmoCGezzHOFouWqZzNOSBXtZYu97J9mqEvMmeGp8MwVwnfK2shjcd2MgadSCHLronW/keDTTLs1Uwdv8ixjjrtsvkSkhnXD4w40Wj2PK+nIEMmEAtenTHd4jfQqlYogIEVScspTgzC8Vgeg6khx9mxDMdMjrlvYcx907qCb/No/RkaAxbm+97fwaMhEaRKd5HyW0sZwtSGy9HZlL3gtjD1SaTgVfJyMWHyK5Y1tGyy4DzNJcqgkAPzZ1dhrKgeW+Q7b9Pg2IA72WcEf4ecrUoIk/Qa9HwWoGYR2+z5lIUC4lgMaP3yJ9v9LUIcaVWBvAVe4FvNHDePPjsvnKd2gl2KgEL1pSZReGYbbC4GrPOime1yd/X6vDShqWWxLS1/IJ0OBIQE5sBegdjhBGhQ9Nw6ZZDtWadUi/ako/mNPHkW0sxjBBXhShyx3R2UQN7oMdZFKfU2TvneHK5anfIAlXV2f/qTf6770ENmIJk8OrB3CilijfCJrnH2nBJrb0hxsO0XX/KnXc22NNiApRds0IMuL4iDOqRSTI9J1O1sF3iaYwbsKtWKxfwc45I0ECjsPVqMocHNgeo6C4/IyUZPVvqdfFyontsuZ07aRRYPgqnT1VaevuWLpoNVD6o01scLR1nNUPEAZ4zrXU+oIQnC6xfpArCkHP2jjs6v2T1nAIxF1KOGK1rxA4MFdEVYHcr7tA2bhL7znqvryz7CK9XiFik4oxpUDGVQI6zKESc4Q2Au/tQzf4RhVbY7xbFlOucCtnrocr2U+1ykSUAyqsr1aiepcDrkrdNObrRheAkrnZt6ci1DNqFlsUxlv1wnrr+b+H3C47MIE0OSLjpiYzx2A8JLkI+e99sv1lgllbY4+s2fptOQORjkXjzEeu8Rb5xQB+NR+rUDLrSyoLWDCgD+2fYeh+zLwBAfCOPKU5U+lkouANjimVWxmWRxIDgGNh+j54BUluTo01xf4vLS3tLBKFc1F3GWitRFezGvFyoKv4MmkzH6dXIhKEOUkdDe4QzM5Wt0Lz4QxboGaILlXmbW2akzKakyXBZd4gkHC/C2BNspwMi8WW3J53C6p3QTIG2nHbBsq0l6jqyYLGpDcZvBhghaFAKl38hjCPSUa0VKv127ywWuKyvibObwk2DWFLYNLsmrqhQ9UW+uYJVa53qLpT6jrDM/7kS99P/Z3RqFt1ehM1at3H3pdw+jnEL7LNhMt7bC0Q8khHAEq1ytx/AaY9oPHyiRjF6hlYLhtvSzH85EnBmBPv1rj202KwADGVnxzXnyCAAhsLlQWU0XG8629ZGG2iVisOARt8OWdeNO0zf/DHmPYIzjSlKtKINs5HGpvcX4qs+ERxZx9gQ7dE3ai+rXBTz6tvXp3fqAhFJMb1HFkUQFNIMUW6KE/gwQ5sgBIHMvLm1m7j6I9DYz6R8/w6SRwVJoaezVGjTg/FYkj00yqY+8rymWp4L67jh90N+va2mC/1BloSXWzu/XZxUoMnqeM9YyT007SP1OgDLbp6vPw6HMtmqQxnKHyM9ysBsI4zmQTeBGHo3eSLmmTn3EJLPzAt5eFtEtzTOdUwdJfp8nd76ylHyFWsXxDi8jkw28vNW6LGPREPgdDZjjeJeaC9WHkhngLOTwackpnYESelhnwsWHp3duIl75obErPm0//GkULYGxRzqefnEuyjQM7m59MxUxVxSwh1tkzIeg9LkkxHmDz8qUqzhPworuNxKNidF6a4C4MLEicNgul8lCQ/fR+JN9FFOkKZhd495i16ILG7if8Hik2Nndd77AuTeUj8iAdfxqDU0F69kKZLEIB4vRt8p8jriC8xgUQxaXwL+9dMHqGLokkIXQHj6nFMKkxtXvl84Iei0LEjlNZ3E6Ii9hU6ggiCqjDvCsWeqwureY6808FHgE3HvoMNQi+tfc2AHjPDYiMRRZ7oXC91AVN9AlJ/vftdDLGek42nITgoUx/qHRYlr3xsgMmDlhACp5liUkKpNoWiCt+fkLWInb120KPVyUYz67c4lBUPzcv5PR61BikM8ihejUbpm8nZ1GhFzOicYSECDRQ8u5dfKCLyd7vHPtOTUVlH1+skQJazv8bBD0qxL0PfNX03KNWNOr+GkEY0jD0VYfHzMFDLH4j36rfpVURbtmem33DdhKc0evci4NOdi2p7fvaPFoarNcW1EiWVAVErDHBahNH7ZUuWBsOmFFYdmlv7aZ+tsefzNAYf6yqCiLUGgAPU3eAZ4RbF0/kA75artKXx2GuB3CYZbpZouX4id3H1BEuwl0GIg3ZvXLjNpHsY47Mklg+gYnW+Yd7GknYLyDrsd55h02j32cA+zZ/QnSzHNcSVKTFjmJpsSCQUsJmevra0QejpI14gnAA+Jw8HR57LNtlptoxB9JHE1Il2ZG6+8WHnlwwZWzJe6yNJ240Pq3soOwrgjj4tGlEWcgz1Su76IV/CMCKQsiCENVwPh44dg1FKn4OAOUwY5G2AE3caf97BxIxiwxC/mwl0XExmxf/VJwl5QoVvY4655FafZX1TpJg6UyjxUSYdGNPqycwL33Yh6aHGW7m0uCqkqK/nmPDjeM/NU7UF4pMhFafZDAU3mTYOmPK27E4ROnFmUwaoQ=
*/