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