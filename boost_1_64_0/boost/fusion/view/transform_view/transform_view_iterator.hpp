/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TRANSFORM_VIEW_ITERATOR_07162005_1033)
#define FUSION_TRANSFORM_VIEW_ITERATOR_07162005_1033

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/view/transform_view/detail/deref_impl.hpp>
#include <boost/fusion/view/transform_view/detail/next_impl.hpp>
#include <boost/fusion/view/transform_view/detail/prior_impl.hpp>
#include <boost/fusion/view/transform_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/transform_view/detail/advance_impl.hpp>
#include <boost/fusion/view/transform_view/detail/distance_impl.hpp>
#include <boost/fusion/view/transform_view/detail/equal_to_impl.hpp>

namespace boost { namespace fusion
{
    // Unary Version
    struct transform_view_iterator_tag;

    template <typename First, typename F>
    struct transform_view_iterator
        : iterator_base<transform_view_iterator<First, F> >
    {
        typedef transform_view_iterator_tag fusion_tag;
        typedef convert_iterator<First> converter;
        typedef typename converter::type first_type;
        typedef typename traits::category_of<first_type>::type category;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view_iterator(First const& in_first, F const& in_f)
            : first(converter::call(in_first)), f(in_f) {}

        first_type first;
        transform_type f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view_iterator& operator= (transform_view_iterator const&))
    };

    // Binary Version
    struct transform_view_iterator2_tag;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2
        : iterator_base<transform_view_iterator2<First1, First2, F> >
    {
        typedef transform_view_iterator2_tag fusion_tag;
        typedef convert_iterator<First1> converter1;
        typedef convert_iterator<First2> converter2;
        typedef typename converter1::type first1_type;
        typedef typename converter2::type first2_type;
        typedef typename traits::category_of<first1_type>::type category;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view_iterator2(First1 const& in_first1, First2 const& in_first2, F const& in_f)
            : first1(converter1::call(in_first1)), first2(converter2::call(in_first2)), f(in_f) {}

        first1_type first1;
        first2_type first2;
        transform_type f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view_iterator2& operator= (transform_view_iterator2 const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename First, typename F>
    struct iterator_traits< ::boost::fusion::transform_view_iterator<First, F> >
    { };
    template <typename First1, typename First2, typename F>
    struct iterator_traits< ::boost::fusion::transform_view_iterator2<First1, First2, F> >
    { };
}
#endif

#endif


/* transform_view_iterator.hpp
YdUVFquwegprrLDmCjMrrJPCkhTWS2HJChuqsJEK+1JhNoXNUNg8hS1U2DKFrVTYOoVtUliGwnYr7IDCjijslMLOKeyiwq4pLFth9xX2WGH/KOy1wv5VWKEU5+alMJ3CAhRWRmGhCgtTWFWFxSisjsJMCmvKbKorILOWCmunsESFfaGwPgobqDCrwkYrbLzCpjg1VzGL2TRXlwK2QGGLFfadwtIUtl5hWxS2XWF7FHZIYccU9ovCMhV2WWHXFfaHwnIU9pfCnivsrcKE1bm5K8xbYSUUFqSwcgozKqyKwqIUVlNhdRXWUGHxCmutsA4K66owi8L6KWywwoYrLFVhExU2TWFzFGZX2BKFrVDYGoWlK2ybwnYqbJ/CHAo7obAzCvtNYVkKu6mwuwp7qLBchb1U2HuFuQ5zbh4KK6Ywf4WVUpheYRUVFqGw6gqLVVg9hZnB8POQca6uoltS2E00i8KsCrOBFWH2z6JDj9HsCkuTxqTPZsBMR/O/Bi3MltE8B/iP5YJRxLHP1k64xUO6+e9zwEqxz6wsvd4VR8sE0zMb7eX6DZq4CF/TZzbdJ/mygF+uoAJ+ecA/JmEyjcx/zkLTuTg3vatzi3JzbqZCzs1c2LlZ3J2btYgzE8IGEBYiwMwm+L2ouL5jOzRzlBCdBJguz3y/ukq2Byz0k5k+WZ/i3VbmWS+RDdYhPw4+BRAdV3fbimauJkRXZv0d8xflWVJPB1iV/DELiYHiwlrrCLTXYOHM9LUXr0eLqi5EfWbPW7Z1oNnAqjHrmvt1flxyTweYT75BaXsf39SiVZ6liEywiHzzEFYR8ab2uTyDz5eiNfOEPynTLSR/nbB3mXnB6899ft2IfUgFq5xvRWEc0z3X3RiXAdYyv0fe8PqXfysvNO8YIQp9iov6ZP17HGmKppPMt0j6BjR/yabW6RWHFiTZ+JbmgWhlJIu/s+Qmml6y0x2edEczSpZQ8/cUtDB5LclVu6FFSDYsc/ketCjJsifvOoIWI1nvCRUaoMVKdvzfff7UIzDcS2Di9t1H5dBSwUoxG26tWgZtGVhhNmaj/y7tibYSzOWT6cC0X2AiDaw8G3P6tVQr2ikwX2aff6g6Ec9YNhjuJR94nXtj7508ixRBNbS9VEyMFl1PnluYZ1WFuYaWn6+oLsLthz6gTauh1QVMPDqacQVtFpgniys8+Y4NbZlkjaM9OqOlg3kzG3Kr7+j8czRqTw0tB50YMHi07uoYtMc1qJ6frOSQpHpor8G8WNzTlatf0PmrqV0n/OBP5gc0uEXXT7BaLnnXM2i4+MOtbR20PbWE8MiPAxP3wub6o52SbOSMI/9Fuwjmmr9OMJFYolgAWhaYO7N3o09fQcsGc2M273j6CLS70pg9x2w8hJYDFs7WUmNp9gC0MrEF48be3FgBTS+Zvun2DWhGydYYp32DFibZnJynb9EiwAox+z50mwtalBS3bVC12mgxkg34YB2NFgvG61Jx+YV1aHUlu1B130HqrbSWHh8KB6M1luY7FJ8zEM0Mlp2/J0rC7x+9NnRGs9fR+gcmeoyc2wltGRjuCTCxvtf4LLR1YIVZ3IpFJXehZYB5srg9o355guaQxly9+sfVaJlgEcwePV+/lvb850JE5d8fAuD3xW+GnUaLB8OzAia6FPs5HC0RrAqztT91nok2DwxrDSbKukZSnF0ynyIbX1NdwEz5awkSYt5z8Wos7d3Pce/mmV+nht3R9HWFKMUsNNRvC/UWrDSzlUFr6uNaLGBYl1LwJ3XS3fvQWsAi8620gP/37B8P4/UzE0yXb2XgdXODMZfQcsCKM3tW7uQqNBFXMO7lUp8+aEFgRfmYx6pNQwuLA2c=
*/