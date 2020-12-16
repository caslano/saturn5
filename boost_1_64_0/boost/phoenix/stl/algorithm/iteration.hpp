// Copyright 2005 Daniel Wallin. 
// Copyright 2005 Joel de Guzman.
// Copyright 2005 Dan Marsden. 
//
// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_ITERATION_HPP
#define BOOST_PHOENIX_ALGORITHM_ITERATION_HPP

#include <algorithm>
#include <numeric>

#include <boost/phoenix/stl/algorithm/detail/begin.hpp>
#include <boost/phoenix/stl/algorithm/detail/end.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>

namespace boost { namespace phoenix {
    namespace impl
    {
        struct for_each
        {
            template <typename Sig>
            struct result;

            template<typename This, class R, class F>
            struct result<This(R&, F)>
                : result<This(R&, F const &)>
            {};

            template<typename This, class R, class F>
            struct result<This(R&, F &)>
            {
                typedef F type;
            };

            template<class R, class F>
            F const operator()(R& r, F const& fn) const
            {        
                return std::for_each(detail::begin_(r), detail::end_(r), fn);
            }
        };

        struct accumulate
        {
            template <typename Sig>
            struct result;
            
            template<typename This, class R, class I>
            struct result<This(R&, I)>
                : result<This(R&, I const &)>
            {};
            
            template<typename This, class R, class I>
            struct result<This(R&, I &)>
            {
                typedef I type;
            };
            
            template<typename This, class R, class I, class C>
            struct result<This(R&, I, C)>
                : result<This(R&, I const &, C)>
            {};

            template<typename This, class R, class I, class C>
            struct result<This(R&, I &, C)>
            {
                typedef I type;
            };

            template<class R, class I>
            I
            operator()(R& r, I i) const
            {
                return std::accumulate(detail::begin_(r), detail::end_(r), i);
            }

            template<class R, class I, class C>
            I
            operator()(R& r, I i, C c) const
            {
                return std::accumulate(detail::begin_(r), detail::end_(r), i, c);
            }
        };
    }

    BOOST_PHOENIX_ADAPT_CALLABLE(for_each, impl::for_each, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(accumulate, impl::accumulate, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(accumulate, impl::accumulate, 3)

}}

#endif

/* iteration.hpp
UnyJlfkyW3Mtj+Q6HsdXOJSvcgRf4yi+zrP5Bq/mm7yWb3MB3+VT3MC1fI9f8H1u4Yf8nh/zF25iSWX1CQ/np+zKzZzMz3kRv+RcbuE8fhXqFXV26Cdm21Dutfw7sz93kwPsn83Zji3Zia3Yg615PI/gaWzLITyS5/IoXsAOvIFH824ewxd5LF9hJ27hcfyGXRi57ruyIruxBbvzcPZkR/ZiV57Cl3kqP+dp/JqD+CuHsry8pbABR3AYRzKdozmTY3gxx/J2juPTHM8VnMC1TOebnMSPOJmbeCajv8+FPmKsG+f3uRbh+24bVuThbMYj2I5t2ZtHciyP4llsx7lsz4XswP3s/2gmsyOr8VjWZCdKj/lcM/uB2Vc4zhnPL4TjPDt8fsxhEueyEq9mDV7LVryOQ3g9R/AGTuCNnMqbeAFv5lzewpu5gLfxr7yfi/gUb+MLvJPreA/f4RJ+wwf4Ax9kYWl9iAfyER7EpazFZezFR3kiH+PpfJypfILTuJyX8Wlex2d4H1fwYa7k43yWz/E5vsnn+SlX8Su+wK1czd/5Iksr0zWsxpfYgC+zCV9ja77Fw7k+6/t66MvG0f7k/L6+ZD/HhUtZi8vYkI+yOx9jHz7Jyfw7z+VTvJHLuYDP8Cmu4ItcyVf5LL/ic9zKVUyI5I9JXM2mfJHN+RLb82Uex3U8ma8wla9yOF+j/LmIM/u2ub8I9xU9/HsiI68P9hUfNzKJH7ESP2F1fsbW3Mx+/Jz9+TVncCvncRsf4Ddcyn/wbX7LLfyO3/MHVpKYH9mAP7Ezf2YP/sKx/JXn8zdexEKRcmRhPsYiXMti3MF9eeA+NmMd7s+GTGAnluQpLMVxTGQaS3M2y3ABy/LvPIgrmMzXWJ4fswJ/Y0UW8fldmcV4MEuzOlvyUHbiYUxhDY5kbZ7Luvwb6/FR1udbbMgNbMKP2Jy/sgUTiqr/WZut2ICHszWPYGe25TAexdFsz/PZgTfwaM7nMbyVx/JOduYyduHz7MoP2Y3b2J0/sCd/Yy9GHiTpwxLsx/I8nnV4AuvzxHAeuo8L/fx89wrn4en+/Us4D49wnEuyLQ/iUazMDmzIjmzLTuzD4ziYXTma3Xghu3MWe/Nq9uFN7MtH2Y9/5/F8mSfwC57IrTyJO9ifyRJ7MivzFB7GU1mPp7ELB7AnB7M/UziQozmb43gtx/MBpnEp07mGk/kRz+TnnML9lMlZLMFzWItT2YDnsjnP4xE8nx04jZ05nT14AXvxIg7ixRzBWRzFSziBl/MaXsGbeCUf52wu51yu5VV8g/O4gVfzB17DXzifCY7xzUziLWzKhWzFRWzH23gsb2d33sHhvJNjuJi/8AEWd549yFJ8iHX5MBtxGQfwMY7k40zjE7yUT3I2n+J8LudCruByPst1fJ5vcRW38wV+y9XcwTX8lWuZ4LxdxyS+wqZ8lc35Jo/genbg2+zHdziQ73IwN9D14Lm+zL6U8hzuB2pk/J4ankcKnzup7MRh7MHhHM0RTOMYTuZYTuN4XsU0/pWTeRfP5nM8lx/zPH7B81lMnNN4AC9kZc5gbV7MrpzFAfwLL+ClnMfLeD8v50O8kus5mx9wDn/lXO4TOW+YxGtYk3/lCN7GC3k7Z/JOXsa7eDPv4V28l/fwPobPt9CvMtLfMtfnm7bYML8+k3glK3EOq3Mu63AeW/Fq9uU1PIk3cCpv5IWcz4W8ibfzFj7GhfyUf+VXvJUHFpYvJvJOluPfWI93sQnvZmvew368l/15P4dyMUdxCWfxQV7Oh7mQj/AJLuXTfJSr+Bhf4hPcyBe5nWsYqV9eYg2uZV2+wkZ8lS34GvvydZ7MN3g61zON73E63+c=
*/