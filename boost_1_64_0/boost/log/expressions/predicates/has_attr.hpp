/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   has_attr.hpp
 * \author Andrey Semashev
 * \date   23.07.2012
 *
 * The header contains implementation of a generic attribute presence checker in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_HAS_ATTR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_HAS_ATTR_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/utility/functional/nop.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * An attribute value presence checker.
 */
template< typename T >
class has_attribute
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef T value_type;

private:
    //! Attribute value name
    const attribute_name m_name;
    //! Visitor invoker
    value_visitor_invoker< value_type > m_visitor_invoker;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     */
    explicit has_attribute(attribute_name const& name) : m_name(name)
    {
    }

    /*!
     * Checking operator
     *
     * \param arg A set of attribute values or a log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        return m_visitor_invoker(m_name, arg, nop()).code() == visitation_result::ok;
    }
};

/*!
 * An attribute value presence checker. This specialization does not check the type of the attribute value.
 */
template< >
class has_attribute< void >
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef void value_type;

private:
    //! Attribute name
    const attribute_name m_name;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     */
    explicit has_attribute(attribute_name const& name) : m_name(name)
    {
    }

    /*!
     * Checking operator
     *
     * \param attrs A set of attribute values
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    result_type operator() (attribute_value_set const& attrs) const
    {
        return attrs.find(m_name) != attrs.end();
    }

    /*!
     * Checking operator
     *
     * \param rec A log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    result_type operator() (boost::log::record_view const& rec) const
    {
        return operator()(rec.attribute_values());
    }
};

/*!
 * The function generates a terminal node in a template expression. The node will check for the attribute value
 * presence in a log record. The node will also check that the attribute value has the specified type, if present.
 */
template< typename AttributeValueT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< has_attribute< AttributeValueT > > > has_attr(attribute_name const& name)
{
    typedef aux::unary_function_terminal< has_attribute< AttributeValueT > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check for the attribute value
 * presence in a log record.
 */
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< has_attribute< void > > > has_attr(attribute_name const& name)
{
    typedef aux::unary_function_terminal< has_attribute< void > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check for the attribute value
 * presence in a log record. The node will also check that the attribute value has the specified type, if present.
 */
template< typename DescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< has_attribute< typename DescriptorT::value_type > > > has_attr(attribute_keyword< DescriptorT, ActorT > const&)
{
    typedef aux::unary_function_terminal< has_attribute< typename DescriptorT::value_type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name()) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_HAS_ATTR_HPP_INCLUDED_

/* has_attr.hpp
7u1lJpNkTA/aE+LluA+6U3NbebHJPLxWmTd12QViP9SXRPvfBrLJuYmnpgkSMq2C5JL6X8O6U3ju9PaRzbj6UrEbKGPhwZIb0qU1aZTxkfRHtB0nNvLeg3xM0Ho4+E2p2kx/q9yE3U/Y/THL1l3C95bzotMkZr96knyzmb4Hw8CYiLLhyssr3nKhZeFVsJAPvKblYx20VspIfHOvbrngO1H1PWks5cKs+8YoK+mWspIRXlbqLRclPfT+l6BeKm3rM3abcoGKEV1Nj7O9x62tDbeVAXjjH7Nl7I6/vc/Y/f3X3f8dY5/h/R15/sIHssA3wA2DMTfprIPp6DQ25eSbPaJr0/RbTxO317EPKsmWD/htrSes+eDlPbGd1GUV8xeUmm8P+Ni172fLF9zGGrtr+ZZwN0lMYUVzJ6sw7UjujKA7UmSt/yhnc0I3Z0Zik3D9lzFko52W2X7/cO3/4aTSPo9Go9cvnJPsujDtciP1007qpw1if15iH61Xfi7vpyX66eGtdMZSt6Q4R/oGONf5Rjlv+QqcXycs1jrI59wucStLSHEe9D/vv8y2rmq+nyn5oPVTseSFmTc9V3g2Jkb0T8184hyxvzcx09iXT5u/kETW9MgGJwnPHb7TqeceJVcLfadoHmg4pYZ/zHnPyQvrs3QKrpUJz8KEsc5TzonE+Ze+i3zjEpoRbm9cn/e7cXXD+WggLgvmlDtmznamhOF+wql9GKmzzJha2oNQnV4xt0yyNJSnE8T9pQlHcIJrvvOSf2TCUaa+f1q+f0TCAGeN/yP/QDO//aa4ecaf5EzzX455cw3vJ59grnOyu/huhfDdnmjp25ux8RThWZx4An2tMl835+jEVs6kxI66Rs+MrYRhVEIr5yH/m/6mzlf+VpKv2YMDcZ03nWbFM/+1U/w7kLCHk2cP4urVhI5qF/RrdAK3MYhfn/iZ1zFtrNb/mi59hTc3oaXztdPO950vWC6vlHKZZ8nnNySfm3vTetY809dtI2WnGr6lvnaaju3F7F1fFrslPnTedF7xJUja7SHtyiQed4t8nhrI9/mzSkLt59NinyTfK0vEQO+EzNayfreWkxOdPc5sX4AvU+RP1nKMP7USn6bSz53Zg37b4TpXdgwTBimp/GvdPN65sioJU1fTpu+Q96aBfrH6n5vH+VUZ11fdFnmfXyflmRjk8VXtcCfhfX3rWDdTN5XG3yXHRvqbrTxrgzxJS9owy6JtVbRfm+F7PTCf/0HUGpzyHDBhXPK2hLF//WHscETQ3yX7YvlbeETQ36V9xN9j6ve3wvi7dHikvz2UZz88b7j5unR3Wq+kpumJzZNSE3qldU87nCxObWXmwa+lUJ7VmvGj4tlQSKYXuKXXyPQwkd9T6DUOUTNWYMTsXPo1A8Pi1atvMF7LPpZ4da8/XgV9g/FablmTV3ntGxjrJ7VKT1/y46SkhMy0HmmHy3RXk3Q3akt/bfZSnZYj/UWZR2pq2rjpRtfve1JmGI1a656B3rJNOoR0uv9Z+NrjzlbPDAyTwW792JucRZyaL388PSHTxCuvZXjcx/WDAnz3RfCYNK3tp3FvlrD8QjfaSYkkqqapia89rs9JXd3U7KF4SN7PcVrxFyueTwpPlvaH1A15nep0lHBdyHc7wPcnnQ/fofVFDY7/rL//Av4VehP6G/QWNEznbwpBeMw8+kjej4O88+pvqz+aj2Y/YYd6+v20TdrvHyDv9+6Jb97H07c3/VD6a5hJf+2Q9iYx1pD2OTTWCJ8vLEuMvOtXdQ0c6chzlEZyILSNsBd+GtG3NaNrbx93ARG0jiPUvc/DOx9e67whvNa+rq2/Cq+1r2sbR8Bb9/7KM8Q+29Y=
*/