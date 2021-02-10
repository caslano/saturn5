///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_IS_VARIABLE_PRECISION_HPP
#define BOOST_MP_IS_VARIABLE_PRECISION_HPP

#include <boost/type_traits/integral_constant.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class Backend>
struct is_variable_precision : public false_type
{};

template <class Backend, expression_template_option ExpressionTemplates>
struct is_variable_precision<number<Backend, ExpressionTemplates> > : public is_variable_precision<Backend>
{};

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* is_variable_precision.hpp
VqtrN8WGd7cdptZu2+WcIDsz+zF156ftXYmiJeQQP7M0bGYnU2dvjCn79KQKiq98EqFIVH6wUEn1Nx1KYWHUTHOJ0KMX3iL0nXbnycJsvBgP3wlHEl5fhSO/GH/V0FJ644duPzj3YWpSmSXugs+SgcedF8vAHx90F9dfX3DgCa97GngY9vXm2s3fY/gxPch9jP7s6xwXbzSdqUxbCHLz9QVmbEAqnRTM+woWvhmsdbjBTZzUuilt/yQLBfxQfgtxAMeIvOUjd2OaPVQgy/7/hqUyJraJRnjsmgKRgQ7XMgLXvLRAepCOqTB3rxACSbxuak+BNkGukE/dmCJ9RIVHbC11KwVf+miFazUbW6JTDG2ZHiFcXq2vrleUhXkexD3NO5i7v3FjEpHObZP/gI48JyG/125srANcvFACLauQzrE7ttBvl9FY4RrdaEQeWkAacNlhP0ghY3VG2UDUmw27OSvrpw5AyJ+pEafStCFN3/BcQSFjO5ozPRa0iICi0OrmYrK2MK2E2JmtyW6aJxQyXL1UP2VhI5BegKTKD2s160srJN5Hih5z/WB6zo/3Yb6B7LkAuTYwE4ua5LV1NKNaOdVnKlOigEVZW8aPQ9N/5Shry1iCfhCuKOLzmaNJ7csR1R1Y9gHFz1KDKisk
*/