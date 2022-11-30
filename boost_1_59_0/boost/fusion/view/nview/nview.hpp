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
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
*/