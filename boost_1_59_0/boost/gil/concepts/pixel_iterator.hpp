//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_PIXEL_ITERATOR_HPP
#define BOOST_GIL_CONCEPTS_PIXEL_ITERATOR_HPP

#include <boost/gil/concepts/channel.hpp>
#include <boost/gil/concepts/color.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/pixel.hpp>
#include <boost/gil/concepts/pixel_based.hpp>

#include <boost/iterator/iterator_concepts.hpp>

#include <cstddef>
#include <iterator>
#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

// Forward declarations
template <typename It> struct const_iterator_type;
template <typename It> struct iterator_is_mutable;
template <typename It> struct is_iterator_adaptor;
template <typename It, typename NewBaseIt> struct iterator_adaptor_rebind;
template <typename It> struct iterator_adaptor_get_base;

// These iterator mutability concepts are taken from Boost concept_check.hpp.
// Isolating mutability to result in faster compile time
namespace detail {

// Preconditions: TT Models boost_concepts::ForwardTraversalConcept
template <class TT>
struct ForwardIteratorIsMutableConcept
{
    void constraints()
    {
        auto const tmp = *i;
        *i++ = tmp; // require postincrement and assignment
    }
    TT i;
};

// Preconditions: TT Models boost::BidirectionalIteratorConcept
template <class TT>
struct BidirectionalIteratorIsMutableConcept
{
    void constraints()
    {
        gil_function_requires< ForwardIteratorIsMutableConcept<TT>>();
        auto const tmp = *i;
        *i-- = tmp; // require postdecrement and assignment
    }
    TT i;
};

// Preconditions: TT Models boost_concepts::RandomAccessTraversalConcept
template <class TT>
struct RandomAccessIteratorIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<BidirectionalIteratorIsMutableConcept<TT>>();

        typename std::iterator_traits<TT>::difference_type n = 0;
        ignore_unused_variable_warning(n);
        i[n] = *i; // require element access and assignment
    }
    TT i;
};

// Iterators that can be used as the base of memory_based_step_iterator require some additional functions
// \tparam Iterator Models boost_concepts::RandomAccessTraversalConcept
template <typename Iterator>
struct RandomAccessIteratorIsMemoryBasedConcept
{
    void constraints()
    {
        std::ptrdiff_t bs = memunit_step(it);
        ignore_unused_variable_warning(bs);

        it = memunit_advanced(it, 3);
        std::ptrdiff_t bd = memunit_distance(it, it);
        ignore_unused_variable_warning(bd);

        memunit_advance(it,3);
        // for performace you may also provide a customized implementation of memunit_advanced_ref
    }
    Iterator it;
};

/// \tparam Iterator Models PixelIteratorConcept
template <typename Iterator>
struct PixelIteratorIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept<Iterator>>();

        using ref_t = typename std::remove_reference
            <
                typename std::iterator_traits<Iterator>::reference
            >::type;
        using channel_t = typename element_type<ref_t>::type;
        gil_function_requires<detail::ChannelIsMutableConcept<channel_t>>();
    }
};

} // namespace detail

/// \ingroup PixelLocatorConcept
/// \brief Concept for locators and views that can define a type just like the given locator or view, except X and Y is swapped
/// \code
/// concept HasTransposedTypeConcept<typename T>
/// {
///     typename transposed_type<T>;
///         where Metafunction<transposed_type<T> >;
/// };
/// \endcode
template <typename T>
struct HasTransposedTypeConcept
{
    void constraints()
    {
        using type = typename transposed_type<T>::type;
        ignore_unused_variable_warning(type{});
    }
};

/// \defgroup PixelIteratorConceptPixelIterator PixelIteratorConcept
/// \ingroup PixelIteratorConcept
/// \brief STL iterator over pixels

