/// @file
// Boost.Convert
// Copyright (c) 2009-2020 Vladimir Batov.
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
#include <boost/core/ref.hpp>

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
    typename std::enable_if<is_convertible<Fallback, TypeOut>::value, TypeOut>::type
    convert(TypeIn const& value_in, Converter const& converter, Fallback const& fallback)
    {
        return convert<TypeOut>(value_in, converter).value_or(fallback);
    }

    template<typename TypeOut, typename TypeIn, typename Converter, typename Fallback>
    typename std::enable_if<cnv::is_fun<Fallback, TypeOut>::value, TypeOut>::type
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
        using this_type = reference;

        reference (Converter const& cnv) : converter_(cnv) {}
        reference (Converter&& cnv) : converter_(std::move(cnv)) {}

        this_type&
        value_or(TypeOut const& fallback)
        {
            return (fallback_ = fallback, *this);
        }

        TypeOut
        operator()(TypeIn const& value_in) const
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
        using this_type = reference;

        reference (Converter const& cnv) : converter_(cnv) {}
        reference (Converter&& cnv) : converter_(std::move(cnv)) {}

        this_type&
        value_or(TypeOut const& fallback)
        {
            return (fallback_ = fallback, *this);
        }

        template<typename TypeIn>
        TypeOut
        operator()(TypeIn const& value_in) const
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
    ///    std::array<char const*, 3> strs = {{ " 5", "0XF", "not an int" }};
    ///    std::vector<int>           ints;
    ///    boost::cnv::cstream         cnv;
    ///
    ///    cnv(std::hex)(std::skipws);
    ///
    ///    std::transform(
    ///        strs.begin(),
    ///        strs.end(),
    ///        std::back_inserter(ints),
    ///        boost::cnv::apply<int>(std::cref(cnv)).value_or(-1));
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