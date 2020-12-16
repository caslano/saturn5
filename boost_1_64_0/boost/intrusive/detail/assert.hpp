/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ASSERT_HPP
#define BOOST_INTRUSIVE_DETAIL_ASSERT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#if !defined(BOOST_INTRUSIVE_INVARIANT_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_INVARIANT_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_INVARIANT_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_INVARIANT_ASSERT_INCLUDE
#endif

#if !defined(BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT_INCLUDE
#endif

#if !defined(BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT_INCLUDE
#endif

#endif //BOOST_INTRUSIVE_DETAIL_ASSERT_HPP

/* assert.hpp
ZEJS00/GNYQpuakmfYnT4fvZY54R6toMY78vcsb78Hh1Lce+D5eo89SYe3jCscoKtz5eJM+Oyb79vxJ/5Eno/dZ6xUR5JhOOen0bI/emq5XcV0x5RpzmObV8ybe3qOuPMXs73vNxZbfMp8n7bZFyqVV8j6j0g6owNnEtfN99m7p2e9w5tjPJy0yZY/tBTvT82l5/4nk2f8J5thHZ6T9VcwCM9x1tyDjvpvedh/7B3pkARlWcAfhtdoGEBEhCEiBACIiAyE1UQI5whztyKCBKAoRDAgQIgogaFCtVrKjgQVGjRUUEiRUFxCNciogWrQcqtbTaVititHhU0fZ7s/++zO7OJhtAa9td/fny5v0zb2be/+Yd889Mw4D+DbHdHNKU86C3m7bVVnpNETfIRg02id7J93OEtDF9HdpGAXPSi40VmcumrCuctWmKAvLdLoz+KFO764zdbWzOZ3EF+eQTc1jr6BQH5LX9SebVV6cnGpvtpVTLq7TBjsGE0w6XhmkzpT+yzaxLM5+LI8byyckI4zwcOc02k93EmE9emg351I0mjLxa754emznXquP9RtXUq7gZcSGPIdeQ13RvXrUP+hMnsUvvZ1bPRc18fR9K/xFrDP/OQAqRXyMPIIZykH7g+hnO923ne9R0pTMMM4ribbm50eb0dJp5VL5830HlezzlUToNg9/xDfmglhbMuzzPzoiTj/FKJ5/0OjFHcyNVB7en27rT5hVo38CGKb1azr16n9quZsm3LfV+04EDd0Q6VcHfXfWJS32n6OtB+NWZ9JUTAV2/b8Gd5FwfaeqMN3c4wrZVr9/7/JneGQSnLCjwnuenk513YNM5lHgu7btsRbaYPlgvE2nL+5h/Hpc1C87jM+jG++dx9oJZ4eUxPiCPZfEnn0ffNZN/RnAed6Gb7p9H74JgVnj5JK72zc9ZV8Rs8wFl+uIky6StLWJcM8Ts/x/Kj73q4wKqusaFebxAaP/5h4vs8Bm9vtqVOPvPV9/d/s+dH1ne496f37gAs59/1cdrnK5xAeZxFqHGZfz44wjM40dCjy/4Ssb08FN9DqUw1qWeR9TfVBXfxbxjYnL5+3Pt763xXp2pyKQkJ5xvqN7wVOQLJNvnKwXbIKXy3ttPjvswDYHNR2BNuAHGwU2wFnwUNoAb4dkS7qzZIOnWM8ypP1jGIQyBKXAo9OWnTOJlG/IzQuJlw1bwAniWbGfJ9iDZHmFvS7rFjm8MdSPpJiCrtLU4XPA30A5fBxvBB2E6fAi2gE/JcR+BXeAG2Bc+CgfCjXC46GXDzXAsfByOh1tgiex/XLb5m20pv893Bd5gKP929FLhc/BM+Lwc90V4IdwNc+ALcJEdLukWOH4fXC+SbiwyBVG7pLyvwTPg65L+m7AN/FDGp7wj5X1XyvkHuAK+DzfDP8EnbX057nSX+AqIv0UpbI1MkLl3LhG7yoEJcBKsDyfDVLgONoFTYVs4DXaD02EvOAP2hpfBfjAfjoOF8BK4AM6VdBbAhfA6uAguh4vhjfBKeAu8Bt4Hi+Bv4LXwQXgd3ACvh1vhL+Cz8Ab4vGzvlu39cDk8DFfAz+HN0E2ZfwVrQDudZHg7bAtXw47wLrtc8G6YCe+FY2CxXR54P6RuVHmmwV/CfHijXHdjfX3aMFPOczQyVM7zLvSi4F65fl+A6fBF2BLuk3omXJ3v/VLPL0v6JU7/K9eOpF8XWSfp15f2ohG0w9NgPdgENodnwE6wJewJKbt3vBMcATvBbNgejoQd4EUSPha2hlMk3nyJt0D2Xy7ht0r47Xa45Psu5Ijk+7jkOx5ZgfjmI3bDm+T6XwGbwV/JeKtbZLzVbfBKWYvnergK3gR/Ldc=
*/