// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DEFINE_ADAPTOR_HPP_INCLUDED
#define BOOST_RANGE_DEFINE_ADAPTOR_HPP_INCLUDED

#include <boost/tuple/tuple.hpp>

#define BOOST_DEFINE_RANGE_ADAPTOR( adaptor_name, range_adaptor ) \
    struct adaptor_name##_forwarder {}; \
    \
    template<typename Range> range_adaptor <Range> \
        operator|(Range& rng, adaptor_name##_forwarder) \
    { \
        return range_adaptor <Range>( rng ); \
    } \
    \
    template<typename Range> range_adaptor <const Range> \
        operator|(const Range& rng, adaptor_name##_forwarder) \
    { \
        return range_adaptor <const Range>( rng ); \
    } \
    \
    static adaptor_name##_forwarder adaptor_name = adaptor_name##_forwarder(); \
    \
    template<typename Range> \
    range_adaptor <Range> \
    make_##adaptor_name(Range& rng) \
    { \
        return range_adaptor <Range>(rng); \
    } \
    \
    template<typename Range> \
    range_adaptor <const Range> \
    make_##adaptor_name(const Range& rng) \
    { \
        return range_adaptor <const Range>(rng); \
    }

#define BOOST_DEFINE_RANGE_ADAPTOR_1( adaptor_name, range_adaptor, arg1_type ) \
    struct adaptor_name \
    { \
        explicit adaptor_name (arg1_type arg1_) \
            : arg1(arg1_) {} \
        arg1_type arg1; \
    }; \
    \
    template<typename Range> range_adaptor <Range> \
        operator|(Range& rng, adaptor_name args) \
    { \
        return range_adaptor <Range>(rng, args.arg1); \
    } \
    \
    template<typename Range> range_adaptor <const Range> \
        operator|(const Range& rng, adaptor_name args) \
    { \
        return range_adaptor <const Range>(rng, args.arg1); \
    } \
    \
    template<typename Range> \
    range_adaptor <Range> \
    make_##adaptor_name(Range& rng, arg1_type arg1) \
    { \
        return range_adaptor <Range>(rng, arg1); \
    } \
    \
    template<typename Range> \
    range_adaptor <const Range> \
    make_##adaptor_name(const Range& rng, arg1_type arg1) \
    { \
        return range_adaptor <const Range>(rng, arg1); \
    }

#define BOOST_RANGE_ADAPTOR_2( adaptor_name, range_adaptor, arg1_type, arg2_type ) \
    struct adaptor_name \
    { \
        explicit adaptor_name (arg1_type arg1_, arg2_type arg2_) \
            : arg1(arg1_), arg2(arg2_) {} \
        arg1_type arg1; \
        arg2_type arg2; \
    }; \
    \
    template<typename Range> range_adaptor <Range> \
    operator|(Range& rng, adaptor_name args) \
    { \
        return range_adaptor <Range>(rng, args.arg1, args.arg2); \
    } \
    template<typename Range> \
    range_adaptor <Range> \
    make_##adaptor_name(Range& rng, arg1_type arg1, arg2_type arg2) \
    { \
        return range_adaptor <Range>(rng, arg1, arg2); \
    } \
    template<typename Range> \
    range_adaptor <const Range> \
    make_##adaptor_name(const Range& rng, arg1_type arg1, arg2_type arg2) \
    { \
        return range_adaptor <const Range>(rng, arg1, arg2); \
    }


#endif // include guard

/* define_adaptor.hpp
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
*/