/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_ITERATOR_05042005_0635)
#define FUSION_VECTOR_ITERATOR_05042005_0635

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/container/vector/detail/deref_impl.hpp>
#include <boost/fusion/container/vector/detail/value_of_impl.hpp>
#include <boost/fusion/container/vector/detail/next_impl.hpp>
#include <boost/fusion/container/vector/detail/prior_impl.hpp>
#include <boost/fusion/container/vector/detail/equal_to_impl.hpp>
#include <boost/fusion/container/vector/detail/distance_impl.hpp>
#include <boost/fusion/container/vector/detail/advance_impl.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    struct random_access_traversal_tag;

    template <typename Vector, int N>
    struct vector_iterator_identity;

    template <typename Vector, int N>
    struct vector_iterator : iterator_base<vector_iterator<Vector, N> >
    {
        typedef mpl::int_<N> index;
        typedef Vector vector;
        typedef vector_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef vector_iterator_identity<
            typename add_const<Vector>::type, N> identity;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_iterator(Vector& in_vec)
            : vec(in_vec) {}

        Vector& vec;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(vector_iterator& operator= (vector_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Vector, int N>
    struct iterator_traits< ::boost::fusion::vector_iterator<Vector, N> >
    { };
}
#endif

#endif


/* vector_iterator.hpp
BcK6PCJq+5RxsOD9knezDSK3sqqAV9P906zOrGe9GRvqrDo6bYPL8DKDYT+VlT8eY8CyDRPgmTHmq7qi1MRj66L4gx/tCVmd7T2yNpywJ+T0PmFvlVONKzZqAw/j8wgOK6dzAAPQan3486zeByZTZrVjZayq48mtrA9s05N/zCnGxFXV8RFD/ELfvVZfll3vEYQhFN1JDOmOlXXnEHSnHXTnV+rOId4dB3WHNdWZNRW4C3k+TdNJtj6BcYYXx0EGGGZ4kWljL/rBscfJtPceAcydIXXxvMJQleFm/3rJd+/bIcEEGA55p55iXfNSfMy4erw8n3UKgihCPPWSmWyEp/gNbSxpNoTgFBEJ1F3p2NqCx6ATs2swsnaOqvz2LOd3rJK+gNg/3Rdy6VDzPpwwcTzsz411ZAN7hz9frSPb2Gr++4k6vn/bi/2LelgBw+HX+hr0MKBxWSlqtu/eOkn2gQ4AcQIiggNoquvUvAygaTKTcmJW4qF6Th3bmxfh6d+fZpD+l25hkx9AGob7a94WuNZ4ryLJy+t42F3/KEUPUp5Vw5o+zEZdozrmbIErxrNZcToMGwViVpWiPlSP88JKZFJtrHfjqzBGyqg6igGBgQiAgLRsjoCkS3Tz6+fNohoteybETYDwB/VsFWv0COhyvb1sOttVjFGXf+WO16K0UnuPKzhFB+CDliSCffA9Rx+wsRLRWEgoTrirfzkN
*/