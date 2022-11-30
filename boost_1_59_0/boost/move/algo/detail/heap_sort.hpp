//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_HEAP_SORT_HPP
#define BOOST_MOVE_DETAIL_HEAP_SORT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/detail/workaround.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/algo/detail/is_sorted.hpp>
#include <boost/move/utility_core.hpp>

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

namespace boost {  namespace movelib{

template <class RandomAccessIterator, class Compare>
class heap_sort_helper
{
   typedef typename boost::movelib::iter_size<RandomAccessIterator>::type  size_type;
   typedef typename boost::movelib::iterator_traits<RandomAccessIterator>::value_type value_type;

   static void adjust_heap(RandomAccessIterator first, size_type hole_index, size_type const len, value_type &value, Compare comp)
   {
      size_type const top_index = hole_index;
      size_type second_child = size_type(2u*(hole_index + 1u));

      while (second_child < len) {
         if (comp(*(first + second_child), *(first + size_type(second_child - 1u))))
            second_child--;
         *(first + hole_index) = boost::move(*(first + second_child));
         hole_index = second_child;
         second_child = size_type(2u * (second_child + 1u));
      }
      if (second_child == len) {
         *(first + hole_index) = boost::move(*(first + size_type(second_child - 1u)));
         hole_index = size_type(second_child - 1);
      }

      {  //push_heap-like ending
         size_type parent = size_type((hole_index - 1u) / 2u);
         while (hole_index > top_index && comp(*(first + parent), value)) {
            *(first + hole_index) = boost::move(*(first + parent));
            hole_index = parent;
            parent = size_type((hole_index - 1u) / 2u);
         }    
         *(first + hole_index) = boost::move(value);
      }
   }

   static void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {
      size_type const len = size_type(last - first);
      if (len > 1) {
         size_type parent = size_type(len/2u - 1u);

         do {
            value_type v(boost::move(*(first + parent)));
            adjust_heap(first, parent, len, v, comp);
         }while (parent--);
      }
   }

   static void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {
      size_type len = size_type(last - first);
      while (len > 1) {
         //move biggest to the safe zone
         --last;
         value_type v(boost::move(*last));
         *last = boost::move(*first);
         adjust_heap(first, size_type(0), --len, v, comp);
      }
   }

   public:
   static void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {
      make_heap(first, last, comp);
      sort_heap(first, last, comp);
      BOOST_ASSERT(boost::movelib::is_sorted(first, last, comp));
   }
};

template <class RandomAccessIterator, class Compare>
BOOST_MOVE_FORCEINLINE void heap_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
   heap_sort_helper<RandomAccessIterator, Compare>::sort(first, last, comp);
}

}} //namespace boost {  namespace movelib{

#if defined(BOOST_CLANG) || (defined(BOOST_GCC) && (BOOST_GCC >= 40600))
#pragma GCC diagnostic pop
#endif

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_DETAIL_HEAP_SORT_HPP

