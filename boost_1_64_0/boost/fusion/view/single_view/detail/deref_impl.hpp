/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258)
#define BOOST_FUSION_SINGLE_VIEW_DEREF_IMPL_05052005_0258

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
    
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.view.val;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
tZpTDWglmPVt2bGAMMdV3AaZpRY4PJRyQbMyk+/XYS7XrNCI2dPI7DbCPGjdWO1V/0n5l+YL4+cPLK7shD6pwoJoPM8LsRNWCYMbVshslpbYpVgTYb5bVmjF7FnkTEiY9w88r4A0Oq+gRdDqMxtUYE8mYa67VpjGrHyOI0nC4B5+psjss8ut2woLoT0zsW0iR/XFNOYDKziZzftz7Snq9UMrJIA0+h4mmuUvvNZgRtcaaA40OzPa39HcaEnMaJ9G8xtYGC2RGR0n0LRH6lycaKoxvQZxfoO4MJqqPkuqQV/QlH1BU/YFTVV72CBOi6jnc0XUY/oM4oIR9Xzwt3pMJ5pqW/KgfcbsVs1O16mf/1ihPLMGv2c8QT1DC5qkrWvSoSjV8NgKB2OkLXKOH0a142skrVlc8M3MIcLglRXmgrQWXcbYqXa0arHSfipScSLlabLBFRZ3/ostDcT3LRxmG10zZDCXk+9to7l0RtchaB60bMzoOhLNh7aGWckpGSPC3DHR1mNSnRTKJdYGPmYTLtRwC4ugqeazpFPn6UBT1ofG5/N9ebwwjZneBu2ZwYlOB4R50VRj+tFUeQbRVHmG0Uowo2siNC2DDdoyy//18LXUa7SSzJaumN5XWAitNrMFswaNob5kjM6Frj/RXBnVY/rQKjCr/vUeB9WAVomZtv9yP5rvA3WcF60ws5ahQ9eFBdBqMgsWrJWD1ihTdA2z3sSspfnQlOsebfJ7E2getBRmK02dT9D6oSnXT2d0XY4GmaONvlOBpkWb/O4HmhOtEDN5zY55os1n9lej/66n2rNEW3mtapKwiM7+2diM1jaQ1Qa1mJm33DhGvc4WHZf5WLHFwkI663hg9w1hvuzRVkU7mELrYIm20gvLRGi+HOr9wYWWxIwd53v40EakWUbz0EFanRGPhDly2uCdWdraxakFhEU+tEFXFheanBonzJMn2tLl+TeR4tCOsDEPfXhxGMUVsIGdxdG5Cs2PlsiMzkdoYYM4S0F1nKugOs5rEBc0iIsYxDni1HFuA/OhJTHj6xdCU81nibdBVZO0LllufEX9tNpgKYs74vt0OeVis0FfZvNmnDpI9aE9Z1a1R9/tVJ/dBgkmVkOdfy/QfAk26MbWfcKz1aPICttgK7Nj3TqUFwaJNijIxny+s+xNYZ7iNgiAtNoX0r+ktU2ywXYW91vRl68orqQNvmdxN89VLk9xpWxQj8VtLpLe/N42xURK2+j3kD4wb4pp2OZhLWGhslg7SMtV4NZQYZCMx2tm7nMLfhDmQNvGbJyj0u/CLOXw+MIskO3X0sI8aJ2Y5Xi4z0F5onVhtiHUdyLFpUTnmXTpRk5hfrQ4Zq5VcWepPrRkZuPf9l1LeZaPHvPnb4/fEeZES2JG2y6aFy2Q1utMaJXyXexNuVS0QU6ztCbLBoyiMavYYC5Iu7j5TQZhUBW3MxY3o1bqGLIaeOxJJy3LVymlacy6NmjJ4n6+9aIIrVEDGzQHafIeD/NES2LG6wuj2ZnRPo1maaiOcxmYz8BCaKr5oJEN8jKjexk0DU0V50JT5oKWyEweezAXNFeaZUaj58JozsY26JxmWdDSbTn2p7Cgzj7+wTmV4prYYBizJ0/PeKjXaIOYNTs9nbYJT1MbVGGWq2LqHpoPbSiz9ScOLqfam9nglknayDebbgoLNLfBehbXptXWrtSXFjYoxuJqFH8i9+lWNmjF4hp5N70Q5kU7yCx4yFWPrHW0FckcO4isjQ16mKU19f45n6y9Dc6yuExPu06nPDvgfQ6zUVUyZaH6OuJ1AbNzeSq3pL50skF5Zh/N2rFLmB8tOzN5zYf1oPl53KlRayiXT/BcxezPz10=
*/