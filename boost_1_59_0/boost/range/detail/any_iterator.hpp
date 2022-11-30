// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_ANY_ITERATOR_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_ANY_ITERATOR_HPP_INCLUDED

#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/range/detail/any_iterator_buffer.hpp>
#include <boost/range/detail/any_iterator_interface.hpp>
#include <boost/range/detail/any_iterator_wrapper.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost
{
    namespace range_detail
    {
        // metafunction to determine if T is a const reference
        template<class T>
        struct is_const_reference
        {
            typedef typename mpl::and_<
                typename is_reference<T>::type,
                typename is_const<
                    typename remove_reference<T>::type
                >::type
            >::type type;
        };

        // metafunction to determine if T is a mutable reference
        template<class T>
        struct is_mutable_reference
        {
            typedef typename mpl::and_<
                typename is_reference<T>::type,
                typename mpl::not_<
                    typename is_const<
                        typename remove_reference<T>::type
                    >::type
                >::type
            >::type type;
        };

        // metafunction to evaluate if a source 'reference' can be
        // converted to a target 'reference' as a value.
        //
        // This is true, when the target reference type is actually
        // not a reference, and the source reference is convertible
        // to the target type.
        template<class SourceReference, class TargetReference>
        struct is_convertible_to_value_as_reference
        {
            typedef typename mpl::and_<
                typename mpl::not_<
                    typename is_reference<TargetReference>::type
                >::type
              , typename is_convertible<
                    SourceReference
                  , TargetReference
                >::type
            >::type type;
        };

        template<
            class Value
          , class Traversal
          , class Reference
          , class Difference
          , class Buffer = any_iterator_default_buffer
        >
        class any_iterator;

        // metafunction to determine if SomeIterator is an
        // any_iterator.
        //
        // This is the general implementation which evaluates to false.
        template<class SomeIterator>
        struct is_any_iterator
            : mpl::bool_<false>
        {
        };

        // specialization of is_any_iterator to return true for
        // any_iterator classes regardless of template parameters.
        template<
            class Value
          , class Traversal
          , class Reference
          , class Difference
          , class Buffer
        >
        struct is_any_iterator<
            any_iterator<
                Value
              , Traversal
              , Reference
              , Difference
              , Buffer
            >
        >
            : mpl::bool_<true>
        {
        };
    } // namespace range_detail

    namespace iterators
    {
    namespace detail
    {
        // Rationale:
        // These are specialized since the iterator_facade versions lack
        // the requisite typedefs to allow wrapping to determine the types
        // if a user copy constructs from a postfix increment.

        template<
            class Value
          , class Traversal
          , class Reference
          , class Difference
          , class Buffer
        >
        class postfix_increment_proxy<
                    range_detail::any_iterator<
                        Value
                      , Traversal
                      , Reference
                      , Difference
                      , Buffer
                    >
                >
        {
            typedef range_detail::any_iterator<
                Value
              , Traversal
              , Reference
              , Difference
              , Buffer
            > any_iterator_type;

        public:
            typedef Value value_type;
            typedef typename std::iterator_traits<any_iterator_type>::iterator_category iterator_category;
            typedef Difference difference_type;
            typedef typename iterator_pointer<any_iterator_type>::type pointer;
            typedef Reference reference;

            explicit postfix_increment_proxy(any_iterator_type const& x)
                : stored_value(*x)
            {}

            value_type&
            operator*() const
            {
                return this->stored_value;
            }
        private:
            mutable value_type stored_value;
        };

        template<
            class Value
          , class Traversal
          , class Reference
          , class Difference
          , class Buffer
        >
        class writable_postfix_increment_proxy<
                    range_detail::any_iterator<
                        Value
                      , Traversal
                      , Reference
                      , Difference
                      , Buffer
                    >
                >
        {
            typedef range_detail::any_iterator<
                        Value
                      , Traversal
                      , Reference
                      , Difference
                      , Buffer
                    > any_iterator_type;
         public:
            typedef Value value_type;
            typedef typename std::iterator_traits<any_iterator_type>::iterator_category iterator_category;
            typedef Difference difference_type;
            typedef typename iterator_pointer<any_iterator_type>::type pointer;
            typedef Reference reference;

            explicit writable_postfix_increment_proxy(any_iterator_type const& x)
              : stored_value(*x)
              , stored_iterator(x)
            {}

            // Dereferencing must return a proxy so that both *r++ = o and
            // value_type(*r++) can work.  In this case, *r is the same as
            // *r++, and the conversion operator below is used to ensure
            // readability.
            writable_postfix_increment_proxy const&
            operator*() const
            {
                return *this;
            }

            // Provides readability of *r++
            operator value_type&() const
            {
                return stored_value;
            }

            // Provides writability of *r++
            template <class T>
            T const& operator=(T const& x) const
            {
                *this->stored_iterator = x;
                return x;
            }

            // This overload just in case only non-const objects are writable
            template <class T>
            T& operator=(T& x) const
            {
                *this->stored_iterator = x;
                return x;
            }

            // Provides X(r++)
            operator any_iterator_type const&() const
            {
                return stored_iterator;
            }

         private:
            mutable value_type stored_value;
            any_iterator_type stored_iterator;
        };

    } //namespace detail
    } //namespace iterators

    namespace range_detail
    {
        template<
            class Value
          , class Traversal
          , class Reference
          , class Difference
          , class Buffer
        >
        class any_iterator
            : public iterator_facade<
                        any_iterator<
                            Value
                          , Traversal
                          , Reference
                          , Difference
                          , Buffer
                        >
                    , Value
                    , Traversal
                    , Reference
                    , Difference
                >
        {
            template<
                class OtherValue
              , class OtherTraversal
              , class OtherReference
              , class OtherDifference
              , class OtherBuffer
            >
            friend class any_iterator;

            struct enabler {};
            struct disabler {};

            typedef typename any_iterator_interface_type_generator<
                Traversal
              , Reference
              , Difference
              , Buffer
            >::type abstract_base_type;

            typedef iterator_facade<
                        any_iterator<
                            Value
                          , Traversal
                          , Reference
                          , Difference
                          , Buffer
                        >
                      , Value
                      , Traversal
                      , Reference
                      , Difference
                  > base_type;

            typedef Buffer buffer_type;

        public:
            typedef typename base_type::value_type value_type;
            typedef typename base_type::reference reference;
            typedef typename base_type::difference_type difference_type;

            // Default constructor
            any_iterator()
                : m_impl(0) {}

            // Simple copy construction without conversion
            any_iterator(const any_iterator& other)
                : base_type(other)
                , m_impl(other.m_impl
                            ? other.m_impl->clone(m_buffer)
                            : 0)
            {
            }

            // Simple assignment operator without conversion
            any_iterator& operator=(const any_iterator& other)
            {
                if (this != &other)
                {
                    if (m_impl)
                        m_impl->~abstract_base_type();
                    m_buffer.deallocate();
                    m_impl = 0;
                    if (other.m_impl)
                        m_impl = other.m_impl->clone(m_buffer);
                }
                return *this;
            }

            // Implicit conversion from another any_iterator where the
            // conversion is from a non-const reference to a const reference
            template<
                class OtherValue
              , class OtherTraversal
              , class OtherReference
              , class OtherDifference
            >
            any_iterator(const any_iterator<
                                OtherValue,
                                OtherTraversal,
                                OtherReference,
                                OtherDifference,
                                Buffer
                            >& other,
                         typename ::boost::enable_if<
                            typename mpl::and_<
                                typename is_mutable_reference<OtherReference>::type,
                                typename is_const_reference<Reference>::type
                            >::type,
                            enabler
                        >::type* = 0
                    )
                : m_impl(other.m_impl
                            ? other.m_impl->clone_const_ref(m_buffer)
                         : 0
                        )
            {
            }

            // Implicit conversion from another any_iterator where the
            // reference types of the source and the target are references
            // that are either both const, or both non-const.
            template<
                class OtherValue
              , class OtherTraversal
              , class OtherReference
              , class OtherDifference
            >
            any_iterator(const any_iterator<
                                OtherValue
                              , OtherTraversal
                              , OtherReference
                              , OtherDifference
                              , Buffer
                            >& other,
                         typename ::boost::enable_if<
                            typename mpl::or_<
                                typename mpl::and_<
                                    typename is_mutable_reference<OtherReference>::type,
                                    typename is_mutable_reference<Reference>::type
                                >::type,
                                typename mpl::and_<
                                    typename is_const_reference<OtherReference>::type,
                                    typename is_const_reference<Reference>::type
                                >::type
                            >::type,
                            enabler
                        >::type* = 0
                        )
                : m_impl(other.m_impl
                            ? other.m_impl->clone(m_buffer)
                         : 0
                        )
            {
            }

            // Implicit conversion to an any_iterator that uses a value for
            // the reference type.
            template<
                class OtherValue
              , class OtherTraversal
              , class OtherReference
              , class OtherDifference
            >
            any_iterator(const any_iterator<
                                OtherValue
                              , OtherTraversal
                              , OtherReference
                              , OtherDifference
                              , Buffer
                            >& other,
                        typename ::boost::enable_if<
                            typename is_convertible_to_value_as_reference<
                                        OtherReference
                                      , Reference
                                    >::type,
                            enabler
                        >::type* = 0
                        )
                : m_impl(other.m_impl
                            ? other.m_impl->clone_reference_as_value(m_buffer)
                            : 0
                            )
            {
            }

            any_iterator clone() const
            {
                any_iterator result;
                if (m_impl)
                    result.m_impl = m_impl->clone(result.m_buffer);
                return result;
            }

            any_iterator<
                Value
              , Traversal
              , typename abstract_base_type::const_reference
              , Difference
              , Buffer
            >
            clone_const_ref() const
            {
                typedef any_iterator<
                    Value
                  , Traversal
                  , typename abstract_base_type::const_reference
                  , Difference
                  , Buffer
                > result_type;

                result_type result;

                if (m_impl)
                    result.m_impl = m_impl->clone_const_ref(result.m_buffer);

                return result;
            }

            // implicit conversion and construction from type-erasure-compatible
            // iterators
            template<class WrappedIterator>
            explicit any_iterator(
                const WrappedIterator& wrapped_iterator,
                typename disable_if<
                    typename is_any_iterator<WrappedIterator>::type
                  , disabler
                >::type* = 0
                )
            {
                typedef typename any_iterator_wrapper_type_generator<
                            WrappedIterator
                          , Traversal
                          , Reference
                          , Difference
                          , Buffer
                        >::type wrapper_type;

                void* ptr = m_buffer.allocate(sizeof(wrapper_type));
                m_impl = new(ptr) wrapper_type(wrapped_iterator);
            }

            ~any_iterator()
            {
                // manually run the destructor, the deallocation is automatically
                // handled by the any_iterator_small_buffer base class.
                if (m_impl)
                    m_impl->~abstract_base_type();
            }

        private:
            friend class ::boost::iterator_core_access;

            Reference dereference() const
            {
                BOOST_ASSERT( m_impl );
                return m_impl->dereference();
            }

            bool equal(const any_iterator& other) const
            {
                return (m_impl == other.m_impl)
                    || (m_impl && other.m_impl && m_impl->equal(*other.m_impl));
            }

            void increment()
            {
                BOOST_ASSERT( m_impl );
                m_impl->increment();
            }

            void decrement()
            {
                BOOST_ASSERT( m_impl );
                m_impl->decrement();
            }

            Difference distance_to(const any_iterator& other) const
            {
                return m_impl && other.m_impl
                    ? m_impl->distance_to(*other.m_impl)
                    : 0;
            }

            void advance(Difference offset)
            {
                BOOST_ASSERT( m_impl );
                m_impl->advance(offset);
            }

            any_iterator& swap(any_iterator& other)
            {
                BOOST_ASSERT( this != &other );
                // grab a temporary copy of the other iterator
                any_iterator tmp(other);

                // deallocate the other iterator, taking care to obey the
                // class-invariants in-case of exceptions later
                if (other.m_impl)
                {
                    other.m_impl->~abstract_base_type();
                    other.m_buffer.deallocate();
                    other.m_impl = 0;
                }

                // If this is a non-null iterator then we need to put
                // a clone of this iterators implementation into the other
                // iterator.
                // We can't just swap because of the small buffer optimization.
                if (m_impl)
                {
                    other.m_impl = m_impl->clone(other.m_buffer);
                    m_impl->~abstract_base_type();
                    m_buffer.deallocate();
                    m_impl = 0;
                }

                // assign to this instance a clone of the temporarily held
                // tmp which represents the input other parameter at the
                // start of execution of this function.
                if (tmp.m_impl)
                    m_impl = tmp.m_impl->clone(m_buffer);

                return *this;
            }

            buffer_type m_buffer;
            abstract_base_type* m_impl;
        };

    } // namespace range_detail
} // namespace boost

#endif // include guard

/* any_iterator.hpp
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
*/