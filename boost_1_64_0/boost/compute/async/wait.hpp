//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ASYNC_WAIT_HPP
#define BOOST_COMPUTE_ASYNC_WAIT_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/utility/wait_list.hpp>

namespace boost {
namespace compute {
namespace detail {

#ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
template<class Event>
inline void insert_events_variadic(wait_list &l, Event&& event)
{
    l.insert(std::forward<Event>(event));
}

template<class Event, class... Rest>
inline void insert_events_variadic(wait_list &l, Event&& event, Rest&&... rest)
{
    l.insert(std::forward<Event>(event));

    insert_events_variadic(l, std::forward<Rest>(rest)...);
}
#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

} // end detail namespace

#ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
/// Blocks until all events have completed. Events can either be \ref event
/// objects or \ref future "future<T>" objects.
///
/// \see event, wait_list
template<class... Events>
inline void wait_for_all(Events&&... events)
{
    wait_list l;
    detail::insert_events_variadic(l, std::forward<Events>(events)...);
    l.wait();
}
#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ASYNC_WAIT_HPP

/* wait.hpp
2FcrtLM4+1zob07y3hdYn/5a8POGOHFf3p+eya8nsccrO+AXdMhZeFNje/qi53DdvMXyZaI+l3C/+cfh0D3WT8hnWWPZ/3i49DI4erc+AX28W8+hf58vPopnVRfTKfrjP3vxm4nqLV/AfSeLsw+Li8fw61/w+Bh4yXOuGi3u0zcq1f3i3tcHexI9+Qr17gjzehp/Oo7/z8F7a/Wr/4SHX6MP/FfrDq6TR3exC/m9abj+zM3s27rs7XhIzlj+SL9aNZ9epo6Q5NyNtiJ1kvusV4KT8heq//7pOVbSnexjmU6PaQ33KVlLR8vAO77Elx8Xp+CI+ofg8yPgjVvk12Hyvjw7daD6p7iX8S84exT9oj/7fgcuPVh9/nbx6APzsBqfOo3/+iz7Tp3M/mt5sXS/jfjpefBFqbq4fVBjprneX84z0E/ZFAfnfqqvs5KOciVd4zd2bh3uytfw6dv1rdF5c+bqA3xYfXSxvJdBf3sS3k6yf85Cdf2r6UInw6PV4lGF+Z8Fz9wMPz5iX4Qs593AHbml/OND9YMt/BkOmUI/n2/9QZF4WfCG/NW9A5wZbb9z/nICffi5cB+j9vAPHbuAnjFXPt+k3nW8+FMrfieI73hGSyTeaP171UC4MVL97gjzd7F5j9CP+Dt7eZy/Fckf98TRS9j3UnjnBHrJ8fBOp47iNRx5GfvpIn/hKcWd5N0NscG4/CnvPsCfrftbVcc+7lfHsA9KTrS+2zv1WdiHpvlvOPIv+dG664Ly9ni8z43i5YPqdDfL553Y6RMR5r0DPRTu6swO1Udnfq0OkCxOXoh/HwpHivNZn4rzn8mr+hyWqK+2XCdePySfzKbn3Wp+lojjneirBeLWYDgmRx9IbzybnU/pY5+4k9UZVsjzzeKw56ylYyQfJm/+wI5/EK/uontd7r6uM7u/n1ezh1x/f6FzgF40L23wXm24HkdfUWV7eUlepFO0GKcVG+m72foMJ1sP1iU++L31jaVx7OMyOvoR8IX1Aivct/l661iv8f5z8c+7jd9NsfbVoO/8aR43wa092cfP8nqhusQl9PrDxK3x5pfOkXuU9+nZTp8gnmi9y6xT+fOr4n8Rvn21c5vwoHH8vtr4Vj4X8i39h/ZpLuzAL5/mv763/WQ8hk5TeQAvWmzfETy2hu7/z3Id46LfNpZO0Oz34bkpYf3+K+/7Nb5H7yxohQem49uL5eHR+hWcn1gCr6Tdqr+S/lLxmfj8Op1hEbz/mHMM4K2yQfrwwz60YjjjAnaVgQ/o66ytgCMH0VFCO4KfkvR7tA62zm+/cZznOd6Gw+5jBz/SGR/FG3eqZ72GD9MHpvSwD0R3/Mn+qfX72FU2v0yDjxLh1QR9jR/gVTeIp2eqxz4f7l9FN1hpv/5V4sjneOtgcalR/8so/H2EOtHXcNTR4TmQzo3Tj5zi/KuZ4mb5UPj7JbrN6/TAB/nRieLQeHFpkn6zw8TRpew8Qb/KYPFhrnHfLI/RVetKg+dPrqG7HsUvzo+CB+CxNvmzvzrtmerKZ8IPZ+FNM8SrE+jN8mjhd/j00+odBXAi/pX7t3pcAt2qEA8qYm8V7IJ/xoxTF2jgR+cE18+Br7ea56ZmOjx+mX2DuucP6nR1+nPPk1c/ihC/6UHVcLy4VYevReIRmZHi9J0+w31r1P+XTNHfWcAuevDDhzqqw8KRfd13GN76HnuvoleUWMf8G3/uz36Xihsz1Q/W6ac5HG7fJ37INw0L8DPrOJPvFpdr8e1b1Vlu4y/d5PdwX5Z8479Hn5j4vioRzjkYP9jb0blo+ieT2GNoJ6l0c/k0a7F5n+x6a/CDIfbjvYidw+l534gv7LF2oHi0zPj0oZs=
*/