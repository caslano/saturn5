/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_SEP_23_2009_0948PM)
#define BOOST_FUSION_NVIEW_SEP_23_2009_0948PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/view/transform_view.hpp>

#include <boost/config.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct addref
        {
            template<typename Sig>
            struct result;

            template<typename U>
            struct result<addref(U)> : add_reference<U> {};

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename add_reference<T>::type 
            operator()(T& x) const
            {
                return x;
            }
#else
            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<addref(T)>::type
            operator()(T&& x) const
            {
                return x;
            }
#endif
        };

        struct addconstref
        {
            template<typename Sig>
            struct result;

            template<typename U>
            struct result<addconstref(U)> 
              : add_reference<typename add_const<U>::type> 
            {};

            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename add_reference<typename add_const<T>::type>::type 
            operator()(T& x) const
            {
                return x;
            }

            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename add_reference<typename add_const<T>::type>::type 
            operator()(T const& x) const
            {
                return x;
            }
        };
    }

    struct nview_tag;
    struct random_access_traversal_tag;
    struct fusion_sequence_tag;

    template<typename Sequence, typename Indicies>
    struct nview
      : sequence_base<nview<Sequence, Indicies> >
    {
        typedef nview_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef random_access_traversal_tag category;

        typedef mpl::true_ is_view;
        typedef Indicies index_type;
        typedef typename result_of::size<Indicies>::type size;

        typedef typename mpl::if_<
            is_const<Sequence>, detail::addconstref, detail::addref
        >::type transform_type;
        typedef transform_view<Sequence, transform_type> transform_view_type;
        typedef typename result_of::as_vector<transform_view_type>::type 
            sequence_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit nview(Sequence& val)
          : seq(sequence_type(transform_view_type(val, transform_type()))) 
        {}

        sequence_type seq;
    };

}}

// define the nview() generator functions
#include <boost/fusion/view/nview/detail/nview_impl.hpp>

#endif



/* nview.hpp
Vg9KO/Icl7ARsLI372zPPbZT/CcVoAF8+FWhN5Hu0gOtbjyepEbWXhM+sEvw6r3FI/1xD1jf8rplS0w6WYBW93KCHwZJvb5gUbdmcb/7U8baYO23BcbZAitvge22kKZ7tH8niB+OQgI8lS7lxwHLDdx3C3QPR4EBngrVHK49g557dn4XpCleH2Uk8sCb2V454PA/2c4TY/+9J8CeH1OycgZbhH/EwnjSrD6LpvoOSXIubuNdy9/+Ksl7+caaCrxquUDT/rK/geOjEUYpJcKGlRx1+G9KzOBR3LkfA5OyLan2sfxEBYAMw+gU71EFGsCPBl7ZQ11fuXnoPWw3iBb4jgVaQNTa8/GDb6ONnyEm5y7zm+OAGTOuabBQZrlEn6gTICVCI8FyTD1+LwFTapRv1gI9KDmOt/38d3pY45R5U5jV3RldNc8076xj8wC490cp6vdqRxf9k7n8gpWeRXMjUXGubhLRP5NLb+HYMUsyNOYRhS/Wi83dhbbTLT8/15G428x50ghqWajF+xRXbrCCC/3K89k34TVoMID3JowzU9NiAV9yRQF0+3g6iL0TUELjy3m+KIpZNYpdUQ5pvM0aOso27PA3lD5UfEhZkm/tnX9djcFMju725T/4znuOJZflee/lfh8mAgjgfzIQnugep/YUSePN37mlo5NTlMfAl3kIcvafMHELvI66HJ/lGpIndr/eHPbN5aozIgS6
*/