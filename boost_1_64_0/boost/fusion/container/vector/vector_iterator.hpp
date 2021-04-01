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
USAo/qhss+1iToJJUWWwtFrIQ6g2bz1KEsBbHpfefJWYw8pelpp5IwwBc4bV6F71rzniQ4/Ral3QWSdpWSosdgBjAU/9QgfvudhNuPcdJlt82cTk6Q1/XHKXrf+mPa3JLUwn879FtZEHSGou8rU4WBR1inof8bGShbAVmIYITTYhAAn4QyNu1Zb5rmZPDAFFhFn07VQKJrAvpRXQGdVPKm++NAb4TvzQ2e7d7VDjAozNxjbBER6AFcPT+LtDKiqLz/qtWXTrQlQ9hQQFW8P69NU+lNfUjhXBxfehin61tSAjXS2kEJ6ad/AOYJMf/2Hl7zmsAX3YbSHHF8Hej/I2tIn0DIP08QVWnIIWtfHK63HdjpBEc6hVingGEAu5g6S6pZyn0CGnsHsOD+/5gj011fh4JyyvsEop+/9nyPkepapvD1sRbLwuNIgd64/CQDXPdphaXZLyAfWH7oNrb6o+MUmTao8S1stwpXtDXUWE6/h+IYBp4HkgR2j80qgUh4zZmXsxt3wLPLzSTffHgP7FlNQwUk/gBQC5Je1Wv3HsfTokL3MlF/IjUDpj3w==
*/