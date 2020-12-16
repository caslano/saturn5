/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_SEGMENT_SPLIT_HPP
#define BOOST_POLY_COLLECTION_DETAIL_SEGMENT_SPLIT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_facade.hpp>
#include <boost/poly_collection/detail/iterator_traits.hpp>
#include <typeinfo>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

/* breakdown of an iterator range into local_base_iterator segments */

template<typename PolyCollectionIterator>
class segment_splitter
{
  using traits=iterator_traits<PolyCollectionIterator>;
  using local_base_iterator=typename traits::local_base_iterator;
  using base_segment_info_iterator=typename traits::base_segment_info_iterator;

public:
  struct info
  {
    const std::type_info& type_info()const noexcept{return *pinfo_;}
    local_base_iterator   begin()const noexcept{return begin_;}
    local_base_iterator   end()const noexcept{return end_;}

    const std::type_info* pinfo_;
    local_base_iterator   begin_,end_;
  };

  struct iterator:iterator_facade<iterator,info,std::input_iterator_tag,info>
  {
    iterator()=default;

  private:
    friend class segment_splitter;
    friend class boost::iterator_core_access;

    iterator(
      base_segment_info_iterator it,
      const PolyCollectionIterator& first,const PolyCollectionIterator& last):
      it{it},pfirst{&first},plast{&last}{}
    iterator(
      const PolyCollectionIterator& first,const PolyCollectionIterator& last):
      it{traits::base_segment_info_iterator_from(first)},
      pfirst{&first},plast{&last}
      {}

    info dereference()const noexcept
    {
      return {
        &it->type_info(),
        it==traits::base_segment_info_iterator_from(*pfirst)?
          traits::local_base_iterator_from(*pfirst):it->begin(),
        it==traits::base_segment_info_iterator_from(*plast)?
          traits::local_base_iterator_from(*plast):it->end()
      };
    }

    bool equal(const iterator& x)const noexcept{return it==x.it;}
    void increment()noexcept{++it;}

    base_segment_info_iterator    it;
    const PolyCollectionIterator* pfirst;
    const PolyCollectionIterator* plast;
  };

  segment_splitter(
    const PolyCollectionIterator& first,const PolyCollectionIterator& last):
    pfirst{&first},plast{&last}{}

  iterator begin()const noexcept{return {*pfirst,*plast};}

  iterator end()const noexcept
  {
    auto slast=traits::base_segment_info_iterator_from(*plast);
    if(slast!=traits::end_base_segment_info_iterator_from(*plast))++slast;
    return {slast,*plast,*plast};
  }

private:
  const PolyCollectionIterator* pfirst;
  const PolyCollectionIterator* plast;
};

template<typename PolyCollectionIterator>
segment_splitter<PolyCollectionIterator>
segment_split(
  const PolyCollectionIterator& first,const PolyCollectionIterator& last)
{
  return {first,last};
}

#if 1
/* equivalent to for(auto i:segment_split(first,last))f(i) */

