// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/to_mutable_relation_functor.hpp
/// \brief functors to convert types to mutable relations

#ifndef BOOST_BIMAP_RELATION_DETAIL_TO_MUTABLE_RELATION_FUNCTOR_HPP
#define BOOST_BIMAP_RELATION_DETAIL_TO_MUTABLE_RELATION_FUNCTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/pair_type_by.hpp>
#include <boost/bimap/relation/detail/mutant.hpp>
#include <boost/bimap/relation/mutant_relation.hpp>

namespace boost {
namespace bimaps {
namespace relation {
namespace detail {

/// \brief Functor used in map views

template< class Tag, class Relation >
struct pair_to_relation_functor
{
    const Relation
        operator()(const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
                            pair_type_by<Tag,Relation>::type & p) const
    {
        return Relation(p);
    }
};

template< class Tag, class TA, class TB, class Info >
struct pair_to_relation_functor<
    Tag,::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> >
{
    typedef ::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> Relation;

    Relation &
        operator()( BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
            pair_type_by<Tag,Relation>::type & p ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(p);
    }

    const Relation &
        operator()( const BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::
            pair_type_by<Tag,Relation>::type & p) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(p);
    }
};


/// \brief Used in set views

template< class Relation >
struct get_mutable_relation_functor
{
    const Relation
    operator()( const BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return Relation(r);
    }
};

template< class TA, class TB, class Info >
struct get_mutable_relation_functor< ::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> >
{
    typedef ::boost::bimaps::relation::mutant_relation<TA,TB,Info,true> Relation;

    Relation &
    operator()( BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(r);
    }

    const Relation &
    operator()( const BOOST_DEDUCED_TYPENAME Relation::above_view & r ) const
    {
        return ::boost::bimaps::relation::detail::mutate<Relation>(r);
    }
};

} // namespace detail
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_DETAIL_TO_MUTABLE_RELATION_FUNCTOR_HPP


/* to_mutable_relation_functor.hpp
Q9a6+NbFmu6hTTrRnu7fLP7dXgzWg21v2NO1JpgAwopEsC2YBD7I8iXsXgHWA58B64MHwAbgYbAh+CHYGLQj7iZgENgUDAVTwBQwFRwNpoPFYAb4HetMBe/pWg2kPYvBVmBf8A5wGOtMn2ad6VqwA7iF3QfBTuC7YDewCe/Zmgr2AFuDt4IdwF5gV7A3uADsCz4K9gOfAAeCZ8FB4HlwCHinBfm4zjU2VZ/w6638xm/8xm/+n82v1P8vGFMy7obM/z9s6P8v4PX/PfG7Gsps4zwvcZ/s/3Pad47zufaf+/KHyP/vFNYHcPi6IoL7xcZz17mvz36qyzm1e11u1bTvL8Os0PcHe9PpXox02+D3fYvpGv8eCHuMws7lc9rccaV49d3dc0J30fUE45x+DqPwGeAyDvVOpZnXuVI8b0rm0ev8Jr6n2+n6X3AHDuz1Yq/Yh5R7wh2ntJ5X+ijQc/Bebxvekvdg7BMiDM9zp+sh6PGpcq54A0rvBewA8JwSxfN8v6K4jyk58NlFCeHnrPcDq/D83v2uMkRccBvK/wuUU4V+nexLDyc/B/HdZxVDUAMD0TdTxPWdUXTsLb3/FfSWdz/jyptSJvtG3+gy2Tf6XJfJOTsf6jLZXzqoy2R/aZcuc+09B9krUpbN580Z+jbcX+lE/RLvs5x7mvRv8kzW9w/16t9A9h/Yl8ml+SYnjj5StPvT/T9env3WmLaOBLXydfsb3O8St0FTwEjYZ2CN57JEgfXB6uA0MBqcC4ZzH+Ym8FkwBlwPxoJ/B2uAX4E1wZFIpDZYCNYFHwATwUVgEvgKWB98HWwAHgEbch8mE6wPNgNTKukrHPTRX8jw9xf8xm/8xm/8xm/8xm/+J4wFdtQv1/8vmDxyUknRhPH/ct8/Cn2pTHzw5j7sHD0tGDV22OgSZJl0AgcMOoFuCv4xnEHXB3ZeVej5XTqBW5HxPn265XO25LpuXCvlsUi3375XPUe+inNevxyjKfVYv/s858PGAaywL+DKCp/5yHcuFL5qeu7+Ua5q1n8xm/9uNj/dvF9zJID2LwuO3J6fkfFGa2uj7Im1OsSanaN6/eeT3qj1ByWzSH6ua9rWzi90+/jgqqwVvZ+8iH1pNad8Zf89lpD7f1wfv/lIfP3lXVqbzd83Owf2+vuh17tXc7nqlLeJG3lx+pDRjbTJo4OmnRp5COtFSf7eks/ebDuy6Ol7z08dvil+rfX61yuY9Iu538p1nd8Xh2Lot3J/1b0+wQJGg0HgzWAweBMYDtYCo1l+E5gA1gKTwESWJ4GNQFgai0tjeTqYBmaBGWAblueCLcFuYC7Yh+XnQJo/wvm2cb41StdlwjnfEaAVjAS3K4Lmt59cFnDVPYadZxvmwZbyuYZHfcyB72QyD954/mF92L6VzIm/ZDIvfgPPjT8KexnW1/x4OkfxKvPkRxjmyj9fyXz5BFg6h/Ea587nwA7lOfQLYJ83mUsfzfPpuxnm1BvPdbxUYX59ro859uLJABH3pF/34Dd+4zd+4zd+4zd+c6PMLzz+X1CK//OnZKZkT07/l3UAzr7+jhhnfyGU8ovPRzItYUNgm8GmQUcQt4f62EVpk/L7tOub361zn740tr6omoB83MjSwgkjDPP/2X8SzYdHX4P8vhhP4/DI/NiiklLdb0fyG0TurnpYGj9+IsxzL62e8noNOQadQ+5qhrMCi8aPGDlezi0IB1PITx1yF8k4wuTY8zwee86qRFcQxeO5uGfoJvieDWO6uD/I5f3JfdRwDx7zWPOkfkPPJ/QQ8hlEa4JMfX4GtWF/Qpplu/kZlOQXTygqmTCey/VH38+A/df22PdFo3UXk4eNZX9dpb9o8oc=
*/