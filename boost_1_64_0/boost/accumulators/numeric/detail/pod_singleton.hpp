// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP
# define BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

namespace boost { namespace detail {

template<typename T>
struct pod_singleton
{
    static T instance;
};

template<typename T>
T pod_singleton<T>::instance;

}} // namespace boost::detail

#endif // BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

/* pod_singleton.hpp
MrTjy/3r1wJNa71Nyf3ZR3piZmfazQFqDyXaGvDW64K9XBPhQ5eyjwlTqZLPlLPc2YfD8wJqlrVy9q35t5UHyvJpgAsHfbSsUK+hn9qjg9fEAzHpKHgN8RxzVpnjZaNXnLnFHgg5lr4hREE1/C915gLXIPTJoTLAT3X5q7kLx2+I2GzvgVMZE3FZXn7732kKf4ZzVTh/t3cXtJLG1LiNteXaG/tVMgRs88xFue/tMm16htJA3kvtdjYrzPoM+7VNdoFXT0sd33Js0FkRnAsDsLa+OX5lhXUmckJxfFoVgKVosFT+BxSgJlVA28vRfSFjc5y0fTnbA2HctZ9F1fc7emZfQfV+8D09LYUwYNDqJEgy3hHZu4hLgUBCsH4JpJcjw+TS1qcZfGG2UcWbU6glBp7l+5Nheg6OBdMaWZ6vig/JnBjr8Ivyf+EZ9dBq/ZuQlROIG6B0+frVnNkhU2aXc3LvGGxe/dYZusOb4UCEJBCmIuEXd90AgL2pw3kgmtuAc/t7LGSQksX8TBrkF98KF8H/zrhydUB0F+mrDEkh7xcALaIkR1qWJaP9jA==
*/