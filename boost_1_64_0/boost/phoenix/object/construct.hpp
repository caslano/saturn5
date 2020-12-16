/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_CONSTRUCT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/construct_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(construct)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct construct_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
            : detail::result_of::target<A0>
        {
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Context const &) const
        {
            return typename detail::result_of::target<Target>::type();
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/construct_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::construct, Dummy>
        : call<construct_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::construct<detail::target<T> >::type const
    construct()
    {
        return
            expression::
                construct<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/construct.hpp>
#else
    // TODO:
#endif
}}

#endif


/* construct.hpp
VHKtUnM9IHLpajhfcvb1+TaKLlZHaBpROl+h1Gkp2gUwniMUXG1/VWPKCh1T7rpSY4oF25XbWU0dbBHBBHrKauFat5VsFO1ax6MPR7r3YFPusSpxGFJSQxJVQvFvShFeHwPsNnjY4y2j1N1f2Yo+J0rKuYR9kgAvjTd7fZzux8SA0hW9qKZbbCJdl3jwcy1NLSpCFKUqWRH9psmgwyZibJKaxXjhWbZzqSe8ZSIiVklyV0R42KPWwCaI1FCWCSqN3hJOl81dKXk74z+hJptiRTKlqSVpSc0WhCmpx3ecglojhbjfphH3Ra8vGkAC6+qj1NJwRm1EQ3juYKPcgaGsw3bXm0VCqUGfUVE3ouHU+mg0GwTNYjgViTiNvJklXYUxq/U6LkTgrAyk9Ga5pxVn1FBxBVoIFqmaOlWnqTGD4blajjqDMegUtHx3G5pcnuQp2kkeH5LtQWOTKWGnNkJBuanLMXgOMPX0+qpZqVQkcLctqVjUzltGqXlI7e4tOcb9/Tci1es7ycB/4aBJN6EvO05ZFDK9vmNi1GcwSzozo5AmjmXHmKlPJIQmjn+XxMTxZiKT/sWphfZQSaI5p4pzvC5ruZLVZFC1mdFa0u1bRYZmMOeneEot+A6PMTeJicW3L7+ONFNkGpiXI9srebljl5KVs4ZX3+UIXie89rayI20JY+JD8SrFFtr1ld/msEkshgy6xZDWBPJvBIhO/44QuFF/gc29i/M42zeniMfEC/HkErDq7PuOvPatYPDC15uXP5c/lz+X/sH+B05cMWdZXEC7KrRVQqfapCawT+PJMCnbLOfIr+7jsmZZHqGujQldAqWJ+dUVPAM976aN2D/yMkwonCOvMvEkMT3TMo8RawWmnxVxKL9F0DDHyKAKbVc4DIzgdGs9gvPVb4ax+fptaX3B9RP75wlvKIO5NwfH2rUwgvFhU9NHR5BZaA4xRiTS3q0vs17Ez0F8qOwUbqJajxH77XyAaMHWLYUsdLada7qwbUWNnpK9Z6XHjvTm6Kk+82+hR2uvFYbw9jJyC4xodd72UvJvapQ/gvPHnj+/rr2PG5pv7722C25vlt8jjMek4GlNE6BW1m3EHY/hHEhC8m9Q5N/G8m9FRp4pnjt3KP/o8PztafuVEXBV5d3X8zh83upo+EwCn7veyPhS1QrtrjZznRi3dVsWPJa4WDoKOj+v9PjXSwr+CMZ/Uwi/LRz/7hPmUBEKVAbxNY6K9hgvRH+hvH5SGH/aNOLP+6dZ1BU8TfXVEGWjO7Qff/1uZW9ghnflEmLWHoMIehBUp2/ucvIbC3JZpqJ28cypK70H5rqJp1S9WAij9ihTqo9ilfP3BgV1fkP6yiSgmGfVIjwcIYLu7YTfgj2Wadqu7wDy3SQm1VWx6mI0YLy4c5Qm+iOzIhgMzT5zdzDFvJ85Q7IWvympVfaW0jN2nuw6NRjPwVo1mMTBBjWYyMF6ZsMQIXP2VUS8UkMcC/Rl0eWFRxKMbkR8ZRGtNeiPs77wxxBrnVc14pUarPesTNQF6zwrbbpgrWdlvGrBOHyrWj3Y9RUN4rVeHB1YSD+ewS7FDbw50B3QRZ9LS1BiIqUxNUipLBqukBZowdVkPDZPq0vh/8V+VHl3l4fOl5/dyX4Ufo7zssmvBoP6gz2NMcwkmJkRktBRUhdhMsJNV4+VxNaQCUw74Q+8diH1Ddn/7Tpb+fFc/tXnLP82XfmPb7mU8iejfK1gi3Jg72/lyaby7NaHf8kS3mDdtnTDPWT2V7ICX2SFw/IX3KwO6appXWAht8Pi19TT5sB0+T1ojoGZtkLSQONZuGbQJGwpSWU5Zxohv2DC1zB5Pb7ccpoK3UcHLUTaFrg=
*/