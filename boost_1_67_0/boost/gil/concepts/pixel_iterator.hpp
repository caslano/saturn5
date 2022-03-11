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