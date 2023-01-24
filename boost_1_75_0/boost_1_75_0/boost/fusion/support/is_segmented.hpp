/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEGMENTED_03202006_0015)
#define FUSION_IS_SEGMENTED_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion 
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template <>
        struct is_segmented_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_segmented {};
        };

        template <>
        struct is_segmented_impl<iterator_range_tag>;
    }

    namespace traits
    {
        template <typename Sequence>
        struct is_segmented
          : mpl::bool_<
                (bool)extension::is_segmented_impl<typename traits::tag_of<Sequence>::type>::
                    template apply<Sequence>::type::value
            >
        {
        };
    }
}}

#endif

/* is_segmented.hpp
3rP2j3Jc9jBXXidfzVF3JTNBR0j8d6XlhI/bKFdzSPIEI15BWZaVhuWwA3/eKmaCjijy2beW77xfPQtXc0jvcbvDEcXSLF0vJXzfU72taG+6qa3JI9cylseILL+6gg3S0kAjcV25FOP6QWuF60yF657E9WQGKdI7wim27MHcRT6Fa2icZiFX3gL7mU7sJ6nYr6Zh//FXpth/f41c4jtSWYnHSLzXI97bq3jPUHhf5EX3HzAQm1oVxnhoTJGPnbgW/RpxlqX3NNqFv9iKRAaHfuV8GQrLxawnOVzBsEHBOOS8K2pLD6ZgTO7BFYwKX+ntisq2mNQur64t3mwJGyHmGQuQRPcx65ili3y8V8uLsgHCvTdVW7rviuWC7hxMKzLrWyrdOb80q5F6ZdCdE1PRnV8sQHfeuYp358Uz1Fu61z7JoS3dCbJtJVO2rbQn28r22qUsQtkMZwtNkc+oVaoTM0Fv8rM8PRVe5xKveS0UXkOI12ml0V8v/AcnZub+A15LruL9Nnt6YVF6eatUiINs4xaWZBl4tUgS69296MPslb90sfkU+WSuVJXjxwmqctxeIPP2JfEWruJtlyfj7YonytH2H5Rj7mPwNm4lL8eg6epyHFDgUo7fyuW4EPayWmI5HjqotzU+wJQxuMVqsxMsW3F0v6ur/qtojYbyucWN1mZqmtvUKFqsGVzXzN1tqj0tZgy4x1YapsLuuxu5
*/