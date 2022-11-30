//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_SAVED_HANDLER_HPP
#define BOOST_BEAST_CORE_IMPL_SAVED_HANDLER_HPP

#include <boost/beast/core/detail/allocator.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/assert.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/exchange.hpp>
#include <utility>

namespace boost {
namespace beast {

//------------------------------------------------------------------------------

class saved_handler::base
{
protected:
    ~base() = default;

public:
    base() = default;
    virtual void destroy() = 0;
    virtual void invoke() = 0;
};

//------------------------------------------------------------------------------

template<class Handler, class Alloc>
class saved_handler::impl final : public base
{
    using alloc_type = typename
        beast::detail::allocator_traits<
            Alloc>::template rebind_alloc<impl>;

    using alloc_traits =
        beast::detail::allocator_traits<alloc_type>;

    struct ebo_pair : boost::empty_value<alloc_type>
    {
        Handler h;

        template<class Handler_>
        ebo_pair(
            alloc_type const& a,
            Handler_&& h_)
            : boost::empty_value<alloc_type>(
                boost::empty_init_t{}, a)
            , h(std::forward<Handler_>(h_))
        {
        }
    };

    ebo_pair v_;
#if defined(BOOST_ASIO_NO_TS_EXECUTORS)
    typename std::decay<decltype(net::prefer(std::declval<
        net::associated_executor_t<Handler>>(),
        net::execution::outstanding_work.tracked))>::type
          wg2_;
#else // defined(BOOST_ASIO_NO_TS_EXECUTORS)
    net::executor_work_guard<
        net::associated_executor_t<Handler>> wg2_;
#endif // defined(BOOST_ASIO_NO_TS_EXECUTORS)

public:
    template<class Handler_>
    impl(alloc_type const& a, Handler_&& h)
        : v_(a, std::forward<Handler_>(h))
#if defined(BOOST_ASIO_NO_TS_EXECUTORS)
        , wg2_(net::prefer(
            net::get_associated_executor(v_.h),
            net::execution::outstanding_work.tracked))
#else // defined(BOOST_ASIO_NO_TS_EXECUTORS)
        , wg2_(net::get_associated_executor(v_.h))
#endif // defined(BOOST_ASIO_NO_TS_EXECUTORS)
    {
    }

    void
    destroy() override
    {
        auto v = std::move(v_);
        alloc_traits::destroy(v.get(), this);
        alloc_traits::deallocate(v.get(), this, 1);
    }

    void
    invoke() override
    {
        auto v = std::move(v_);
        alloc_traits::destroy(v.get(), this);
        alloc_traits::deallocate(v.get(), this, 1);
        v.h();
    }
};

//------------------------------------------------------------------------------

template<class Handler, class Allocator>
void
saved_handler::
emplace(Handler&& handler, Allocator const& alloc)
{
    // Can't delete a handler before invoking
    BOOST_ASSERT(! has_value());
    using handler_type =
        typename std::decay<Handler>::type;
    using alloc_type = typename
        detail::allocator_traits<Allocator>::
            template rebind_alloc<impl<
                handler_type, Allocator>>;
    using alloc_traits =
        beast::detail::allocator_traits<alloc_type>;
    struct storage
    {
        alloc_type a;
        impl<Handler, Allocator>* p;

        explicit
        storage(Allocator const& a_)
            : a(a_)
            , p(alloc_traits::allocate(a, 1))
        {
        }

        ~storage()
        {
            if(p)
                alloc_traits::deallocate(a, p, 1);
        }
    };
    storage s(alloc);
    alloc_traits::construct(s.a, s.p,
        s.a, std::forward<Handler>(handler));
    p_ = boost::exchange(s.p, nullptr);
}

template<class Handler>
void
saved_handler::
emplace(Handler&& handler)
{
    // Can't delete a handler before invoking
    BOOST_ASSERT(! has_value());
    emplace(
        std::forward<Handler>(handler),
        net::get_associated_allocator(handler));
}

} // beast
} // boost

#endif

