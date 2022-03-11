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