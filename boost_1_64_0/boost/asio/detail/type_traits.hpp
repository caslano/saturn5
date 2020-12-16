//
// detail/type_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TYPE_TRAITS_HPP
#define BOOST_ASIO_DETAIL_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
# include <type_traits>
#else // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
# include <boost/type_traits/add_const.hpp>
# include <boost/type_traits/conditional.hpp>
# include <boost/type_traits/decay.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/type_traits/is_base_of.hpp>
# include <boost/type_traits/is_class.hpp>
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/is_convertible.hpp>
# include <boost/type_traits/is_function.hpp>
# include <boost/type_traits/is_same.hpp>
# include <boost/type_traits/remove_pointer.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/utility/declval.hpp>
# include <boost/utility/enable_if.hpp>
# include <boost/utility/result_of.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
using std::add_const;
using std::conditional;
using std::decay;
using std::declval;
using std::enable_if;
using std::false_type;
using std::integral_constant;
using std::is_base_of;
using std::is_class;
using std::is_const;
using std::is_convertible;
using std::is_function;
using std::is_same;
using std::remove_pointer;
using std::remove_reference;
#if defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
template <typename> struct result_of;
template <typename F, typename... Args>
struct result_of<F(Args...)> : std::invoke_result<F, Args...> {};
#else // defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
using std::result_of;
#endif // defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
using std::true_type;
#else // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
using boost::add_const;
template <bool Condition, typename Type = void>
struct enable_if : boost::enable_if_c<Condition, Type> {};
using boost::conditional;
using boost::decay;
using boost::declval;
using boost::false_type;
using boost::integral_constant;
using boost::is_base_of;
using boost::is_class;
using boost::is_const;
using boost::is_convertible;
using boost::is_function;
using boost::is_same;
using boost::remove_pointer;
using boost::remove_reference;
using boost::result_of;
using boost::true_type;
#endif // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
fOgAqruC8ydPGTM2nwjJrHnIOF4/eSZnJ/nvUcqZw7mY6qqsvLCIzzPJOOmWvGK0x5ZkepK/WMbpQ2n+bRidCyyo1pzJeZDCH1VW4CxmCsomgrnFvmNuMfH3i5kC/Z8lM+FAlNwz0AfXSB864+Iw5xGTnEa1bKuhE2fQEe7PCdBnOpV3Piwsg2x7YH9c1nC34aqnjFm2E4UvpFQQRXNuaxmFdzC2Q5OzvWjTzJGGPHRtY40Jx/8mwU0n0meOf8MzDfMcP6LjOUcca55zGW7Jc47w4HnOHwmC51zth7UmPP9bBW+DpwzkMwaCSPfNOt0b/eje6Ef3xmbovrkZuq804fnfjvTi8qTunvmedd+m0x2y1rrLcEvdER687tuC0H24qrsJx//jSC9HpzvPe1L/HTr9c/zon+NH/5xm6L8jCP2l3ak4o/5PIL0Kj/6eOYh136nTvcKP7hV+dK9ohu47g9Cdxz2cezbq/hTSq8P9MPe21bhnfL/N88m9jfDgubdPDAyM392eYNTnaejTIPUxjGGG98QGP3o0NEOPxxMD0+MTEz2ehR7KDKmHZjwyfQeDrE89EB68HrkB8tTvNrEd8Bz0yJJ6GMYW0/eLLD+6ZDVDl48CrJOlJrYD9kIXp9TFME4YntedfvRwNkOPq9oFxk9/jgk8bkcG7YA3AfdDj10T2kl++qLKaizSuc/wrzI/w8/ySXSG3ymuyzEBUT06QY45JvkM/xHyz7UZnqv5efYtEY4TsHyen+On+OTihYzk4l0A/yFOQ89ZWY6woxSWT/mjHdMJm7K55ZJ/sv1EEd5f8k9+JeRx8qqbcoq4JV2o+DMok43ivHlou5jw1jjL3gfMqRZn2YdwnDHt3c/hoa7VESGhCdF9I5JCIyPCQntGZ0TEh8bjWhy51qEhEa1iEuwq//nZOOPz/KFMQirzm6h+rltYUFoleXaHkw4fsl/VYaySwH1LIXlSW3LYXkNxHoIM/DJOum0BrplxVeeS/B62B2gsp7O4r07Q+TDuNQZKu42FbQZY8IpwnBzEeVPEiXVt0p/3Fy6Ry7MUcptEHUSPjQntovjku+ayo76Ubd2XJE/GKnOeDJ6H0L7N+M05/iI/PNgrO7szXIqb68H4mlhXco8jZeXVJXOKArBfB3k9hwbzYSxEGtz/WE7LofEy+SeEptlCtH2qYHA5jPB4nkkQj99vuU+9SP5LQ9NtYYoVz/Gnl0MGp0eSuU10vwx+MBkkKfPBfpNtaxdyCLLaNujh+nmD0r84NJl5OjCe4QdVNBwa4ZTeBaFrlOmybT9A1y415eloT2FfhSxzy+OaKv8jPdeG5DzKFuE48V6AOEdsWdBFXPfo0lYpwHmvDKkL5nRxn5VFSCSB6yaEyqEIjB2RXF9qvp1lPQndqjTv8S9RnI9whgt5imuaPF8jdo5cpV3IAmOePG7dR/HjbTOUKZDBNZlnNnRDrxB2lpNxVs0HV0cCyx2A3H7iv5lrkElhmbPJKp/HzTHhrTAGNvrg8+A49o6Sz2NNTGi8oc92Y7kVkFsdR+PGWxEhGFujY6LTxR/R1msFhaRrmnGtgNtzAYcT9w7nc0bmU/M45wOIbiX+vtC4LiH5WMZQWfe1zGsUhWd4lWlSJzxbU5nW3GBV7iM7cZlGLhti4M9mGadMZ1mUTEdXzis6MUdx1DIYWo1RDBxGLLdDlWt9S4iVTANk9rjvO0PPrTIA/mj4v0UZ/aoNzgECZ8MBwYGMa5JbpWkcK3sv8+ZYQTvWcqzw2GvkUgEyl4oYAw22JXiM8+YzWtvFnfkrcJ0ZXxdrvrPc4zE6WT56KtV1tJtvCCSBkneb5eySizruCuF/BGcho7UcRUg=
*/