/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED
#define BOOST_FUSION_REPETITIVE_VIEW_REPETITIVE_VIEW_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/if.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/fusion/view/repetitive_view/detail/begin_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/end_impl.hpp>


namespace boost { namespace fusion
{
    struct repetitive_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequence> struct repetitive_view 
        : sequence_base< repetitive_view<Sequence> >
    {
        typedef repetitive_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef single_pass_traversal_tag category;

        typedef typename boost::remove_reference<Sequence>::type sequence_type;
        typedef typename 
            mpl::if_<traits::is_view<Sequence>, Sequence, sequence_type&>::type
        stored_seq_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        repetitive_view(Sequence& in_seq)
            : seq(in_seq) {}

        stored_seq_type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(repetitive_view& operator= (repetitive_view const&))
    };

}}

#endif

/* repetitive_view.hpp
vHi1xFg2me0ZU3uAVvScijvPT8lm+yLO/pffM9zjck2uLHVn4v1bfdDARy6dEftiW4hACmF7GVXkCjidOTjnmcrpxvUT7aRG/6y5AE5OjZe+38dwxjRiaR35xZk89eCnSGVf3UdKGwgzjiuh6fhCNkgTIawkM/I8Jm0Wq2miogR/QaLDL9+E1LaO8cvL43cUlxPLL8CO2iHV4Qj6wETcz82d29LuUaiUVR0heVaM+wibt6Cj72cvpyPJMGkaX8+CRkbK8KunLKoKrmhuCoHlIDhxnH5fC1g6mC5RBJvy2yc6Sv/i8MPO3yDb1gL4mkbKSf8t8jXpDoNxwwZO9s4Ztxjcjr6Ejde1gBxBLnC5QSq0auTu2MtqkR67i0MAOlLLOzWLP6GG5fp+SDPLHN+rdb/uaUHbrkyh99MAUKH9RLdzQTlYeKa0VGZySopMPHt0DG/EM9FIPIRkdbRCaXXZFFEjs1V9DI/xEhBDoYCJ2FkL+QbVmpqr/IymVeta/bEzsT/U++Xb3cU5M9ofvmSYVB5vd1PY5Pi/obp35NCdYyVIbGnxDbIUN0/UVZMDPp1MncfAXbKIpz8jqqQK3mrmezVTsRJHZiLQItHF/45BhDzGUkGB6SchMvwLEUGYSNlKlJAX0xKgnD/kXhju1X399/RKOj1B9dr6rlBkNgn53pO8RnoB6GveImMNqzspgc03N/fVRLsmWAJkJEp3
*/