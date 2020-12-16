/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_ITERATOR_05052005_0340)
#define BOOST_FUSION_SINGLE_VIEW_ITERATOR_05052005_0340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/view/single_view/detail/deref_impl.hpp>
#include <boost/fusion/view/single_view/detail/next_impl.hpp>
#include <boost/fusion/view/single_view/detail/prior_impl.hpp>
#include <boost/fusion/view/single_view/detail/advance_impl.hpp>
#include <boost/fusion/view/single_view/detail/distance_impl.hpp>
#include <boost/fusion/view/single_view/detail/equal_to_impl.hpp>
#include <boost/fusion/view/single_view/detail/value_of_impl.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;
    struct random_access_traversal_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator
        : iterator_base<single_view_iterator<SingleView, Pos> >
    {
        typedef single_view_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef typename SingleView::value_type value_type;
        typedef Pos position;
        typedef SingleView single_view_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit single_view_iterator(single_view_type& in_view)
            : view(in_view) {}

        SingleView& view;

    private:
        single_view_iterator& operator=(single_view_iterator const&);
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename SingleView, typename Pos>
    struct iterator_traits< ::boost::fusion::single_view_iterator<SingleView, Pos> >
    { };
}
#endif

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* single_view_iterator.hpp
tuIvwjxjItfFEZP38jAObSCzb299+Zbm3YPXjTHS5ib8G6L6xuGaYP3tdk0sKsw/QV6roUVd24fQ4pnx+wW2iepxTjS1OK9GXEAjDiapx9nRjMz4vQunRpwHLYEZ324DGgaTcZ/FTP6GE4BjskoN+MeDli9iR/F/Lpip7V5hfrQtCrORnwYJC061gIvFLRmyrp0w5zQLLGBxmfK1ukc2wwLZmH383FSh/mZGW5OU1pvCdF4L9AZpC3f4EoT50LYzU/JsTkf1/WiBP5lNfzk8PfU32wJfWH+nPp7eL8w+D7cVFufXrVwiLIA2kNmn5st7C3PNt4CPtdnnYyBJmHuhBYaxuJI/nXBQfYssUINZi0ExhSgO7QmzMQemLBfmXYz7SJ7Lggy5yJZY4DmzQv/06kA1LMXrv1hpp7+svSEs5MNcWA2JpT9fpvFcKdcgGluD2KaGwSpc89LYmsexRlOLc6PFM+Nr149mZEbbGP4JarSpW60eZ1+tFgfgRmsasWP4D8/mxMpzfbTizPj5hG2NBdYw+xH0W4WF0Wozc10osoW2lZ/xujgyR8dxu118opuchw14HqJIO9R20wVag5ss8ACkzVXSZaK4zXgMj5FWtE7v6hTnt8BS1maBVOlpG3Nvt0AhlkvpC+Mrk+3Cex6ppbXrv/U42SGsAaSlv3n8mLCQhjkDeF7Acqm1atgsmvfDci2hRa2lEFo8M75ebL/hvDPj8+5AS2DG14sHTa0/v4aFNPqDI+pxdjS1XNxoyeuje7hoYjxPoPH7KLajFrgcsZMK/t34wzJh9mMWiFGkPRvW57Qwz3E8BjArP6fOVGG+kxZIBdJmmv3ThfnRRjBb975qX2HOU7j/ZHa8X+0swsJoR1JKm5971jzK84IFLsRIa9di+Axhgct4L4/lqbsxqS7dT74qt79TOC4JU7I0Eea8ZoFizJTiudML86L1TSnt6Pgug4S57uL2wOLo2R80H1oRZvR8D1oIzaFIq+lqel2YO0T3StD4vRKsAa0tsz/HnP8kDO5bIAcz+r0lNDuaOTWr/bz+ljDdMwukY3HWvMNPCbMlM5s7rgy1iZaHGb1/Av+40JwROxN1Ly8GgmjNInYW41Z+HL5JmOM53qtkdrvh37OF+dGeMhs7ZNttYaEX0XF7mv8wRpjzJR7jmBUr1VChNtFOMjMMXzqM7E8LzGCWddjbtsJcryxQgdlfOd7/Q3FoM5mNa766pjB3GOeIjM0Rmg+tJbMhe54Vozl6jefQETuvKNC2fp+NwpxogxVppVtWz0Vz9Fbue9DYvgfj0AYyu9u31TJhYbR3kW0siJbXW2qeMP9HC2Rh1mPEoZXU5l8W2KRIW3ixfUiY+4ucIzR2HxoghCZ+M/EC/sOndRkqCnNksULVWGlvO/x3ozCXwQrpmDlDFUGY3WKFQ5E8L+IarHV9TAca6xxWaB2xS2ilm1m603Zrs9LvMF7GhhZOP9mMjh3xVvo9xSsYt7FjnT9p27Rb4VHar3YV4+ZMrNtQmK2SlX5/+hraqlominOgLY6R1uVtruXUZhUr/XbJdezvpDVnHOVZ0wrfg7TmD/aWo3mvZYWizOgZMzQ3WpMYaRdyvZL7s7pWyFhOWj9/GZp3mGul3xW6gfO3Q5+YKCyMtixiN9FqNFhdT1hgnhU2MMs+9kQKqmG+FXoye1Nhw1KqYYEVPMx6bJ48XFgQrQizc6aeNmG6hVa4xuzVzN+SaB4WWaEZs7bNij4W5kXLz0y+QwNrQItndvPG6wvCYLF6nF3DXGhVmJ3f3HEG9YdWnVnDm4+eUQ1LrBBk1mXcNxbqb6kV3Iq0RT1NnYTBcitMY3GbV2VpJcyPVpzF5b8=
*/