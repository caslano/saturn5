//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593
#define BOOST_EXCEPTION_E788439ED9F011DCB181F25B55D89593

#include <boost/exception/to_string.hpp>
#include <boost/exception/detail/object_hex_dump.hpp>
#include <boost/assert.hpp>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        template <bool ToStringAvailable>
        struct
        to_string_dispatcher
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub )
                {
                return to_string(x);
                }
            };

        template <>
        struct
        to_string_dispatcher<false>
            {
            template <class T,class Stub>
            static
            std::string
            convert( T const & x, Stub s )
                {
                return s(x);
                }

            template <class T>
            static
            std::string
            convert( T const & x, std::string s )
                {
                return s;
                }

            template <class T>
            static
            std::string
            convert( T const & x, char const * s )
                {
                BOOST_ASSERT(s!=0);
                return s;
                }
            };

        namespace
        to_string_dispatch
            {
            template <class T,class Stub>
            inline
            std::string
            dispatch( T const & x, Stub s )
                {
                return to_string_dispatcher<has_to_string<T>::value>::convert(x,s);
                }
            }

        template <class T>
        inline
        std::string
        string_stub_dump( T const & x )
            {
            return "[ " + exception_detail::object_hex_dump(x) + " ]";
            }
        }

    template <class T>
    inline
    std::string
    to_string_stub( T const & x )
        {
        return exception_detail::to_string_dispatch::dispatch(x,&exception_detail::string_stub_dump<T>);
        }

    template <class T,class Stub>
    inline
    std::string
    to_string_stub( T const & x, Stub s )
        {
        return exception_detail::to_string_dispatch::dispatch(x,s);
        }

    template <class T,class U,class Stub>
    inline
    std::string
    to_string_stub( std::pair<T,U> const & x, Stub s )
        {
        return std::string("(") + to_string_stub(x.first,s) + ',' + to_string_stub(x.second,s) + ')';
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* to_string_stub.hpp
dV5Puyr+Mu0K7yjt0lf9/0m7rg/pCO3aWn0h2iVfhktfcllQ2rVhSbtr/74hGG4pR9zyssEXtywzdAQApOpguGXwReKezud299fFPhgFpKp03SzORN0NaPrDOtqFcqwpJ9ET8Sx+ow6hH9fTqeOgqeTv7Ae4TycbcJDxLIo87y2HgkmYxsuiEv618TwroU1WglKHWThQ3P0CknDEWZmEOpolunhLElYfPurp/oH5ktULzGRV0psJIhK8sra7O1tLTxZFkStGc6SkuZ8Emckf3ji2ADeqRm5mUXcO9qYov+l+vF7RGapQP4uym2aynMxA2MaiQzeZH9MJqVx3QhKrV9iHZHKx/RHsIunRSceP+OCdXg+0C3vD2FCC4x2bactKEHbnEeYJx3FfCPBWfRQM82zt7a9f4Id78hfpcI9piz/yWXU+rg3yMW3Zib0U6Ac2PkME71e2wT8PXRD/dAmOf9ar+OdG9v3Oyv8eAb1/Lq4DCCh1z4UQUNd+CAKh/YLxNuaidmHgunNxQfAPOUK+nOXr8c/5PzsCBss/DIZ/3om/AG8ze6EeE/3Lj7cpZR1ow9t8h7yNuEZhvM1H9gEH2uVtwlBsvHMj8g51yuwkPW9zGJJ+uzwWs+5N+os8zo6uCEYHOsbj1CnfXN4+j3OgPR4n/2ycH48zlaXpeBzr2bgO8Dh1VRfgcZ6/GOHsqYuD8ThvuNqFs9ozF8I1
*/