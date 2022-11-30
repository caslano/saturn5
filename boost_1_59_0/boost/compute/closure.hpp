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
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
*/