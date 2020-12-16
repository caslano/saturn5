// ----------------------------------------------------------------------------
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_STREAM_TRANSLATOR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_STREAM_TRANSLATOR_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <sstream>
#include <string>
#include <locale>
#include <limits>

namespace boost { namespace property_tree
{

    template <typename Ch, typename Traits, typename E, typename Enabler = void>
    struct customize_stream
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, const E& e) {
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, E& e) {
            s >> e;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    // No whitespace skipping for single characters.
    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, Ch, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, Ch e) {
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, Ch& e) {
            s.unsetf(std::ios_base::skipws);
            s >> e;
        }
    };

    // Ugly workaround for numeric_traits that don't have members when not
    // specialized, e.g. MSVC.
    namespace detail
    {
        template <bool is_specialized>
        struct is_inexact_impl
        {
            template <typename T>
            struct test
            {
                typedef boost::false_type type;
            };
        };
        template <>
        struct is_inexact_impl<true>
        {
            template <typename T>
            struct test
            {
              typedef boost::integral_constant<bool,
                  !std::numeric_limits<T>::is_exact> type;
            };
        };

        template <typename F>
        struct is_inexact
        {
            typedef typename boost::decay<F>::type decayed;
            typedef typename is_inexact_impl<
                std::numeric_limits<decayed>::is_specialized
            >::BOOST_NESTED_TEMPLATE test<decayed>::type type;
            static const bool value = type::value;
        };
    }

    template <typename Ch, typename Traits, typename F>
    struct customize_stream<Ch, Traits, F,
        typename boost::enable_if< detail::is_inexact<F> >::type
    >
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, const F& e) {
#ifndef BOOST_NO_CXX11_NUMERIC_LIMITS 
            s.precision(std::numeric_limits<F>::max_digits10); 
#else 
            s.precision(std::numeric_limits<F>::digits10 + 2); 
#endif 
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, F& e) {
            s >> e;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, bool, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, bool e) {
            s.setf(std::ios_base::boolalpha);
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, bool& e) {
            s >> e;
            if(s.fail()) {
                // Try again in word form.
                s.clear();
                s.setf(std::ios_base::boolalpha);
                s >> e;
            }
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, signed char, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, signed char e) {
            s << (int)e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, signed char& e) {
            int i;
            s >> i;
            // out of range?
            if(i > (std::numeric_limits<signed char>::max)() ||
                i < (std::numeric_limits<signed char>::min)())
            {
                s.clear(); // guarantees eof to be unset
                e = 0;
                s.setstate(std::ios_base::badbit);
                return;
            }
            e = (signed char)i;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, unsigned char, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, unsigned char e) {
            s << (unsigned)e;
        }
        static void extract(std::basic_istream<Ch,Traits>& s, unsigned char& e){
            unsigned i;
            s >> i;
            // out of range?
            if(i > (std::numeric_limits<unsigned char>::max)()) {
                s.clear(); // guarantees eof to be unset
                e = 0;
                s.setstate(std::ios_base::badbit);
                return;
            }
            e = (unsigned char)i;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    /// Implementation of Translator that uses the stream overloads.
    template <typename Ch, typename Traits, typename Alloc, typename E>
    class stream_translator
    {
        typedef customize_stream<Ch, Traits, E> customized;
    public:
        typedef std::basic_string<Ch, Traits, Alloc> internal_type;
        typedef E external_type;

        explicit stream_translator(std::locale loc = std::locale())
            : m_loc(loc)
        {}

        boost::optional<E> get_value(const internal_type &v) {
            std::basic_istringstream<Ch, Traits, Alloc> iss(v);
            iss.imbue(m_loc);
            E e;
            customized::extract(iss, e);
            if(iss.fail() || iss.bad() || iss.get() != Traits::eof()) {
                return boost::optional<E>();
            }
            return e;
        }
        boost::optional<internal_type> put_value(const E &v) {
            std::basic_ostringstream<Ch, Traits, Alloc> oss;
            oss.imbue(m_loc);
            customized::insert(oss, v);
            if(oss) {
                return oss.str();
            }
            return boost::optional<internal_type>();
        }

    private:
        std::locale m_loc;
    };

    // This is the default translator when basic_string is the internal type.
    // Unless the external type is also basic_string, in which case
    // id_translator takes over.
    template <typename Ch, typename Traits, typename Alloc, typename E>
    struct translator_between<std::basic_string<Ch, Traits, Alloc>, E>
    {
        typedef stream_translator<Ch, Traits, Alloc, E> type;
    };

}}

