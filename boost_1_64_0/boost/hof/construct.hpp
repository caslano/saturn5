/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    construct.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CONSTRUCT_H
#define BOOST_HOF_GUARD_CONSTRUCT_H

/// construct
/// =========
/// 
/// Description
/// -----------
/// 
/// The `construct` function returns a function object that will construct the
/// object when the called. A template can also be given, which it will deduce
/// the parameters to the template. The `construct_meta` can be used to
/// construct the object from a metafunction.
/// 
/// Synopsis
/// --------
/// 
///     // Construct by decaying each value
///     template<class T>
///     constexpr auto construct();
/// 
///     template<template<class...> class Template>
///     constexpr auto construct();
/// 
///     // Construct by deducing lvalues by reference and rvalue reference by reference
///     template<class T>
///     constexpr auto construct_forward();
/// 
///     template<template<class...> class Template>
///     constexpr auto construct_forward();
/// 
///     // Construct by deducing lvalues by reference and rvalues by value.
///     template<class T>
///     constexpr auto construct_basic();
/// 
///     template<template<class...> class Template>
///     constexpr auto construct_basic();
/// 
///     // Construct by deducing the object from a metafunction
///     template<class MetafunctionClass>
///     constexpr auto construct_meta();
/// 
///     template<template<class...> class MetafunctionTemplate>
///     constexpr auto construct_meta();
/// 
/// Semantics
/// ---------
/// 
///     assert(construct<T>()(xs...) == T(xs...));
///     assert(construct<Template>()(xs...) == Template<decltype(xs)...>(xs...));
///     assert(construct_meta<MetafunctionClass>()(xs...) == MetafunctionClass::apply<decltype(xs)...>(xs...));
///     assert(construct_meta<MetafunctionTemplate>()(xs...) == MetafunctionTemplate<decltype(xs)...>::type(xs...));
/// 
/// Requirements
/// ------------
/// 
/// MetafunctionClass must be a:
/// 
/// * [MetafunctionClass](MetafunctionClass)
/// 
/// MetafunctionTemplate<Ts...> must be a:
/// 
/// * [Metafunction](Metafunction)
/// 
/// T, Template<Ts..>, MetafunctionClass::apply<Ts...>, and
/// MetafunctionTemplate<Ts...>::type must be:
/// 
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <vector>
/// 
///     int main() {
///         auto v = boost::hof::construct<std::vector<int>>()(5, 5);
///         assert(v.size() == 5);
///     }
/// 

#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/join.hpp>
#include <boost/hof/detail/remove_rvalue_reference.hpp>
#include <boost/hof/decay.hpp>

#include <initializer_list>

namespace boost { namespace hof { 

namespace detail {

template<class T, class=void>
struct construct_f
{
    typedef typename std::aligned_storage<sizeof(T)>::type storage;

    struct storage_holder
    {
        storage * s;
        storage_holder(storage* x) noexcept : s(x)
        {}

        T& data() noexcept
        {
            return *reinterpret_cast<T*>(s);
        }

        ~storage_holder() noexcept(noexcept(std::declval<T>().~T()))
        {
            this->data().~T();
        }
    };

    constexpr construct_f() noexcept
    {}
    template<class... Ts, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, Ts...)>
    T operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, Ts&&...)
    {
        storage buffer{};
        new(&buffer) T(BOOST_HOF_FORWARD(Ts)(xs)...);
        storage_holder h(&buffer);
        return boost::hof::move(h.data());
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&&)>
    T operator()(std::initializer_list<X>&& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, std::initializer_list<X>&&)
    {
        storage buffer{};
        new(&buffer) T(static_cast<std::initializer_list<X>&&>(x));
        storage_holder h(&buffer);
        return h.data();
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&)>
    T operator()(std::initializer_list<X>& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, std::initializer_list<X>&)
    {
        storage buffer{};
        new(&buffer) T(x);
        storage_holder h(&buffer);
        return h.data();
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, const std::initializer_list<X>&)>
    T operator()(const std::initializer_list<X>& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, const std::initializer_list<X>&)
    {
        storage buffer{};
        new(&buffer) T(x);
        storage_holder h(&buffer);
        return h.data();
    }
};

template<class T>
struct construct_f<T, typename std::enable_if<BOOST_HOF_IS_LITERAL(T)>::type>
{
    constexpr construct_f() noexcept
    {}
    template<class... Ts, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, Ts...)>
    constexpr T operator()(Ts&&... xs) const noexcept
    {
        return T(BOOST_HOF_FORWARD(Ts)(xs)...);
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&&)>
    constexpr T operator()(std::initializer_list<X>&& x) const noexcept
    {
        return T(static_cast<std::initializer_list<X>&&>(x));
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&)>
    constexpr T operator()(std::initializer_list<X>& x) const noexcept
    {
        return T(x);
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, const std::initializer_list<X>&)>
    constexpr T operator()(const std::initializer_list<X>& x) const noexcept
    {
        return T(x);
    }
};

template<template<class...> class Template, template<class...> class D>
struct construct_template_f
{
    constexpr construct_template_f() noexcept
    {}
    template<class... Ts, class Result=BOOST_HOF_JOIN(Template, typename D<Ts>::type...), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Result, Ts...)>
    constexpr Result operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Ts&&...)
    {
        return construct_f<Result>()(BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};

template<class MetafunctionClass>
struct construct_meta_f
{
    constexpr construct_meta_f() noexcept
    {}

    template<class... Ts>
    struct apply
    : MetafunctionClass::template apply<Ts...>
    {};

    template<class... Ts, 
        class Metafunction=BOOST_HOF_JOIN(apply, Ts...), 
        class Result=typename Metafunction::type, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Result, Ts...)>
    constexpr Result operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Ts&&...)
    {
        return construct_f<Result>()(BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};

template<template<class...> class MetafunctionTemplate>
struct construct_meta_template_f
{
    constexpr construct_meta_template_f() noexcept
    {}
    template<class... Ts, 
        class Metafunction=BOOST_HOF_JOIN(MetafunctionTemplate, Ts...), 
        class Result=typename Metafunction::type, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Result, Ts...)>
    constexpr Result operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Ts&&...)
    {
        return construct_f<Result>()(BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};


template<class T>
struct construct_id
{
    typedef T type;
};

}

