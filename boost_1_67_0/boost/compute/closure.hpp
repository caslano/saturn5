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