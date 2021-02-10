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
BwyKDcocQK5jkflgv/JNiVJTL/Crran4xmA0koF6bwqDaR1m3EobwPUg/Ht8FcJ1bzLpjcIbGH+B3uiGwL4NRufYeonFMhD3aSYsFs9ALlMlRVzWfL+rXftV6kjlsYA6NS9KRHTXSuq1nXGbChFvJ6pxDI+54z7aOu5kBGdXkyHsCW4fus/GIoMJuZaOWeHytLEyMm7WvtcAHevQhxZOfVyfjb9hJsBCmRlXTGJKgybY1+H4r96Q9YbDZhfnqQTmEGVG70Wkn5Lzxi801ATChyKmxIuU4Brr+0DAwg57v6l8FbLxF3bRvxhPbmj+qbaNQIbd2tN2SUS/XI4zu6up+GwqeSbd2qs0KlCvRK45blclGsroBTi5FExJ9HFQe/H88VG+P/8b5mub+Zy5IviVMGIQi6hqTGRyjf5HoTu0BLR1jmc0oREz0GaNU9/xODt4ovltp1GuXLluiTKXmvsE39lKIrQCHgJeocDnji9DNhxfs+llv3/OhoOLQRjsrq7S8Wfyw8FFP9iR0GefUbaH9IYpu4MTuO8Lu7TxQOB3wm93rJUJXIHLuLZzFMJnAu4aiqTk/c9pZha0S1tlcIGOuvjnxmekB3l8W97vp5I76lgaEr1bxDbLDs0ywe+6G2LWibQ4lEj+kgZmt9wK
*/