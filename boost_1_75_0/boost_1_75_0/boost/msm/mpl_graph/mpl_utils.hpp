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
JjgjCaceUBt5YQ1DrbeTVMPzIYTam7ibBcRpZglldlt4oMc/PxYQOmfJT8cTyZ0wnn/YuKxhucmkrcirLjBbomg9ZMjnzJO0deokDan3S+S9iQCPQ5sPqUXGDeg+p/S66dCiF7WHDl5ADrgPbuHmJbpvgMewuJvTyx6J7hWv0tdbid7pZvDimk3LsG2H6k2IR/gk0/oMQ/pEQPXmlXlu+Nh5T8sBdvH0Mopt5UzYeREgiv9OzJVqs8zxFzDu5NnQsrkYIeQoMiAEXueJm58TZJ+eHlgybGOwuh08fEJoGhI/+kDzFO31JmJ1KeZkIXOuwTXqWWCr1gPrU8ArRV1cCa34/WcRRGrTS4QcVma9mj3tUpc6Gcu9TbhfKMl24BSQJ2dVDL6/1ZyqG5Cz2l8f2ljL34JlE3uKd9D3sg1+s4CpSnv1ynvqSzYiGXeyNCoSuAUdLL6XqJudtf9rKecizpUb/lIC0kNU6mn90MMr6/Z1YT94YD/sicRzRkhwIXHoO9sbCoFiTNo6xfU7or5mW1ApnQnzmJ3ZmOC01rcCoRLXs5dRoCTv/op5ltvCF+0ouh4JZuzeG1kYSFrEGWAHD2194gWQ87fDWnxQvFE+QytXCwJQxP1e7Ktkkrncol9+PNS0fb41zPWlL98GVf/8lChkS4T7vR7IuCIr9bTQDtRzTK83gRBiouysWGKYBEYVy7Wbz7AQwgcYAxs/
*/