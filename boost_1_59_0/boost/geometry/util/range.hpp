// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_RANGE_HPP
#define BOOST_GEOMETRY_UTIL_RANGE_HPP

#include <algorithm>
#include <iterator>
#include <type_traits>

#include <boost/concept_check.hpp>
#include <boost/config.hpp>
#include <boost/core/addressof.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/has_range_iterator.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/mutable_range.hpp>

namespace boost { namespace geometry { namespace range
{

namespace detail
{

BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator_category)

template <typename T>
struct is_iterator
    : std::integral_constant
        <
            bool,
            has_iterator_category
                <
                    std::iterator_traits<T>
                >::value
        >
{};


template <typename T, bool HasIterator = boost::has_range_iterator<T>::value>
struct is_range_impl
    : is_iterator
        <
            typename boost::range_iterator<T>::type
        >
{};
template <typename T>
struct is_range_impl<T, false>
    : std::false_type
{};

template <typename T>
struct is_range
    : is_range_impl<T>
{};

template <typename Range, typename T = void>
using enable_if_mutable_t = std::enable_if_t
    <
        (! std::is_const<std::remove_reference_t<Range>>::value),
        T
    >;


} // namespace detail


/*!
\brief Short utility to conveniently return an iterator of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_iterator<RandomAccessRange>::type
pos(RandomAccessRange && rng,
    typename boost::range_size<RandomAccessRange>::type i)
{
    BOOST_RANGE_CONCEPT_ASSERT((boost::RandomAccessRangeConcept<RandomAccessRange>));
    BOOST_GEOMETRY_ASSERT(i <= boost::size(rng));
    return boost::begin(rng)
         + static_cast<typename boost::range_difference<RandomAccessRange>::type>(i);
}

/*!
\brief Short utility to conveniently return an element of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_reference<RandomAccessRange>::type
at(RandomAccessRange && rng,
   typename boost::range_size<RandomAccessRange>::type i)
{
    return *pos(rng, i);
}

/*!
\brief Short utility to conveniently return the front element of a Range.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_reference<Range>::type
front(Range && rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *boost::begin(rng);
}

/*!
\brief Short utility to conveniently return the back element of a BidirectionalRange.
\ingroup utility
*/
template <typename BidirectionalRange>
inline typename boost::range_reference<BidirectionalRange>::type
back(BidirectionalRange && rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((boost::BidirectionalRangeConcept<BidirectionalRange>));
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    auto it = boost::end(rng);
    return *(--it);
}


/*!
\brief Short utility to conveniently clear a mutable range.
       It uses traits::clear<>.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline void clear(Range && rng)
{
    geometry::traits::clear
        <
            std::remove_reference_t<Range>
        >::apply(rng);
}

/*!
\brief Short utility to conveniently insert a new element at the end of a mutable range.
       It uses boost::geometry::traits::push_back<>.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline void push_back(Range && rng,
                      typename boost::range_value<Range>::type const& value)
{
    geometry::traits::push_back
        <
            std::remove_reference_t<Range>
        >::apply(rng, value);
}

/*!
\brief Short utility to conveniently insert a new element at the end of a mutable range.
       It uses boost::geometry::traits::push_back<>.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline void push_back(Range && rng,
                      typename boost::range_value<Range>::type && value)
{
    geometry::traits::push_back
        <
            std::remove_reference_t<Range>
        >::apply(rng, std::move(value));
}

/*!
\brief Short utility to conveniently insert a new element at the end of a mutable range.
       It uses boost::geometry::traits::emplace_back<>.
\ingroup utility
*/
template
<
    typename Range,
    typename ...Args,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline void emplace_back(Range && rng, Args &&... args)
{
    geometry::traits::emplace_back
        <
            std::remove_reference_t<Range>
        >::apply(rng, std::forward<Args>(args)...);
}

/*!
\brief Short utility to conveniently resize a mutable range.
       It uses boost::geometry::traits::resize<>.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline void resize(Range && rng,
                   typename boost::range_size<Range>::type new_size)
{
    geometry::traits::resize
        <
            std::remove_reference_t<Range>
        >::apply(rng, new_size);
}

/*!
\brief Short utility to conveniently remove an element from the back of a mutable range.
       It uses resize().
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline void pop_back(Range && rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    range::resize(rng, boost::size(rng) - 1);
}

/*!
\brief Short utility to conveniently remove an element from a mutable range.
       It uses std::move() and resize(). Version taking mutable iterators.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline typename boost::range_iterator<Range>::type
erase(Range && rng,
      typename boost::range_iterator<Range>::type it)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    BOOST_GEOMETRY_ASSERT(it != boost::end(rng));

    typename boost::range_difference<Range>::type const
        d = std::distance(boost::begin(rng), it);

    typename boost::range_iterator<Range>::type
        next = it;
    ++next;

    std::move(next, boost::end(rng), it);
    range::resize(rng, boost::size(rng) - 1);

    // NOTE: In general this should be sufficient:
    //    return it;
    // But in MSVC using the returned iterator causes
    // assertion failures when iterator debugging is enabled
    // Furthermore the code below should work in the case if resize()
    // invalidates iterators when the container is resized down.
    return boost::begin(rng) + d;
}

/*!
\brief Short utility to conveniently remove an element from a mutable range.
       It uses std::move() and resize(). Version taking non-mutable iterators.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline typename boost::range_iterator<Range>::type
erase(Range && rng,
      typename boost::range_iterator<std::remove_reference_t<Range> const>::type cit)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<Range> ));

    typename boost::range_iterator<Range>::type
        it = boost::begin(rng)
                + std::distance(boost::const_begin(rng), cit);

    return range::erase(rng, it);
}

/*!
\brief Short utility to conveniently remove a range of elements from a mutable range.
       It uses std::move() and resize(). Version taking mutable iterators.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline typename boost::range_iterator<Range>::type
erase(Range && rng,
      typename boost::range_iterator<Range>::type first,
      typename boost::range_iterator<Range>::type last)
{
    typename boost::range_difference<Range>::type const
        diff = std::distance(first, last);
    BOOST_GEOMETRY_ASSERT(diff >= 0);

    std::size_t const count = static_cast<std::size_t>(diff);
    BOOST_GEOMETRY_ASSERT(count <= boost::size(rng));
    
    if ( count > 0 )
    {
        typename boost::range_difference<Range>::type const
            d = std::distance(boost::begin(rng), first);

        std::move(last, boost::end(rng), first);
        range::resize(rng, boost::size(rng) - count);

        // NOTE: In general this should be sufficient:
        //    return first;
        // But in MSVC using the returned iterator causes
        // assertion failures when iterator debugging is enabled
        // Furthermore the code below should work in the case if resize()
        // invalidates iterators when the container is resized down.
        return boost::begin(rng) + d;
    }

    return first;
}

/*!
\brief Short utility to conveniently remove a range of elements from a mutable range.
       It uses std::move() and resize(). Version taking non-mutable iterators.
\ingroup utility
*/
template
<
    typename Range,
    detail::enable_if_mutable_t<Range, int> = 0
>
inline typename boost::range_iterator<Range>::type
erase(Range && rng,
      typename boost::range_iterator<std::remove_reference_t<Range> const>::type cfirst,
      typename boost::range_iterator<std::remove_reference_t<Range> const>::type clast)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<Range> ));

    typename boost::range_iterator<Range>::type
        first = boost::begin(rng)
                    + std::distance(boost::const_begin(rng), cfirst);
    typename boost::range_iterator<Range>::type
        last = boost::begin(rng)
                    + std::distance(boost::const_begin(rng), clast);

    return range::erase(rng, first, last);
}

