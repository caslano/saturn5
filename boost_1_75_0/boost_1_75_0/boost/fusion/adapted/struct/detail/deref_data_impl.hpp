/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_DATA_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<struct_iterator_tag>
      : deref_impl<struct_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
fzakUsKITV+pnws3bvQ3GHcSOFSj5oWSs3mejLWfZkmKIN1XJV2/XsYCaYQskX4z7qAVGEr8LA19y4P1StSx/5t6pHE8SSNV8fYKJd7I75i8whK/Z1fUEb95K1D8enNn5KwwxU/ij/3yXEDkPYveyoMkcosP1hG5/AcIZDPIplM2n/Cve5pyR0lXT1HcBcod7CxV24Dt55fpSh7bKQsDY7BOkgjeNQJFcBxGNTr+vkKJwfIvUmOwrlymxmBFvduQLI6tZDsPX9tctfNwAyVyUGU9Nj4YrLUz0HEuZ9M2HvvOSPqdxNIjTSlHEHLsEuLfrFBG7QAx37mcug62RdmUyYS4bm90gjrvNG3aowiQFWo6I3mtxN4c0qqXDmymWYvBknUFF4iGHNeXGhL9jdr/Bn54BDNR+6jfMWyxjpHe9oF9IST9tsXguXrSF9cOdnDGLid1hXCQEKAcuheTa8lA+s1GwdQYLd13sw38t33RnURtdkHHGDY1xmTD7/hmmW5CWwDOMXJd4i/ohjlypmqUZcaxeJlV2+vhmkJgonhS+xCg5NLM5YNFwDS+NH0RMGz44kKB4UqFxJDw+hheNQUYTpcMu707jc+mqMw6SFJlb+Am7Vqabsk5VHZAJ3dYrpiJk2wmIjlW/iTSrFkqensxGbW38J7SyZQeTC5TPxLTEa4uhGUVaao1frhMqbGaazzMhqkaa3wCaoTKqgMr
*/