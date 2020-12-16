// Copyright (C) 2003, Fernando Luis Cacciola Carballal.
// Copyright (C) 2014, 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#ifndef BOOST_NONE_T_17SEP2003_HPP
#define BOOST_NONE_T_17SEP2003_HPP

namespace boost {

#ifdef BOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE

namespace detail { struct none_helper{}; }
typedef int detail::none_helper::*none_t ;

#elif defined BOOST_OPTIONAL_USE_SINGLETON_DEFINITION_OF_NONE

class none_t {};

#else

struct none_t
{
  struct init_tag{};
  explicit none_t(init_tag){} // to disable default constructor
};

#endif // old implementation workarounds

} // namespace boost

#endif // header guard

/* none_t.hpp
PCdC3jpUtQ2sST3tkacaPO1TCRj3WvXkxhOzvMvx0kel9UvmRgbg7YKQtxGPlygO7Ax5l4PJIeEKrC5gwTBMLmkQJrirGELfygaemw5TFK1Ncko9jBJ8bS5EpkvzrknlZ3bOH4z8zI75ns75Bcj3IBNFVH5W5/yByM/q+H125/w85Gd3zO/bOT8X+X075ud0zs9Bfk7H/NzO+X2Rn9sxP69zfjby8zrmD+ycn4X8gR3zCzrne5Bf0DF/cOf8TOQP7oifws75LuQXdvy+uEOmE5nFKtO/t95eniVFtl+WKuzQvE3ISUvmXJ7KSVM5znIP5YE1zci8gplehCrtFY7Boh0ZRpvB7t68VupBS5i/AVrBrLyQ/sqnMcX+o34dTMFUkdvFszO7WFuOraIg1yHcA+6H8YTwJ1qbbbzQpraKpoTiEZfw7BeNGqRpXtj2xSClefdpcdoS5YCn8TNkhhCsOOQNgq4D+HBQ0IMEGxI8qUT+U9ruFhBClF0yt+SW68eXILQy+u2UwJq4pj613st5og6niNSRpoKMVI/LdmHBj4+tDWKX9Zqush5cHIwP7aevwMo7/zHEEtZWUBFTFxdywT5DFukhJc2MLLWUFrJ+zT/BI3Zb4ADm/sYYiqorER3lDd77FC++wsiE/Btdhqppx4qpKH+RosG51Idph4Bl1L2gt10Zwt6xgxzLDNpN0Lq/uphkSfOE3igGB6N6eWd4rhR4SvzNCZuyBQZx2ZKe7e+/0bsXZ9gzNVghNceqkG/l1ApvDSdREcyw23DKDPv8OBGLTcSQ78U7uyBG8JrW/vX66n2bfLVzKnwNlV/7lb38q/kby7v6cee/07etYoz72Ub3s8qujHjNAPfKe5wXa+bSeNb5Rl8oLe4/NKxpc2xE+bmXE4zmWVQffVBSp3UjrDz5kShJHRiIFcDVK1HGnK8x52w+3cqnvnyazaeefLqET67ktdKI6quOmu34eU/bIoQWVJKTMamFUlNM3by6BHk0AFx5ivKwe1BUWJ5E+w89myP0ak3Jbzk6RO4MFF3pmnMC+5A6lhIpQxRraBgO44ObeW1hL54UQYhrceKU9JeRLltxx32YBVcq1nd+d3V613R75/cyv8vnz6w8F75kIgPB3EO7e/t+ZQ86m5o1ETqZouTs3fL9R9/X8700dfttKCtNi/UI4HpI/J/Z4PcgU10bvB4q89G+j10NeI/ub6pk2UvTLAmQfI6C5yYjjj3L5E269z+qwpjW0M+O5Jm8qbYHTD8K+yVkVZq6LUUu+m8gruk6PnkCh2FFbJbLuBjwSeGU/6z2T92vUp3NS4oP68+HMvFxdoti9scnvYwtf14edihCFWan8WNMAblOb/UB/uVZnxvwmPQhOQA4LYfVh+iIRseY+xuC2NuoormR9jheya6yUGsqtxa5zDrFKVI/95Pjox2ye4hQhT+zM24hmBXdmVmsFM9sj1svctRFP2S8sVXye0F+NhuYtMF4QZLKW9rPrNAU1rnlYagCOv/Jj/S0lextsJfnFE118dbKt6KvgY8N/G0ii+4Lel7yNV3FHCya5oFjY2yap2iqpzxt31Z2eZxDubG8ZiNUSAFUVyuoPGYD3gGSPwlS6ijb33YcDhLCQCpYTkYzLlw7C86Wwcs0dFt0exe/+w8DF7DVbELqoi/UvjWJUwVKFx8Bkny0KpGhEo+o5cxanKDchiAKuWmw8inUuAMHjYrebQoUfY8FDC5wZwF1VLMlNsVjzEiz4meAHROjf22UoQi+r79Fwnh5peWtV30IBWQ9Zp+ChjoiMfaTLcz/ph8dGvorplKCAxb0h65eq5T4rz2Mdf0czP2PuuVLIwM84r7r9w9aVS0=
*/