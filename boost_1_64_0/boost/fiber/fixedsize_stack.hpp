
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIXEDSIZE_STACK_H
#define BOOST_FIBERS_FIXEDSIZE_STACK_H

#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using   default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIXEDSIZE_STACK_H

/* fixedsize_stack.hpp
StA/Iiieu5qH8X5SlgSae7QsQG96WPQ6StABAIr09jcLg943DgLaX6HRqxcWvZcl6EMVRO+mcOjNkUCv/UWjt3J7OPQuk6B3/oXofRsbBj2PBLroE41e57Do/a2yTIBGfEL05oVDb7UEOujS3796LRx6oyXoGheNl7PCoZcsgbpFavQGhkXvh18I9NsIovdk0zDolUigG37S2vOD0nDoLZSgHX6i9uwZDj2fBLrQ0OjdEha9WAnqMIjea03CoHfwZwIatQ+B5K7raxq2/9xqCR+P8Nz/JeHwO1qCVuwlfs9ifsOyXxYLZjuJYw3iwBO/dFHdbfUU67tdymThyLv0/tlJQj0IUNu9f9aghu+VTZX47nXbv39WU3wJEt/lR2z5G15TfAdOEL6iw7b46tQU3yKJb3eJLb5N9WuIr4/EN+oDW3xjaoqv/DjhS/jFFl+zmuJbLvE9UGmLb2d0DfENkPgOf2+Lb2pN8R39ifAd+swWX0J0+O/lPStRdX/TKv/uqhfOe3XjJPyCqHIL/J1hwSdJ+IyvrPQvDwvef4zg3zxkha8bFvyzEv7LbUH1d4cDP07Crzxghb8zLPgkCf+nN6zwz28N57zl/5Hgk04E1T8s+s9K+HUng+pfNxz4cRK+3rdB9Q8LPknCNzsU1P/VwaeI+h8V8NIi8qJe++FEOOln/dpaXiuPonvheDffC9+J98LthDgIOki8qZPv5zXH3N78Cl3UyRroAOzfPyQmjX+8VxZs2W3e3uKMx/DIg/4I+CUf8+vFzORDPwdetXnQVVMr9aD+/0GwVtyTo/GU/hlSpB9YD2n7EkPvit/qlyYxyFsKhULWID8+Xv2VptVUK4noG3s/sDHiaEV9llMnEGOJ+8x5SPTZxcYX78jbVQwrTnH5yP6pTlQ5ZSxxAr8YsNSDKP7AISe7Hi8Lw8Ir5H1szveCdUaYaizaZurf3Gj5VqFHNGZP8aV7RCUa3YF5frlQLOVONFhLhFGcFRnOPW26jSr/PbQK1COBX/auuXGTtDffm0QFomhz4z79D2zcCnxfgg/PW14vqxSGUaMqythgRihpZ+Uaq1iBjsWtjrEu/23G1m91cypMuy4QXyYJMoXJ7ACCt3tm3L3L4QJ+uFb8WFuWgT2gP2d1AdbPR/XrFWlTvx1wLiLKHXfIyhjr95adoZjKVcw/rLnFXrLL/rJq33vIFuffI+ZuZrtqqTJP9WC3fWpAt+02cn4hyTxhv742kva3pwuP/GhMY40W3y9CtGGnCG7DAm7DOX+HW5l3nQFyKV5pNp6hXv3JpGlxy49C7RJVsZZL4+APOGZECVsmN+IPvOE3zV2OUBSnjfh43IV8rDDzcexj4CPDiZaJn9AeghafRAat9CsdFItKjruoCmHtzTFoOSD8j7sklw4ncjOE3u3p6lLh2WfX0cKz41WOr9d+giyKKCfInaIeQwnyW6dHrjN3v2wa+vSYEaHQ6E9WWOY4rK3kDN1KV9UVUAnCP5NaabrTppX2g7mLvzNRcu5BY1BJnVsq0eiwU2qj/B3gGQdZfyfXP0oZT5XuLvv3PYBwin+B86dlIj75lZyIYqiUJAtZQEjWyuTkiW5h6JhD4r/EjL9FMP60cPBb90//l7R/Dt5F83v9p/pSr6YxLYVZlTHSfbl4Jg+MLbDxVrwph1wmrhgbDosV46LjhPH7N82jVwy1SwhjI4FxghnjWMDonyVEBLBfLp7I8sFFKJeRwR3KFPRTRhv09+dggT5kIiNSBPYkaoOI2upfbPj/6X2g5uGIgjR+GxDB/JNlp+GJzerHk9UJ6n0R/+YLXp4zgx2ZyDjSFMo9ZOh3n0pcZ+MH5eUI8Jbw8KlW96o=
*/