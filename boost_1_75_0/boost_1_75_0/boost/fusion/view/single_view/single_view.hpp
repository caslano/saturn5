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
AXfrgdzw7sA7WU1RrmGoTPh9V2HG6gXgk2xSkPKFCeUJR0gfRIO8IddEOE0Tn85tvNKcZzhltyrhPv5+Va242f5PTWEQ4VyjMcEcvzW24Uvjqwvh2SRI+ubSOcSPfyWRRKSFEn9HnU8dvjZaWzFFXtEJR4XnWbsWgBkVNo2hQ/LOQ5E+4w6bqjhPa9cwsONMCAOKqoPbV12YjDNnh1m5HoDpFjmYT22/uI7p81Qnht6EilS536aIqdB/Hqxwj22M/qqo/xcsLNPTuYU9VWzUlDz8W7KFRfqZMp0ExwBPy1d+Bvqvk1fRJFtyS7fYnv6qv8PO7trpKflW2LBKZ/dp+apnyzemn11TTGgLsSgf0SSdbB+J94duLNNbw/PekqxPy1d/BvKV6RRt6VN5Q4O8tCbtIjqxSVbtlm5OlbTLKrta3PmnuXzNZ3D+hnTOm6T95nQDuvQOb7IAW3p/izz9Jd3KSdp8S7I+nt2n5WufLV+b/r1X/qpL+qVI1uImb6dL8nW603OyGb088jV5bOMlnsnl654tHzkeop9R8cciL7dJOm5LUq2yBli6JVmdVesOl/gtl6//DN5flSx9lyJu64Na+b8+nTFybrs81Tk9wZZWGvX7r3t/w7PlK9O5GpLe5V3V8orJr7G/UzSH/8ytZX+LdLvyeOsq3/P9l/nwJGvp0zL5UpX0X5FWIV/byfsak3To6DbZ4Nft7/P9
*/