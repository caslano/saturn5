// ----------------------------------------------------------------------------
//  format_class.hpp :  class interface
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_CLASS_HPP
#define BOOST_FORMAT_CLASS_HPP


#include <vector>
#include <string>

#include <boost/optional.hpp> // to store locale when needed

#include <boost/format/format_fwd.hpp>
#include <boost/format/internals_fwd.hpp>
#include <boost/format/internals.hpp>
#include <boost/format/alt_sstream.hpp>

namespace boost {

    template<class Ch, class Tr, class Alloc>
    class basic_format 
    {
        typedef typename io::CompatTraits<Tr>::compatible_type compat_traits;  
    public:
        typedef Ch  CharT;   // borland fails in operator% if we use Ch and Tr directly
        typedef std::basic_string<Ch, Tr, Alloc>              string_type;
        typedef typename string_type::size_type               size_type;
        typedef io::detail::format_item<Ch, Tr, Alloc>        format_item_t;
        typedef io::basic_altstringbuf<Ch, Tr, Alloc>         internal_streambuf_t;
        

        explicit basic_format(const Ch* str=NULL);
        explicit basic_format(const string_type& s);
        basic_format(const basic_format& x);
        basic_format& operator= (const basic_format& x);
        void swap(basic_format& x);

#if !defined(BOOST_NO_STD_LOCALE)
        explicit basic_format(const Ch* str, const std::locale & loc);
        explicit basic_format(const string_type& s, const std::locale & loc);
#endif
        io::detail::locale_t  getloc() const;

        basic_format& clear();       // empty all converted string buffers (except bound items)
        basic_format& clear_binds(); // unbind all bound items, and call clear()
        basic_format& parse(const string_type&); // resets buffers and parse a new format string

        // ** formatted result ** //
        size_type   size() const;    // sum of the current string pieces sizes
        string_type str()  const;    // final string 

        // ** arguments passing ** //
        template<class T>  
        basic_format&   operator%(const T& x)
            { return io::detail::feed<CharT, Tr, Alloc, const T&>(*this,x); }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST
        template<class T>  basic_format&   operator%(T& x) 
            { return io::detail::feed<CharT, Tr, Alloc, T&>(*this,x); }
#endif

        template<class T>
        basic_format& operator%(volatile const T& x)
            { /* make a non-volatile copy */ const T v(x);
              /* pass the copy along      */ return io::detail::feed<CharT, Tr, Alloc, const T&>(*this, v); }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST
        template<class T>
        basic_format& operator%(volatile T& x)
            { /* make a non-volatile copy */ T v(x);
              /* pass the copy along      */ return io::detail::feed<CharT, Tr, Alloc, T&>(*this, v); }
#endif

#if defined(__GNUC__)
        // GCC can't handle anonymous enums without some help
        // ** arguments passing ** //
        basic_format&   operator%(const int& x)
            { return io::detail::feed<CharT, Tr, Alloc, const int&>(*this,x); }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST
        basic_format&   operator%(int& x)
            { return io::detail::feed<CharT, Tr, Alloc, int&>(*this,x); }
#endif
#endif

        // The total number of arguments expected to be passed to the format objectt
        int expected_args() const
            { return num_args_; }
        // The number of arguments currently bound (see bind_arg(..) )
        int bound_args() const;
        // The number of arguments currently fed to the format object
        int fed_args() const;
        // The index (1-based) of the current argument (i.e. next to be formatted)
        int cur_arg() const;
        // The number of arguments still required to be fed
        int remaining_args() const; // same as expected_args() - bound_args() - fed_args()


        // ** object modifying **//
        template<class T>
        basic_format&  bind_arg(int argN, const T& val) 
            { return io::detail::bind_arg_body(*this, argN, val); }
        basic_format&  clear_bind(int argN);
        template<class T> 
        basic_format&  modify_item(int itemN, T manipulator) 
            { return io::detail::modify_item_body<Ch,Tr, Alloc, T> (*this, itemN, manipulator);}

        // Choosing which errors will throw exceptions :
        unsigned char exceptions() const;
        unsigned char exceptions(unsigned char newexcept);

#if !defined( BOOST_NO_MEMBER_TEMPLATE_FRIENDS )  \
    && !BOOST_WORKAROUND(__BORLANDC__, <= 0x570) \
    && !BOOST_WORKAROUND( _CRAYC, != 0) \
    && !BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
        // use friend templates and private members only if supported

#ifndef  BOOST_NO_TEMPLATE_STD_STREAM
        template<class Ch2, class Tr2, class Alloc2>
        friend std::basic_ostream<Ch2, Tr2> & 
        operator<<( std::basic_ostream<Ch2, Tr2> & ,
                    const basic_format<Ch2, Tr2, Alloc2>& );
#else
        template<class Ch2, class Tr2, class Alloc2>
        friend std::ostream & 
        operator<<( std::ostream & ,
                    const basic_format<Ch2, Tr2, Alloc2>& );
#endif

        template<class Ch2, class Tr2, class Alloc2, class T>  
        friend basic_format<Ch2, Tr2, Alloc2>&  
        io::detail::feed_impl (basic_format<Ch2, Tr2, Alloc2>&, T);

        template<class Ch2, class Tr2, class Alloc2, class T>  friend   
        void io::detail::distribute (basic_format<Ch2, Tr2, Alloc2>&, T);
        
        template<class Ch2, class Tr2, class Alloc2, class T>  friend
        basic_format<Ch2, Tr2, Alloc2>& 
        io::detail::modify_item_body (basic_format<Ch2, Tr2, Alloc2>&, int, T);
        
        template<class Ch2, class Tr2, class Alloc2, class T> friend
        basic_format<Ch2, Tr2, Alloc2>&  
        io::detail::bind_arg_body (basic_format<Ch2, Tr2, Alloc2>&, int, const T&);

    private:
#endif
        typedef io::detail::stream_format_state<Ch, Tr>  stream_format_state;
        // flag bits, used for style_
        enum style_values  { ordered = 1, // set only if all directives are  positional
                             special_needs = 4 };     

        void make_or_reuse_data(std::size_t nbitems);// used for (re-)initialisation

        // member data --------------------------------------------//
        std::vector<format_item_t>  items_; // each '%..' directive leads to a format_item
        std::vector<bool> bound_; // stores which arguments were bound. size() == 0 || num_args

        int              style_; // style of format-string :  positional or not, etc
        int             cur_arg_; // keep track of wich argument is current
        int            num_args_; // number of expected arguments
        mutable bool     dumped_; // true only after call to str() or <<
        string_type      prefix_; // piece of string to insert before first item
        unsigned char exceptions_;
        internal_streambuf_t   buf_; // the internal stream buffer.
        boost::optional<io::detail::locale_t>     loc_;
    }; // class basic_format

} // namespace boost


#endif // BOOST_FORMAT_CLASS_HPP

/* format_class.hpp
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
*/