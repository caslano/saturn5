/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    callable_base.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CALLABLE_BASE_H
#define BOOST_HOF_GUARD_CALLABLE_BASE_H

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/apply.hpp>

#ifndef BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)
#define BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS 0
#else
#define BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS 1
#endif
#endif

namespace boost { namespace hof { namespace detail {

template<class F>
struct non_class_function
{
    F f;
    BOOST_HOF_DELEGATE_CONSTRUCTOR(non_class_function, F, f)

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(apply_f, id_<F>, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::apply(f, BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template<class F>
struct callable_base_type
: std::conditional<(BOOST_HOF_IS_CLASS(F) && !BOOST_HOF_IS_FINAL(F) && !BOOST_HOF_IS_POLYMORPHIC(F)), F, non_class_function<F>>
{};

#if BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS
template<class F>
using callable_base = typename callable_base_type<F>::type;
#else
template<class F>
struct callable_base
: callable_base_type<F>::type
{
    typedef typename callable_base_type<F>::type base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(callable_base, base)
};

template<class F>
struct callable_base_type<callable_base<F>>
: callable_base_type<F>
{};

#endif

}}} // namespace boost::hof

#endif

/* callable_base.hpp
iY0wVY/TU3N5ABMf20bFvB2NOYZZ23so0SpWdQdJpZXRK3GEU4J10rlDu95JqKgu9apkYk+5EgxBN/BRV+ThCFUiiEM9qR4m+inzhbgJGy8q4GFifZEVpcjCpPG0qqzSdlY1TBrOdoaJOdVJQNvOc0I9d2ILjc87PXPPpdZUgXzif/YRzTBpPoGqJFGnUb3QdBou22h1AWndhYlJlFpYwFdt504lTDAI9WkzJMuamIKCujn00AxIMtxwpomsFSiqdbxqMjXu55DaNFnZlS/UOowI0sys6MyjuGhdzFGbb3CFVMi29Ig3vQxJYidyYsA+gW3sFh9eWzaLBFhfJeKyYMAJtm5p3cdALRttXMJofEXAyjfWK5OTk8pnl4eHk9lM+wWiarA6KtY2p8hpsziqq+Tp4qqYl3M3TH3TNOlLac3O7OlN69F+IEFJBS+RUOhdXhv4k00Mh0aubTyq+g/nUpkf058up7K0i1ep5rWs6jsZd0fSgn+Onjz5daTp12xrm1G380TldTzylb1NUZXcWQJIyWubkte/jthr+zZIRzG6Tt8aOnJd2DZetSnEthboNaTKP7OjU/59KFHX9KdxDFn55OjQIrc+/vxQ02eLGrccyp1QJyMo+sQ/5MdX7NGjoQpyXSm4sq5/6Ado
*/