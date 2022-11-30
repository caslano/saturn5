//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DETAIL_ATTRIBUTES_HPP
#define BOOST_SPIRIT_KARMA_DETAIL_ATTRIBUTES_HPP

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/support/attributes_fwd.hpp>
#include <boost/spirit/home/support/attributes.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    template <typename Exposed, typename Transformed, typename Enable = void>
    struct transform_attribute
    {
        typedef Transformed type;
        static Transformed pre(Exposed& val) 
        { 
            return Transformed(traits::extract_from<Transformed>(val, unused));
        }
        // Karma only, no post() and no fail() required
    };

    template <typename Exposed, typename Transformed>
    struct transform_attribute<boost::optional<Exposed> const, Transformed
      , typename disable_if<is_same<boost::optional<Exposed>, Transformed> >::type>
    {
        typedef Transformed const& type;
        static Transformed const& pre(boost::optional<Exposed> const& val)
        {
            return boost::get<Transformed>(val);
        }
    };

    template <typename Attribute>
    struct transform_attribute<Attribute const, Attribute>
    {
        typedef Attribute const& type;
        static Attribute const& pre(Attribute const& val) { return val; }
        // Karma only, no post() and no fail() required
    };

    // unused_type needs some special handling as well
    template <>
    struct transform_attribute<unused_type, unused_type>
    {
        typedef unused_type type;
        static unused_type pre(unused_type) { return unused; }
    };

    template <>
    struct transform_attribute<unused_type const, unused_type>
      : transform_attribute<unused_type, unused_type>
    {};

    template <typename Attribute>
    struct transform_attribute<Attribute, unused_type>
      : transform_attribute<unused_type, unused_type>
    {};

    template <typename Attribute>
    struct transform_attribute<Attribute const, unused_type>
      : transform_attribute<unused_type, unused_type>
    {};
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits { namespace detail
{
    template <typename Exposed, typename Transformed>
    struct transform_attribute_base<Exposed, Transformed, karma::domain>
      : karma::transform_attribute<Exposed, Transformed>
    {};
}}}}

#endif

/* attributes.hpp
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
*/