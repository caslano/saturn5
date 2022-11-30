//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_COLUMNS_DEC_03_2009_0736AM)
#define BOOST_SPIRIT_KARMA_COLUMNS_DEC_03_2009_0736AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/detail/default_width.hpp>
#include <boost/spirit/home/karma/auxiliary/eol.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/integer_traits.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::columns>   // enables columns[]
      : mpl::true_ {};

    // enables columns(c)[g], where c provides the number of require columns
    template <typename T>
    struct use_directive<karma::domain
          , terminal_ex<tag::columns, fusion::vector1<T> > > 
      : mpl::true_ {};

    // enables *lazy* columns(c)[g]
    template <>
    struct use_lazy_directive<karma::domain, tag::columns, 1> 
      : mpl::true_ {};

    // enables columns(c, d)[g], where c provides the number of require columns
    // and d is the custom column-delimiter (default is karma::endl)
    template <typename T1, typename T2>
    struct use_directive<karma::domain
          , terminal_ex<tag::columns, fusion::vector2<T1, T2> > > 
      : boost::spirit::traits::matches<karma::domain, T2> {};

    // enables *lazy* columns(c, d)[g]
    template <>
    struct use_lazy_directive<karma::domain, tag::columns, 2> 
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::columns;
#endif
    using spirit::columns_type;

    namespace detail
    {
        template <typename Delimiter, typename ColumnDelimiter>
        struct columns_delimiter 
        {
            columns_delimiter(Delimiter const& delim
                  , ColumnDelimiter const& cdelim, unsigned int const numcols)
              : delimiter(delim), column_delimiter(cdelim)
              , numcolumns(numcols), count(0) {}

            template <typename OutputIterator, typename Context
              , typename Delimiter_, typename Attribute>
            bool generate(OutputIterator& sink, Context&, Delimiter_ const&
              , Attribute const&) const
            {
                // first invoke the embedded delimiter
                if (!karma::delimit_out(sink, delimiter))
                    return false;

                // now we count the number of invocations and emit the column 
                // delimiter if needed
                if ((++count % numcolumns) == 0)
                    return karma::delimit_out(sink, column_delimiter);
                return true;
            }

            // generate a final column delimiter if the last invocation didn't 
            // emit one
            template <typename OutputIterator>
            bool delimit_out(OutputIterator& sink) const
            {
                if (count % numcolumns)
                    return karma::delimit_out(sink, column_delimiter);
                return true;
            }

            Delimiter const& delimiter;
            ColumnDelimiter const& column_delimiter;
            unsigned int const numcolumns;
            mutable unsigned int count;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(columns_delimiter& operator= (columns_delimiter const&))
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    //  The columns_generator is used for columns(c, d)[...] directives.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename NumColumns, typename ColumnsDelimiter>
    struct columns_generator 
      : unary_generator<columns_generator<Subject, NumColumns, ColumnsDelimiter> >
    {
        typedef Subject subject_type;
        typedef ColumnsDelimiter delimiter_type;

        typedef mpl::int_<
            subject_type::properties::value | delimiter_type::properties::value 
        > properties;

        template <typename Context, typename Iterator>
        struct attribute
          : traits::attribute_of<subject_type, Context, Iterator>
        {};

        columns_generator(Subject const& subject, NumColumns const& cols
              , ColumnsDelimiter const& cdelimiter)
          : subject(subject), numcolumns(cols), column_delimiter(cdelimiter) 
        {
            // having zero number of columns doesn't make any sense
            BOOST_ASSERT(numcolumns > 0);
        }

        template <typename OutputIterator, typename Context
          , typename Delimiter, typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& delimiter, Attribute const& attr) const
        {
            //  The columns generator dispatches to the embedded generator 
            //  while supplying a new delimiter to use, wrapping the outer 
            //  delimiter.
            typedef detail::columns_delimiter<
                Delimiter, ColumnsDelimiter
            > columns_delimiter_type;

            columns_delimiter_type d(delimiter, column_delimiter, numcolumns);
            return subject.generate(sink, ctx, d, attr) && d.delimit_out(sink);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("columns", subject.what(context));
        }

        Subject subject;
        NumColumns numcolumns;
        ColumnsDelimiter column_delimiter;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////

    // creates columns[] directive
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::columns, Subject, Modifiers>
    {
        typedef typename
            result_of::compile<karma::domain, eol_type, Modifiers>::type
        columns_delimiter_type;
        typedef columns_generator<
            Subject, detail::default_columns, columns_delimiter_type> 
        result_type;

        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
#if defined(BOOST_SPIRIT_NO_PREDEFINED_TERMINALS)
            eol_type const eol = eol_type();
#endif
            return result_type(subject, detail::default_columns()
              , compile<karma::domain>(eol));
        }
    };

    // creates columns(c)[] directive generator (c is the number of columns)
    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::columns, fusion::vector1<T> >
      , Subject, Modifiers
      , typename enable_if_c<integer_traits<T>::is_integral>::type>
    {
        typedef typename
            result_of::compile<karma::domain, eol_type, Modifiers>::type
        columns_delimiter_type;
        typedef columns_generator<
            Subject, T, columns_delimiter_type
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
#if defined(BOOST_SPIRIT_NO_PREDEFINED_TERMINALS)
            eol_type const eol = eol_type();
#endif
            return result_type(subject, fusion::at_c<0>(term.args)
              , compile<karma::domain>(eol));
        }
    };

    // creates columns(d)[] directive generator (d is the column delimiter)
    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::columns, fusion::vector1<T> >
      , Subject, Modifiers
      , typename enable_if<
            mpl::and_<
                spirit::traits::matches<karma::domain, T>,
                mpl::not_<mpl::bool_<integer_traits<T>::is_integral> >
            >
        >::type>
    {
        typedef typename
            result_of::compile<karma::domain, T, Modifiers>::type
        columns_delimiter_type;
        typedef columns_generator<
            Subject, detail::default_columns, columns_delimiter_type
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, detail::default_columns()
              , compile<karma::domain>(fusion::at_c<0>(term.args)));
        }
    };

    // creates columns(c, d)[] directive generator (c is the number of columns
    // and d is the column delimiter)
    template <typename T1, typename T2, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::columns, fusion::vector2<T1, T2> >
      , Subject, Modifiers>
    {
        typedef typename
            result_of::compile<karma::domain, T2, Modifiers>::type
        columns_delimiter_type;
        typedef columns_generator<
            Subject, T1, columns_delimiter_type
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type (subject, fusion::at_c<0>(term.args)
              , compile<karma::domain>(fusion::at_c<1>(term.args)));
        }
    };

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename T1, typename T2>
    struct has_semantic_action<karma::columns_generator<Subject, T1, T2> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename T1, typename T2, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
            karma::columns_generator<Subject, T1, T2>, Attribute
          , Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {};
}}}

