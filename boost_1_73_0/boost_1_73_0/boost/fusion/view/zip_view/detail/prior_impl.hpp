/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_20060124_2006)
#define FUSION_PRIOR_IMPL_20060124_2006

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;
    
    namespace detail
    {
        struct poly_prior
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_prior(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;
                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::prior<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_prior(It)>::type
            operator()(const It& it) const
            {
                return fusion::prior(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct prior_impl;

        template<>
        struct prior_impl<zip_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Iterator::iterators, detail::poly_prior>::type,
                    typename Iterator::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& it)

                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_prior()));
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
fGUCMy5VOGBaMdAr2n9+3OSwjinnE+LTQqzWfWFPirPS5DC4brx2SJgH1yhRpBwK3U374q1t7EOPZpPBB//03bR/7tGz2m8cIHhfWQDymQEQ8KZ/2qnTBmcwDKw1EYYW2m8xekv5r0pqY/HQsHuB4FO8AiBxIvNsmUzaDPKZs7qWhy2GOglEOkhyLdu69vPrepbbK5GTZ53XXNRHb/tns6HL89ftNhCJCtEEQSwDGLnlIrTxji6AuZMzQFLXhqRKmcrM1HWa8iKwdyNZ00KimDTvN6is7WZCVd3bLWPy4ZEussYf7yGPanqNIEyjLt8su4tvuJL8G2wF2G2WZ7Xy/eNhZz05W91bV3Br+Zy9PuYcAZKxh0UAtbDdzJ/Zp/HgfWcJ17bm/f7p6XQ0fjtpcdOqgG5yFaI908LnmuB+an8rDq9pv0c+eM7gsJaZRh11hXIZcEDY3tmwdvQ527FlgQZuH5NQ/EXtCPScUH4m70wDSAGwHjUa/cO2gI1kNp+eDcd/ubJq9PN1JFLafRF6NBj3z4e0i7VnZ8P/Wj/4VIKlr75F6SNQAdR5/ZB0RDsvcS1Pduo6HizhnfcJv26qtlAeu4mCUP+WedTGdaez6eKuRtiWq9OU+RPuo9YTd4hbJ3Ln3XectSwvfG1S
*/