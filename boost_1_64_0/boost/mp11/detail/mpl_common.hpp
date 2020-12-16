#ifndef BOOST_MP11_DETAIL_MPL_COMMON_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MPL_COMMON_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/list.hpp>
#include <boost/mp11/algorithm.hpp>

namespace boost
{
namespace mpl
{

struct forward_iterator_tag;

namespace aux
{

struct mp11_tag {};

template<class L> struct mp11_iterator
{
    using category = forward_iterator_tag;

    using type = mp11::mp_first<L>;
    using next = mp11_iterator<mp11::mp_rest<L>>;
};

} // namespace aux

// at

template< typename Tag > struct at_impl;

template<> struct at_impl<aux::mp11_tag>
{
    template<class L, class I> struct apply
    {
        using type = mp11::mp_at<L, I>;
    };
};

// back

template< typename Tag > struct back_impl;

template<> struct back_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using N = mp11::mp_size<L>;
        using type = mp11::mp_at_c<L, N::value - 1>;
    };
};

// begin

template< typename Tag > struct begin_impl;

template<> struct begin_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = aux::mp11_iterator<L>;
    };
};

// clear

template< typename Tag > struct clear_impl;

template<> struct clear_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_clear<L>;
    };
};

// end

template< typename Tag > struct end_impl;

template<> struct end_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = aux::mp11_iterator<mp11::mp_clear<L>>;
    };
};

// front

template< typename Tag > struct front_impl;

template<> struct front_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_front<L>;
    };
};

// pop_front

template< typename Tag > struct pop_front_impl;

template<> struct pop_front_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_pop_front<L>;
    };
};

// push_back

template< typename Tag > struct push_back_impl;

template<> struct push_back_impl<aux::mp11_tag>
{
    template<class L, class T> struct apply
    {
        using type = mp11::mp_push_back<L, T>;
    };
};

// push_front

template< typename Tag > struct push_front_impl;

template<> struct push_front_impl<aux::mp11_tag>
{
    template<class L, class T> struct apply
    {
        using type = mp11::mp_push_front<L, T>;
    };
};

// size

template< typename Tag > struct size_impl;

template<> struct size_impl<aux::mp11_tag>
{
    template<class L> struct apply
    {
        using type = mp11::mp_size<L>;
    };
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MPL_COMMON_HPP_INCLUDED

/* mpl_common.hpp
ZANaQkV5eDmCMSQG+ZBlkA+dnZ7CNxVNZDl1d+KssUhCQiySkDk9hW8qqsjRG7G7Y2d5kYSEuUgeOztNhY80D0avPU/eoyqghIBu0o7oCVVkHfU3INAbMNGDzMQKXwgVPhYZIn4/5hRmXYSncFueAi5dyoBsQEzoIoM3IBz9Ygr3W6Zwf5wpzEpAFJ2FMhKMoYwEw8rIm6i/XiGiei0iqjeOiBo8GUP1SUnlGL0eO+8RnfdYOu+J6rwphr45c36CdQRKMGTQHROC7pC20j3aTxC+jS1Me+EPCMbwBwTD/oBnl2Gf3QL9bgv63XGXh+w4RobDHPs55thnJwO5OlisdWBGXgv5QTAtnCPggWCM2T/RsYXJsppA7BSyrtMi6zrtso7JIsR5TLK0kPFP3gcW6pSRR64JLhT3U2wyLB32G3TUMjjfLEVwDglJf8gi6Q/ZJT2DI0ZszDGznqDZyPYHjhnMyKMM1W8phIrMGjbzMROhWUTQHDxrmNyYECY3pCPNl/kt91iuSYllobWsoQ7XmrRZQ7TBDKMQ0tj9GkGbNfRzLUPziesQmgOCNgcstDlgpw1DI0ZUTAWnpZLAqTLBqSRwMMMohDT2XynAqaSfVQyOm8DZL8DZbwFnfzxWsaUTU4izMYoGsBjI5TSQySLGtDCT/eViIJcTOBUMzvZrEZx9YiDvswzkfXEHMt/YpaDnG+cbr9zC8okNJhmPZL3yigPWJIJJpi2mhb3rX2E4aNjuxDcQzONLEcy9Yhnaa1mG9kYuQ3YwYzNxGfVrGHXIxGXERMwwCiGN/WMaCcJ2Kb6B4NxK4OwRq/Aeyyq8x74KMzhiTMVcIpYQNEtNaJYQNJhhFEIau18ioFlCP5cyNN+6BqFpF9C0W6Bpj4bmHsuNPjF9Ay1FBE6xyasi4lUxZVMhpTV/keAVJjR8A8FZTODsErzaZeHVrgS8GhyJLRoLqNtCkzgFRBzMMAohjd0XCOJgQqM30P93NULTJojTZiFOWxziRK2nORZeeQmcfPYnomzEjDzKUP2WQq4ohzihYSaCM5vAaRXaaatFO4V0Yr+7cGjMslBHoh49JnUkog5mGIWQxv4lQR2JfnoYnHuvQnCaBXWaLdRpjjeQeZrbvU3RYOZawHQRmG7smvUgF4GJGUYhpbUOl9CGXPTTzWA+uQTB3Ck0gp0WjWCnXSNgMKOZOMvCxNA5BMdhKkWYkUcZqt9SyBXlICc0zERwygmcHUIZ3WFRRiEdVykafCa2LhKgDoPwl92vHQGEpiVI2VRIac2PaRwt9IaGbyA03y5BaLadNXyhkBC+UMi0uel4hNtddYefy7YQZ4L6nTwneAUZyCvMMAohjf1Dmnk1QT8nGZwrCJx6wat6C6/qE/IqO7YyMkrg6OfCvBolXukEiKWQK8pBTmiQyfP/pbTRJXi1xcIrSCdQYHNiKiPD1OGISZxhIg5mGIWQxu6HBXGG6ecIQzOHoNksiAMJc6srkjg2UT0rlq8c7E4CZ8gcOido6AxRNhVSWvOfEEMHExq+geC870raCRNDp9YydGojh45tWc2NvSk5QP0eM3mFGXmUofothVxRDnJCw0wEZ6KYdsQErzZZeLUpIa9y42xK5sZe/XsJkv5zYRWul5iIGUYhpbUOTCNBKFPDNxBMmcDcKFS4jRYVbmNCFW5WLC9DSzdB03MurMF1Ew97KJsKKa35Ic0aXDdB08PQfOcK2mcTGtx6iwa3PlKDs03/nNjzrZP67ToXVv4xI48yVL+lkCvKAU5omIngFBM4a4XyDwlzvy1a+Wceiv2L8G2GFuocpB4PmdQ5SNQ5RNlUSGnNf1BQBxMavoHgPLiY9uMEddZYqLM=
*/