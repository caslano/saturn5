
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
UeIDDAm9PcCnT1esMuqzUXGtCiKg6K2SepyBTw14PpavWHVjaYe9OLj+XifdGCNZYSMtK7LReuQN72+P/jxg+42myVgq3oq6dt08Jrxu1tXhOjteN428u88ImbbeexC46nDbiOPuZ+jxAfO9iQbPJiciHSvNw2jESybd+jU4qLHcuLCh9cOD/jTSvKfSPxDXuVPart1XlTM3gZlHM39Z2eZpbYmBVRxTN1br9h19I8e7f+q5rLNju2j4ZcPUwL6YTXt9JPaJTJs8Xs7ki8q047SumXYFD1fVvjYY6uYLbLr/Svn68Vav0uKVMeGVKZbwFA0TbRLX7RQyzfq4SPi6cZukyzlk/zs5MpeRLVVMWxag31audXwho96+ge+S+/1F6fqb9rwu+u0T8UTtq/eRTBL/d7SFsE/T7Z1tOG/r7Xtdez6Pmqral5rb8xuIdWmYdvJRevaIvN1lGk3t+a14PQLe/h2zq1Wh7txU5c5kvHncdYxg2rvfOefHYb153/YQXzDQbfM5fIMFn0zpyzp8K6uWn/YQXmAw7Vkufe5bhnz3t39D1LTD6YNKVntk2bO13C+g2O5zJ9Ep+SIU7wKYPuwCZsE4WNU+FxQAxevT4UiTvNXd3Ze/OPKQksw2VTuwjw3H2JmqT1Pq2mOSuQkjrccmYoadfO0Js1BIqVrKdMW0Yr60+AyWN9HcJN/D6guqNOF3d+IZDBbd6fr6uHz7CUUpH2BV15p4H+f36+35PLg5xDbTc2ce69NzVzjtKU4cLU1GqotTm0P3fbMTQzD8CaRG9tJEOaqFkg8ZqzQQx2KkRnHkFb5sJe+vLUxLvr2CG1mM3TRNzM56Xxf2pUsHTH+G+PJIuZfu0A6gBrbyTWK5pLHB89JhhIb7x1NB/b2MBvvH2PVxtQOOeuY02rcZ0/Ye+WF0bVy1TR6YaJRfpFk9mRzVp+qHYcS7i9UgTrmWDmN69/wG+xP6bavG+bSdVEJVN0Zluht6I03yiAlro0y9vgRieX9ApEm94d/zMNI1zzte6bWqubmrq9u0kz9sIv8oH314RNdvgyelovHePhl6cq5XluXLt+D/YgmDdCcXal/evrxtbIv70uIW969UOPI7grdAl7vOGe9+uQn5Hep51Ai+oTbi2gKQYTYRVcbbTk+UauvySesRPD06Il8LmvJsCtl0R67g34Zf37bDcHTF8P1fXHxq79VvK+A5Rws2/9Z+4fa1b79uBc2FbgnNg1q4/iDogVwPQ2u53kNegdaRR6Ct0AhtMvRzJ2i72NDekXXyHdAE7ffeFAjcBMn6wZtcm/34PTAH25Dw1+P3TVx/A37fzPU34vctXL+r7AjjLtLW7zZXbNz1u2P9INfvMRc+ub54Lnxy/T60lzzfV+y5/gCsPxB6MLSU68ugBNeHoU1cj0P7oAD38fBcd7/ej9930L+svxM6yPV3QW/i+hHozVx/N+N+AL/vYVxZf6/E5fpRicv190lcrn8X+jb0Teh70HegM9CiL7cGl0A5qA3qg9ZAu6EENAUdhnbd3Bo8AW3F+j7oAHQM6gabB+2HzkAnwRbi9xB0HroZ2xZ+j0KXoLPYXobfa/jdi99TUC8Ug7ZAGegq1PKV1mDg/2C50fNpCt0J3wml5f70xxcH28c8Mg9aduEewSfePxB8JdkCaN/pewQ/dKdA8CZGz3y1NThXc7f/TGtQ93sE2/DrMvo9AfbANR5bBJ022FKo7cTi4MhWL62TSKuFfruh82f85X8Z2yfGvfy2QNfAtoY8H8u+1hqco+3jom+1Bl+q+bjwtXtImlV2E30shc237hgItmjxusG+ttZNaw7Lpg9MT6v0NeaX21u/5S+bErbH40g=
*/