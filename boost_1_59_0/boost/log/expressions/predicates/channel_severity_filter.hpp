/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   channel_severity_filter.hpp
 * \author Andrey Semashev
 * \date   25.11.2012
 *
 * The header contains implementation of a minimal severity per channel filter.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_CHANNEL_SEVERITY_FILTER_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_CHANNEL_SEVERITY_FILTER_HPP_INCLUDED_

#include <map>
#include <memory>
#include <utility>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/allocator_traits.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/utility/use_std_allocator.hpp>
#include <boost/log/utility/functional/logical.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

template<
    typename ChannelT,
    typename SeverityT,
    typename ChannelFallbackT = fallback_to_none,
    typename SeverityFallbackT = fallback_to_none,
    typename ChannelOrderT = less,
    typename SeverityCompareT = greater_equal,
    typename AllocatorT = use_std_allocator
>
class channel_severity_filter_terminal
{
public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;
#endif

    //! Function result type
    typedef bool result_type;

    //! Channel attribute value type
    typedef ChannelT channel_value_type;
    //! Channel fallback policy
    typedef ChannelFallbackT channel_fallback_policy;
    //! Severity level attribute value type
    typedef SeverityT severity_value_type;
    //! Severity level fallback policy
    typedef SeverityFallbackT severity_fallback_policy;

private:
    //! Channel to severity mapping type
    typedef std::map<
        channel_value_type,
        severity_value_type,
        ChannelOrderT,
        typename boost::log::aux::rebind_alloc< AllocatorT, std::pair< const channel_value_type, severity_value_type > >::type
    > mapping_type;
    //! Attribute value visitor invoker for channel
    typedef value_visitor_invoker< channel_value_type, channel_fallback_policy > channel_visitor_invoker_type;
    //! Attribute value visitor invoker for severity level
    typedef value_visitor_invoker< severity_value_type, severity_fallback_policy > severity_visitor_invoker_type;

    //! Channel visitor
    template< typename ArgT >
    struct channel_visitor
    {
        typedef void result_type;

        channel_visitor(channel_severity_filter_terminal const& self, ArgT arg, bool& res) : m_self(self), m_arg(arg), m_res(res)
        {
        }

        result_type operator() (channel_value_type const& channel) const
        {
            m_self.visit_channel(channel, m_arg, m_res);
        }

    private:
        channel_severity_filter_terminal const& m_self;
        ArgT m_arg;
        bool& m_res;
    };

    //! Severity level visitor
    struct severity_visitor
    {
        typedef void result_type;

        severity_visitor(channel_severity_filter_terminal const& self, severity_value_type const& severity, bool& res) : m_self(self), m_severity(severity), m_res(res)
        {
        }

        result_type operator() (severity_value_type const& severity) const
        {
            m_self.visit_severity(severity, m_severity, m_res);
        }

    private:
        channel_severity_filter_terminal const& m_self;
        severity_value_type const& m_severity;
        bool& m_res;
    };

private:
    //! Channel attribute name
    attribute_name m_channel_name;
    //! Severity level attribute name
    attribute_name m_severity_name;
    //! Channel value visitor invoker
    channel_visitor_invoker_type m_channel_visitor_invoker;
    //! Severity level value visitor invoker
    severity_visitor_invoker_type m_severity_visitor_invoker;

    //! Channel to severity level mapping
    mapping_type m_mapping;
    //! Severity checking predicate
    SeverityCompareT m_severity_compare;

    //! Default result
    bool m_default;

public:
    //! Initializing constructor
    channel_severity_filter_terminal
    (
        attribute_name const& channel_name,
        attribute_name const& severity_name,
        channel_fallback_policy const& channel_fallback = channel_fallback_policy(),
        severity_fallback_policy const& severity_fallback = severity_fallback_policy(),
        ChannelOrderT const& channel_order = ChannelOrderT(),
        SeverityCompareT const& severity_compare = SeverityCompareT()
    ) :
        m_channel_name(channel_name),
        m_severity_name(severity_name),
        m_channel_visitor_invoker(channel_fallback),
        m_severity_visitor_invoker(severity_fallback),
        m_mapping(channel_order),
        m_severity_compare(severity_compare),
        m_default(false)
    {
    }

    //! Adds a new element to the mapping
    void add(channel_value_type const& channel, severity_value_type const& severity)
    {
        typedef typename mapping_type::iterator iterator;
        std::pair< iterator, bool > res = m_mapping.insert(typename mapping_type::value_type(channel, severity));
        if (!res.second)
            res.first->second = severity;
    }

    //! Sets the default result of the predicate
    void set_default(bool def)
    {
        m_default = def;
    }

    //! Invokation operator
    template< typename ContextT >
    result_type operator() (ContextT const& ctx) const
    {
        result_type res = m_default;

        typedef typename remove_cv<
            typename remove_reference< typename phoenix::result_of::env< ContextT >::type >::type
        >::type env_type;
        typedef typename env_type::args_type args_type;
        typedef typename fusion::result_of::at_c< args_type, 0 >::type arg_type;
        arg_type arg = fusion::at_c< 0 >(phoenix::env(ctx).args());

        m_channel_visitor_invoker(m_channel_name, arg, channel_visitor< arg_type >(*this, arg, res));

        return res;
    }

private:
    //! Visits channel name
    template< typename ArgT >
    void visit_channel(channel_value_type const& channel, ArgT const& arg, bool& res) const
    {
        typename mapping_type::const_iterator it = m_mapping.find(channel);
        if (it != m_mapping.end())
        {
            m_severity_visitor_invoker(m_severity_name, arg, severity_visitor(*this, it->second, res));
        }
    }

