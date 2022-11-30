/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    is_unpackable.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IS_UNPACKABLE_HPP
#define BOOST_HOF_GUARD_IS_UNPACKABLE_HPP

/// is_unpackable
/// =============
/// 
/// This is a trait that can be used to detect whether the type can be called
/// with `unpack`.
/// 
/// Synopsis
/// --------
/// 
///     template<class T>
///     struct is_unpackable;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         static_assert(boost::hof::is_unpackable<std::tuple<int>>::value, "Failed");
///     }
/// 

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/unpack_tuple.hpp>

namespace boost { namespace hof {

namespace detail {

struct unpack_impl_f
{
    template<class F, class Sequence>
    constexpr auto operator()(F&& f, Sequence&& s) const BOOST_HOF_RETURNS
    (
        boost::hof::unpack_sequence<typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type>::
                apply(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(Sequence)(s))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(unpack_impl, unpack_impl_f);

#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
struct private_unpack_type {};
template<class Sequence>
struct unpack_impl_result
{
    static_assert(boost::hof::is_invocable<unpack_impl_f, decltype(boost::hof::always(private_unpack_type())), Sequence>::value,
        "Unpack is invalid for this sequence. The function used to unpack this sequence is not callable."
    );
    typedef decltype(boost::hof::detail::unpack_impl(boost::hof::always(private_unpack_type()), std::declval<Sequence>())) type;
};

template<class Sequence>
struct is_proper_sequence
: std::is_same<
    private_unpack_type, 
    typename unpack_impl_result<Sequence>::type
>
{};
#endif
template<class Sequence, class=void>
struct is_unpackable_impl
: std::true_type
{
#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
    static_assert(is_proper_sequence<Sequence>::value,
        "Unpack is invalid for this sequence. The function used to unpack this sequence does not invoke the function."
    );
#endif
};

template<class Sequence>
struct is_unpackable_impl<Sequence, typename detail::holder<
    typename unpack_sequence<Sequence>::not_unpackable
>::type>
: std::false_type
{};

}

template<class Sequence>
struct is_unpackable
: detail::is_unpackable_impl<
    typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type
>
{
#if BOOST_HOF_CHECK_UNPACK_SEQUENCE
typedef detail::is_unpackable_impl<
    typename std::remove_cv<typename std::remove_reference<Sequence>::type>::type
> base;

typedef std::conditional<base::value, detail::is_proper_sequence<Sequence>, std::true_type> check;
static_assert(check::type::value,
    "Unpack is invalid for this sequence. The function used to unpack this sequence does not invoke the function."
);
#endif
};

}} // namespace boost::hof

#endif

/* is_unpackable.hpp
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
*/