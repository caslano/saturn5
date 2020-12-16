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
1+4HfZgu0GRKfs4v/fS0ans37XK5f236ex3NStvUbRolSv0np6I8TMlrggn/zXUnncnwHH50Zl8/q9ydnmSgf/vg+VWe899dx2m1HO9+Oy8gl69jDvXVM+ksY7SzxxpRYY1IV1a0X777dyXrW4h5QKQvnkhHxixmj/Utf98mUN3M6v6LPn/HhIoWGRHli2ezec5/t76hHq3uumN2ZPB1zAPConoPCvXFy2bImcVsnMcV5nHtS6/RdneAPn/fInzwkLAhvnjtABmzvu2xD6vCPqxaTWR038/d4vPxHEEfjYsIDdbe+Qvs2r1P1IBuvujnf30UtL/H/rEK+8fSnVc118/9bGiOt1QX9K+u/bsN17bQD/RdXXgcBXXhdS9WuoOsYnO4f8/L+9brIrLi26gLOgqrC4/9QhX2C9WuYu/a3M+S+XwPFXcp6Y8Vu3Yf0rNnmC/et/RyEPrnL/cWVSp1b1HtixffuPfacOb39XtKvJgpf/ZxXeAgrC489qpU2KtSu4OxWrthpP2djL6ui8iKXXt098W7p8iYxeyxvyN+86B/SqpG7nV+I5+vhSIr+uh9W2TMYvbYg1FhD0ZFu4q2du+P9rTgW4jZN+t8ZGxYF5w1qWfu+V+7kAvud+nXFC2hHO51QXvbW4jZN+t8ZMxjdlw2Yc2bxbDmLa6upnXPbel8Pp5pU5BukQN9cdI3ZO2O5wztOYu+TXuBTrdPw56C1AcCmX0SsQH7KYaTFdGN/b7p79F3AtF3NHNcoP0izbqtLLZlWqrFXaI8WbqdR8yNUqycR9uEom00CyBryQz3xMliyf5h0+3MgBp9U83vJu1fzNJFjt96M9VCyJpZdJs3qMfRVIumjbcrsnTjljhPplo82VhmE5yVNqda+D3aT5jZ4+vdL6daAllHZutiGt1KNed9k/qMWbuGc4ukmnqgtQMM7UDmsa+jf/K+joiBLBuzxjeno5yxQrokD1tRYacL5aTN82iLUdjKtbfH43iPTGo4s8J3ll9AXdMHQI+zPGs8ezofdfY77VvNzDEk8T7a7wm1O7PB53dbcDwyyhbWt8b6qqizP73H4CLjefK+FE82n1mb5nftqRZDHb4wM+2+G9KRlWGG3zvI1HPv5hQsmuw9Zl+7vmuMviSk83tBv/0ww31osgAybzGEkHnLM1awRMEcL2nPYGbabz04Hpm3ckaTeStnnGCJZF7L8sq7hZB5yzOGzFsMCUI69dqkvrXo9rzVmeeoTwv9Xsf67neW49NRFptZvWPTrffwqQ/RzzKYlYWlu101Uxm0eyazasb7bsdKpTDGyO4wO5d4sQTKktmsLtp1u9T1JsaDM5dZrWDH2/Bt8YIoZx6zKsytfuJc1Etes0rDbH3tFpFoB3o5IhezUvnPfoF2L2BWU1g5TQOuNEXfLWhWFZid/b3JBsRHNpHZk977luN4hczqNLOpC44cRZ4O+jYLs+idYesQg4d1+eR4RhyvMP3+adYtd93y51BnxczUvrrFhh2YiDxLUruzPO+O6AdzlTKrAszS1NqWiHoh89Z348m89cEkskBmL18376aZt71xU81ZUfs2hW4Ltsfq90rJXMzuPEmH53SSPCyk0ak1uPdWyayCmdXMUKIEfj8i4+mmJ0424XokyKwyM2t5en5AqoUHeaS7PKoG8iRzMMtQ7I9c+G2pMo0VZksf5B2HPMmqMXvfFtEc1wlktIc2LPOsrztjbVnNrLIgnfEZHidZQWZzD5d6hOORZWLWMGrcLtQ1WU1m216fhSWQVWAWn+VMZcRX3UznOBg7x1GeZDdZDK9K/dIS7VfDTL1EtwKrG3VFf6EPQZxkdvPPu+8gvprUd5lpfRfxkU0=
*/