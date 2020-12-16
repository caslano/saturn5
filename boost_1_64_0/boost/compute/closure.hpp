//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CLOSURE_HPP
#define BOOST_COMPUTE_CLOSURE_HPP

#include <string>
#include <sstream>

#include <boost/config.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/static_assert.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/function_traits.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/function.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/type_traits/detail/capture_traits.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class ResultType, class ArgTuple, class CaptureTuple>
class invoked_closure
{
public:
    typedef ResultType result_type;

    BOOST_STATIC_CONSTANT(
        size_t, arity = boost::tuples::length<ArgTuple>::value
    );

    invoked_closure(const std::string &name,
                    const std::string &source,
                    const std::map<std::string, std::string> &definitions,
                    const ArgTuple &args,
                    const CaptureTuple &capture)
        : m_name(name),
          m_source(source),
          m_definitions(definitions),
          m_args(args),
          m_capture(capture)
    {
    }

    std::string name() const
    {
        return m_name;
    }

    std::string source() const
    {
        return m_source;
    }

    const std::map<std::string, std::string>& definitions() const
    {
        return m_definitions;
    }

    const ArgTuple& args() const
    {
        return m_args;
    }

    const CaptureTuple& capture() const
    {
        return m_capture;
    }

private:
    std::string m_name;
    std::string m_source;
    std::map<std::string, std::string> m_definitions;
    ArgTuple m_args;
    CaptureTuple m_capture;
};

} // end detail namespace

/// \internal_
template<class Signature, class CaptureTuple>
class closure
{
public:
    typedef typename
        boost::function_traits<Signature>::result_type result_type;

    BOOST_STATIC_CONSTANT(
        size_t, arity = boost::function_traits<Signature>::arity
    );

    closure(const std::string &name,
            const CaptureTuple &capture,
            const std::string &source)
        : m_name(name),
          m_source(source),
          m_capture(capture)
    {
    }

    ~closure()
    {
    }

    std::string name() const
    {
        return m_name;
    }

    /// \internal_
    std::string source() const
    {
        return m_source;
    }

    /// \internal_
    void define(std::string name, std::string value = std::string())
    {
        m_definitions[name] = value;
    }

    /// \internal_
    detail::invoked_closure<result_type, boost::tuple<>, CaptureTuple>
    operator()() const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 0,
            "Non-nullary closure function invoked with zero arguments"
        );

        return detail::invoked_closure<result_type, boost::tuple<>, CaptureTuple>(
            m_name, m_source, m_definitions, boost::make_tuple(), m_capture
        );
    }

    /// \internal_
    template<class Arg1>
    detail::invoked_closure<result_type, boost::tuple<Arg1>, CaptureTuple>
    operator()(const Arg1 &arg1) const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 1,
            "Non-unary closure function invoked with one argument"
        );

        return detail::invoked_closure<result_type, boost::tuple<Arg1>, CaptureTuple>(
            m_name, m_source, m_definitions, boost::make_tuple(arg1), m_capture
        );
    }

    /// \internal_
    template<class Arg1, class Arg2>
    detail::invoked_closure<result_type, boost::tuple<Arg1, Arg2>, CaptureTuple>
    operator()(const Arg1 &arg1, const Arg2 &arg2) const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 2,
            "Non-binary closure function invoked with two arguments"
        );

        return detail::invoked_closure<result_type, boost::tuple<Arg1, Arg2>, CaptureTuple>(
            m_name, m_source, m_definitions, boost::make_tuple(arg1, arg2), m_capture
        );
    }

    /// \internal_
    template<class Arg1, class Arg2, class Arg3>
    detail::invoked_closure<result_type, boost::tuple<Arg1, Arg2, Arg3>, CaptureTuple>
    operator()(const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 3,
            "Non-ternary closure function invoked with three arguments"
        );

        return detail::invoked_closure<result_type, boost::tuple<Arg1, Arg2, Arg3>, CaptureTuple>(
            m_name, m_source, m_definitions, boost::make_tuple(arg1, arg2, arg3), m_capture
        );
    }

private:
    std::string m_name;
    std::string m_source;
    std::map<std::string, std::string> m_definitions;
    CaptureTuple m_capture;
};