template<typename PolyCollectionIterator,typename F>
void for_each_segment(
  const PolyCollectionIterator& first,const PolyCollectionIterator& last,F&& f)
{
  using traits=iterator_traits<PolyCollectionIterator>;
  using info=typename segment_splitter<PolyCollectionIterator>::info;

  auto sfirst=traits::base_segment_info_iterator_from(first),
       slast=traits::base_segment_info_iterator_from(last),
       send=traits::end_base_segment_info_iterator_from(last);
  auto lbfirst=traits::local_base_iterator_from(first),
       lblast=traits::local_base_iterator_from(last);

  if(sfirst!=slast){
    for(;;){
      f(info{&sfirst->type_info(),lbfirst,sfirst->end()});
      ++sfirst;
      if(sfirst==slast)break;
      lbfirst=sfirst->begin();
    }
    if(sfirst!=send)f(info{&sfirst->type_info(),sfirst->begin(),lblast});
  }
  else if(sfirst!=send){
    f(info{&sfirst->type_info(),lbfirst,lblast});
  }
}
#else
template<typename PolyCollectionIterator,typename F>
void for_each_segment(
  const PolyCollectionIterator& first,const PolyCollectionIterator& last,F&& f)
{
  for(auto i:segment_split(first,last))f(i);  
}
#endif

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* segment_split.hpp
/ALgD6HsQ6BTWV5q0LHnaGwvMs/9L5N0orG0l4nGz6J52s+8nOjMpvQgos28AjTrTQQy7wBDsjkwpGqpe4nBK10YeV1D475KOPdbDRp35FUChy6rvNGSQD6PwOvt+4SrvW0hE/I03sTafZHRIQ+vlzdxGnhz2j8MGm7nMNrw1YxGl7ZkP/udoh2dqUS87JnQn0EZxa9RkoW2/KdeA/wmb0hcddCJhb6H+toJjK4KltcnJnHsThpor5ukU9EV5p0ODFUBjUvQX48/8k0L7bWjm4/LRFj7doDMb8cbbLoumuQxnsSgWJrHtUm6FEXxGL5xAoNRpHn8a4JOxWZlOfsmjpFi6n7zM4MOEVnaI2/mNCmeTvstTqdWkbRDb2E0Eku99SJpYviL+bF5Z5hu0uk2i9/qxslS8D5wZRoWJZL8dl9yYngf0DK6sVQSrRMcepvAWa7d/K0vSafzCVyNXp8dLCw0Kj1sC9gbnGH89ryd8Jar9WNlOd302c6xsI24FrM+7hRG7N27k+8gvMPVWmKuEcbhfq4w1TsJM+GurNv8OwpTz+sYM1Sf9C4+0dg5AZocJn2+th96N+HqFqn3dHSFj+mQCnNG7X1wcf0cyqXye/R7CGM/sVFH0T6r34qocTd8ikPbUN/rwI+wTaY76+rs5X0GDm+pNAC1h5R0VhmiTg3fovcTprlIzOpC17n3AYkBkWrz7lKH+iDR4HpulIG+u0N96zK0PkQ4dP614dwCSajmhwuSrncs6FWa/h+bTumVnfbDRGeu8w+S5bpMNLqcVGt3dPlIvRf3UcJMddPXZb4yidUoxnP3xwg37ZoAq583aeyauHMDPR6DXNMf/XGiy001EGP2dtHDPwE6vV10d6kTNt+gEjVTkmznrZ9U35f7ok+xe5zD5o4ljOR1GmrJkegOCrP+TH5vtelQ9VPoq5CXMGdNDOQ9uzRm9zb+7npfeH1jZXZ1ZYHHwH8Z8emkzaIkdLu7E+2f+v4rPNNbszLNG5CGvmMw7Nu3n/H7oEE7sHcfo31M0/DMNKwHC7o8nzFpg/7g8QKgZPmipq8v7Nd3nr5sfJ9dRCgGIazK82uajs3LnOCpaN/iafeZ8nzXpO3f05AV/YeaPgd59+47ZKb/qYO+sKzpv5ykn+H031j0w5Z8fzbp+w4cNPlfn6SDP8aObFun/E39oeH2AqKw/5ngNR17i2dtyhdpNXYbsFP5ElaOiTtq7ALM88Ph0pxkrjA7HRhiqu7A3ZthFucWkMse6BTDc3sfv+cAyPtk39ilcJjwMK+Ah6rbh2oahos66Dsn6Y826f2lM3gVgNH3/E3dgYIzoj5GOEj0q39UdBwONvoOPyYk1aWZNPCfisfC71s8vuvj3f24l8LV3opzdYXj9veqPPPryJFxm25O0L3oet407qtEnV4QAF3HyT7MEoz2Ef69HJ/h+f8cQZh6PZbg8D5KMy4ozWcojX5PxQ87iLV00/d/MEOCX+1DPxb9oHkTZLy6tjbo0/e74Oc/noLvpP+NxNxP+H8Z3+v5FunQT4n+n5q+qhZ3haw/rWM9RL+iPFpPJV5yZhdzP/HZatNUVuh4hNkGDMur6SAsCc/zIKXZbqVZWd0kGfnwC1lpcSgLP9T2dvjm361Fy4oqrtbzz94C9E3kA0Tpv9cE9oZl0byzWwK/eTlQT2QHuDGW2Ot9x8O3Io2jHfle4nWEcbe11pf+UuPo8tn6HB69EP2tpeNoPL1lxNFAqMCiiDAaEbcBkVNgEEfgB9x5URplMyi2RHJM8PQ+gqIkXYSxCitvbgyDiIiKMq4DeWyMWPBacATvpdOIzKpiYhh8IgR+SRHUB7Fm5sBCXK3FjzrIqxg=
*/