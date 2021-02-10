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
DxNGisDpijD2HTrkZ4QCB4PJwKVsVFyogoI8R/FDYMR1kRVOo4QlKhPQU2SKnAoC1JZG/MR8j3FJtyN/vESIECKT4ST0UAxCgDSOjwAXYeI5JIxpY6PnElI0Y2gfcMlCVwd8DzUBoa5DSxdgYDHKinDV6p91LvpwVe/16lr/GjonUNeukdfHltZEf1OUFAKZBSFhKDkEOg5cSpxY4OsdhcIUoUHnVuFA3i/JJfk/gwl1nf8WCsSb0tD3xsSLqgUe3WMLbZolbYANuCEeCS1uYuPc+kQkNA3bl5RNLB7ME4f60CMuwWGImbJ0qgT1bvdSve70zOOLVrtpXnV6H9We2Tqvn6pVEJZZ7JTK+0JhfoslE/Rrva+eVxPB2bVu75/mqard43CEPEqHwhJd4+S0Otcuu9Dpqpqut6vojZNsUG+c1TVN5aNaNqhq9eO2al5orUanqS5POOv3u2ZHa18vD/dVvY9hs8L8rN5Tm0usmy2d826afIKOxiwUb3TOu602ItWt989yV54N6NHXAVqurDDp13unah/ppDrMKnvPglpbh3QOop9QPwh1vXf+TLC/eVznxl6A9tMWmSYZTG7ed4kplziTElxRb61HYhWf7I/Xin7tef74UC7vHsGH8n6p/IPdCOvXnOeB/oWb
*/