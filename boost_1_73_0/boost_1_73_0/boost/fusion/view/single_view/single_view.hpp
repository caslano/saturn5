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
2m2T5Ui2TD3ObclmKJbTaTof/3g+9WaXvx43wloF71naw1gC/vFpPZhwKxo27K063JarngSra8aR262lZhTdaB0ks3YaPtIzlsaXgwpgYKON6t+/YfPw6Pdnzx66Dwc9nvA3dgDxiHU6aFURSrDy522s7kYB1auX67IUwEGcVUgOPRw+vIHekn5G89fn54WJDIchklTObEw4bpwGp46bvu8VJ9jk9atz7+xisfR+GS8nZ3TSWplf2LXTshZlL7VbR7eGMuoSIfnNDIW3TH9bBDg+4aOhPjcOxi89PqYanxx6UDJmQM/pUSeePT7tJdUXzRx37IBnrgbhLE//nbU2Kd/wTfTPXGb2KpkIPt0e18O6IqrhK6eSPIZwlZM43KqSFam3OXKL9NxsNlDg6LRFjbo793HDvcWNlnhBDr6kdPVaMl/RUYHSki5cvMW153s8qoSBn+4lXf8qPTzsO/RkMKCPVnZPuLarPhdh3Lu5/z9z+/YQbNLcsKaV530KN1J3b7+b7Xl8G2VwFw0L/vGVqjmtcrCv6LeajCoV9hjwA9gsLwi4hYnIHG5gtPDQWq2eE+o2lrqBQXsnPh5t+EsHoNAtYEqA6gJWt/ueHB02Zp7uIdIh1afZnVmojyBU6hZLayB7KFUnVEuybfP2
*/