/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CLEAR_10022005_1442)
#define FUSION_CLEAR_10022005_1442

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>
#include <boost/fusion/container/map/map_fwd.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>
#include <boost/fusion/container/deque/deque_fwd.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;
    struct map_tag;
    struct set_tag;
    struct vector_tag;
    struct deque_tag;

    namespace detail
    {
        template <typename Tag>
        struct clear;

        template <>
        struct clear<cons_tag> : mpl::identity<list<> > {};

        template <>
        struct clear<map_tag> : mpl::identity<map<> > {};

        template <>
        struct clear<set_tag> : mpl::identity<set<> > {};

        template <>
        struct clear<vector_tag> : mpl::identity<vector<> > {};

        template <>
        struct clear<deque_tag> : mpl::identity<deque<> > {};
    }
}}

#endif

/* clear.hpp
gk2XyWstr7eZtxfk2fG98NIsnm8et4F35TSvtTP53KBTSR1kcv1Fgv4yLLUnbhT+xvdl2IWTQZ7p++uYP8J87AxwbYc6zuZSzxd7R14W4tnxJB/kmfEEshaCfD2e4DyB4arDpsuYQ7J4XidlmhMvt1w+Nizeowzy4OkCbyvIs/10O8hT/fQUnzHVXDxwLPrp3h0tx4+X4IzubDl+POM12100x9t//PZPUeFqv+dA7l+wPPRHjAOGo+Z5XtsZnprjOS5qeGZ+P5Vwc4c018ztxIVOG25wXl+HDWX4ek5HXVoe9F7yRpaH+VDydgxPz4WoJ8Mz82AX9TSd4to5sIv1g+VC71E3hqN0fgDeNTQvvpJx1Vf2gPfPp9Mjymm5HyuF+7mLzwSVFO73/2o93TIcpafgbRue0lO2cQ3P6CnbW4Zr9LQLG3fWcPfV00nD13oKO+uahoe5hKpqeGog6tOkaeeSLcMJn48dWx7GevhMD1sO9w3Os2B44b7RNLzsvrFpuLZvoA8brpqPBiiz5WGOQT87Yji2nxmO7mfoP2nexnrUg9B/UrgPZQLf7gFfXFiqJ2f32Gc/0Dj0S56DH2qOPx/Sw1xicETT+N0uw0GEDJzJjTQHUS9wNg0HOsd5GQ7aCGXaTnHicKU4M3XG4NI+GyAe8ln4dY4WK9qPVFCY9gfVFBaPehjTrwg/VnzLRvz2o2u6xHUB7uZ+3OHycdozxn3nSplceu2xS9XD3O0wV72yCPs+zE3ig6uw0a4c5Hl14rsMd8I8FaSFn3M/bq/d7sf89YSfu0omv7G8QZtoV2nLwKqIlYT5MiB7BuNwFhdDLHO3wlxWZ+Ji/ZbNdcs3z2eZd7P4MJtzJ9F2YS6WhegP1wzzvHmK9tjN4K11z7RleyAGcq0gX+2l2AtzIlNAvuPey2fxEDxcQx1lc5O+sIY57Nr7cDsijrQ/z12kDu7kdbK5aR3f2Y+L65dZx/PXzeKHdbyQybd628zkWr3d2Yfrqtjz19GXM/lhPZ+4XpCvpm74rTK56BPgboW5YqoX+h7mxkMvT6briEUidqJjaRgj6QyaxPttWrnxxstV6OSO5jm5QCMe4g7Xl/m57MS54Y9wGm53tB+IjyNunsJ9hwM++eNrAd84i7jscb4DCN8704y8LGTituNNY7CDLg35Iv+LOukl79u9jOal7Zwd7F/xKSyf7rTk295PSuEry2xDfVZjfqwAvvs5jSdzJWyAL6Twjnjz2mJuHAA+hlx6hYH6uSzKHdofsgrb6Sk6HXQA8e5d74xOK7FbcafG5YCrs3S7L5e/w6vlug3XwSskJ8agR9BBFfPlO52PQk9wzu6KuNeAsY2euIvgiyhv1FrJ3SLwJ18eedKu/pbYsU9XAOAoHc9D21dI8+HiXceb0ZBF73vZOYlv07FmpD9Ocda7w+KJYbsvZcidMpxD7RMUeSIOyn1FcOT+mj7Ghddd2+LxO4zDvvCX7XxU8fQ4M2DeFvILxrrbkP09SC+9pweyTTz1gORgU4QTsNMS66dUPQyPD1x6dDM9+5xyH1P5qfFPvidZSKW14bZzyDEOeqT2GAGf+JLGuyuDnhzjRkjf7D8aYu65FnOwivAeCgpcLksbubkP1x3egK2zP4/2fJ8BdzObG58qEfPZ1n/huoSlf3gU5GOUciKfwVoWOqI8afy+mR8ngIv34SZuACy9PwKcJjhmXwT8EdvgBPdDtKDPOENk90Fg/gNH73+ArQR95/1arXYr0veNwfLJdo7fv97VXAwh3ug5iXFK9kd9PhD1kH+aTEtml1uG3muO8xKtttfR74mg8X737DmwxN16u1oePxxxHeReH8Bj/12bhj/XF88=
*/