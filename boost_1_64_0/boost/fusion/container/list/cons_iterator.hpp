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
aE7cK/16bPca0yZ9esr9zg/3dGGpPj35Hvr0xJziWDjmY96np+gOQ3orpT+PWxqk34Ln/gDm5dCeyrO9L1c271fgfbt/834LlVdebt4fwHP/AfN+Ap76RXjff8Dbfg7m5fee+6uY90vx3D9hewtlevTQb59e3PKL26+fFTj3+fTEPM/9T46r70aQezQokne11MAgOZhflvbfr+F8PIxX4Bt4AN/E4+hfRe5N5J4lTPooNZL7wq9kOccxBn9EO/6Ec/BnXIoncDX+ijfh77gFT+JW/BM/wr/wc1TaIddhHdWwIdbAC7Am9kYf7Ie1cQzWwQlYDy/H+jgfffFGPA83YEN8GBvhDvTDv/ACbEvemmNvbIH9sCVGoT+OxDY4EdviZGyHrnoX+c3HRbK99fUu70l77SJMwg8xFT/GXPxE9sOnWr8A+d3E22R5+n4BodIvoC/6Yz+MxP6YhmF4JYbjBoxAbTzSO2WcVNmf+vFIB8jyBmIXjMJpOARzcCjOxmF4FQ7HVTgCN+FIvBdj8SEcjTtxLO7DODyK49GXdU7A5jgR2+BkDMR47INTMAKTcDAm42hMwcsxDW/DdLwfp+I2zMC9OB0PogPfwRn4EeZgNfLuRB/Mxa44C6MxD0fhHIzD+SjjDMjvsPr7zPYzjjNwhfQDWYSBuBjTcAnOw6vwBrwa78Nlsl2uwbfwWlnPddJfZyW2wOuxO67GKFyLk/AGzMF1mIfrtXe0yG+y/FaHub2jZaOk8xbsgJswHG/DAbgZd+Fd+Djeg3vxXu34lN9QHGlyfHbV9Yvqgj2wJwbhJdgTozAEh2FvXMMyjs4qXz8C/wKrL0FF+hLYibFneV+Cf7ofQa083odNDCHGEp3ENcSdxCN5Vr2zFaxgBStYwQpWsIIVrGAFK1ih/KE6ccqZqv9X6i4qoe7fj3b9Tpbh+6bSrj/HmeVwqC9Nv4DprbFAne5Mo6W/nb8qdSfq3wZT79FU+058GpXXLC5HXZ5S7+Wv/k1JJO38k3gXF9MbKGXI6vQpiTnJrEPWHaBNU2tk1PVfJH/rpP4tiw0Sry7sb/buBD6K6g7g+MohNwQIECDABkLIBSQQIELAQAIEiBAwQKCBJGQDCeRYkg0mGjDUiEEQI0VFBYmIGi1to2KLioqWKlVsqVWLV0krtlSpUu9e2t/M/nd2ZjObbBBbP/3sfD6PL/syO++YY2fmzZunzqV+5L1f3DAcLsuNUedTuxQ4K0jrVUCbrywrzts8WrLUpcwb75FucUmWyRd1OWGaKN9NMH631S8OlTIkqt/LsdmylMGScwvs+dQo8eNkuckeyzXOab7MFMMyaVPPK3Pol5lqvkyZ07jMMfKdtGZ1I1/zKFd/yUO6Oj9DVK8uWMNHbb1n6OJlFajfUdohG535ttuLc4rydOsw0yNt+bY+WW3e7Ob59Jxd2y5tzvTKKotztfzlu+Mke+7tstBj2c65tOVq9W9X58srXlPAUwqya1t09e/wWI5xTmO5BskyK/TLLLWVsu9p66bKdHkyl0n+qvXLslVS2wW5+vzVmC9P5jTkT1tmrX6Z9hybcgDQL3O7+TJlTvMy1+mXmZtjL9Btj7tMlidz6Remrevd6vxXFxascm+Le7S45segeo/lq3NpC3b2fRo93KKNH9FZbh8ekPbnfYT5yrscdxrGachx5FUUOHx4x6frnYU1VqWtWQ61Eh+Oc5zjX+RdpfxJ3k14viPtchyHJ/H5OTVdyirPx6RF6ZZTVllkke9UMP95wmg+n5DvSDu3/l2L2jgbz+jyo3sfqDre9Rn5/pWkpR9b46DUTR+l3Q57YGCg0lBoqBt5WqT1tnmlTFatDnLLS0vd9TM=
*/