//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ANY_RANGE_HPP_INCLUDED
#define BOOST_RANGE_ANY_RANGE_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/detail/any_iterator.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace boost
{
    namespace range_detail
    {
        // If T is use_default, return the result of Default, otherwise
        // return T.
        //
        // This is an implementation artifact used to pick intelligent default
        // values when the user specified boost::use_default as a template
        // parameter.
        template<
            class T,
            class Default
        >
        struct any_range_default_help
            : mpl::eval_if<
                is_same<T, use_default>
              , Default
              , mpl::identity<T>
            >
        {
        };

        template<
            class WrappedRange
          , class Value
          , class Reference
        >
        struct any_range_value_type
        {
# ifdef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
            typedef typename any_range_default_help<
                    Value
                  , mpl::eval_if<
                        is_same<Reference, use_default>
                      , range_value<
                            typename remove_const<WrappedRange>
                        ::type>
                      , remove_reference<Reference>
                    >
                >::type type;
# else
            typedef typename any_range_default_help<
                Value
              , range_value<
                    typename remove_const<WrappedRange>
                ::type>
            >::type type;
# endif
        };

        template<
            class Value
          , class Traversal
          , class Reference = Value&
          , class Difference = std::ptrdiff_t
          , class Buffer = use_default
        >
        class any_range
            : public iterator_range<
                        any_iterator<
                            Value
                          , Traversal
                          , Reference
                          , Difference
                          , typename any_range_default_help<
                                Buffer
                              , mpl::identity<any_iterator_default_buffer>
                            >::type
                        >
                    >
        {
            typedef iterator_range<
                        any_iterator<
                            Value
                          , Traversal
                          , Reference
                          , Difference
                          , typename any_range_default_help<
                                Buffer
                              , mpl::identity<any_iterator_default_buffer>
                            >::type
                        >
                    > base_type;

            struct enabler {};
            struct disabler {};
        public:
            any_range()
            {
            }

            any_range(const any_range& other)
                : base_type(other)
            {
            }

            template<class WrappedRange>
            any_range(WrappedRange& wrapped_range)
            : base_type(boost::begin(wrapped_range),
                        boost::end(wrapped_range))
            {
            }

            template<class WrappedRange>
            any_range(const WrappedRange& wrapped_range)
            : base_type(boost::begin(wrapped_range),
                        boost::end(wrapped_range))
            {
            }

            template<
                class OtherValue
              , class OtherTraversal
              , class OtherReference
              , class OtherDifference
            >
            any_range(const any_range<
                                OtherValue
                              , OtherTraversal
                              , OtherReference
                              , OtherDifference
                              , Buffer
                            >& other)
            : base_type(boost::begin(other), boost::end(other))
            {
            }

            template<class Iterator>
            any_range(Iterator first, Iterator last)
                : base_type(first, last)
            {
            }
        };

        template<
            class WrappedRange
          , class Value = use_default
          , class Traversal = use_default
          , class Reference = use_default
          , class Difference = use_default
          , class Buffer = use_default
        >
        struct any_range_type_generator
        {
            BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept<WrappedRange> ));
            typedef any_range<
                typename any_range_value_type<
                    WrappedRange
                  , Value
                  , typename any_range_default_help<
                        Reference
                      , range_reference<WrappedRange>
                    >::type
                >::type
              , typename any_range_default_help<
                            Traversal
                          , iterator_traversal<
                                typename range_iterator<WrappedRange>::type
                            >
                        >::type
              , typename any_range_default_help<
                    Reference
                  , range_reference<WrappedRange>
                >::type
              , typename any_range_default_help<
                    Difference
                  , range_difference<WrappedRange>
                >::type
              , typename any_range_default_help<
                    Buffer
                  , mpl::identity<any_iterator_default_buffer>
                >::type
            > type;
        };
    } // namespace range_detail

    using range_detail::any_range;
    using range_detail::any_range_type_generator;
} // namespace boost

#endif // include guard

/* any_range.hpp
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
*/