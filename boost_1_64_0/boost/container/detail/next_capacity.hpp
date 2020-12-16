//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP
#define BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// container
#include <boost/container/throw_exception.hpp>
// container/detail
#include <boost/container/detail/min_max.hpp>

#include <boost/static_assert.hpp>

namespace boost {
namespace container {
namespace dtl {

template<unsigned Minimum, unsigned Numerator, unsigned Denominator>
struct grow_factor_ratio
{
   BOOST_STATIC_ASSERT(Numerator > Denominator);
   BOOST_STATIC_ASSERT(Numerator   < 100);
   BOOST_STATIC_ASSERT(Denominator < 100);
   BOOST_STATIC_ASSERT(Denominator == 1 || (0 != Numerator % Denominator));

   template<class SizeType>
   SizeType operator()(const SizeType cur_cap, const SizeType add_min_cap, const SizeType max_cap) const
   {
      const SizeType overflow_limit  = ((SizeType)-1) / Numerator;

      SizeType new_cap = 0;

      if(cur_cap <= overflow_limit){
         new_cap = cur_cap * Numerator / Denominator;
      }
      else if(Denominator == 1 || (SizeType(new_cap = cur_cap) / Denominator) > overflow_limit){
         new_cap = (SizeType)-1;
      }
      else{
         new_cap *= Numerator;
      }
      return max_value(SizeType(Minimum), max_value(cur_cap+add_min_cap, min_value(max_cap, new_cap)));
   }
};

}  //namespace dtl {

struct growth_factor_50
   : dtl::grow_factor_ratio<0, 3, 2>
{};

struct growth_factor_60
   : dtl::grow_factor_ratio<0, 8, 5>
{};

struct growth_factor_100
   : dtl::grow_factor_ratio<0, 2, 1>
{};

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_NEXT_CAPACITY_HPP

/* next_capacity.hpp
820aT5h4/iGI2a32fvqtB7vCosg8zLq+6ngVlkLmgIk60xTLIHMx49dU81lcXxFXqFixYqWKlZOZMBwTYY7ILGbh6cubYE08p5iHFqW9NpbzNrFvtNbSNpIZv37tT4Y5Cqa/pyY0BMHCyVzMds/2vAOLE/bmxgdGwdLITG5/hQ6FZZOhzn7098RX9z0CKxTmuCR9PqyczGTW9fC262A1LM7e6f895+gRWBOZAya3n4q1Kea3jmphxn8rd5HxWjp+MWgKLIjMxezmDWdiYZEiZ/Vdn3WBxYmcg1cu7QlLFfbcI7/dD8sWZl+nhRWSuZkNrdtaCqskczJr6jvwClit6MPINx4aBmsR1rWksA1mFnn376Hg/L0wfzIPs+Cwe66BRQibe2OXn2CJZLx/iwd/8gMsg4zXcum3JyJh+cJaLlyYBSsjw7zfLrfJilUpVqNYnWINZBazT0fs3wprE/boDz+8BbPWe1uPqsJUWCCZySy/9O/hsDBhaWN+mw2LJnMxK6v/+p+4JBEX8VqndFiGqKVocKsblifsjvlPfwArETmj3+oUCKsUcUcX/jYEVi/qvCHwzGZYm8g5qWevWpi5wTvuxM5BF8ECySw+R2+8/REsnIznHHHP1j2wGDIns1G3zxkASxA5xwwqqICli1pWzXxwIyxPWJdvg/vCSkUt/DnaKjIHs8dzP3gGViNquWfBM7tgTcJ+Orh+Acxvo29zKxasWORGMUczP74WFkfmhIn9WBIZ+hci+pfKTaxj6YplKpatWC43cc6VT+Zkdt6dZzbCislczGL2umfDqshMZqsC4mJh9SJneMqmf8GaySxmHz7e6WOYo9jbBkx5cgjMIyzq1IcRsBBhlZ9/lAuLIuN1fuX6YRksXtgzQ+avhKUKu+3C2zbDsoT5r573z3t788kw1gOMpPaxhhUKs+cIVqxYKZmLmX0eAKshczI7+vkjs2ANZBazL//99B5Ym7AZRzYsgVnv+LZAxcIViyXzNS7xIq7DotE9YGnCNhzOmwzLUaxIsQoyk9mpTx+vhtUKmzVx0GxYk9KHFmbe83eH0cbsDmNW+/0FML93vaz9+BrmFMZzWoq5FfMnczHr2C+hDBZGZjHr/kLyMFgMmclsWl59MixR5OxyXocusEyR897OM/Ng+SIu7rGPF8PKRHv2vYWwamH7b28rgTWInI8cGLUcZrznHXfeg58HwywyHtdQkPkNLIjM13iGiJz2eRUsUuR8PTi1CyzBZ9wEI421d6cxqf23F1iGt7FaxhlZzELpL7ccxfIUK1CsSLESxcoUq1CsSrEaxeoUa1CsSbEWxdoU8yvxbU7FLMXcivkrFqhYsGKhioUrFqlYtGKxisUrlqhYimJpimUolqVYjmJ5ihUoVqRYiWJlilUoVqVYjWJ1ijUo1qRYi2Jtivm979ucilmKuRXzVyxQsWDFQhULVyxSsWjFYhWLVyxRsRTF0hTLUCxLsRzF8hQrUKxIsRLFyhSrUKxKsRrF6hRrUKxJsRbF2hTz2+TLYg0nGY6J7qJjnTUnFoyDecgsZjVVaS/DQoSl5m38EhbF2iNrP76GxYi4oJc6XQlLEpa3q+YxWKZi+aI9+7wfVijiNk04sAhWLvq+dPm0cbAaYfaxIqxR2OvPXvcNrE20V1ETdQHM2uxtCRkL7oEFkrGc7D7/ZCOMDP0baMz1Ok+NYDnJ2q/5w+LInMzsayWwJMXSlfYyFctWLFexfMUKfdp4o5jZIOPW9nNDWKli5YpVkpnMLr8m8g5YnTB7mYA1k1nM+LuSHKW+2ptpmMzCjPHt6wrM5W3s/sFUw8PsbmNSe05YgGJBwuzxhIWQOZkt/PR4MixCiYs=
*/