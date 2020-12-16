/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
IQf18ySMPi0S84yYSXb7RIyYA04xo0oNGOEq0kDvEYQ5TAiNNkMIlwhg/VXvxALq+1pQZITjztxINLWFatTWqgE73YhgbFFlcFMVAlwcmUw0KUwyLqmYVMBV6IMhDqPCUvFoHuuaGKkpXB/bclUeFWWf0QbKbmO9A+s8FZaVNJG0RvRaHx01xEI7tqd5yjc90jx0lRQDdTUtmeLa+pmDhHEcM5dOMtQFJIaJR5jaoh6qqh5qq3qQNcac/6OGiFPZnP7xpTTjRFXTqi01FHR2HQFGXUR3GSptgXgWYiTVSqFgcVFBSGN15UDzqE1A+hH0ZToFMNsa37GxZ9yzHFoXQnSRI5Fe+sJfFwkiAKW6GOVCdBDFzblYelBQZxnSSE8QlUCkH2F8L0KRLsD8hLEYh4vntEXKCLVpcQXn4uycHe4CrOj4IYY+FEDWhc51vZYB7bUMaLdlQPotA8BvGQBRywCzLRHSFCVsmYOzqdEesK16SCMvD4IXcGloxst5s+lTdpQCZNVGJN3WQhgNigD8US0A9b2uWIl3XQaGpjh6FDUckoDQcAQqHooAetl64wRoGiNcwJvoOKVFg0eMU2v4o0kErsMuIjSWlcaMGMTUXGskKSJaZLyTFPPKNvBhtLFHq61UoCpUoFIqUCkVqJQKIqOJhwwCL0AFagsVqFAF2qQxCpSAm4ZwHBhx3BkocmRLe+bC4QAQrHGjhslYSFOWAEtNWhp6oRRoLhtWY9dgSCyFd08t4Rm/JhEABcyStuvHyHh55aPoER5QdglC9EkULDoHUFWKE8JeJ4o4WHLGWByTDh0Vl33HTJyzHRTXLHms4jF/XHfYeARgq9PHFGpTXaaqrJRKVEolKwXt+8LRtS4Wim6JqeBgq6WCg9thLEfPecDeFkOwyXZd+Th1YoLIKgH5D5NCGLYTQGiqbQmoUHCM64tjAhxt5SPWscRwSgRlPnYZw7T0Idw9jxNw6PBNzPBPubt8nCxzbBTnKFuu5QXRcbTGI9yXQQhHG6UY5YuWEQBttxNor0NyuFcIuSAU0QrpKDuA+jYXeAlKXe4xRICfHmgsjt+O1oqIwp5oCKxMBwg2PhEOwOUwWtGEAXRss97woMmwvMmovMlUeZNReVhyd3D4o5hFNotzOx47aAAgSV8Q3sMUM8KutBE9wMLayVG4EzZOMKSDZoPxHbOehSDrQQjyPQjNvAIo9gvxtCvmxMXR1CuGqYfEHFhxQiQ0VVUS6CMBR9qLX0OKWXASVTDm2wGHDthWMmoDLCARrIwQ5eq72XiyF3Nixau04lWl4lWV4lWl4lVa8apK8apa8SqteFWpeFWleHVBilcVisfdBNivSzpztIdH1OCTau5cy1YrQOKuiuGsW14FHaE01BEcj3MKB/5TYlaNeyr0mSrymSrlM1XkM9XWPhPsYlIdI94EJWhoUKGSMPGnTJws6TStpU1ThrSfYWAQVTglWsHNLcUiw1J2ReFvpwSbJGYut2HOHJaQu88H0jh9TeKkJS6FwKy1EdIY+mBmuBRjspKDl959XmPTp3HjRAjgJ4QCAG3l0rgVwqM3gkJ6Ab+3bml7j1oEwICbHoiLXog+c8pXCGhUzadRkwhA1QLIB1A1j0bVPHojKARV8+l1j/arBiCuGlrIqwpov20rOaB9HmTzaNQ3BKCAEPIBKMCjoQCP3ggKgQJ8et2jfQUASCrAtu3aeqkLBPUdIiUBQUzQlrHWwdHiqbWdk1MOqUq1NMztKbb3xCD0kUTxk8QTKPQVg5A1AiG1D5ZGHIOxXGS+STxGI7lKa47ASK7SzmIwlousKonHaCRXaWQxSHKp4U5HIFDGMohGBkRRymN1/Jva5hE=
*/