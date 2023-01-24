#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_CONCAT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class A, class B>
        struct concat;

        template <char... As, char... Bs>
        struct concat<string<As...>, string<Bs...>> : string<As..., Bs...> {};
      }
    }
  }
}

#endif


/* concat.hpp
vhj2CVFvW1afL0jaIkp18hZp5UzXwIGFazz/+96ArSGrE/9UbaWkAnAubODd8dNhXcdcyAhS9P5DEo4EHnUT+bu0szCwvVWO74rsO7rtik+38LHWkGKoAxKKE/fUN/HcVvLcXl5g6pvE3DYhmy3jn8p6BKfqryGkg8k9ICZXbFwshXFX8OSKamByaxbw5Dxich5tCExOqdOsjI0+ZQtOqwSmVX7UmJbwLy26XUxrhZhWqpjWypRuWo6EPY4TOniUJsRhyvYv7jImZKGyyJ0wJ39+QzBa9zwFJdftQAa0vq6VeMu6vTSlutX860eqqUfLHL+HbiVrcJJRtYVpHN9Rz9+MLqjRf6+wcg4MOUhel/W+/wY1gG0FNIO/QgJWD2MjWhuVWG9k0H12iPAiz0bkaTsBTlYexqFqOV0MvZABPSmMgV88FlklGGpHQwKiCAnifzbxtsiz07ZAiBk2TANHnIQjKxhHSgX+32mAtLi7Xj7j5fdsFu0KoZhD3S8nY8wyYhyk2k24B0+5VqSmDgI1Uu2FF5Hj4AvXW8lxEAN7BnJGAHyXUTCHPQd7amQw2ASt8JS+QLuwg2oFcyiTd7XsZI7TYyRAr/IdJ/AiXUzCUKwVC5S7v4VRrjSOcpmEckAtdn4MJwLV/7lYxNGAdPvoLiYly3eZ/oRozrlqfg9zDsVdqBmLtgK8TmNhbQg7ShrWmEEtbI3Bzjy74rJY
*/