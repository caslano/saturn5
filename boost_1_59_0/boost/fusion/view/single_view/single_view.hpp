/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_05052005_0335)
#define BOOST_FUSION_SINGLE_VIEW_05052005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/view/single_view/single_view_iterator.hpp>
#include <boost/fusion/view/single_view/detail/at_impl.hpp>
#include <boost/fusion/view/single_view/detail/begin_impl.hpp>
#include <boost/fusion/view/single_view/detail/end_impl.hpp>
#include <boost/fusion/view/single_view/detail/size_impl.hpp>
#include <boost/fusion/view/single_view/detail/value_at_impl.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct single_view_tag;
    struct random_access_traversal_tag;
    struct fusion_sequence_tag;

    template <typename T>
    struct single_view : sequence_base<single_view<T> >
    {
        typedef single_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef random_access_traversal_tag category;
        typedef mpl::true_ is_view;
        typedef mpl::int_<1> size;
        typedef T value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        single_view()
            : val() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit single_view(typename detail::call_param<T>::type in_val)
            : val(in_val) {}

        value_type val;
    };
    
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline single_view<typename detail::as_fusion_element<T>::type>
    make_single_view(T const& v)
    {
        return single_view<typename detail::as_fusion_element<T>::type>(v);
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* single_view.hpp
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
*/