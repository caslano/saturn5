
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINE2_DETAIL_WRAP_H
#define BOOST_COROUTINE2_DETAIL_WRAP_H

#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/detail/invoke.hpp>
#include <boost/context/fiber.hpp>

#include <boost/coroutine2/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename Fn1, typename Fn2  >
class wrapper {
private:
    typename std::decay< Fn1 >::type    fn1_;
    typename std::decay< Fn2 >::type    fn2_;

public:
    wrapper( Fn1 && fn1, Fn2 && fn2) :
        fn1_( std::move( fn1) ),
        fn2_( std::move( fn2) ) {
    }

    wrapper( wrapper const&) = delete;
    wrapper & operator=( wrapper const&) = delete;

    wrapper( wrapper && other) = default;
    wrapper & operator=( wrapper && other) = default;

    boost::context::fiber
    operator()( boost::context::fiber && c) {
        return boost::context::detail::invoke(
                std::move( fn1_),
                fn2_,
                std::forward< boost::context::fiber >( c) );
    }
};

template< typename Fn1, typename Fn2 >
wrapper< Fn1, Fn2 >
wrap( Fn1 && fn1, Fn2 && fn2) {
    return wrapper< Fn1, Fn2 >(
            std::forward< Fn1 >( fn1),
            std::forward< Fn2 >( fn2) );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINE2_DETAIL_WRAP_H

/* wrap.hpp
9YI4ezxndcrgo5v857QRHF3mvexfKy5i1JsBlV4lzB0ovx8BI9i2qDBSRokgr+RRkBEAr+B8UGQhJBF7pBFbDRY8fl4w2QtjttCbNxFYynpdwUhFcArc2gsqqp1f+QI5BwPytxThMqyBLxj7LlMic62neWcbYNIXFii6babL/MVn5p3QVm9ww+ylL9g/mwfT4Df5LOAM98XzBfAy02V9+HO1mFAz41fLOcUJhTWUQClXzgcRazb88jfLGaGQWjaTsJYfS9b89Hk505d0G3k65300NNNPSntHb138SYqys9NuRCJ5DAxUqV3pdFt/43SLNhUCblKzG5k1cvZUMHRLK9sFaXSkONmny5UiCXYzMqTVKeX4F2iHOVTccRUsZiiBSi50wWP2uidUQlmK4vtD9vz4gRahNQ6zgGW55pJGm2jCuQgPqWFLa+8WL/r0CgVUH9oE1SIhYgVSvizeLEn3cBjH2mGCOSXDJZep7GkWGWGrTyEK6cGo5V/oBof1WFWI1uLkS6PN9w5dFl/xAXKH6ydyXdkzdAeSwsNM10JjD/qM1G6XoWGFSEIlF+6wTo96r49YVygVJv+8q7+qJHgevc1hvj2DmHQiEL9F4iL181ExCceK6LjnZVLqY8KbaIHVNw1BpCzLkJR80tb2JhPuKbvIX66wX3MReBGNpphqQWo+NHlT5jTHoa+t4NuEj426638EBUk5ouhxDkZN
*/