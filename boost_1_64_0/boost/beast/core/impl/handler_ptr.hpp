//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_HANDLER_PTR_HPP
#define BOOST_BEAST_IMPL_HANDLER_PTR_HPP

#include <boost/asio/associated_allocator.hpp>
#include <boost/assert.hpp>
#include <memory>

namespace boost {
namespace beast {

template<class T, class Handler>
void
handler_ptr<T, Handler>::
clear()
{
    using A = typename detail::allocator_traits<
        net::associated_allocator_t<
            Handler>>::template rebind_alloc<T>;
    using alloc_traits =
        beast::detail::allocator_traits<A>;
    A alloc(
        net::get_associated_allocator(handler()));
    alloc_traits::destroy(alloc, t_);
    alloc_traits::deallocate(alloc, t_, 1);
    t_ = nullptr;
}

template<class T, class Handler>
handler_ptr<T, Handler>::
~handler_ptr()
{
    if(t_)
    {
        clear();
        h_.~Handler();
    }
}

template<class T, class Handler>
handler_ptr<T, Handler>::
handler_ptr(handler_ptr&& other)
    : t_(other.t_)
{
    if(other.t_)
    {
        ::new(static_cast<void*>(std::addressof(h_)))
            Handler(std::move(other.h_));
        other.h_.~Handler();
        other.t_ = nullptr;
    }
}

template<class T, class Handler>
template<class DeducedHandler, class... Args>
handler_ptr<T, Handler>::
handler_ptr(DeducedHandler&& h, Args&&... args)
{
    BOOST_STATIC_ASSERT(! std::is_array<T>::value);
    using A = typename detail::allocator_traits<
        net::associated_allocator_t<
            Handler>>::template rebind_alloc<T>;
    using alloc_traits =
        beast::detail::allocator_traits<A>;
    A alloc{net::get_associated_allocator(h)};
    bool destroy = false;
    auto deleter = [&alloc, &destroy](T* p)
    {
        if(destroy)
            alloc_traits::destroy(alloc, p);
        alloc_traits::deallocate(alloc, p, 1);
    };
    std::unique_ptr<T, decltype(deleter)> t{
        alloc_traits::allocate(alloc, 1), deleter};
    alloc_traits::construct(alloc, t.get(),
        static_cast<DeducedHandler const&>(h),
            std::forward<Args>(args)...);
    destroy = true;
    ::new(static_cast<void*>(std::addressof(h_)))
        Handler(std::forward<DeducedHandler>(h));
    t_ = t.release();
}

template<class T, class Handler>
auto
handler_ptr<T, Handler>::
release_handler() ->
    handler_type
{
    BOOST_ASSERT(t_);
    clear();
    auto deleter = [](Handler* h)
    {
        h->~Handler();
    };
    std::unique_ptr<
        Handler, decltype(deleter)> destroyer{
            std::addressof(h_), deleter};
    return std::move(h_);
}

template<class T, class Handler>
template<class... Args>
void
handler_ptr<T, Handler>::
invoke(Args&&... args)
{
    BOOST_ASSERT(t_);
    clear();
    auto deleter = [](Handler* h)
    {
        boost::ignore_unused(h); // fix #1119
        h->~Handler();
    };
    std::unique_ptr<
        Handler, decltype(deleter)> destroyer{
            std::addressof(h_), deleter};
    h_(std::forward<Args>(args)...);
}

} // beast
} // boost

#endif