/* heap_sort.hpp
E0J/7a/j6k9uIBmyeQFYKfFtq7QhzAK7MAAy+1ulTVNqACCkDsgd4R+hZFyif3umkE48Gq3gnSerGq6953om3DY8KpGwT0DnmX93GNEkjuKb36xYPcnF5X4IcgjsjA75dDh7efUYIukdmohpyfcU4E7WPDD3cFUTgtuva0Ic+co9FgvXUOFcT3TKLPXYZZX2WGb181GxwTvOWYpISDUktH7M83Lk15vdbOsWI5/B0je4t8e1YcOqsBL7CmGij5bAS6wkgPpxi323gaAB8F1iCjDZfZyZdEfRUl/lq3/TCJlR1WBinf5Bh1n/IMBRa2Yz5EEPZBvtVdpGnHxBP8fb8ddb2v7Jxa0xOLu9+eBljlvZeFZUMtMLeIQgDh6ty1N93RF2bhH6lJbeeq1DlQ2K7PLUUZ+Nkr4BMrB6Zb/1kscXr9kKIORvB5xh00frLwFv9WKSnDQCzNf1Y7Ka5khf65z0qNjbGq3JaeSxwZflq6nhqzxyerAf9BJ5W/SIw3FS9m1r7lid2KwoRBxU+exbXIW3zjL5fPiigD3nCqiHKSu2bB8+0faSkGrQ14/+X+gfoX+H/h/6f+j+oQyPlpoUiC4O/w9SGCoyfwoA9f/DBVAo6Pwn+FMWp/E/NgOron84XVD/9wIQoEhjLD/+ipNSMssXBFgoIErcWzCnR5b/KqGfuDg5trL8N2opkbHif/8JgrTgxN7A2szM4tfYEPAeBv8gH4zi/mxAdm2m/ldGhR9mQL8xYfz8f73he4n2/v+O1K7wxe4yBgyc//tfQZGNsdHFv3n6+m/T/bcI8er/N/s09X+v391r560/Z4RA/Pa/P5U1jTWzfLKjPvAb+J/93eSEwd4D+9qzkwOi/yJ/f7VrLIf8jdv0J4j//hOL0osz8U9OisJ86k/4HSAjKJ/MutzyRrJpjXBJJHdcefdSDGK/SFV3Aj9lW9m0dzGYRsZu5IzqRnOLjzKgkS/BILq9K4NoRj3Yj0MMBcU5Eymaw+oXZdC5hew9wpmiCell8/4SRreUQXVEu3p2St7xk9OZqGxT/OV8NBgQrnZNTDcTbvEyPDJclU5+AA/+zTC6pry++bW/Pqs7uacUQl9n9/2smzomD/Ki/8BGSFTMobV1m1l5j1w7+tsBvzF7dvk+83VxAvgfwZ+63uXt/3VuTqL9plJMlqp6beO6/A5neLYpbZu/HmjvZrRwC8vPuBbKbm8ocP8BMEBrDBinBfJfJHdioavniuTjomfXCWORfi8u7VU9lv7v+wyB0o89HyHCjrVrdP+GjC+jJnrfbuf4HzkBA+MA5OTCsyGPLnb/hoHrUxCBwnNX/6XsgEoIljRBSN8DypDRv3tGtuL+TY8qPQ/2lSH7KipdCraun/3h4A0h/52yBMAfyMRry5T3UU4+IngG1pTDLX9RSDgCdDTPrnx3dL4Uf7jyHdWvRlu3SRbjG1AAeHTXrPm/ONq58MlZrG+ISbWcKzIiAzb1Y5eqguG0DbbbjzquA9YhaPz8wL4fVK544qSvFzB63NCEL+CGu42u8DP7nyhYIOXy9ytIjCyWhJ3uzQOhBh00hVYTFYX4e/Hii5KgAgLbF86NSysriwtrHxEllpFo5ImoraBPl9nU9KiLxVmH7cTUZZnHw/mF6H3iHeRLiAshqVOncTVl/hpt0pQB4pQ6JqKukcQ1SuEa7jP88Dxkcvy/ADRsM3VtMEy8vU+vdYTUECmb26mtPjX/+vcQj/TYoPMQvAEdmt8VRik86N3FCiIlwb8VEfIWyOwIn7/XY7Bh4yP59Tt5BD4YRpUeHb2FzRH/3+XA8kWSVMhhDN4Kc+PZkqDYN2dWtSHeqCTlxLdQitCTilqOjqi1K2FONjhIDhRmVoJmqaq7rUxfc9yYm0UY4yt5Z4PKYRYJerLwHmIvSPivK4MyJ8PFNiFRaefl1gob5Yur8q9m6dPD2mvkLQvvzRWXGJ9X30jBY99toG5A9hkEtL5bbsEVXadMkn6s06lXcNp4grCuqLBKTK2PsOWkkFG/YdW0+yQIZTfBIr+h7E6GAu5R9VtkGVVnWHxoQ8nj79rw8E1JVgzQB+dmvrDMJfCyB9JnRAzXKNWVAgf/dUj+331oJGnynDImRv0LueMyxLQdTku+6pfMGjYg7YUfiY1ocPReBTqqankcGw/5PEauBrfTFUw0JfeKskFMgUSvNwriw4/AjM/LuYM0M7vhw1gkRcNs/Sj0L35yIZw5SZSsNKCyFnGwgveLyE+HLC5hpVN0GAs01WmbZh/t0UFntoy1pKhilx4x7X9RsLd+35x6y9nBMGeoQB+fA70PTEnVjiZda4rDeUui7/Qs0humPUKEBa0/Wkl9KQx/EtSSFYfMtJMdqk9SMcrFCqQx6fef8wCxU1aRJWMJEq/FKS27YWom+6hW/JDp7RsxVejAS8/l6iJlMA1xY8kA/ip9OrLlck28ODMot7UMUd/1MmTtCj2OqPok212H+T9/1lAJjqljX4jzinifAT9NYFBvrNMpw06TaK2X2/goJ6EF6G9Ay83MrNDNZMueCBhYbK794nkF1noCM5HHHBrFmzlAss0zI6XbiVrsUVSPeAjP3XWdIoKjMOmhugQv1twD121xq184Dc3dWoLIRO3pMTjBrs29MHy/w33rfedOfW70um/uP4XxhE66wZxXW0bJE8KgB97D8qnBwkcjpeeTNWOzhqTAxKzNRq8z7rhY6IldJwuvg5/fzxhoevwEKe1+kPi14mCm7DAM5at+emJigKTWC1W6Fqqxe2LvewTjdPe65LBR7PB4eNzroVNevmVL44dvbBgXy8hdr6YQgVDiSmXAxOuvw/scUA8LqgdeOnjgHrztFcQBAhQnLcX55vxWDyFqtqkD4QV6w9swAAVpGnhPB0JNiYKpXb75Nu20/KcMLVrc3K/AvJwiNJqqA3bpPZdfMXEtLY5ZnxeCQPoNziMdpEm+QZheQdT1W8TGwPst9Jf97x0JQA0hqzMFp45z4m9IaXOkqdtwAfNH52cJcNud3l3dQFzi52ut3Qc75bfKpDRpmETbIeZuqJ0JTx8yvLUTYJRUur+VyCGRXPoHQTdXmHKf4vNwmi8o7WLKWn5DE1J5tGhRJPWL4CRpjm2AKF90OFnhdzrSg35CD6GGqopf2Vv2VYspYGoQKQd+VZ2gj5+YdWwwgWIkMCnfxLdACwbanG3OG+dYiUOHU7DxYELVxMBKLwOOrMOxx1iCK9V5LTnwaI8DnaRYRWqvLb1v1sWV2vzGMS7akj6Drh72UD7+fv8Z8+A9xNhrRak6+qVs3KDLteuG35ULfK/HNxi5npT9HVuqGhtGh9PNWuUDq2wZ15nWeT2YswP0R4B1L2H+hzt95iEuoqKH/WYLe327UAx7BeNz2Cez1XyGv/PzWqW93SirwU9OkQGfCGZ5N9ibK3I2dIA+b0W4sI/YNRpyxG3elYcPbk0r+/qAmaKmFv3Yn/gCxevkZQrFKzgJvpKkLcBcVJ5W3unaKMx2QPycPHjFNr95VsH9ig2fZ/2mBo8d8TZYyxRLpLhg+Sy9ZHdxkaD5iUDAv8N/pZSJjAszBeUQD4GCyGIeDloDzf/r9pdkliNG0m8xR5FWDxCdz4spTYWDMUIPF3E+YEo/ZwU+l7Nl5I1bHgippN6po6VXmzIpyZzecJLEmZgMJSX9QgkdIhEmiBIrPx5KCDTO4c8xWB0LDW7yNiffY5UvP6q6uKSCLQyJb2RLTW3BBc6P9EGCNaIBTiPDmYOepD+KYkh1hhqKF4PftQMxht6DqU/4zivZKlHskuqUM87gygtgqrhtEE7KnpJA0q+vo2qgvp+PNF+PzhcyOcuRQt9Hmx9Z3mRhyEU4GIXtPDeikse1y1qaDAI2vocnxLAVr1rV5RtBEIYX/nFB18lPRyFzRUhU2WUeiXTMiO4EYtV+U4mxKJabqdnAYcaHuTnSKaGAgiywJBAeAPpgfzLZONZhh8+uqXQ4FKc/sNHlztLjXkzv8I8DE6jR7JP5lABYfD5vnLo4lv6V151ynm8j2NyTbl/lCl/j3zyibT3BRwunwhTALqduHiEg3upuiJ5nxWgZso6s3Z7AqB1eHZ2N59I7KahN7jAQeROY3zPi6vzZjFdRK2dfVM+/M/ANOlR/tKZd2Vlr2ToXya5XlbdozbmhqS3yDp6Yhguk8kOG/UiY9SocrjDg6RR8oFz4izEZBPKHxfUwv7IgBSlppVtDwd4XQ/CoqOXYJmbcp7ga6gt/9c2AUpMyhSKNT4iHVzadIgsKqHWSmqkMcaOBzHDJoiNc9Q5iJCk5iHxxUbpi1Ndf+eFqHKAgRXqKLJpkoesG4o56PSY3OYVySORYHEW3Tg7nuLzBWGZ2Bzz9XzFRcWtqmCwiwEVbf8/dpewJqcGehjosbY6KeTDJb8IYDSz+LgQhGDyuEgZIwzdONZMjjeYJQnlGIGJZ2aPD/tqi0PrKTzdPBQll8Zd5ee3bevyQBPq8H2k1jXsk5xK49zQtlhB0oiIEUpgk6SIf0D58OTw6XBvC+aUrx+CGhfqtfuBjmzBVGuZtGM1lrh8YNuD15AGo647VNNK5O70FoJE5+ckSMlQjyRt33P0GHFRO06jrAi6MjDPFmnyIhUfMnqYUJ9ehce7rVXkkvb/VSdcZuIRwFvvMXZwdKalf+fFcW+bbvpVbOpVeVg3RyNqi/hrKNtk8VyOOozEWBLHBJpM2DA2XJhkppHWb26oO5XGCXNvvSGkkmkXTkIH3wZ5G3GGt08uDzFjn4rVncgRvyMUN2HMEKbOgeq5I+kFJqkkrFe9xrME92sJA1WFPZlAMi5/gCSn4N9UAPm75vDIL4x0ZtUwdQ1FqNYEBnz0en3EMcu409O7vl13gEUoSipPPoEuX4oB3T9l0pDaowMchiDQf6ILosEksEG2EvCmMJkQ7v027GMZirnOlXEch5pBAC5JXVlF8jVywhtsGqzBFyVtKd7Gx3Dhi7c/9kYmILTswu69X6fFSfxM7Si5FolwpTVdd+afpD19V5CxHHxSlv9cKr37aZm0fP5MJrCqSWZ59qk7LEQhigmowCAig62O8ZhWO44eswWUH0QdVC0GLT7VSQyFxgf9x1ZoyD8oN4X7hVrQWOdcH7NUJRdt70NcoJKUq6Z+DCYk+hwUR6hAjYVXYZpLFLDdHoQFEyyltsohs5mSmM16IPDclScI6coB3Jws4I5ZJncnfDpczgd7f5k5o8mZZGLQcLIE+BO2d0XbCa3e5nEDZtlUiv8IOLF5+jxYPyDZO1dGP1oZc72QB6zIHD+R+mdXX+2BoA9XI8l5v+c4quCcNxrMyiDYCDe7WHAG4bEN+/Fas314QpFB1DJw9vS+Ho0sQQCfrEw94cy5he4NtZeqk2d/oZidNeOvVL2IZCBcS478b5mH40ZLSXq/fEi8wgzwFHuEdEg+t47D7xcMoTXitKGp+nTcG/uRswBdh3A3Fv97TSqDqotC/H+ajDYsP67AL1iAhoyzqvQfoiOlzOJJmz2oBp9LCtU8PaMMMyR6vN8gJdw53xpt7dPIln2wH9LnLHhyFttSiwfvgMFyxyRpt/4U2QGga0uMs++ngi1aCeI9VpWOVNnU0Kk0iXVjsJI/95rlsMYb4FZX3V+VKKy2x1UdCwdZpvXkNN1V25P+7GlpMwaiTa30L7qwxCMCT2P+jrMIniaDVHpE7JEG2X/3w0AtHJ0lnVL1rsaUG7g9IoV5IOf06F57+fnUUwzKvPNqOMEckLu9Rrdp9cu9ulJRttVXfrQJnAiALAhndYjiHcPQbASV60XteWzYbTlihibBhNfXQuH9ZCSRixHeLnEirdcZHFiYZN157JAmEqVpEdhwpVs0GTkQ0UGcX+A96ZK1RrqGZ9qKnuDz/4sLm5B2G5/78SWt8EnZKSEpxD7pUa9X9TxR+1KhQoH6LNnZ4PpwO7pWn0pXX1Wvw8mMd7X23UwmJoQhmeZmAG0LT0gw07KHxN1vYpiVuiknQylY0d2qE7dVN8C/6j5XYyRPkF+JRRAdeJZOOqS6MNGyiu8vJE5TEBoPvmdpHnfI32Eygm5xEwSfErxMVFkSIqGPiYlauXTk7G9q9SLEJk9riw0mUkNcSNnxJky2mxw9Y7SbKzrIieOvC4je3PNzsSgvZPojx8e4Xtk4xG0/DeQsK5iQLsdx3f4Yz46K9mactc9fQT1e34Gs2u4eC0cmBJ7WKUti4lFkxrBmrM9FoazJRN2r+feMjLS+U5t/U2Xykz+VfENLebjtdgsS9wcexwL4xTIp9hZApiDODiKHmN6PRDD0YHk5QsREBlgL5s08S5Ltm1NQFX03SzFIF7vgagYvxR8uiwe9XVIEzFkhtg6gi/JnJru6/NTjpUR+pTRS27BIrWDvZVWwV4lQ2HuAIojhQitb8chrjwJcfHTmodQT7a/6BCbJd05oLJT16zQnTyyTVYThrC1QMjHOzWoOwhJtkjoITMY4me9BCce4vxCnunERLhDDvWo4Jp3liGnhBEejoAq0Yfkxvfbfaj6Mw041NCiqPjcDxRUv/R8yxDgsHPeTYscrVGexgVRs7k8EaWqkDLGQyMrnDFYHt+HftErUbOj88qHKHaBZe3WIQPbU+scaCX0gVa1uQ4MXNPHvQHoZCRiTzQ25h4CYDR6nQYGLA12lFu/fIVBp2s38IaEt/VEOWZl/OzRCCkw9KeywXcce+1PHCLwdjlUnlcsvXOYf/EC33q1wRH4SViehvgSmGIwKnI4MJdZWlMMbSLA3+ot9mlVSnfEnbsdc4F5YlFzoLh9FQ7RmNOx1d/FMCOxhmZJohtBTY1JGG9E+G45URTT73jfbuoHl6IFLv7NsJGY5G+nByfsZhEaGzLfg7Qqz1HY7S1EhURd+e+2Gq05P+wedeAU22WCHxoOeVVX17gh6KqVUutF6H8jQvEP7geNbRIhplIrJVrVl0haBdisLdFY8g24WA58E3qagFGr+hHLEGM90vn+SkzhnKVZtn2vtvUsrkiL1fPYYknU8gPlfS+guvunjwLbGoNOZytdnP45jU3U2LIY2FF2Nxi9qjNRa5g/0CstZ0FG7D7uySIlgrCpk12uQPEaR0cniBYBSRwsbAmAEVdUahEMRZqSoJqaFrrfliDSPCbNfydT8CoNmsGXcl2GZE2dpS9JzwTAyQ9/6PyA6XTKvPELApHny7X/fhcr9KOFImRLFR2OvB74Z6i+i78FnmZHEnUwORwkHtj7PeY5FNlm7FR17WUsoSHh5LBb7ce2p/TXNviRzvj6MtItCzz099g4updl1IjJMJPF5KS0sAhmUnBsqT0dO31tdRRf5HUUB0SJ7E2yTsS+f7PCwJAopJkvYy7BTCClBUmIBkbDDyAehEMdQs99STpoIT5JAMbhcMYdou7u037MiEwJbq/o01Ik2ltAzS5ee8A0lX0gK2S1UoV+R5uuUIBpO20u/Cd5Ase2fXVWZTK1W7RsfC2maTyLthPpe0hvg2THMTckwTeSWqaAIPSpV4zMrWXefhq7LZXbTJ1Ft5qgjzh9292P9DYwhkfwH5XWi01irMmCNsraxgjh0ljOVJmtjrdyIlXPZK8FTTt2jEYITr9w60fzpduAq+n7z4KV/Y8qnzlBUm
*/