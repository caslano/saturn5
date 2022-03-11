/// @file
// Boost.Convert
// Copyright (c) 2009-2016 Vladimir Batov.
//
// Many thanks to Julian Gonggrijp, Rob Stewart, Andrzej Krzemienski, Matus Chochlik, Jeroen Habraken,
// Hartmut Kaiser, Joel De Guzman, Thijs (M.A.) van den Berg, Roland Bock, Gavin Lambert, Paul Bristow,
// Alex Hagen-Zanker, Christopher Kormanyos for taking part in the Boost.Convert review.
//
// Special thanks to:
//
// 1. Alex Hagen-Zanker, Roland Bock, Rob Stewart for their considerable contributions to the design
//    and implementation of the library;
// 2. Andrzej Krzemienski for helping to partition responsibilities and to ultimately pave
//    the way for the boost::optional and future std::tr2::optional deployment;
// 3. Edward Diener the Boost Review Manager for helping with the converters' design, his continuous
//    involvement, technical and administrative help, guidance and advice;
// 4. Joel De Guzman, Rob Stewart and Alex Hagen-Zanker for making sure the performance tests work
//    as they should;
// 5. Paul Bristow for helping great deal with the documentation;
// 6. Kevlin Henney and Dave Abrahams for their lexical_cast-related insights and explanations.
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_HPP
#define BOOST_CONVERT_HPP

#include <boost/convert/detail/is_fun.hpp>
#include <boost/ref.hpp>

namespace boost
{
    namespace detail { enum throw_on_failure {}; }

    /// @details boost::throw_on_failure is the 'tag' object
    /// to request the exception-throwing behavior.
    detail::throw_on_failure const throw_on_failure = detail::throw_on_failure(0);

    namespace cnv
    {
        template<typename, typename, typename> struct reference;
        struct by_default;
    }

    /// @brief Boost.Convert main deployment interface
    /// @param[in] value_in   Value of the TypeIn type to be converted to the TypeOut type
    /// @param[in] converter  Converter to be used for conversion
    /// @return boost::optional<TypeOut> result of conversion together with the indication of
    ///         success or failure of the conversion request.
    /// @details For example,
    /// @code
    ///    boost::cnv::cstream cnv;
    ///
    ///    boost::optional<int>    i = boost::convert<int>("12", cnv);
    ///    boost::optional<string> s = boost::convert<string>(123.456, cnv);
    /// @endcode

    template<typename TypeOut, typename TypeIn, typename Converter>
    boost::optional<TypeOut>
    convert(TypeIn const& value_in, Converter const& converter)
    {
        optional<TypeOut> result;
        boost::unwrap_ref(converter)(value_in, result);
        return result;
    }

    namespace cnv { namespace detail
    {
        template<typename TypeOut, typename TypeIn, typename Converter =boost::cnv::by_default>
        struct delayed_resolution
        {
            static optional<TypeOut> convert(TypeIn const& value_in)
            {
                return boost::convert<TypeOut>(value_in, Converter());
            }
        };
    }}
    /// @brief Boost.Convert deployment interface with the default converter
    /// @details For example,
    /// @code
    ///    struct boost::cnv::by_default : boost::cnv::cstream {};
    ///
    ///    // boost::cnv::cstream (through boost::cnv::by_default) is deployed
    ///    // as the default converter when no converter is provided explicitly.
    ///    boost::optional<int>    i = boost::convert<int>("12");
    ///    boost::optional<string> s = boost::convert<string>(123.456);
    /// @endcode

    template<typename TypeOut, typename TypeIn>
    boost::optional<TypeOut>
    convert(TypeIn const& value_in)
    {
        return cnv::detail::delayed_resolution<TypeOut, TypeIn>::convert(value_in);
    }
}

namespace boost
{
    /// @brief Boost.Convert non-optional deployment interface

    template<typename TypeOut, typename TypeIn, typename Converter>
    TypeOut
    convert(TypeIn const& value_in, Converter const& converter, boost::detail::throw_on_failure)
    {
        return convert<TypeOut>(value_in, converter).value();
    }

    template<typename TypeOut, typename TypeIn, typename Converter, typename Fallback>
    typename enable_if<is_convertible<Fallback, TypeOut>, TypeOut>::type
    convert(TypeIn const& value_in, Converter const& converter, Fallback const& fallback)
    {
        return convert<TypeOut>(value_in, converter).value_or(fallback);
    }

    template<typename TypeOut, typename TypeIn, typename Converter, typename Fallback>
    typename enable_if<cnv::is_fun<Fallback, TypeOut>, TypeOut>::type
    convert(TypeIn const& value_in, Converter const& converter, Fallback fallback)
    {
        return convert<TypeOut>(value_in, converter).value_or_eval(fallback);
    }
}

namespace boost { namespace cnv
{
    template<typename Converter, typename TypeOut, typename TypeIn>
    struct reference
    {
        typedef reference this_type;

        reference(Converter const& cnv) : converter_(cnv) {}

#ifdef BOOST_CONVERT_CXX11
        reference(Converter&& cnv) : converter_(std::move(cnv)) {}
#endif

        this_type&
        value_or(TypeOut const& fallback)
        {
            return (fallback_ = fallback, *this);
        }

        TypeOut
        operator()(TypeIn const& value_in)
        {
            optional<TypeOut> result = convert<TypeOut>(value_in, converter_);
            return result ? result.get() : fallback_.value();
        }

        private:

        Converter        converter_;
        optional<TypeOut> fallback_;
    };
    template<typename Converter, typename TypeOut>
    struct reference<Converter, TypeOut, void>
    {
        typedef reference this_type;

        reference(Converter const& cnv) : converter_(cnv) {}

#ifdef BOOST_CONVERT_CXX11
        reference(Converter&& cnv) : converter_(std::move(cnv)) {}
#endif

        this_type&
        value_or(TypeOut const& fallback)
        {
            return (fallback_ = fallback, *this);
        }

        template<typename TypeIn>
        TypeOut
        operator()(TypeIn const& value_in)
        {
            optional<TypeOut> result = convert<TypeOut>(value_in, converter_);
            return result ? result.get() : fallback_.value();
        }

        private:

        Converter        converter_;
        optional<TypeOut> fallback_;
    };

    /// @brief Boost.Convert deployment interface with algorithms
    /// @details For example,
    /// @code
    ///    boost::array<char const*, 3> strs = {{ " 5", "0XF", "not an int" }};
    ///    std::vector<int>             ints;
    ///    boost::cnv::cstream           cnv;
    ///
    ///    cnv(std::hex)(std::skipws);
    ///
    ///    std::transform(
    ///        strs.begin(),
    ///        strs.end(),
    ///        std::back_inserter(ints),
    ///        boost::cnv::apply<int>(boost::cref(cnv)).value_or(-1));
    /// @endcode

    template<typename TypeOut, typename TypeIn, typename Converter>
    reference<Converter, TypeOut, TypeIn>
    apply(Converter const& cnv)
    {
        return cnv::reference<Converter, TypeOut, TypeIn>(cnv);
    }
    template<typename TypeOut, typename Converter>
    reference<Converter, TypeOut, void>
    apply(Converter const& cnv)
    {
        return cnv::reference<Converter, TypeOut, void>(cnv);
    }
}}

#endif // BOOST_CONVERT_HPP

/* convert.hpp
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
*/