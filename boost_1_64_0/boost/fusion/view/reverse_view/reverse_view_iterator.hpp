/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_ITERATOR_07202005_0835)
#define FUSION_REVERSE_VIEW_ITERATOR_07202005_0835

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/deref_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/next_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/prior_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/advance_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/distance_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_of_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/deref_data_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_of_data_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/key_of_impl.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    template <typename First>
    struct reverse_view_iterator
        : iterator_base<reverse_view_iterator<First> >
    {
        typedef convert_iterator<First> converter;
        typedef typename converter::type first_type;
        typedef reverse_view_iterator_tag fusion_tag;
        typedef typename traits::category_of<first_type>::type category;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , category>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        reverse_view_iterator(First const& in_first)
            : first(converter::call(in_first)) {}

        first_type first;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(reverse_view_iterator& operator= (reverse_view_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename First>
    struct iterator_traits< ::boost::fusion::reverse_view_iterator<First> >
    { };
}
#endif

#endif


/* reverse_view_iterator.hpp
gJd6Ackiyg808Q/av6RlFPZ39GpJomGOt68EaEQCekUSEwhJIkj9m0moRp9Y19Qft2if3i0ux3ONwHRUUxXMsPeh09qb2nDn0J7bxVtk46jsjJHoGrQrDQ/AET5Gz8uyPIJsuOjQrGuvbTOWDznhFe7zV6w0N1+lsOO0RnLrZmtPmB8Z3M4y678lJPZqGPk6JpNXKgJ2Xo7bRzAw8VmrNQmjuazLsgl2i2ONZ7FhN9nkda6jTFf1XyGXPv5wH2ApbQPdZBVeHEC7YisC65tOQLO+EbuvMKQIMr09SLnDNFB2fAohJ4gujDebeFVR/F2+tz6SKcO1CmX2oRCcB0RiPeOdPGjvk8OR+C/0LI163aGB9m+fW4cuTjZcZ8SBwB5zbUC9BRP9zJmAXCibIuuE3WtviImziOyaH/Dmqs5bFdEc+cSJ1dTZpHUFT1J/rYPEQRoFpLJQeAmYUTbHt52yr4SemLx9L7BerCBaN8YKMFZAhpXuGRkV7SGss7iE9cWOYrXF2dhI9RNl0I7tftRpqfEwgmJFDx9FIWXTP5N6693MQn4p32ZGU6JK8g==
*/