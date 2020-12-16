///////////////////////////////////////////////////////////////////////////////
// foreach.hpp header file
//
// Copyright 2010 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//
// Credits:
// Kazutoshi Satoda: for suggesting the need for a _fwd header for foreach's
//                      customization points.

#ifndef BOOST_FOREACH_FWD_HPP
#define BOOST_FOREACH_FWD_HPP

// This must be at global scope, hence the uglified name
enum boost_foreach_argument_dependent_lookup_hack
{
    boost_foreach_argument_dependent_lookup_hack_value
};

namespace boost
{

namespace foreach
{
    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::tag
    //
    typedef boost_foreach_argument_dependent_lookup_hack tag;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_lightweight_proxy
    //   Specialize this for user-defined collection types if they are inexpensive to copy.
    //   This tells BOOST_FOREACH it can avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_lightweight_proxy;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_noncopyable
    //   Specialize this for user-defined collection types if they cannot be copied.
    //   This also tells BOOST_FOREACH to avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_noncopyable;

} // namespace foreach

} // namespace boost

#endif

/* foreach_fwd.hpp
pxO5eCkv+dUX8R7ShX0D+tUwefH+P2IX//f5a+X/9H55y360S7/ZRbKgQwlkkG3cwTpc/TS83xxq41B136TX7fsVXmX/7/44P2TdFan8El9C/FsTUuOPS4h3PZ0anynjKa4gSB+EJdJLEmjzLyygau5G7Xdn78BPd+ynYGXiyie75dcyHaQwPhp8Py8fRIV7URbErm15enFX7ORyQxUqXqyHVOaqfFCZYZCi4MM0RL4B/6VRajeODSInWlkG86Vq6kKl4Ij9kS74mbitccWN0K/jagXJMC/ue36J79usb2Hb534ETUMQSlH6BCvAXsGh2BF7k2RNxUWIVMC3j+VShfsnAzwzjwbDBWGS4XKxYLhcNdOSyn5ygzxmuxNzdMbepMi7si1rALJ4cBPNqqGqaDVf9P4eZWzNLDHW2PQ3yVeBKgdrMDAidfvqbbLGlPVX+x2yCFXhp2VyIZdimjYk5MYN8NBa4vZA7YeZQedNLqy45cJbK/XSTPv2gcinvDMakK3NnId5LM19HEaGA5emGS0xxWTIQQtjdSUXe2aggciHVOyQPTQ53InNhfzZTbphQx5uv/N6Z302C43be+UcEIvDc885bFULHLaP8Tt+IR68bxBh/9rzVvq/uP+Zup/LycFO20BUnICxzfexI4UfyaDuL6D6VxfhiSYArEVoe1yazTftiTN085wzMsPHyFnxgugo7ObrjGseZ9c5bZZrZv2cDNhODnVsbiPO9v7qUTTRgEQ/s1HR6fvQKEb3iXyTGZqECRTKVxkdm5wRwo3Sa5MDyQ7V+8PHrPyud5LvL9+lzSG6hYMKKVJjdH/xNkn9V9kLLzwts9o/H9L781c6In67fPB8aR2Rej6CZS0kstvnfphAQlXuEERM0O39HIppWaHJYv2g/yQgcEA/iyg+5zJBjvTGvFCU6wdPSGpkiBYbmY9TqjhvUfxy1HcxRbUOukxQrWsI/vqVAOeMEIgdqM8yO4B738V1sfOYB6hp5rARO78ZdRD2RLX+3xNf3wdcuZv1PyH+rkt3s/4nxBuPp8ZvvbvV/sAbfsn4LyHAX0HfksAXinNIYJwEYLLVB+Mbhj8lXux1Pk2W+blfdmA+CR78bUJwKkR8Z44Y0BKT+kz++8BbvaXHEoct6KzXYqhAf+HYvWynLQt4GC4XhFij+2Uy8m9am+AtnfOTkN3NSXgM0NqK52Rs9d20FNkp3E7IpeZ56EYvkc9xeD7Cd674PrB1K5097rF3sU+kzxTuoxp5Ft+ITTOo35hPC1G4+LIDu6YTjZ1yHnbMk31SUpH7ktosCV1sdlIPbl3ccpq70FCa2kSzjVsycXjIgdlubnEnOaV61XK7ckOUxlo3ksgsmxt40bYT9wVSO2/D70rsLeZSjhywZYUWYtvwBMeVFXA1cRudth9qaz7GP25QAe1mv84F5VI2edlF0uwsk3qRFLmpbbHlYSgE0pnzRKxNZjncf+yqJFoLFm4hWJOuqTWpQ7zYPE8ATOvaVH+WUJsv1rE2Nwv2RkJtFtlEbZAAlXlsurSu+HN2j1xCAiSp9KtdxZM9s06dMMHcb/3yGkfPMGKlra0jhfpa6GK/1Oia7JmxUbRr3g+7bVflVISrMgzIB5ZMU7LjB6T8tWwd5a/3QHbcbJw5QwiLB8VTLEpMcbdM0d5KgS1epjgCKSbM2wUcfv0FIA6eLng24/usFxh2YLj97/An17OOd4iZRGw/xVwHPFgHCrgOdOYaJ/fikCdyc4Y93JaboV3yk3kvWdG9ezz/q/3pmdsVTdAgXW7QI4uy8qMsRJll9/GBNOhsVuBELdaoZpoFiTgP49rFw7hC8UJd0Q7UVMrYu+r9MyK7vpc=
*/