    //! Visits severity level
    void visit_severity(severity_value_type const& left, severity_value_type const& right, bool& res) const
    {
        res = m_severity_compare(left, right);
    }
};

template<
    typename ChannelT,
    typename SeverityT,
    typename ChannelFallbackT = fallback_to_none,
    typename SeverityFallbackT = fallback_to_none,
    typename ChannelOrderT = less,
    typename SeverityCompareT = greater_equal,
    typename AllocatorT = use_std_allocator,
    template< typename > class ActorT = phoenix::actor
>
class channel_severity_filter_actor :
    public ActorT< channel_severity_filter_terminal< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, AllocatorT > >
{
private:
    //! Self type
    typedef channel_severity_filter_actor this_type;

public:
    //! Terminal type
    typedef channel_severity_filter_terminal< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, AllocatorT > terminal_type;
    //! Base actor type
    typedef ActorT< terminal_type > base_type;

    //! Channel attribute value type
    typedef typename terminal_type::channel_value_type channel_value_type;
    //! Channel fallback policy
    typedef typename terminal_type::channel_fallback_policy channel_fallback_policy;
    //! Severity level attribute value type
    typedef typename terminal_type::severity_value_type severity_value_type;
    //! Severity level fallback policy
    typedef typename terminal_type::severity_fallback_policy severity_fallback_policy;

private:
    //! An auxiliary pseudo-reference to implement insertion through subscript operator
    class subscript_result
    {
    private:
        channel_severity_filter_actor& m_owner;
        channel_value_type const& m_channel;

    public:
        subscript_result(channel_severity_filter_actor& owner, channel_value_type const& channel) : m_owner(owner), m_channel(channel)
        {
        }

        void operator= (severity_value_type const& severity)
        {
            m_owner.add(m_channel, severity);
        }
    };

public:
    //! Initializing constructor
    explicit channel_severity_filter_actor(base_type const& act) : base_type(act)
    {
    }
    //! Copy constructor
    channel_severity_filter_actor(channel_severity_filter_actor const& that) : base_type(static_cast< base_type const& >(that))
    {
    }

    //! Sets the default function result
    this_type& set_default(bool def)
    {
        this->proto_expr_.child0.set_default(def);
        return *this;
    }

    //! Adds a new element to the mapping
    this_type& add(channel_value_type const& channel, severity_value_type const& severity)
    {
        this->proto_expr_.child0.add(channel, severity);
        return *this;
    }

    //! Alternative interface for adding a new element to the mapping
    subscript_result operator[] (channel_value_type const& channel)
    {
        return subscript_result(*this, channel);
    }
};

/*!
 * The function generates a filtering predicate that checks the severity levels of log records in different channels. The predicate will return \c true
 * if the record severity level is not less than the threshold for the channel the record belongs to.
 */
template< typename ChannelT, typename SeverityT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT >
channel_severity_filter(attribute_name const& channel_name, attribute_name const& severity_name)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_name) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelDescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, greater_equal, use_std_allocator, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_name const& severity_name)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, greater_equal, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_name) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityDescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, use_std_allocator, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword)
{
    typedef channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_keyword.get_name()) }};
    return result_type(act);
}

//! \overload
template< typename ChannelDescriptorT, typename SeverityDescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, use_std_allocator, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_keyword.get_name()) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, greater_equal, use_std_allocator, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_name const& severity_name)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, greater_equal, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_name, channel_placeholder.get_fallback_policy()) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, greater_equal, use_std_allocator, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, greater_equal, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_placeholder.get_name(), fallback_to_none(), severity_placeholder.get_fallback_policy()) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, greater_equal, use_std_allocator, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, greater_equal, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_placeholder.get_name(), channel_placeholder.get_fallback_policy(), severity_placeholder.get_fallback_policy()) }};
    return result_type(act);
}


//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, fallback_to_none, less, SeverityCompareT >
channel_severity_filter(attribute_name const& channel_name, attribute_name const& severity_name, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, fallback_to_none, less, SeverityCompareT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_name, fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelDescriptorT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_name const& severity_name, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_name, fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelDescriptorT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_name const& severity_name, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_name, channel_placeholder.get_fallback_policy(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_placeholder.get_name(), fallback_to_none(), severity_placeholder.get_fallback_policy(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_placeholder.get_name(), channel_placeholder.get_fallback_policy(), severity_placeholder.get_fallback_policy(), less(), severity_compare) }};
    return result_type(act);
}


//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT >
channel_severity_filter(attribute_name const& channel_name, attribute_name const& severity_name, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_name, fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelDescriptorT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_name const& severity_name, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_name, fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelDescriptorT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_name const& severity_name, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_name, channel_placeholder.get_fallback_policy(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_placeholder.get_name(), fallback_to_none(), severity_placeholder.get_fallback_policy(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, use_std_allocator, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_placeholder.get_name(), channel_placeholder.get_fallback_policy(), severity_placeholder.get_fallback_policy(), channel_order, severity_compare) }};
    return result_type(act);
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template<
    typename ChannelT,
    typename SeverityT,
    typename ChannelFallbackT,
    typename SeverityFallbackT,
    typename ChannelOrderT,
    typename SeverityCompareT,
    typename AllocatorT
>
struct is_nullary< custom_terminal< boost::log::expressions::channel_severity_filter_terminal< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, AllocatorT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_CHANNEL_SEVERITY_FILTER_HPP_INCLUDED_

/* channel_severity_filter.hpp
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
*/