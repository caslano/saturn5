/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 Revision history:
   28 Sep 2015 mtc First version
   
*/

/// \file sort_subrange.hpp
/// \brief Sort a subrange
/// \author Marshall Clow
///
/// Suggested by Sean Parent in his CppCon 2015 keynote

#ifndef BOOST_ALGORITHM_SORT_SUBRANGE_HPP
#define BOOST_ALGORITHM_SORT_SUBRANGE_HPP

#include <functional>       // For std::less
#include <iterator>         // For std::iterator_traits
#include <algorithm>        // For nth_element and partial_sort

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn sort_subrange ( T const& val, 
///               Iterator first,     Iterator last, 
///               Iterator sub_first, Iterator sub_last, 
///               Pred p )
/// \brief Sort the subrange [sub_first, sub_last) that is inside
///     the range [first, last) as if you had sorted the entire range.
/// 
/// \param first       The start of the larger range
/// \param last        The end of the larger range
/// \param sub_first   The start of the sub range
/// \param sub_last    The end of the sub range
/// \param p           A predicate to use to compare the values.
///                        p ( a, b ) returns a boolean.
///
  template<typename Iterator, typename Pred> 
  void sort_subrange (
  	Iterator first,     Iterator last, 
  	Iterator sub_first, Iterator sub_last,
  	Pred p)
  {
  	if (sub_first == sub_last) return; // the empty sub-range is already sorted.
  	
  	if (sub_first != first) { // sub-range is at the start, don't need to partition
  		(void) std::nth_element(first, sub_first, last, p);
  		++sub_first;
  		}
  	std::partial_sort(sub_first, sub_last, last, p);
  }



  template<typename Iterator> 
  void sort_subrange (Iterator first, Iterator last, Iterator sub_first, Iterator sub_last)
  {
  	typedef typename std::iterator_traits<Iterator>::value_type value_type;
  	return sort_subrange(first, last, sub_first, sub_last, std::less<value_type>());
  }

/// range versions?


/// \fn partition_subrange ( T const& val, 
///               Iterator first,     Iterator last, 
///               Iterator sub_first, Iterator sub_last, 
///               Pred p )
/// \brief Gather the elements of the subrange [sub_first, sub_last) that is 
///     inside the range [first, last) as if you had sorted the entire range.
/// 
/// \param first       The start of the larger range
/// \param last        The end of the larger range
/// \param sub_first   The start of the sub range
/// \param sub_last    The end of the sub range
/// \param p           A predicate to use to compare the values.
///                        p ( a, b ) returns a boolean.
///
  template<typename Iterator, typename Pred> 
  void partition_subrange (
  	Iterator first,     Iterator last, 
  	Iterator sub_first, Iterator sub_last,
  	Pred p)
  {
  	if (sub_first != first) {
  		(void) std::nth_element(first, sub_first, last, p);
  		++sub_first;
  		}
  	
  	if (sub_last != last)
  		(void) std::nth_element(sub_first, sub_last, last, p);
  }

  template<typename Iterator> 
  void partition_subrange (Iterator first, Iterator last, Iterator sub_first, Iterator sub_last)
  {
  	typedef typename std::iterator_traits<Iterator>::value_type value_type;
  	return partition_subrange(first, last, sub_first, sub_last, std::less<value_type>());
  }

}}

#endif // BOOST_ALGORITHM_SORT_SUBRANGE_HPP

