/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_20060124_1933)
#define FUSION_AT_IMPL_20060124_1933

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace fusion 
{
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_at
        {
            template<typename T>
            struct result;

            template<typename N1, typename SeqRef>
            struct result<poly_at<N1>(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::at<typename remove_reference<SeqRef>::type, N> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_at(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::at<N>(seq);
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_at(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::at<N>(seq);
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
        struct at_impl;

        template<>
        struct at_impl<zip_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<
                    typename Seq::sequences, detail::poly_at<N> >::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& seq)
                {
                    return type(
                        fusion::transform(seq.sequences_, detail::poly_at<N>()));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
d98FaFlgnswaH4zRouWBKZmtvB5XCk1Rwvws7dcPcEezB+O5NDi96SGam7BmZVe6oGnEmsZvT1LRKom6htkNqqEFgfGsv/TJrUF3AozP/YQpmeauFebX8nZfNJ1Ys8Waqt3RosDsmGkv2o6luYNZszXLtnryAi1B1I1Ksh6FlijqwiOUBjSjsKo3qlJmSWCWzCrvanATbaWwIdc/JaCZRNa9VOdqoaWC8bmP7NHtB9oRMYcE91uz0U4LU3x5HYKWJfazyQqjO5gjrIv9g5JoeWBOzG6lLM1Fs/E2f1ae3iw4iqYWdq9y+Da0ADCeZ0aTo4fQAoX1bTdoD1oQGD/L5XdznNF0Yr/vS56EokUJa9EtywYtTuy3vpl1OFqCMIfOt5uhGcRZujzJmYWWJPb7a8U8ev6ShZ0dMfguWprYr/Kt0zXQ0oVNPuMWjJYB5szWnOiY2pxmK/YLXZYeQ7MVltMg5jSawsd8TZ/Rlf6h2YLxuqqrx8yn2QqbFfygOs1PrLmy84I6ND9Rt9bh4Fuan7CiW3xb0/zA8DUkCKxVzP0jND8fute/LSvyexDaFLCirG52GY8laEYwJatzbFj0GJpJrDkuq5MWLRXMjtnBykeyaX5iTb9VLcqgZYJZs7Mcm5uWg3ZDmG99tRvNFgz/3lNdsDaulYJpRr6FnxmCwa4f/ltDWYMFM7N8V2PqH9tpaQILcvzzGaWexU7LmnXfrUZLrUp//v7b2h+sW+2PjVDkgCVY/KlraFFF8enXjz5/rIoitZqlItv6jzWyqK5oF5u/EE1Tj37f/W0vh30d+MeqK6LAcM0Qi8GKL/+53uSPVVMENrBUxCr+WGOLYYp6F97tR0sFq/1nzd/2eMHIH3+suyIPLKjIn7omFpUViyc41PtjcQpTCHy3sPpjTS1qK+J3jTyOZmxGef62YfPm4P8LVJEFhucMtRiqWFst8heaqYWlQq/4Y83Arpgsu/02OKFKW3iWFhZ9FJqSI3Ro6a0o69+2xnKhGi0PrBSztYsXX8X9NGGWirT/76cF2zt0xqU/Bo99eOE5wyy6Ky4suNPyjw1VZLUuPGc4WI8dM4r8sQGKkDaW9HcSW1uEKibsfdiFrC3l8tsW3Y1rj5YAVp9ZxKiWP9HSwaoxMz5UnvhjQxQKXeFn7zYWvRUFlklpaEFgSmZjlZPy0bRg9swa27bLw/70bM22cCduq/y6ohnB4n6b7rcNrRr/Ek3TzlKhZTaj54NlaAlgVdiawyOfnkNLBSvHLLxpkd5oOWDlmb14Hp+Bpm5f+L6iAzNOvWOHFgjmwMzp6gdntBBRd9Erfxz1DqZiNu91g09occL6JyRWREsU9n7neBOaCcyFWZ1Sdw+jpYEVZ9Y9ds10tGwwZ2ZBKTVroeWBuTNTKfdGoKk6mPfXbduiLWgBYPwsq0YWOUu5gLkx2++4bjflIqz961kWlAuYL7OdXiPC0JJE3dJPU9Np7uIsnrfK+aFlCLP3iW+JliPWLDjlmYpWIOoyEx9HUy4d4Wc5ZoFNq1+kXMDsmb3dY+iPFgTmwOzyWAuakRaMz/1x7XUb0KLA+IwSemwci2YQZ2k8eQvNKAmMz8+1TLMmlJmw4lsWFFBmwlxqX2pNmYF5MqtY8UUOmqKTeWau171D0NRgHsyaPc3LolzAnJktjv1VHk0nrFXdqKZosWLNzk330T1LBOOZ9W7YKxMtGYxnndHtfBpauqjL2vQ4nnoH4723re5XnXrvbH7OKoMuzaHewfg5HzTc5Uu9g/H9tPn/DEfTizU/nDrnjxYHxrMu23faVupdrKmclqeh3sFcmSUG/kql3sWa0YM/PULL7izuZ7IXnSVP7Pd5bJ8=
*/