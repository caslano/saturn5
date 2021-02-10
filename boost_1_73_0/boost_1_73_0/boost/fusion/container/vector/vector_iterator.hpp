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
6G1lqkr78VIZnVcZpYLgejiiMB6iOQy2qBEwo4RgKabY2+YtLvH7EF6trzPTu456CDqhlzOmLvo4Uf5hO2amIDvGiy8GJR1tA3jbgqC/8ortrbYIAUvJ/aDweLTrDkxqUg9u+Exc8UYBXTkfxfHhXJKWdHLG2V1tDvXRn728RmTUHRy3VS84Jo0DSHDgFeZhk2hkH7VdD9sbtjdVfjGW9NQ4t9r2m0kLgvpCXXDxuM8gG4X4gDmwY0lFhTIh3eCjcklHkiiVQs0rQ3+RQkqUpAWnGF2Q8qABCUyNTXkMChlpKySiHj7G6gUqMwJGQp7O52ux6GwZOzqdWo9W3P9obAFMVp0m9PgQZFyooghwYwYwC/qSoxZv7rQaqcG1d5gTm9E4vxIG+jvzfUTSX3xJX9H4GzBxz/tVi2FfVRTFmMs7nlycHXFFu2GIZ5I5A6rBzLGq519h1UujNtryTUPTKhyro1HDXNqM5e0QdjVu4eLIDT151H4tHjfedGVWiYg/C9y3VX9r1isvbvUiVFVvQbwGg4EY8BMXBijdB05g5Y9T30SZ+LGqyayoHTnL7Trep/+k3ZZwvmcBZ9WaI6ccVRO8uU+6zNVA8megH2mgoOkB796F0ubY3W8ETN7l1+Al1XEMEmkeWVWUWSBb
*/