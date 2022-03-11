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