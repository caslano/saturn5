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
dZ8jT9G8g4ykoJFHBHUSbf0AieLNfvuG+xfe8px0T7KsSGRTK7aJNv+QnDbwVzSuxvyEqAcieG4HBfVZwl3GI7ro8Y+5C1qGMeoC2R4KrrujAt/fNfJikXnTPITMlxYg7CISizq00xSiX0RSgrAK2lN4O8m1Iykg+F2Ajqugv2/gbwrN3bgVCwlZdPmFCSmpGJ4qAvmH90xiYvzn0eHPgfLhvSLETo68+IiZg8BDS50wQZaH3sLI63X6qZ4sQjS5jrBpVtw54Azochffk+OOqNNZxy4Sh3U0do7IO7ndwyBVtKoBXRwdgHKVhn85y/7g+JxheSe4kk5fp7tD0P1Bu2x/9WZlZJinR9oc2g7agOeRWY4X/uCOfByQZqrZq92w7Tx0TZqO3y211bLMTs9oajgrreqfiVjdXFlcop21JODgeprizs8DLhYeMh2h9LEfhI7YGZTs8XqeNrEKM9x8x57IGFqefhX9PrlwRvbci4k9SFZyQQeAxW//gHPn8C8v8Bx+yfTCHaVhXlZdvJy6ZNpzItOe5VpNW3XLgieisHXxvygQ0M1HS5oh1bV5UdWw6zkd5DwquEB0qcKzobYcMCihL0qm20sfX8PjxNchStrV45dhDv+7CvxDOf6hFP8wiz+/kv2+Ar8jx+9I
*/