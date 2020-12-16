/*==============================================================================
    Copyright (c) 2005-2007 Dan Marsden
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_THROW_HPP
#define BOOST_PHOENIX_STATEMENT_THROW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/phoenix/core/value.hpp>

namespace boost { namespace phoenix
{
    namespace tag
    {
        struct throw_ {};
    }

    namespace expression
    {
        template <typename A>
        struct throw_
            : expr<tag::throw_, A>
        {};
    }

    namespace rule
    {
        struct throw_
            : expression::throw_<meta_grammar>
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<tag::throw_, Dummy>
        : enable_rule<rule::throw_, Dummy>
    {};

    struct throw_eval
    {
        typedef void result_type;

        template <typename ThrowExpr, typename Context>
        result_type
        operator()(ThrowExpr const& throw_expr, Context const & ctx) const
        {
            throw boost::phoenix::eval(throw_expr, ctx);
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::throw_, Dummy>
        : call<throw_eval>
    {};

    template <typename ThrowExpr>
    inline
    typename expression::throw_<ThrowExpr>::type const
    throw_(ThrowExpr const& throw_expr)
    {
        return expression::throw_<ThrowExpr>::make(throw_expr);
    }
    
    namespace detail
    {
        struct rethrow {};
    }
    
    namespace expression
    {
        struct rethrow
            : expression::value<detail::rethrow>
        {};
    }
    
    template<typename Dummy>
    struct is_custom_terminal<detail::rethrow, Dummy>
      : mpl::true_
    {};

    template<typename Dummy>
    struct custom_terminal<detail::rethrow, Dummy>
    {
        typedef void result_type;
      //#ifndef BOOST_PHOENIX_NO_SPECIALIZE_CUSTOM_TERMINAL
        typedef void _is_throw_custom_terminal; // fix for #7730
      //#endif

        template <typename Context>
        void operator()(detail::rethrow, Context &) const
        {
            throw;
        }
    };

    inline
    expression::rethrow::type const
    throw_()
    {
        return expression::rethrow::make(detail::rethrow());
    }

}}

#endif

/* throw.hpp
lvx9g2XxjOTzW6yF30s+zxnyly7x1fcQXzXJXzCWw+oYJH3ua0hf+7pYxzj2TuIrIfEZx7Q1lPw1kjEyjSUfoSY5x6s0ZDlfbT79V0OWq4l+Wnx6PdWW5a0mOU/L+XtnAT19syzvL8sHSLplsaqMQW0rY087yBjT/jLGdJiMLb1fxpA+Iumv1dOXMSVyrpVz8E6XMSUDJN1wVNMjMAQHYR8cghE4HJNxJM7G0ah9d1XGmEXjSbTgdYxV8ZJenORjnUnOn1hc8qHqaanko4GkHyLlbYaDZazgaBkraJYxgVNlTOBKGQv4OLbHjTL27xB2xrPYVcb8dcNf8D70kTF9hbG35C/bJOdFOV+q/KntnTi0X6Lkzypj86ZiDE6TdGfKGJtZMsbnfvwE5+AXOA9/wgexpI8+dq48LsTK+DeshUuwCy5T9Y8PYwQ+gptwFe7FNfgurlXp4XqsSJ6fwFDchJ0xHbvjZhyCW3AEPo3lfG897mJn59yPvXAfd3H3xlzcredU/w3jLbw9r9p/G8+swm1jK/IwriJ/TIWXMRV38fmW1/EU/8GxFNtjyAchO4ZpZtYZoS8hnpBuZn5CUYsp/5f/y//l//J/+b/8X/4v/5f/y//l//J//we/v/T5f3zcOO3p/x32/w/krdYjy3Efna6e8yTEmeVLrVWZPorpGU+q6ZYYnrJOjk5Jtn3eVPv/0fx/pvx/TCqPtRz/barI/4/h/3dq/5+cGpdiGRelz6T9XzT/t0f7v5T45GbN7Z/BrirLnTYsZ/9Pfiq/Zv7/nGHZyWZ9uoXpIZud4tTSimX6WKY75te+gqr1fVhCw2gXed4cK8/bH5R3l84l9Atk2Ud8Dc+2o5Oj4rXXtEdZkyzj46bz7KyZ/tzOLw/PngMcz+0o5TgmOT9j1JPw+PzO/q7avQH296/ay9CooOcy+D16izI0/8+Xwfbcf6eUoZ48e69DGEAZ9hnLoL6tq73W/Paf+6v8EItbfwdjfYaxE2tKfbYnhJMX0ypDXrSvs9LhITlqpiUpUeuMYXuW65uLfPW156utf2UVL9MGBTr3BTnu6943ZgjzhLvkwzoj731BXNdnsO9N+4LY+wq1tz27lzypuIaSp3SnPKmYcp8XqQundLZIOn6STmlJJ9MpHUtCXvqAeEqnkTzDHyTregAhknSynNOZkhodfxvrVq/b/X78nZLkVK8JqZOdtv+tko+mUt7GhOHkI2y1IR93ud+Lvf9XEc/9v9JW+/71/b+KeO7/tW+177+1/5dt358uHUqSZXtItB1L17jkx/2E8B8/ltrK0L6Y5zKk37IMzf/jZbBtF3uKed4mQ9a6liGB0Py2twvX7bKjpD+4uPt2OTKQZd3Sp9RRere0Ozn+Ourv5n3xLku+Vsq6XUYYrc6TTvmabJlsTrXezvnIlp/X/T3sL9K/y9P6NeZxegnPfSjT1vn+W/pQlizpuQ/lvnW+//Y+lLbtaYvkqZXkqQUhKlB1VnDNk+GEfgf5utn53FhX9UrpsXWRfIXJugp3y5e+o91JXXnb1/aVct/Xo9W53i0Php3tDvKR232tUWnP/V6zH/O96/1eMyStBNmvJxLMavt43JhWckpSAjv2HezX4wIN68D4LZ8y0t9HylqFMJ55V5C+fIskJtYSM0n/Dvrt9xltyd/TDdtkaz+VP5O9z2gof2tJuHyzJlxSy5T6ySDEquOePX/awVi/ebbfPN7BNyYIcebp5MvRt9JKtORL8irTYqOTY9U9KtOCjPOp6TJvZdkfk5hukmnBtmm25eWYGqXyESv5d1lHPf3lvedSBy9IHaSvd6oDWfh/p+za+USuDawyn/H69LSUu6uUuxPhpOo=
*/