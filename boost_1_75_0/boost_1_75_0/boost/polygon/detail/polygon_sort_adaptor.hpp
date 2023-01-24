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
/WR9qMV+/sr0/kuYI20v4m7/D3jd8X5NqcHg9u12qei9rj9yfbhDXC5Wm+Exc2/YgbMFU+9QwPZbk/3Vh49SeAfu7UK6v8G0sQELFlNBPYXpM1CBTXTrXkD7qN/cAthx/Ve3A+UjVMW/G3K7YnAIJ1C7ANYOQ+uOQ6EZPgF+FuMzvjCDxToxhcDGK93TaeD9d7AzMWAC4n5ocAimf7qU63p15q31MkwfFTAp3qtRXHevgXgh4owcgGY75gNcB+nAAo2QTsEn1jSr3pdsxczE5NdluXHjI9/RF3Nwp26gl2VExG0dHPgDRG9Y/Wf1ayUFDACB4/wdVDEPKeVUsf8Bqv/fBC7nvyhV3dLUwtHy3+pUfwMZEviR5QLt1FyTsqK+r4OGvP46b+dG0bsiuYY1LH1bRUc7SUVl4+QVC9NGsu2rH2hlXWUyass6RYzjHWXVDJX40pKo/S+EOF04i75h5BCNP83fZm74N3gVGpNAKoej/r3gbh8e0KTXpMDfzqswUPbT9UsCxyNW/Bey8mCj3ymzTVncJapFX5AiXgOpk8dWhzPSFuCavpRlpptWla6sQ5mJPnh1xDpIWdisqD8RJwi2dMrtQjv+1mO1LoknEZd1UMq5TY+VYIRBr+Rezily3J7YVd+glPK3J7fhbksFqDU9NJ+LSkf2sf/JylKEHatBJUHUJSAV+/bnb3w6LozPVDnBcIx5nRrx5KT2
*/