// back_inserter

template <class Container>
class back_insert_iterator
{
public:
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    typedef Container container_type;

    explicit back_insert_iterator(Container & c)
        : container(boost::addressof(c))
    {}

    back_insert_iterator & operator=(typename Container::value_type const& value)
    {
        range::push_back(*container, value);
        return *this;
    }

    back_insert_iterator & operator=(typename Container::value_type && value)
    {
        range::push_back(*container, std::move(value));
        return *this;
    }

    back_insert_iterator & operator* ()
    {
        return *this;
    }

    back_insert_iterator & operator++ ()
    {
        return *this;
    }

    back_insert_iterator operator++(int)
    {
        return *this;
    }

private:
    Container * container;
};

template <typename Range>
inline back_insert_iterator<Range> back_inserter(Range & rng)
{
    return back_insert_iterator<Range>(rng);
}

}}} // namespace boost::geometry::range

#endif // BOOST_GEOMETRY_UTIL_RANGE_HPP

/* range.hpp
7jXzNKnu5eoIIy4ZQo72Bos/gNBdPtuIQxXtu/lvjfqry1DOgd7rvBLRyoLP/jeZ9c/7HTEWpg/z9FLoBLnpKMriNAOMQ5i5+b4j2bRyajksHIoW/eu3LXm4Od3BHXl4O2az2P6nnzpy24a8FEh8wE0A/+sZLiuPzI5DSo8LqbnQWrNdeKs6LiBai/F/HbSefqOeyN+Z4r8O57vBvaULvfKiOhBXQk0jcLuMMelLR3z3M1y3BKwn/YHg1pLGyd4jSy25BD+Bh7iy2QVe20veJTTtsBRT5qzzRDurdMENiWZLXIAY+pNd4XaHzoigRUlnpMKwZ4n0RLEgR+ozypS6FWbH0aUyZ04f22inrhlf1ThRs2Pc1ifBs+TuOUHVLTg/7J+DiW+deNP4akbhvfuC5KL1lO9ttMvUn7kstABieAeOplzVlP+dFCT7hLDZ7s9dT9Zf9zkHqwUELHjsjOBnXsbh7nRpJQ/QbCa7nJX/ggMA/P5GecPqKy0/u20UkQoSAGqWaRbPBLQVEAGKwZghKkZieZHO+cnvncYZ2+OXuasHqzJYP1/HTyRR2sAYBDxkWv0TiAImBC0S4aQIUyzOXF5271SW4aMRoXr9/v39DVgAAAj8E/Qn+E/In9A/YX/C/0T8ifwT9Sf6T8yf2D9xf+L/JPxJ/JP0J/lPyp/UP2l/0v9k/Mn8k/Un+0/On9w/eX/y/xT8KfxT9Kf4T8mf0j9lf8r/VPyp/FP1p/pPzZ/aP3V/6v80/Gn80/Sn+U/Ln9Y/bX/a/3T86fzT9af7T8+f3j99f/r/DPwZ/DP0Z/jPyJ/RP2N/xv9M/Jn8M/Vn+s/Mn9k/c3/m/yz8Wfyz9Gf5z8qf1T9rf9b/bPzZ/LP1Z/vPzp/dP3t/9v8c/Dn8c/Tn+M/Jn9M/Z3/O/1z8ufxz9ef6z82f2z93f+7/PPx5/PP05/nPy5/XP29/3v98/Pn88/Xn+8/PH4DFv/pv731n2m9Jze1/v7/EdztzT3M8b947TndayYbtxmyhfJ8HGLA36zmH81qoHapYu9fjzCudn7FgwYC55gbdyzw8K/rthpYzNTMb2u3aonHbapCR2ErkDaEivZ3gdFcxz5b7eINX8zpTQ03SLZVU72GwH3mX+9ebLevYHN3OwM6uWS9olfVbcp3xGlT1dUa7cCyHle761KKO0z95cUwqo0Dw4NunkEiZhQKMFnkBSOL6jaFTp71m4dwO0+tDDFrKTgEES5KGkhpY4b8Kk54epqbJQ9eL4jqjvy9eZGeOMViYfwINWKsBxfM3QKo7ZYYnrhoZs7V5kGSaxdYc/B7y1vdag7Yhmh6C+BGNWumu914Km89TkqQz/1Ej6P6D/HB5pWpUpQQtlnQGjRIs16RFSJgwmb45qIDlpIBqNxKxwPVtwZNvNTZwKqJdGzQuvIiQ4H40hYW4qlJ8ed3kfE8hDZ9qcTNhYR3faYcF/O+Wj9DEljTgRaWd1bNgChAEooQBFNCegRoGUnNk3b8VxW0QsXJ0/UcyLU3PQIiKXnVznb73kFtdJ9SsWkYvJ8O8MVcxhw+mduIR9u7zxQHH1JmHlPnA9tn8rbrawl/vSoqnAUJgw5+AliIWGaUFpaAAPOUV0GrYjKTIQ0An7a7vjN2KD0zdTBtgU7uZds1lNuUeW2zj6paqRhceoFI1OD9HjRYYS3Ei7TGOe6GeEkiioXllOQCXnfWYqB0jOQHtNL8PQaCeSEEWHaSyLROXNKXvW94zXnMZhOMix+SLNmEp3TFqFLW9H93foZ81c6MyqYnQP9mJkpSHsN16s8Uab5Y19sBGeXtant9+GRs7qb10WZeuMU4b/n1zbWjFsesZ4WnyGO2T0vO/FhQHFvGqwzEOuGavLX4O8Xo8WZ5HHojgVJGMcpDknKcPDroRk2o3lA1D890+7uciTWofKFvCIgRN6HGAhymyvHR5VMPtekqaEe3gspQlZKt15bx81JI9NbLhZcPqMlAGEw1qqns5/RUay2MAM7azCFg/UiQHFvt2GR7C+nK+AMmaHMHwnfVJtlG9zj3n72nD6PlJpbsDOfNt/7JPd3jmRWQH3JWM855gqAryvWzaDo6fheGIs2LyDnTFgBrWshU0h2shN/idAG9nAQ/CnphuDc/r/NVJER4KvOwgFd8dUJVOwZrttHdlB1e92NKEg+PGe02WoDdgt/s55sjy7ZIUxpZ37lAk2jgec6insxudrrGfVtApwmKMGCIjhuBeYUW9HkU970bp5vNN/w2NbdAZb8dQdesegbtDuUfGPq8yC1qCoRnS4qrU6t1sQwgVU3UWMo9pttO2Br7VkElKcJ/w7Gt8aLmJH/snrp0Q6KhsnXJ6yGVjOInufluZWE1frPwX6ilrnSziWyoOM8G7Gw/EPq53Ny9SIitOS1cnIsvRngR1z0mWNqJDeeMcXvKQeVMQpPv31tMiDJBctnoAmFQZobEvpYF/Lh90LhcNfQ/K2s4Vkya3qnyKExeoaolGCx76Ng/6Lp7gpxFbEEE08GXOLAcJsO2DV7BpkCI3zrpJMi/iS2U75kBgbrH6xwZowedOY9EPCQdxlRoHsRmo7RrxWn7U1A7Ys1egBWpHi801YP/5eyWA6OyLO6Fd2Ogbs9u9N5XZHKTDgAAVHaY1WVzhc8yN10T7Bfd1z2E6Gejgt6unajnW0+2kOssJL5wVY44N5x7IrZ+gRwVMPhNyACMJURk6YHfeO6pPGT+/3JwdatdAgyKei2eS+gGO0mXt9PHESEgh0jLhdFqt3aKM1qQQ3rkW2G48vMJAvJ62HmQ8lBJIiTMrAMjw18C50/HjTQ8ZattIJk34K76EnU18ZIoz/CNYM9J8HmQJteMMjL+103QhRIeHOXAotHiqGG1j9pkmzHK8sUngQyb6N9WTtTS+PosH3J5mfUcP0+uv9G1vHtHvo2rtqi2CzBVEGwn5oswRsoa85y4So7gA46VOadBX5Gbic8iALd7CrRZ5YeJ+YzK87EfNc1SRmpQwKCmRfVCjJvlSv737ZKeM8BMjKIMVitSjQMkF++iGRcLtCcyuaD/W7f+N1AfV7oowzetFPHMrSnLBvn2l30lmaEGc6trQn2hQ7vkWAVDk2C5gL6I/oK/b5pWGGuuHuR70bymX6uTLRenIfJXPD1oSb8+g78qFKEmdzzRdccFp6BkSAZ0r8DDcDwOROdN2IODqGJ+0T/DvyiwFvJqSEJzYp5iQbTxWA5ZtlLS/fxv41YbC8P5Q0K5naGi2Qo+ZWoaRBo5XX6lMYqE2piW441drR4nVpYeZ9JGkepgZmZAzHTCbUAO90b/1FVFCSsMRdXC4GkUMcFCQp5JgF1B346fXN4O/oOOfFx4dAxMytlyP7FMG6bJcLxQHgOelcopNKQVcC1UrwvAqI2G4nIPj1Qtuj1wnJijOdvZnToEtiNBJ1f6Bo+FDhIj3Nuxs+nqxzf9qR+WMFar+j5d5/vpfKQgYSqOvQjJxZFzvMLSTKzlUV6YyAMSTJYk8OHPol9ghd+Fapx6U1X8fC36CkZHvxBzcTDBYJpcU2Yb44+eT6j2phpcgwxNcKO7kilXao4pc/oax6tS8wteCNlXO2aINpAHJnhpQ+rOBIJ2+QIqDNgVRGV1SkC5sUtl5iFZptEGaF9v+7K0K2qGtwQHswYpmHueskKTbrC8k+jO5EUEWt2AnbcAUDFF783cWOjJ1CYdJHmvuJPrKqZkR9e+3ZGT6mNJ21gRgv5GQ9v+WQ/p3upFMfk//TcXYkjvh59xpaf8C5q3EcufHgSwkFG/YhyW/Wd2GxFsN28P7oJa7tQrt+GNduxQ/4I39xLqp7tAEXW1MYN5thkaXXlhxB2lYoTsNl9OwFisWerWPLCQiroBrfcnQtEZPg+3TYQ3Ek3sYTasRwLUgwbX0Vuzzw9zUQ7L/8P9z1kwoa7QT57tQPs3A7YVLnC+Y01PpT0aqYqwfztsdmQSdpCGgnZ7AOugfFC6fKARkSskSJp2G9OhtIZ8/Bg/8dMa0ws4sotiUK8cPvmFF9Uxut57YSvvXKpW+CUxV+chjOVxZRozuv9wMGcyvgQYf5To1nWAdcypOpFM5t3sG4enqLzSTEBrp5B4naBhkfSHSFXjzLl7Twn3Uwj1XPGHobswjum5F04hhnFlPA4zumngQQLpY0IaBRKHM4X5PcprOW3YSl3nELKbhuAe1vA2REPnZ3rqWqsKH1FQ2rm8q8qCQH06t9wkl/z6BEAhKLSuzr8iaFkGs3Dp830Q3aKVvWk+LjmiPFlhDC3gTpFGCdsQfHd/08X1XS6LKp45r5E8BkbptXlxCoyV5/wPwFS8GCr5I3WjsbAc5Uf1ON+J9w5n3U+5ainFSGViPIb5mruNQQiLRg8Okf1YCW2A3POfSAwpNszAGVo3G4GuajvspwYTf5zKQJEoaq5YP4oKOoGXHZ/EV0sfPWpC8luyVqJkMi6AmeuTUTAWd69ZXopovkCj+WOqHam6y22Tfo1+vH+g48HrImX2HUPGfyTOxZ+vBxtVa8ERxcwMTKOZyjOaqizJA5D6+ep39pjtXJuiFerVlJeTxgK4y+hIgHp0tKKomFvTVCeUTLAD4Bh3ggJhrf4CTtY5SpIdQnVVl+9dSSnOdU7YYP3Ucxmlw8MP1Pv0Nfw415LH4Oguwj2VgsKqBYMN4HkQkjQl07qHhtSUkeKg/KU8yDLYayBv23XYYET5YT6UfCF/jMR6FRw2iCNaRyYo3vyAmOwsDd2HlTu6D4Y4AatI8ZyG1wwN3z1Q133phG5Y/TX7Y36YuFM1UP2bKjyr6Gc9aq27R8uMMOSkvlaxZszkTZaJWJLPeYHPGd1+jIFwrH21H4KgeeX9FdSyAXKntRKXzYmxb7EbR65PpBqDSvk/XMbS74tUdDA/HmbMG5TV5CGrIT0CRudjJaG73ifoQFv31YjL76MztExr0VhcuF8sCWf0LOv8jNkSHLmccw3/UnvP68i8HNNB0PTqZRiNM/pHdH1LyB9IhdrhpIB08BpQvBw57DiEbMVKXrMUEeR0NSQEqFdRcgL2KwZpAn2XoYgbysYMES3h5w4Tqy2AeULPaQG2mjqX5h8RuRSjMmFJb9/krRBom51tUXP3VAAByjHaQJAsudRfQ0roypThTId/QUcFIJZjQUV2w5z1eY0E/xdr+UPVAJCaW7KOk+y2Gy2xOD7+54TAu/+FJey3LHs3U5HCrSZdvRM82rfAXLq4kc06icOditdG47WAwrMeKRr8ULka84WkX5jswaYTjQXIZ1gJv3s8Feehzqsr6ldMYPFCcBr9dvStxe5/YLDwSMH2bUOhqNcs9Ftdx5RlmXeKmk0nP3LkRy6pFf5cpmilONb+jORSjZASDkyvrJ6wVHOfRFQEHNoJN0obwd1ikuMVzsI8gaJuw0ixsU2LK42Co+nMwrH2geaz/e/W3QMBtndr/N5nKoY0W8EIliPsxQTPFhQCAVQCXHPF2FeUYrSb6gE4o3peXbH4SxO8F4oY+0eCUJlvc10BB1xFBwKZuwwoyAmbLNLYaot09d74SOzdPbgokdQWq6g6trGpTSZtnQKvrxIyp2RKaiJooG7ct7FfCod3C74kjju15+I/B+b9IuNJhn6Z/ht71otWA6rRgv0d3+PGoLXxhUKyeANjcl22aePqxTT2QPHSOSfqZf/lbzSzWDFgPxDrEj+mp7Lyxu7nm4zLuDaH8L6qr3HJKagIhJyWAMchkoc8ZrQvz4l1qAZOsgC1gkh0AInn8taaluA1EMku+5ZnOXIr/oOZakSMjv7oSoTqzZDhmMuJ+PCXMlp46RhrOf+srEa1x3yPYgAroVeH1Vy5VZibO8Am5/+J3PYBhpnKnJxb5OQBawKwzskKB0OjYgFsvviPvECnoHJ9kxAUxeHHXZr4xp7LL4qBQwQTOWzjTnjGSblUXeX4MwjYPIQqB2uIdDLxhVBa/KdsgZAC8L3/z4MjYHqcUgwYD7aRNtkvcGkXNXNJm9YWAoTVzQ8qqAldiC4Y3pGE7p68wxW1w/YOORNHv6/sAUGU0x0Em2J6AIM2v9ObM3q4tq7BeqUTHNtarSbvDEvca7sGK9bWtPwzU6ZtBkVlu/wu/2/iCNd+r5YvuFKmTv/PXFarjXgWg/bWwr70J1u4sSmXK5Rs/BgqCeMoY8YEsS0gKuOd2nPkc9DuPVoPih+8Az0kOwCkmyCzzNQz4iIzPb3lEPXQrEQ4eoQeawCAI/xh/ka7zKvAX94JpmmA6VXg8nDONruWSizft4phvXRFjbMGjh4cPThO7DhiYr0mJfY2QTnsHCkLzB9H1ouhaLosE0DaWQUfeOC4cIbGcQOnxc/NcQB/dFEbmdGEDsmHJpdvkhNeZBlzILvbfPTPD0YNBOs3IhaKO00wvaB3o6QJP4r7Bh1ju60GNbmiZ7NkvMCYK/76Mn7ze5f+xpdDTCtbQKs2PnQqBmvJ5OLmZzTul+Zgu2dX+mJYg3F2X6vlvmieWHEwz2yMcKzseQfoFotyqjMDPzc6ZsgZPn8OiU7ghxmn30OoUtm2ldcod/0hlAw35i9AegGhvrXfc3SyWpuWX1hfxcyW8i3tntu2/3pbUjeUq73dmjHdJDWnKS8UJj6YYtGROPsitQrwKbuy02pPMZWoBX0APu9CUWQWd0uXlMKADhjwI60dkpTWwxx3xTryjKRFdehakzekabupbWcUadK7gNINeMK+ympGz01QiYO9bm0bNYFz3a+5b4b3wdP9jJuBHUzCTKZioHA4m/Wzz6i8UdBzImbPAF4g0wuW3K6/aK8Bmsg/kZqzSf+qJJSt+WC4No2cNa3LZlq09usjZWLONPbrRjhjdPb6SujJOReLQ0wylIuDv9FOzhWpG0Y0tXxzNhB+WptfIfftZIP/p450NjRWgeBjfzl4gYAFyKn8crsaykv10s+/OPl4obun4KKQtSTz1NIdr5IYlAro1/lojYntSF0wXbDoQHFjls4jnMzCe9y/gBFa1/zfMOun8yOm29ZI3MvehXnRa2cQCuLIrbsLnefMpWVB4drHbT6X5BZCxwzAnainCuPC2zTHDaTm83TYvQFbbfOCiDVAGGuijVdp2ocBGh2QEOx4vj8lBr9QargAe6/ALisPy+JrgTpdk1k5qi14gS2v5ErRlieqEpQ3MzNON0k4GsTYxa99RWquYmnkdP2FzaUsUp37vWEXkRUYlOxvJEHw6E4hBq/5w0P74UujeHGGZ2ziiGY0Nn68TxmDqSTDNSC1GhhgxA+gKfLF/Izq8XSSDMAppPkcunEnHgPt4sfSU7oOADwtgJBQPzyKAIHWZ0hf4XYZFghUBANv+AsiDAiiAoxQwRPVCpFBPvYXbkVrJGgYTiLEhZ5Bldax4hO2g7nw9ZP8dctR7sFOOdmAXO2CH+mqTdkkuLxmcI2TCwsXsSvu1y45dpbRcdZIpiAl3qq3q095YhQkC+B5XgMZvZibqkXEAVckImH8fpNiiQbtpzV0wpoX66jLcTKzORU5iG2KuuPWp/GrDYoydOlJp/BnQXKK/LsuwfwMuuqIJZ5Xp7VWfvQpNxMXeCsxxS8nAgnZedK4gxT8MziJhDY49M8WrB2SsmkRFJ+UU4VHUwMUgQstSCbykNdeR
*/