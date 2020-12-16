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
Ruqbu9LUJsY9mtiFx8XY81vfJL+eEkm5D5nXjaHzqnG5uHnzqrGFyG/9CeQ3xT+/5j6Bz3hIrC3PSJM8e8wexTWrq0qd0Pne0Uy+G4KeMTGGsmecQJ4DnzH38K4fqPndGxton2iP3J+Fe0B+5RGzem7VpYU1l1Za8mwfJ9FyuqfZ0x2YxnUdxK9Zr20wsp40vhmYRvNICsV0Evq5HJgXepzCmyeYZu+7kxYXrNcHsnDPD0izfKO2Vp9p+S2mzV4OmpTxvZo2hdMBeZC0ZQSkTcZ6VNcUr6wMpcsuMFPCRFvTm3GC6WWck47RCNblDtKbHZhe/cz0bDVFsmtWVzut1Gv2CabT+8yTO5r0mX2xHiKdswPTqfthtS5ts09S2vZo2jJ9/azyDhX50sZHzBKaKOWlNaX2550ES8R/mi2txBU43uuDVqzzHSLd5pshv5Mjx1gNdBbyQ099bNJtxhL7von92gSPi7+h2DKiWxxP7DQznnhT5+BxzTtJh3OeSUe15bff/h0jYQZbdSjx8Z+OrWnmt9/4NWN3xG9h6HVWxb95Psf/TeT9TSF95rvBjKVxcDPpCCyDUfIvXYf6bhQgj3jeY38dmu+JIP0Zu/tk8T8PW6Rrf599ekGHLX9TeP2niB59/jULpm0wTfzNwFYaYdGviceUszr57mz9uD1/HacE6NiX/h7+eg5MZ+C3apK9vDb46Tr4O8ZeXh9qprw2BJbX5r9jgsorfpsprw2fSnnlnkHl1aQjQIe7dEDk1Vper0IeRYeHA3Q4orl33pTZDyTM5U6VvcxqnK7Zn99tMq49fr7nepZVr4dD1wOm7A6R8GeTN3vZNXGg60jV9eBkyvBxll/VOXvlt62OyNWNGL6tOr9ddb55foDOQ9URZkztVvG/SeqIm0LonDiN3t4NbHsYvb8lfobZ9E74ZusN03d0j/i7SeqN62z6N3GZsb/o/cSfQYp5BsdXh+xKsZf/ygUBz6K5OsSU/9ULmi3/xNm0/BOr33PYsCBk+SdsyHrFlP/tC5ot/8TxaZb/luscb1vnzW6OHKjZfK89xklagU/nwe0xu94TYbqEG+ykhtA78ZoyXCp9qgHRmu++AeLvdKv+JQ5TT7f4bTUthM7MmG3SgZt/OgJ1dCDVfEfIUYA84SmXfjqytwftOrpDwg3kvJ29bBa0fuxhZdt00WL5MWMBm9STvXo4ckzViHKRtZ42cYAOAtuXH1u+5w+I/8n2tnBByH0zzHt5UPx0tOrChKfP8SDPrKE749WkzzHL2xcp7nu87p36RsexmUVr7BIWnTW3b4Wp05J7OnKgPjN35sf4z17o01tw29euuxwJk2LTHfFp3s18BxOlTVf4b1s7z5Zv7oObuU9g27SXxMG5r355ytP+88+3aZva85wIrxb/Sfb2n1+el0h5MdHZ8oz/k/OumDHJ8tzNPQP6EA5r/kdqZCO0/dtg8u+rLwJbwsFt4SRv/56EHeoMstetGrcr+7ukcv+dyEeU8zhH7Bidop3W2eBCtZFHetvIfbQucHmH4GR4r+c71eTNmOBCfi8558v+N24/6sCZCLYO7umNY47Jl7qZ+vDuJna4FDhc4opyu1nrBRPeOv83lbNFEv4Vq/0lCk6U60edlmxakeJvpJtGqvMQm23laDO2lWOtsK00yD3anbA9qpk5LtO8c1ziFpm1zOQ8Wc+rqpr/Dbnb2GN8c1jMfDBH57sYN6ODgL10jvYJsd/PouPc72fRydvvxzvv4GBacBq/62k7BKSxclWlWtI7iR29+XQS1tRp7TM8fj1hl66uWGKt04x/n5299fkqN/ny1WncEzdzz4BnsqevfX+jhkXHt79Rw6LW728=
*/