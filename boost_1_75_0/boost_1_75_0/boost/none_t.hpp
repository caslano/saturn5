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
8xZaA0WlY9IQow4UiXQd4ScOAdJvQd/9JcguOecHEJCMDNwcqrBnU3PlCz3qayjsyXCY+hnzYQU2ReOh1aJ7hI5FdyTcg/UuuEmqx5Ydv0ltFq0x1qizQTtjUXe97RzIg6MgN9+otJ6mEzCPbtXl46M8Y9bSqhVA5dbnAC8FRuTsYh3JY0oC9M80lYuvLzKSuI48GRl3vvSVpwu7UzK7aKUnQusnxVM7SeEVhKPNgFA17lqrmC6Sjnguhkg92iiswZzc55PGG/kWne2xXDmmR3vRiKV1QBLg5S2E+SZHQrFUvPCrLLgDJTXI93yC+yKWkszxQAs//ps+gYM9JvwF8nmr4Ue+Be/IucGnjWPTZeMa8hodV+zsjhQzb4uCX5PtemWhSb4Zuqqq2Nx5ke0vh4opJjHF6Ld1NOXxX1ExcAMQPs17V6587SU0yfbJsGQruXLSPlxeHlM0ebB6LW5fLYkEpfLP6Cs2q+/6gD6XFg+NGAmNgFKhqXFu9ozUK24cAZ5VkcgJL4AvV7Z1q/2VK8/HwerVO7fhgtMgj/g3UvWV9Lh/DwgBURFfusivw3fkOz24CWO7fqWO9+hAacplEfYzvJu4oqPhf0m3WenpWWJo4tuUuFreY/wb0emqbLKU1A3ww53HbKNhPivEHu5K6sEiYzx1rqRu1fc3FAPtn7qSFH/SJdUHszlqAjT+ZpBt+PubmLHurTWUlfET
*/