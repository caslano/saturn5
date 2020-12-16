/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_09172005_1146)
#define FUSION_ADVANCE_09172005_1146

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/advance.hpp>
#include <boost/fusion/support/category_of.hpp>

#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct advance_impl
        {
            // default implementation
            template <typename Iterator, typename N>
            struct apply :
                mpl::if_c<
                    (N::value > 0)
                  , advance_detail::forward<Iterator, N::value>
                  , advance_detail::backward<Iterator, N::value>
                >::type
            {
                BOOST_MPL_ASSERT_NOT((traits::is_random_access<Iterator>));
            };
        };

        template <>
        struct advance_impl<iterator_facade_tag>
        {
            template <typename Iterator, typename N>
            struct apply : Iterator::template advance<Iterator, N> {};
        };

        template <>
        struct advance_impl<boost_array_iterator_tag>;

        template <>
        struct advance_impl<mpl_iterator_tag>;

        template <>
        struct advance_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator, int N>
        struct advance_c
            : extension::advance_impl<typename detail::tag_of<Iterator>::type>::template apply<Iterator, mpl::int_<N> >
        {};

        template <typename Iterator, typename N>
        struct advance
            : extension::advance_impl<typename detail::tag_of<Iterator>::type>::template apply<Iterator, N>
        {};
    }

    template <int N, typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::advance_c<Iterator, N>::type const
    advance_c(Iterator const& i)
    {
        return result_of::advance_c<Iterator, N>::call(i);
    }

    template<typename N, typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::advance<Iterator, N>::type const
    advance(Iterator const& i)
    {
        return result_of::advance<Iterator, N>::call(i);
    }

}} // namespace boost::fusion

#endif

/* advance.hpp
GObZ2NEHeWocGHPxquad1r+Mlc1rntfvqs8+t6ZP17dIysucc2skrmWOzO8y55C/5/n/8/n6PiHXV/+3X0WWIi2GhC6iDVbJUqDLhIOLaocqbUaEo+aOZbbIU6XN1P9JmfyU+XFvXN0d5YJyg33XT69gDV5C35ezbi5rbV/GvZcUu3PFhJ//L2XNOr9zMe1e3Ppjxs1d36LIKUNCMXXoXFKsLLr3lOGlxRg3Fm2fMmJBm+tUSOp7hW1KjInpe4ktMjTZubx7xZv6p9ywwyFlWoyI/EvbrLPHEVW6zCj4W4smA8Jxf8fGKjvkKNNiRMTfOi2wwT6H+j8+2zfiSp77lK9srMSvIlY2OeCEBn0iKefJsHlV4zQXI3mPy+cyh9ToE5HXJXZJyeMae9ToE5LTBbY4ZENuDygwJCrPi5zDIXWGZ3Mo7ptTpU9YDpfY4YToFT0mSzqpP7pEjC0j5rW48xxTp8eMhHlc5hxaKfknov48PWOIamODhFxtUmAurh/zu+D8lGLqv3uHtJlyjhhKtFlS/4BFcWyRZVH9sWsTx3P/23chTZ4GA8KL7qXIkOgN3ccxVRZvpB9yVOgRurG4OYcua0ueHxSI3ES85CjTZkripsbPDkdUGVC8mX6J3lwcFGgy5OQWjhkRv6X72eGYBkMS/9vLoMmYxK21T40+O9ZQ4XquM+J0QfzKFLHr65NN0hxRo3PG2DfEHdX39FXnDQYL6i0aJ1ljLhESd4o19tkVyxF1RgzP7X1mf9MXXN5zh3UOCMt7UztRuZxpJ7XksfuXl8XLEavi2ybDplhO1dmSkxVjSt9Q2x4f3Fx9jzf/6BzH1OgQubA+WaN8B3m5o/7uZD7ZZEryztqjehtx3M76UEZYYI8juizfVr0VbdzefGqruqoP7R37O8cKbSZEL+s9ddbY42jFve7JUaXPvPvXVrXP8n31q/2E9ndci7i2zh5HtNSZkL8TyhV97nDIgXMjdSLOVzyuedxl13jGHm9rO8Pa/Rxr/4g6Q6Ir2qFGn7CxL7BJhhId5rV9oo3+nHV6HXPEgPi5/O6MY2OscmiNda7na+3dzeW6eEjf1X0E99DeXcTpuHBv7d/NuO8iJnKcMmTe9TXy1AnU26BMl1VtHtFmzI6+usxpf+1e4qSm/TYbYtvlkDJtJiStxxW2ydEW+5Dw5awV1tjjhDp9goTfT7OunwwlOhzoZ3XTWMUw87h9tifEhjzRZEBSTD0CdeeJ/W/vhpT7Zsa0uy6X7j8k6f4VziFLmRmJDf2ww6Y2xixpY5N9muxqb9nzzWfJ/U2TuuIN6XebDDUG6gWb2qVqvto3Pm9wTIU0uQeI6wbnDXquFR3XiT3QWqRMkyGRBzm+7nmDruubHh8xcbyknHNtlRxNigTniEfZJ+F4gTUyFGgwIHn18wY7ytCDxcEK22Qp0SL6EM9fNjg4r6/LrJ3PnDHy984bSfNGn5s/VHwM1J2RcJwnvaukTp/wY42RU9eChu/rlPtUiGyLl3X2OKRKh6VHOk/oMeJllR2ylGkxJKftEpNt8T/MOmCDfQo0GfL/vSDWSZOnTp/gEfpgmR0OqdJlRmLHNbbJUabNhJgYh4+yznaNwfHhnc2Zsk7k0cbB+Czf6uyx43Ge5V35Y6RezPnI4+SCFWPpM0+Tk17Ie8Dy557mQ3A8drzv+ITt/+2r0CfJMhnqzIimtcUK22TIU6XNiNCT3MvN2WKfI8qcMmBG3PpfZINdz4McRU4ZEd43L4yJPdV1Uo5X2OWICjd3/hzK3PxajslQpMmA8Lz1ziq7HFKhzf/3rVpkgwNOqNMn8Bra83NC+H//Z8MWWcp0mJHyc9AaafI0WPzf/rs=
*/