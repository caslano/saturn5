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
8LyPAnYFzjHQ178yud1gj+vmwt9D03Qa7Asr4/NhX9jeqeWPsN/E7QNIOJdRLhvPZR2Q5rXQSwQ+1O/hXHfQMtjN7z4uC4XfwMc49/HxziUQ68b5ysAal/4tf37nO+LsDfK9XgaGpXkqAyJPrNzdVvEb80D4/ZB9FQjTU5kQ66/c7iePZaKgP/ezOUO4XY74nXd/5qmMIJyHn5GhcLvfMHNJxRkZwj1SJgZncJwkJdz3WRQMi5+KVUrMH2vc7gaph3h0hRkHswrmB5i/t0dD9TnnYLAi93OMLEIdDxZ7VMpx2Qmk3SKksM3dL5/DL5M3LubuPiRe0LIc+ozmMH1gFiP0V0C+lq+H9xlhsNmM/fomoaeQP3KfwuOWs4edf+F+1qjnsyif/ExRz2eTPvzszb78DNIK5p+7v3kjpvxbVePY3E2rh//rzwL9Z51x6vks0Ief+en5TNQnP9vT81mjDztb9cnPOPV89uxDzybl54UC4qwa6CP6sWCYN2B43UID5gMGg1YwBCwB1gRtYDjoAiPAVqAVbA8WBzPBEuBAsCQ4GiwFTgSjwPlgaXAxWB5cBtrBHSLcV8FK4H4wGjwEOsDTYDXwHFgD/BGsqX8DUJyzAvK9WgXO/zsszv87AoaA74G/gEvyzgIBdgl//jCzhb9Acf5fCGgEQ0F/sBIYAEaAZUErWB0sBjYHi4NPgSXAkWApcCZYGswGy4ALwHLgJrA8mANWBHeK8H8BL+jnIfCzKHj8wmG+FvHbyhAvcAdYDNwJ2sDdYEXwVbAOuAdsCr4GtgRfB4eBb4DPgm+Cz4FvgxvBfeCn4DvgBfBdUMH994MW8CBYEjwENgMPg5ngEXAQ+D44HjwKrgGPgTngh+Ab4HHwA/Aj8AT4MZir7wYm3jcV70WPBFvDLBffuXIJfROEvolC35ZC32Shbyuhb4rQt43Qt63Qt53Qt4PQt6PQt5PQt7PQtwsYAHYFrWA3sAHYHewCpoKjwDRwMZgOvgRmgjvAHuDHYE/wJ7AXqEGX3mBpsA/YEOwLusD+YEdwADgVHAguArPAHHAQeBQcDF4Eh4AqCvpQ0AwOB4uBI8CG4EgwA3waHAmOAheAo8GXwTHgMfAZ8CI4FrwFjgcVtCsTQDs4EWwCTgK7g5PB0eAUcCk4FXwVnAYeBmeAJ8CZ4G1wFlhCQb0CY8A5YBI4F+wHzgOzwPngdPBZcDO4ADwELgTPgotApqKPAk3gErASuBRsAC4Du4HPg8+Ay8E54EpwKfgCuA9cBX4HvgheBF8Cb4JrQCvK3VqwHLgerAZuAJuAG8EW4CZQtDtiPzDaGw/tTo50v915BWTgdlC0O2K/KeLgod2JEe1ONdHuVBftTnPR7jhFu1MLjAFrgw3AOmBrsC7YB4wFx4ANwYlgI3Ay2Bh8DnSBy8Fm4CoR/i9gjr4vEGkm2p1AmDUifiWghw9YGvQHy4AlwXJgNFgedIAVwHpgRbAPWAkcB1YG14Ax4JegAzwDVgUlCr3BimB1sA5YE0wFa4OTwTrgYrAuuAKsJ9J1HxX7NsQ+mZFgdZid4vzoTxniDX4F+oN/AUuC34DR4CnQAZ4G64FnwD7gd+A48Cy4BjwHfgmeB38AL4A3QdRJHu9LYBr4IzgEvAyuB/8KHgGvgLfAq6CJoU8Gw8BrYHPwOjgG/BVcB94Ad4E3wVPgLdCAgnYbrA7+DvYC74AjwD/A6eA98A2QSIgnSMEo1EcGVgRlsDOogNNAFdwDauBR0Bv8EjSAvqh/PmAsaASTQRM4HPQDN4H+4A7QDJ4BA8E/wCDQF/kRDFYFw8B2YDjYG4wAB4JWkY9Z+nMp8lAYH5gMUf4SRP1IAr3B1mA=
*/