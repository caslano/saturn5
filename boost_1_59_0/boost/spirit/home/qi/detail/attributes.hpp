//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_QI_DETAIL_ATTRIBUTES_HPP
#define BOOST_SPIRIT_QI_DETAIL_ATTRIBUTES_HPP

#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/support/attributes_fwd.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/home/support/utree/utree_traits_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace qi
{
    template <typename Exposed, typename Transformed>
    struct default_transform_attribute
    {
        typedef Transformed type;

        static Transformed pre(Exposed&) { return Transformed(); }

        static void post(Exposed& val, Transformed const& attr)
        {
            traits::assign_to(attr, val);
        }

        // fail() will be called by Qi rule's if the rhs failed parsing
        static void fail(Exposed&) {}
    };

    // handle case where no transformation is required as the types are the same
    template <typename Attribute>
    struct default_transform_attribute<Attribute, Attribute>
    {
        typedef Attribute& type;
        static Attribute& pre(Attribute& val) { return val; }
        static void post(Attribute&, Attribute const&) {}
        static void fail(Attribute&) {}
    };

    template <typename Exposed, typename Transformed>
    struct proxy_transform_attribute
    {
        typedef Transformed type;

        static Transformed pre(Exposed& val) { return Transformed(val); }
        static void post(Exposed&, Transformed const&) { /* no-op */ }

        // fail() will be called by Qi rule's if the rhs failed parsing
        static void fail(Exposed&) {}
    };

    // handle case where no transformation is required as the types are the same
    template <typename Attribute>
    struct proxy_transform_attribute<Attribute, Attribute>
    {
        typedef Attribute& type;
        static Attribute& pre(Attribute& val) { return val; }
        static void post(Attribute&, Attribute const&) {}
        static void fail(Attribute&) {}
    };

    // main specialization for Qi
    template <typename Exposed, typename Transformed, typename Enable = void>
    struct transform_attribute
      : mpl::if_<
            mpl::and_<
                mpl::not_<is_const<Exposed> >
              , mpl::not_<is_reference<Exposed> >
              , traits::is_proxy<Transformed> >
          , proxy_transform_attribute<Exposed, Transformed>
          , default_transform_attribute<Exposed, Transformed> 
        >::type 
    {};

    template <typename Exposed, typename Transformed>
    struct transform_attribute<boost::optional<Exposed>, Transformed
      , typename disable_if<is_same<boost::optional<Exposed>, Transformed> >::type>
    {
        typedef Transformed& type;
        static Transformed& pre(boost::optional<Exposed>& val)
        {
            if (!val)
                val = Transformed();
            return boost::get<Transformed>(val);
        }
        static void post(boost::optional<Exposed>&, Transformed const&) {}
        static void fail(boost::optional<Exposed>& val)
        {
             val = none;    // leave optional uninitialized if rhs failed
        }
    };

    // unused_type needs some special handling as well
    template <>
    struct transform_attribute<unused_type, unused_type>
    {
        typedef unused_type type;
        static unused_type pre(unused_type) { return unused; }
        static void post(unused_type, unused_type) {}
        static void fail(unused_type) {}
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
namespace boost { namespace spirit { namespace traits
{
    namespace detail {
        template <typename Exposed, typename Transformed>
        struct transform_attribute_base<Exposed, Transformed, qi::domain>
          : qi::transform_attribute<Exposed, Transformed>
        {};
    }
}}}

#endif

/* attributes.hpp
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
*/