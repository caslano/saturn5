//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_EXTRACT_FROM_SEP_30_2009_0732AM)
#define BOOST_SPIRIT_KARMA_EXTRACT_FROM_SEP_30_2009_0732AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/attributes_fwd.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/container.hpp>

#include <boost/ref.hpp>
#include <boost/optional.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    //  This file contains attribute extraction utilities. The utilities
    //  provided also accept spirit's unused_type; all no-ops. Compiler
    //  optimization will easily strip these away.
    ///////////////////////////////////////////////////////////////////////////

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        // extract first and second element of a fusion sequence
        template <typename T>
        struct add_const_ref
          : add_reference<typename add_const<T>::type>
        {};

        template <typename T, int N>
        struct value_at_c
          : add_const_ref<typename fusion::result_of::value_at_c<T, N>::type>
        {};
    }

    // This is the default case: the plain attribute values
    template <typename Attribute, typename Exposed
      , bool IsOneElemSeq = traits::one_element_sequence<Attribute>::value>
    struct extract_from_attribute_base
    {
        typedef Attribute const& type;

        template <typename Context>
        static type call(Attribute const& attr, Context&)
        {
            return attr;
        }
    };

    // This handles the case where the attribute is a single element fusion
    // sequence. We silently extract the only element and treat it as the
    // attribute to generate output from.
    template <typename Attribute, typename Exposed>
    struct extract_from_attribute_base<Attribute, Exposed, true>
    {
        typedef typename remove_const<
            typename remove_reference<
                typename fusion::result_of::at_c<Attribute, 0>::type
            >::type
        >::type elem_type;

        typedef typename result_of::extract_from<Exposed, elem_type>::type type;

        template <typename Context>
        static type call(Attribute const& attr, Context& ctx)
        {
            return extract_from<Exposed>(fusion::at_c<0>(attr), ctx);
        }
    };

    template <typename Attribute, typename Exposed, typename Enable/*= void*/>
    struct extract_from_attribute
      : extract_from_attribute_base<Attribute, Exposed>
    {};

    // This handles optional attributes.
    template <typename Attribute, typename Exposed>
    struct extract_from_attribute<boost::optional<Attribute>, Exposed>
    {
        typedef Attribute const& type;

        template <typename Context>
        static type call(boost::optional<Attribute> const& attr, Context& ctx)
        {
            return extract_from<Exposed>(boost::get<Attribute>(attr), ctx);
        }
    };

    template <typename Attribute, typename Exposed>
    struct extract_from_attribute<boost::optional<Attribute const>, Exposed>
    {
        typedef Attribute const& type;

        template <typename Context>
        static type call(boost::optional<Attribute const> const& attr, Context& ctx)
        {
            return extract_from<Exposed>(boost::get<Attribute const>(attr), ctx);
        }
    };

    // This handles attributes wrapped inside a boost::ref().
    template <typename Attribute, typename Exposed>
    struct extract_from_attribute<reference_wrapper<Attribute>, Exposed>
    {
        typedef Attribute const& type;

        template <typename Context>
        static type call(reference_wrapper<Attribute> const& attr, Context& ctx)
        {
            return extract_from<Exposed>(attr.get(), ctx);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename Exposed, typename Enable>
    struct extract_from_container
    {
        typedef typename traits::container_value<Attribute const>::type
            value_type;
        typedef typename is_convertible<value_type, Exposed>::type
            is_convertible_to_value_type;

        typedef typename mpl::if_<
           mpl::or_<
                is_same<value_type, Exposed>, is_same<Attribute, Exposed> >
          , Exposed const&, Exposed
        >::type type;

        // handle case where container value type is convertible to result type
        // we simply return the front element of the container
        template <typename Context, typename Pred>
        static type call(Attribute const& attr, Context&, mpl::true_, Pred)
        {
            // return first element from container
            typedef typename traits::container_iterator<Attribute const>::type
                iterator_type;

            iterator_type it = traits::begin(attr);
            type result = *it;
            ++it;
            return result;
        }

        // handle strings
        template <typename Iterator>
        static void append_to_string(Exposed& result, Iterator begin, Iterator end)
        {
            for (Iterator i = begin; i != end; ++i)
                push_back(result, *i);
        }

        template <typename Context>
        static type call(Attribute const& attr, Context&, mpl::false_, mpl::true_)
        {
            typedef typename char_type_of<Attribute>::type char_type;

            Exposed result;
            append_to_string(result, traits::get_begin<char_type>(attr)
              , traits::get_end<char_type>(attr));
            return result;
        }

        // everything else gets just passed through
        template <typename Context>
        static type call(Attribute const& attr, Context&, mpl::false_, mpl::false_)
        {
            return type(attr);
        }

        template <typename Context>
        static type call(Attribute const& attr, Context& ctx)
        {
            typedef typename mpl::and_<
                traits::is_string<Exposed>, traits::is_string<Attribute>
            >::type handle_strings;

            // return first element from container
            return call(attr, ctx, is_convertible_to_value_type()
              , handle_strings());
        }
    };

    template <typename Attribute>
    struct extract_from_container<Attribute, Attribute>
    {
        typedef Attribute const& type;

        template <typename Context>
        static type call(Attribute const& attr, Context&)
        {
            return attr;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        // overload for non-container attributes
        template <typename Exposed, typename Attribute, typename Context>
        inline typename spirit::result_of::extract_from<Exposed, Attribute>::type
        extract_from(Attribute const& attr, Context& ctx, mpl::false_)
        {
            return extract_from_attribute<Attribute, Exposed>::call(attr, ctx);
        }

        // overload for containers (but not for variants or optionals
        // holding containers)
        template <typename Exposed, typename Attribute, typename Context>
        inline typename spirit::result_of::extract_from<Exposed, Attribute>::type
        extract_from(Attribute const& attr, Context& ctx, mpl::true_)
        {
            return extract_from_container<Attribute, Exposed>::call(attr, ctx);
        }
    }

    template <typename Exposed, typename Attribute, typename Context>
    inline typename spirit::result_of::extract_from<Exposed, Attribute>::type
    extract_from(Attribute const& attr, Context& ctx
#if (defined(__GNUC__) && (__GNUC__ < 4)) || \
    (defined(__APPLE__) && defined(__INTEL_COMPILER))
      , typename enable_if<traits::not_is_unused<Attribute> >::type*
#endif
    )
    {
        typedef typename mpl::and_<
            traits::is_container<Attribute>
          , traits::not_is_variant<Attribute>
          , traits::not_is_optional<Attribute>
        >::type is_not_wrapped_container;

        return detail::extract_from<Exposed>(attr, ctx
          , is_not_wrapped_container());
    }

    template <typename Exposed, typename Context>
    inline unused_type extract_from(unused_type, Context&)
    {
        return unused;
    }
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace result_of
{
    template <typename Exposed, typename Attribute>
    struct extract_from
      : mpl::if_<
            mpl::and_<
                traits::is_container<Attribute>
              , traits::not_is_variant<Attribute>
              , traits::not_is_optional<Attribute> >
          , traits::extract_from_container<Attribute, Exposed>
          , traits::extract_from_attribute<Attribute, Exposed> >::type
    {};

    template <typename Exposed>
    struct extract_from<Exposed, unused_type>
    {
        typedef unused_type type;
    };

    template <typename Exposed>
    struct extract_from<Exposed, unused_type const>
    {
        typedef unused_type type;
    };
}}}

#endif

/* extract_from.hpp
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
*/