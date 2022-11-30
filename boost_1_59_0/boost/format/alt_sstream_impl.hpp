// ----------------------------------------------------------------------------
//  alt_sstream_impl.hpp : alternative stringstream, templates implementation 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_SK_ALT_SSTREAM_IMPL_HPP
#define BOOST_SK_ALT_SSTREAM_IMPL_HPP

namespace boost {
    namespace io {
// --- Implementation  ------------------------------------------------------//

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: 
        clear_buffer () {
            const Ch * p = pptr();
            const Ch * b = pbase();
            if(p != NULL && p != b) {
                seekpos(0, ::std::ios_base::out); 
            }
            p = gptr();
            b = eback();
            if(p != NULL && p != b) {
                seekpos(0, ::std::ios_base::in); 
            }
        }

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: 
        str (const string_type& s) {
            size_type sz=s.size();
            if(sz != 0 && mode_ & (::std::ios_base::in | ::std::ios_base::out) ) {
#ifdef _RWSTD_NO_CLASS_PARTIAL_SPEC
                void *vd_ptr = boost::allocator_allocate(alloc_, sz, is_allocated_? eback() : 0);
                Ch *new_ptr = static_cast<Ch *>(vd_ptr);
#else
                Ch *new_ptr = boost::allocator_allocate(alloc_, sz, is_allocated_? eback() : 0);
#endif
                // if this didnt throw, we're safe, update the buffer
                dealloc();
                sz = s.copy(new_ptr, sz);
                putend_ = new_ptr + sz;
                if(mode_ & ::std::ios_base::in)
                    streambuf_t::setg(new_ptr, new_ptr, new_ptr + sz);
                if(mode_ & ::std::ios_base::out) {
                    streambuf_t::setp(new_ptr, new_ptr + sz);
                    if(mode_ & (::std::ios_base::app | ::std::ios_base::ate))
                        streambuf_t::pbump(static_cast<int>(sz));
                    if(gptr() == NULL)
                        streambuf_t::setg(new_ptr, NULL, new_ptr);
                }
                is_allocated_ = true;
            }
            else 
                dealloc();
        }
        template<class Ch, class Tr, class Alloc>
        Ch*   basic_altstringbuf<Ch, Tr, Alloc>:: 
        begin () const {
            if(mode_ & ::std::ios_base::out && pptr() != NULL)
                return pbase();
            else if(mode_ & ::std::ios_base::in && gptr() != NULL)
                return eback();
            return NULL;
        }

        template<class Ch, class Tr, class Alloc>
        typename std::basic_string<Ch,Tr,Alloc>::size_type
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        size () const { 
            if(mode_ & ::std::ios_base::out && pptr())
                return static_cast<size_type>(pend() - pbase());
            else if(mode_ & ::std::ios_base::in && gptr())
                return static_cast<size_type>(egptr() - eback());
            else 
                return 0;
        }

