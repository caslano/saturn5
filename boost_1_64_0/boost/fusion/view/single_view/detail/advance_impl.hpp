/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ADVANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/plus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<single_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef single_view_iterator<
                    typename Iterator::single_view_type,
                    typename mpl::plus<typename Iterator::position, Dist>::type>
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.view);
                }
            };
        };
    }

}}

#endif

/* advance_impl.hpp
qOamdAbqQFlAfnV74p7/88mwNtWcj1vuTq6LfkQova2wFDO35KE7u3r5AbKZ0KQ20DCDc97uERsW619BgxHLYjakzj3gWO1lteJDAt9h32Y8XMYOa0ZJ8+0fBWUPsQ4fpjrwu57jpzoURWmOZ7tc9lCOhUpVo+NoAFWmD7XGiVt2OhSPcK6TIvcnRimBEir2txyeqpbXbMKzrT2EvQCuRsyBjYQE1bJ5QF7PLJBQ82/TvoZ1UlY0OFLCz/w343NiXCIGueUKy5YL3iiHFXY9gXZOR4aCrlhh6KnHMupR5JnU13yzElUMRkzxToI6wUNNgk6rLlAySBHP5EpIVLDJRWvZ7eVRRDiseYWzh3qQr+9pqffml+l8nBwkr+eF7uVhdgeusPPeLeob7+FUYlELmGuwHmrgXmxYlnLalzngh/BvVqORvJ+Tenvet0UxoiD2yHBFDd1keocMGUVJIwHkISmTUKfj5PUJEA6rCJyDRqpIowd0IgCMUuQ4pMATiQytV3PuBzLVrGAG6ryyA1c/3eFUg1/KYDSCMbqel8JRxPyEIrbfdki/MLJ4lA==
*/