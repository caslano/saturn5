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
4dCx/gvrjHRyFdg3eyxOtt8YRvy/lCjGz64wcpT8ImYqlHMkfzJqwch2CSLcZ0+dqlAWepfEr9QplCaB6ZyRSrVjYxAogwK6olmUVrdYA3w3b80LmqlggVnYqW+cQk3fHBUAu/7IitxJcGv4xswA3YHhpbNP/zZaWStQ9aJGRGQSw+CFLD3VDqV0QSZRlO2ehypNyE5VqUZr8ULvnVvXjDgEA1wGZ0sfAaz1mEgfKon+qqdoqAvTKYcGnGcK0rqqh2vJ+z8NQsNc1mEEAG4IguO0J0FMM/eMUAmhWuBXF4dpMiDHBuDai2vApO5t2cFSpXvtPp21sCd68SR6IcKCARV890Vx8yU+MB8kX2igRxDO/MD30VdOU0fo8JC156Vd4Vnj5xEDID2kmQ0YNp6qcvqseT1fRTaLXB5h5zqQiEUIAR+FY/XhlnUiiLdqJxxPufu7u5nk1yTE71lU3B1BK4Dp29s32kVoEbnzqxy128wWyF30pohGJFnElVwckiMB/93o3EKxAUxf77+SDb2qgDStJs2js8q0q9bvy3fR2E4297zrv7Dj9jYDCg==
*/