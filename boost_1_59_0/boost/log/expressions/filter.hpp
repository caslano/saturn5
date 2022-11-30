/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   filter.hpp
 * \author Andrey Semashev
 * \date   13.07.2012
 *
 * The header contains a filter function object definition.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FILTER_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FILTER_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/log/detail/sfinae_tools.hpp>
#endif
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Log record filter function wrapper.
 */
class filter
{
    BOOST_COPYABLE_AND_MOVABLE(filter)

public:
    //! Result type
    typedef bool result_type;

private:
    //! Filter function type
    typedef boost::log::aux::light_function< bool (attribute_value_set const&) > filter_type;

    //! Default filter, always returns \c true
    struct default_filter
    {
        typedef bool result_type;
        result_type operator() (attribute_value_set const&) const { return true; }
    };

private:
    //! Filter function
    filter_type m_Filter;

public:
    /*!
     * Default constructor. Creates a filter that always returns \c true.
     */
    filter() : m_Filter(default_filter())
    {
    }
    /*!
     * Copy constructor
     */
    filter(filter const& that) : m_Filter(that.m_Filter)
    {
    }
    /*!
     * Move constructor. The moved-from filter is left in an unspecified state.
     */
    filter(BOOST_RV_REF(filter) that) BOOST_NOEXCEPT : m_Filter(boost::move(that.m_Filter))
    {
    }

    /*!
     * Initializing constructor. Creates a filter which will invoke the specified function object.
     */
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    filter(FunT&& fun) : m_Filter(boost::forward< FunT >(fun))
    {
    }
#elif !defined(BOOST_MSVC) || BOOST_MSVC >= 1600
    template< typename FunT >
    filter(FunT const& fun, typename boost::disable_if_c< move_detail::is_rv< FunT >::value, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) : m_Filter(fun)
    {
    }
#else
    // MSVC 9 and older blows up in unexpected ways if we use SFINAE to disable constructor instantiation
    template< typename FunT >
    filter(FunT const& fun) : m_Filter(fun)
    {
    }
    template< typename FunT >
    filter(rv< FunT >& fun) : m_Filter(fun)
    {
    }
    template< typename FunT >
    filter(rv< FunT > const& fun) : m_Filter(static_cast< FunT const& >(fun))
    {
    }
    filter(rv< filter > const& that) : m_Filter(that.m_Filter)
    {
    }
#endif

    /*!
     * Move assignment. The moved-from filter is left in an unspecified state.
     */
    filter& operator= (BOOST_RV_REF(filter) that) BOOST_NOEXCEPT
    {
        m_Filter.swap(that.m_Filter);
        return *this;
    }
    /*!
     * Copy assignment.
     */
    filter& operator= (BOOST_COPY_ASSIGN_REF(filter) that)
    {
        m_Filter = that.m_Filter;
        return *this;
    }
    /*!
     * Initializing assignment. Sets the specified function object to the filter.
     */
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< typename FunT >
    filter& operator= (FunT const& fun)
#else
    template< typename FunT >
    typename boost::disable_if_c< is_same< typename remove_cv< FunT >::type, filter >::value, filter& >::type
    operator= (FunT const& fun)
#endif
    {
        filter(fun).swap(*this);
        return *this;
    }

    /*!
     * Filtering operator.
     *
     * \param values Attribute values of the log record.
     * \return \c true if the log record passes the filter, \c false otherwise.
     */
    result_type operator() (attribute_value_set const& values) const
    {
        return m_Filter(values);
    }

    /*!
     * Resets the filter to the default. The default filter always returns \c true.
     */
    void reset()
    {
        m_Filter = default_filter();
    }

    /*!
     * Swaps two filters
     */
    void swap(filter& that) BOOST_NOEXCEPT
    {
        m_Filter.swap(that.m_Filter);
    }
};

inline void swap(filter& left, filter& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FILTER_HPP_INCLUDED_

/* filter.hpp
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
*/