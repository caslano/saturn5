// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_HANDLER_HPP_
#define BOOST_PROCESS_DETAIL_HANDLER_HPP_

#include <boost/process/detail/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {

//extended handler base.
typedef api::handler_base_ext handler;


template <class Handler>
struct on_setup_ : handler
{
    explicit on_setup_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_setup(Executor &e)
    {
        handler_(e);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_error_ : handler
{
    explicit on_error_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_error(Executor &e, const std::error_code &ec)
    {
        handler_(e, ec);
    }
private:
    Handler handler_;
};

template <class Handler>
struct on_success_ : handler
{
    explicit on_success_(Handler handler) : handler_(handler) {}

    template <class Executor>
    void on_success(Executor &e)
    {
        handler_(e);
    }
private:
    Handler handler_;
};

}



}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* handler.hpp
sXRIT6VUWsX7RdGp45mjj2YeiEub50rSjrjO6aULpMNLbls6kCrTguNnzpM/bt+rknvG/nh7kOeLX6Ge4LO+1D5Jqhx0cA+lppjKLNAqrk3at65QSeNDBZ6JTHkmgvbIM8tz7gHJC9KshLk/UB+RjaAur09/YVFzj7tFIneJW3OKq3zQbPvtyf109QwY6VGFoekyLn+89hGuN1Ua+suVV9wIlMmPuLdF7jUJ5IGZz2P9p36IzjvofCk60aJDeqj9Qzlxzra34AXR+SXEcocoy5L0gM5edE6KTmRQnUPe2PbUf0t0anuOMMh+gNJt+ZmdmZnhX0M4ycyPg6Jb3DOWsvEFT3ge+ptdv+qSplbZ4Lntow/Su7usfE/PJfCShi6u5h+UcGm15Jp+KrnO0cOQtSDt+2BGYqahsR3fv6dcn9cyHNfrTxG7lTUjDI/K9UD9Tuwsou45wBqKeuitp3xtsJ95aDMbhRilsxUzGdMnlnSiAL3N7xj4CDTMFqWzQ3E75iDm87jAvipvqDMzTnDtjrH2hdqmzBfIF0G/6a3uf4nsK8zXmG8whp1v4yB8AW5Va8nqX8b6ny8PFVz/M++Qtf7nh4PGGp4G5v6DRyxZHUP2liVLNWTPm7L6TQxZ+H5DVq+BIdMsWX1D9vM+U1bPkOVbMjMsJyyZGZajlswMy7umrK4ZlncsWWNDts2SNTJkGy1ZQ0O2wZKZ8Vhjycx4PGnJzHg8asnMeNxnycx43GHJzHiMM2V1zHgMs2RmPPpYMjMedSyZGeZV+wuu5YpC1jkgY/OdgE6NwPW4HHZ+HJMTvI6LN5TtrMxfopVskqz9kXev6Nneycilvpe9ydR7wL4mSHNf+Zod57U5V74Gp7A1L1F9/fJhr74w6M3NPbeNmZE+elFPb7nC1gpd+Vob5zUsha1V+c+ttXFeU3Pla5Gc1xBd+dqWK11r47xm58rXlF3pmh3ntV2FrzmS9QRu9b2gvl3mw0mYTcg1NY4ZBXvB22FvOB/2gY/DG+BmOBRuh8PhbpgO98NM+AEcAY/CUfA0zILn4Gjo93wM9MBsWBSOg8XgeOiDE2A8zIUl4U2wFJwMy8EpsAK8GVaF02B1eAtMhbfCujCP/xvBGbApvB02hzNhG/hn2A7Oht3gHbAHvBP2hXNhP3gXHAzvhkPhPXA4vBeOhAtgFlwIs+F9MAc+ACfDRXAqXAJvh73hPfARuBA+Ch+C/eE6uAu+AovqpDOMgrthMfgujIYfwhj4DYyFv8I46G/o+GACLA5LwkG4VwUOgbXgUtgELoNd4XLYCz4Fb4RPw1vgCng7XAPnwrVwKXwZvgBfga/AjXAr3AT3wOfhcfgCPAGfhSGUsddgJNwGY6A/fMXh61yXhG/AinAnTIVvwZZwF+wC34Y94TswA+6FY+B+mAcPwJnwXTgP/hUugYfhU/BD+Cr8CL4Gj8BD8GN4BB6Dx+Fn8Bz8HIaE0JaCxeBXsCL8FjaCJ2ETeAp2gfmwG/wRpsGzcBj8GU6CF+DN8CK8E2rE/z6ow2XQA9+AofAQLALfh+HwexgJz8Pi8BxkLP13xtCRTWJsF/qQf8TvMxjvZMaSMPUxHTFDMDmYmRjG2694rP3qOPul4+zBY+yMr/9DY+tjMIWMqV/2eHoh4+j/lePnVzJ2/s8YN/9fHDNXY+X/dePkQWPklz0+boyNPzT56rj01b+rf1f/rv5d/bv6d/Xv3/v3rx7/l8F/TfuHx/89ycHj/yILHv9HFjT+r2QuNZ6uhshNudsY65cbljwkeL6AknuUO3ZZqOGGTVZEZD2va42q4Wa4OX4vuqY8wpQXdDda5N17oG3KYkTWt92Avpb9WJF169E=
*/