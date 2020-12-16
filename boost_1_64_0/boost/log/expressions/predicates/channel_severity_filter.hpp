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
    typename AllocatorT = std::allocator< void >
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
    typename AllocatorT = std::allocator< void >,
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
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_name const& severity_name)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_name) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityDescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword)
{
    typedef channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_keyword.get_name()) }};
    return result_type(act);
}

//! \overload
template< typename ChannelDescriptorT, typename SeverityDescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_keyword.get_name()) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_name const& severity_name)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, greater_equal, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_name, channel_placeholder.get_fallback_policy()) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, greater_equal, std::allocator< void >, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, greater_equal, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_placeholder.get_name(), fallback_to_none(), severity_placeholder.get_fallback_policy()) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, greater_equal, std::allocator< void >, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, greater_equal, std::allocator< void >, ActorT > result_type;
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
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_name const& severity_name, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_name, fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelDescriptorT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_name const& severity_name, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, less, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_name, channel_placeholder.get_fallback_policy(), fallback_to_none(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, less, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_placeholder.get_name(), fallback_to_none(), severity_placeholder.get_fallback_policy(), less(), severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, less, SeverityCompareT, std::allocator< void >, ActorT > result_type;
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
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_name const& severity_name, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, SeverityT, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_name, fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelDescriptorT, typename SeverityDescriptorT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_keyword< ChannelDescriptorT, ActorT > const& channel_keyword, attribute_keyword< SeverityDescriptorT, ActorT > const& severity_keyword, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< typename ChannelDescriptorT::value_type, typename SeverityDescriptorT::value_type, fallback_to_none, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_keyword.get_name(), severity_keyword.get_name(), fallback_to_none(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename SeverityT, typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_name const& severity_name, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, fallback_to_none, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_placeholder.get_name(), severity_name, channel_placeholder.get_fallback_policy(), fallback_to_none(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_name const& channel_name, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, fallback_to_none, SeverityFallbackT, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT > result_type;
    typedef typename result_type::terminal_type terminal_type;
    typename result_type::base_type act = {{ terminal_type(channel_name, severity_placeholder.get_name(), fallback_to_none(), severity_placeholder.get_fallback_policy(), channel_order, severity_compare) }};
    return result_type(act);
}

//! \overload
template< typename ChannelT, typename ChannelFallbackT, typename ChannelTagT, typename SeverityT, typename SeverityFallbackT, typename SeverityTagT, template< typename > class ActorT, typename SeverityCompareT, typename ChannelOrderT >
BOOST_FORCEINLINE channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT >
channel_severity_filter(attribute_actor< ChannelT, ChannelFallbackT, ChannelTagT, ActorT > const& channel_placeholder, attribute_actor< SeverityT, SeverityFallbackT, SeverityTagT, ActorT > const& severity_placeholder, SeverityCompareT const& severity_compare, ChannelOrderT const& channel_order)
{
    typedef channel_severity_filter_actor< ChannelT, SeverityT, ChannelFallbackT, SeverityFallbackT, ChannelOrderT, SeverityCompareT, std::allocator< void >, ActorT > result_type;
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
GA+uB2eDD2m5eRhcCm7Qeu4RMDfOs33/y2f54j3HZznDJ+f39oNyhu8HPL9X39m9IZ+lfu/ze96ze4X4UwZVQ+ugHdABKGd/qjMEKoIqoTXQJmgvlPU5dlARVAXdA22HDkC5X6AfCyqBVkB3ftF4nq/xaXwan8an8fn/fv7t+//nlsm/4jmzzvuh9v9f5dn/v9gXfXfXhkH0jb+UudZRp55cWDxqYpFMtwbXPNYH1mYrKj3znQuFv5tlnlX94u/73Mnlfqu1+dbRLZeJX/QzB4Xvmeug5xiS1ZMkaDM86yLiMaPU3FYocXk6FBdb2HHfsLuTnjbhDQ/fRn/4PGsL6I/wbooOn1y4iLU3fGRfDL3a3y98+Ke6rDV8dybovInKwVhoC7y1EeFjqU3CtW6QuZ/OrD18K7wx9pMFwqnyE31f3adif5ST4tlHdXsD76sjTGH31aUcCMjKwxGysqaJ6j2CgjqWnoNn+IFQXN0UWlBaXl583pz502ZHyb0J9xjXDanYzLpvVP3UeOcm1q2r38sLj8uLglbLfhyLv3qnkUXfss3fWa6/Zi2jSOw7idssj9ssi1vNN5PnM8U+o969bpbybNaBCD9mpIvZC6RrZBp/1dcKX/g9FFmGT+NDnk/XPN8YkefVyfY8r/bkeWll2dR5JcEcj53n19eT59UNyPPqBuR5dQPyvLqePL+zjjyvrifPN/yP5flD4Xlu2rY8DRBg2oYX4KkN5bnUt7ITXfN706A6793EbcPq202mTgoP29aU6PZqG7x7I8JGWxB32PYeYtj2u+XD1/B1PPs6Uqz1vYavL114jw/zc5Z0a7Zp8LaKu24sLS+5+kYmpd9Kd/l/N/nioj1JP/vtj+9sVbvt9ms2x14fs6/j/XD6g1V3n/Z3iKdFd18/nXfLB1PBI8FMcCCYAw4Ce4ODzXyz9kHAZMt8c67OA3YGk8Au6m646RtofQARbKOXeLK6OxNMB88Cm+l7C3kPrTfUqj/HW9YbMjU+rcG2YEewHdgGzAVzwP5gW3AE2A4cBXYAxyq/fkfbGmTQ8p1j9TvHgc3BYaDo9QelnQIPB0eA/cCR4ABwFHiU8hkdwXV850T9zsn6nVP0O5P0O4X6ndP0O+P1OxP0O5NMvmldAaZY8q2Ppv/hYDKYF3JHOY6d393VXQ/N755gPsyrTmYOEtoKBedVy6AhpzDHB62GNkA7oHGnBuZUy8BqyJ1HrQWD86i7XCwMzJPmnxaYJy0EV0FZOj+6i9+5XzKnNz58TjRxAvOSUCFUDS0Pm+uEJjIPDI0+HX5oBTQQf+4Et0IHoaGTAnOem0Cd8xTljjnQQKiE9x1gShFzpJB3brMIGjcZcsMGrXD9hjZDu6CUA6lOtwON84+Nzw/z/MfG/5wa+iHG/+79/S8Ooq/U2q1XpJvh3k8zfeG8ae4hebE/nUX2neH2Cwjb/HkwuPMHKzs75tztHJ0/GBDU9QrdlkU9Fhg3jhk/PnCHa9AnAiNn8YPn3FPxZUkGFMedZME+SoovVlse+86Cu6UP4c8784kX1sxufeCK78b26946MXZfwb53KFZfoeF9Jnvf6Pv3OSS9NR/yvX0ObSOCbU6mtjkdtc2BpE/SH8wHV4Kbv0p1dkLe9bkqXYcrGRreTqzUdTRtF8LbAtFfGdkGRK9nlciaVXQ9nvh1Yz3d+DQ+jU/j0/g0Po1P49P4ND6Nz//Okwid/+8e/xdfrKv/hzb278LY/glX74WM7V0/dSm8eN58940oyPj+Z50dsy6cp+P7JM/5u5fwI8OzLhxwG9/4PThvUK3+AubZjuvcgL8y5SEhnEayzFtY5l4DH+83Avc4NnxM3tB1DPt5pIY=
*/