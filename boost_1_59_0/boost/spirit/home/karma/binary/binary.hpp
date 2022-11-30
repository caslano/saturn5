//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_BINARY_MAY_04_2007_0904AM)
#define BOOST_SPIRIT_KARMA_BINARY_MAY_04_2007_0904AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/detail/endian.hpp>

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/config.hpp>

///////////////////////////////////////////////////////////////////////////////
#define BOOST_SPIRIT_ENABLE_BINARY(name)                                      \
    template <>                                                               \
    struct use_terminal<karma::domain, tag::name>                             \
      : mpl::true_ {};                                                        \
                                                                              \
    template <typename A0>                                                    \
    struct use_terminal<karma::domain                                         \
        , terminal_ex<tag::name, fusion::vector1<A0> > >                      \
      : mpl::or_<is_integral<A0>, is_enum<A0> > {};                           \
                                                                              \
    template <>                                                               \
    struct use_lazy_terminal<karma::domain, tag::name, 1> : mpl::true_ {};    \
                                                                              \
/***/

#define BOOST_SPIRIT_ENABLE_BINARY_IEEE754(name)                              \
    template<>                                                                \
    struct use_terminal<karma::domain, tag::name>: mpl::true_ {};             \
                                                                              \
    template<typename A0>                                                     \
    struct use_terminal<karma::domain, terminal_ex<tag::name,                 \
        fusion::vector1<A0> > >: is_floating_point<A0> {};                    \
                                                                              \
    template<>                                                                \
    struct use_lazy_terminal<karma::domain, tag::name, 1> : mpl::true_ {};    \
                                                                              \
/***/

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    BOOST_SPIRIT_ENABLE_BINARY(byte_)                   // enables byte_
    BOOST_SPIRIT_ENABLE_BINARY(word)                    // enables word
    BOOST_SPIRIT_ENABLE_BINARY(big_word)                // enables big_word
    BOOST_SPIRIT_ENABLE_BINARY(little_word)             // enables little_word
    BOOST_SPIRIT_ENABLE_BINARY(dword)                   // enables dword
    BOOST_SPIRIT_ENABLE_BINARY(big_dword)               // enables big_dword
    BOOST_SPIRIT_ENABLE_BINARY(little_dword)            // enables little_dword
#ifdef BOOST_HAS_LONG_LONG
    BOOST_SPIRIT_ENABLE_BINARY(qword)                   // enables qword
    BOOST_SPIRIT_ENABLE_BINARY(big_qword)               // enables big_qword
    BOOST_SPIRIT_ENABLE_BINARY(little_qword)            // enables little_qword
#endif
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(bin_float)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(big_bin_float)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(little_bin_float)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(bin_double)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(big_bin_double)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(little_bin_double)
}}

#undef BOOST_SPIRIT_ENABLE_BINARY
#undef BOOST_SPIRIT_ENABLE_BINARY_IEEE754

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using boost::spirit::byte_;
    using boost::spirit::word;
    using boost::spirit::big_word;
    using boost::spirit::little_word;
    using boost::spirit::dword;
    using boost::spirit::big_dword;
    using boost::spirit::little_dword;
#ifdef BOOST_HAS_LONG_LONG
    using boost::spirit::qword;
    using boost::spirit::big_qword;
    using boost::spirit::little_qword;
#endif
    using boost::spirit::bin_float;
    using boost::spirit::big_bin_float;
    using boost::spirit::little_bin_float;
    using boost::spirit::bin_double;
    using boost::spirit::big_bin_double;
    using boost::spirit::little_bin_double;
#endif

    using boost::spirit::byte_type;
    using boost::spirit::word_type;
    using boost::spirit::big_word_type;
    using boost::spirit::little_word_type;
    using boost::spirit::dword_type;
    using boost::spirit::big_dword_type;
    using boost::spirit::little_dword_type;
#ifdef BOOST_HAS_LONG_LONG
    using boost::spirit::qword_type;
    using boost::spirit::big_qword_type;
    using boost::spirit::little_qword_type;
