/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_09172005_0751)
#define FUSION_DISTANCE_IMPL_09172005_0751

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct distance_impl;

        template <>
        struct distance_impl<vector_iterator_tag>
        {
            template <typename First, typename Last>
            struct apply : mpl::minus<typename Last::index, typename First::index>
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename mpl::minus<
                    typename Last::index, typename First::index>::type
                call(First const&, Last const&)
                {
                    typedef typename mpl::minus<
                        typename Last::index, typename First::index>::type 
                    result;
                    return result();
                }
            };
        };
    }
}}

#endif

/* distance_impl.hpp
/rZTpEVULjsMJkMqFhyEtXmfArtqHUSwdMqfSTz9o5K9iPT3QZFgW/0Q9f+DAhTYw2omsa2QF6EJgMMcXkLq7WfzyQzAXx+poKrUCMIMrIHfCIdC6DiybjZwdfohpdnsZTmI/Xxt5BvKIDM8Q518mORbXIvP4OgcWfYNH2IuAmXoIYrZnx/sj/P++pMwLjiIucopf04JEe5ZSD1ZgAbjj9ig2MTyJIC1Si2Tq1Zkpi1q8Dicleu7kgqerxz7gldMYixbG8QhoLZM6U0e2gnDFSfd3JXCFq+HhdsIiO+s3MBUMqYy4koxxp+qTBoSqWGkaibkz1eKF1koYR9O1yT8pSWlff0ZvscISTFp3uPPWA1IryE1fFrwjHHnEC1PCOSfgZgc+tSvMk79qHvqVUyeCRfWP1XzikUPp4IlewqoGxWTzJxy6nv0SuyYqKRiFmxgQQpExj5OF0RKQJvxm03/hhEN3vmb0W452kU9fuFvaPYPE54r+8ZRw0Qf33naSHibTGhIIaFhs7mfFkHd8wBkrSnkyJdSBSJLYQyr/jbyechAQtuE1MRw+8MPyBpUuY2ea/lzDX+ugqdyWSYTMJUO+G9b9i/7IHNA7wfI9xbwnzUb6FnFnwW8nvxtjfkit07f3lbj9wXkV0fZwSnfmzGu/KKnjOk+kPnnoVAURAxG1mylTDIg1aDh/ytEnExAd4bVgNGIyxtHMPx2emtU
*/