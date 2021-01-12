/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

    // Here is where the magic happens
    template<typename T>
    using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
        function_object<unwrap_reference<T>>,
        function<T>,
        pmf<T>,
        pmd<T>,
        default_callable_traits<T>
    )::traits;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

/* traits.hpp
tW99znY28Yw0oBcVBt/T22TYKcb54gxxtLvlMmgIpX2a5O8h+fWNcRyDt8aiHXwH/k+2uMrqcEMVx+9HfL5t3yxVbKV9WsbptCNxtn40Eqq4Nzluj44Lx6x0LyPuWO8H+AuV+xbslS4SRXzm9zCFvSgyhA9hDwvXNT3rbB3pp7+rvhLvnOhxWZZZl2tJrDYet56vUNhdJCNIvLvoTvvkYB3k9C9Qa69AZtNtfo+ns7z9nUnz
*/