#endif
    using boost::spirit::bin_float_type;
    using boost::spirit::big_bin_float_type;
    using boost::spirit::little_bin_float_type;
    using boost::spirit::bin_double_type;
    using boost::spirit::big_bin_double_type;
    using boost::spirit::little_bin_double_type;

    namespace detail
    {
        template <int bits>
        struct integer
        {
#ifdef BOOST_HAS_LONG_LONG
            BOOST_SPIRIT_ASSERT_MSG(
                bits == 8 || bits == 16 || bits == 32 || bits == 64,
                not_supported_binary_size, ());
#else
            BOOST_SPIRIT_ASSERT_MSG(
                bits == 8 || bits == 16 || bits == 32,
                not_supported_binary_size, ());
#endif
        };

        template <>
        struct integer<8>
        {
            typedef uint_least8_t type;
        };

        template <>
        struct integer<16>
        {
            typedef uint_least16_t type;
        };

        template <>
        struct integer<32>
        {
            typedef uint_least32_t type;
        };

#ifdef BOOST_HAS_LONG_LONG
        template <>
        struct integer<64>
        {
            typedef uint_least64_t type;
        };
#endif

        template <int bits>
        struct floating_point
        {
            BOOST_SPIRIT_ASSERT_MSG(
                bits == 32 || bits == 64,
                not_supported_binary_size, ());
        };

        template <>
        struct floating_point<32>
        {
            typedef float type;
        };

        template <>
        struct floating_point<64>
        {
            typedef double type;
        };

        ///////////////////////////////////////////////////////////////////////
        template <BOOST_SCOPED_ENUM(boost::endian::order) bits>
        struct what;

        template <>
        struct what<boost::endian::order::little>
        {
            static info is()
            {
                return info("little-endian binary");
            }
        };

        template <>
        struct what<boost::endian::order::big>
        {
            static info is()
            {
                return info("big-endian binary");
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
    struct any_binary_generator
      : primitive_generator<any_binary_generator<T, endian, bits> >
    {
        template <typename Context, typename Unused = unused_type>
        struct attribute: T {};

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        static bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const& attr)
        {
            if (!traits::has_optional_value(attr))
                return false;

            boost::endian::endian_arithmetic<endian, typename T::type, bits> p;

#if defined(BOOST_MSVC)
// warning C4244: 'argument' : conversion from 'const int' to 'foo', possible loss of data
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
            typedef typename T::type attribute_type;
            p = traits::extract_from<attribute_type>(attr, context);
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

            unsigned char const* bytes = p.data();

            for (unsigned int i = 0; i < sizeof(p); ++i)
            {
                if (!detail::generate_to(sink, *bytes++))
                    return false;
            }
            return karma::delimit_out(sink, d);     // always do post-delimiting
        }

        // this any_byte_director has no parameter attached, it needs to have
        // been initialized from a direct literal
        template <
            typename OutputIterator, typename Context, typename Delimiter>
        static bool generate(OutputIterator&, Context&, Delimiter const&
          , unused_type)
        {
            // It is not possible (doesn't make sense) to use binary generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator,
                binary_generator_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return karma::detail::what<endian>::is();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
    struct literal_binary_generator
      : primitive_generator<literal_binary_generator<T, endian, bits> >
    {
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef unused_type type;
        };

        template <typename V>
        literal_binary_generator(V const& v)
        {
#if defined(BOOST_MSVC)
// warning C4244: 'argument' : conversion from 'const int' to 'foo', possible loss of data
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
            data_ = v;
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif
        }

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const&) const
        {
            unsigned char const* bytes = data_.data();

            for (unsigned int i = 0; i < sizeof(data_type); ++i)
            {
                if (!detail::generate_to(sink, *bytes++))
                    return false;
            }
            return karma::delimit_out(sink, d);  // always do post-delimiting
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return karma::detail::what<endian>::is();
        }

        typedef boost::endian::endian_arithmetic<endian, typename T::type,
            bits> data_type;

        data_type data_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, BOOST_SCOPED_ENUM(boost::endian::order) endian
          , int bits>
        struct basic_binary
        {
            typedef any_binary_generator<T, endian, bits> result_type;

            result_type operator()(unused_type, unused_type) const
            {
                return result_type();
            }
        };

        template <typename Modifiers, typename T
          , BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
        struct basic_binary_literal
        {
            typedef literal_binary_generator<T, endian, bits> result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                return result_type(fusion::at_c<0>(term.args));
            }
        };
    }

#define BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(name, endiantype, bits)            \
    template <typename Modifiers>                                             \
    struct make_primitive<tag::name, Modifiers>                               \
      : detail::basic_binary<detail::integer<bits>,                           \
        boost::endian::order::endiantype, bits> {};                           \
                                                                              \
    template <typename Modifiers, typename A0>                                \
    struct make_primitive<terminal_ex<tag::name, fusion::vector1<A0> >        \
          , Modifiers>                                                        \
      : detail::basic_binary_literal<Modifiers, detail::integer<bits>         \
        , boost::endian::order::endiantype, bits> {};                         \
                                                                              \
    /***/

    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(byte_, native, 8)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(word, native, 16)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(big_word, big, 16)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(little_word, little, 16)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(dword, native, 32)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(big_dword, big, 32)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(little_dword, little, 32)
#ifdef BOOST_HAS_LONG_LONG
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(qword, native, 64)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(big_qword, big, 64)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(little_qword, little, 64)
#endif

#undef BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE

#define BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(name, endiantype, bits)    \
    template <typename Modifiers>                                             \
    struct make_primitive<tag::name, Modifiers>                               \
      : detail::basic_binary<detail::floating_point<bits>,                    \
        boost::endian::order::endiantype, bits> {};                           \
                                                                              \
    template <typename Modifiers, typename A0>                                \
    struct make_primitive<terminal_ex<tag::name, fusion::vector1<A0> >        \
          , Modifiers>                                                        \
      : detail::basic_binary_literal<Modifiers, detail::floating_point<bits>  \
        , boost::endian::order::endiantype, bits> {};                         \
                                                                              \
    /***/

    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(bin_float, native, 32)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(big_bin_float, big, 32)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(little_bin_float, little, 32)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(bin_double, native, 64)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(big_bin_double, big, 64)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(little_bin_double, little, 64)

#undef BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE

}}}