namespace detail {

struct closure_signature_argument_inserter
{
    closure_signature_argument_inserter(std::stringstream &s_,
                                        const char *capture_string,
                                        size_t last)
        : s(s_)
    {
        n = 0;
        m_last = last;

        size_t capture_string_length = std::strlen(capture_string);
        BOOST_ASSERT(capture_string[0] == '(' &&
                     capture_string[capture_string_length-1] == ')');
        std::string capture_string_(capture_string + 1, capture_string_length - 2);
        boost::split(m_capture_names, capture_string_ , boost::is_any_of(","));
    }

    template<class T>
    void operator()(const T&) const
    {
        BOOST_ASSERT(n < m_capture_names.size());

        // get captured variable name
        std::string variable_name = m_capture_names[n];

        // remove leading and trailing whitespace from variable name
        boost::trim(variable_name);

        s << capture_traits<T>::type_name() << " " << variable_name;
        if(n+1 < m_last){
            s << ", ";
        }
        n++;
    }

    mutable size_t n;
    size_t m_last;
    std::vector<std::string> m_capture_names;
    std::stringstream &s;
};

template<class Signature, class CaptureTuple>
inline std::string
make_closure_declaration(const char *name,
                         const char *arguments,
                         const CaptureTuple &capture_tuple,
                         const char *capture_string)
{
    typedef typename
        boost::function_traits<Signature>::result_type result_type;
    typedef typename
        boost::function_types::parameter_types<Signature>::type parameter_types;
    typedef typename
        mpl::size<parameter_types>::type arity_type;

    std::stringstream s;
    s << "inline " << type_name<result_type>() << " " << name;
    s << "(";

    // insert function arguments
    signature_argument_inserter i(s, arguments, arity_type::value);
    mpl::for_each<
        typename mpl::transform<parameter_types, boost::add_pointer<mpl::_1>
    >::type>(i);
    s << ", ";

    // insert capture arguments
    closure_signature_argument_inserter j(
        s, capture_string, boost::tuples::length<CaptureTuple>::value
    );
    fusion::for_each(capture_tuple, j);

    s << ")";
    return s.str();
}

// used by the BOOST_COMPUTE_CLOSURE() macro to create a closure
// function with the given signature, name, capture, and source.
template<class Signature, class CaptureTuple>
inline closure<Signature, CaptureTuple>
make_closure_impl(const char *name,
                  const char *arguments,
                  const CaptureTuple &capture,
                  const char *capture_string,
                  const std::string &source)
{
    std::stringstream s;
    s << make_closure_declaration<Signature>(name, arguments, capture, capture_string);
    s << source;

    return closure<Signature, CaptureTuple>(name, capture, s.str());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

/// Creates a closure function object with \p name and \p source.
///
/// \param return_type The return type for the function.
/// \param name The name of the function.
/// \param arguments A list of arguments for the function.
/// \param capture A list of variables to capture.
/// \param source The OpenCL C source code for the function.
///
/// For example, to create a function which checks if a 2D point is
/// contained in a circle of a given radius:
/// \code
/// // radius variable declared in C++
/// float radius = 1.5f;
///
/// // create a closure function which returns true if the 2D point
/// // argument is contained within a circle of the given radius
/// BOOST_COMPUTE_CLOSURE(bool, is_in_circle, (const float2_ p), (radius),
/// {
///     return sqrt(p.x*p.x + p.y*p.y) < radius;
/// });
///
/// // vector of 2D points
/// boost::compute::vector<float2_> points = ...
///
/// // count number of points in the circle
/// size_t count = boost::compute::count_if(
///     points.begin(), points.end(), is_in_circle, queue
/// );
/// \endcode
///
/// \see BOOST_COMPUTE_FUNCTION()
#ifdef BOOST_COMPUTE_DOXYGEN_INVOKED
#define BOOST_COMPUTE_CLOSURE(return_type, name, arguments, capture, source)
#else
#define BOOST_COMPUTE_CLOSURE(return_type, name, arguments, capture, ...) \
    ::boost::compute::closure< \
        return_type arguments, BOOST_TYPEOF(boost::tie capture) \
    > name = \
        ::boost::compute::detail::make_closure_impl< \
            return_type arguments \
        >( \
            #name, #arguments, boost::tie capture, #capture, #__VA_ARGS__ \
        )
#endif

#endif // BOOST_COMPUTE_CLOSURE_HPP

/* closure.hpp
yG5k+6MC25+uvvPG7S9W2P7B/rKrdtrPdHPZVRfaP7gL7V8THdj+ndR3/Gspuwp4/oHfPPKby7CQ3nkZFsoykWHp27Jou8C2ZKjfkIC28FmafUPaaUtpF9qyT19LHrctyeMqhDxu450XjD1/xmO1jacklN601yejzeRrZnI6M/mUmfzun5PTGcvXtp78TsrF2szlXX2lXIxzGBN5XLLkA30VWn6lQfgGST7+/TYpN03DtyTE/FpCrN/mEPNzfB1afvgWBc1vcQhyxXdThFwRGdss2WIXZItdkSvevTTiH5Ut/l/kisuvjOgW2WI63p0iUBVoMagZtAG0GZSYCr/XoLLUbVfe2EPr/+q5W1H/n79Q6v+nFk/S6/8ntqP/t6Wi7C+p+2YGWv1/RYpuTgjezq8rkVfAurKCa+sU3986JQ51Utr0dcKxilnec652EGsO9CHirBf5U0T6IDGPdc2qAQPnqjLdjvQdU0V6RfXcynrt2dLkaddHoffs+R3EegP14DX1JpSNa6Js4WMuRc1f8Mny9O2PCGy/HfyOwPbPY/v5TLTtJz/bPz6g/Uxn++vjjdvv6GD7UY+A9o83aD/KC2i/tP8wkSvk69vfIfuPpoVB7D8M1vkJ6tpIX17X7D8M1tJJqahXm8/+g+WIdyxRt4Ymn+kamunma2ikd34NndiJNbS0/zBodwrya26T607Z7sBvC/nM15tI7/x6syLFWm9uS+vNS8V687SGY4df98q9h+w696OSJ36/023Zf3TV/gN/n03XQX00Z0wpXG+mkI9nHcl1lYqp9A3ZD2ij78Q4NW/6VByoyc8RJL/BzG8I80tnfkOZ307Mb5hmPZcfZD2c4OPDd7v99op1boh8ze3wrQlhHenE9VWY40au9Nio5K4Argq+nix16deUVSu27rpywYr/xtpStVtpMbVdQXxFaOvMYGvMrJXdv87sqA2Le6Vvvbl4ZdfWnMtWtr/uvBs8mcDMKyO6Zf3ZkbXnlpWhrz/X4b3bBFL64bwdUC5oGsjVb9tdc1ph2wk9s/53HVV5fNf1/+r6frxc3/OsTvpiTiBGqfrSL3xrm9L9Jhyi1RufYFeQ1ih9vq8QvFM4J+e9mvPyfxLxMCUVc/AoVY6L+0+Jx332kM7O183JUTbm4I269bCD8oBT6b/+RNB2qbj+pb4N2nPykQ9CXaVbUaQv/gmC/zBlhLeuPCf/a/DeA0pL9J2ZnxW0rlHxx4i8lPTKujqff3hrrcC1gtmctPvXEE+LNYRzUM73f7ZU3l5+6pUz9hlw6Xtma4L/pw6qSuE7zN9NWr/snIMrnIMnMJ5EP+xpPKc1AzgCOIr+2Hfnua3789zW2cCRnEM3KnxXgaeyvFhgDcuLp1/2RPp978PzMFOAo7n2yOXao4hrjf24hphCndQhQAdwPnU7JzK9MMS5eXC9jqXTMdfpdFyf0126nMgO6nEWZf+39DcdmT+HOnd+F3Pk3615shWsYAUrWOF/GHpm/V9zdO3crq//VX2nsy/WoVjPRihqnuWuI6j3z03E3Jxr6pwwE7v5z8WauuSAye3qV8dr9av5JwXoV2VZy0zK2uwpawYLC7ksl2FZvUVZcV5dbphHVpAMnN4X9ftMlCU6ZE52tZARXO/RecPxAvKmjOAgwbdd2HT8/5bvzD7e30fcFxmn3jfn6Fq35779ZPqAsFKsTp5Vhgo+t08PK/iqNHxOaEM/Avn4GtzHuypFedWSzy7OsStTFKGjd4kz71RBTblaOK5NiD8gTJyTRf4wwe+kDORa0T6x50HyZvnxVpHXLnqtxj3PBV5RhzDlHMH3MtZqywTPYMED3X6tpz3qGvlQwRMeti+e7no=
*/