#endif

/* stream_translator.hpp
1WN/7t0/eNu+fTtrNn6/8PDeR7/944E1+9/6Y8jkmuqN5Qd3DDm47dlZO3fW1Gy/7KvVD65ZXFPz8cHqxeW3VNT8uK1637odOx4/vHXenv3flO/dsbimuuaPIYvbv3/44LeLaqr3/7LvYPvN+3cenLmxqvq9jWvaf7vxcPviD3e/W/1yTfWOg9U7BrxVXXPzZ9X726/+tqbm8MFDl/S9o2BIdfniiiE12zbu37m46vZfH3lz48GNNX3fWjyhfM5j3yzev7g6fOT9/Ru///PUn2vaHxyys6ZgyH92/lBT/fG7Q6prBn8278fVQckP/dx+8cad79U5uOj3mhcGrF9UMX/lzvO3JfyrHeTEIG2DdAoyMMjwIGODzAgyN8iSILuCHBcMp0mQ84K0CnJlkNuC3BdkaJAXg0wL8mGQFUG+DnIgSKPQG7ooyLVB+gUZH2RWkC+C/BIkkR7mEeSMIC2CtA3SKUi3IL2CDAwyPMjYIDOCLAnyXZAtQXYFqZUR5hakSZDzgnQJMjTI6CDTgqwIsinI9iB1U2EuQToEuTtIvyAjg8wKMj/IsiB7gtQ+IswhSLcgA4O8HGRukCVBVgX5LsihIMcdGXQR5MogtwW5L0j/IC8GWRGkbq1wvyAdglwb5O4gg4KMDDI+yKwgG4LsCXJGZlh/kE5BegXpE2R4kBlB5gZZEuS7IFuC1DoqrDVIlyC3BRkaZHSQt4N8GGRTkO1BGh2dSJwd5NogPYIMCjI+yKwg84N8EWRPkNq1w72DtA3SKcjAIMODzAiyJMiqIFuCHApyXp2w5iBXBukS5LYg9wUZHeTFIG8HWRHk6yCbgtQ9JswjyEVBOgS5NkiPIP2CjA8yK8j8IMuCfBEk8Zdgk0FaBGkbpFeQPkGGB5kbZEuQXUEOBalVN8wlyJVBugTpH2R0kGlBPgyyIsimIAeCZNQL8whyUZAOQa4NcneQQUFmBVkWZEOQ2vXDfYP0CTI8yMtBZgRZEmRVkC1BdgU5FKTJsUEfQVoF6RLkviD9gwwN8mKQD4OsCPJ1kO1BDgTJOC7MI0iPIP2CDAoyPsgXQTYE2ROkdoOggyAtgrQN0itInyBjg7wcZG6QVUF2BTnu+HD/IF2C9A8yNMjoIC8GmRbkwyArgmwKUveEsP4gHYLcHWRkkFlBlgX5IsiGIIkTw/2DnBGkW5BeQYYHmRFkbpAlQbYE2RWkScNw7yD3BRkaZHSQt4OsCLIpyPYgGSeF+wa5KMi1QXoEuTvI+CBTgswPsiFI4uSw1iC9gvQJMjDI8CBjg8wIMjfId0FqNQr3DHJfkP5BhgZ5Mci0IB8GWRFkU5DtQRo1DvcNcneQfkEGBRkZZHyQKUFmBVkWZEOQPUFqnxLWHaRFkLZBxgaZEWRukCVBVgXZEmRXkENBap0adBDkyiBdgvQPMjrItCBfB9ke5ECQjP+xdO/x6UZjAMBfhDAMw8/9NvfbMPwQhiEMQxhCCMMQhhCGIQwhhBBCCCGEEEIIIYQQQgghhFy+wx/fz3PqvZznPO95T63drqgGXJYtdtgjQ5Y8VRq0GTLnzJXkwwZpclSo02LAmBlXvLIciHNCgTJNOvQZMeWyV1EXkqTIkCVPiQZt5qysy4N1IsQ44JgiFep0GTDjild1jdhmnyM69BkxZfVqcmCLFFlKDJkTXF2/REmQJkedFmNmhK/hHmCbXY44oUCHEVMWrF7T2NlkhxQZSlRpM2FOcC39s0GEBGlyFGnRZcDatY2Zs2xzyBE1moyYErqO9ZhNdkiRpUSDIROC66o3EaLESJCjyJjw9fTJWbaJs88hJxSo0aTDlAWh66sDl+UapMhTpceQYEPfJDggTZEKdQY=
*/