/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_CONTAINER_HPP_JOFA_100923
#define BOOST_ICL_CONCEPT_CONTAINER_HPP_JOFA_100923

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_container.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Emptieness
//==============================================================================

/** Tests if the container is empty. 
    Complexity: constant. */
template<class Type>
typename enable_if<is_container<Type>, bool>::type
is_empty(const Type& object)
{
    return object.begin()==object.end();
}


/** All content of the container is dropped. 
    Complexity: linear. */
template<class Type>
typename enable_if<is_container<Type>, void>::type
clear(Type& object)
{
    object.erase(object.begin(), object.end());
}

//==============================================================================
//= Size
//==============================================================================

template<class Type> 
typename enable_if<mpl::and_< is_container<Type>
                            , mpl::not_<is_icl_container<Type> > >
                  , std::size_t>::type
iterative_size(const Type& object)
{ 
    return object.size(); 
}

//==============================================================================
//= Swap
//==============================================================================

template<class Type>
typename enable_if<is_container<Type>, void>::type
swap(Type& left, Type& right)
{
    left.swap(right);
}

//==============================================================================
//= Iteration
//==============================================================================

template<class Type>
typename enable_if<is_container<Type>, typename Type::iterator>::type
cyclic_prior(Type& object, typename Type::iterator it_)
{ return it_ == object.begin() ? object.end() : --it_; }

template<class Type>
typename enable_if<is_container<Type>, typename Type::const_iterator>::type
cyclic_prior(const Type& object, typename Type::const_iterator it_)
{ return it_ == object.begin() ? object.end() : --it_; }



}} // namespace boost icl

#endif



/* container.hpp
xpObHl8WWtdxb+vDTU+SJ93dfi9rwYf3X3tyu8QvceXFde2y4r+7Vm5x79C7Fe7anHVWhO1cvyyv28HQh+V3R06bYNy5yDrq2hProTGZ05qHBHZMvBNy88zW5z+42r/jqu7LX//6QdtLm2+8miWkn74+sWKFszc7rV4/bPMvOaPn3Clb5HvD0i//UrdNeqvzmzq8dSsxfFp2mwN3P+lkili2d1WFPbqYqutmjb1w52K17pNPnb282X5iT6cSa8fuGzX4yoCfBnU4+krPA4awI6v2rwo/lPfz9amRp/Z90yyhzZQRG57cajFyWrFdlz7Ov3hvU0avcR9/vWvF0vzSY67PbjW/d4PyZRZsjK4+9maTz8s3r73iz8VOvzDvbIvpE+vu3HH9x/c2/lRhwOmRkbdsxvS7F/bEbh86oe+cd8t2HGquO2P9qvEnGl+IGn1l8vLfXz1/dXrSkznf3Br8TeDp+f1jT3508XhLQXAM2HKmjLN8U9Pg3uPmzt/cpG38xHI2U/fDdXIWvDbi3OxR2x8999zgUa9tmnaoZ+t69c+W6rN52Zh7E35IDX7fPHD0NauDqr4aHhU8IusEGU+X6l6kS633150dPMy044elqy9drz3j8OX9y5tfXv7pW6Z+xSOm6FvMvr77z0UvNyo7oM/0FyYWP5tZ1fL53Qvl1pStHjNt1IqfzlWJPdG6d+6duBeq46j3w33pkyeVfrHs45YDf1zaqlPg6Nebtys+uYyx/TvdR/9l2KRSM9+p1bBlt+A3Q3OvbjwUUqxH3dAyXSfllpo4a2nSoYGG0jU/S1s1scSJh+Fz7+i29bJuNvWp93rpOpdr5r//UbyQcfPapBUfzVp6f+Y1+n/4f/h/+H/4f/h/+CeGcUU48LBuUIh+E4B+JRhSiuqpECG8kHKeEI2rUULojadSExLiDO60IcvsyrCZvO3UAcej3HzANp/yz/1KfVGpRfX21Ge3Zw5kwk1Pl8OvkmaYHUT4nU3Cr+0CUaHDrz1zm5plTOX/VM/bOiwmQgUxVi6Dd7N1zEy3OfDLplnEg1limE09pFYIAD3gtiVEryMpVCdAlnY+2yId1of0kOdBB4gFbWxViaYHlHopRB8g84MAiT5l2JFu3FZbxiugNY8GTZVvPmjBA5Vy41EuVzWEUoAlqnJ1gOVO8MuR/ncq2hbIfBNG3vas9mnb1+D7zXem/xxuG4x3rKnoOsC5wUo/9ADdEKnsG6ijFPBtn7LnLC2vb5NGmjL01hD9kHpKGbFDtO2rbi1EH528HaApv1XaEvkm1VT6/coQZeyCAHFW/37no39qXag8NERfFPgC8lYHXu6T597v8Xt1IaSfo2qLHTJ2lDNXLicIkG+V2kequduJscNYeHSNMydDbmscoupxt/5tujJmqFZXDqIcr44PVXS8MuB2gf3SztMVyNxWzX+Q0gelX4pOFFjedFV5pWw8b6HL87Q9Klnb9jCbtu2xNv/1mWjTrs/3krU6Nszmrwv6LO0a0AHGQO6NVK2eTQbtvRiJFuCZH9CWJEu0IjJtEWjvDpJoOo8ug0ZZRZW2DJP07TbaF0RYq7aQZ47jNsjo7UU1/TkCmviSdhyvgGaA3EyVfuvsIfra1UhfTE7/jtcvhRBAZfuz9aKly38eDTkh+nW2opr6q68oj3lU6goyhmh0P7wQdfn2IaiAPriMWr3vDL6HdwW84jKvLuAV+z9ufF+y83Hw6oa+gLEJUY3NTFlfKgMy7Vq56oCRdknvZ8o6ZACMkeSeOU6r7T7rSKnXOxZLUpRx0gN2Io/ajo10SmumAsFuByn0U5DbGE76ij70C6AXNZO+kg/9HuidO5C+ig89KDtEP34=
*/