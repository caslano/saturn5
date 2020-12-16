
#ifndef BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
#define BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/single_element_iter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct single_view
    : iterator_range<
          aux::sel_iter<T,0>
        , aux::sel_iter<T,1>
        >
{
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, single_view)

}}

#endif // BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

/* single_view.hpp
pfdBg7uvTpKj05ZjpsihCFhnUcLM1rzU7zJV4/1IHTZHlr4PfVE5/EHRfQ/PoD+hHPpL4r4rKB6IhsXfqbaeTduWYkckhb9tz4GAv8IFWbxXaFnD7wSUXu25eY0YSKSsbUgP1YmU8oBbp7yMlO3O0E0ihUJh65SXRMo72xQwp06Q1XRXKd1jU7wqxatTzk1hROLPG5/u39uHViiMYO/TKwhcOdUdnbp2W3pwoZXqimunvawztq32ot2ji17+Rnd7qjc21cupXW9nVDzDTKH/HRUdz7D5q3ZEm6DIhl+pOIU0HT0U3oLeITdl4xlpITxRlDz6uyGjEnMbgSroHU8Zc+U3824SavjVoYDmYjktJwtDFXX/b05VxkmZ1HaNIhASvIWrGgVUSpjtjGSYaQOIcYbFp/WLctr2UookeO+iPzj42lTjAbCXjWBH3kUq8kcrlZkaQkvLKE4F/VdumwLDtnHuNwWWq0Re56zJIRTyvrioQvxf05pTNSoU5k93lH4tPn2dXXXoimwqw98vCS4qFf9zQSGD1+O1Vvx9p4FiBKJFDaJFLtmiow9pai98PVTfgPJLcgVmaIZoc7hWtLEs0C4xps9Ne9OIpY0EvvM94XqRIVgvhs0gmKKEaKHZ3Y0VkFZoNB/olVPwCNELCqrV/DbZWbW25k+QbV19R87Xe0Vbc6pGUEvwaUnGHvHpq+yq/tRWjEauyJTNGYQrCh4YRDC8Fe3eah/J4/o3UT9t5bICH9nYIEgwMiiUI9h0NMqE6V3s7cy5alaJv+pOQFECXHsJc22Er7pJJOQaLIAs1Ql0J2AgWwFVu7gooJU9caCcFQqLVwoJE8mVcMxXHVas0cEMxBJhLnRJRfG8bJ4RIPyxlYK6q/gT/RBeEtUcbMwgSyFe0s3KYzFqNWMxGeYVYML0xYRZo4LKAIiapcjomJdhXkChgUAyTBEk6WcCVAh5Wa3xg1H/HWqN7+xn3f8wIibeEC1SYeEuB3rDcMK4Ko+IpmJ3lHZqE1ZO7uCmQu7gTvSlghaQSe8frhhh2x/7HNUIe3G7SKlqN/Xd4lW0ZaKpVcbhTBFehIM5lfZrsm0d5w2DLcNhbMzmIzY0FbsDlPNzbKnVByN0jirhBZiFRUoYhVn2zp54xfle57HMU/mhv51C/h1u7++F1R5BufNpuWndCxYBnb4niFd1pB6iN/BuQd881xY6oQWgeUuf7AzT9KQz9VOKov6SY7tM/YQvtGd2/Lfg/PPoKH30mUDWYF/GYHiueKgXr8H6SvqrbEZfdktFZD1yjMwOVmasDJVku4IlGWtU4kv4/x1aUUTREOUoHNkzNDFjTeHEni6VGHw+d54APzF3AYCvbaByEE00cGewMmdlaKLTFZyYs0YmEgaQUGgFZ+A5BNwXKslZU1jic6lEBbxEAn+ngYpDTOsYNNJQ+J3tCQAjLQoueiRdNjo9WY+ky0anJ+uR9PgeccpGO5P1iFM22pmsR5zxmGdI5DKSYZ4hkctIhnmGxlwDz5TlM5MBz5TlM5MBz4wH3k2W75YMeDdZvlsy4N1swDfUzmzXUcrwLA7k+GGV+JvtDVfQzfI6dNgLE3NXEmHx6wneF0rodVvI/6pJwluh/63PxGbe9WqzeHO9tYv+k3r7YylrDmWlPJ9y4j+txKFW4iecuNNKHGQlSrAtVmJ/KzHCiZ9Zib2sxI858VMr0WslNiERVUvyygr9RjS+8I6daNeinaLmYP35otdqZ9Dflx2gsHTdHyhG3TONYG4Pebg/PO9F9cd7oj/kMciJlDWXslKeTznxn1ZioZX4CSfutBKHWYkSbIuVONhKjHDiZ1biIVYi9wdVrRN7W4ncH6g6GJ4=
*/