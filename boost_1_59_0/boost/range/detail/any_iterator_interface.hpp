// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_ANY_ITERATOR_INTERFACE_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_ANY_ITERATOR_INTERFACE_HPP_INCLUDED

#include <boost/range/detail/any_iterator_buffer.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost
{
    namespace range_detail
    {
        template<class T>
        struct const_reference_type_generator
        {
            typedef typename mpl::if_<
                typename is_reference<T>::type,
                typename add_const<
                    typename remove_reference<T>::type
                >::type&,
                T
            >::type type;
        };

        template<class T>
        struct reference_as_value_type_generator
        {
            typedef typename remove_reference<
                typename remove_const<T>::type
            >::type value_type;

            typedef typename mpl::if_<
                typename is_convertible<const value_type&, value_type>::type,
                value_type,
                T
            >::type type;
        };

        template<
            class Reference
          , class Buffer
        >
        struct any_incrementable_iterator_interface
        {
            typedef Reference reference;
            typedef typename const_reference_type_generator<
                Reference
            >::type const_reference;
            typedef typename reference_as_value_type_generator<
                Reference
            >::type reference_as_value_type;

            typedef Buffer buffer_type;

            virtual ~any_incrementable_iterator_interface() {}

            virtual any_incrementable_iterator_interface*
                        clone(buffer_type& buffer) const = 0;

            virtual any_incrementable_iterator_interface<const_reference, Buffer>*
                        clone_const_ref(buffer_type& buffer) const = 0;

            virtual any_incrementable_iterator_interface<reference_as_value_type, Buffer>*
                        clone_reference_as_value(buffer_type& buffer) const = 0;

            virtual void increment() = 0;
        };

        template<
            class Reference
          , class Buffer
        >
        struct any_single_pass_iterator_interface
            : any_incrementable_iterator_interface<Reference, Buffer>
        {
            typedef typename any_incrementable_iterator_interface<Reference, Buffer>::reference reference;
            typedef typename any_incrementable_iterator_interface<Reference, Buffer>::const_reference const_reference;
            typedef typename any_incrementable_iterator_interface<Reference, Buffer>::buffer_type buffer_type;
            typedef typename any_incrementable_iterator_interface<Reference, Buffer>::reference_as_value_type reference_as_value_type;

            virtual any_single_pass_iterator_interface*
                        clone(buffer_type& buffer) const = 0;

            virtual any_single_pass_iterator_interface<const_reference, Buffer>*
                        clone_const_ref(buffer_type& buffer) const = 0;

            virtual any_single_pass_iterator_interface<reference_as_value_type, Buffer>*
                        clone_reference_as_value(buffer_type& buffer) const = 0;

            virtual reference dereference() const = 0;

            virtual bool equal(const any_single_pass_iterator_interface& other) const = 0;
        };

        template<
            class Reference
          , class Buffer
        >
        struct any_forward_iterator_interface
            : any_single_pass_iterator_interface<Reference, Buffer>
        {
            typedef typename any_single_pass_iterator_interface<Reference, Buffer>::reference reference;
            typedef typename any_single_pass_iterator_interface<Reference, Buffer>::const_reference const_reference;
            typedef typename any_single_pass_iterator_interface<Reference, Buffer>::buffer_type buffer_type;
            typedef typename any_single_pass_iterator_interface<Reference, Buffer>::reference_as_value_type reference_as_value_type;

            virtual any_forward_iterator_interface*
                        clone(buffer_type& buffer) const = 0;

            virtual any_forward_iterator_interface<const_reference, Buffer>*
                        clone_const_ref(buffer_type& buffer) const = 0;

            virtual any_forward_iterator_interface<reference_as_value_type, Buffer>*
                        clone_reference_as_value(buffer_type& buffer) const = 0;
        };

        template<
            class Reference
          , class Buffer
        >
        struct any_bidirectional_iterator_interface
            : any_forward_iterator_interface<Reference, Buffer>
        {
            typedef typename any_forward_iterator_interface<Reference, Buffer>::reference reference;
            typedef typename any_forward_iterator_interface<Reference, Buffer>::const_reference const_reference;
            typedef typename any_forward_iterator_interface<Reference, Buffer>::buffer_type buffer_type;
            typedef typename any_forward_iterator_interface<Reference, Buffer>::reference_as_value_type reference_as_value_type;

            virtual any_bidirectional_iterator_interface*
                        clone(buffer_type& buffer) const = 0;

            virtual any_bidirectional_iterator_interface<const_reference, Buffer>*
                        clone_const_ref(buffer_type& buffer) const = 0;

            virtual any_bidirectional_iterator_interface<reference_as_value_type, Buffer>*
                        clone_reference_as_value(buffer_type& buffer) const = 0;

            virtual void decrement() = 0;
        };

        template<
            class Reference
          , class Difference
          , class Buffer
        >
        struct any_random_access_iterator_interface
            : any_bidirectional_iterator_interface<
                    Reference
                  , Buffer
                >
        {
            typedef typename any_bidirectional_iterator_interface<Reference, Buffer>::reference reference;
            typedef typename any_bidirectional_iterator_interface<Reference, Buffer>::const_reference const_reference;
            typedef typename any_bidirectional_iterator_interface<Reference, Buffer>::buffer_type buffer_type;
            typedef typename any_bidirectional_iterator_interface<Reference, Buffer>::reference_as_value_type reference_as_value_type;
            typedef Difference difference_type;

            virtual any_random_access_iterator_interface*
                        clone(buffer_type& buffer) const = 0;

            virtual any_random_access_iterator_interface<const_reference, Difference, Buffer>*
                        clone_const_ref(buffer_type& buffer) const = 0;

            virtual any_random_access_iterator_interface<reference_as_value_type, Difference, Buffer>*
                        clone_reference_as_value(buffer_type& buffer) const = 0;

            virtual void advance(Difference offset) = 0;

            virtual Difference distance_to(const any_random_access_iterator_interface& other) const = 0;
        };

        template<
            class Traversal
          , class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_interface_type_generator;

        template<
            class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_interface_type_generator<
                    incrementable_traversal_tag
                  , Reference
                  , Difference
                  , Buffer
                >
        {
            typedef any_incrementable_iterator_interface<Reference, Buffer> type;
        };

        template<
            class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_interface_type_generator<
                    single_pass_traversal_tag
                  , Reference
                  , Difference
                  , Buffer
                >
        {
            typedef any_single_pass_iterator_interface<Reference, Buffer> type;
        };

        template<
            class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_interface_type_generator<
                    forward_traversal_tag
                  , Reference
                  , Difference
                  , Buffer
                >
        {
            typedef any_forward_iterator_interface<Reference, Buffer> type;
        };

        template<
            class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_interface_type_generator<
                    bidirectional_traversal_tag
                  , Reference
                  , Difference
                  , Buffer
                >
        {
            typedef any_bidirectional_iterator_interface<Reference, Buffer> type;
        };

        template<
            class Reference
          , class Difference
          , class Buffer
        >
        struct any_iterator_interface_type_generator<
                    random_access_traversal_tag
                  , Reference
                  , Difference
                  , Buffer
                >
        {
            typedef any_random_access_iterator_interface<
                        Reference
                      , Difference
                      , Buffer
                    > type;
        };

    } // namespace range_detail
} // namespace boost

#endif // include guard

/* any_iterator_interface.hpp
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
*/