#endif

/* binary.hpp
TF9Ww0mycpEsAgRnMw21L1ZjJ/ibn8gqK1O7MyTfWfEZCLg0Y3diz9gpeNPKV+Ip8C3u03aw0t74cG5nzPVhSeeHgc73O1Qg7rv1SFaGdrkeGZOhjaD3qirltu7p0GeEXbKz8XlstvUZ9ajP36TPZdGZEyoGGU88Iv2vwNeN/09VpdF8Z4gNCmZOkG4sDfAHYlgZ8ad9RFyCaLfU1A4SdCtGQFEkvfk9rLqZE2zXz//sjq/in1E6fTVzdsZrACMGuxFu5jjMPB27GzBDu1lN4czRVJh+2bzZ8KP9eDOiPauzjeqxRvU4o3q8fGe5qlU+03PapHZCevTlD8D/xDmcO9rMZP5nHD02MwjkWFS7j3LNbfzbyr8gF5rrAGCgRGTsPslvu/i3k38BaJL4rw+++1kyd3aIHpvrwLuxhGs32Dxjdzb/juFf8He5B4pyG0NluW9Dw72MTRM98laoW+yX3UeS7AaG0UP5eMoh54UvthuAu2a5/0iy3cD4U4C+Hv1l9gahrEma08LvjLAdkzRMfEcp8pVVpPyeqKKlVNz34aXA+P4i+v1yhWt+bneB8QZBRcd84xVWJnoFAaWM5TX8+yj/lvPvGv5dy79V/LuMf8F2G9/fiRYsB1NkawQ6maOKvsIaf3cDAN9AHNHD0BS8O+n42OJaBvzKoZT0+rFCSjXOOsK/0leHVoVH+goWaZYt5LN4kwjB6LFED6vR2NoD4Sv5DDb+aLse11/GC4dYvbZ/MusxkQwvqEMNITWOqmmw5vn0SdpFM8PQiOWhontj+Up1A1oCiz9aB5E6MMJ7T/ckxSvW75r4i1EZjjJxRpsgHgjLP/ySCcKxiGPcvGKZwwrwC/aNBZ+FtPz0n+O9Y9581olG3K8KOA5ASGVYoIfkPd/uMeOqmFSaS+RlVzhC5d/onyyLkvVjxJ7xuBw2I3bN4xdGZxVXZv5mVAaL35Ubk3uVxz7lj+rgt+Cd4WgxYcBv7Oq2XKaFryLeNkfC+j48Qn/zFJj08KDmVBSEfs1XnPqeT92OeQYX358z/FOXO96gNY9dxBmGLjy/UV7M0o3AVt+8R8MeUYfVGksTrJIphgCsnpAKrBqBnf6DYfeJxljKiabW9wFYp2hX4tWHJ+Af/P3gTstn+Fv7Uh2UOkYfPmzlQIVPesyRO2EeHWkUzddT0cueSi3UW87nhZ3TxMzxVMj1BCG300ScMCHf0BvTOBwkZHApERfHuMc2E/wbnTzN2IDN4ptXrn2NGq49QoyiMxrczrpZi0RgO3TBfXMbwqPEauytqLvQWYcc/kjDUpeINAhWpfXvrR59QQLBurr+3qUIMh3c6VqNl4iqu1MEthoeGNZVuhWPsL0+WeEy2au7rVslRoSIvzSfhcdIfckih8hfSMwAUUD5ACMOxehMgt6q/tWFlOJRR3R6lvg0GmlhpcDnjiPRv5WnbPgEKpH1NEfbrDnaxnN0V7850tpoDV0wR9filT1HbdYc3bAX4fXaiWsUXWqiRH52zn7DaaTI1iPgZorBmNEGgkNDoTMMgM4s8V3aAqFJIXhCdB49cFkcFaU+ZPFayjsSoNsbYz1w3+HUXFNigyCOT33jBg86X2GF8WAH5FEBj0H1rIsFP/BwuCgf6NcQOPMXkfaohtFBAMJgX72IyKjGjsSJqs5fiGm5clM/cfK4/qqgEeLh9CXlDiNy0lt7I8/Low5v7ZVObhGtoVZ4caQ1FGyNLs4SafAveYDWUrAtPMcWmgc6XdxtF9HkncqHqhE8lRNoU/qQBExDlpoqm3ULV6Kb9fD6wT0MVYnAKRE5SRXoO9iDqXc1bJH0JQ9Te6K8PPSgNO0lcoWcchijIe7AWOxj2HjELJ2AoMWqNYF2FnBzG9Gw/4fRr49OdxcRP3WSg7ti7InfNhHVStoxT2zOePdPP3d4xQmiipK0sf1CYNnkdiOimO+xbAQB+2s9deJHwAzw1XUTTalvcba3hv2EE6vfTJ87RqTgCHnbcV5ZLK9Hx3bgGQ+5ZnM+m4r6dqB4by3Hjt8W5ikUB5cfXpbhzDPXwI5LjCjFecezHKOR1zBOfH+HlBzIoKzCWf4gYPyibPNdtcjLysr99hu9xRmy3pYH4skOyiKqEdGv/n3OVF0EAcweUfPcFc5QxQTgjHfNbewEixPI6zb1EM+JLliOmXayuxgCUFw+SyAO/VyJFCAZsruvXIx2+xYDOgtr5wve+SP77fxgq//dC3f+GLyyd36rtfPHv5mKiA5qzwdO5TTRWvFtAzUSHq3WtdrazmCX/q1TKTcFeylB7Gqh4yV7mdqpbvqdiCivyfAED/3mIlhrcMdDpbKWuq4eKtzyrz+jB53nf394vG9RdvhGMb3cWAkEaW5DIiHwVX4bWnd8S7m2Uq74yfbkjTj4rRjTcCuMV773ByWZmZuO41kj0Obbjb5w2DIsAWWXeH+FRRO2KmtOT6n8z2lldmc+UchSc0RDNuqYQkuKcCUyym/AVqM9B++AFpXTqA2hQn5sUTqxtQiququHaMTXQBkKLsV8DUC+/DvWurF9csrZf7hIzVc8Y5FYI/WnshFymBUK9XZ3SL72UxqvZyzSagR/HtLz0ehu/a/uUvniTxP+rFQs+KZ6VM/DmAi6DiVylpddmbTMwhkqnYrIDj/5qtmfm3htv8Tz5z0UJ6VVQZTqDs54S3LGsVZriK1VUjejsEq9UgWx2C2JZooXp3wzd2ObzyEA8Q9H/01SA3kTYsZfpehTORcDxbcVZrFc8wOXo+NnDnswEHFc3AW6y3wvJIsejVNe/9rGroz2hkeIluZl6S5FPcoMKiy2QOXl7obkGM7UtpUy/Z4yiVYi1z4IX8MRBELy/Fd71BmDevzXV9lR0YGX7DYRSggZTIDL0y+4ks6Gcz+Yr6qxQ8fEx6QfYRcnwofyEvCA6P9wI0rHtMyjD+n8IW1ux/6NikityGz43ddg/9zECvN3cSySOoZA5nvRun3WTbKlzcz4TE7lmbw7eSZvUY3GdgrRXpHnU6j6NPZ6SjsHn5YBfbEIsF1OdPWYsmRP4mgbQr/b2uoBc4cZlOhd7+utbzooS0XGdX8iqFriyT1wXbP/RPhG/Wx+OFU/+0Utq6io3AkpVKCvn1fbifrZ0vBAfxMNBqUaSKlSKFWslTJTvjn2py/xJwc+7WL1NhboTmxYByHIdBqVaKAdMINd7l4U1M5iRcAVQoDRHEBsIYevMl1zGZHj6iufUGVb93l0n2ndT4BOjxFp81VX4aykjRfV8v3M9YhW4RR+WD6Y2nH2O11q/mAnobxQ7gfF5fkAF09YnSVK33yEMhWEfXPKw/NE5Tj/uXAZcQgD25hDmOH7CTiE8NTSaLBRfstJKIaobaJhECdr+MnzJttZQD5M75jL//s/z9P0tCK84ED6rmarUdZRVrmjkdljrDb0okzNdS4qGm2NBl4QgvxZShJMQx9H8OotA3tjVFepBWxUV84ntjKJKwXrt67FAf2T3QQsedfnNvqmLNQ8PuYDwy6a3r2C7+nPMvVnofqziP+wqdmHB8Cqz3iX9uKZRex5BphW/u6vp2GMcX8XpAPs8eUdTHXP7rhoBFlsyUsGoqRyRpzk3vD307bHjjPv0tcfEpbcW446G5xAM6PfVGjmhFHLseQD2TmBLF78WiaUYlyN9UYtotKL/Er9q5UOo1aFbc90BTLqEcgWIe7roV3hUgQm4fRX8Y76zkHow/eXVpjK6VHCtZOI4pOljgDC0knvAseJcHMR2m4jcofoN2jkICYft8uiLMfkcGO4cRw2HnU3VvD6sCtA0zjBVkUxbhWUghi3horPooGt8WTpHLmeC7+lHNQkZSibFTJLy0GV7ao5rzxIWgTLrrX2s9YYXZJl38WJN10H4P5Uhvcq0l612mIz5LwL34Lm13dAYOIIfzsaRRR7Wf8GAVAuBiXzmUjFeWp/e8V5LHWsc9V26eXiVLai3ANFRXbcwAYeG+TEOc2shSoJn+7v+j1hjt8lFV7xWT0GJO5xTBDU4ALMYKfeOAD0d1rFABDJY0Ha95pae7R263kVsfFL5+AkBOYlmpQ/Ow2RbruLY1HylIYSKd3nEh871Ud6u+g08neqZDgbOxyS75/ld6rMBygB3G79wIFTn/Toq5gPHnjBK5CG/1VMSXwG9KaueiO/Ut72t9OmbNlJAHps3JwA+m3Vleyu+JsJxMA2sfD4LKf8hGBpkZz1IsNEmEDOOXUOISm0mxWCIqLoet9T2eFsefiHPQih4GQvC+ErbMxcJrufccG1OOOSU4wZ8/q75JTtQXgF8NBubR2RYRSE5chv8R6HPEge/hiifqOg0iioUl5W4hIORpNIBM8+nFmGGCLM6/hbd4rDFhTK36c6ytcBXtz2yMWCwh+dQ8zIHcmCwu3nEqftkx9JyFRsCtSxg0FDObus+5S2pWybb1Ob7DWGRmVQqeS4i61EcX5gUZw4PuPw0uniYDL+kd+hIYJ1hf9P4YFgSgEvMCcjFWmL6Mxt4nCxPAMtnr3StSOZoPxUIha13d5V8/u19+to79/ewDEPzWfuB9FnMEPAFu8NYgIml0Xa/FYWt9PgMWXqPxjO8D2YTRW/zl9Kf9BjJnTYfPPnaAWElPw/YEt2f3OglSW6c9uMudKYe9KY2w622nyyULQwEjrToZxKdfnmti+9VqEmhzxwkl2BQhL+4klam1m/V8RDoMu/t2q+P9Ae+TKONd3LzQnlkMzK3F/Cipuot/+EJ/h7wuObC9iChqaiSG/sMr7WKdqIMPvTadM6D3GxExx9wRwiusxAF0c9aK/6SccSGHPllCfpeSoT5U/eISCwAh22EcwUKuz/W+moMoFWFtBiBYuKWQQnVrB4uI5Dcq9ggXFdFd+zALpuId8v4ntmOVawILmOmeAVkFnNN1ielby1tPQyxsJnZMOHia7NdMtvfHTams/taGWjNrC5IOsL1LzYYH3BGAc95KCtfMA3gcVVM8fQgpyfx0LjioyGp7GunnmdCc25HpHv1nszaX015nV81wUbTd8L2Kne2gX0dBeisDHV5Pu+JZEugkS6INvngh/2WUpHcvkSN9wXems/RdWKrJoE7vjPDviSMUeClnwDBOSC2qZwhjmyk6Wq2pwe+Mqv0asrk1kgLZfKZ9e4gU6YlzYXYHAczYGTGfxHQtAqn/3JefNBxeMQCfaeXl3l0B5PIn2o61/Vv9bp0L/WZcl3WqnSYqLbiilDcwHjKWKkEjmU7iNRSmN/jhhNkS7v68Qrzww3/S1jcG+coioudyRTVDSEb4IP8S1xe2tvSenf/WuQcjGEwPWnlCIJn8Ple/Tegd6a/zgh7RnirUnjm9HhRXpvtreOBZC91z6Rq/feEP6S3jvOW3vCyeXqbyjkerlNwtqEL2Bzx50oOk7eems20cuXIH+3ZOTm4nRqC9xAsWfZwf2ShzPtpIMxpOyCNvbHJGo513yN1eYPy9TngC3wUKTLDONrXdi6+W3WaaeL8si7EU5lLvp9zUKAKm/NKNUDu3G1A5xcVspC5r2Ca3vMju9+1q/9tScxy/sXWAe/30MFIOHgsuaw/M7jjHcU8OgSfSHZ9IHVggFowc6zXFiFU259gWoqCIs8COaCyg6RV19PCZoWD5STPFT+Fu06ymMumiTvehtH+g9CtewRC+L9nCBLxyHCCdSOKd9kUHwFpdY34lQEvRr/Te7VkzRQsYNJh4vfpowxa86wN701dVxKsdxzK9H072y3j37Z00fnNmxRue9rlsuOZR/YI9CFEfgWglzPDONpeRNDvAfeJ8gQ6LIBKo3Jr99PHpPNZ6iyYBdacpKAiPzqdsacShiRP5t5F8KBDdYpj324g5M82bnCpbjeMnUsgs0a3YBFUExf/7yI21JsNWT/idN49L2BAQlnTCuTOc/zJBgNeEPcXVI3U7mbOntac4Sr5EAOoBxezEztt+QfHrW6v/z9ft3/+BMQnfLrqPmwPK6eUp/tuWAEfnUiPgIcF1f+DKIqvqW1sXYtpB08Im9/iMFL17Mdcvo2xtENW04gUvIj79MvOJ9y7VrflEe1K33LTwIojvQtdxOE1Ib4pkwET9SOl8wTNex7P36GRiPbthOVpOM0cDXQRe6B5jT3B/A5CUQC23ORN94oGG+sZnSxmhHFakYRfKDBFAGRDHxECYAu8gr3iimFe6P8Rp/kCKcLB1uc/hQQquNr9Ku/gW+O8GUqm4orCTDBbsP2MuumhML93C9YCoj5WSEj0prQm5qOZnf7+DDDu4pjASixpg3ovuC0X+ktpu8VeBOjMXmlF38HC1cZJNWH4mnEsFCxyYURV6KofK0VDIf5LNg9oXNBDeyTTBuiN6AYQi7waGarpK85Skk6oH8s332N+RA+QAwDALPkVSeiaWBz4PgAYMYh0SkpSkp3pRE4npC862c+08Yo3UJR0ksrIedYdFGK/93qAdGpnhQjAE1wS6pd4cztLlXSYJwTwAV3hYuf4WTikAk/E0flHTPOsHduWi+LK+m19/lGeq2kr3DE2ypHzkiK6nOVSJLP89kjmv5ZeIh1VHyAeJvYVSJNXxB2wAGKZYew2hr7NQjK2c/GWBFDrW9dSKAkES7TquYTOZ4gNRJWwrNpifYvLPoKZxnKAoaTuE3TGzp5WgboAzz6NLdHNFsn3Hx2DluOgbDqYAk7rTKqRX+qkoUFe+2lWISZQliu+CoUBr5YVnoZ6guf6rfHd5Klz1KSETK42/LTvThGT3foRhuwLNGoy6EzafDuNJbv499D/NvJv0f59zj/tvJvF/+e4t9G/gVp0by8hX7THHju5WcsRCc/Q0Bl8L43eMNTnS5HEvtxnOMZKF1m2qoD5JffpBlMlT2AAQFPYq6SLZB5l0z27UYztaEVfRV9UECxGNg02/0GmFZ2wDEmunojjxb0o4vlgPzPlHJ1tiW7KxLOUvEKCuv5KFrSO7p7lv7XPmv6An3RqYs88yyvI5BoG6+gz+K+CUTvjioqx4DLug3dKrRSmrEVXxVH4pQzDjriIkLx/S4u0CMMgBXLTY3bsbwJjZNbr/rMRCaLj8v+NfFxIF7kt2ZdyMcNCIXkEULX8p1fJ3NyV9N2tzmjx2clOKOE6LlgAuTOWorYb+2IYSG1rnwbsBar/qtMVE/yn9OGWJ+foodwQD34XsSEhwdQrz4FIcR7w5izyN5bxYqwxVxa6vXKQxGHmoulFcsHVzMii09oUVExjufP+OZ6lDNzuGcx5vYSv6YoTzFtEjFckxBuME5kKjqexZZ7w1/n09M+aLz3mrMyQ+VAI/LsesxF7G7xjGpYqU2rJhWDXPwZrltoB4G5tbLv4OzzqHiPbx1GJXKNggzEp42itmrQlrfKxvCpqEoH1NR5xtHUfe1Xtju6Ea+xBUnayTYYufU185gpfSCGNbsZZ+1m/LUbuCzK+IvZyD8/63I0s4hBqSit4UTr+Xcd/67lDBtVBpf8cikUkLakWAYgL1F+wvNe0Ev75S9+FV8p0Iiwgok8c9RhCeu3OhWi09vdeuOdxrSsOP8Dw1pG3wMt9O20QJAl8rznnXOm/jK+UHOxt50KxBIYe0MBvhHi+4AP+llXted+g+/3NnNZSApKgSGD9yeNSgCq72Z+JeytcEgm9+qw
*/