        template<class Ch, class Tr, class Alloc>
        typename std::basic_string<Ch,Tr,Alloc>::size_type
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        cur_size () const { 
            if(mode_ & ::std::ios_base::out && pptr())
                return static_cast<streamsize>( pptr() - pbase());
            else if(mode_ & ::std::ios_base::in && gptr())
                return static_cast<streamsize>( gptr() - eback());
            else 
                return 0;
        }

        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::pos_type  
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        seekoff (off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which) {
            if(pptr() != NULL && putend_ < pptr())
                putend_ = pptr();
            if(which & ::std::ios_base::in && gptr() != NULL) {
                // get area
                if(way == ::std::ios_base::end)
                    off += static_cast<off_type>(putend_ - gptr());
                else if(way == ::std::ios_base::beg)
                    off += static_cast<off_type>(eback() - gptr());
                else if(way != ::std::ios_base::cur || (which & ::std::ios_base::out) )
                    // (altering in&out is only supported if way is beg or end, not cur)
                    return pos_type(off_type(-1));
                if(eback() <= off+gptr() && off+gptr() <= putend_ ) {
                    // set gptr
                    streambuf_t::gbump(static_cast<int>(off));
                    if(which & ::std::ios_base::out && pptr() != NULL)
                        // update pptr to match gptr
                        streambuf_t::pbump(static_cast<int>(gptr()-pptr()));
                }
                else
                    off = off_type(-1);
            }
            else if(which & ::std::ios_base::out && pptr() != NULL) {
                // put area
                if(way == ::std::ios_base::end)
                    off += static_cast<off_type>(putend_ - pptr());
                else if(way == ::std::ios_base::beg)
                    off += static_cast<off_type>(pbase() - pptr());
                else if(way != ::std::ios_base::beg)
                    return pos_type(off_type(-1));                    
                if(pbase() <= off+pptr() && off+pptr() <= putend_)
                    // set pptr
                    streambuf_t::pbump(static_cast<int>(off)); 
                else
                    off = off_type(-1);
            }
            else // neither in nor out
                off = off_type(-1);
            return (pos_type(off));
        }
        //- end seekoff(..)

        
        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::pos_type 
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        seekpos (pos_type pos, ::std::ios_base::openmode which) {
            off_type off = off_type(pos); // operation guaranteed by fpos.operations table 127
            if(pptr() != NULL && putend_ < pptr())
                putend_ = pptr();
            if(off != off_type(-1)) {
                if(which & ::std::ios_base::in && gptr() != NULL) {
                    // get area
                    if(0 <= off && off <= putend_ - eback()) {
                        streambuf_t::gbump(static_cast<int>(eback() - gptr() + off));
                        if(which & ::std::ios_base::out && pptr() != NULL) {
                            // update pptr to match gptr
                            streambuf_t::pbump(static_cast<int>(gptr()-pptr()));
                        }
                    }
                    else
                        off = off_type(-1);
                }
                else if(which & ::std::ios_base::out && pptr() != NULL) {
                    // put area
                    if(0 <= off && off <= putend_ - eback())
                        streambuf_t::pbump(static_cast<int>(eback() - pptr() + off));
                    else
                        off = off_type(-1);
                }
                else // neither in nor out
                    off = off_type(-1);
                return (pos_type(off));
            }
            else {
                BOOST_ASSERT(0); // fpos.operations allows undefined-behaviour here
                return pos_type(off_type(-1));
            }
        }
        // -end seekpos(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        underflow () {
            if(gptr() == NULL) // no get area -> nothing to get.
                return (compat_traits_type::eof()); 
            else if(gptr() < egptr())  // ok, in buffer
                return (compat_traits_type::to_int_type(*gptr())); 
            else if(mode_ & ::std::ios_base::in && pptr() != NULL
                    && (gptr() < pptr() || gptr() < putend_) )
                {  // expand get area 
                    if(putend_ < pptr()) 
                        putend_ = pptr(); // remember pptr reached this far
                    streambuf_t::setg(eback(), gptr(), putend_);
                    return (compat_traits_type::to_int_type(*gptr()));
                }
            else // couldnt get anything. EOF.
                return (compat_traits_type::eof());
        }
        // -end underflow(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type 
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        pbackfail (int_type meta) {
            if(gptr() != NULL  &&  (eback() < gptr()) 
               && (mode_ & (::std::ios_base::out)
                   || compat_traits_type::eq_int_type(compat_traits_type::eof(), meta)
                   || compat_traits_type::eq(compat_traits_type::to_char_type(meta), gptr()[-1]) ) ) { 
                streambuf_t::gbump(-1); // back one character
                if(!compat_traits_type::eq_int_type(compat_traits_type::eof(), meta))
                    //  put-back meta into get area
                    *gptr() = compat_traits_type::to_char_type(meta);
                return (compat_traits_type::not_eof(meta));
            }
            else
                return (compat_traits_type::eof());  // failed putback
        }
        // -end pbackfail(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type 
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        overflow (int_type meta) {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4996)
#endif
            if(compat_traits_type::eq_int_type(compat_traits_type::eof(), meta))
                return compat_traits_type::not_eof(meta); // nothing to do
            else if(pptr() != NULL && pptr() < epptr()) {
                streambuf_t::sputc(compat_traits_type::to_char_type(meta));
                return meta;
            }
            else if(! (mode_ & ::std::ios_base::out)) 
                // no write position, and cant make one
                return compat_traits_type::eof(); 
            else { // make a write position available
                std::size_t prev_size = pptr() == NULL ? 0 : epptr() - eback();
                std::size_t new_size = prev_size;
                // exponential growth : size *= 1.5
                std::size_t add_size = new_size / 2;
                if(add_size < alloc_min)
                    add_size = alloc_min;
                Ch * newptr = NULL,  *oldptr = eback();

                // make sure adding add_size wont overflow size_t
                while (0 < add_size && ((std::numeric_limits<std::size_t>::max)()
                                        - add_size < new_size) )
                    add_size /= 2;
                if(0 < add_size) {
                    new_size += add_size;
#ifdef _RWSTD_NO_CLASS_PARTIAL_SPEC
                    void *vdptr = boost::allocator_allocate(alloc_, new_size, is_allocated_? oldptr : 0);
                    newptr = static_cast<Ch *>(vdptr);
#else
                    newptr = boost::allocator_allocate(alloc_, new_size, is_allocated_? oldptr : 0);
#endif
                }

                if(0 < prev_size)
                    compat_traits_type::copy(newptr, oldptr, prev_size);
                if(is_allocated_)
                    alloc_.deallocate(oldptr, prev_size);
                is_allocated_=true;

                if(prev_size == 0) { // first allocation
                    putend_ = newptr;
                    streambuf_t::setp(newptr, newptr + new_size);
                    if(mode_ & ::std::ios_base::in)
                        streambuf_t::setg(newptr, newptr, newptr + 1);
                    else
                        streambuf_t::setg(newptr, 0, newptr);
                }
                else { // update pointers
                    putend_ = putend_ - oldptr + newptr;
                    int pptr_count = static_cast<int>(pptr()-pbase());
                    int gptr_count = static_cast<int>(gptr()-eback());
                    streambuf_t::setp(pbase() - oldptr + newptr, newptr + new_size);
                    streambuf_t::pbump(pptr_count);
                    if(mode_ & ::std::ios_base::in)
                        streambuf_t::setg(newptr, newptr + gptr_count, pptr() + 1);
                    else
                        streambuf_t::setg(newptr, 0, newptr);
                }
                streambuf_t::sputc(compat_traits_type::to_char_type(meta));
                return meta;
            }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
        }
        // -end overflow(..)

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: dealloc() {
            if(is_allocated_)
                alloc_.deallocate(eback(), (pptr() != NULL ? epptr() : egptr()) - eback());
            is_allocated_ = false;
            streambuf_t::setg(0, 0, 0);
            streambuf_t::setp(0, 0);
            putend_ = NULL;
        }

    }// N.S. io
} // N.S. boost

#endif // include guard


/* alt_sstream_impl.hpp
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
*/