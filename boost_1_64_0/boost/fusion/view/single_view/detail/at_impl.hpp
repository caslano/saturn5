/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type 
                call(Sequence& seq)
                {
                    return seq.val;
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
zYUFy+P2AtJoe0GDCnGQyOzc+bpthTnRkpjJbQnnQ6vH7Px/nm8WFkbLyYy2MzSoiNsZM9rO0BxoZZjJ7QzAg3YsbX+4Z+o06HTgu9fCAjXi4HSstCVvY9rI91/ioJRJWq2qm9MLc9aLg/kg7WqrFXOEQf04cLK4e11bLRLmaxAH01hcxjqWVBqzYRwsjJFmcRfoQ7k0jYNeZmnn2/n3kTWPgyHMSnyRheJCreLgE5bLX9v6DqRc2sRBZ2bZF/rGCnO1i4OazNyTV1YWFmmP84G02c7024R5O8TRezp/mgAKhGPGCLN0jAM/s9O/lNsqLIzmSrP7JoBVfXK0oVw6Yc9ipW1cV72vMOgWB81Y3IESy07RuqPNSidt4a5ujvfWq6S7TxxMSKvvgalH768+6DNcmKtfHGxlVut+uVu0Tw+Io/8JfYj75s353+0VFhgUB2tAWqsGi0GY1xMHjVkcBL/uJUwbEgfBWGnVxpzu/N5GDLWMioPeaXF/mcqXC8Vc3SwsPDoO8pul/ZoSe5DuV8bE0XnlkWmQZ0vP0T8Ig7Fx4DBJc3fd/YDixsXBHWbT9s0V92ODwt446JfWz1TT8D7Hnk3dKiwwNQ66m6UVnFmBzgGBGXGwoOR7i5h6esq9nj6d7Kdo654x9THZ6zg4o0m7eyvHYNGzYOF4+mzib+zZofs9Cr23Id09ReLp+dI/eB3SvMI/J2h7KRpP343/1wSQY2CxosI8aF3S7LEJII99pXzvF+2HNHtiAvbst3fXcLF4ekb91FSmwuvnL6zCoHQ89AFp9IwazYdWhhk9o0YLobU0S6Nn1GjBsvHgqSTtaPVSaft7p0G+z+Jhc9qYz0xDeuYYU9gvzPN5PCQxo89T0QJoN5l5BzzKKiw0Jh5SmNF/H6JpY9Xzwbh4WB4r7cOPcmSmMb+Inq/nq8fDhEUmYV+YUV/QHJPf90XYniw1UiiXafGQrqG0WpOu3XlvA4cGbss8n5s+Lfm06E97hfnuYF+YUV/QQmgfmaRdv/l7HWHOu9gXFif7gmOiqebz3IuHyumkvf7pyUVhkBo93/a7FW5SXAT7AtJkX7A+tOZmaZ//0+1LYf5/42G3U9rMpYFWaceQnr6PrfR+3QvT8CFb8i/6XpinjhVWmqTVvxXjEuatZ4U2ZmnNT9i3UlxDK7RkcVeqHP5dmNbYij2TJnuGcWgl2JjTjhZ7KczRzApJLE6uEcah7WPW+4ehd4W5XVb4ltmqXd1z0pjNreBl1rBgsY+FhdCaM6PP6tCcLazgYJa1/PD/Ul/QNrPaXx88W5euoVtZ6bdoXppKDbp+JpBHmLO1FSqbpR34t8INYZZ2WDuLo9rRXGhzYqWtzXXmDsV1tkIVk7R1pYpmpVy6WMHM4gZnrfhWWKCHFe6xuOq2nI+Eab2s4AZpbZ98lkpjohVncY+61llJcX2scITFtXzUbwVZXyssYPZNzt4VhYXRpjObee/TNsJ8/awwi9mr2K7NqZ/9cVtiFn/BqQnzom1h9i5ds8vC3AOsUN3E1ii5/c/CIgOt0JvFze1YuheNOQi3F2Zye8E4tCnM8h/e2JB65rGCnRm9/4IWQktkRu+4oFkGq+OcaCnMOv49rj71DC0vM/o8HC1gMGYYTZWLNkQd50JT5eJHU+USNBgzgqbKxTFUHedGU+USQFPlEjIYE4ap900nmipPL9qvzMJLxg4mG26FYjHSUiYenE022gqDzNIabx0U+9569vCNscJPpvf2ytR9yL2eee8JC42zwkmQdtdXsYew8Hgr9GVWuUuewcI8XiuEmWUqVs5F802wQhlmH1/sbKf5dEbnKjTLRDw/MCtV9f5jYV60nayGKSU=
*/