/* saved_handler.hpp
LfTkJK1ceg+M9tR4Xrj/t8Fj1RyZXsv22/yBaCkBJI3/y0OhcIXgF0pLUxPxkzrkfpJF0MUh0pdQuCS0aetrrkG1zkFuRSF0RxZe8s9oSlJSU0JU2Chx/BbHmTv4XdLML1nPUhyjNYiTe4JMUzznnCL+NboWxJSILS8RWwwXyQCRmMkHMB6S1Nvr4KgPcG0xURAKdk1qIWcTTMxD9oKUCAuhHxSbrf/KFa+FVikDy4Kn8Bpho9zXDLqK/+nGQl50ht5dEXWqZ9+SvSFomK1KLO6XLyPmQz09UX0f7XJMuM/w6KCAkPDBbFOo9aB0t0FAAoOKXRFnXX/JS0GCn9B+4NgpyanrlD7JE6rImG7YmP5tEMb4VZ/xL5dYiraMHux+SxrBMI3iQkzoZPh1vxSlCa++TLCSWJ2SAATlyOsbLhPJcxYq2lQfw/EpFIIq8jaqCPtPb0jy7tlZ4hvanjQCc4FC6ulnIrqHDN8zfGvsQeJtahiapO0WbHIyqpHt8DiUUZtwt5AUia9y5Tn2Vf/g8g3ppX71ArqRAARPurJ1OjUE24y72j/R7AdybB9qt88vj7wFsXylH1kwQp1L9jtnyX8xEKcLl/0STJqAe7uWUzEgmLKv3gPyMK3YM0BOHM+dOjU2kOkJVBDo5pLXu+aQ0N69+T/GvWAXn/IFIdPCfp5p5bCYk2nVqWhA2pRWznT0SdEPE5cMEOjS07izEn12YFyjGg+KR9j+WHVIr/rwP5U/BaYiujPtP4/TqcwdidFrdA148MqDnTdr3/h3P4/3pY+JOrZvDEQTwWlGpDlj1yJGgAEuViXQ8//xsHq0X7y3jWXOYHCotmpRQcyQ3py6rYFq4/Jim/uz01SPXc2uNWllFt8bCK8ttT5GcwhfQLOsWYA2zTETYr4Py6CgsFwwA9heJmWEnpDzHykAcfDQZDIFT6ots9bxtNAp2Z0h3m0UYBqaoLuHFWJoIOOwaeNEc1hoO/rAP7rrnYnYtW5MiEkvkgOMicoF0d2r+AQptEkpCAoFSAAYRfWWWTMAa7sN9+MnupuaOkowgg1YBDAAAAT+CfoT/CfkT+ifsD/hfyL+RP6J+hP9J+ZP7J+4P/F/Ev4k/kn6k/wn5U/qn7Q/6X8y/mT+yfqT/SfnT+6fvD/5fwr+FP4p+lP8p+RP6Z+yP+V/Kv5U/qn6U/2n5k/tn7o/9X8a/jT+afrT/KflT+uftj/tfzr+dP7p+tP9p+dP75++P39hADDwZ/DP0J///gz/Gfkz+mfsz/ifiT+Tf6b+TP+Z+TP7Z+7P/J+FP4t/lv4s/1n5s/pn7c/6n40/m3+2/mz/2fmz+2fvz/6fgz+Hf47+HP85+XP65+zP+Z+LP5d/rv5c/7n5c/vn7s/9n4c/j3+e/jz/efnz+uftz/ufjz+ff77+fP/5+fP7B5Dxr1YpanR2bdWNW1J4JVSEF0El2cQq4ptciJmpT9d+rgkGY/SaOSAVtWeHJlC8+oOIEt10dJyJoYsIKaiu62mNWb5c0EwYUh8lglGhcBEgvaBU5PULIq6Wj/GdhV09c9XbDu+tSe0yGYtZUWkXZa4P0VXD83hB8exVyGIVET3NzDye/nBtKmtPWa+g5cE6cGQ5P7FzRHmNhAZzxCUb0fD1H7W1P9lAsxZNUFvfPS3pHnMqiyP7Fa8y9YGBgwfRcqlE2IFUOR3MKXrrWsy4acKZ0Szg8mokMSYOFMf9OrQij0bgYDFDRLnM1I+p+FAxo4kPRRlKM/lSgtd9GLaQeXWK808TNn0UlB5HbM0u9sIct3UuPtSFV6EfISdQ77baXZ67impNKIA34ntpzTt916LC9q8d2OCeUiTVKZM6CBgeFDbnmPASqyG7s14OTKcNR9uyIV+e1qIqKmnp0wovkODItw9x9GMHeaYx0WUNSt91UFb3MZeb1FDmVQArObab5sfgOW9SNlgqIBEnChwDwURwj0XtNE27h7hRtZxe3dH6bho9v+2yd+HBhe9flI7/YVJovQT7tiMH0qlucGtq2Du/m0V/+mqNeImxCGQkawUEPIZf9SL/sLlcF2F2vdZ5Ppbwzj7TobEB8772bm4B4LnLRnQk+VA2vrsDJ/OrZqM1vucDRI5paMG/OgRl63c7RdG8g1JHMX2BP3WQYTLh6GDRJAe616bYpj1HlWyWSS20sB9aJnG4bn78Ak/jYNdv+v9v71lNzmEimc5i9WYrq+1m69/x3mj1bIux/P/76+PP24wB/kAlqmpKgrqIqAkwWYw7Q90IY9dVBopMD5lzZrB51HYpt1IJ3q0xdOpm1yrye5Xri9/JR6TqJDcedPyqSZf7tYE/kDgCYvu4Bc62hZCKLSwYaxEZKoyO9ZBGoO0I1pvfqDnB7vi4mXUqiLKMihcUzGHwc0h9WnR+JRUYAVVlTSEVGddobzmBsOCkdBtlVD82wutgn8aiYsy6qjwLWgxrY0/xR1WXbezto2hJ4ZOiTHH7o9u83Q48qhnLfg/ST7yxPSd5jGTZ9IUbVxKyXt9MxM53FUByM7RM5upfYpWpB8rHN6Snl7xC9QKNGHExu/ynlBpTao8JRuirpV0uRn7cVSfww6jVn9rwPFm9eJGKNc5g6jqoLVnMIBqcWIoEBQXB4j9lm5rgEv8irxs43Oc/X0iztH/itrxdQkpaVY1Tx4GXWhIq1jQTBlan2bWrpqnlH1LVQydtUBbKWIZxqSnqRYnu8kjbkBptY97YoXCZ55bZrW//X5pZHO3uGPR9R2x7BazB+69idpd0ZU8EI9dQSBVfrsxkv2r+/kB/Ayszc5Pj2joj9JdfVJfOic2EKqo87LhM4dyxaYRyiGRnhsSpeNb+rf9Xg2dE1KE+yLi57oOAzivbwodB49moKjv6StaCqza6H8xiuhn3iBF7nQ6yzShgYiKvU6PdY69OxYhzL7v0Pe2tKcWBx6vd/cP79H966GmBEeb3iZnX8PSDBCBYrsw0YVXlj/Pn6kViRggFcFAgTkhID2ZxF96bimOm78/NU9AUwUgVY3FYISUl3eFQYcyQTJH6fKr+hTEhp9S2dfFvUYuRZZP+zp5DXjwwXo3X+abdj6hgtZYcZnnUOPkSJeVZ8fzAiuz7bKUhDI/uV5wahiuqVmbEN0ganiIXXFHrG3FpFelY6SXogt3kkC3WPfNEvfxZwRVr7WA06Zp9QJF9C9521NH0Fy+fyx+Oy5+okY57IEE1nms+VrCiovSn9jT2I9LfWXbl2f+J7nkyxLtQp8l3wLyz09p4mT6RxGzVGNx+Rg9aqe2keb5+4sljGSjlie8p6aN69KtO7rrJO7KoLCIhELIbwaFMOCfpmbiINCPYs7DBSGOujnzDQ/yniGbRCj7A4/52B4OWxOctI8zuEU+1DQagFBzbeXXnbf6cnjIMONdsFQYG6RcMxfQDZTjj93nzPDaUh+KwWsMx1A995FSTxFnAbXS4FyiX4F/IcvazD6TyoQeyKBORkwntguhYuXKpzgCVBn1vyGXTso08IfxaiCGLMHACKHlQr0vKNHooARiRDrwPGe8cq5ohWzpOyUmmMpeVX9RApyVLKcPNUZ0182aHLLP74yJbWv1fQ4SpRjJ+cDs+DiO7l9YxQHsXOE7L0jn8y+iL36S1VfmarhxrY39RzX7tL6ukw/S51sNuy6f5wpWPFwyahrsD9UdapIuSuvW/YDPX8eLFU5jmJHgTagvQsYnaJcqU1IfzRoXLDkgFYFwQPCUMOYau1tSx4nmgwLsoYiOVsYrPmmnw+CV3Omv+wl10HpZGO4Hcvdh5x6cl5/FXjFeo8a0pRbO1UEx3TuvEdiABwyn91nJNP2GHSradpJarw4Wl5aYJDi0ALN7bm7iGNiA33B112Bdc/xKzD881+HWgldTzmDZZpSLwurl7Umw76SAARu9bxHwDb8y7A30Ih3+SsEFezxnZ4PsrikOvjPKtoqwImZOTqoDMvmWH3eeIvD0LrUJmVSs0CVCMmJfnRZHzAkSaHeIpHHxf6BOk9Wv+/6niV0gzygDd7p7QvY7W/JvX8RsJwq0fxaRp+lpYqF9R3GCYqEN4e0CujUE2uWvQAJQ1k2lnO0qPjh9eOfy9873F6CwANB4uiRuB67ZyH1fatV+TW6+MVO+J18pRNb/LDgHj20GXN96mzMem0rFPQLz2oCOdsN3z/TIXGTN9exwtP63wYrHhnFxwn0dhefh+Ki8qCurQAPz8hr8ZVH1v3sKE5MREOKLcoaf4b4GvZuN+9bNIvW5bCBjaTxKKerK7Xxxvc7xxyPyw0z0LqGXLkJiZRUaBgVA95k3C4LtgqvlOeVe1eIM3tTtF++qTSZDaoAU65xb1Irm7mxlCNXcRIuTrpl2Or/wiqiNy8Ey+m2K6bQGSiUEFH9nNQpyOA9RC91RkBZ4Wrq459ZhfM33731DS047y+6gGkF8UhdUl11qWerbZNFhPa2sKBiPzyb6wHZzeBMWUjI30KnKnk+e1OXIYGPevR505rnfqDh414v3pYorZcqz6nDqCNkhIEXN8SmTHVatkL+MnWx5sBH+wwC/g12geWblFbQaxnZxGtU0a59t3SFSjDp6yb9n+RZIXtE5Tph8TpZVXToYNK/OjL9MBFU3qibCdyM4DlbLC8l1Oge7kYWfqVylkni8uqED3bAy+zufoAdS4aWnzFhg+AOVAvSwsGIDAVw+InFXlUsR4kOknOMjUeeRFeK0c7nCwbaPVsGu6UKzVGIeqdd1lvTN6G2dPXe4WCY+NkIigdkrlqUSDX/vgJUo+W6vxRKxwofXYnF8YnAh+2/FPZNy1T09T5ggJpkklzYwEIESABZg3I/VvNygR6X0d+aQCljcNOCDw738eUMc0/f7XxJUqm3d0o2h8olRN575xHrsHY8Y97moxTgmw4wtBoEL95gjliPLgx7AuOBRLJ5l1B06Y1i8L+QguMw9Oq9wVsBRlOdRwm0LObkGy8N4wjzvj9+OckioOmkBQWqzvoLDfUdthPBK95laXQlZ85+kz3QTaL++AjLh0ezmvP3B5pOC6j12ZuRdU4yfQCSdYN3Tffs3+u0/g+3TNM5fzZpHKLxKwvKyslyRyb18fr88/mxdKizR7ejHbSgdqlAeuYUKUNrPwnLUiDcmauQGpboq1IjjZCNKb6L4S9vmKtrATGBydlMkOessWEE5ZzNOvzF+rWz+fizuu7tcRpTdniN1HCkd5F0z2YfrLgctE0yxbKA7OvkuEI86z/xonG17tFT50ojIu7GJqSJ+0cpz+tzj7dn729Np+aPR+DyWOQEGH6y5rSBkfuREkuiKH6KqawYNgYRIlhvm7ftYQEDQw9VBjzEgetapPgQZ12UAomUxelgeul7iV/CfkjXI9qL1DLWK1DpSvqP/2RWwKFJ9UFOoERCkdjiphBNcXG8/Qu3+6qxD9zd8bAKq3TBOeZNFukEOuJ5OaiRZ68Wo/73lX4DezknuNzG9oESCOQ07Wzh4/NpLpFp9EKMmEdXCDI1ZmViBrC7vqP4Sa3Be+sO44Hn/Ey1yJrJCEKva2e8ZQQVA3AoRYeT6OKwBO+F6jWChHquzyW/kpqUt/qYpbS0eopny33d4u4LiRdztgSQ9QU9PRKTgVNI1IUx2O90JeoHWGOlR1eGUcPdaK8jZZGbmej5bot2wVoswEIaXFfMASpPNaStHJnP67QiUsl50XH67FWSdKkn+nQU91UMt4z006Hdu+3JS2/dkdCuwvKDQAFCzr0xdc/Js5FHRgCqTTfNbcE7DX8Nlt83LwVr/EMZ9fwqFpDDPEGhix/nkS8pv5mZb1iy03j1T3e63IwsdmYCHYnmMuLgwB89IAHjI1N0BAyAX3Vfzuk3cYh+9B4sa+vXlVKNt5wy2Py4tZA+DnOUur/L3eIs/KBdSvGyfPR0gGUxYJl4PRy/kYh/sLzvrNPok3/CfE9NE1PFtyZTsHE/wEz5JD2RP/3YvHDjyA3PYhJiHjENZz7D/ty3B/w4Ale+0+fVJZPHUT8ehlzDo4qrH2A3pkgRuBGR6LpV2SBwwU4AZCwdUmtXV7yVsgMHvatUVcrfZdcAAZz0VR1MsHwCfpu3djwpiZE5G3g4DGsTyIv8JpKnPSLv1X/g6msQbaC7CjDOSJipSu3AHcfuG0hFMOep9C5plvcNipXpGcyPD6kSulVXF7fq+/2C1vzs04Wjiq6PHtUYPNEzPEpNyyeHY+wyDhsPwlAM4ctoju0Q6xb8zGv9tPl+bFM+77nVVoveOBBeMBkQoF7NO89AFUGdn5ws0P2pMxq4m+bxXJmJmbdoczBqY4l9fjwBIROLzeb0CUAjBI3csZPo8S2ZMaXjmc5xeqU7rDVmWyntOBUQ61HYFTKmU3kPapKIMwxo6DYI/y3hMJ3Li/MLHTUJvlz7XIn7+qlT42lZ6fSEyFoDKvsXIoZK1aPvNfqYvwg3YxiwIuAgSpvXzgGT0PbEfyX1/7RbeKA0LbNr/jnVy0/UzzTMniOfeeJbcrGCYkJaes7BWZtg1YAIc0UrRNGoWJxyf+EBWVBgaaUdyq8uYKNPFdNy8xjDGlA87VXl4GOiG+dmo0PCGWOothracgc8VGraqKktjqwopABE7KZ0P9kvzq+ukh+6SuGHQW/vyN5sxb45iXP5tbm+vebYsNH1Zuxv3BaIZksa0XHFx9KBoA04r3qIhiL5mB4nHyLKLNSzpnl4pF2/HRVfq1s0lEnuYJhCJLierxHJANUaV54032lS6afi2vG8ecI2NlX+kXhIAoGBZeBQOufLtyIlhDUGTGIzvC8k0tuHwgtwbn7JrkG/MdzUtZzqrL9RALFhX4A8OeiZ7/4N7gADgUctR98eAVgHBLHk8dR/b8n/X3gp8FynSzOCWhq/DwYzCMbzlfCZEyyXc6X8ieejCYcfmVP3W9aiC76hhqpSa/fmYxxsgAM+xLkZQyJQqYzyel0Nw62p58VoxrWov2dVvIyAx7Ak7evxD6fIXabBdB3XbWeJxPR27tylQOL3/h7p8PtGMPjwkzcVfiM3kT6bpdrJ3j2slLvdtMSEZpsqXz6NXAerRXi+2wFewmi4tQ3IW2ntNsQswYzq8pdZabW838blWQxV3Bt+xdIud/rU+ODtrEb3NYa3BQ77Cii1gCHClVB3QVtdylbCrswrVoeDSdWInXg77wrH1mtFZjjU3JmY4EeEMKYedzPTU5kJO1zx9bzXkf81XXFO+S22BXnTUXlNfktqyrgDGB2ffNhG2c+PIaliNloOISoJV3XDccMfRtZnhfh275OLVHr1CEpsYBQIqn13XsKeDdfbSLLgkKCozyZNZjZ8Xe22x9N/yB+W0Bh21op/RlNjJVb6okHT3UzDOY774p/RNSnLrBCVXfuD5k74ueYTuFe/7QNYVYwFH4pDUkAOm3s1yna5/F+97/4NC1dHTapLJqTZ7fvAQdx2QPlC4/fGOKx3She2m8FqW9shHfvg+Ao1sRGlAckyqXe3stTf71fYfXz3vPR6fxbW7u1CN309qae5QnvjwHbdDuqLtPBo6HApQtEvHB4h+O3W1+aYSRHtUrFB+7/vM5IefW5O8T7tfEyHseYlDFpOKIKvQEc4ETfCqpq5IZ21eN9LsPlTF7J0m5w9p3p90AOg6JvxPk
*/