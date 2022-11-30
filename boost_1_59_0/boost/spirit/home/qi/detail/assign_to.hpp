/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ASSIGN_TO_APR_16_2006_0812PM)
#define BOOST_SPIRIT_ASSIGN_TO_APR_16_2006_0812PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/detail/construct.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/fusion/include/copy.hpp>
#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/ref.hpp>
#include <boost/range/range_fwd.hpp>

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    //  This file contains assignment utilities. The utilities provided also
    //  accept spirit's unused_type; all no-ops. Compiler optimization will
    //  easily strip these away.
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T>
        struct is_iter_range : mpl::false_ {};

        template <typename I>
        struct is_iter_range<boost::iterator_range<I> > : mpl::true_ {};

        template <typename C>
        struct is_container_of_ranges
          : is_iter_range<typename C::value_type> {};
    }

    template <typename Attribute, typename Iterator, typename Enable>
    struct assign_to_attribute_from_iterators
    {
        // Common case
        static void
        call(Iterator const& first, Iterator const& last, Attribute& attr, mpl::false_)
        {
            if (traits::is_empty(attr))
                attr = Attribute(first, last);
            else {
                for (Iterator i = first; i != last; ++i)
                    push_back(attr, *i);
            }
        }

        // If Attribute is a container with value_type==iterator_range<T> just push the
        // iterator_range into it
        static void
        call(Iterator const& first, Iterator const& last, Attribute& attr, mpl::true_)
        {
            typename Attribute::value_type rng(first, last);
            push_back(attr, rng);
        }

        static void
        call(Iterator const& first, Iterator const& last, Attribute& attr)
        {
            call(first, last, attr, detail::is_container_of_ranges<Attribute>());
        }
    };

    template <typename Attribute, typename Iterator>
    struct assign_to_attribute_from_iterators<
        reference_wrapper<Attribute>, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last
          , reference_wrapper<Attribute> attr)
        {
            if (traits::is_empty(attr))
                attr = Attribute(first, last);
            else {
                for (Iterator i = first; i != last; ++i)
                    push_back(attr, *i);
            }
        }
    };

    template <typename Attribute, typename Iterator>
    struct assign_to_attribute_from_iterators<
        boost::optional<Attribute>, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last
          , boost::optional<Attribute>& attr)
        {
            Attribute val;
            assign_to(first, last, val);
            attr = val;
        }
    };

    template <typename Iterator>
    struct assign_to_attribute_from_iterators<
        iterator_range<Iterator>, Iterator>
    {
        static void
        call(Iterator const& first, Iterator const& last
          , iterator_range<Iterator>& attr)
        {
            attr = iterator_range<Iterator>(first, last);
        }
    };

    template <typename Iterator, typename Attribute>
    inline void
    assign_to(Iterator const& first, Iterator const& last, Attribute& attr)
    {
        assign_to_attribute_from_iterators<Attribute, Iterator>::
            call(first, last, attr);
    }

    template <typename Iterator>
    inline void
    assign_to(Iterator const&, Iterator const&, unused_type)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Attribute>
    void assign_to(T const& val, Attribute& attr);

    template <typename Attribute, typename T, typename Enable>
    struct assign_to_attribute_from_value
    {
        typedef typename traits::one_element_sequence<Attribute>::type
            is_one_element_sequence;

        typedef typename mpl::eval_if<
            is_one_element_sequence
          , fusion::result_of::at_c<Attribute, 0>
          , mpl::identity<Attribute&>
        >::type type;

        template <typename T_>
        static void
        call(T_ const& val, Attribute& attr, mpl::false_)
        {
            attr = static_cast<Attribute>(val);
        }

        // This handles the case where the attribute is a single element fusion
        // sequence. We silently assign to the only element and treat it as the
        // attribute to parse the results into.
        template <typename T_>
        static void
        call(T_ const& val, Attribute& attr, mpl::true_)
        {
            typedef typename fusion::result_of::value_at_c<Attribute, 0>::type
                element_type;
            fusion::at_c<0>(attr) = static_cast<element_type>(val);
        }

        static void
        call(T const& val, Attribute& attr)
        {
            call(val, attr, is_one_element_sequence());
        }
    };

    template <typename Attribute>
    struct assign_to_attribute_from_value<Attribute, Attribute>
    {
        static void
        call(Attribute const& val, Attribute& attr)
        {
            attr = val;
        }
    };

    template <typename Attribute, typename T>
    struct assign_to_attribute_from_value<Attribute, reference_wrapper<T>
      , typename disable_if<is_same<Attribute, reference_wrapper<T> > >::type>
    {
        static void
        call(reference_wrapper<T> const& val, Attribute& attr)
        {
            assign_to(val.get(), attr);
        }
    };

    template <typename Attribute, typename T>
    struct assign_to_attribute_from_value<Attribute, boost::optional<T>
      , typename disable_if<is_same<Attribute, boost::optional<T> > >::type>
    {
        static void
        call(boost::optional<T> const& val, Attribute& attr)
        {
            assign_to(val.get(), attr);
        }
    };

    template <typename Attribute, int N, bool Const, typename T>
    struct assign_to_attribute_from_value<fusion::extension::adt_attribute_proxy<Attribute, N, Const>, T>
    {
        static void
        call(T const& val, typename fusion::extension::adt_attribute_proxy<Attribute, N, Const>& attr)
        {
            attr = val;
        }
    };

    namespace detail
    {
        template <typename A, typename B>
        struct is_same_size_sequence
          : mpl::bool_<fusion::result_of::size<A>::value
                == fusion::result_of::size<B>::value>
        {};
    }

    template <typename Attribute, typename T>
    struct assign_to_attribute_from_value<Attribute, T,
            mpl::and_<
                fusion::traits::is_sequence<Attribute>,
                fusion::traits::is_sequence<T>,
                detail::is_same_size_sequence<Attribute, T>
            >
        >
    {
        static void
        call(T const& val, Attribute& attr)
        {
            fusion::copy(val, attr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Attribute, typename T, typename Enable>
    struct assign_to_container_from_value
    {
        // T is not a container and not a string
        template <typename T_>
        static void call(T_ const& val, Attribute& attr, mpl::false_, mpl::false_)
        {
            traits::push_back(attr, val);
        }

        // T is a container (but not a string), and T is convertible to the 
        // value_type of the Attribute container
        template <typename T_>
        static void 
        append_to_container_not_string(T_ const& val, Attribute& attr, mpl::true_)
        {
            traits::push_back(attr, val);
        }

        // T is a container (but not a string), generic overload
        template <typename T_>
        static void 
        append_to_container_not_string(T_ const& val, Attribute& attr, mpl::false_)
        {
            typedef typename traits::container_iterator<T_ const>::type
                iterator_type;

            iterator_type end = traits::end(val);
            for (iterator_type i = traits::begin(val); i != end; traits::next(i))
                traits::push_back(attr, traits::deref(i));
        }

        // T is a container (but not a string)
        template <typename T_>
        static void call(T_ const& val, Attribute& attr,  mpl::true_, mpl::false_)
        {
            typedef typename container_value<Attribute>::type value_type;
            typedef typename is_convertible<T, value_type>::type is_value_type;

            append_to_container_not_string(val, attr, is_value_type());
        }

        ///////////////////////////////////////////////////////////////////////
        // T is a string
        template <typename Iterator>
        static void append_to_string(Attribute& attr, Iterator begin, Iterator end)
        {
            for (Iterator i = begin; i != end; ++i)
                traits::push_back(attr, *i);
        }

        // T is string, but not convertible to value_type of container
        template <typename T_>
        static void append_to_container(T_ const& val, Attribute& attr, mpl::false_)
        {
            typedef typename char_type_of<T_>::type char_type;

            append_to_string(attr, traits::get_begin<char_type>(val)
              , traits::get_end<char_type>(val));
        }

        // T is string, and convertible to value_type of container
        template <typename T_>
        static void append_to_container(T_ const& val, Attribute& attr, mpl::true_)
        {
            traits::push_back(attr, val);
        }

        template <typename T_, typename Pred>
        static void call(T_ const& val, Attribute& attr, Pred, mpl::true_)
        {
            typedef typename container_value<Attribute>::type value_type;
            typedef typename is_convertible<T, value_type>::type is_value_type;

            append_to_container(val, attr, is_value_type());
        }

        ///////////////////////////////////////////////////////////////////////
        static void call(T const& val, Attribute& attr)
        {
            typedef typename traits::is_container<T>::type is_container;
            typedef typename traits::is_string<T>::type is_string;

            call(val, attr, is_container(), is_string());
        }
    };

    template <typename Attribute>
    struct assign_to_container_from_value<Attribute, Attribute>
    {
        static void
        call(Attribute const& val, Attribute& attr)
        {
            attr = val;
        }
    };

    template <typename Attribute, typename T>
    struct assign_to_container_from_value<Attribute, boost::optional<T>
      , typename disable_if<is_same<Attribute, boost::optional<T> > >::type>
    {
        static void
        call(boost::optional<T> const& val, Attribute& attr)
        {
            assign_to(val.get(), attr);
        }
    };

    template <typename Attribute, typename T>
    struct assign_to_container_from_value<Attribute, reference_wrapper<T>
      , typename disable_if<is_same<Attribute, reference_wrapper<T> > >::type>
    {
        static void
        call(reference_wrapper<T> const& val, Attribute& attr)
        {
            assign_to(val.get(), attr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        // overload for non-container attributes
        template <typename T, typename Attribute>
        inline void
        assign_to(T const& val, Attribute& attr, mpl::false_)
        {
            assign_to_attribute_from_value<Attribute, T>::call(val, attr);
        }

        // overload for containers (but not for variants or optionals
        // holding containers)
        template <typename T, typename Attribute>
        inline void
        assign_to(T const& val, Attribute& attr, mpl::true_)
        {
            assign_to_container_from_value<Attribute, T>::call(val, attr);
        }
    }

    template <typename T, typename Attribute>
    inline void
    assign_to(T const& val, Attribute& attr)
    {
        typedef typename mpl::and_<
            traits::is_container<Attribute>
          , traits::not_is_variant<Attribute>
          , traits::not_is_optional<Attribute>
        >::type is_not_wrapped_container;

        detail::assign_to(val, attr, is_not_wrapped_container());
    }

    template <typename T>
    inline void
    assign_to(T const&, unused_type)
    {
    }
}}}

#endif

/* assign_to.hpp
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
*/