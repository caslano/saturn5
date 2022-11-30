/*-----------------------------------------------------------------------------+
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_MAPPED_REFERENCE_HPP_JOFA_091108
#define BOOST_ICL_DETAIL_MAPPED_REFERENCE_HPP_JOFA_091108

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/icl/type_traits/is_concept_equivalent.hpp>

namespace boost{namespace icl
{

template<class FirstT, class SecondT> class mapped_reference;

//------------------------------------------------------------------------------
template<class Type>
struct is_mapped_reference_combinable{
    typedef is_mapped_reference_combinable type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<class FirstT, class SecondT>
struct is_mapped_reference_combinable<std::pair<const FirstT,SecondT> >
{
    typedef is_mapped_reference_combinable<std::pair<const FirstT,SecondT> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<class FirstT, class SecondT>
struct is_mapped_reference_combinable<std::pair<FirstT,SecondT> >
{
    typedef is_mapped_reference_combinable<std::pair<FirstT,SecondT> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//------------------------------------------------------------------------------
template<class Type>
struct is_mapped_reference_or_combinable{
    typedef is_mapped_reference_or_combinable type;
    BOOST_STATIC_CONSTANT(bool, value = is_mapped_reference_combinable<Type>::value);
};

template<class FirstT, class SecondT>
struct is_mapped_reference_or_combinable<mapped_reference<FirstT,SecondT> >
{
    typedef is_mapped_reference_or_combinable<mapped_reference<FirstT,SecondT> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};



//------------------------------------------------------------------------------
template<class FirstT, class SecondT>
class mapped_reference
{
private:
    mapped_reference& operator = (const mapped_reference&);
public:
    typedef FirstT  first_type;   
    typedef SecondT second_type; 
    typedef mapped_reference type;

    typedef typename 
        mpl::if_<is_const<second_type>, 
                       second_type&, 
                 const second_type&>::type second_reference_type;

    typedef std::pair<      first_type, second_type>     std_pair_type; 
    typedef std::pair<const first_type, second_type> key_std_pair_type; 

    const first_type&     first ;
    second_reference_type second;

    mapped_reference(const FirstT& fst, second_reference_type snd) : first(fst), second(snd){}

    template<class FstT, class SndT>
    mapped_reference(const mapped_reference<FstT, SndT>& source):
        first(source.first), second(source.second){}

    template<class FstT, class SndT>
    operator std::pair<FstT,SndT>(){ return std::pair<FstT,SndT>(first, second); }

    template<class Comparand>
    typename enable_if<is_mapped_reference_or_combinable<Comparand>, bool>::type
    operator == (const Comparand& right)const
    { return first == right.first && second == right.second; }

    template<class Comparand>
    typename enable_if<is_mapped_reference_or_combinable<Comparand>, bool>::type
    operator != (const Comparand& right)const
    { return !(*this == right); }

    template<class Comparand>
    typename enable_if<is_mapped_reference_or_combinable<Comparand>, bool>::type
    operator < (const Comparand& right)const
    { 
        return         first < right.first 
            ||(!(right.first <       first) && second < right.second); 
    }

    template<class Comparand>
    typename enable_if<is_mapped_reference_or_combinable<Comparand>, bool>::type
    operator > (const Comparand& right)const
    { 
        return         first > right.first 
            ||(!(right.first >       first) && second > right.second); 
    }

    template<class Comparand>
    typename enable_if<is_mapped_reference_or_combinable<Comparand>, bool>::type
    operator <= (const Comparand& right)const
    { 
        return !(*this > right);
    }

    template<class Comparand>
    typename enable_if<is_mapped_reference_or_combinable<Comparand>, bool>::type
    operator >= (const Comparand& right)const
    { 
        return !(*this < right);
    }

};

//------------------------------------------------------------------------------
template<class FirstT, class SecondT, class StdPairT>
inline typename enable_if<is_mapped_reference_combinable<StdPairT>, bool>::type
operator == (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return right == left; 
}

template<class FirstT, class SecondT, class StdPairT>
inline typename enable_if<is_mapped_reference_combinable<StdPairT>, bool>::type
operator != (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return !(right == left); 
}

//------------------------------------------------------------------------------
template<class FirstT, class SecondT, class StdPairT>
inline typename enable_if<is_mapped_reference_combinable<StdPairT>, bool>::type
operator < (                         const StdPairT& left, 
            const mapped_reference<FirstT, SecondT>& right)
{ 
    return right > left; 
}

//------------------------------------------------------------------------------
template<class FirstT, class SecondT, class StdPairT>
inline typename enable_if<is_mapped_reference_combinable<StdPairT>, bool>::type
operator > (                         const StdPairT& left, 
            const mapped_reference<FirstT, SecondT>& right)
{ 
    return right < left; 
}

//------------------------------------------------------------------------------
template<class FirstT, class SecondT, class StdPairT>
inline typename enable_if<is_mapped_reference_combinable<StdPairT>, bool>::type
operator <= (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return !(right < left); 
}

//------------------------------------------------------------------------------
template<class FirstT, class SecondT, class StdPairT>
inline typename enable_if<is_mapped_reference_combinable<StdPairT>, bool>::type
operator >= (                         const StdPairT& left, 
             const mapped_reference<FirstT, SecondT>& right)
{ 
    return !(left < right); 
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template<class FirstT, class SecondT>
inline mapped_reference<FirstT, SecondT> make_mapped_reference(const FirstT& left, SecondT& right)
{ return mapped_reference<FirstT, SecondT>(left, right); }

}} // namespace icl boost

#endif // BOOST_ICL_DETAIL_MAPPED_REFERENCE_HPP_JOFA_091108

/* mapped_reference.hpp
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
*/