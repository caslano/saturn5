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
h4uYsqLTIs1o42YKtD/mAe5n9xSsDmlgLp3JcJNtHVakR47ulkkibsP7UOhVDMvJdoPqJAvmv98c2NNK0KF0V/Q5diNukkCG7rw7hgenGaIW+wzs1DJmUHOhxd3SAdW+qYbrVKWo+EQbfNzHCkNPI7Btrx1AJp8Mu+MpgYR0tDHfR9ToxTJmlHXwDnqsX4PrRhvAqagBbCI6BvHFEUDLVQdVGpljl5qbIH/HMZSmWgdFEtewuUdF6PG4N7Zr11qkoOSJ+6UJQC4vC9qki4NLmy/mGGZNvOeyQRsGKeByQxC+quM+CsvSAa8j02A+J4rll19H3CKH8eTaM0j46ChQaEQC/6lG3CS4HTDvYSAXmoPkFfqwwW0QekcCUQFlLarpP4A8ajnAQrAZy5O8DdrXxnAZ+kSYPCqCtdpJQLjrcZzlphakfTHDKJOSkQT3BuAg3ktS3g6A9GuPIZXeD59SlERXvnhgIpfaINeWFgV0NUF42TwWuikCHZGph83VwUA9kQAtj9+g8Mwx/HjmVdRHdw2F8bOhDRytOK2MATQzcCMBKxsIdKjCSOvWgYf+C9TY3IDuHQkA/+ajcIDNBmu4EQwuuTPYB9MwYHyyFloumKEZ0edYIvcACrsPeNa59ejpzBrwqqFEGtEjaGffBJo7th2eBuVBwbIyxJC1Gl5otWHW7npokr0MyUjKIMWiR2h2Rxs6fP4jZNWmo2LcEbdhp4FEzQHkfVASrZJ9Auee3UMzzc+wbpUcJHOyEhcZJPI4Gw96cQlwZqMEDB7cBjKWW/AAG2biXdIwZlE3h85f9cHI52SRhrM19qw7Brxt87FIOS+wdTkG+Tepgb2lAp7SFKMonkEkVdENNgLZaHolH1x7dAmjWAMIbTuOxwtFoV1r/fAIHh/4LD6OB8dEoubZAvwM8byg6dIERCfKwei+OsyjBAHQH8W4HwUjSt59cHjOECU2PoBllk5o+WQxxLyNgAIsFCdcP4HeDo1g7du90LxfDj7e1YlajPqA8qosBEzLY35al5DcVCMuv5obuUq9xcVfPYa8l5Q4icVGqJCrwHO0G1HsoUJ4X9UPJVIJuK6sFkq7R4LJ3+IA8vVVcKH0JARvaQUeW14o0tXCISYVqtnHcIsv3UjQZx7cImTQPT7i3eMbFsQ7woilBkug9JQZoH5XjAI+keGNUzygmjuOES6ngLf0PriwwRnWmrohMQEX+HxeCVT3nAB6GRxOM3uC2TUz1Ex2G/jaiee8VgeQacIVvP9oGKr6NA2K/sboi8MjHA/mgnhfUrSV6TnErGaFLa+tofTwDqBsy4VaQwk8Y04N2g3fI6GuHvh4PAkVCkgh7QJ/qAY+FH7JEan2KkEfpSmmUUQB54X6MALXdiROsgwdvM4ASZWD+AtVcRiWzsXa9wtAwhFBPO4NHxKT50Tbjkwhe+L/a78t8IY0Jx4s+OoLCD74GA8c5QTF2g68piwP5dQMgNwMDdqqbQ1oOh/1btmNXHfIojERdkzcfxheXpLHJ83KgPPGM1SrLI4YY6PAqZYbXZW5AZxyg6hzxg1WDF6GJN3d2P499iiZlwRDc5eBnHYYP8gmDM3XePApX0lU762O17upIgbVKYzx/mUotC0ExRlP4HZLRwrE+2EwlcN3HU9G9So92BivFPDf/4CORNxArwS+IGbbVLD+0o3t9BVDFCVqaEvpfQirnMX6+20hasUD/FzDTdRcSsDT3l0ALW4jxB4Uiw7f6MM2PJWF9ppw9FZ4K6rzE8BTL9MhCbkPePPwdbjxdisUcZxCtYQq3JHUEiUOceH8zMvRmptnIWBKCJTbT6DsFatRzek+LIeZHFZo38Q23u4F0cP8+K0=
*/