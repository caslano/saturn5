/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fallback_policy.hpp
 * \author Andrey Semashev
 * \date   18.08.2012
 *
 * The header contains definition of fallback policies when attribute value visitation or extraction fails.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The \c fallback_to_none policy results in returning an empty value reference if the attribute value cannot be extracted.
 */
struct fallback_to_none
{
    enum { guaranteed_result = false };

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const&)
    {
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
    }
};

/*!
 * The \c fallback_to_throw policy results in throwing an exception if the attribute value cannot be extracted.
 */
struct fallback_to_throw
{
    enum { guaranteed_result = true };

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT&)
    {
        return false;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    static bool apply_default(FunT const&)
    {
        return false;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const& t)
    {
        BOOST_LOG_THROW_DESCR_PARAMS(invalid_type, "Attribute value has incompatible type", (t));
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
        BOOST_LOG_THROW_DESCR(missing_value, "Attribute value not found");
    }
};

/*!
 * The \c fallback_to_default policy results in a default value if the attribute value cannot be extracted.
 */
template< typename DefaultT >
struct fallback_to_default
{
    enum { guaranteed_result = true };

    //! Default value type
    typedef typename remove_cv< typename remove_reference< DefaultT >::type >::type default_type;

    /*!
     * Default constructor.
     */
    fallback_to_default() : m_default()
    {
    }

    /*!
     * Initializing constructor.
     */
    explicit fallback_to_default(default_type const& def_val) : m_default(def_val)
    {
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    bool apply_default(FunT& fun) const
    {
        fun(m_default);
        return true;
    }

    /*!
     * The method is called in order to apply a function object to the default value.
     */
    template< typename FunT >
    bool apply_default(FunT const& fun) const
    {
        fun(m_default);
        return true;
    }

    /*!
     * The method is called when value extraction failed because the attribute value has different type than requested.
     */
    static void on_invalid_type(typeindex::type_index const&)
    {
    }

    /*!
     * The method is called when value extraction failed because the attribute value was not found.
     */
    static void on_missing_value()
    {
    }

private:
    //! Default value
    DefaultT m_default;
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_HPP_INCLUDED_

/* fallback_policy.hpp
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
*/