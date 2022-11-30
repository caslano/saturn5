/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_ITERATOR_07172005_0849)
#define FUSION_CONS_ITERATOR_07172005_0849

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/container/list/detail/deref_impl.hpp>
#include <boost/fusion/container/list/detail/next_impl.hpp>
#include <boost/fusion/container/list/detail/value_of_impl.hpp>
#include <boost/fusion/container/list/detail/equal_to_impl.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>

namespace boost { namespace fusion
{
    struct nil_;
    struct cons_iterator_tag;
    struct forward_traversal_tag;

    template <typename Cons>
    struct cons_iterator_identity;

    template <typename Cons = nil_>
    struct cons_iterator : iterator_base<cons_iterator<Cons> >
    {
        typedef cons_iterator_tag fusion_tag;
        typedef forward_traversal_tag category;
        typedef Cons cons_type;
        typedef cons_iterator_identity<
            typename add_const<Cons>::type> 
        identity;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit cons_iterator(cons_type& in_cons) BOOST_NOEXCEPT
            : cons(in_cons) {}

        cons_type& cons;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(cons_iterator& operator= (cons_iterator const&))
    };

    struct nil_iterator : iterator_base<nil_iterator>
    {
        typedef forward_traversal_tag category;
        typedef cons_iterator_tag fusion_tag;
        typedef nil_ cons_type;
        typedef cons_iterator_identity<
            add_const<nil_>::type> 
        identity;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        nil_iterator() BOOST_NOEXCEPT {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit nil_iterator(nil_ const&) BOOST_NOEXCEPT {}
    };

    template <>
    struct cons_iterator<nil_> : nil_iterator 
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons_iterator() BOOST_NOEXCEPT {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit cons_iterator(nil_ const&) BOOST_NOEXCEPT {}
    };

    template <>
    struct cons_iterator<nil_ const> : nil_iterator 
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons_iterator() BOOST_NOEXCEPT {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit cons_iterator(nil_ const&) BOOST_NOEXCEPT {}
    };

    template <>
    struct cons_iterator<list<> > : nil_iterator 
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons_iterator() BOOST_NOEXCEPT {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit cons_iterator(nil_ const&) BOOST_NOEXCEPT {}
    };

    template <>
    struct cons_iterator<list<> const> : nil_iterator 
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        cons_iterator() BOOST_NOEXCEPT {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit cons_iterator(nil_ const&) BOOST_NOEXCEPT {}
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Cons>
    struct iterator_traits< ::boost::fusion::cons_iterator<Cons> >
    { };
}
#endif

#endif

/* cons_iterator.hpp
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
*/