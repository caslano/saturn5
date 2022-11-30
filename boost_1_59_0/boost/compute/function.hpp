//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTION_HPP
#define BOOST_COMPUTE_FUNCTION_HPP

#include <map>
#include <string>
#include <sstream>
#include <vector>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/static_assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/function_traits.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/config.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class ResultType, class ArgTuple>
class invoked_function
{
public:
    typedef ResultType result_type;

    BOOST_STATIC_CONSTANT(
        size_t, arity = boost::tuples::length<ArgTuple>::value
    );

    invoked_function(const std::string &name,
                     const std::string &source)
        : m_name(name),
          m_source(source)
    {
    }

    invoked_function(const std::string &name,
                     const std::string &source,
                     const std::map<std::string, std::string> &definitions)
        : m_name(name),
          m_source(source),
          m_definitions(definitions)
    {
    }

    invoked_function(const std::string &name,
                     const std::string &source,
                     const ArgTuple &args)
        : m_name(name),
          m_source(source),
          m_args(args)
    {
    }

    invoked_function(const std::string &name,
                     const std::string &source,
                     const std::map<std::string, std::string> &definitions,
                     const ArgTuple &args)
        : m_name(name),
          m_source(source),
          m_definitions(definitions),
          m_args(args)
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

private:
    std::string m_name;
    std::string m_source;
    std::map<std::string, std::string> m_definitions;
    ArgTuple m_args;
};

} // end detail namespace

/// \class function
/// \brief A function object.
template<class Signature>
class function
{
public:
    /// \internal_
    typedef typename
        boost::function_traits<Signature>::result_type result_type;

    /// \internal_
    BOOST_STATIC_CONSTANT(
        size_t, arity = boost::function_traits<Signature>::arity
    );

    /// \internal_
    typedef Signature signature;

    /// Creates a new function object with \p name.
    function(const std::string &name)
        : m_name(name)
    {
    }

    /// Destroys the function object.
    ~function()
    {
    }

    /// \internal_
    std::string name() const
    {
        return m_name;
    }

    /// \internal_
    void set_source(const std::string &source)
    {
        m_source = source;
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

    bool operator==(const function<Signature>& other) const
    {
        return
            (m_name == other.m_name)
                && (m_definitions == other.m_definitions)
                && (m_source == other.m_source);
    }

    bool operator!=(const function<Signature>& other) const
    {
        return !(*this == other);
    }

    /// \internal_
    detail::invoked_function<result_type, boost::tuple<> >
    operator()() const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 0,
            "Non-nullary function invoked with zero arguments"
        );

        return detail::invoked_function<result_type, boost::tuple<> >(
            m_name, m_source, m_definitions
        );
    }

    /// \internal_
    template<class Arg1>
    detail::invoked_function<result_type, boost::tuple<Arg1> >
    operator()(const Arg1 &arg1) const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 1,
            "Non-unary function invoked one argument"
        );

        return detail::invoked_function<result_type, boost::tuple<Arg1> >(
            m_name, m_source, m_definitions, boost::make_tuple(arg1)
        );
    }

    /// \internal_
    template<class Arg1, class Arg2>
    detail::invoked_function<result_type, boost::tuple<Arg1, Arg2> >
    operator()(const Arg1 &arg1, const Arg2 &arg2) const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 2,
            "Non-binary function invoked with two arguments"
        );

        return detail::invoked_function<result_type, boost::tuple<Arg1, Arg2> >(
            m_name, m_source, m_definitions, boost::make_tuple(arg1, arg2)
        );
    }

    /// \internal_
    template<class Arg1, class Arg2, class Arg3>
    detail::invoked_function<result_type, boost::tuple<Arg1, Arg2, Arg3> >
    operator()(const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) const
    {
        BOOST_STATIC_ASSERT_MSG(
            arity == 3,
            "Non-ternary function invoked with three arguments"
        );

        return detail::invoked_function<result_type, boost::tuple<Arg1, Arg2, Arg3> >(
            m_name, m_source, m_definitions, boost::make_tuple(arg1, arg2, arg3)
        );
    }

private:
    std::string m_name;
    std::string m_source;
    std::map<std::string, std::string> m_definitions;
};

/// Creates a function object given its \p name and \p source.
///
/// \param name The function name.
/// \param source The function source code.
///
/// \see BOOST_COMPUTE_FUNCTION()
template<class Signature>
inline function<Signature>
make_function_from_source(const std::string &name, const std::string &source)
{
    function<Signature> f(name);
    f.set_source(source);
    return f;
}