/* handler_ptr.hpp
AvGNdo8Te3L0ckzExTGRrWMiavbEREYa9Bnui5PgPockzX4kHNVpWi+JiQB6xvUC5ktDvBXixRjnBQj6eeVXcYISXgtRRghjafIRlwnE+OGae/zamvT/F7llGzh3jkf4y8MNwtxpqJS5U7kwd8K0qeflzh6XNevc3PKlizyyDQOQx4HxMcwf0lCmjX1jP4+TTTJtKA9tk/JM7dvXwr99QzvrN2PRPsyApUW27SNNvFFvpXCF0sdV6d7xOsH2UyaP/S11qPPHemfo53c2500253R250d251P251Avy3lZabUjLm75h6/lt9p0cP/oXUftzvtCP2e0Oyd9Ws7v/vhSzqG7yroe/Pb6uol/7/XgZ+ChyfWd78xN+Wner1tfFb3PEX/szt/Znc/anfPandvanQOGfm5rc95ncx5qd84Y+nmozfmszTlp6OeJNue2cs5IMXhZK0c63L4Yjxr+dn8z8/3H9+IOzfzNfA55IGOBScBxwJ6Mk7fE942864SevCV1lhRPf0FdeWY0iGdGU4FJwGyeJVxMf0xLeIZUTX9MVzK+nvEbeKa0g2dov+HZ2yvAwcADLO8d4DDy+IcDTwcmA0cDzyLvXs83HZgKXAFMA67i9c+kPVxDud6h7+hLSn7oR5UPg9p0vl0ttID8hR0IWRXkMRj4C40VRh4DggvfiC4zr2Eb4jtdXp7Dfpe176TjLju+A8JifJ8hFCJ4eBBb8fd2BJ0X8SjQjh/x+mIvTyJ2idm/0lDEsxDKEGr1NITDCL58im6VZr9LEyt9+RTASjevYj/weKWZZxFbhW9eBF/exdgq5AXmAX15GDVVZj7Gxl4Ripexs8rfR9PxKsSBsUtRBoLO0xirI/LkAT18jZ1LvbyNevzduNTL40gA4yodwcPrmLnMy+/YusyK52Hmd9Qjz0GEw/r15V7fTunL/XkfJbgWMxjpOk4A/wG4DffYF9d267TAmT58kIPLQ/P7NGAF2o+wDsHIE7kH8RzE3wV6eCPHV6BtwL4rT8wnVM7KwDyS6pXWvqEKD0aZ+CR7V3p5Je/i74RVoEEYgPhMoBXvZMWq4Pgn1ahL03klyF+L+G5gN8QPAkcCY1ajjQgenkom/q4DlgF9eSs7V7v5K3uBryN+GBhb7ea1pAON/JZMxMcCXcCOmegXoIf38mi1m//yOtDIg4lZY+bDTER8G9q/C+F1hK8Phnkn4d+p+f4vL6goLJLP/5P7/tft+6fpurETIjSn+KXPnV9anpFfWVBa6rH/fxAbkvSJKl3SMpBLo/3/P6doSi+jFb97Vuv6ssS12JC4Sox6hWj7+LKKgoXYuyr58Sp+73jyxqhv4mqJV+A7OxLnIpE6DWXCi/k976FZrfSiHdSPKTGkWenYlCN9vZ6Okpfg/1yHw083Ol6/z1I9z3vYs3U0pBd49f0k/TrI7XRTstwd5doftfNwtbWykVEm6aW6DIOkD9Bw4sBrHpqXUMrNhnrmS3pn3SaZpG/XrmQ9nVU9e7UhuOqlyVf1pEv67zFFZmttWc/zcq2L6JQcQe4jukyDrlPSFXbUIpzucZF+zFdy5pukn6KUntB2iQ+HBGxPt34dyxoawbLOj+4JDRWZEobySA8ZDKGPFultI/1MD31No7uASM2UXqXSX2UF5vStKv0py/SHVPpdpvIpx9ukva4EJWNdJfFkJUtdLPG+6vu53KSvtC7Sq6/UAWE2Qn/dT/llPs+Fwa7Ve/2oh2HgZS2T/MO07iibzwvLSPPXWSMPq1LSO/JZ8eTvxXSHdpvELexr8PkrlvTJWgbtymWrMuIt7QhskLREzJRozh1vHcq2XmJg+3MeHsV7/U5Mb3C4jz9/mhaTdek=
*/