// ----------------------------------------------------------------------------
//  alt_sstream.hpp : alternative stringstream 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------



#ifndef BOOST_SK_ALT_SSTREAM_HPP
#define BOOST_SK_ALT_SSTREAM_HPP

#include <string>
#include <boost/core/allocator_access.hpp>
#include <boost/format/detail/compat_workarounds.hpp>
#include <boost/utility/base_from_member.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>

namespace boost {
    namespace io {

        template<class Ch, class Tr=::std::char_traits<Ch>, 
                 class Alloc=::std::allocator<Ch> >
        class basic_altstringbuf;

        template<class Ch, class Tr =::std::char_traits<Ch>, 
                 class Alloc=::std::allocator<Ch> >
        class basic_oaltstringstream;


        template<class Ch, class Tr, class Alloc>
        class basic_altstringbuf 
            : public ::std::basic_streambuf<Ch, Tr>
        {
            typedef ::std::basic_streambuf<Ch, Tr>  streambuf_t;
            typedef typename CompatAlloc<Alloc>::compatible_type compat_allocator_type;
            typedef typename CompatTraits<Tr>::compatible_type   compat_traits_type;
        public:
            typedef Ch     char_type;
            typedef Tr     traits_type;
            typedef typename compat_traits_type::int_type     int_type;
            typedef typename compat_traits_type::pos_type     pos_type;
            typedef typename compat_traits_type::off_type     off_type;
            typedef Alloc                     allocator_type;
            typedef ::std::basic_string<Ch, Tr, Alloc> string_type;
            typedef typename string_type::size_type    size_type;

            typedef ::std::streamsize streamsize;


            explicit basic_altstringbuf(std::ios_base::openmode mode
                                        = std::ios_base::in | std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                {}
            explicit basic_altstringbuf(const string_type& s,
                                        ::std::ios_base::openmode mode
                                        = ::std::ios_base::in | ::std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                { dealloc(); str(s); }
            virtual ~basic_altstringbuf() BOOST_NOEXCEPT_OR_NOTHROW
                { dealloc(); }
            using streambuf_t::pbase;
            using streambuf_t::pptr;
            using streambuf_t::epptr;
            using streambuf_t::eback;
            using streambuf_t::gptr;
            using streambuf_t::egptr;
    
            void clear_buffer();
            void str(const string_type& s);

            // 0-copy access :
            Ch * begin() const; 
            size_type size() const;
            size_type cur_size() const; // stop at current pointer
            Ch * pend() const // the highest position reached by pptr() since creation
                { return ((putend_ < pptr()) ? pptr() : putend_); }
            size_type pcount() const 
                { return static_cast<size_type>( pptr() - pbase()) ;}

            // copy buffer to string :
            string_type str() const 
                { return string_type(begin(), size()); }
            string_type cur_str() const 
                { return string_type(begin(), cur_size()); }
        protected:
            explicit basic_altstringbuf (basic_altstringbuf * s,
                                         ::std::ios_base::openmode mode 
                                         = ::std::ios_base::in | ::std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                { dealloc(); str(s); }

            virtual pos_type seekoff(off_type off, ::std::ios_base::seekdir way, 
                                     ::std::ios_base::openmode which 
                                     = ::std::ios_base::in | ::std::ios_base::out);
            virtual pos_type seekpos (pos_type pos, 
                                      ::std::ios_base::openmode which 
                                      = ::std::ios_base::in | ::std::ios_base::out);
            virtual int_type underflow();
            virtual int_type pbackfail(int_type meta = compat_traits_type::eof());
            virtual int_type overflow(int_type meta = compat_traits_type::eof());
            void dealloc();
        private:
            enum { alloc_min = 256}; // minimum size of allocations

            Ch *putend_;  // remembers (over seeks) the highest value of pptr()
            bool is_allocated_;
            ::std::ios_base::openmode mode_;
            compat_allocator_type alloc_;  // the allocator object
        };


// ---   class basic_oaltstringstream ----------------------------------------
        template <class Ch, class Tr, class Alloc>
        class basic_oaltstringstream 
            : private base_from_member< shared_ptr< basic_altstringbuf< Ch, Tr, Alloc> > >,
              public ::std::basic_ostream<Ch, Tr>
        {
            class No_Op { 
                // used as no-op deleter for (not-owner) shared_pointers
            public: 
                template<class T>
                const T & operator()(const T & arg) { return arg; }
            };
            typedef ::std::basic_ostream<Ch, Tr> stream_t;
            typedef boost::base_from_member<boost::shared_ptr<
                basic_altstringbuf<Ch,Tr, Alloc> > > 
                pbase_type;
            typedef ::std::basic_string<Ch, Tr, Alloc>  string_type;
            typedef typename string_type::size_type     size_type;
            typedef basic_altstringbuf<Ch, Tr, Alloc>   stringbuf_t;
        public:
            typedef Alloc  allocator_type;
            basic_oaltstringstream() 
                : pbase_type(new stringbuf_t), stream_t(pbase_type::member.get())
                { }
            basic_oaltstringstream(::boost::shared_ptr<stringbuf_t> buf) 
                : pbase_type(buf), stream_t(pbase_type::member.get())
                { }
            basic_oaltstringstream(stringbuf_t * buf) 
                : pbase_type(buf, No_Op() ), stream_t(pbase_type::member.get())
                { }
            stringbuf_t * rdbuf() const 
                { return pbase_type::member.get(); }
            void clear_buffer() 
                { rdbuf()->clear_buffer(); }

            // 0-copy access :
            Ch * begin() const 
                { return rdbuf()->begin(); }
            size_type size() const 
                { return rdbuf()->size(); }
            size_type cur_size() const // stops at current position
                { return rdbuf()->cur_size(); }

            // copy buffer to string :
            string_type str()     const   // [pbase, epptr[
                { return rdbuf()->str(); } 
            string_type cur_str() const   // [pbase, pptr[
                { return rdbuf()->cur_str(); }
            void str(const string_type& s) 
                { rdbuf()->str(s); }
        };

    } // N.S. io
} // N.S. boost

#include <boost/format/alt_sstream_impl.hpp>

#endif // include guard


/* alt_sstream.hpp
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
*/