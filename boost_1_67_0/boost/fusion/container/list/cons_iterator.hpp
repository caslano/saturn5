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