/// \ingroup PixelIteratorConceptPixelIterator
/// \brief An STL random access traversal iterator over a model of PixelConcept.
///
/// GIL's iterators must also provide the following metafunctions:
///  - \p const_iterator_type<Iterator>:   Returns a read-only equivalent of \p Iterator
///  - \p iterator_is_mutable<Iterator>:   Returns whether the given iterator is read-only or mutable
///  - \p is_iterator_adaptor<Iterator>:   Returns whether the given iterator is an adaptor over another iterator. See IteratorAdaptorConcept for additional requirements of adaptors.
///
/// \code
/// concept PixelIteratorConcept<typename Iterator>
///     : boost_concepts::RandomAccessTraversalConcept<Iterator>, PixelBasedConcept<Iterator>
/// {
///     where PixelValueConcept<value_type>;
///     typename const_iterator_type<It>::type;
///         where PixelIteratorConcept<const_iterator_type<It>::type>;
///     static const bool  iterator_is_mutable<It>::value;
///     static const bool  is_iterator_adaptor<It>::value;   // is it an iterator adaptor
/// };
/// \endcode
template <typename Iterator>
struct PixelIteratorConcept
{
    void constraints()
    {
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<Iterator>>();
        gil_function_requires<PixelBasedConcept<Iterator>>();

        using value_type = typename std::iterator_traits<Iterator>::value_type;
        gil_function_requires<PixelValueConcept<value_type>>();

        using const_t = typename const_iterator_type<Iterator>::type;
        static bool const is_mutable = iterator_is_mutable<Iterator>::value;
        ignore_unused_variable_warning(is_mutable);

        // immutable iterator must be constructible from (possibly mutable) iterator
        const_t const_it(it);
        ignore_unused_variable_warning(const_it);

        check_base(typename is_iterator_adaptor<Iterator>::type());
    }

    void check_base(std::false_type) {}

    void check_base(std::true_type)
    {
        using base_t = typename iterator_adaptor_get_base<Iterator>::type;
        gil_function_requires<PixelIteratorConcept<base_t>>();
    }

    Iterator it;
};

/// \brief Pixel iterator that allows for changing its pixel
/// \ingroup PixelIteratorConceptPixelIterator
/// \code
/// concept MutablePixelIteratorConcept<PixelIteratorConcept Iterator>
///     : MutableRandomAccessIteratorConcept<Iterator> {};
/// \endcode
template <typename Iterator>
struct MutablePixelIteratorConcept
{
    void constraints()
    {
        gil_function_requires<PixelIteratorConcept<Iterator>>();
        gil_function_requires<detail::PixelIteratorIsMutableConcept<Iterator>>();
    }
};

/// \defgroup PixelIteratorConceptStepIterator StepIteratorConcept
/// \ingroup PixelIteratorConcept
/// \brief Iterator that advances by a specified step

/// \ingroup PixelIteratorConceptStepIterator
/// \brief Concept of a random-access iterator that can be advanced in memory units (bytes or bits)
/// \code
/// concept MemoryBasedIteratorConcept<boost_concepts::RandomAccessTraversalConcept Iterator>
/// {
///     typename byte_to_memunit<Iterator>; where metafunction<byte_to_memunit<Iterator> >;
///     std::ptrdiff_t      memunit_step(const Iterator&);
///     std::ptrdiff_t      memunit_distance(const Iterator& , const Iterator&);
///     void                memunit_advance(Iterator&, std::ptrdiff_t diff);
///     Iterator            memunit_advanced(const Iterator& p, std::ptrdiff_t diff) { Iterator tmp; memunit_advance(tmp,diff); return tmp; }
///     Iterator::reference memunit_advanced_ref(const Iterator& p, std::ptrdiff_t diff) { return *memunit_advanced(p,diff); }
/// };
/// \endcode
template <typename Iterator>
struct MemoryBasedIteratorConcept
{
    void constraints()
    {
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<Iterator>>();
        gil_function_requires<detail::RandomAccessIteratorIsMemoryBasedConcept<Iterator>>();
    }
};

