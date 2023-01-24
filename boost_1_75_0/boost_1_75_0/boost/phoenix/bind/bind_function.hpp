/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_HPP
#define PHOENIX_BIND_BIND_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename RT, typename FP>
        struct function_ptr
        {
            typedef RT result_type;

            function_ptr(FP fp_)
                : fp(fp_) {}

            template <typename... A>
            result_type operator()(A&... a) const
            {
                return fp(a...);
            }

            bool operator==(function_ptr const& rhs) const
            {
                return fp == rhs.fp;
            }

            template <typename RhsRT, typename RhsFP>
            bool operator==(function_ptr<RhsRT, RhsFP> const& /*rhs*/) const
            {
                return false;
            }

            FP fp;
        };
    } // namespace boost::phoenix::detail

    template <typename RT, typename... T, typename... A>
    inline typename detail::expression::function_eval<
        detail::function_ptr<RT, RT (*)(T...)>
      , A...
    >::type const
    bind(RT (*f)(T...), A const&... a)
    {
        typedef detail::function_ptr<RT, RT (*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, A...>::make(fp_type(f), a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function.hpp
PyMbz+HBfIcS97BssOBP9GYUd8tBQLxbHoEBctAeOgghCMp7zZ491Ct8vOJQ14RMmnnD+vu9/cJNpF4bUiYLETA5hJa8hrR6ZVz/newavr7eiP7slfT+WeLWqPJwTBkGkuOkifQuIPdKOAasumibJufbBl335ptrt4Q+XFG8OMXus15cEY6Qr/QYd+537b1/H8jql+U2hoyBzRve12Uh66aHvSUveFa53bV8ahj6vaEv+X+56f38RQ3yxO//4wXK+ndRTeFU4Az+n6Y/9P9RVP+jpixm7mDjqGphYu5g8W9MGv0RDWG3lkZqEdzVdNL1mz1dgLlA6/mirwN9EvmcrZaO2roL86KcS5w/s4HCWbXnYoCkpmqZFqcj8Wgh72AJsyF3CTcu0Sy1w89gGgQ6ZbqZa1kFctGsDkE9eXFha5usAxEON62zKfn0hUAjeqMj/6OtdjfQpM9kZqbb5eVdvt77bkSe9oMGA71fxXdD0PJMVyF3gUo6P1yYb6BQPqhz6oU8g7ziVuhnsI9e5VEDtlfeHYMxVz0SL/kvmF+ffsnOpzE+zHe9ubz06sQrkyRSpojjDgiJFZXo9Tdb8GngLwm+DYM90Cze3E49tNhqmjwcJtqSWT9gLmeUt8qflnJiwDKN+YkU8yJGYTd+lcJaMJu/3pYMp1uyomG/QnrF0HDC7HUzAo489tVeT3qwsKD1Q/k37OQuAjhOBqo1
*/