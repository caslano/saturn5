/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_27042006_2221)
#define BOOST_FUSION_IS_VIEW_IMPL_27042006_2221

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
oYW80PlGoe5E5IxCqqF2RYgaXn+mKKx+VCcKi+CF9TYKi4Easlrdlw9HJwDNTTUNXcnw/qLc3M6Uq/Shcl8N08stZ0E0MULp80MXd81lorgmRyeK68+Lu9Io7ixzcUsW4cI9VIkJ/USJ93amxDd7U4kIaEglrmJBWb5lwvgQne2SHtAHXATT+V9vru6Uq8a18WuIJDVc/GQZ5fcWU1NuwAnhJl0XC+4/99AhYaPFonsc9negp11EKN+t7MkeLfxVpdd99PiWHrvosY0en12Es/6tI9qdg+iYl8XlZsxLNPT3XlPFFtOVFnEG8oQtwKcTCH3UfNDPbWULP//jvprtavyONnTi8IRFv5+nadrw0EhKJqATGBzwO8XGcUyEy8UcxG6oAZkHUwVdjeXgoYSWk0vdtJr3Jft+fy9+XZGBC7vrNVC3+JAFIkaEfiPhh73td4H9qMgAGUbgxBu4DoG7BQShjPhW0kEo7Ryn2CE68+JkOqLaOYKen4/ALuqXHGyvA8vcr5b5XTdykB3vtAbWQQ1A5Z89zcgyiDiQjF1E8yv2SFz0kwCHduMZtCQuvgt5UrPVwrfkmglrvKIncG0X4cRJx2vm6xCuypDKx88oyM64EOz+Da048sxgiFjpK4eT/d9wod9hmPUf9ZlBGsBPqLLR5YsbcXFPi2vY51JFDJuAesU4hn0uDtZ24mFqrOxDFMemItRRgk96DTj9
*/