namespace detail {

// given a string containing the arguments declaration for a function
// like: "(int a, const float b)", returns a vector containing the name
// of each argument (e.g. ["a", "b"]).
inline std::vector<std::string> parse_argument_names(const char *arguments)
{
    BOOST_ASSERT_MSG(
        arguments[0] == '(' && arguments[std::strlen(arguments)-1] == ')',
        "Arguments should start and end with parentheses"
    );

    std::vector<std::string> args;

    size_t last_space = 0;
    size_t skip_comma = 0;
    for(size_t i = 1; i < std::strlen(arguments) - 2; i++){
        const char c = arguments[i];

        if(c == ' '){
            last_space = i;
        }
        else if(c == ',' && !skip_comma){
            std::string name(
                arguments + last_space + 1, i - last_space - 1
            );
            args.push_back(name);
        }
        else if(c == '<'){
            skip_comma++;
        }
        else if(c == '>'){
            skip_comma--;
        }
    }

    std::string last_argument(
        arguments + last_space + 1, std::strlen(arguments) - last_space - 2
    );
    args.push_back(last_argument);

    return args;
}

struct signature_argument_inserter
{
    signature_argument_inserter(std::stringstream &s_, const char *arguments, size_t last)
        : s(s_)
    {
        n = 0;
        m_last = last;

        m_argument_names = parse_argument_names(arguments);

        BOOST_ASSERT_MSG(
            m_argument_names.size() == last,
            "Wrong number of arguments"
        );
    }

    template<class T>
    void operator()(const T*)
    {
        s << type_name<T>() << " " << m_argument_names[n];
        if(n+1 < m_last){
            s << ", ";
        }
        n++;
    }

    size_t n;
    size_t m_last;
    std::stringstream &s;
    std::vector<std::string> m_argument_names;
};

template<class Signature>
inline std::string make_function_declaration(const char *name, const char *arguments)
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

    if(arity_type::value > 0){
        signature_argument_inserter i(s, arguments, arity_type::value);
        mpl::for_each<
            typename mpl::transform<parameter_types, boost::add_pointer<mpl::_1>
        >::type>(i);
    }

    s << ")";
    return s.str();
}

struct argument_list_inserter
{
    argument_list_inserter(std::stringstream &s_, const char first, size_t last)
        : s(s_)
    {
        n = 0;
        m_last = last;
        m_name = first;
    }

    template<class T>
    void operator()(const T*)
    {
        s << type_name<T>() << " " << m_name++;
        if(n+1 < m_last){
            s << ", ";
        }
        n++;
    }

    size_t n;
    size_t m_last;
    char m_name;
    std::stringstream &s;
};

template<class Signature>
inline std::string generate_argument_list(const char first = 'a')
{
    typedef typename
        boost::function_types::parameter_types<Signature>::type parameter_types;
    typedef typename
        mpl::size<parameter_types>::type arity_type;

    std::stringstream s;
    s << '(';

    if(arity_type::value > 0){
        argument_list_inserter i(s, first, arity_type::value);
        mpl::for_each<
            typename mpl::transform<parameter_types, boost::add_pointer<mpl::_1>
        >::type>(i);
    }

    s << ')';
    return s.str();
}

// used by the BOOST_COMPUTE_FUNCTION() macro to create a function
// with the given signature, name, arguments, and source.
template<class Signature>
inline function<Signature>
make_function_impl(const char *name, const char *arguments, const char *source)
{
    std::stringstream s;
    s << make_function_declaration<Signature>(name, arguments);
    s << source;

    return make_function_from_source<Signature>(name, s.str());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

/// Creates a function object with \p name and \p source.
///
/// \param return_type The return type for the function.
/// \param name The name of the function.
/// \param arguments A list of arguments for the function.
/// \param source The OpenCL C source code for the function.
///
/// The function declaration and signature are automatically created using
/// the \p return_type, \p name, and \p arguments macro parameters.
///
/// The source code for the function is interpreted as OpenCL C99 source code
/// which is stringified and passed to the OpenCL compiler when the function
/// is invoked.
///
/// For example, to create a function which squares a number:
/// \code
/// BOOST_COMPUTE_FUNCTION(float, square, (float x),
/// {
///     return x * x;
/// });
/// \endcode
///
/// And to create a function which sums two numbers:
/// \code
/// BOOST_COMPUTE_FUNCTION(int, sum_two, (int x, int y),
/// {
///     return x + y;
/// });
/// \endcode
///
/// \see BOOST_COMPUTE_CLOSURE()
#ifdef BOOST_COMPUTE_DOXYGEN_INVOKED
#define BOOST_COMPUTE_FUNCTION(return_type, name, arguments, source)
#else
#define BOOST_COMPUTE_FUNCTION(return_type, name, arguments, ...) \
    ::boost::compute::function<return_type arguments> name = \
        ::boost::compute::detail::make_function_impl<return_type arguments>( \
            #name, #arguments, #__VA_ARGS__ \
        )
#endif

#endif // BOOST_COMPUTE_FUNCTION_HPP

/* function.hpp
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
*/