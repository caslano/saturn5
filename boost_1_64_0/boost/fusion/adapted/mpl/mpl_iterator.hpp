/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_05052005_0731)
#define FUSION_MPL_ITERATOR_05052005_0731

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/mpl_iterator_category.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator_>
    struct mpl_iterator
        : iterator_facade<
            mpl_iterator<Iterator_>
          , typename detail::mpl_iterator_category<typename Iterator_::category>::type
        >
    {
        typedef typename remove_const<Iterator_>::type iterator_type;

        template <typename Iterator>
        struct value_of : mpl::deref<typename Iterator::iterator_type> {};

        template <typename Iterator>
        struct deref
        {
            typedef typename mpl::deref<
                typename Iterator::iterator_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator>
        struct next
        {
            typedef mpl_iterator<
                typename mpl::next<typename Iterator::iterator_type>::type> 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator>
        struct prior
        {
            typedef mpl_iterator<
                typename mpl::prior<typename Iterator::iterator_type>::type> 
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator)
            {
                return type();
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef mpl_iterator<
                typename mpl::advance<typename Iterator::iterator_type, N>::type>
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& /*i*/)
            {
                return type();
            }
        };

        template <typename I1, typename I2>
        struct distance : 
            mpl::distance<
                typename I1::iterator_type
              , typename I2::iterator_type>
        {
            typedef typename 
                mpl::distance<
                    typename I1::iterator_type
                  , typename I2::iterator_type
                >::type
            type;
            
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Iterator>
    struct iterator_traits< ::boost::fusion::mpl_iterator<Iterator> >
    { };
}
#endif

#endif



/* mpl_iterator.hpp
sDxjDr+KZTpusYaYrQt8DObpCl+BubrBD2KxbvH7WKIzS3pjFyzQBT4GC3WF78fUbT0Db3+rPdV5vh/TdYf3/It90SWu325tdfUOvtNa6fKy3vjqXd49jfPyu+1FGm+ac4+10pV73f9+75v6gd64+lFrkvqx3mhi6HaegQste6FL/N3H7Z1u8ONYlp6ThzzhHjrPe2CWLvJJmK2rfDXm6gY/jsW6ze9ioY4nrSfm6QIfgyW6wldggW5wrHIGtnMv3oAxuvBUb3z+7/ZRV/mzq50B3XnGb9c/nas05wX//2qtM6Cb3PdvZzXN551etp66xGdjqq7xh+utuS6/7tkxT9f5MSzQbc53PL+u8vNYrOPN3hiBJbrAX9/YG9XU7znnmKTL3MAy3eKd3/c+usgXYY1u8BWb7Zdu8+4f2CNd4vlYn+bwzP/Zx9S894f2Qpd5ATancd4n+mLo9taTz8cwXedNGKQzW/TFlzFWl/iBLfsipwtb9cUBKKRxXo6i7vDaj/bFTN34WF/cO6QvSmnOx/ti89Z9MVVXhvbFPZig29wZ0Rd1XfxUX5y9U1/M1+Wd++KkXfuipguf7os3RvfFIl3frS/e/1xfNFIX+uK7e/TFUp3fsy8+3KcvmrpadJ+D+mKVLn6jL54t9cWaNH5oX3zvyL7YoOvf7Ishkz2rLvBx2KwrfN/RfbFel4/pix9cah2G2buFfXErhuoOn3+N99VN/v613kXXeevrvK8ucAOTdYs/RFlnFvXFy5im89f3xU9R0TW+FTN1k19BVccf+2InzNEFPgI1XearUU/zedAN1kfnuYMVaf5i/35jX7R0/KkvzsPg4faFX/pzX2R0odEXv7vZmptTvMVaYp1u89Db7G9qvvkOZ0BX7uyL05f1RV43+fi7+mKUrnHj7r7YqIvNvrgGq9Mc/ss9fdHWcW9fHIqGrvB37/Osus4fX94X2fQ8fCWWps/yygftqa6tcPYe6YsYbv7KvhjxqHXQRT4Rc3SNb0dVt3nI36yzLvAhKOsyn4sJusGPoZjm84jHvG+azycjr6t8Fyq6xdu07K/O8+EYq8t8CUbpOj+JmbrN2z/uDKT5vB/m6xI/+bS90dVnrBUW6QZ/8lnrrwu8Em0dz/kOYrUu8QK00nzejKbOrOmLKVihK7wMS3WLJ/3TOmv/AWLsjoYu8mEv2C9d57tetLZdrvOSdcJgXeXXkUnja/viJ+vtkW6+7rvZsQ66/N++uBBlXecWZup4qy92RF4X+KdvWx+deacv9kVBl3iXd+2FLvN7KOr8RucTY3VxU1/8DBXd5APfs6e6xju9b211ibfd7Dyk5jrm6Or/+mLPD50HXecxkYv5qbfMxfitclHXFR4+KBeLdJEvQEM3+H9YqvMfycUP0NQ1/gdW6MJHc/GtwblYpzt86JBcbNYV/to2uRja7ZqfyMXNGKRb/Pz2ucjr/PBcHIzV6d35PLR0h3foykVbF/iD3lyM6da5XEz5VC7G6c6Oubh3lHfQ8elc7FTIxUTd2D0XG8fmYpKOvTwDpugKv4bpOjMuF4dghi7zN/bOxVRd47n75GKhbvHwYi6W6Ao/89VcLNbV/XKR+Voulukmv4Z5Og7Ixa6YrYt8Euam+fwgZunChFwchwW6wuO+kYthWc98SC7OmZSLnG4ekYvXj8zFSF38Zi6exPJ0/cm5KB6Vi5W6xtmjc7FGF/mpY3OxVje/lYtdjsvF+tT8+am52KBbvNv37Iuu8esn2AvXL03LxUUn2iPd4e98Pxer0jPzWxhjPHOSs4DRus2F6dZcl3h1JRdlHT+2nhinK7z5VHuhy6fl4oWf5WJamn96Lj6clYtKmnNGLnY=
*/