/*!
@file
Defines `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COMPARING_HPP
#define BOOST_HANA_COMPARING_HPP

#include <boost/hana/fwd/comparing.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct equal_by {
            F f;

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) const&
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr auto operator()(X&& x, Y&& y) &
            { return hana::equal(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto comparing_t::operator()(F&& f) const {
        return detail::equal_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COMPARING_HPP

/* comparing.hpp
4BabHO7tftxYht0ukesf4D7zfik3pcmXOzniMK/1yWsyZRa4fXyCuxDc10q4iOJk1qgS3IZDHe4LpVxskePlirp9AdxZPlwKKGRlSv3HwxAv4MesqAvrasezwX3Ahxtmzqtgbn64w5zrx6zRk8/pYD7mel/1aOII5iqTsAfPy6SBqKDJL3AemHPcTGcVOp5J6NibLM+/OcJh3+vPZo+5kPu/wZ3p5mqdGw6DOcPDbDmBP35N+v+PdJhj5HtTZb8zLe2pdDGVjcbbzQ6D2caQ/n+wV1LYNi9KbZmUNXWNeZGj4HMZLOUmCFvQFA/6Brhjlfw21NfWkQZwjiak5S3M+4Lk/L/Z4T738Qh3YnWkpj6MYd5IJ6xAAO55g9Q/Bn8rkW9nt4I9Z2o1c+3c+3dF297/aMQ7I9/gCmUkLX5FwX4C7BYfdjyX7Ygmc2ZGE3v3YxBrXcpGhGI6xq0rJvqwWWAX3Wzb5cJtS0r9qyjKesjLNKwZcXvRiGa45+Uy/hfswzxs8ptSv41uRYPmglgTGT8ZPh/3u6XNbzsNvGY1v9ihossHIOM/Yijrj0vZdkfCrC8h7R9wt+/zcrOGqdnvsATsBneetdiYcv7bgthDN9M5VUbDHlLB/QrcrxTugY31hzZYPRddBrM9sKfIbxxrQH5ce2x2+mycXk49t56zgL/Dc3zo+xyi5+a1s+X5hwnsa/SyS3oy3r3icv0P/Ce8fNvHlEtEc7zn44q6zxvw05dwW/+Vupf5x3O85fscOTPBvMYt7f8k+pchP27CaNXQz4g2Nwh2x6AP22lwWvxtIu+TW7F35ePR+QcewHs+m2D3gt3jz84lY/Ei95qNPP+wzWG/4scuE8Ma/xqKjH8G/2EvX0M8vWCGUw7zFw8TZ6WxMqX+BZjr90lmw8ENcvedFptY5HfnY2GHj7zX5HrTo0sv9f/BzLqY/Hr0Uv9gCuY5Cq8mCpNfo50yDdxy0ZYol46WiR4NelGnK6QR41bKTXDbvqJOp4J5gyhj2Yp4bXzBGwZvuuCJFqSpTJszOJvJxbMnM8fpmiPPA/MuL1NDm5X611mHOdirMKm1cp9xK+M/wZuh8siU1PVubJ5DTM/HCq9Vbz1OB/PLXpWppx7LxXw/D3+4i4mJqLK1mzvuVMY/gL/lxyV8LX2u1H89DvEPSr51nKsleHnw5qg86mVpMYmVJ+1/8K59T/BqmyKOd1jLXF/2f6bDvUDms8YZUjRoREv9VzAnjzC17AkTutu7Fxxe3QiP3T8m/Z9gXaWwqEvQErcrmBsXHealChNdH3tMX7mI+wIzqTB9uiFtseBj2x1+ZISv5T0RvE7w0grPnjlo4n0H3pEKj9QztOmYpTuwDvi54FU3WTaJHXTenrWzyu1/k/r/YH8/NMLGERLs+ZXnnxyP+aDKzOo7Q0KUcw+4vytcW6dY4/kVok2FpyL2+BOFbf0ysw0o9W/A20q0qSrqFdLpVIwalo4zSeT61wnw13u5GstY9v9gT50v2I1HNETqrRAJ9jmaXP86Eb7TAQ+TSjljZKIJo6Vdlw08A+wLPPk1DQpIzcW1MMeehD1tn7mZlFf2Mpbnv4H58EAJU2tMyBJwzfkerlW8mjRjp56MuLHP3czWeIYUt61mlergzq9gLwb7NX+2aaSNWIHZRyjqOH0KYsh82frO8BgE9wV/biymadyddKrDPdXdtrTYUfL8LzDPcjOd0H0N/l/BrTnN4V78Hrj28V+ZXKI9bRQoipy7jMWYOxfc4gKFq4Enz7/pxJnfguc51o3bjyby2Q1up8rVWJ/jT4fe24eCN7FJkcQ3Unk9c9fzwO1UuDr8obL/B+8tldeetZzcplHgjVU=
*/