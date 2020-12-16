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
H1Xo6OnOUx8zkn22ViRrg2Ric32NUmaXIHNMzGubQewE+YNSliBBJpggf2wGcRBkLqsxCkWoG4D5uGj9eqvlwg1Wy/no/2fx3ID/i/D/cfzfs+G/0377+gnQhxj+WexvbqYV586UziOfedQ6zHohmKtHCugd+7Ybas63Rjd7C25AAsrjUwtKdFex1IpspWL9qelSUiXQ0yK4Vn1XG+4TJxC7oXECzHMLSBqkVt8T8Vh9JCveZO0zJ5FWBAJwguS8WHoNUwVuRBq9WksAjpztM182jyBRQoc7wCP+zUVim8s9EM/U7WCeLtIevsrUw4NnV1/XbgXPIO6SoyrSEz4TsgsQhL1OHx37UkU96+O8Kh5K2VpJHrb8XmxB1rpC3YvPvwMlS9T/Nj63saLnLOCrONdyNdNOIp8/hQP7X7f/+Cj928/vlF2oq29zy8AhPXgGlQ2V2d0CKa5eLc83yIvqGyJxdihHoSLstynNkjPOSTWck9tWCqv1lAk1nEZQLboQGejjDVUk6zWAteAzpF8wdeMxLn5S85K+r+tyzHqG5Uz61y24w9iNrIkLLrTnx0Q9STNBlnoaNrDhNpCq52I01YU3mgpFWihGguxcW81WmxLx8GoGb2Tg9XMg9Lk8DdhJ75oftosh0KsfVwjX8mLb9m1WC1aKsm3GSgGi6Co+jFyKLrW4iveb2THvsfhAUe5/vJlC2rUPbgCFvBlY4V8cOCsKe62EvSkGNlF7kbCDAYsCC6flyGj0MIUoMpV8y9QuK5FGoTtsEtENeCpl5Fnqdtpa53KLzMUak0u8Noq57EAMehks7zoOay6/xNrbwHqbwPo8sZYchXWGxPrMYyZWrsdfFwJrCDHSdqXMi8EKaisSzhRYXyTW84/CWiyxjonB2l57kljPRYw2aHwUoTRelSKUPVz3IbArHIjyUgINhMOEWWDCVFhZ3XwnhH6egqotNVoxyyjZvaJkZSzZYqsoWTBhpVVcAxrSsXthpQXvIAm/p/krMtxJyQtb74xstWevE+ju+dCoyzMCnUJ0NNNE6/ikrONtj8aylJU/RR19Vgor1zTXkeYXH+CY7PnWg3ohk3QRBbUHfbSulhr2uQn3CFNS1A5ZLkryLEvyskW2AalfVO5AVaxGw9R3ZrXPi2nKh38MlueIPZhMiNCE5L3i6U12hvtCHMAJYSyAIziAMOejvG1shjAeuSqDVpnIsCPa3WNFd6xnYVaLwrAc9f2jbfK6bJNrH2luk8Pa0utB2LMZvUOkeU0yH9kAQkJTLpkPKL+6mrwBU9sY1hZqYLJLA67gvBd0ueXkz3zDavkV/l/xltVyYKvV8ine34HNegj+F25Dm1ptNrsjISHBmhCXwF9cXFxCXHy8fL7+/98J/kC/TVZDshhrp0lBufAQ9HTGvRoFGM5vc1HP01M6vcItU3ilHN0e98kH2kCuyvHmbA6eWVJxx4Dy540Rs1+OmL4PNY+YBO2un5h0Xp7LLj30FMF2So5i/KViJPZH0r2/kxPrADABbfPEGnhMLOJbYBKBJ3kwxTf88saMNq3L3sif03fRQyuNlO6JqaZB797Vhgt+STJttw1elHmCjp8PrccFwqPuwgNL7SHE3CIKGAFI+AUn3iNj+3kFnYoMhSDXgGrv2EcZo0lruELwVu1q7FXC+7mOqxHPOowoe7El6/ZO6IVbeB0wwqZo0xohwV4MP8sgElTIBP2QADxY/5kIekEGdePkp/DiUaEbq2H3p2nzv9JNreuDIajwgWOQKFwwrk7DQ3Q9p+syqhi4QXGXdufloDqEZfZ54ua/wGShvnDTekHJ6UqpW4kgSrssrwmVaiyucJXSQZZbefq6071u+y4=
*/