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
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
*/