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