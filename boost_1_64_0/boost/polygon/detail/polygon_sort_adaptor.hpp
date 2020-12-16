/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_SORT_ADAPTOR_HPP
#define BOOST_POLYGON_SORT_ADAPTOR_HPP
#ifdef __ICC
#pragma warning(disable:2022)
#pragma warning(disable:2023)
#endif

#include <algorithm>

//! @brief polygon_sort_adaptor default implementation that calls std::sort
namespace boost {
  namespace polygon {

    template<typename iterator_type>
    struct dummy_to_delay_instantiation{
      typedef int unit_type; // default GTL unit
    };

    //! @brief polygon_sort_adaptor default implementation that calls std::sort
    template<typename T>
    struct polygon_sort_adaptor {
      //! @brief wrapper that mimics std::sort() function and takes
      // the same arguments
      template<typename RandomAccessIterator_Type>
      static void sort(RandomAccessIterator_Type _First,
                       RandomAccessIterator_Type _Last)
      {
         std::sort(_First, _Last);
      }
      //! @brief wrapper that mimics std::sort() function overload and takes
      // the same arguments
      template<typename RandomAccessIterator_Type, typename Pred_Type>
      static void sort(RandomAccessIterator_Type _First,
                       RandomAccessIterator_Type _Last,
                       const Pred_Type& _Comp)
      {
         std::sort(_First, _Last, _Comp);
      }
    };

    //! @brief user level wrapper for sorting quantities
    template <typename iter_type>
    void polygon_sort(iter_type _b_, iter_type _e_)
    {
      polygon_sort_adaptor<typename dummy_to_delay_instantiation<iter_type>::unit_type>::sort(_b_, _e_);
    }

    //! @brief user level wrapper for sorting quantities that takes predicate
    // as additional argument
    template <typename iter_type, typename pred_type>
    void polygon_sort(iter_type _b_, iter_type _e_, const pred_type& _pred_)
    {
      polygon_sort_adaptor<typename dummy_to_delay_instantiation<iter_type>::unit_type>::sort(_b_, _e_, _pred_);
    }



  } // namespace polygon
}   // namespace boost
#endif

/* polygon_sort_adaptor.hpp
d72IXmcSD1I0v1Z77JODJQd/y05+jLyn4Q8HU5644Psj/FQ+fiqHc9oPdL9Vn72/5lzOl3EmzuZckHhebv/9/kXkXsM8PYvfxZ52f2z8mGsUep3Ncwd3cT6EHnlhJwuR+3b0PAW/f5j1zVHOjw8lqz9Wfzs5z0Rv+qOfR+hHCuXLxxl7T0wz8+OLPHe+h39hXTYtHzuKYr2Pfbmnsk6kf2E1+N8c9j/M9xn7nMs+B4zDHvGHw7FTJ3p5qJqU9efReexvb8W/PIwdcL415izrAOtcxUrxtwHHuP8tztl/jd6vQP+G41d53iTgQfZlzHPJrdQ7mnU99axgf+VKYf3MecmG0/ydhfOFAM4nlqew76vgOSLsNWMtcu1E34bgH5DvJuavnLjmYr0wjPPArehrf/ZZC4mDkym/63ni3Uv4D65ncP0Q+W7G58K+gvPwE634gUH4r/Ho4w+xA84dx8xmvY5/C2N+vWoojx4ffg77Pk199t/ZbiCOML+n+Lu9+wn8K+WP/Rk9OUO/n8euf0h6J+eig9Fb9vf5Gezb0E8vxjcQ+fd3o5fM0/oXWEc52Zcg51MfmnOzXSHoXxr7DZ43OpVtn+cT95D34SPoH/ORgtwTOc9eNh07Osm8JWEXxPuRS9nfJuFfd9vxmOucT0zDjg648G/t+EHs80icylntByNX/OOQv+J/RuCv440cx5xj3MHYK3Z18lGeT2Vduon12awB7AvZP21ORP/R+2FBtMP+z4v7VtPf/cgjDPt8xfJ3Vj73n7D/7sM+YendZjyziW/Dp5h+ZzyLfq4mDulub+v+eOx5GuNCbsfo1xmez5z4IXF+pJVvyZ1+WfprpfdzXiE997HkfoBzja3odz5+qJT9Gno4yz4n+DNxfiXzdzP6+hCpi33wjchlJ/EkjPjEeUw5852fjNwT+Psz69p81q+b8Fdu3adUz7Vip5y/Tea84xDxLFb6Zt23AvkM5JwjmPr6L2I+ifPTPmM/lck6Zgb278JOWF8MeQ+7yEc/7f1+Mn7tJ6zL2OelsF93oS+b72W/9Alxk3YWBhJ/OE89wveyLPzwDfiz0eg35xNOnosuYb+81z4fyaXf+N8xg9nnPMDfp5Czm/3+7inYheTkqzSe84EjI6jP/vt4JHJRPTdZ/TLP76hd9gv288pHmL+X0B/02H8H/ph56Y8+D+QctvwD9i/otzub/QDzeiYTebFf7Z+B/iezr1uLn/6CUit/PvWxnirJdJgUOQVjJ8PKzbhTnJw/DmGdthM9j9d4rXzixO4m7EhS97H6wX7OhX4M/CF2TvsnPmXfvoL6ApjvFOxhNP3/iX2ux/zZ5/FF2N2L2GU8153YFfIZNpNz0iHEIfzmbOrbz9/ZD+Tg/zjPLqd9r1lGnmHEr8PMQ3/kEEC/4+19Eesb51Hiw1zO+bKwzwj0LwT9y2T99Qv8WgLr2ffRm6nIkfk6+5yDv8fzPFYJz1PO4e9+cdjBvciH+0u+zjne/dh1MvbK/njrXfhHJ+PnfGH1g9iZ/TxgIHGHdXEZcWfhC+xvZxg/FvAs/WQ/uJv6MubQ3xuJa9msW6oYL/uHIy3o5TfRW+RZls585rCuuQE/PxM7DqVe9u0n7zHpsJ9yPvoccYX1y7Qi9CAfuS/hfBz9PsL+Kh5/OXIW+zjZZ19rvOqnj9JlJegzej1rJHGAdPUSni9kPhLRp7Xp9rkH+3jWT4c5Lwmwny9ei90n8XzebO7jPH0g5zTLf4zesb8vt/1eJOtQxrMcPfN93fTjfBZ6YT8/8S7PZ+D3Duxm/8C56SFrXWWlrzmMvZ9jvZPN/HKO4EU82snzLa4c9B59njUH+12LnDifnN3IuhY=
*/