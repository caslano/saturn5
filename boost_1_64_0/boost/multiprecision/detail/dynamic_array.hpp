///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP
#define BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP

#include <vector>
#include <boost/multiprecision/detail/rebind.hpp>

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, const boost::uint32_t elem_number, class my_allocator>
struct dynamic_array : public std::vector<value_type, typename rebind<value_type, my_allocator>::type>
{
   dynamic_array() : std::vector<value_type, typename rebind<value_type, my_allocator>::type>(static_cast<typename std::vector<value_type, typename rebind<value_type, my_allocator>::type>::size_type>(elem_number), static_cast<value_type>(0))
   {
   }

   value_type*       data() { return &(*(this->begin())); }
   const value_type* data() const { return &(*(this->begin())); }
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_DYNAMIC_ARRAY_HPP

/* dynamic_array.hpp
TWehk4UNFhLX4ZvNFw17G8HWzJkqSs87ZlIw8SsZGtZXxGd3cQXvFhobTWxK3nCDOrHD/rDgDVpkTVe3q3hneIY2N4JvmepUa4yvJv3e2N3t80+Tc9aj/k5tZrZpYZXXYhX/VAf81NdC4xm+kNRTs0pyLmyjynZcm+Fn4mjTJVibfCzSvZdc1YYeT/bQ4xx/OTbBdbKWDJMOAMnR0wfdymmfV1kpqiayk83d4lv9XTndldZWGnZzzQ53dvGe72jo+7uBluQWULU1gdslNX66pQ83PL+h7wHBaiak0sYIXWB7U05hHyHYiiUDPLfSL7HLD3KxC05dRX7wb/+d7mnOK8m1WMLqZKOa2s1/Snjxhf8ZzP+W7fAr64sH7thEot9/JriWOeV8nbwsN8HNzN7ah/wWdlUN6Gf6D3oGEUKL2Ma8i0Nbb2FsZorpRC2Fsj0mLmy3iME3gjnmBdFLp6q0hG4uTJf0bChz2quNUhLmTAV3Dpsn42XbmVGXYk5/WbVaeB1iyvow9cV9RU4bWeBRSWkiVp6Sv88Kv+jdfxSysTx980p2pMXVS5dSDMtd8As8Lt+mvDPHrVVB1HXt4e6nW++vRHp61HPCR7EAq7/pROhvW67NdlOiICIU1NUPFW10rbHcg0LchP7sb+2+TSxNxKUt7+MEp5kIneuMtGyenA5nwx1ezhR5fptgBYtOtsLbXneObm3s77x9/Mwd7/9+TuTrY3qF3M8OfLk4tO/PxZhIqYMHHum1B7TLbdyY7e7mryNgTIa16EH/JHfijayDlB17aRmb9GE53fNdVE7YVrGT+Ri5dndoz+P+SccLhsq2jbQLZ3O4oTnYAgldS47yeO9xAefAP6k/dOti8rbby+4nt/DMkdMGFmWnVTCOHd3cBJXzALlx0E9lvA/+9oPIXbyVje5gyHZWvV2I/6S+L9xroWDe39x4y0GS+EwegSMInZdbOcYxme5XOx0WEw38+m/Mjop9I6e/IoPVMracHW6DQ2EZG/0dOe2aELH2RvmFDPolltoN7yJjGYIMrvGcba96D/yenPYFTUx2Lpjye+n6vsyF9QEiX8m8Ss8zVMAFYvoO4QLaGanMKmklr7hA6PWd491ZcS/7JcKPs9oE12qPmD6p/mQd+z6VHzCSTasrxKVHdmVc3Z8TXhXMdd1K3SDG9Zc95fnrzL8Kf6foeOu6dPbYm12HO1SQ6P4MNYDI9VE5dk2lhAtdm0yhEEjneAPXoxN8W5rTdwxGvlVOR3YAzilHRO3PHA39uvwv2i9nHK+EjQwU59gfbC1ehaHj87hPmxwXmRJONbxpCKzqW4hvy3PMC2zV+So0FQPvxc2Do8L/cJu0SzNvrW8kUE/PLZdesITiuL0rx15NN+nRRcn2XpEzOjPGFH8PodeVC52rOdtfP4X+A0QuQWgjm0azeeAEcB3zAwA9ecOleB2DYpspZhHlcQnz0RVy8Up7W7WBwXw+2NxJm1m/EVK5fIPKJTQh6K6uMhhewKBu/5jwEqyLTZv8LRc6GmFV2NglizK+TctxgQlhnKzqmg0uaOOcHc+j586cLd6QRl45V7O9gxs7u6tnBOYTI1jNGiukVNqzw7QWrYQilhGsYr6WXNfCl3v8ODoj9hUFX8s7VzVeswPcp1N3c2s/jtHxGZrrou6qrqob9saN/dkxnZMn6GtX8As6mFYKu9jt4uI9DFzy967tBb8PUn4xcO6CEezGyc5u8orM+neAcatyjGPOgyQr49jWOn/J8qhA5fC5M0UcLiND5LLtY+S7GTy7JMBsLL9fyN/4oETldbKdHEOcNb+zv7N3sreS7+8LrHY6qjoqxG7cLrGo4w+6W5GrpAradlo=
*/