template<class T>
constexpr detail::construct_f<T> construct() noexcept
{
    return {};
}
// These overloads are provide for consistency
template<class T>
constexpr detail::construct_f<T> construct_forward() noexcept
{
    return {};
}

template<class T>
constexpr detail::construct_f<T> construct_basic() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_template_f<Template, detail::decay_mf> construct() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_template_f<Template, detail::construct_id> construct_forward() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_template_f<Template, detail::remove_rvalue_reference> construct_basic() noexcept
{
    return {};
}

template<class T>
constexpr detail::construct_meta_f<T> construct_meta() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_meta_template_f<Template> construct_meta() noexcept
{
    return {};
}

}} // namespace boost::hof

#endif

/* construct.hpp
4Ta4DugPH2ckyHALyPDrTsa85rTsXPGBJFUT3033D0hZ/85P/tbOSjk/KDvF/tEv+XtKSnmLUtIPSYmfmRI/4ItY0nf87JTzj/onf/dPyR9MwSeelfy9KiX/qJT0oZR4LYUeHZA+iZ6rrfRU+uNEUR+nqeGkxgo5GK+O0SdO75KD8QzYTniq5G99ezfrqylXKJZyHs5iyj+oxnyTMd8QNm8i7IMHWE8gZfqb2mxDl7iQTUZS/BfPcKK7vw25kJB2GSTtjn7VsrTzSqdEPlCE5d2tjmq+1Sw7Ig+OHLWHweILLv60/hmfh/Oy+0nOFguC1fTdmEeqMgx+wBqQipHYVf7hBIzUb/CxOqUkH270i8ffN+qQFbpGe9aoQ7BA1cEQ2bASyEqoK2JQEVvzjfAme1xbZmQaUZBc8ffFrqOq4lVBe1XzWB21qEJ1xJZujGxxduhq7Qsj+/5zU2DmiF8ctRIui0/J29cy4ZrbM+Gmm5TDG48MZ/Cqn9N65P6BP+fK/Rmmz+YuvLn5bY/4s4jxqClP4v65nSgcEFN3UG2Z6D9EkLwt6e5PzMBbEKhXTMQwEBA16MNG8DQ+V3y4XlFYE9+OMHUn0HiE09HzA82UQxHC93/LUevW0XpFEedxU2w3LqeATHv481aLn3zNspX4UB5TzuXd/IWJ0Mc00s3Iq+1QPCO/Nqt4hjfkEvvAYfKk/ihidTZUdMVwGT5mZvsDR+QbEV99Zkas5Ag2SyBih4oI1ZFJuwqjiEdJ9+D+isEZIRdR7dZsFVgN4mAhkLIDz/OaVfaLkdgemsfMz1thBjdOsNHgi3H7+sM0kk6Rs73IBAdlxhn+W48ok0hpQDjIBjnZHDNux78hWLwJYqxR07Qb3+Phn83zhe2lJtSNCZ9TLZ5FRapEV6gN7APzhd2426goR+5aaTR2KvwvmbaVh8+nInv1+In6pbl6KTEY3KvgOPG12SVnaUulal6dbarmUaLlVMwdWL+VTqO351b79oDnl/6RPFfk+QzxudhN3EvJs/Oq6ftAT5ZnTKaHkV+yaPnxCVAhthknUmEOcYOWYTbLAoXCm1m0QsSNUCV+NIDWvqQ6WryQ5PPwg1Yx4yIxc/W/WhYzS7K4QgTzzLh3b60yzi7lDRm+/fqEifqVuVVissdQVhb0hn6zH4Ic6zr6hNLq+HY2w1egvu+15fhRad8f4mb5o4fIYRitRxvCfHtg8ADTRwcYLYI2XGAScL62TBJwpUNO9N+lcrI6ykkakt6ZUJtU0llG0kfos0dALD9odmba3IY1tGAmusfX75jBd9pYiBVf6Q5V0KJt7zfRKStyZE8d7vftwmZcpegNZP6oIrPfZ935co4v3qAxP2e8yOdEuSU763ajBVEtKuvyj0j2gFcwUl2j/dRE91aF7tOZkjt3qX77FCPm4H57pdFvp51l9NvrESm9s21k37kim8P1qNzHpm0j8ryHCvuD2cFhVWKrHJB4QfWXJux5zXdC/DhCWagknNU20GTh869Y2VWC9XvxOE0orv0sbrRKF+23Zv5Q01hEB8Q54BbjiPaLEUD2lDHHSZ5Rlj3I8kiidZpykAKqUbUogxxTZT5qJqhraobaXA3if56IXmeJ3nqc8wegbYljLq42OGihv36mvelTxG39f35oFicmO401qUvFa29Rh8+la+pkmw2UihzOvBJ7/mHMS7yBoINsur9AYl4RQxnf8qpr17LrK+0w7gTEBohs7MQB17NrZ5sMPoY/Smv+K6n+Tk5zDafSGRoDBHCk+JPAzFi4gXHuEzLmPtKexdRccPYHNosHBg7jfF8630TmOU9qhU+G51DwJiTBe9UCLwR430uCh8saFDxH2+A=
*/