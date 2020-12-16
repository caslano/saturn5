/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unary_function_terminal.hpp
 * \author Andrey Semashev
 * \date   21.07.2012
 *
 * The header contains attribute value extractor adapter for constructing expression template terminals.
 */

#ifndef BOOST_LOG_DETAIL_UNARY_FUNCTION_TERMINAL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_UNARY_FUNCTION_TERMINAL_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/copy_cv.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

/*!
 * \brief An adapter for a unary function to be used as a terminal in a Boost.Phoenix expression
 *
 * This class is an adapter between Boost.Phoenix expression invocation protocol and
 * a unary function. It forwards the call to the base function, passing only the first argument
 * from the original call. This allows to embed value extractors in template expressions.
 */
template< typename FunT >
class unary_function_terminal
{
private:
    //! Adopted function type
    typedef FunT function_type;
    //! Self type
    typedef unary_function_terminal< function_type > this_type;

public:
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;

    //! Function result type
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv<
            typename remove_reference< typename phoenix::result_of::env< ContextT >::type >::type
        >::type env_type;
        typedef typename env_type::args_type args_type;
        typedef typename boost::log::aux::copy_cv< ThisT, function_type >::type cv_function_type;

        typedef typename boost::result_of< cv_function_type(typename fusion::result_of::at_c< args_type, 0 >::type) >::type type;
    };

private:
    //! Adopted function
    function_type m_fun;

public:
    //! Default constructor
    BOOST_DEFAULTED_FUNCTION(unary_function_terminal(), {})
    //! Copy constructor
    unary_function_terminal(unary_function_terminal const& that) : m_fun(that.m_fun) {}
    //! Initializing constructor
    template< typename ArgT1 >
    explicit unary_function_terminal(ArgT1 const& arg1) : m_fun(arg1) {}
    //! Initializing constructor
    template< typename ArgT1, typename ArgT2 >
    unary_function_terminal(ArgT1 const& arg1, ArgT2 const& arg2) : m_fun(arg1, arg2) {}
    //! Initializing constructor
    template< typename ArgT1, typename ArgT2, typename ArgT3 >
    unary_function_terminal(ArgT1 const& arg1, ArgT2 const& arg2, ArgT3 const& arg3) : m_fun(arg1, arg2, arg3) {}

    //! The operator forwards the call to the base function
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type
    operator() (ContextT const& ctx)
    {
        return m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }

    //! The operator forwards the call to the base function
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type
    operator() (ContextT const& ctx) const
    {
        return m_fun(fusion::at_c< 0 >(phoenix::env(ctx).args()));
    }
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename FunT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::unary_function_terminal< FunT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_UNARY_FUNCTION_TERMINAL_HPP_INCLUDED_

/* unary_function_terminal.hpp
8B54Bsxo5ls6x/I9vSf8PR0+wkf4CB/hI3yEj/DxHzuikKWfXvt/ySWlVdVlqypOuO2fQntnbE/6gitcJ8JZsrS8eFk1SZY+gT2mT0DGsMsxvRHONCSZj9+GZdInMIuEz5uXV6jJcpwOxl5cY9ryO8TvFFtfgMbjBu0r7QS1z2jzGJtFTcAc3Wc1jdEaoB3yNnlIWG5LY6FnMnCL9/O2bwZEhBrD3/Yx+Z+wKRfuR6aPfHjqD/Le2Lt19Oa5t3148tatDbXPI/v54X7n/J9Edbz2k/v67Xi534BvT5vQ9jH8uyI87menlX54+eJlgyMvWRa35o+lL2JjEfdXvvL7n51TWnbH2r996aIH+t3dLtTcgba380LNEdgj7s/Ed9lVmJn51IR2g8dc3Htyz9BzBOztxVD7b7Z9H8wj0h7WMq3vTK62vW9DHG1XAmlXxsBU2BFOhJ20fdkF9oap6o6bkw5xk3Zkf3VPh4PhQDgUDlP34XAkzISZcIy6nwXHwGl6fgRmOPqewGhNb6Tcr/FI1PQmwXawC9yCZ8aXt7jmbd29urcZbdhesq8ZbpZx6IeDxqIH7n22CznYzLj0DZax6ckTGsenj0OKEMsYdd0/rfmx6lHZvvHqeZYx61vMvmvNj1/fhOxC9iNHQ4xnL9Ex7ZsCxrUH7t+WgxQ0GeO+uck4903ofee94T6B8BE+wkf4CB/hI3yEj8/i+JTt/0tq+L+wNitjzCWjTrgPwNPW30vYkU5nSe+QCF3/rxFOGlKRRR/BUmlHl42sKpw3Kb8wb+q8fLGhH01ycF9ZWrN8VQlere17whqbe3mW2NzJQHlZdY1jte3j39jNVyaYsfyWPfMC48aPjEMoKa2osa87Zfwbu/Av01ruB0jRfgdPXruavPrsreQJd1+ektTeStoDxmwmmL4LXxrpYzC6T40064PLkYxc34Vn4NV9dWHlqrJqTxeL5PfaLi3rPs1Pl5E4uM4lxeWOXe9pTXTz3YTW64a0GN34j1vlnrhzT83rBM3rGh1ncra4O7gzRxw97m3M66ol1ZWFpbU1hSUjy3wFzmnsW1otZajYjJl4VcKMYMxlhFUHe/10cEh0VlnpWHUQ6NeMK7GXPeO3g5Zrx6k241/ekWsDnP5SNs+XdbJ+RVl7EdlnKXMxIfq6VkvZKjb6JP2cS/pxa2LXb1KetrUzfWGGDxE+u1HH1SPL2l6eCGv086D4X1JTa9NloF8Kv7z3NVUhdJndpOw9knTiZe9BcZf0GV2RDtwkHY39h6qrkvaOHPO072Mucim6T1vWqKvSmkJ9wflDKnPHPHfyZcri6drPOcGJseqP+Ex9VSxhNTa/dR0niJ9M+nli7e8p1wPXxywz5W6YXJtI322sGfdfIm4Rjv/ejtV+6yPNlOv9nc7UkD2cGYnbKSgH6Qh6KY1n48bFx0TGuwPiYyLMPhMJIsQ4MzFJ/cejv5fTPEwzz/CI+vGev2Ip9/HWcm/qVFPHFsu50VVAOY+JCS7nl+O/Xp/dCqlBpMtXdFDZqPcVIco44QLL4uFm68G0af5rX1ZKOom7SRoPWdJ4JX43B6SRenJ1aavSSLgmc7PKSkK8h8aveS7HmR95r8xvGPdrUqfP7mCv0+sa6xvPF0ur6/QbW6jT69pQp9e1oU6va6ZO//p/sE5/X/d/K5njsR9EPpFYctHFQ++89d4HFvyz354lofrBQ/dfT+3kcX/qVwXv3l3e8+C/btmc82r/B4+E7tce2tnj3vD7hX2/WXRPh2vi9rgpH971CPaJO13c13118k9+2+Vbc8dV1694Y+cP1zMvoaODe02PGz5YO+fW868ZtODbCZmxB0L3syfhn3ju+tY=
*/