#endif

/* columns.hpp
1FBNJT/pmAGNVYawOeMUypi6S4aiCdB6W67rpkHs4KKiqOWnykmaNyXL6/AH5hG6cWUROjhoxHviCLHiWWpk+NHSsGLfvJkFoAHL5gAsujfX8lmd5LYgDmU9IxdsRH8K1DHr8wTDZQR/+AptEloUbR+0yFLD+WnhEPpT4JMaWPkJTBLX0yqRRq5KG1QflF73eF8VsS3na/kpmjczy5ueRfhkritrrt1aVzDbR1wJd4OYkSxiswqol6l5Mtxjq7g9s0OHuXMZ+1Q0arpAVqPlZ2Tlp1EBnIpxkUj/sDeNxm+J9MjcLEZQ8UAi/G8wq1AnVvd2IrBYW8yE1hgfAl8ewrCSFt6JbiGplg/rMEzyBD2LnQkH5lEHsrus+SkFxBoYbaLtJJ23k+joD3+3Q+dR52k7e8R3Y4ikI0uLqjSLiVbTv2wrgkNcRY/ixSbaIDJwlPUkZuXiJiB0PiC6AuZkJ5hyRLXOijOW/+FMaeM+ZbjLzWEdlKSqq+/ZbQlN6l063GUvHxv4mU+ssZ6WZ2I9maBQVxpnTvK8qdZbsZZbWtHyLJVf9p6u1dW0uK78wLn9Pa2+5j92dcHKZQf1Kz9xbv+w5nP7gPcox5X1zu176CFwzYC6AvFjrj7Mx2/P0xcM38jy0ClB3ANsLYO0LlgJbQ54aS6ebrnVIkOorpHOwLnbnlE4bOuVR3HcLFmtnmAO3ipxx8U0co98RntaV9KhmuGuhKLddfRHuSg0kB+Fb007m9kNTG7Xi5c/AQa3JsEyXxuIbNnV7smdymAfPOKeebODM85xtOsb8TIa1ibtrLA2cHnkbdVO+tSFwb5RkbH4jcGu9Qp4AnyMg07fwNqLAMpijCr7EBQzMC6w/jqs++ctL+PsijOQGLjTCNsLZ4EbfVuGc+BkdQUmlE9/36ySZlZVM59Ice2tsq/BbyZ+Q5Myt8BSw5pdvXdjG22nhFa6xDL4qoRnw98fw6KV/i1HR1XAzwvPsmsJC/XFi40en/V+KOFsaSSQRFuqXfx2Z4fOeJJQyPIaOEtsOZPRIb1hhnaPdgGHXFvoDyRJRH2bdFwzZnmtoKwzlDair/l8LLw6g/KKPVT24vUotui2+AZk/kADbOICswFSsX30LwgcZpWAuF6xzILNv1RqKNcmT10jjR9rE3DXMvVJYw8g2ow1W49GrJoPxsX0FauWY5vt0x+w6anpG/tYIn1/XhneziiRwSWi8e9sIWEpChZwNJFReUoZlbJ6XdqTW2kEPvj2g25EIErJenIbPYb+44rkfN97R2iPK3IZ0NRyJIeEi0h27J4uKmud69D+guIfnPng26yPQjX2YBpbRAwJDIYqyGxfcdVThJWW/5WHymgYT1AzpJZ8vHkpULy2Yl8ieLFM048YBxDc/hoSU9OoW31JCjb0oFFw+FUuqCUXWwjkdF8m7CuqKSWYLRSirfKCg/OU0bVJDnqbBDT684hDPp3HSHW+VqMOtNPjSzb6EY1NgNHw7jqqwR/Ot0uXKuASr9MmweU+dHMh54CbFTFuJCHbyUves5ipx5A6klK1IlvoP7aNqFObhOq19U1A6KvBTQdn3hz03hwcc3NwyM1KUdZe6Rt+RSMVjkwwHrN6ZIK6uwnJY43k0Mt4tBiZL8jaG6kNvYx7i1ZrOplfgSz6eBe+ugLMoE/sub8H3DIWiXhsBMKWc57tjfwrB7lpg7Ejm9Qpm3RIZEK8BYHbEJaE8MRgWYBwPstQBOAt7lodo2cGPHYWxWoArjo5CGsGaXFnWGTFBB5Ulzy7Ev/09+ghJqj08Op11BfxAaXA6X233fn4zxOgppFZuXTCIFf2iQhdUyIDAomR5IA1khiw3cYG2jNfnKBNfTFTzbcjopbzmRpwBjXqCgAJNSVLzDoNMDk/T8nQbL/bMAmuFHvpbhXf2SP96b5EpkIZ1U3ASpWw/8QV1ZiL1exaQrZ32BMwm+Db4bN7dP1hl/H0B1+nzlZCwat9kKzI3qgrAFuiaXWP2b3PC4xS/PQAldLMliaFDkIFfhEEtMNDj6XpymAx5lMDpz5VD4GJVZuWFjqt00xBfu8rND5+50yqf5adiPxJ2vyMyhOIRggVM/gbliACBajbwaM9NseipAnPt3TbnRgcxMF+H3YVyl2AMCMQfni6xX7dIJeDrsF0pdJ19vP5dAUyqmpAQSw9nmCRemF2X623ef/+/XCQdvjwYYtUIsju0oNvNRMJwk6vNqZ3GOeBcDIudl9Ij2VpFq1BOxIcAdEN4aj9rIkm6lOhP2MnDEgpkQsJG9BfjK33mE+8yS9liosqutQFyd8Rcf+FUZKn1tvKHpmu/bZdzw2dSXSuQvQ0sZ7auycFHO03aP6OjwyONjTLhlGsTd7yJEF5PwwR2imH+Lvl5hQyffEVPYZexsKy1K7AsgPhFVoNDErwvI3/vFyF16GXd8lcmGUm+vaL9ONSw8U7l75/nfl9+WHzbGVXN/HkvKKlNjY+IO7raY9vxYU/MaGRvU056FEy4Xa5E4m//prIlj9/hK/Zqz5/gGo48Hd8LZxrzz7h2SvdPrrnZUg3W7wbG66lf4nZ5ASga/d6dAJBfM5G25FCSZYvAFleSP9w0hCjtNvT2LELV1Qcw/uUwqWNidJQWDyBGLHsaVSc/rtUt3JULccQpfxdDpEQL93TwRYGx55kjq0K5BosCmaVqrkl6mpsx3J3Zm2jrz5hbJ/fWsCnIAaq35hOmJM9x2iQf6euY7p+VonwUmM3ZsRetkZfsvGsuJTe0+wt/LucvdfRtEeOGbMn87yLBhlHTqpb7IK4f1YJk+Nu8edTUXX5i1WamNS/s4wExMUvENp4NXYlvTZ5wtMpruyj6nPY+NTn6un3bY4mw5uS+lwDfnkrql2BXVYC1UI0qQlN+veHUYBCTXLXendln4aNQsO4PqNtQ2Jt+ymCM6JfJmEaFyyYTeZWALClbxiiOj17leFyS1actPzxAfd6SHBoF1jQ7NkbHCQhViYqyRJg1fwm9wJH8A4qvVDj3U7jPUsj7mf6HOthVakvBvZlTVHiOQBgCzrVBd3SeUBh4eZCNb9By4eHPNV7CP4qjxmOUaEnulksWNKjt+zFzq40m652631ixCwOUVCsW/gNILYwfrf0i5Z7OAfnHntdjy775qx4GAg78RtGnM6KnyVYGIXJtRDfQD21eQOM5zHq7vVVss8rMNTAd4eHEQwttYW+sqneZmdFLTVjlrOiEn+Cs2Y5K/tRvSFvWz/2htSI0AtHfKIWh4Xe7jwfP4vrB0QfO+kxa4BcY/wwcgB0Floguw3d303VdIe9+4xqlrk4I/yJt4pv+kcfOoXgh+7ITkoJeVv74dxLBjSayZ/upPQ8PL7b33js5setshxlj4xH0fs7qWhn2LsNLwfHf26FzCkfHjGLocX30UNhnF+IzVqZEBt6YLDUTK9/BzxvKqRmvJZgMRyIX1xEoH663lx9s2y1yUsI2kUdPM5cOXGQq7jJQ3tUUjHYAXl8mK37oBa175sEwuopTgOJjirt0dXdmS4sJ3AKjM6Yv1B3j+HfsS7G2nd/YC4J2pTCvt7Qt7aHnT+r5vor7K2dMqC3ISwtR/NuN5sn22aidncHUDu+FYfan+zAioy2Kue2HtmNPj3wMZ6/piPBIvG8TQThxOdQPTDSxKpX8FEfPup10PJUESPHxY4Fyw6p3kb3+DmE3JSBYmI7POo1IJZYv1pvA5Ysztgn9odYpNdzJho3ihDgfVLqUSUKaTrdSoOyuIhZ+Yftfd3GZW6EcOZYrbceKFCSp9LfmESh+fXiX0Mw7cdk8aiXr3r0ySgmtPZ2CKZoFIK3uOEyrsn5TPWZusyaM3XRbzm3V/sMeIHOIlEVCZtNB47KobCSAlMGDSO5Wfjvo8Vcdii7K/JLXakLhzDogM0F7RCAYXqDM93jwc0qU91vuvDdie43mwfR33FM+aPd16VgTUkHIrEqcjm+T73Z8g9OtuuRVGTTlcZYrox26A/LTzmfrQ5V94OnqiuX78V0hqq/w7S8CSweHKArDZrVD2ODscv3Ys71/EblC1MBYq6TdoxThxPYc9ntVf/GVN91WKohu0fwxA4SP22T6KnysoT/QXITHyRN9dbL0AmHfOqCfeqCOjX/kLpgl+h/8lsdBMI/sKlV8Q7foJYdo3k8BtXmCwYjNEf+WnF8EEc3Ypjt7Yf5XSfVig24eU1cOAipDbqyVSiDYQSvLw1Suq7Uq95qmjCaF13ZJ9ZcRjPCnkQCiXLOb7RVr/R+CkqwkHAYIbutaCXKZ9ytLmjc7/2MgGsiIhV5q2kbMTRpbcgoBgyONetCbuJaqBqXDTKJw2PUGTGirV0XL72PxVNcNdRPIzoUgQ6kNOxCJwerIKSBQSzr7RNp7pxx9PupW9lHfQX+2Si851LqTXlp8CZR/5UktSdUAZzcu9FDIi5yS2Bu0QSBlbhleBdxbKBdTI+vQIPhslXihU7jWIVyfUZtF12H4nSjvzuYYCkGkSBufuBc3eh02qrEG/H530f+cRCGXPA9+bcQwSt+dcjEcaBK5n8TO5u4+IHvObzo6oplsMRlIAD1YTj30ReBfwzMc5HY8185GqkxGaaUXLZcZELs97kBPgdi6yTEKq/BgShBrFIn5n1FELvfWfERqAulodZ7DGDLAKv0ip8NgjdiAtjLHICGbQwZM5LOBdhtIjDAANgqsY9KaTOCUWyjevdtDocwhb7wlBL4bNrm2yx+RSMHeXCjL7urCLHbqCiaJ0W03kZayVFI3efZH7RqS2xFqP6uQbG2KAMYShnBfzQgCqZGN8SD/yVQ7X6PZkdGvnwaw3vXe5CoFxqRaAIOdrjM4XK6fBxSrFdM/AoWCdvcCkLleLfIuDg/OM4qB7Os5XiVfdB4oonGwxyj68KB8PSbZ1SlcaX6EjNiXNyA9RktGU1nswDjLCuSJhDm10S4tR2h0HgMjn8lCVKjc5/TkIjuA/HQ6YiDztDPz5ZDIPIoiK9gisp/NRUrJVRjE4u+k/r80aMu2KcuZxw8ROYiRtqOnOM5Z9xp3qju2CddZ38y1Do6jlDOPqp9HJ5hK/Krc1sRcXlupzq3m0hWz3vOij+ARi7IkL6piPvVg2Pdc9MUl/tp3pFGqfw3Miy7K9etpClDZboyQOVtRCAcHdOeD2Uay0NpzSJaqqwtq6zbqtitZQ6r4rKWpWBxN0ZDHbJx2EOZH5z5QJfCHbfSqCS5y5qCF2j5DbRzEQ/vL5ICva0vc6gYEDRR4uul34P4MgJAQHiEOJPEKg7T8h3uleYe5oL6/0YO7hpzhgBx3goAggxhNNw4N4L5o1ScPyxG9+hS2tqVZN/DAnbbHilg50fxdYkUsL/21Um9+AkI2D97hQXsyCYF7Kk+n684w46D63VSyP5150l9IzKYEl/p0o8YZPdupsz7ia00pRFfoV/lBHEzAVtoNyh+ODUf2sLoSrn6bHlKpR50aSvA0MTJWBJYbv1Nq67fJp1OBOZU7cU6fWc/SDIZQtS7wf0miEtnZQcERMprtd4tIACL6B8t2CjvvEVsP69Dr/VusmFf4MMjrV+hrmxi9+yEbh6HbMCHOEk04I4vaKfwbpLC71DZJnv50Y0zael69hNVkC90PS9PubHqy5uAc32SOFLfnOqEK+k8p2QhxfVECMtXwnMjzQavfSOhblKnrk1ixsaLgDav9fGKe3wjBK6nGrClVUdtAwn46gnhWb2HAglw003EaJ3VW/1BDx7mHkK4zAa2C9+HsBdzG7W5dQEbaCyVUPbcJjW/WU/dyoOhsQT/ZTsfu0nSyuh3yuedOtxK63IniLqSPq49aiP0q2zAy7jDkBe/gxNLOy1M3T+PUPGiomIOpES5tSPqbSXiR78nKlfuVleJlC/lbjUqRhJnZOvT/EVybN72wWpSrPwHUX4I3JfcAxeL09SdYBjUnZhlicW3GHMsXvuSsPg1f5MmAmueNv3EErle5GflBCUFcRXt2g1wjOJNU3NLNW96rP3ywEF83IteWPhEhzW6BqGoi09zcPwovjkAwQcCj4XzHVHBB6ItLIiFu+kTgsRRWAS3fwSkJ2HBZ/MbNOVA4fw3MQsLhMEscOADQxoPC7nMvoJotz8miO5K7pBo6gdYZGntrq6A0Az+A71t6gpIzuRaI4rOWFfaLFuoJxGuSaxBdpiTfWBygb4dazRcbmcuEfG5Wn3idUI7hTyhkAT+dANN5QKhXMQeleTsQZAfP3eHTrTrhQE7Za9dAREXL4QrN8SxnH/6nWQ5q7oxXVWlz9Av7Q8D+RikX8AiOii3nMa7jc2EsR0WbHAYy1eXGjJwvmljYXjstAMBWtgFB3WzCt5XPXUP3r28ZxDdPYxwmrCTXEVIybkj16F6u+nPIEwYx6ORR0QZsN7rLvCxtstUwuvOHd5e5478bvi+q/FB05Jzwz+ZaQ4B3G5HuNlHc+APRIaLgVh+VlAACCz30/y69SSr0hqx/A4vbIFve8R9px3wkjlwIbaORkEseAhKpVTg/BYuAPYaYaLUErta4pClValEwT40FtWyUi57U2RPoZAlzQpyNBOucDl9GJ+zLY3pUIi/67Et93d3x0UNhIij6jTQ68IaSQYRkXy3NUq0P/T9RHs4zNHBrY2duji8n5fJYWJlODXqYN/NfreVdE1ZE+e+uslXJCmcFnTKzR65laulj262/kw+96Sb0o3DbvH6PwlPzEVoXuOA+Zbmb3WNXeaDDiJULV1Zy/qUJunyW+aNebO+Vf/WSGMy6RKqI5tqgXP6s4JWhN6B329d9a5U7HjW2iLJGjsQl43Eb/4qn6jvD7swdMlTqzgCgzGO/6ZxjDh9YiT9ZR5lmA1OEFbCCm4l8bGwhBYf/RyRFfG2/6l2nZmm5yFXfChYPK+GN/WVg6Xie54WYt3mulMfF9A2EWdgGAJC0/Jbs6aUZuU3e+rKBhFOsHqb+agrgTDStVpuZ8AFSz9fUeRi7beox3/qRGFcHcnnGJ7qvmLZO7EwqgGxSvwugWjIbe+CI7qvaoibpiTzXZhypsGSc1PlCWfFY9g9H4VGKywIWTXl0RK/qToTHKpdG54RLBKqU7r58YFJVzYZqh7Ub+pyb/NJMBorxTtQYOdhZedS1XJoVwotUQ7t3gQe2pViZyKGdh1Oj9bR0HKs9Ufvp8JlKVllDmMo1bJN4nqXHM2ZG9MfHu4K3VVPNR+zEIlH+Jg9ks6tr/U2QJ2VBoTHgoZgJQxwu+X4W6uthGbrqS6rt0FrI1okcmERWwhSMwqraDFoPE2W8Lg8VdlArBFeXJiIF3wK8t5v2A4zh2gj6Np8pM61R84jUjtsu0b1uqDR9ybmM+uh0rDNrXpTsmo8+8uc2oxSOc9qPqGwFBnaMburYLYRzPEsPuT7AjtirqOhAZpioQE0fFVoc5u07ixQdlntnjPs/jvNU1PeX6vJyt+g5tsjA91z7WUDNO8G6x5qMje1lYZXm9tMIxwtdTJyvqakeE5SwZNZxD7lOyID3HMdZedZlU3qXIeqpGQpjiyvvdiVCE8aOKw6GFXMKf8tUSc27aD4529YWmRh1pbR/kMG2hdfae06R41EIHgOG0kUzh/MY5CV4tPviDwY+g4fT0lVLqkI3yODjG10gNTt
*/