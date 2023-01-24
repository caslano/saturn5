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
obE4bbvedzrdntMZIRWqaF8hbaK5/HVIpJquA5lqCuasVHC/rg24T1/HMj5XHsvONNWreNtHuIZVdYAjmaU8wRWHVWTwXwXG/yrKso9fSggq6agXD3flOr2/u6ppKJ1R1C47Zf9XE0FmjLqfrA5g0wnwY8i1oVx7XUF82bNZrl0vXHMzYsDrh+PWd0kfjtnbGKs7Bm2oCMWj4pa5iGSRhOV8A1U0/X7X3nqvAipoaGXL+skqLydDL1ySbSr9sYuS2U3jLWd20XgKIwnMz3dtR73e3MOmVaT+Q57XGUB4r42pAMMbXHs50CKvM9gbs5sQsvnbyfAo8ws0OBZYsE9zeQvIu6IBOp3OGE2DwRSGOS8x/yv+tbo3rSQVLEVYzW7impXjBn3QUGlm4MTnmK/hQEx+qrtoyq5ygxEjVXzyazZOK7BDJxN3kauxKQul7B340khop6zwH6QLhEyjC6EmfrDV3Auf2P4dtvr9y11owHemJpRSkupUSVlnCZnMfztcY9Qvyt2rgM1VncMpN4HYONxTrn4xajHdVuzkGKnMPI0fLMuCDW+W9l2/bFK4qW6uBsKWLVQEgwum8D+Zn3cDPYfRRs+TgqZeDpGbEN3nqLyn2CuKOLXN4+qgPAOcMATDGMihBguo8zykIZVm2EWN2CYnliu5x9Y9RVdq2dZEkZ/sayqPln9DtSvJ+WUTrfKm2liTiLA6WAIAMW0k
*/