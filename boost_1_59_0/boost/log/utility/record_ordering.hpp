/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record_ordering.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * This header contains ordering predicates for logging records.
 */

#ifndef BOOST_LOG_UTILITY_RECORD_ORDERING_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_RECORD_ORDERING_HPP_INCLUDED_

#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/function_traits.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/utility/functional/logical.hpp>
#include <boost/log/utility/functional/nop.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Ordering predicate, based on opaque pointers to the record view implementation data
 *
 * Since record views only refer to a shared implementation data, this predicate is able to order the views
 * by comparing the pointers to the data. Therefore two views are considered to be equivalent if they
 * refer to the same implementation data. Otherwise it is not specified whether one record is ordered before
 * the other until the predicate is applied. Note that the ordering may change every time the application runs.
 *
 * This kind of ordering may be useful if log records are to be stored in an associative
 * container with as least performance overhead as possible, when the particular order is not important.
 *
 * The \c FunT template argument is the predicate that is used to actually compare pointers. It should be
 * able to compare <tt>const void*</tt> pointers. The compared pointers may refer to distinct memory regions,
 * the pointers must not be interpreted in any way.
 */
template< typename FunT = less >
class abstract_ordering :
    private FunT
{
public:
    //! Result type
    typedef bool result_type;

public:
    /*!
     * Default constructor. Requires \c FunT to be default constructible.
     */
    abstract_ordering() : FunT()
    {
    }
    /*!
     * Initializing constructor. Constructs \c FunT instance as a copy of the \a fun argument.
     */
    explicit abstract_ordering(FunT const& fun) : FunT(fun)
    {
    }

    /*!
     * Ordering operator
     */
    result_type operator() (record_view const& left, record_view const& right) const
    {
        // We rely on the fact that the attribute_values() method returns a reference to the object in the record implementation,
        // so we can compare pointers.
        return FunT::operator() (static_cast< const void* >(&left.attribute_values()), static_cast< const void* >(&right.attribute_values()));
    }
};

/*!
 * \brief Ordering predicate, based on attribute values associated with records
 *
 * This predicate allows to order log records based on values of a specifically named attribute
 * associated with them. Two given log records being compared should both have the specified
 * attribute value of the specified type to be able to be ordered properly. As a special case,
 * if neither of the records have the value, these records are considered equivalent. Otherwise,
 * the ordering results are unspecified.
 */
template< typename ValueT, typename FunT = less >
class attribute_value_ordering :
    private FunT
{
public:
    //! Result type
    typedef bool result_type;
    //! Compared attribute value type
    typedef ValueT value_type;

private:
    template< typename LeftT >
    struct l2_visitor
    {
        typedef void result_type;

        l2_visitor(FunT const& fun, LeftT const& left, bool& result) :
            m_fun(fun), m_left(left), m_result(result)
        {
        }

        template< typename RightT >
        result_type operator() (RightT const& right) const
        {
            m_result = m_fun(m_left, right);
        }

    private:
        FunT const& m_fun;
        LeftT const& m_left;
        bool& m_result;
    };

    struct l1_visitor;
    friend struct l1_visitor;
    struct l1_visitor
    {
        typedef void result_type;

        l1_visitor(attribute_value_ordering const& owner, record_view const& right, bool& result) :
            m_owner(owner), m_right(right), m_result(result)
        {
        }

        template< typename LeftT >
        result_type operator() (LeftT const& left) const
        {
            boost::log::visit< value_type >(m_owner.m_name, m_right, l2_visitor< LeftT >(static_cast< FunT const& >(m_owner), left, m_result));
        }

    private:
        attribute_value_ordering const& m_owner;
        record_view const& m_right;
        bool& m_result;
    };

private:
    //! Attribute value name
    const attribute_name m_name;

public:
    /*!
     * Initializing constructor.
     *
     * \param name The attribute value name to be compared
     * \param fun The ordering functor
     */
    explicit attribute_value_ordering(attribute_name const& name, FunT const& fun = FunT()) :
        FunT(fun),
        m_name(name)
    {
    }

    /*!
     * Ordering operator
     */
    result_type operator() (record_view const& left, record_view const& right) const
    {
        bool result = false;
        if (!boost::log::visit< value_type >(m_name, left, l1_visitor(*this, right, result)))
        {
            return !boost::log::visit< value_type >(m_name, right, nop());
        }
        return result;
    }
};

/*!
 * The function constructs a log record ordering predicate
 */
template< typename ValueT, typename FunT >
inline attribute_value_ordering< ValueT, FunT > make_attr_ordering(attribute_name const& name, FunT const& fun)
{
    typedef attribute_value_ordering< ValueT, FunT > ordering_t;
    return ordering_t(name, fun);
}

#if !defined(BOOST_LOG_NO_FUNCTION_TRAITS)

namespace aux {

    //! An ordering predicate constructor that uses SFINAE to disable invalid instantiations
    template<
        typename FunT,
        typename ArityCheckT = typename boost::enable_if_c< aux::arity_of< FunT >::value == 2 >::type,
        typename Arg1T = typename aux::first_argument_type_of< FunT >::type,
        typename Arg2T = typename aux::second_argument_type_of< FunT >::type,
        typename ArgsCheckT = typename boost::enable_if_c< is_same< Arg1T, Arg2T >::value >::type
    >
    struct make_attr_ordering_type
    {
        typedef attribute_value_ordering< Arg1T, FunT > type;
    };

} // namespace aux

/*!
 * The function constructs a log record ordering predicate
 */
template< typename FunT >
inline typename aux::make_attr_ordering_type< FunT >::type make_attr_ordering(attribute_name const& name, FunT const& fun)
{
    typedef typename aux::make_attr_ordering_type< FunT >::type ordering_t;
    return ordering_t(name, fun);
}

#endif // BOOST_LOG_NO_FUNCTION_TRAITS

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_RECORD_ORDERING_HPP_INCLUDED_

/* record_ordering.hpp
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
*/