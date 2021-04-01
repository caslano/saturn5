/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07162005_1026)
#define FUSION_DEREF_IMPL_07162005_1026

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        // Unary Version
        template <>
        struct deref_impl<transform_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first_type>::type
                value_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first);
                }
            };
        };

        // Binary Version
        template <>
        struct deref_impl<transform_view_iterator2_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::first1_type>::type
                value1_type;
                typedef typename
                    result_of::deref<typename Iterator::first2_type>::type
                value2_type;

                typedef typename Iterator::transform_type F;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.f(*i.first1, *i.first2);
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
ZJvg++WO79F511rR/gePhakhjeZTCRceXw+eZ2iCo9fBxZH1F7ZqqMTiE/dd7voCy8ZPUKQJjKwZ7leUZegqsYW3iK1oKGUeMnug6QbDF5SPbrSdWAlBqsqm/bmutdMv2ITahZ29wHS7pqQz7FjmCcOqHGADgILi4YsWwydJeZhqMUzJeqfJN8RlOL0LplY391LAqfI+4gYtrr+nG3HWLkDfx1A5wjEeMd1BNejtRVn8zE90dq0BxqWAkCSs3IsyzjB56eWFi6HtE/n/adMVwEmjv6whQ7Vc36HGbIWFfHzqqx7cW18xbpXpiywfOw7OzW0FSkfhrafRMWinB+7Kz/3h5hH1MBuOrZCvTiRIf1tAAIwiqAuBrXctnRVcaLjfE3XJGWmJ3rwukK4e/Nb/j/Ap7TNCnPAPh84Ys4tSWx3o20S0KDqYOFcuv+cUw5bZneiBXNx3IR80sE83tKXoQZCcTOkndoB/O/I4SsltOSF/ytJyCIsmqvRm8HYnsaceHk9YpuAgc+wgfx7YhW33uQ+TbO6cAlvDppXHXZTTKD9ubtS4Dwp52nr+SQ==
*/