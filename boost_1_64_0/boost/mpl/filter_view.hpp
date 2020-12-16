
#ifndef BOOST_MPL_FILTER_VIEW_HPP_INCLUDED
#define BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/filter_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct filter_view
{
 private:    
    typedef typename lambda<Predicate>::type pred_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

 public:
    struct tag;
    typedef filter_view type;
    typedef typename aux::next_filter_iter< first_,last_,pred_ >::type begin;
    typedef aux::filter_iter< last_,last_,pred_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, filter_view)

}}

#endif // BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

/* filter_view.hpp
PWbHuwjNpab8hbBPbZZy3bhccfNzCzhnOou6eR430ou88k6Xg+It0X4P7/6/b6Ph6DOyAgcTFUns/Yp8+Gi9T4h7n4x3q75cvNvx8eNLivSiifH53fhgpofi4Acc7+y9OAYopY7/e5ftfjWRmXEGg62oI7+cPnQu8ctxipkaX18oeX2Cb0WfYjQ4dfxbksTVeUm+q7JX3Il6fus2MYdp/LZDnRqgHeZsLNwnLlJHFn+utB9ZtJDlEx+MzMpVD5W9+f6Y6RzYouPME+ijmz92j/Wixwx+7BzrqgWnHHqADW03c+d2v7g3sj1nR5V6SFtJ3T/euPHHeNrjsVz+bbava7bCn9yqJZjX4Tam9vEIf7JPCSJl4S0siLSwIHLcVCWI7HPbNT8qvND6em1uBm1sS2VHNozva5lnt5TFnbackwcp+0Abr9sXT+/+uHdfyvmp/b/qTXrJS6SXPJNeHo2nF/Eil4DJCxXN/Hx6OjRTCpoZpWlmSKxI08xpMQmY/ZOpgDP8U7ZPD5B6JhO9e9FF6N1EsjKVQfd+5/CSVWI8n153OOin8iLQzvcXp6Kdq4V28iuJdv50VVu08/vJmnYOAmWNH8wpxQzq66ZfJZs38mCwWnZ+f/VQeQkfALyfGS3npPup7KwwsS2+tPFpXNq4jP5TR4nv/4RyS673OdcoyRV+BrlC9J+GvtzWKxsy+T8TG6D9LW3gYrFxDQ/xf85rOJ7ThuE/PMjNFCVSbxFgRGp8eLPevuh9Fkz7fiiLs+qSuwYSUiH6N4D+XUL/rqB/Lm+Kn1v+40mRnOFt/+fyeA/957nmrlGE51j6Vwj8bbhnZma6M/+LfzTv6f8Z1Ndb/5N+4JdJjdKCzBLt4nWivOODvAPWG2+vBcMuzYnl1yb/Djjfx/i0/OBLKT9ktyU/+CA/pE5HYdt7Xsr1Rcs/31Lyj1dUWSFjbInd9KWya6SAFwk4uI7rhcUuDUs9gh++kDgHuCf42R9utAyUUuOfj/TU62NO3Hv/uHfSCx/IeCT0D4YlaX9q/19aK8PDdcsiBcZCsVDX3cWuUmyLyp4ckCW9afSWY/zzlX4nVXpuO+k57aT3byc92E66v530QDvpee2k+9pJz1bp7cmPmK99wgV6rMQi6Eei8H5yNnbOLN11kIFvl54T5K8w4n/W2vfX9cXLKPLBCopdslLk5LsniWhF2rtOF+oDworIZeF1M4l6bo5U8vmP4AJ8j4nQ7m91Twpcs7bU6Ctq8FhXmB3TLRFrQ8bI7+Mbp4f3MAyP8YKItKR4/kKkGpwOBCDAkL9boLUqC+b6O4/l2SvmbitbOc8q5BlOehW6iGGCEgJPulOt66RbWwXTNyAbZl0h8K2ZpQ8L5IB6BWCtAayhddR6Y/dFCtbci7UaERqfnMhsgXW/hnX2LFvc+RzqszXEp1fFmbMEy1rLl9GGn7ru2Mg86brZKP7pTKdJtWzq5y48Mpv6dPb7T5LRLQTLLhAKT6hAB9gFWigauyCcx6U1Wuzk1BZORcuhzJdoGEQ4S+agkdyi9s9XhzPI4StZLVCVG75pW1bA2IZ4/d4H+KNOymys0cc/0p/ZxgW32RgZa+emJLAy6l4YOPqQkk28AEnB6KgApOFjGHiZ8UOuEK4YwfDPdQ0I6fXqtULRHbUh769MBEYKgXWAJhpjeihDyOvPxpeyAvczRiG6EhIYbc7k11T+WzmI/zHfEe8T5zmrZItJvrwIh2SoTqw8o54iVakaLpAa5IC1tbI7xk/1xyOSpnu2e+TY8ETaT9RzoKl3uSLd6yJfDAaFdBYnbPIzibpJbYcP2fjg5w9BfAjiw2GwBrDiX85j+g0cO50xOfO64kB2JuM=
*/