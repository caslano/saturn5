//----------------------------------------------------------------------------
/// @file search.hpp
/// @brief
/// @author Copyright (c) 2017 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See copy at http://www.boost.org/LICENSE_1_0.txt  )
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_SEARCH_HPP
#define __BOOST_SORT_COMMON_SEARCH_HPP

#include <boost/sort/common/util/traits.hpp>
#include <cassert>

namespace boost
{
namespace sort
{
namespace common
{
namespace util
{

template<class T>
struct filter_pass
{
    typedef T key;
    const key & operator()(const T & val) const
    {
        return val;
    };
};

//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #           I N T E R N A L      F U N C T I O N S             #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//                       I M P O R T A N T                                 ##
//                                                                         ##
// These functions are not directly callable by the user, are for internal ##
// use only.                                                               ##
// These functions don't check the parameters                              ##
//                                                                         ##
//###########################################################################
//
//-----------------------------------------------------------------------------
//  function : internal_find_first
/// @brief find if a value exist in the range [first, last).
///        Always return as valid iterator in the range [first, last-1]
///        If exist return the iterator to the first occurrence. If don't exist
///        return the first greater than val.
///        If val is greater than the *(last-1), return (last-1)
///        If val is lower than  (*first), return  first
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found,
//-----------------------------------------------------------------------------
template <class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
          class Compare = std::less<typename Filter::key> >
inline Iter_t internal_find_first(Iter_t first, Iter_t last,
                                  const typename Filter::key &val,
                                  const Compare & comp = Compare(), 
                                  Filter flt = Filter())
{
    Iter_t LI = first, LS = last - 1, it_out = first;
    while (LI != LS)
    {
        it_out = LI + ((LS - LI) >> 1);
        if (comp(flt(*it_out), val))
            LI = it_out + 1;
        else LS = it_out;
    };
    return LS;
};
//
//-----------------------------------------------------------------------------
//  function : internal_find_last
/// @brief find if a value exist in the range [first, last).
///        Always return as valid iterator in the range [first, last-1]
///        If exist return the iterator to the last occurrence.
///        If don't exist return the first lower than val.
///        If val is greater than *(last-1) return (last-1).
///        If is lower than the first, return first
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found, if not found return last

//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
                class Compare = std::less<typename Filter::key> >
inline Iter_t internal_find_last(Iter_t first, Iter_t last,
                                 const typename Filter::key &val,
                                 const Compare & comp = Compare(), Filter flt =
                                                 Filter())
{
    Iter_t LI = first, LS = last - 1, it_out = first;
    while (LI != LS)
    {
        it_out = LI + ((LS - LI + 1) >> 1);
        if (comp(val, flt(*it_out))) LS = it_out - 1;
        else                         LI = it_out;
    };
    return LS;
};

//
//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #              P U B L I C       F U N C T I O N S             #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//-----------------------------------------------------------------------------
//  function : find_first
/// @brief find if a value exist in the range [first, last). If exist return the
///        iterator to the first occurrence. If don't exist return last
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found, and if not last
//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
                class Compare = std::less<typename Filter::key> >
inline Iter_t find_first(Iter_t first, Iter_t last,
                         const typename Filter::key &val, 
                         const Compare & comp = Compare(),
                         Filter flt = Filter())
{
    assert((last - first) >= 0);
    if (first == last) return last;
    Iter_t LS = internal_find_first(first, last, val, comp, flt);
    return (comp(flt(*LS), val) or comp(val, flt(*LS))) ? last : LS;
};
//
//-----------------------------------------------------------------------------
//  function : find_last
/// @brief find if a value exist in the range [first, last). If exist return the
///        iterator to the last occurrence. If don't exist return last
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found, if not found return last

//-----------------------------------------------------------------------------
template <class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
          class Compare = std::less<typename Filter::key> >
inline Iter_t find_last(Iter_t first, Iter_t last,
                        const typename Filter::key &val, 
                        const Compare & comp = Compare(),
                        Filter flt = Filter())
{
    assert((last - first) >= 0);
    if (last == first) return last;
    Iter_t LS = internal_find_last(first, last, val, comp, flt);
    return (comp(flt(*LS), val) or comp(val, flt(*LS))) ? last : LS;
};

//----------------------------------------------------------------------------
//  function : lower_bound
/// @brief Returns an iterator pointing to the first element in the range
///        [first, last) that is not less than (i.e. greater or equal to) val.
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found
//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
                class Compare = std::less<typename Filter::key> >
inline Iter_t lower_bound(Iter_t first, Iter_t last,
                          const typename Filter::key &val,
                          const Compare & comp = Compare(), 
                          Filter flt = Filter())
{
    assert((last - first) >= 0);
    if (last == first) return last;
    Iter_t itaux = internal_find_first(first, last, val, comp, flt);
    return (itaux == (last - 1) and comp(flt(*itaux), val)) ? last : itaux;
};
//----------------------------------------------------------------------------
//  function :upper_bound
/// @brief return the first element greather than val.If don't exist
///        return last
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found
/// @remarks
//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
                class Compare = std::less<typename Filter::key> >
inline Iter_t upper_bound(Iter_t first, Iter_t last,
                          const typename Filter::key &val,
                          const Compare & comp = Compare(), 
                          Filter flt = Filter())
{
    assert((last - first) >= 0);
    if (last == first) return last;
    Iter_t itaux = internal_find_last(first, last, val, comp, flt);
    return (itaux == first and comp(val, flt(*itaux))) ? itaux : itaux + 1;
}
;
//----------------------------------------------------------------------------
//  function :equal_range
/// @brief return a pair of lower_bound and upper_bound with the value val.If
///        don't exist return last in the two elements of the pair
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return pair of iterators
//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
         class Compare = std::less<typename Filter::key> >
inline std::pair<Iter_t, Iter_t> equal_range(Iter_t first, Iter_t last,
                                             const typename Filter::key &val,
                                             const Compare & comp = Compare(),
                                             Filter flt = Filter())
{
    return std::make_pair(lower_bound(first, last, val, comp, flt),
                    upper_bound(first, last, val, comp, flt));
};
//
//-----------------------------------------------------------------------------
//  function : insert_first
/// @brief find if a value exist in the range [first, last). If exist return the
///        iterator to the first occurrence. If don't exist return last
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found, and if not last
//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
                class Compare = std::less<typename Filter::key> >
inline Iter_t insert_first(Iter_t first, Iter_t last,
                           const typename Filter::key &val,
                           const Compare & comp = Compare(), Filter flt =
                                           Filter())
{
    return lower_bound(first, last, val, comp, flt);
};
//
//-----------------------------------------------------------------------------
//  function : insert_last
/// @brief find if a value exist in the range [first, last). If exist return the
///        iterator to the last occurrence. If don't exist return last
//
/// @param [in] first : iterator to the first element of the range
/// @param [in] last : iterator to the last element of the range
/// @param [in] val : value to find
/// @param [in] comp : object for to compare two value_t objects
/// @return iterator to the element found, if not found return last

//-----------------------------------------------------------------------------
template<class Iter_t, class Filter = filter_pass<value_iter<Iter_t> >,
                class Compare = std::less<typename Filter::key> >
inline Iter_t insert_last(Iter_t first, Iter_t last,
                          const typename Filter::key &val,
                          const Compare & comp = Compare(), Filter flt =
                                          Filter())
{
    return upper_bound(first, last, val, comp, flt);
};

/*

 //
 //###########################################################################
 //                                                                         ##
 //    ################################################################     ##
 //    #                                                              #     ##
 //    #           I N T E R N A L      F U N C T I O N S             #     ##
 //    #                                                              #     ##
 //    ################################################################     ##
 //                                                                         ##
 //                       I M P O R T A N T                                 ##
 //                                                                         ##
 // These functions are not directly callable by the user, are for internal ##
 // use only.                                                               ##
 // These functions don't check the parameters                              ##
 //                                                                         ##
 //###########################################################################
 //
 //-----------------------------------------------------------------------------
 //  function : internal_find_first
 /// @brief find if a value exist in the range [first, last).
 ///        Always return as valid iterator in the range [first, last-1]
 ///        If exist return the iterator to the first occurrence. If don't exist
 ///        return the first greater than val.
 ///        If val is greater than the *(last-1), return (last-1)
 ///        If val is lower than  (*first), return  first
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found,
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t>  >
 inline Iter_t internal_find_first ( Iter_t first, Iter_t last,
 const value_iter<Iter_t> &val,
 const Compare & comp= Compare()  )
 {
 Iter_t LI = first , LS = last - 1, it_out = first;
 while ( LI != LS)
 {   it_out = LI + ( (LS - LI) >> 1);
 if ( comp ( *it_out, val)) LI = it_out + 1 ; else LS = it_out ;
 };
 return LS ;
 };
 //
 //-----------------------------------------------------------------------------
 //  function : internal_find_last
 /// @brief find if a value exist in the range [first, last).
 ///        Always return as valid iterator in the range [first, last-1]
 ///        If exist return the iterator to the last occurrence.
 ///        If don't exist return the first lower than val.
 ///        If val is greater than *(last-1) return (last-1).
 ///        If is lower than the first, return first
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found, if not found return last

 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t internal_find_last ( Iter_t first, Iter_t last ,
 const value_iter<Iter_t> &val,
 const Compare &comp= Compare() )
 {
 Iter_t LI = first , LS = last - 1, it_out = first ;
 while ( LI != LS)
 {   it_out = LI + ( (LS - LI + 1) >> 1);
 if ( comp (val, *it_out)) LS = it_out - 1 ; else LI = it_out ;
 };
 return LS ;
 };

 //
 //###########################################################################
 //                                                                         ##
 //    ################################################################     ##
 //    #                                                              #     ##
 //    #              P U B L I C       F U N C T I O N S             #     ##
 //    #                                                              #     ##
 //    ################################################################     ##
 //                                                                         ##
 //###########################################################################
 //
 //-----------------------------------------------------------------------------
 //  function : find_first
 /// @brief find if a value exist in the range [first, last). If exist return the
 ///        iterator to the first occurrence. If don't exist return last
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found, and if not last
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t find_first ( Iter_t first, Iter_t last,
 const value_iter<Iter_t> &val,
 Compare comp = Compare() )
 {
 assert ( (last - first) >= 0 );
 if ( first == last) return last ;
 Iter_t LS = internal_find_first ( first, last, val, comp);
 return (comp (*LS, val) or comp (val, *LS))?last:LS;
 };
 //
 //-----------------------------------------------------------------------------
 //  function : find_last
 /// @brief find if a value exist in the range [first, last). If exist return the
 ///        iterator to the last occurrence. If don't exist return last
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found, if not found return last

 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t find_last ( Iter_t first, Iter_t last ,
 const value_iter<Iter_t> &val,
 Compare comp = Compare())
 {
 assert ( (last - first ) >= 0 );
 if ( last == first ) return last ;
 Iter_t LS = internal_find_last (first, last, val, comp);
 return (comp (*LS, val) or comp (val, *LS))?last:LS ;
 };

 //----------------------------------------------------------------------------
 //  function : lower_bound
 /// @brief Returns an iterator pointing to the first element in the range
 ///        [first, last) that is not less than (i.e. greater or equal to) val.
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t lower_bound ( Iter_t first, Iter_t last ,
 const value_iter<Iter_t> &val,
 Compare &comp = Compare() )
 {
 assert ( (last - first ) >= 0 );
 if ( last == first ) return last ;
 Iter_t  itaux = internal_find_first( first, last, val,comp);
 return (itaux == (last - 1) and comp (*itaux, val))?last: itaux;
 };
 //----------------------------------------------------------------------------
 //  function :upper_bound
 /// @brief return the first element greather than val.If don't exist
 ///        return last
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found
 /// @remarks
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t upper_bound ( Iter_t first, Iter_t last ,
 const value_iter<Iter_t> &val,
 Compare &comp = Compare() )
 {
 assert ( (last - first ) >= 0 );
 if ( last == first ) return last ;
 Iter_t itaux = internal_find_last( first, last, val,comp);
 return ( itaux == first and comp (val,*itaux))? itaux: itaux + 1;
 };
 //----------------------------------------------------------------------------
 //  function :equal_range
 /// @brief return a pair of lower_bound and upper_bound with the value val.If
 ///        don't exist return last in the two elements of the pair
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return pair of iterators
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline std::pair<Iter_t, Iter_t> equal_range ( Iter_t first, Iter_t last ,
 const value_iter<Iter_t> &val,
 Compare &comp = Compare() )
 {
 return std::make_pair(lower_bound(first, last, val,comp),
 upper_bound(first, last, val,comp));
 };
 //
 //-----------------------------------------------------------------------------
 //  function : insert_first
 /// @brief find if a value exist in the range [first, last). If exist return the
 ///        iterator to the first occurrence. If don't exist return last
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found, and if not last
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t insert_first ( Iter_t first, Iter_t last,
 const value_iter<Iter_t> &val,
 Compare comp = Compare() )
 {
 return lower_bound (first, last, val, comp);
 };
 //
 //-----------------------------------------------------------------------------
 //  function : insert_last
 /// @brief find if a value exist in the range [first, last). If exist return the
 ///        iterator to the last occurrence. If don't exist return last
 //
 /// @param [in] first : iterator to the first element of the range
 /// @param [in] last : iterator to the last element of the range
 /// @param [in] val : value to find
 /// @param [in] comp : object for to compare two value_t objects
 /// @return iterator to the element found, if not found return last

 //-----------------------------------------------------------------------------
 template < class Iter_t, class Compare = compare_iter<Iter_t> >
 inline Iter_t insert_last ( Iter_t first, Iter_t last ,
 const value_iter<Iter_t> &val,
 Compare comp = Compare())
 {
 return upper_bound (first, last, val, comp);
 };

 */
//
//****************************************************************************
};//    End namespace util
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* search.hpp
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
*/