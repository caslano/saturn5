/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_unrolled`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/functional/reverse_partial.hpp>


namespace boost { namespace hana { namespace detail { namespace variadic {
    struct reverse_apply_unrolled_impl {
        template <typename F>
        constexpr decltype(auto) operator()(F&& f) const {
            return static_cast<F&&>(f)();
        }

        template <typename F, typename X1>
        constexpr decltype(auto) operator()(F&& f, X1&& x1) const {
            return static_cast<F&&>(f)(
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2) const {
            return static_cast<F&&>(f)(
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3) const {
            return static_cast<F&&>(f)(
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4) const {
            return static_cast<F&&>(f)(
                static_cast<X4&&>(x4),
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5) const {
            return static_cast<F&&>(f)(
                static_cast<X5&&>(x5),
                static_cast<X4&&>(x4),
                static_cast<X3&&>(x3),
                static_cast<X2&&>(x2),
                static_cast<X1&&>(x1)
            );
        }

        template <typename F, typename X1, typename X2, typename X3, typename X4, typename X5, typename X6, typename ...Xn>
        constexpr decltype(auto) operator()(F&& f, X1&& x1, X2&& x2, X3&& x3, X4&& x4, X5&& x5, X6&& x6, Xn&& ...xn) const {
            return (*this)(hana::reverse_partial(
                  static_cast<F&&>(f)
                , static_cast<X6&&>(x6)
                , static_cast<X5&&>(x5)
                , static_cast<X4&&>(x4)
                , static_cast<X3&&>(x3)
                , static_cast<X2&&>(x2)
                , static_cast<X1&&>(x1)
            ), static_cast<Xn&&>(xn)...);
        }
    };

    BOOST_HANA_INLINE_VARIABLE constexpr reverse_apply_unrolled_impl reverse_apply_unrolled{};
}} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_UNROLLED_HPP

/* unrolled.hpp
9NtQpB6A/AGE66ENBYStr4S4O9FvY26NnY37t7hc1zVDjxHrLBHVIHRu+5oTgaENlgs7JROo09IwtBey/1HKFh2DRbQroM2F8cm36NEkLuJJrzeNiHwEwd4PgWCrCMUZqbJht22vhj0y9jTdRDAMpsWVdWMCXpHIXoNMvIWmEd/0kLELsm1agVTY7DEWeAGyZjx8HYyHB7wM3m/bbC9Caml26/hSPfc2ssLU0wB0CjSw6gMskZciT8ToE7tk206OyiNgIMiFH3IwahXnNdLMvBD3bvfPiNHK8zbr5uHls7omcry02aV5PXhlVJts2+yfoY1Byz3QbwfKmvp6JQU2WD1+6EAubKgXYaAgaGz77NHgFY9F8JIBp4DOzbJtu69JpzUARrT49ucxMH7A8B9te4VRdvZolGGMsYHZ57tg/XlG4cKKJ1eo66nIGgnegttONgPeLqDHPXT1jm2KCwyOimLSoKgcsdiMGP6nRKOJHEPFV74WXrqwjNaFzRDsiXTd0Add3zyg61f/H3U9pe8Xo179f61rUb5WLY+QfKfo/9m9ICYsXnPV1eqJ+qWKamCxmZ8YIduS3boFiyXgRoZMpFMwtZOBlRB9oMdgbz3bhR7nEPEH/EJSQFsQtYDYwlcHKNP/jlKmc1/9ZYwLq+hTCsQVs3l9+NWUAecxpsYpBx8qzaY69KOqF2ipYIPpDFroA9mNvsfL40xrG28B0eVfEsP6TnOe+8LpC3I3u/o7xfZe/J8QWDHfdCtnJWI76HTEYHFWwvIDnXTgy3qKedKaZvT5gUG69EmMYUuWtBjDfsPXIf5rGHk+gT7oEmCuOPreizu1YRPqqStixRWugTjkMZ8tTwH1ttQglRqlkpBU2elKfAzDzjox7LB8+1lQTg/b3dB8iCfZmyja7AWYjNNnsEieAcxJKc/IUgPKmUTM1EulZtwxtP2NPjdzIlYEQY0PDjczPSTciazjLG6+DHAHlGDA1KdU9p6GLxHQaQgoqPdeo1S43XVumcn8cc+pUdD0S5K3gdWcQ+9pdmPNcdOzjXRj0v0HuwCATezGT8WXWoAv6+Qn9E6eVACA2/HVsl3imuYn8FwFpJO3o3McniTbOpYECWIn7wDfhxr+KoXHSbYNTjTSpcrXic1lTDdyW3s/kyvsAAamlWcadIXtwMakQibPNOpanBijB2Y8crmD6EcX7Kwd9TP/DEMM3vVk2y5rlPyDxOYagc1tV9icPLF69wizOxYb2A7Kg/FsF30ZTLY14HZb4XZ25BRq8h7ySoAyCByyd5pZ6xkM+IhzD4V6Yae/cA1bGsDtl7Wy9yXx9Ss9BQzRvhLorgnbSLtvoRvszJiYaZAdRrnJ9K7N7ErV7NPgxWzed+YUAccFdkp7UmsAQaj4tn+CTa9DZP6THjdE8IfN2F4nRgxAYMRxwLZm1ZUJZpbxjkoum9g9O7s5O6Yj95Ei4WZESThVhzSCDrkvu/FkvcV22LQav7ljsbWaqjs0dPn0YdfG6OXHvR2SrZl5mvCmMIFDOcSPynslWwvbHSYsjsDbUPeytT0DMNhra9N6hqDSAOg7CsXxa1Vix5HKgwxlk6BKFDlCk2fC3eIatP/+A0iw3Oy7SeMd6bdttzvZ309z2gx9LC4Qj6LVd1PcIyMBjyDA6ANc9mKWFua8utE7YmAuhiwAspXOUd4BtBk9vN+zOPELoW+75zZo/oQXrcfQll8EMnZXGCcWlghXl0gewAeTZuvt4r52e47dO6/YX7iBnWkUKwZesXXEljYwYzOuL7/tQ0DvJp60vAnjhCG/B5YQyHlptkfON+bKYWvTEzHyGTGbG5gOUB7Uy08Y84Hx6GKi7niJnlP0z0cBKlzlUkmPVBJmfz2tXCYdy9btw7soOzGw0LVugMGYD9TfKdZQj0Psk6o7dSp2Rh0cYI2kDfB94023DqF6R89kmzSZjYf+8cIn5LOj9hG6Rp7qUq6PvxIDQ51OX9jsnSlIDvr9UuX+eMMb41/CsmEgDU3+dUIy1Knl5BbQoF84Xcl0LXSzm0Eq7PA1xgTv7y8CDQQniDEzZMbKsKVKYM09UmWYf4kfkbLhEV47T8KP0uHXL7iN9cPAv7TYWMW24GjchwB+jDsi2BmiC0RyZSzwbI43N8q2DoGqzv1i71i4P1ZejkddQOYPaQxmwOiTe1RiuQxST53n6J2xgw2/IXpKcOtL9UbZLqfDLl+fjK5Y/L9UjFgopq2VYDmxcVDWGqgahMH1GHcfIwfkkVhZmDxU/5kUMgRL+i81MMag4wP3kcFe8MT6wjrvKNAycu3uPujNNXg57t5VoL/jQTkOFffIBZcRW24OYBONoK4XhBFk9qVqfIsMmoFWmF0yyCOdqgVEgCArHIFBNM6LOxMguhMbxuMa1eM3N47h9zMqDfzRZPbF9m763l9Nr7pEX9sDxJZvQEX7Gmi4N9+oM1WPJaXXPpDLITdi7PRJJE5kcijY3sAtykdxdbBPfuYk6/DLLL57Qxq3AShQ2exwx+Jlymoy01cZ0gDNe8f15oP0SJPj3MNAU+df2mWw+HETH3KGDsjJlEs6fY97NF50pj6OnnxnGzEOA3vuq5ASLAIkCqDsZU0h9DuzjOkeITOTsg8FEwK2EKK0Yfny5ZoT96D75CAG640BNfHhHn9+SpF8W6rdHaP7vIhnQY+ORfTJMxEI4m1X2KJydDP7SIgDovSeob5AipPk0x2Aeva78xrNr7IAVaxI3jb26VnO3XEgXjpO1vsKQd0CtIIY72Fju0A7TvWMFw6LzgEOC3+B9vSxy/b8BnSYsGcI3tIdJ08jd4jOX9hBjgo8cC0X9pSVLrQWtj+qkwvbUVkqMKO5V2CE9Zf9D/bI3igmhQFELMMzocBzdYHnUh8zeuJKTqzuRKFqZvPxqEphoqQNpmByHSSDI/AJA82DBnzaEaZbzij4NrnBjuT27DkNRpD135a5Rll6R+ljCFVLArY2VJTpjEgnnRHpcNPmAap/R4rDnK7uDrmeVutZSkJV1wJD8ees45OA6Of+SPIzSRy9m8SWoNjCF/qzGJtVEqo4pH4vzgXCix0/1z8lInyU/bura6AL9BY8qNqKEQK9nYKG8XMCYl2bqtH89IVjTdV/0QhPqal6AzLaKHeyezTycJB8vqryOAfo3/J+f3kMq+pEtuLVFoAKDgxqjkOa18c+OydOos09gyc+2bif1RuH3zLgoebR+ImileroYaRGvI9kP3vxAsedhP1sforiumY7oWq/41q2hYXvGoNKyqjo+BS6RE11rV7kRXcAADgceb/HrHy11WtgX2I/saz7Mvp8kVqzCN28DhEfskCr3m87wOWLBz/kVhUjCCXQve8cN1XjyQgVmYLxxYoPlwCIGT/RecVNBlO1hL4Kb5Cm9+EBWJDICVgUjV4QY2AqshQobrUZBIpBdQccs1KczTxAEBZY/xOFZQGaVCz19WMJw+jD2J49qMMv19SoHQafYJ0/wDRBr0z0Ku+HYkqnb/7wi06leQb23zNiYh8/TRNb9GMXf4vOqQ8mWmWtQKli4gb9NHDiIiAFq+Hto5eKO8/6ke/APVxgHrY+ME9NdRhhJyxjuz1iBh4hE9D01IsUZhBtBgIhnjpBZiAeSCiQ98pnnXY2+Qzdf/t2J0ApCA9eujUFdoF2bBFGDzxrLxuLS6z/6rvKS8nOm56KjCvMcn5EDIcjGI5soBzB3uxurUArNhgcGeWUQ5NxbBxRCWCABmzWNMyNuNkiwTVyHQbCAA5XNNExrbRXMWVWs40rmpDzIe0OfjV6J0GWMBit5MS1gC8RUbMDoxg0nqvlumYRCTKa6T7G+B4lqe6g+t7ADA2ex1737AVx9wj7cHA3D8TtG0YhllGfD8QAV7vr2ZsFCBcW0r0ddEnIrUreDwvxfOwGvJzANXKayDuy8OQvAsekOgxa9E0xNo8yG0CvqCWwUEbzpi5exJeAmGlsHGEWqNZo7UFtkb8O22XdL2DYEZ6fbDSgIoCaqfqMgWPCm5DY0DgOzz+d0uAW/UrRPF2QQVeprG1SrgJe04SnqgvbWdFHQk93GfASv1lPA6sKLWjA0KvFUlwDbrLKLYul2TH+2foiOwqtDp60Ci2xz7DtYp60HcDFndObt3bzYmZ7WlzUvgDbvgXaZlN6NWB/pzV4UHjMR7joCzStGIdU042zbd3UxVF2BMR9xHwLxnYEaluVPV6e1IOMqJy9u0bZ8e+UKvusBzyDmA03jFpBhTou6+iSHBSSi7TifkYMMCIGvggxhQ9rA8qDAb2M7PlReCUBTohk6wzmubVOp1OcgZsgohnGr6g8jCB45/oqW4eC5lbZehly0U5YwldD1xKNQowFbNikVvQuidT7PCmM+pQIJQFxr8UHvajBrgE07ILG8fYzz8fwEI8Pm0GM402wB+dw+3yYpUQBTCoeRqanNHIDhfB2HPui4Erfx61E7MP5ewcjeMLoiVg2cmQ3x8hNhRy+OYlo9+0Q5adi2DrhYXILcnicqls/IJ0AKYGkBMzyavRwwEinnFc/39rOHv2A1PCtSTCx9/SA2FU0fNOW2v1I2G9QD047pP+Biwb+I37tzAgMRikk1zUqrwYWuf8DEhcLk5A3Rh0fEyuS3X1Nd8TB9nXdrxwiy/MISk91a/2FeAAUR2jfjYsJWOrWQmNTu3lIE+n7eR762mr/ZeH7WUcihXka//+2p41ujxpyYahdw4tI9nd2I/7ZfX+6wD9etBPM6FcMJ+nLZcitTNVr+nlC5QJU+29jsDrFlSX0BQ+/H7cM2Vvx6iN69WbG093BgqXgRLX/U/1sGhYJ1ODvvsQEM/vicBcPXit4IGuBKbQL9z/U2XsOTwE7I7YuPSA7Ybg2dzVkmfEOgc1mEYJDnsq1XcRbgFlXUUip+KSYXGrASM9y0JGvxEhPUzVyct+56Z5BvnPjTTXrNcqee3NAmBV+ItkGjC75/UHFb/m3/SGgkqeQSkxbVhKrBIIsgiwklSK8U8y1aHgSrN25bSHl+hlfc6J/hibG7tKkYoOLcP+l1QHaOjwUw0A3wX9IJuM/91Bgr8gEkrbj5jWdlQixgs+xLQMGfASeusCZ3KVR7iH7ASfv9ZBG3YSvHp6kCCXlnHx0eCGRdVSG4Nt0fDRxI961kale3xHXjlc8oFShM/Pv74xc5HPd1Wc5GwL973Lhkm7IWAsArCYAWHprF2cvPYTfPgPCHMuefohib//b0cU/1mhyNTVNnsHOIiSfS74DQlDoae5AOsJLmdmdseoj0pEuFumouZ+O1n2p0lEa0VGaSkfSoS5+4pIYZHlISt6r3AZ2KQjwBRiUL5XrA5rVHySYyaLdL5FoYw+ADuJUJNg1axAOzFYy7ns+ApjI2P8UZuzrzzj/jEZDmGDv/1Fh/m1KlCcIgGHOYjpcyyY1CEMaoVairMSBCYq1ev2TLu5Kx1O1D0U3EiMaiWd/+bC/tgtP30kUv8tuii6tU0unvd1fWqrFOZepuLSZAtwoRzzzLduJ3SEg7I+fg8DY0tif8RhkiBP1s2CkUmW7VNkhVaKHRpwuUE7AjHtbjU4Gtu+Cf3OLhYiTbZ0Ztg4lVjjRLg7g25Fze9ud7BWgCuCsnyscdo/yv0WZ4sperr7uZ8cDCrGv/kqepuduxslAWmXl+3s5e/pzoMLVn1N8sWv4TegqTerDAPjag6SW5rJFP2nIOU+L574flcUDwsU1De+3eafuAs8+LpoEi1AsKmbZgTfaRFbIOC0eq8YkHquOWknWl+kO+cvXN4vVo5PWE/LXE9qFMKcBSOvpwEztYUWLsJQkehK5N5HV/q2bX76eDvgTiSoyS97N/gSwqh5julIwKnTwoVVRV2glN3xxHYytpxMZIU9q202f4TaJq0C88dmNJ1Zo6JvM0m0ejGSQvO2St0PyMsnbGTk9wvL3ACZv3vMLTBa7zcDMkPqn3ax8Fav3vyFeXFyMJIEksIaonnvb5AMutFPxazsvYxQARdbJIbbs7yHcJjnSSYysISWBNG6n/IXbvADv5NT4/6APxORA9sm35Z1lu9wzWP03FOIfL7ecOITxrY0R/ddXlanxJrpyoTQ7MZiEB+6CS3mZ8uxM3M8zKKqnq/zkSDNz/yxUPKBohJctagHjYfNy4vZ2PANa2aEEPU4G7oO7tvjdKzqElRkdIfnTFnHa5qBk64D1h1f5MLydTbZ1sJk/08DQuOtAWzFU0wsmWFIO7qyLAyj4pS+eNBf6g1fxTp40f5e63Y26+d5AF11+UKBnM6BhJeoN45Iu/QKU0Vp0s/pr19JCCCBsGGgxDV7hxrwcCOrcMfPLSne58taYzB9n9oJEv+Ub4a8/ccMWvLxCjyvg5T/DNN/7Q/8KcGtY7H5xk5Q7zb8D23drnIG4uYjboh1AjM3GQJ4nfglQbnwarrkXsfN5Bqn2dRq60ddiFveNBOguhyOzYszSc0gDeGLV16JVLiPZzXb/QNoZQOG9A6D4+oQCBbv1vtP04bksoetl+uua8f4Fb3og7vDzGOWQNjD6WPUaNCeAhLJN8L3x4RhaOzljqJ9S7CdL07BqJR19833OpacZFljRib9PG7X4a6Zf/IawtCKZflPoN5V+s7SaiFM/deDhJxGKcAy/7jE91Xd3KtB6O517cmvqgTDc5MxXIl3RYtxLziXGXDPwxtEOaWZqxHsPVo0mOtLPUOx0wIQnHzyD0dw1xz0TXTn301dWX91Ga0EnVRlc6x6hrKdE1hCJJg1eBON9b+CjRtqB6luZVPrggDBPUFvDiTCr68NdESaSXh39Cd/BIN/vR/n+DiOeBiPNBs7otHyM+PDcQnLb7ve3nQLK/xueRqVHFNl2OlsZ8A6WayqAk0tx8tfK93JPocDGXxLYrcCngzlOJ7SyFsqxxWcpcl2ksKHvD9F1ftDOotPR7VDpc/Aj72JrADx0N6c2vIrQPvu9WN/b2lYnmKWSw6rkapMqW0F+BWydgxErlX2WHTi7HuASD4LgvHLj5n+NElvNH47FCNpU/7zDc4r4xHt6o77a42oAqmK7nxSnOVEUgGpxl9KSQa7L1JLw3WOh28chh+7kQHFs2YF05YmTd6SRuoM4hB5An12xO0SWIDrR+bI0vixlThFYUXZQesPF7Di6bMLCvjkMw2GjlgLlBFjt9yjFlLONG/9LKm+JATTYjzuA0qVXkMbZl92nuJQs5z9Id0Al4h1QJrAWbos65mXxGk3Vr+BCp2OP9n/1cuXII3JtVxeeiquaiKceM+nU4wRx6hGXE5v8sXLqcThgYagM7IPOPYY1dO7xIPv+3EkuL9EHs1nTe3g3BFQ/Jaone6D6mQaleoK8avVQUF9uS/UaoAU2P3SOQwP71YOT/2kDwf7sfzUaNe6SfXPzGR6IMyZRvGot4q/jBQxZxUAfqQ4FqlTXR89h+sVPiQdqcUMDNUC2vhkV+jqcCfbVzhBnfpFBt3DtwYwKkYHzyRp24skg8poqwa9fIqFlfhfRuxEQMflRH0d/egdUoybxWI+PUmlKygspfx3CE9ASRMY6VLlDqso9d3hE5R4z5Qxn677D2c5q6MWOU75DfpgmVwJHSZUxMi4Fp96bjL6qRMnb5rQ7pMrD7P07z2AD9y0Kk0P5yhjU
*/