/* sort_subrange.hpp
qV/yAexViclzwYJmR+Ca89U9/vYOuvzotDj1SsQ3/81V2TXKR8r1dXjOtw8sbeZ0tSttKp8hemHmhFTGoXlhhnVpjROfWb/wdF1sMXOd9KjOuf7gGE3U8q/hd6kg/5iTdbs7tTkYD9tK9JR7x4ihUFdrpTiU24x8FWV6rYlHNx1zyQKThp9AMnkrjpUEVs9IIU0Nj2iNjVgN2gq6KZjnl9E9COsTKYrLWmy+3x1YxyEhDHwprHE4rnkEpusb1iqIDGZ1GCO9k92wx+IAGgWeHHlmpn/y8zEGZybrqCgrF2bn+FRn30iIP3o11mIvQKRoQoYzJ/P995wtOv3xVqbIwhvKKK3ubmmN5vUOMq6VpZLQuJx8HpXsTr0f5eoNVN2AzALtoy20EE6tMi9HhcJax0AaooTHGEJXWct7Y1TAS2LqlcYlnHVWljLISQeRikpcWMeCmIpbv8KKBM4MY5oRZDToEv1pWdD4xCe7PNGk6JfrYTKqdrJ/0cWZMu2QSX7oqvpIWJ0D6X0JUF0YeF8RWCQsLXK7wZUjDMIcahqWmZHag5S+zI+87+hCP3udOWJhHd89ho3v8oyBLiiH+eu8SaUa0uL+7BbqfZs/LKahPHoOtDoWwF9ZDHLXZ5CzCCE2io8fWpuapE1i1YlgPPrRGbN8G99Qo3i8H51G2a91rxWQYZoQsDHkpxzeuV5rXvSxTEllMyNDdDD0TBSJAGW4fRI5r7Q/NrOckneJmBN0Seg/Zjmc8k/uFXDrCtyMe5oZTVQ/763PgLM06odRFJDhWn29LECVmTM0vFMY3MbAEMQzIc4k5AqCcHTurU5AlJSzJc5C5FLH0kfEk0b/pHukvyzfJqRPAsjzhoDs2Ae5KTWp88kKspoGhByA9Wa61NZsmwcl94xZlJi1cWMupRpqbZXqE7q9uOV9wHXQSZM5UJNzeqPc88kDEZHQY1dhULGe8gfpjeO/5nL2dbNKF4+yrFa3Fo7KaUyepeoPf00gDaAU49NI4tgjn+83fa0yU5EYeVn41R5nGvVsJ1YgUCJOoVimdPYrMKUHo3rVqvcNBcBXOCzdT0BwywTLgg643IEeHIfoM5S9dpDBvNPemd9RVfP239B/NFdXuWzs7Gw/rumDvJSGp/qfQ/3jw++9+nsDI4+6jKFdv/7sRoc/rGdx0lpSEdoKAZGPjKispKCpaLS0uJlooLemPbO57e9Da2tB4yDubOtsbu3DvN4ncQd7+4eJSIkHJweGhx9E/TT949Mj1M+7wTDua7+meYPQaGus8nR1dkq+Pcl0dWBgdHW2vH19BKMDfQVn/X0FP+G3fnR1W5J0dVzwv9x48dGJ2dGnvPDxY+MiM/2vuGFC5qSgq7W+/Ya+hvNqx7/EZY0WbOlrnL7fkNJMj1+p0V/WMvr7vkZovz0Lv94h8Ymfvkc3DgkM8JHTLzW8qV9UORFeFeFCfdUf1ly0xlK1wYJ3nt0lXc2a8RNFn0ThlWO4iRqMijBCP+17uFiIve884tmdjFlrTiEhjQ9ehI++RT/8MeYEkeMKUYbz1/tQwCO0BB7tF+dwbTz0mMfO43QZ4/P2jeWHZkJrcHOkBgVuscTA3qs4ak7av8clkrcksKZ+TxCq1cQtZSMHWPI/8TTikxRdArXmJXRvYgQzZdrGgAZKBo6ia8vhEP90zpF6aH6puFEu5jOkZOc6J5XgExcuLQfQofwcnWWcMkYd4RP5WxIQpssOM4pTsVcdKtQKZqVY6bfskL14YW/PDhQuL454y1OBFW3TeWSNmdMkEhljaKxJ866egbh8nLfsnIjfGC6+YJwi7EjgNit9cRykRB64U3+2cDBJ+ucb7jjEzXX4EHmR3g7BQhvEpx/E+Hxlnecz0AAyBfRHKuW0Vm0y7OJRg1lEKXxL9mmNEvgmhi7MpOtGLt72mi1Q6/49jXUc9hJJTjs+CY2MLcu6dKki64Et9Nl1CeuuR+0EqnKa41Cy3F6vqH9qIADbnrvpuwYzASJf3HUdRFxuNDH+1100o6B4TtfVFUBU116SdHwNlfH5PGsx8xqF86u4mOAbgXX0O8D1Q+7wQzlAZjn67Gp25BukeFFmVl5xTh/Brp65RmHxJZqV8OkLVHr03hut6NDg+JVtc2D0qdoRHhirrD0/tH5yCzbyi78UjhLygytHOtAL7/frx9RP2If/I8wZ3x3q/oiK9Xb7xrfGancHloYUttaG9QvGk339Drn17W2/pFkrvwnV2EwFnTJ22BV96+9j2kEvLrUD3TdHPmh0cPlaZSlq9Yxib+NCYR313O8TvOXWWze9pElHdt/swHvE/aL5o8XUDNLxHRKGO2NFmugeRXPRqxglr4H8ZVJ2eojkJfJGL/8yGwKnCfB9RF0d+6FG/lhLV6T3dWVZgO0bkPfcjajJbv1NWktKeKqemUSqqHS7VcLhIRgaWQg5C67cOODOW2gykz9LKj7j7B3jdQW0kCyb3bISvk/J5GkSrymDUm/f8aoTybiENh1xCNTWHQc/0f/x2+f9rSsk9hsZP9KruvhLDAD/DXI68O2pBfMTKwW3t/MDKfBxIov+s3t+SQuib7BflylXF15uoMjxUxh1k/vz8flyiliwkvSFaRSGG6Zo3G+ZTNJePkbGGXPTtLtv5N2fjxV/XvgfctRgQVGRWc4sufJzYp0lRXMOCFHcuho1quWO4QrtS2xaPJ1o7/C/bsK8Ii5knRz9/p8dF1OkngLT+0VkXD8O5uUlOgQKVOeHzci9ROegbGJnRY8LLq6HoU0i0DcORKrOaaUTvfUToWwT1BMKaX6N/ZDLb2/vbgdYYt3KwvLzEpHo8wAELPvTK/eYRxkkrBLb+QcWq6nk7unmI4kc5WD8ohWpExZdH0LjCdxNNZwpNxTn7wMP2HqqNzjGT/Z73iKibqap/UdFzGZqHsIE+rx+Wop3WIPOkdRcJ8YfW8B0LC2rX3chkTfUuPdYKRKsK8y3Xg3yiF6NclbbnS9ByuDw4X+i/TYB0uLEL7GAnZkdZn5f5cnnqADNMGEKG0TLEb8SIM4YK8T3RzmH/zTZt5I5D58Y++z7RJ8VLCZ7GGJdbFyaIVk1HxeqD0UaxzC5W3hsV1o1s9mJiOhsdyEFdIQ4InK7zWhzXM00IY4KaxJWVwt7dL5IuudhYz09NX+f+EW9vNmCwf+dfOc+/5LwrPMOX2nEflfG0ea8nu5Gs0gWEPhBvTzW0zKiUv2yAji//AqC5kRGH/IqXj6gxsF8wnpxTO0COGf0xnBRYX31Zu7LXgaAz474C9+XWtsXGagO0r+PDvqKP+bdzDVmnk2auJK6zSd3OcgAUIFAw8+keuKQHvFUyqatIkyTyxYCVBscWC+BWAN1T+AIcTLnjEdPcKfOFeK2RMRqm6HaqU8/BPvOeTLGgzYNAQo9f6o9prUulgA678/iP8843k+cPTQBcuKj7OM6PlomUmPeMYTHf1qvVT2SNlbzPCX7+VbSi01MiRnaq+8SK5H9QkXiC5zZebg1ytxCXt7lU66gvCWlNbtcSRVDievwMkoSDuDC43Eztv9o8dmB3yuvwyJ2nSqBQqGBq7WPG4gTJQ35AM9oyZkfhxTA2yMcrhNhgKyotyjc/lajSa9iR1+gGSMYK+hb/dDg5XO5y+SUQGsmkjvqyhf+JN7PvuYfZ2LigED5GvPoYqudtUEJJYRXgOco+/FO1RC/+/IiH3l5y+u/6ztTa1CKohI8zBaN3/9KPv6mnvjKmDv84D7SvskSTfse6Pq98R7r0qW/S0L++9e7pXxyPZrLQUcnYux4dCQ+NkJXp1OMAcAPsQRABxbKbuGr+ZB7Y1PzW75dbXZwYMBf81uK+b56WPKbnk17bXTwLpvj+rX5Y/rJ+hnm2/PJnTIdBQ4HASTVWem3wpLs0sKi7C3v56WY15WdE7Vj+soi0TvXcplO2EgvzEhgFdkKlWxW3lkDsYXS5N4sHBghv/E0AJEOoEKD1QMGfF44h6VjxBFdmUKNaNjS6piCaw9c6svQrQhmcEtW1NrnLgoJVEgeZv25643zvnvx+rPb6LL3rfvXvPsaX9ORrL6ee5cdtnC32sEqSv9lQyJjh1eZI6OysJn13gzONqnmtk1GtIee33fOTX/WjFbzA1pH0PPfja18rYmpZ35usn4eUM36CLU4xOtMhleamJa90LRGoC4dW5ksioPI2oGa5OslfKP0wCUpA4dctlnIJvtVU+KztWaMQa/Gk0Aw1XoAlqNk6OVpssmh9P5FNvKhsfTwhZJU3nLAxttXlLBTOpwn4vnmYlZtp9XgADxmn8k4U7b0OhRswpiG/2zPZ3b6LcmCFaO5ludR607YrUQy92BDLEB51R4YP6d/3b7cf9ObgV596132Dkw+X1dgfJm+bVdgsK60foc2/DMzL2154xt9P57ObSk/QW1Be3yfXN5qi15271z0fhsXej057x5+Xrux195+svHefgpnMVBnc1Xudbux33jqHb9hc9VdCIwPn7QfaDLd+D0R2DSKRlVHZa+/f39/AYH++w/oD/AfkD///oD+AfsD/gfiD+QfqD/Qf2D+wP6B+wP/B+EP4h+kP8h/UP6g/kH7g/4H4w/mH6w/2H9w/uD+wfuD/4fgD+Efoj/Ef0j+kP4h+0P+h+IP5R+qP9R/aP7Q/qH7Q/+H4Q/jH6Y/zH9Y/rD+YfvD/ofjD+cfrj/cf3j+8P7h+8P/R+CP4B+hP8J/RP6I/hH7I/5H4o/kH6k/0n9k/sj+kfsj/0fhj+IfpT/Kf1T+qP5R+6P+R+OP5h+tP9p/dP7o/tH7o//H4I/hH6M/xn9M/pj+Mftj/sfij+Ufqz/Wf2z+2P6x+2P/x+GP4x+nP85/XP64/nH74/7H44/nH68/3n98/vj9+X/s9QRUNjjLX8fG5eO2Oj2xBu+FCxfp19GoPQsXDR938GIuREojXXzl9Au/15Pbm6wKHG9fr05hfZ55OrVEJyjJX18sHilq3x7vRxBFS/gwlT7ZkbYbpSNPTxuQtFF9x6X0VaWplpQTDVILH9VNjhO28nsR/DGcD3aEcfEOaYkdNWowQZ6szV+c9Yr9MvPi/vN++MmO7pO4kGnAAE35dTktXUptA74p6zxChkVM8LUcW1FQd1oOpz3Ixoo1T1llNqd7Ox5EbW1dfCuwZqwEky6WtbGQIRCGVFPjKQbhozay/PmOPTgcWFs0rXLyQiHZTCvhQkKb4J+r2RcCjtTUX2F+AxqHk9HTtHYP31Tcn+C0J8Qu5r+YfdMwnxqVLQ1UxpfAUb9tjZfuR5bQUJRGGMcwL8TtdDqeRAcVfDuhogk1yhalak7gsi/PVMBjc0poqpePZdg5CG8A2Z4RsmJQWsQ/kXwKvHjfYj8XRlqBSOe/y0gyeIo9i3lyOH/ASuqff79MW9N3zURv7BkzHQuPSDdMlx5B6gj9V6Vbid4Ye/SyEaJZeV555sA7K1u3RCdvZIyrf1t0xcTv9IqTxYXMDM/l2+ySTzAGS3HNjTe5BPp+heYHQKHhIeETs/yT0Xt11EC5E91OBWqZW9FV6cIZIMeeX3lYVesCwI/cqznJz1LuedwFiSFg7dlXTTIFBF4L7CAwT+34BjWfAMzMTL83ByBUxzPGN5+z8O090iCscd8AaG9eLTs+FRaCHcI8AXtVHbFLRCcaPBqVSS+xY/yXmA/ZDl/aeZFPfdlBz3yVPusbK/CHsiBtiw54Bx7P0+skF6j+w/6misqCq49QetlseujXgY/3SsRg1PZdd1IPy2rJYjEB13l/aSUgpt4gmhxsGAwsUKlVorW5NJADEfNpx+rF4u2/tjuVq299UtrObWA8UZJwjwTFoA4bXh9eFvbu3ay7/JrvmmyTTFJgLeFhPI9cETOueP/0UpRLtiDEomAKYiyM/1APCZCr4M2fyiIR7PAqg3rA93EGHdDNVRe3h6b3H/AMsCqfQYDGxwKe3XNjiw5AOCvdHewZnB1UOvMpkIyTLkqif7K4NkmjabhdIOLRM/OgS4co/3S/o3vRTayHuzUyDtKLcMyeyQ01/aHaX98N7Kfr/x0cQ9SWIZKFK4Qi/4VA7obcY18O5B+dcCVtMfRv6lMj9PBLKpDOD5eHsvtpxGNNENMZPc+VvveiKzvno+E5eBvLGUEa+NeDII61hDu7QXYdJv4kVGCDl99jFL+JvOE0EwwBe9tPHBu0WBw/V3w8RzxULtfyK16RtEORZASo9nq3JOfBDib6sIejDVgJQeyHe4kTjDFBDIovg8MkgWOVL8nmCV9ohGVgN/C6BTzG35UIGpwISn+GMKZELvxA/LXFIyB/jLfReI5JcbUn8Ig6n18aSFv4X8eWaYcWW0eTXkfTrBP4iUPSiC6PkNdp0YgU+Y/aXpGsek7WWzQ/tKQzqbpAYAaGoqK8isENCLOA3E7YBxVPKFe/vhz6AMdX90ccz0FnEpaxu8hB61TSkO3k0VKa9PtUmhagb0EFFrEdp7pBysksV8SFWoW6pG9PMS5khrER8RVDCXgG0/Gav+j4SePW9Pfu9VJ+BeU7z2QwjwwFFTspV0aPk/m/8Qex8YeF8Yfi8X+0LPA8og7CZQ7CUQ7CQw7CgA7CYg7CxUrgIk7gl07gA07g2k7gAeO7LAg9wQb4p+LA88RvRJNdxSMOn2HEKPj5Eu9VAu9VFiFppjiXU+biNKbvOjXAIRiaOijx4nnmx0ZKSp+lAfYFWh+Y0U5Nx0IpsWhwWhsD/I+SnRuU44LZQO2SCQUWLyj+6jv8tl8NEfOb//1r3Z9pU5/WJnKKbBp9NUYGmGA5R4q9t639t9MgGjWghDYe64uFTqxPPq1PHs0oZ/GbCJXcBZ00ttEYbJy9brtrd04H6sxG1ATNG30qqpDljtqNJgLeeaFrXIUkVbX//mOzk2obD9zEwEu1KX2/Jrr9Rf68Jj28LvrOfj6Yebxz9OkCqhF7rg/7uDoag9kFdG4prdMFMMDwVJezu+ce9ubFwO4CS7qh8GkFJpUq6lgayK0paxsEukSsLZA0uiwMnJTbkqB7cnbbWJEWa87tM1OqMqbiJ0qgqv81sjdVzy3/STrGw05OZcrr1Y9HEcDpttvSAYkk5MjMpZj+Rr+ph70eznYZscOkYnWkM2JoV4ams1uesmRO71j1U7hx3PRItGyZ16b+H+i5X6SWfbk31qZ0zvBQdP2GfZthrA+J57iMLZjQM3/NxldV9qSrYnSVNQq39TtfdJVzCrH1u9D0ZyAWVVvyh8DVVUZAADfeXP4mznxs8mxff4JyE1XkHNAwSivY3kmRdqjsfsxnm9pfmYj1kThMQN1WubCgbRV2qdaWB2AOXxNWMHAhFuJZnMlZ/7tWhM4/d7tUqCs/FRLzc6mYej0h0ZYsSHZv3e364xYFUaavZ+6ZSG/WWiMgRW5kPbdzfNFNPE4U3nqE2brUbOP5kCg8bJhhvjAozF7qapgYeGQCjYprSioE6vN29NnHYlZoAonVGpMJ9ky28agbid/LVD1SY0Rx67WnWVc6Fs+xTQ/wbdH7n7Nek5vX5Ddzfber+f4gqMy/p9UrmizcbcY3+N/pPaPTF4TznN/j7xGy9ZyH4Z3tMNh634RBnHX3re2+xEfIDcuKX7/fErEgb36M2gVOKpblWM0kJP14
*/