/// \ingroup PixelIteratorConceptStepIterator
/// \brief Step iterator concept
///
/// Step iterators are iterators that have a set_step method
/// \code
/// concept StepIteratorConcept<boost_concepts::ForwardTraversalConcept Iterator>
/// {
///     template <Integral D>
///     void Iterator::set_step(D step);
/// };
/// \endcode
template <typename Iterator>
struct StepIteratorConcept
{
    void constraints()
    {
        gil_function_requires<boost_concepts::ForwardTraversalConcept<Iterator>>();
        it.set_step(0);
    }
    Iterator it;
};


/// \ingroup PixelIteratorConceptStepIterator
/// \brief Step iterator that allows for modifying its current value
/// \code
/// concept MutableStepIteratorConcept<Mutable_ForwardIteratorConcept Iterator>
///     : StepIteratorConcept<Iterator> {};
/// \endcode
template <typename Iterator>
struct MutableStepIteratorConcept
{
    void constraints()
    {
        gil_function_requires<StepIteratorConcept<Iterator>>();
        gil_function_requires<detail::ForwardIteratorIsMutableConcept<Iterator>>();
    }
};

/// \defgroup PixelIteratorConceptIteratorAdaptor IteratorAdaptorConcept
/// \ingroup PixelIteratorConcept
/// \brief Adaptor over another iterator

/// \ingroup PixelIteratorConceptIteratorAdaptor
/// \brief Iterator adaptor is a forward iterator adapting another forward iterator.
///
/// In addition to GIL iterator requirements,
/// GIL iterator adaptors must provide the following metafunctions:
///  - \p is_iterator_adaptor<Iterator>:             Returns \p std::true_type
///  - \p iterator_adaptor_get_base<Iterator>:       Returns the base iterator type
///  - \p iterator_adaptor_rebind<Iterator,NewBase>: Replaces the base iterator with the new one
///
/// The adaptee can be obtained from the iterator via the "base()" method.
///
/// \code
/// concept IteratorAdaptorConcept<boost_concepts::ForwardTraversalConcept Iterator>
/// {
///     where SameType<is_iterator_adaptor<Iterator>::type, std::true_type>;
///
///     typename iterator_adaptor_get_base<Iterator>;
///         where Metafunction<iterator_adaptor_get_base<Iterator> >;
///         where boost_concepts::ForwardTraversalConcept<iterator_adaptor_get_base<Iterator>::type>;
///
///     typename another_iterator;
///     typename iterator_adaptor_rebind<Iterator,another_iterator>::type;
///         where boost_concepts::ForwardTraversalConcept<another_iterator>;
///         where IteratorAdaptorConcept<iterator_adaptor_rebind<Iterator,another_iterator>::type>;
///
///     const iterator_adaptor_get_base<Iterator>::type& Iterator::base() const;
/// };
/// \endcode
template <typename Iterator>
struct IteratorAdaptorConcept
{
    void constraints()
    {
        gil_function_requires<boost_concepts::ForwardTraversalConcept<Iterator>>();

        using base_t = typename iterator_adaptor_get_base<Iterator>::type;
        gil_function_requires<boost_concepts::ForwardTraversalConcept<base_t>>();

        static_assert(is_iterator_adaptor<Iterator>::value, "");
        using rebind_t = typename iterator_adaptor_rebind<Iterator, void*>::type;

        base_t base = it.base();
        ignore_unused_variable_warning(base);
    }
    Iterator it;
};

/// \brief Iterator adaptor that is mutable
/// \ingroup PixelIteratorConceptIteratorAdaptor
/// \code
/// concept MutableIteratorAdaptorConcept<Mutable_ForwardIteratorConcept Iterator>
///     : IteratorAdaptorConcept<Iterator> {};
/// \endcode
template <typename Iterator>
struct MutableIteratorAdaptorConcept
{
    void constraints()
    {
        gil_function_requires<IteratorAdaptorConcept<Iterator>>();
        gil_function_requires<detail::ForwardIteratorIsMutableConcept<Iterator>>();
    }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* pixel_iterator.hpp
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
*/