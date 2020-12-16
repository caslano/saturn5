// Copyright (C) 2014, Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com
//
#ifndef BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP
#define BOOST_BAD_OPTIONAL_ACCESS_22MAY2014_HPP

#include <stdexcept>
#if __cplusplus < 201103L
#include <string> // to make converting-ctor std::string(char const*) visible
#endif

namespace boost {

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wweak-vtables"
#endif

class bad_optional_access : public std::logic_error
{
public:
  bad_optional_access()
    : std::logic_error("Attempted to access the value of an uninitialized optional object.")
    {}
};

#if defined(__clang__)
# pragma clang diagnostic pop
#endif

} // namespace boost

#endif

/* bad_optional_access.hpp
9N6V15r0MxH/sYwPrewe9rd2lHElngvoji8FJ2XI8HfAPwB/Zvgkos4nRBb+5tDKojQ79GSpPnqXwcvxPoR+wH7ZBwjTAEEGvY6uTLKPl822hitoTIjaCnVMoPZoea2Xx2vrMK+t83j9ZNiGIK6UbT5C9F7HPGCuEih+e2K8nJMQv5PjoZES3m5+jmmFyAvxL1M8a3qI64q4QxznruWh7sA5wjguGh6lH+N0p6am8j0RK3cd89R1dGpD3AZb2d5RazO6Dls4Xmsy+Yjb58JLnyv8g+YfgZZWzy+u1N/RUc8L74h/XrVKPXfLij8fCi4S9PsooO4d+jCg1ueH7uE9BF6f8wZC0vV5D16ff0B0bwcex2y/xNNa7If8/xowJdBabAoE2L6J+SPXP3kbzHU6xzv3j/L0GfMatQ5tS7dHRex1+ECKH4M4pZPcTM+v+OXqYrZItz6wfu35BPN3H//Ftp7yAOEMDEgd7E3rp96v+SPib/40d7/Ve9ztFnqwzebQNWqvYBbOhi/2+MUDfr94HJCHvYlpAMeZicnT9Fcx1qnvEk+PXafD9PyBz7LWi+94bxSVvvPFw76u4pcY6D0S60S23t9Hva719vXfJrhuTb7/q4g2ZkdeQ89tYzbj8hkcYnsIShJYOGhIal4fyrrxXsFRyPFH9Hwo0NT+g6aduk7i+uz7wmbS80LRF2vQItFL8qSx+THxPBhIts7/Dtcnn2VkDz1/4ku3vi5e8zwt7vXuYZ8e3W441KZzwa9b71qXe4dB07kc8Bzg74BE/XUQ60kD75W0t/ryQNsfOsg7Yi60/QvFb62RsCHFSs+TC12kQQzzbhWfeCOUZ7b0rqA8B2ON86x10Oou0jzLxROeuzwl/iLxO3+m8AR6yrrS/ROqfCMDxrqWBoZeh3WN2WXMoQlPzXfkVcQ9bY+V16i8D4muXPctxPtTgXao937Uu7c/V2xDff8IkGuhAmHaPkp24MXjWJcrW+L5TDxVtuMom9MGku2o76dzLHttLPWGw9XQYVCvb5D+c5W3O5SHzHx1ni/nnG31rDc1roXaEfSTvsFpewFParpQJdLTkc76E/MuagBvov+t0sWlBgU8qR/tB327hpgu3vhn0sVJjfIG2D6B8UY0IC/FJ0En93gT89xl57knVIU851GefspzHNJWm3m+IfPMoDzBSK3nGG+nneceudaA3ue+ntPteLCB9ciMpSNBEJSia6ZPWYh9gCykd1maSd8RDKlvfRwCXc5CrZ8OIiVS0um0YqQ9RWmZIGoflPzaIW4C4GmKz+XL5NOJLrFc24F3jyxX66UHvNmyZOpMayriV9v5vk8LFqLjtG2AOyntgFQpQ+gbu87TxXSaV7UOlZGFv9n/IpRFtrL2c9hOo36hspi4mawrVRvnDR2a8cmYsi5OT0r5DCLstKFlvYLoCFH7UBQIxCWMwzykHSf/DDMtdpeNfS8T6w2X3RuvN6xby3oBP++7Tz2/mGCvUHOLqvB7bKP2a8A5eOFveiCmJ0ShP1XULy6R1nZIdrVXOEz4D9PX+Ba72iswT34vhsmedk69q8844TptZ7Vf9jcp7VUxGe/CRwCOdzDRJ9o4LJy72LyPntIXYpe6yOkD4UpfUVcSjTrvkjRw5XgOL0Kb36zsXsO+1mGrVSg91DPQKhzyhSaGumHshLP4/Is0td9EyKaCeiPRHiObdZAXiP9UcTnZpyEOT9evl3FdDB8NNl4wdKoDoJOl8gsveQXz/bz4kc2k3RY/ILxckQlMmgu5Hoe5Ht6GhBogLtU6UHmlrFJ5R7Wo/OetT638+evjy6/XZUh0nHEZD+ObOlOUdcyV8sk44YQ7hCPafkXJFcU=
*/