/*
 [auto_generated]
 boost/numeric/odeint/util/detail/is_range.hpp

 [begin_description]
 is_range implementation. Taken from the boost::range library.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Thorsten Ottosen



 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP_INCLUDED


#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <boost/range/config.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>

namespace boost {
namespace numeric {
namespace odeint {



namespace range_detail
{
BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(const_iterator)
}

namespace detail
{

template< typename Range >
struct is_range : boost::mpl::and_<range_detail::has_iterator<Range>, range_detail::has_const_iterator<Range> >
{
};

//////////////////////////////////////////////////////////////////////////
// pair
//////////////////////////////////////////////////////////////////////////

template< typename iteratorT >
struct is_range< std::pair<iteratorT,iteratorT> > : boost::mpl::true_
{
};

template< typename iteratorT >
struct is_range< const std::pair<iteratorT,iteratorT> > : boost::mpl::true_
{
};

//////////////////////////////////////////////////////////////////////////
// array
//////////////////////////////////////////////////////////////////////////

template< typename elementT, std::size_t sz >
struct is_range< elementT[sz] > : boost::mpl::true_
{
};

template< typename elementT, std::size_t sz >
struct is_range< const elementT[sz] > : boost::mpl::true_
{
};

//////////////////////////////////////////////////////////////////////////
// string
//////////////////////////////////////////////////////////////////////////

template<>
struct is_range< char* > : boost::mpl::true_
{
};

template<>
struct is_range< wchar_t* > : boost::mpl::true_
{
};

template<>
struct is_range< const char* > : boost::mpl::true_
{
};

template<>
struct is_range< const wchar_t* > : boost::mpl::true_
{
};

template<>
struct is_range< char* const > : boost::mpl::true_
{
};

template<>
struct is_range< wchar_t* const > : boost::mpl::true_
{
};

template<>
struct is_range< const char* const > : boost::mpl::true_
{
};

template<>
struct is_range< const wchar_t* const > : boost::mpl::true_
{
};

} // namespace detail

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP_INCLUDED

/* is_range.hpp
fLhgXS4/86ct/Jm98ptaxFTZcK7iVyfCEoIk64KroUCEW+i4VZjHpdTYFtA1ouiJwMyd91NXSWrwQuopybyQ2MHPzIR04gzkmlKTYikAVpkq6rkQfoP3+Cd0dAQ9CQ2/XzaFCE7v0lbhQyVyXTsiGxWy0laVwFcoC6gMUThda8iHEtFe/g/ue2iCjVK+iTCgsD+xV3zo/yFGKY/ytKoT8J3x9n9NyqFw7+Wl3GaS0M/Bzj3JVvhjLtEjgqizsDBkZS/zXnIjklF20I09tVTuu4sJ6chVga26vyj6DQnhqOjruODTiTQC1G93dxqPm398L40PsPdUJB528COMLZauboVT5AdZgm+TL50B/dt4/6FNQTs9MU8jIdcfm3hYi6GvdOirmK+Ev3Jz+pZMPv/CH/Mj6O9x56s8f7zqhTRC4AEB28GFeH94e2dfHXdgBUx0Hyt6FgQFKpBe0f56PgGix7D+dKuF+Kee4y3jYYmH7hc6HuqhZNrzJ0OSTV+j8ZwwbJqWLjpG1cCAAYe8YvbHBHIEYWEwiGcbtXXHFbOkf+u1zWY03evT6nu8r+Sl6U9fmpRXdEyLMOTRbu52Ikxrn9iETB7x678bpJHAECXJqDtBWSfrPowENPdFgB02dfusmfxGswtvfMzzijsQLFeSIUofI7tFz75Jz35RdHba7wgTd/mI7+aM8M3zmzAeXYiufPM8eq1u2UdcagtOM5bAZIQgPrk7td/DMXYiJQWcymC9RiIitYzAhvooUECfKkT8QaQjTNornvhbVNXK2UYjF+uN7CkbSWlvjUr7Hc8L7b0FfOJHzRGAekQ2gerVH1UQlwgCCOairTWSxutJ5+pJZ5NSg1asON7CeJ9I+FD/EBjtfQj1CYvgsaKUDDg63CzrLeHmXe534jeirsr5QfDspFOEzlAWQMXMKMCwfNgcgeVHZet//74By17OLZ47cTxMrUn/oDNQHAvP99s1eP47OuMROw9Ew/NucwSe18v6B8v6veLBA+3C87YDEXh+ychu0bP/naIp+w0HOoBnS6B3NLze1cLfoGUgQfo1J0P6LzjeqcHze+ZYeP7rcRodIbq2GPDc8l40PL9tNHKx3sjxspGU9qn3/g3wPCQKnv8sm0D1Rj8SUmhGZ30AkC4mFnDCaOD5hRF6Ro+er4ry6cCt6ZPIT+Jl9VRAStCUqK2r4riIhsP7ouDwIVnRwPdi4bB/WMJh//c7B4dR55ObesWeTyLyv/H0PoF8XZ8wDXEpiscp+l1zFK/8z6Pg9C8a/zcS0IGYmqtDp08MRqiEzgFKaQQ69UyXy0wttxgAWUAA2bPQ5HuSoBGrooTGfgSNFwMaaxQ7AyJo8txtJ+kJDHRXVumFF7SkgPHwBKAQ+Wimt5yhqBGQ02t+/h2ueSZA7g2MrE/kIkAK8dpP9yGE9n86PYPwedKAS72j89QOcmO2ECK5mRpjQnvnoLeSJONSpli11irlxMbygPHijEqUtSSlQMYTresgsQAr1+oBXnqOqhuWW52rrYcy3Ug8rmUmF4PqcGuXl6iXSXkyw2atDh/HQhfO7kRqUTLX+KM2LWrpbRAKlCutkZnkkQheYL8GqJ2/Cencr24Uyz9YI/qBcHp1OOMmyyNcFg5MCEllJsG8zA91SjXRfGGSYVwwKTBpPkcS8hI6fbFFShKPwF8xFeAIjt+3tXvaig/R92VGDxMOEr7gJcAuEFe+rQN2klJpJLGAZ4S0CstamJ2LrHRY8BaIy+VWSBXfZZZgoL5ac4Umn2AZT/IJNWjZ0Bdqis3V9pzynZBXaHLvcSy7jmhZzB3lDfceA7qJxns1koqZCm79L22OFb3IgwWFrpIdtTnWre8=
*/