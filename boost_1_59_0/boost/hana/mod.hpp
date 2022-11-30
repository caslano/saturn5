/*!
@file
Defines `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MOD_HPP
#define BOOST_HANA_MOD_HPP

#include <boost/hana/fwd/mod.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/euclidean_ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


namespace boost { namespace hana {
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) mod_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Mod = BOOST_HANA_DISPATCH_IF(decltype(mod_impl<T, U>{}),
            hana::EuclideanRing<T>::value &&
            hana::EuclideanRing<U>::value &&
            !is_default<mod_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::EuclideanRing<T>::value,
        "hana::mod(x, y) requires 'x' to be an EuclideanRing");

        static_assert(hana::EuclideanRing<U>::value,
        "hana::mod(x, y) requires 'y' to be an EuclideanRing");

        static_assert(!is_default<mod_impl<T, U>>::value,
        "hana::mod(x, y) requires 'x' and 'y' to be embeddable "
        "in a common EuclideanRing");
    #endif

        return Mod::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct mod_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct mod_impl<T, U, when<
        detail::has_nontrivial_common_embedding<EuclideanRing, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::mod(hana::to<C>(static_cast<X&&>(x)),
                             hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for integral data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct mod_impl<T, T, when<std::is_integral<T>::value &&
                               !std::is_same<T, bool>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) % static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over an EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_mod {
            static constexpr auto value = hana::mod(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct mod_impl<C, C, when<
        hana::Constant<C>::value &&
        EuclideanRing<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_mod<C, X, Y>{}); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_MOD_HPP

/* mod.hpp
AkC71sj4af2GxCE6Mn6M6zUR6TME6eNHsv7nmnoH/X+imnof/b/672pqxLqTE2sN0XVwU2DlRPUUll0NZZdMVN/HZyT8vIlqAJ/d8HztRPUcPq+H5ykT1Qv4XA7Pl4KAkRI1Wr3VBxwTsKbX1RwUHquLRf4pKy1Z2aiou7aPKP/6sRHll/12RDngFGMEvIzwzxp4fxJ+R+FnBpKNht8Q+E2E30z4zYHf0zYAfX7/C0b6cG72Ztw5ulyKyc5u5B/p5eZ4+augvDnNZlDOinFF6sjiwBqvusnksZQpuTZ7c+EGx7tIH/uFTRkeo9sMj2+3zwfGf48ig4mxcqpB20iXrCy2eltFs8+IO9AsU06AZPWV2gIJuCg5pdmXa0Pxu9hWO99iXlmGt7vyzXBKgbn+85T63pR0p9klfy7MdGKSst6cfkT+3JZ+xAfv95rTv5O/TE3/zrceMzEnO5JT/SWOKM8c6rMpR9ILzNWfoxSIggUJQLfoSig1eKWF5vR91SeRg9L3ofFPG/XAnjMr++pPptT3pEA/e2KkW+j7dRhdQEKIRs8WjV5qdE52JKf6c8I1Gg2LjkaCz0JNgz0p9yZsGqkY5aAqDrLv3xKnzP+1OWCpzZkdMNXmTA1vJAR6p4AlCqbwMFcgRjmi3GcGpX3et8hcCoOQZ4aCuJK+Lceif5BO5Bf0xm9baNlqwZHDcUADlvY9eg82G/beNbpcHKEsMvOuyz1G7L0JjISDPqcl3DRtk+yJaTa0QXlfnkWK9ZiLAWCrL8+KhXKsjfLPLTHAyxdb5PZUfjEwVhRt22Jq6rYaRUvOXBUICjY3oBa+hegtQ6eqjneExju6CnBZt4Av0VnQycrvZJ5M8ssj12zYoip4jOmtP1Lnmqg6tKcFN3xlgEds5bzcGSJeHkILTi3sa5COSBlfHL/jo0+uM6Xngm8uzMw1B+Ll28yd8uWG6tvMQqe+70+bTaoRACfIqok2tcQozeBMprfIJ4WZi83QnI03V82bG1QEbb2qtaVB89ah+xknJcgnz8mtJt9i2shJ5DTXt6fUB1NEixyMEdFEwYGVM/GT+Ak+F/VE9iW9S5buHHOqGEOeMRjF7EOePMKlzAT3OU7Zp9qUjWZTEDjmbKnSXNaIpjN7kZe6XJnp7RZTeTG8tEu5CIWh6NdeFZzueOXDslJ1tblsFj9ujVtM2d286l2ZDot0CfPhMmWnx5Dr4t3eRju38a7booBJwTtsLYXKZ8q1Poc1MN17vHK6hlIQGkhRGqc0/zxGuaDE4bFoSHfi3U6xU04YK6wcD3DDrCsDCXIFXuYNsJpojEFkIkMfcMFMUJpgyLJM0AngMvYOHcaQhocpmY7Z6U0+cCYbBo5hAY7hTWjst0QLAJfHMFEAlaGNJK5QvNEbGcxTIT6Y0Ms46UoFWeac3ILbcQMp+Ha5QUFmqOoxiValJf1DeE5viYwxcKXHVLt4KnsFV22MtYtns2fRvE9EJmtEM/b6BDGTOmPmnZnq9Fg4caf19mPhP/fqmIgWNU5J9M1/2KxtfsVbQ5SeHVjLA4Rl53pUil4qXg4caoGEz3sI1OBqmOCdeCUVAnIqe9hHFzhQcBXCu6I3pyWl19mDylnoZHPcGRAFUpL9qHhtupphEuMWZJgvlXrtQfEKSJvgLNL4nxoAFeGrtIrDi5zKIXbiAjkNcZiYa+Wbly0oQ7ADykLLtvlGtXFWXSOkgLCy2PdXxij7IR3abhGTM0F+iMPs+8XEpdT/A+wRgocgFuLOpVh/KIR3cTXqr8OArrPolSAMJQiD4V8LZE6DTN56pK30OhRm0lgqOAKaGkpNvROEHrPxemt8Ipxls2B4aiuzlA/JPgRGfcYMapgsRuBR2gM4VFluW+QbYcV0C/wTsPqG4F/fECuVSn7GRn+TfHOCQLRnkuCtzHd1F1631bR1SDK8AqsnYZNPI9yqjGyYKLimY1FjyTQdhsM1CBcHH8zBPQzQckkjoddEMxG5XVoJ/C66kNsLIgKq/TxxgBV5WkCHKwjDjkc5RymJ7N0+Gr04cRhmSz0Y7BM4AAws89Nbvt4gJfVj+bgi9iJQPcLcUdMJlIpQQ1Z3j0moodsT0o9nXiIO9piAA+/DeXQP7fayXxBXAccn2feIy6bsEactLCQUxakeG8sENPGbFQxEktJSxNx9nD/tjTD9podxCYz3WNkQXvbzbYJvhbnZ8B4M29Y8S+Cw3H5WbjHihvmVaJHgJCPRjpxfRZrSCjNxfprVya5TdWmv0GH2s1qx9IP2Bt9IcUR6a4ZNjMvJSDJKvQVO6EZCuAJ9sghXAMzSj+MCq+8SRbDvEWoewCC1o4WaP+JizahtMdc5rOKNWWViVlaamJGVJc7Oul6ckTVNnJr1s83mrF9UpmXlwN+bK1PAJTFnZVYmZVXdZ866uNF6PhaZBt0Rcda8uUqDb1RVhkF6ubAAsLkfOTF+m6WmVZyZfV2+1RcvTgjTCDodSKA3nRw4BVGUorYL4NC9IEin5fbv5JaYwAm+9hIdUwLEv3yFofp26mCtFGxyBHHJGdjPupiiCmYAPetngPQf3OArad+a6FtulT4DXT2lyemCefIpDxiiRzgefL5PDX9+mNTvIq0owsM8Kqqt6PElbs3v2Zp/asuozbGZ+ZYNNmW55fyx4fVNjlPG80d9yy2FaJYUeAahSbCEXRVGZasAs0VpGNziK2mTPs3IP7VSNC9pip9W6+iZ0uwsAqLlcrSAGhhIXermWNFaNdLUjl+79rGNQZwSGIZEjGf/7KHFjkdDfPAt+nbYs9DLfCqo7IPZv0DTQk52B3L71Wwm5YmWIlYNUANpMNWcvdpUG6xeC3MtARyugDV6julzi7MoEQbVk5M9HPohr2IO8KhFjM/BC8GkHmLSNaEoJi0oIFmyzVBTxz+Jga8rsxwuUOSgddPdyhDkMPx+Ur02hINwwH/+QHe9UcyV2y/KzCBO8cQUT6kXx8NvNPyGwi9BZmbpck9cYKgnNjDEYwokeMyB2IJAjMfIVp3DNSGzszY/yAroei4LGnDsJKQHEj1GKBQDaewP3XQrItl8YRwhQxyTlSOaoVwSR9JtWAcCeSWSNN4Tw9bwaiWN4SHDT8zwp7GbKzm6HdMGDn9gEu4eY3/l6RErAWnUjNqUas+4qI8qKcCa42hJFgFj8LErZPeiPZcLY7c9qI3dtIiduZU+vosCms6aDFpBNriS6GRTugaOrn7KhPjHq0JLxVU3GMRlLK5bZ5VLsLl50NxEvbkrI2J8NG/O6jGgpF4U5NIR23r/3E9wEl9Wxs0bIBGK3ifLutJMs1/b2yx4MQh8IR8DS1VPtlCD4eSrem7mF0bTd7A42tSW6JkKJDsEKGqlQfTcLexolf0z5J6ETUnZBcoQ1Gd8JSUOcbLj17nxFUHlKH7toKugHwLjnepPaZSDxuLiyiReS85MEBOoxOdADnyAxn4FA9+daxaEmpXorCcA8+xjFpiRK7GDrZG9KWRUsvvPqqrbAhwDz4+hzkbWy7oCtCUCmwfAPBXwYNO7AEpWiuOMFgFHd6IGtQ9u76I11cJq+yLsOqDEgXNU4s6fLvFHDmOhXiLMu3s7iXfju6LEjSFE4mZdX1jc6KWf5KU/ORdV+psLVPrFcGka8BSXcjX2Kb216voCX35ISsyF0bYBXXyUvi3uunoJZSXMqGEAzm8ETgDdszArc4tD2BEns+m/y83MDy3lxZ3imNr8LvYxdAO/FtMYjVT51fWW2vwO9u8emuhOduFbAPYG8hN4HoHMmjqxFFTbbVnOLbdwyeMx/M5jU44WKQ0FPkeQDU9XVdNRxREc3pCrBHXklD1Z2VLjtrjcrGyeJKXRzvOiAnFypiOE2HSw11EsX8GFyWKYGIHrQWh8h3g+TjnhgqnRaJddDKPdxeJ0tOcD2mUrYWz0vT82TSRFycVoCVq3Xw7GbxLVNG/dSyPK3cuAsIHh7pvwj9U9H//EurPW4cJ1kN3Uq/GasMOgyV02U7Tm5YkW+Jnz8qRL+GanTveMdXgO8j1+vylJ0AXfRiTon77pL0GLz2rspKjXAxb4c2i/1fC7CX6F2k+XsYAC9E1mK4Sax6Ar0P56An0EuKjbERKKpZVhWSw6s7LF3KybwbMBPjGy00CDgETLT7wb9WwYrkO9tRmwlmLfWo/Io5uOeOf1aZQ9/TXUuoFXgKYCp38EwM48ArAGAQQGa2J/FU5i6OXPfqgnoAuA3tysmwGglBK2j6PGysnuw3YdnskwA52sDwadCFxDBF7J71QMXErZkO6JcVIWYn72e5qrp8/Tn6WhSOtgtygj9IZcO0iUSqG5vhGcsjHgCvpzhBqM+rZQqPkH//MsccwiI7BMfbt5bq1o2T9XvmjklTZO8UzFNocE8aO+Cy9i3tBNqDKiYjJyLj5kQ28819c62unt3xe05Mlfh8VYmqRRITDKU4ofVjB/u17Q8DUNBy9RnR/ChTIa+BvPUP8Cc8EOazJMDExRHDZoKD/YZDCyjUCDwGg6oTUc8qsyLhceq7/YWnWyuaq+dKsFt0twwqcaxq83l0aGCCgFZmqRUDMItyZs+BIdDq9aYUaXQ7oaCV4CfQwC2T0ra/MZK+oiYm/spj+f9dJ8tbC26ZqXU4bXI4cHF/dQgUqoEoe4n/LwQXsJCVjCL/xt9xicS9j3vUTHo56VTnYF7WkEj4LJvRpBMlHhqtIeEKe4lQU87+sQJJ+IR53SJZ7JSG0XgPRMcrIvengInBaW00s4Vp7XAP0lwJUM7RB9fZbBUJ3fheuBgHc+7QNl7LSqlvqvIVPIylKoNUQMSdAueM8DbyL/PYT8Bx3AlS5s8r5wkyF48n/KLzYF1vdcQUwbhG6SL4dNe1Y7WU6P3ktSN2GmTY5ox5LTpECqv0YceOwGjX0MQk2vQeOJ+cATxS7E3ZOqc+IirsEeRO4ECK9yQBkaIAznoqtToeZFPI+HOjhwa0SYuEGYrPFcwYcIqPLCpQYD8cBqvMyM5iOutwQ5/N8jQ9AUqbouW4rX5hhkNJ3hBhcki4Pcv0LT8JVuwuVlypFq4fFpXmiM3jcJDcfDnZruT+qO0v2TtEmTyu7ilUbRkMc4WRKPeoTYNPhJueqqgS5DDrKWs7oZpIl10Fn39E8ok0p1ydeJw7U6iMxCj8uDYSMKug521EiwvERr9jO6YSV9i5gPyqMET0xgJPATz6VB+g3DtQCPEUWkMxBteYRpLlm5gp8J2YHpWTd4DNKlYUHsZIeQhT3TcKLFnSfW4WsL79Iubg6v9q60h6rP4M2SYY9tPcEv3JbMQbmEHefki/PB+d0sPJJInzKX4yfMbwx8S778zQyh5jN4WCzU/AH/SLloCJJrUOtwO1meSjtEQRufPs25CTd81+a72THtHcMvedbUOvqcWOpnFNxQAj0I7pcLivj78JOUoy9r2lZHSLJuc1zc6ujDS0bwzEvfVdhIkWct7u/C3VK1+c+yxM5ocfMPtH/ejkyFbGmUpoJeRhX0ITuBNs3jFAWizck+G4PGZJG7nETPe6wecgNvFbEqmKD+e3Fb9RA+YnRnsXzRwQkiPHwjvS4SHsYTBvLFAnGGfHGp4J3NCYE88YdB2AYQZzY3UhB1aP95kJ/+ZKOWhxvpbtOWBbKLwTuw1TpWE2UWnEZIMJ/+NAwF6AhcYKJtLnFOP95KX3VhvvsFkjJdRU5pnHv7Oh6ikd34vS5qfg1P/r/h/LVR5suBk577EfY/v8H6eZsvq7qwaMs43GfLPhqNhMDMMzi1puLTW2CHyd/kipMXiwmLxezFYupiKR93+bKf4TEyKr0jXHrbd4jwTpA44cynw5nrKPMNkN7hzBqawkX4+A76VvFFzIlIKPnr9WWGZ7/sU+VdYrQqspF0o42FFTaDmFmVsUKaDaKYTyamMJr3w2CukM3BOkGo+XFfbYF7P7zjlLgSW6usyiiWRsDkz4YkXtdKB0oCt6NGgjnlcrLJk3Gvsvm2Fw3m4uJScTDONPdOlIUCpMWIZOq53yDighQ8cC5i6q36ImLqvdEBDaKgwViYfBc1DlBYpq+OLKAMdO2aYkcDakb0mZod7dzBu8MYcfBqWvmhG3L08NCNXNFO/l277t+d69RFk03YsVvz7UahbxcK+3YYmJA+i+MejfEVrKp3hXJUSuY0JTqi5V2AMwfvGK/qTYPMDJs4XJNgTwGXgnHif4Qyb5Ak2guSdaEfby9G3j7jxN0fd37FPULWKPTnbZMz8JjG1S2kumsdbxFnO5n4nc7W76B7MEkr9oJWrC7wsbx2PyB/uNax34lX8bHvrkTF7UTU953SiEBOKrqooYiLCtx/A0OEOlA9fP217qL+DubmSn11iQ+EoZTZOvpULku3V595SleVwg5bYfrxt2nU8t3j81e40ruz5d4cX8kaX8kyIpPwSBkJ1BBYa/ZD/DwUbXO4jvY7zKxcKfdmCo9MxZ0gO7JVdbb3VRJKa9hRQAn/vvIFCctxSj108Cb3dg/SZdVZnenWsK8+x26sUfJF6BJeW+YQS1fKu+5qbQSMMkrKARWxrNaR5GQ1fWRq7PVkgbvAt4cDhGXs2zPY1DL2a2gq63ppENgM8Pb3b8hghafnvkGom+2NoglsSup6RrIUW+tYFvBxdlE6ax2zC53siViN+muY83PCnzt/jHVQL1KrKtWZ0hjqS4en0smWdEY6csnnHI33qKzgvQLtrXrKygcM/RipRNel0FuWAuX8ibRdZK5Q81sTSuhTtGnkZuFhxYQPZYL3AFnvlmy5Z4k2IvtoiXu+UDsfy/RkbrldnGffIz4r98C4/Jkyr6kcL/dkCI9sN4THJftOdGZEtt2PquQi7s8Jp/tv7P9em7+K3QXlqvNX44fkWscqfwnqg54bxOlyT3YlIDNXeBjjPMk986RZHqO75Q7k61UwsqTHrVgTWCWwE1G37+GYU8x1uWeGGO8x+nvhudDdhnKpSe5ZJjzyN2StnkKhdh3C9TuFmqVG8l/ehGFfKO3V8Eu7k/NXeSDKp53tfZbYbhnp5gGubhDUP91MHZwpXiHX7ZODMZuSYPDBwBcR0tU4OA/gLhG+v6SUFm2WObE/mD/iDCkER5qTtN8YNE5wRn9D9vcqtv40z5/vJDXT283zf6/nO7V8M+QD5x7T8n+h58/AfLD1p0J+CjDhv78h66eFrdBLJGKJKwjdVWwupPo/DiGOq6C0iitLxXp3HGsAiJWs5hBVTfqGLIwCtM9a/DY1PM46HbH1QpBrAKrtgs7My1jBCc7M357kzLwX47w4VoDAbkArw04juVx4aBY9uISHm4nxioSHUymlWHj4OUoBFk4k7kIWzuGM8FAI1xd65lcmyj25laPlnkXCI/6+MGpbkSWd/d+xL598GTabb5Amkil0aCi3AFax0yzKph6r2dTDQeQ42fZYvdAuKOQ+uo6DC6LlltrXjyL+T0L932cCTdK7c7Wk7ZpwuwBw7OeEmrEXuJBrbedUwtsL5Hx3qn8KPKC4/RWhxO1XwFrw4ln7qnJjmuC9hMI4jEOZ7lLoG1x2dpFCH+Zq89u4jrueREoyu4b+PsWu+hy3P68BN9RN30Qcbc9gxVpH8jNUz/HUMwhPJ1KT4x6DNEY3uO9BjvYYnayL
*/