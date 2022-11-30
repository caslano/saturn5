/*
 *             Copyright Andrey Semashev 2022.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/manipulators/invoke.hpp
 * \author Andrey Semashev
 * \date   27.02.2022
 *
 * The header contains implementation of a stream manipulator for invoking a user-defined function.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_INVOKE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_INVOKE_HPP_INCLUDED_

#include <cstddef>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/type_traits/remove_cv.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/type_traits/remove_reference.hpp>
#endif
#include <boost/log/detail/is_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Stream manipulator for invoking a user-defined function as part of stream output.
 */
template< typename FunctionT >
class invoke_manipulator
{
private:
    mutable FunctionT m_function;

public:
    //! Initializing constructor
    explicit invoke_manipulator(FunctionT const& func) :
        m_function(func)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    //! Initializing constructor
    explicit invoke_manipulator(FunctionT&& func) :
        m_function(static_cast< FunctionT&& >(func))
    {
    }
#endif

    //! The method invokes the saved function with the output stream
    template< typename StreamT >
    void output(StreamT& stream) const
    {
        m_function(stream);
    }
};

/*!
 * Stream output operator for \c invoke_manipulator. Invokes the function saved in the manipulator.
 */
template< typename StreamT, typename FunctionT >
inline typename boost::enable_if_c< log::aux::is_ostream< StreamT >::value, StreamT& >::type operator<< (StreamT& stream, invoke_manipulator< FunctionT > const& manip)
{
    manip.output(stream);
    return stream;
}

#if !defined(BOOST_LOG_DOXYGEN_PASS)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

//! Invoke manipulator generator function
template< typename FunctionT >
inline invoke_manipulator<
    typename boost::remove_cv<
        typename boost::remove_reference< FunctionT >::type
    >::type
>
invoke_manip(FunctionT&& func)
{
    return invoke_manipulator<
        typename boost::remove_cv<
            typename boost::remove_reference< FunctionT >::type
        >::type
    >(static_cast< FunctionT&& >(func));
}

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && \
    !defined(BOOST_NO_CXX14_GENERIC_LAMBDAS) && \
    !defined(BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION)

//! Invoke manipulator generator function
template< typename FunctionT, typename Arg0, typename... Args >
inline auto invoke_manip(FunctionT&& func, Arg0&& arg0, Args&&... args)
{
    return boost::log::invoke_manip
    (
#if !defined(BOOST_LOG_NO_CXX20_PACK_EXPANSION_IN_LAMBDA_INIT_CAPTURE)
        [func = static_cast< FunctionT&& >(func), arg0 = static_cast< Arg0&& >(arg0), ...args = static_cast< Args&& >(args)](auto& stream) mutable
#else
        [func, arg0, args...](auto& stream) mutable
#endif
        {
#if !defined(BOOST_MSVC) || BOOST_MSVC >= 1910
            static_cast< FunctionT&& >(func)(stream, static_cast< Arg0&& >(arg0), static_cast< Args&& >(args)...);
#else
            // MSVC 19.0 (VS 14.0) ICEs if we use perfect forwarding here
            func(stream, arg0, args...);
#endif
        }
    );
}

#endif // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) ...

#else // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

//! Invoke manipulator generator function
template< typename FunctionT >
inline invoke_manipulator< typename boost::remove_cv< FunctionT >::type >
invoke_manip(FunctionT const& func)
{
    return invoke_manipulator< typename boost::remove_cv< FunctionT >::type >(func);
}

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#else // !defined(BOOST_LOG_DOXYGEN_PASS)

/*!
 * Invoke manipulator generator function.
 *
 * \param func User-defined function to invoke on output. The function must be callable with a reference to the output stream as the first argument, followed by \a args.
 * \param args Additional arguments to pass to \a func.
 * \returns Manipulator to be inserted into the stream.
 *
 * \note \a args are only supported since C++14.
 */
template< typename FunctionT, typename... Args >
invoke_manipulator< unspecified > invoke_manip(FunctionT&& func, Args&&... args);

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_INVOKE_HPP_INCLUDED_

/* invoke.hpp
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
*/