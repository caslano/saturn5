/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    flip.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FLIP_H
#define BOOST_HOF_GUARD_FLIP_H

/// flip
/// ====
/// 
/// Description
/// -----------
/// 
/// The `flip` function adaptor swaps the first two parameters.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     flip_adaptor<F> flip(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(flip(f)(x, y, xs...) == f(y, x, xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be at least:
/// 
/// * [BinaryInvocable](BinaryInvocable)
/// 
/// Or:
/// 
/// * [Invocable](Invocable) with more than two argurments
/// 
/// And:
/// 
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         int r = boost::hof::flip(boost::hof::_ - boost::hof::_)(2, 5);
///         assert(r == 3);
///     }
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct flip_adaptor : detail::callable_base<F>
{
    typedef flip_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(flip_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct flip_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class U, class... Ts>
            struct of
            : Failure::template of<U, T, Ts...>
            {};
        };
    };

    struct failure
    : failure_map<flip_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(flip_adaptor);

    template<class T, class U, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<U>, id_<T>, id_<Ts>...) 
    operator()(T&& x, U&& y, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(U)(y), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(flip, detail::make<flip_adaptor>);

}} // namespace boost::hof

#endif

/* flip.hpp
x45tcZBEXCJntDn3tYsf47R0bnD8yZGmLZHRVvSNdJv38OvwsQU/PqPoMq+TSncBv2piWKU7181f/zklIUZlrcXZgcm8oIH5r0c18FdsYI7ewNEJYVutuS7uxwY6+YOTT6quMvJZn3OCrsJZlnNAgzEes69Tyjcfe4sSmgvGso+ng9CAsYd1PqQPiv8GPV/yTM53lTtNyp2SbyxLd/GeahFC7TvW7v+qnL8Pj0zk/tTSfhuH+JU7u4TdGWUOL5VRo1yGHHGsMIcbA+/qzPyL28+gB048u1dmD8hCo2jB9CTOAWtgls5BPUvEqvenqC7Uz/JmjjH4peByifTi6NDi6fszMUjN0mKSqDgHhcU9yRgXEgnuAAwqNK6CvrfDd2zrBmgLtcawrrMCbb46Rm+TPlZJLiUVNZ3wMdowrmEg7zR+H5p5oC9BJ78QhiBa96FuCnYNtGsBZKfx22ejmR466twC3zJ2gXSJvTi3weHf4V8PZzQcAQY2IPfacj71r4NEitDwMe5feFQli0UkxutwH0xnZidOJPrvBJ4BUaXvKvgYSm5HKZiQTi3v2MOmyXM9vAD2eK8tmry+xgrf/kmrsMYeRV4TbrfH0A9uWjdc/kgS+20mSFdFmEtkr9qiMWxg1++ZxKarM+xs/utZhlclBvUHtpwu2PXoGbrWCpah3XkSD+pImtZVL2EEyJkm4QQWYR6EBPUT2LSvnhURDjCgoi4qjnbsf34ftWPnmSpJcZdpFiw9dBFQy3ITtkq8Hw/jLj4e7+fZ++pvNK6fNd3ZtbChL5Vsl3QuDwJ5BNNEBzWkGDLKR7NEQ1hxoN21nQfL9EFn0V6AYQPFXjBxUX941GIvsL8p0UaEwltmBMPNCjPcLOcyiiqaZW3EqwjNf6vUpi+zPMDKedAnO4a9wpkj0I9YSQCs7OUH+wEriRpW+lmpBRCDh8b/B4YDXH1PQQCAQ0vVfQt4VNW1cOaRZJIZmEEGiBo1ldGmktbIpG10oiaahFECTF6TIHnQ/pjGlNqIE8U2icBkcE42g1SBYoutrdxKW1pjpSQoYIaETHjIU3n7AsUTIm9JAoHMv9ba58wjCd6r1/vd///4mMzss/faa6+99tpr77MepsQ8OA7Dvsev67pvZZMM5ANWE2ET/bgnTtNRAL0kqOdfLonzVHFW/Cl01iac9K6n+KVP4iDbDdNQ/8KA/qZcFvr+rF2WzxtIJAGT9LMuFI7I7tZmmXspzEZaM3Fvpbh7VJB7i21i8UxjiA3uCNpiflFOMkfJemV502fp1zfsDZU2+oY2+Jm6kgJ56xtwSUHL8TeAICmkHKx9GMkP5lpYSRFJhpU7BXFc7pjERy7KcsckTr1IbCV2HOdyByYXLxwSLG0dPLqJwjELny/fEy6B4lACpUELE86j2Hs+IIFWlg1I/Zz/ElNp9+WT/IkXj9tl+XMIvgllOt4P9lizUgoeclQOHvKXC+RaZ+jivuPvcvvXPtJEYUxSVW7SKqsIFO6aq6nxZCFD6mmyEIevzZD/LdulQQW0UySCVRRe68GEUiXob71DULApERhxGubMasuFFkj1SDqyNP3wCiZwgUaZrE+GJVb9pQeO/9JPpWMsG0sWg9cxX/dNsLTFqmOkivq69dJ6RIIWHqNo3O9x/UFWF+a37+YbVai/gJyfZe+Oq367eMIenp8F5N/ty4bqEw1kLM7OsTX08tF1Cki2VI419RCsLVgs+LrMoWOF+D0P377dVZnQgmHz8ONosxy2bUmz/P5XH2RnEEkCbLhFVeli9rRQn2yeRlnhGFGIr7P+OT0QwHSqzXJJehpmJCDU48ssdtVySXrTGVKBv/DiibSF+pwgpULiO/or/7BsqPxPRPnfBZsa0xSZ/UUovEVFyQBqeFa2kx0Uv3wVJn0k+mAkotSHmhZfTRQwmLVbBwdlcmiArcPamGnKwbeKp1F/jqxs/8edOBcn/qMH0w3bkO+WcolshbPbwk5KOoQWiOTB4ZgNfGf1/FJh6XrSKMlD4+p5v7o+whGZZemac56pW/iuUYJhdAyre/xVCfBlHIBnWyb4sLAfuLNqBHxRQqHl6pNjSPplYB92cXHBgH+S5eqcbrzkQyTgMKBf8Cs8CKVXKStrObapCA5TT8P3NTK4N1f1+DnaT43hKNvF+wGcBGVOd5Wm8hXevg+qVhnE0imBt9rmraQ3pDtSWZ3a5ZdeaBdqJhzwXla69uKd4RE4pshukWhM0YnhhzfdfIXkTLcafX+du/yVs2roztwElM8U3/mC8gkamCqQw9qUy7bD3pSjIMEmiXfMGJwuzj91WZoEx68AvU05Mno22s7SKZLZeFZoOJJlcO0dgstEjoutWyOHEqn84oEQZCZyZGwhyCRIyKgCyHTfFmgkKrDBaH6ywGqZ3Ar9lVCc36U6cHwLiC3MPlDZZJZgbOyG56pgV5nc9DwMhgAwuJ0btmDdg3qNGtprEbY4ep/UYvrgFtFDW9yGLWp/KbX47uAWmqEtLkAdbjuILS6eHNQiZmgLL7a4IrdoG9widmiL57tDR/6bwS20Q1uUQgs7qNA/HH/F331PZQsfUbJYKLdNktrqQtsmUdvv0KihtT/PSEtm3p9o1YM8qLmtKraymK+Ow1CKof7Rx3rqKml1FUJhN9qiGkEJsZp7XP6nbuD2ybjUmkD0RXCbkWxLL6xe0FjKhVJD6HvHFH7HyO/3mpYNF4LjHKVFRNukmtETW4eY4GOysnQ15qubqwGBYfE6bsGoRgZhFNMwm9om5KrF39rwZRleu1nRb2qXfA34/jSQBAY7iiYN2R41KUKN+FucMeMMsj1057Jr2kOLN/2GgtlROAkjD2WXCduL+EPzKIpaIARu7a+RD5Vu8Z5Wo/96M6bEUNvE49OkbFSyDXdZ137YDoLxQzv9IfFD/z0tLH4oOt8sGy7+JbR7ZTudP9Xcfntn4GIqtRPfdOCTXCJImUdnEuGk5QdG+BKL0fGUx+dd142SVpMn3se7hZoBh8K7lgyJRMn9ATF8poJf991EP0BhLoHjH0p0De4BP8ZB8jgP9LCatHtqBjukbTbMtGeqmvyWbOLhz676gw5vGM97+dD5qWzCTd4R2OkxqjS335gx0O8HRb16ElfUUXsKSfVGunpid6iujq8H8HJ9Z4AKfTmyHxhaRwXc3UKNwAP4cf7e9tuhKgxmOZXtJfkLrClGMpFlWRphyjy2C6+265oEVxqaRr1cDZ++rHai9HMdcBK1kXPIKji8Vp64TI4uq2zoIhJ0D5G8oVbJPgzJn1M9Vw4dtgJeM6+QTw8IMDbdUGksJ6jCy1hJHHmCxAhABinCHT78LyzhUNlZGe5BqAVK3D2V1vVoy1SAZe99xvsq4H0FHLRIAlEVufXvoHXl0t9Rt76sDfhNXP6Z3K9nyspc6jvcK2uVUBhweJl+gvYUqijbjdOYkoAv2ROGykUcuJj+WZBOK4dzpAqFqkKoUbxiGNTfwXbCniEnLqFupXxRqm9YEI0j+xiObOJrizXk1SW7VtlqBZeVhtxKOpIHf7CsVotX77kbwY3Duzp+HJ6yAV+9eVZgJKwat7joU05H/A1od+aSXWuUNLdUDX5HigUSvecOhM1tJ2K8OSqEDp7dvEm0eJcEejeBJitlDl0ToAhVFgo7qf65T4kiniZeUSYKdXEj70LyO0LuOCj+ydCLHcWY/Zb+uh8Njbn4wbJiOgvNMEYIWWs9WWsBCSzJxblKGdnrn9TdwWrclYnJiPY8IkiD+OvjHOt5HOu+ANaxkvG+gT1MIQ5t7Kx57zuaJ+40rEeV4cJfOAz9UrRHixHHw2gajjjyKuPnIPhEyp+NsKe4mcKzDH/neZbhpTva1mvDAgPj5kYDOcsbAl4Ecxe071axmobKVlT7PBgvWNx2jJMtnoa2TAQcuHGyLmCvT8+ErE4C0igNcOkwM7lQzWdyZvWdkpGgULNWrDzGW+BvIMmiAElGBCeS6hbyHhKPc4xqh5lIk5r7WsDZxeNCE2ib/wV+0DT7hVTh3xixg5FttAXtGkcGjjkbZ/v5Kd1vy6xSAKuuys1l7Z5lWCw82pLHl4awEQEIyWL7i5qIqiTgks/RUKYTFdspLZZdjmQyQqvyo/W32e/cpmDtwn/Y/MSyBqGwXdiIP4RU0WnswZsFDaMCc4/w71m4LWa1K2DVjUZRPoZNaXd+MuDyC1PaHRoplIKBFTbhq5pk5iGElYBbbr7N58LWJFxjv4unYEOVASTrwyHIkcm10XEboyEdceFnmNqNSvfG665Ibxkq02iOrvDVNlps+xiJXsRLgA9wK+F8MEbS+4N1n/sERCKf4y/Qd+A5bDtlLYYjWIYFwJhLBjhjjpUbfyE3fhgbp68n60coGCc+dkcXPokz94B+5hyIqkshE8c6NHGse098qgrXX8uRrJajI1Kh2dERyfgZmQifYkyxMcKt/nF2t69y6ZOIz1HEp/cjwKfUDUKXfsNoNDSa7dDN9YNCaA/2oUGzS3H/vV1+3hYRE38L46vSiUfvl6ntKUHiIsFvcIwNM8gUf/2RHEdKwqhdhvITfKKy85JcyeGDcLpRJlKg7m1I0boGS79jDnT8f4bpOH5wx8rBHa+VgYkfwpNoOy+BjlOpY1weN8kdB+qu+YiGeu6+oT3ePLjHJR8GemyiHlfJUJ76MMgQqzhDzJQk1S1yl4HKd0OXIZ4GDVncjY77ZPiyPiU3uqz3YFuaRagwWuSwikaGRIFw9aDogGXE/UUBy9WU2YPQR4lNW8R9Mb2wclfnibfwTsytQtZqIWsNy9oAgsnBwVLkuLUfcFE7yuPCYvS+ulXWDhx+aVN7FodZt5KRMuLPau3a3Of3tzAj6OYtJ/CTCxV5y06fr8H9M5dDEHM/ICWCwycdYnyICuIIUUHGUT9NjJQsVqhjm72iunGbSTHvE8W8Z9Mi3Fm73FPaa9SgwEZO3Apf2eY9oknRsNWdtdOh7sjaGeE64ridnAUkr4lJyWT0z0bbqiLwgKVmKnqRa4tj04pdW0HPIW1zBGgJo2z+vEQha0N3BneZ48gvPQoooQKBbx3F5RtIQ6dHqKMPM4Z8GG1j1i5AUYsOX4iUP0/HSHuENbdIXPAinO6y2htaoQWqoDVmVjOPdXhs6DzYsBUW52ab3TOtRHzpxi6/HVskL4PTnqby6D9QfVok7iEAO8libpf4Il5h1jSxsiSmbcy9HnaH0lZ3IahEuMfcbilL1jdswTf9nmpiKgogY4tnWiDR05VGkC2VfQHtnJydSTvfeB6083hxrwXZJ04gvz1XK0D8riMR3Qjkf3j59p30AcKgrlNQOdvU2C3g0N3Ay4D1Qkq7fo4zO4r7V7huBMT4SG5nWsQLDxw3Mi1shuKMDX4JKrTGlhgWlejmuJWNbnzgetT1DisRABC7ZmRVLNCmI2uXQsx4AXakrA0WVc14ll1s8QlZ83zZxfxU4fLDtMh28lnzYK/HjgG5RPk2mwea4zclnAV+cxhYQBtYIaggQYPvyaqftEoSxelH5HqpfL/m2/la3M7LJddJGDle8zVMo4yRawOy+ew7JcBz6/GGxNx64S961w/I2a6JPWFDL3RM94agpQu8aZM1EV06RHP2P+8k6/oRpi5QB1DSvjkBDehLv7zoJwn/Ze/FQZb0wek+GpjunWfpMHb87sHTnUQW4+VL+rizSE0rGwlKBfbw6/vx8NWRHqfA680q6fiFXWYYuvwt71wPYoHQC+nw00CHpbzDOUM6/D51ePr58A7hwR1iTGiPKAzpYoP3xEpbYfphRd2Oy/TZxeg1sYhuXZFs7CwSDtfOmBfx6hO/3bikx8+Zbqa+uTMXi/qAcSrPtiTTKnv7N3jFgt/OPY81qxRiYjb5hI/AI8oiOqIbu0dUJqzhy7IRGrDR1ESYoxPfhlaVO6Ql+3gA2KrnZeb8Dkq6mk7Jqa1zyH3108Vh7D8R30yUFVs+knlZB7wc0KZoYQilnY5oLnsmYBbmKe25XlF1m4K4tnBRHib8TOny+6uiKkVplK7n0ZdkkbjRA2hNLYYjwiGQHI5Y0ADla/Htll1CWbHjYXRebQEZmcxSJQc77g4Z4oeHyhl3h5Q8u4tJR8/LZE8VSKEPbJnd6BVO8KV7+QI+cyQ9XYjHUM+7s1ncbSPoAs3P8/3DnOfTZH9XOsRLPnWFRjjcs3Nsik6Ag912b5cSthQ44Lun1rKpOSgGsuKcxwcA/ULYKtulk/s7aAbhSAJEMYBIXjq+QFBQFDAbOtvl2MT3J171z/djtScjqXZVovjyjwLK6g7JK1KHkQ+FG3tC3Fhh8ypszc3LL+IOkuIMzH5F7+YSYe8U8KXd3Ot7MBPWd74HumxhZ66gBH350R14XiYXSFC+K074hyOXN5OTyxhR6eYKqPjFLeh+04LuyWL6WUk4HLhwTeFQdS/PQ+FJpfumixdlp1mSbeKXDwJsW9juUZUhtWhB1TQt0IJ+54qbHzQO9V/fuGLo/M2S72Ng0uR7mHxWqhOyWvESa4qBtXlFZRGcBEwY5wjtDjcIhWvd2bXigX9R/NcomEmhVNfTZpC/wsRNPILbPU2ru3SXIw235isKEMfsLAicX/gv4i3b7WxKq/gT/v0GltVqs4vjdT2YBLXxYHdMyx03g6hpLN1lhhOrUHfFUdmTpVM4flqVKf41JTDn7XQgUzmMML+VmGqkSpknbhzVI0ddrWlHwT+lBfQbWy5MdZ6dJmXGKTjK9aI3qb5Bq+KvGFHB68LsgsC3cIKCTqfo9A2YTxEbIje0o34m1LUDLzzyKQj/qKpM3ANRQI8djFJ0OEp3IEqdgNJWyy7ucUyL1uyvyoSxiQfMg5rHOG6SmxfliV8YqLUOeotoibkF6GLeiuc5DTIvoRULaIlbjvu5NkQDcy3Htx9xb3GWnH4TsmSrJ2vJ23ijTruKazI6hRVJPmE6MWsi1MlavQkvBS0dUAOU5ylLc8VJ95Bem1+pk4Dp7ury310jDrfNNVKiMaznwWAR4p/Oy6y5zEC+6N+F0yWcBT6bOGjEIxzRouMfV/GFcN0aT1b7myNtDEkl/rHpaoj3c6fs/awPCMJBEyzWd2PcLKRyQHGXZxDVNIMk/zlEcQm+tJ3Smss7O//Pq5Rw1olvBjPF+yfKlg01nXQYGOW4AYTEbEe/n08tGk+IU/Ty5AYnBXu6TupJTII+KhNeD9ueVwWyZ3kMuIbnngsSCg834gCcz1x+8nj+OfS5GjArEjek0lR0Twfk/nxXgISdRMLRwHNZEs8pbOK6kcFl0IkHp8IW2KiISDY7OQEWnJSXAZBKesMNgB8KAUy0HhMCOMImlo4cfrxj5fGmfTKspPzt/fLGEpCUm29AtmyiI9vYbklS/uP0tdWoYNI1D94GiBlnA6JvCYk+331DhGXlOyGN8AAKLPXTqlIXaLQMf+eJL9wXJi+dX6APxmxnq/WlfOex+1Wb7UWsz+uPMrfiS5/1A0ffWoHmD28rxmf97C3h7++eEbhLl/GpgokY/FgnOExx+sUfxEZEFHaruS0omjnI+ZvZbFOtc8tVyxa9h+In15rm6tfNjlbp19VGK72faVRneFFttCLkV1qq/MMgzN6QQkBa1RKcAxHfEE5qOJwXvimctFA4
*/