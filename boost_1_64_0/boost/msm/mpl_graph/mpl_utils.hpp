// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_MPL_UTILS_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_MPL_UTILS_HPP_INCLUDED

#include <boost/mpl/fold.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/and.hpp>

namespace boost {
namespace msm {
namespace mpl_graph {
namespace mpl_utils {
    
// This is a grab bag of little metafunctions I expect already
// exist under some name I haven't looked for

// I figure there are probably better ways to do all of these things,
// but for now I'll just write some utilities to isolate my ignorance

template<typename Seq>
struct as_map :
    mpl::fold<Seq, 
              mpl::map<>, 
              mpl::insert<mpl::_1, mpl::_2> >
{};
template<typename Seq>
struct as_set :
    mpl::fold<Seq, 
              mpl::set<>, 
              mpl::insert<mpl::_1, mpl::_2> >
{};

template<typename AssocSeq, typename Key, typename Default>
struct at_or_default :
    mpl::if_<typename mpl::has_key<AssocSeq, Key>::type,
             typename mpl::at<AssocSeq, Key>::type,
             Default>
{};

template<typename Seq1, typename Seq2>
struct set_equal :
    mpl::fold<Seq2,
              mpl::true_,
              mpl::and_<mpl::_1, 
                        mpl::has_key<typename as_set<Seq1>::type, 
                                     mpl::_2 > > >
{};
                                       
}
}
}
}              

#endif // BOOST_MSM_MPL_GRAPH_MPL_UTILS_HPP_INCLUDED

/* mpl_utils.hpp
mHEsnGR4uMOWtq+xeNpSbI4+6Khn4yxohnkzEqbeQ0NWdFXFJnAlkEFA0Y4dFiimfAuc6fgv6ngUoYA1a0e4PWCv7uLORm+qu5RzShv+unBOoZdbPe1rWrkhXXNxTC/Bq5MZ7COsd2FHfyss3MjNwpKB3Z/hQ2Qo4orLO/TPHPXclATMCTBsdydlfUXb0J1BxRaoIs5NUeKLur7wRW5C9aU6/MvR7lHwPOUjEC8vCmJ/cDCWCLKfdLVzHC6pGR7/YYs3YWametoHXL2v4LQL8Yogu13Gg0W+EnuB4WtMxSNUdRAX8DXWctSAyOZ7/nFXLb8HJW9mdykqMBrTuZjuwxoedU2YsMnhxTkdhOY5OnGN9xCElfdj172790CKraim96wUM6MVJIgm3mNhn41YqO90jftDDIu4tBWIqWG+f1O8wasq37FOh3kiZiH1i2W9f27T+yeBP2oIEsp4CJkyFltV/3xF75/ATTA3ms5AOP9YoQGgjPnrri7rRmESnP5FB2VqXOsGxZZ2dZlOM0Q2SWaZjktLd3lPuUPnRXeFXjtTrm5oBcXa3OL/m9Hm8JMC3w5JLBPgN0jRQHT5CMm+WJdNe1Huwly1rfBXkWxfWC1ZSkUonSNaOiH8N2dh0c5byv1NmRV2jaqx8MGPqzaaSccP0ghTUDS5vMs7Ta2fgjDKokh19Me7imdC5ZXy2KKpy6+iVuJDpgZ8zLZ+ihwB6Kxdvbk09ft/HCHWqJsqAgTyK1PvJUBZB+ZqWic6cDWAnoO7JcPX32pV3isqnrmUxstNDrdnGXs80LmWqvl4+7M0nyRpHuUIqClLa5RtXrXte7V6enhLaXeyKFTqmY2V4VAlQW+ory3tI+yNVN5pZWyLz5VYubuJeyToPK07SzpfQBBTu7e1MSc9kqWDOEucIn7aMaCDfgHRfOg+W9gYmY/AfLDEyJXepN9e0mnZFWSMW9xtTx5s0AmF59L13RVX2sgK39o+cPwO7De5eJzzd3biJ7tZjivqceWRSbWvbSr5VLE4U3xTGbPcDypaSDSZqCrj/xzu34dq+5PlLHGHdxPO6nc1vVt3whl36MYe4GSbW3oWGwZd1bP4mUFT9SxOLICmjDnzbn6bQVfv5gdv0mnmHXhOdH08avbENRjTT9/5m22M6qfvdptOZaF63gMYZUxb9TTpaj33ajRLD2HO6NaIIreackzcEzh+37f7WynLVwhHfSb1su5V0WS7q+35faLr7aG2xbl7VxhZJ7Wcv2V0fpf/r+Xc2CdwNeX8LdHqy9m/D9F3LOcdhJHlVO/d5+/L6dMue4jFuqj6ML0fo/GTipS9yLvQrftLOo7JXZw0wUc+uPFdrLHEp+R57QGgi7s+T13yfveBkibvNJL3zQdAZ35WqLxyrvz2P6RdS2wdSRW1HSdx/mbITDzBgIEAAQIkEzvJQCDdrz+v/93EzjAIJOP4veDHOLbl9wwGgRSkLCLEYkAsWIDEYpBmkcUgDdIsIogQnwhlEX4iSLMI0gghyCJIIwFSFtzqrr5Vt6o6H0AyhHdP3bpVXd9b9/Mk0My5wRDz/FMqRs/5dVvD6Dm/PneAYZp1CjcZ/RF0Cs9PqDhdp3CbY6RhYNQpnH5awxGZrup0o0ynDmo4Tafwmo7R4m2eehtilGVF9xH6oRlLY9hOGjFaDM3v6TgiH8Zw/QR943JzyN7uPX7On/pMdeOzcmzMPIWpFqdRGYdadVpZxncxucyMC4d123bs6uUQ4JqtwOQn5ftbDsnT2rYXQx18npnqOEzKOH6QtuDpQsSBPloVsPF9FfBy/vvCD+LUtVzvLAZkQexpGTsT5mBnl/q5xWZODbbZO8KPYM6/XNo=
*/