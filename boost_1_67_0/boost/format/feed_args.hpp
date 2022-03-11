// ----------------------------------------------------------------------------
//  feed_args.hpp :  functions for processing each argument 
//                      (feed, feed_manip, and distribute)
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_FEED_ARGS_HPP
#define BOOST_FORMAT_FEED_ARGS_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>

#include <boost/format/format_class.hpp>
#include <boost/format/group.hpp>
#include <boost/format/detail/msvc_disambiguater.hpp>

namespace boost {
namespace io {
namespace detail {

    template<class Ch, class Tr, class Alloc>
    void mk_str( std::basic_string<Ch,Tr, Alloc> & res, 
                 const Ch * beg,
                 typename std::basic_string<Ch,Tr,Alloc>::size_type size,
                 std::streamsize w, 
                 const Ch fill_char,
                 std::ios_base::fmtflags f, 
                 const Ch prefix_space, // 0 if no space-padding
                 bool center) 
    // applies centered/left/right  padding  to the string  [beg, beg+size[
    // Effects : the result is placed in res.
    {
        typedef typename std::basic_string<Ch,Tr,Alloc>::size_type size_type;
        res.resize(0);
        if(w<=0 || static_cast<size_type>(w) <=size) {
            // no need to pad.
            res.reserve(size + !!prefix_space);
            if(prefix_space) 
              res.append(1, prefix_space);
            if (size)
              res.append(beg, size);
        }
        else { 
            std::streamsize n=static_cast<std::streamsize>(w-size-!!prefix_space);
            std::streamsize n_after = 0, n_before = 0; 
            res.reserve(static_cast<size_type>(w)); // allocate once for the 2 inserts
            if(center) 
                n_after = n/2, n_before = n - n_after; 
            else 
                if(f & std::ios_base::left)
                    n_after = n;
                else
                    n_before = n;
            // now make the res string :
            if(n_before) res.append(static_cast<size_type>(n_before), fill_char);
            if(prefix_space) 
              res.append(1, prefix_space);
            if (size)  
              res.append(beg, size);
            if(n_after) res.append(static_cast<size_type>(n_after), fill_char);
        }
    } // -mk_str(..) 


#if BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
// __DECCXX needs to be tricked to disambiguate this simple overload..
// the trick is in "boost/format/msvc_disambiguater.hpp"
  
    template< class Ch, class Tr, class T> inline
    void put_head (BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        disambiguater<Ch, Tr, T>::put_head(os, x, 1L);
    }
    template< class Ch, class Tr, class T> inline
    void put_last (BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        disambiguater<Ch, Tr, T>::put_last(os, x, 1L);
    }

#else  

    template< class Ch, class Tr, class T> inline
    void put_head (BOOST_IO_STD basic_ostream<Ch, Tr> &, const T& ) {
    }

    template< class Ch, class Tr, class T> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const group1<T>& x ) {
        os << group_head(x.a1_); // send the first N-1 items, not the last
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const T& x ) {
        os << x ;
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const group1<T>& x ) {
        os << group_last(x.a1_); // this selects the last element
    }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST 
    template< class Ch, class Tr, class T> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr> &, T& ) {
    }

    template< class Ch, class Tr, class T> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, T& x) {
        os << x ;
    }
#endif
#endif  // -__DECCXX workaround

    template< class Ch, class Tr, class T>
    void call_put_head(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x) {
        put_head(os, *(static_cast<T const *>(x)));
    }

    template< class Ch, class Tr, class T>
    void call_put_last(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x) {
        put_last(os, *(static_cast<T const *>(x)));
    }

    template< class Ch, class Tr>
    struct put_holder {
        template<class T>
        put_holder(T& t)
          : arg(&t),
            put_head(&call_put_head<Ch, Tr, T>),
            put_last(&call_put_last<Ch, Tr, T>)
        {}
        const void* arg;
        void (*put_head)(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x);
        void (*put_last)(BOOST_IO_STD basic_ostream<Ch, Tr> & os, const void* x);
    };
    
    template< class Ch, class Tr> inline
    void put_head( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const put_holder<Ch, Tr>& t) {
        t.put_head(os, t.arg);
    }
    
    template< class Ch, class Tr> inline
    void put_last( BOOST_IO_STD basic_ostream<Ch, Tr> & os, const put_holder<Ch, Tr>& t) {
        t.put_last(os, t.arg);
    }


    template< class Ch, class Tr, class Alloc, class T> 
    void put( T x, 
              const format_item<Ch, Tr, Alloc>& specs, 
              typename basic_format<Ch, Tr, Alloc>::string_type& res, 
              typename basic_format<Ch, Tr, Alloc>::internal_streambuf_t & buf,
              io::detail::locale_t *loc_p = NULL)
    {
#ifdef BOOST_MSVC
       // If std::min<unsigned> or std::max<unsigned> are already instantiated
       // at this point then we get a blizzard of warning messages when we call
       // those templates with std::size_t as arguments.  Weird and very annoyning...
#pragma warning(push)
#pragma warning(disable:4267)
#endif
        // does the actual conversion of x, with given params, into a string
        // using the supplied stringbuf.

        typedef typename basic_format<Ch, Tr, Alloc>::string_type   string_type;
        typedef typename basic_format<Ch, Tr, Alloc>::format_item_t format_item_t;
        typedef typename string_type::size_type size_type;

        basic_oaltstringstream<Ch, Tr, Alloc>  oss( &buf);

#if !defined(BOOST_NO_STD_LOCALE)
        if(loc_p != NULL)
            oss.imbue(*loc_p);
#endif

        specs.fmtstate_.apply_on(oss, loc_p);

        // the stream format state can be modified by manipulators in the argument :
        put_head( oss, x );
        // in case x is a group, apply the manip part of it, 
        // in order to find width

        const std::ios_base::fmtflags fl=oss.flags();
        const bool internal = (fl & std::ios_base::internal) != 0;
        const std::streamsize w = oss.width();
        const bool two_stepped_padding= internal && (w!=0);
      
        res.resize(0);
        if(! two_stepped_padding) {
            if(w>0) // handle padding via mk_str, not natively in stream 
                oss.width(0);
            put_last( oss, x);
            const Ch * res_beg = buf.pbase();
            Ch prefix_space = 0;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if(buf.pcount()== 0 || 
                   (res_beg[0] !=oss.widen('+') && res_beg[0] !=oss.widen('-')  ))
                    prefix_space = oss.widen(' ');
            size_type res_size = (std::min)(
                (static_cast<size_type>((specs.truncate_ & (std::numeric_limits<size_type>::max)())) - !!prefix_space), 
                buf.pcount() );
            mk_str(res, res_beg, res_size, w, oss.fill(), fl, 
                   prefix_space, (specs.pad_scheme_ & format_item_t::centered) !=0 );
        }
        else  { // 2-stepped padding
            // internal can be implied by zeropad, or user-set.
            // left, right, and centered alignment overrule internal,
            // but spacepad or truncate might be mixed with internal (using manipulator)
            put_last( oss, x); // may pad
            const Ch * res_beg = buf.pbase();
            size_type res_size = buf.pcount();
            bool prefix_space=false;
            if(specs.pad_scheme_ & format_item_t::spacepad)
                if(buf.pcount()== 0 || 
                   (res_beg[0] !=oss.widen('+') && res_beg[0] !=oss.widen('-')  ))
                    prefix_space = true;
            if(res_size == static_cast<size_type>(w) && w<=specs.truncate_ && !prefix_space) {
                // okay, only one thing was printed and padded, so res is fine
                res.assign(res_beg, res_size);
            }
            else { //   length w exceeded
                // either it was multi-output with first output padding up all width..
                // either it was one big arg and we are fine.
                // Note that res_size<w is possible  (in case of bad user-defined formatting)
                res.assign(res_beg, res_size);
                res_beg=NULL;  // invalidate pointers.
                
                // make a new stream, to start re-formatting from scratch :
                buf.clear_buffer();
                basic_oaltstringstream<Ch, Tr, Alloc>  oss2( &buf);
                specs.fmtstate_.apply_on(oss2, loc_p);
                put_head( oss2, x );

                oss2.width(0);
                if(prefix_space)
                    oss2 << ' ';
                put_last(oss2, x );
                if(buf.pcount()==0 && specs.pad_scheme_ & format_item_t::spacepad) {
                    prefix_space =true;
                    oss2 << ' ';
                }
                // we now have the minimal-length output
                const Ch * tmp_beg = buf.pbase();
                size_type tmp_size = (std::min)(
                    (static_cast<size_type>(specs.truncate_ & (std::numeric_limits<size_type>::max)())),
                    buf.pcount());
                
                if(static_cast<size_type>(w) <= tmp_size) { 
                    // minimal length is already >= w, so no padding (cool!)
                        res.assign(tmp_beg, tmp_size);
                }
                else { // hum..  we need to pad (multi_output, or spacepad present)
                    //find where we should pad
                    size_type sz = (std::min)(res_size + (prefix_space ? 1 : 0), tmp_size);
                    size_type i = prefix_space;
                    for(; i<sz && tmp_beg[i] == res[i - (prefix_space ? 1 : 0)]; ++i) {}
                    if(i>=tmp_size) i=prefix_space;
                    res.assign(tmp_beg, i);
                                        std::streamsize d = w - static_cast<std::streamsize>(tmp_size);
                                        BOOST_ASSERT(d>0);
                    res.append(static_cast<size_type>( d ), oss2.fill());
                    res.append(tmp_beg+i, tmp_size-i);
                    BOOST_ASSERT(i+(tmp_size-i)+(std::max)(d,(std::streamsize)0) 
                                 == static_cast<size_type>(w));
                    BOOST_ASSERT(res.size() == static_cast<size_type>(w));
                }
            }
        }
        buf.clear_buffer();
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    } // end- put(..)


    template< class Ch, class Tr, class Alloc, class T> 
    void distribute (basic_format<Ch,Tr, Alloc>& self, T x) {
        // call put(x, ..) on every occurrence of the current argument :
        if(self.cur_arg_ >= self.num_args_)  {
            if( self.exceptions() & too_many_args_bit )
                boost::throw_exception(too_many_args(self.cur_arg_, self.num_args_)); 
            else return;
        }
        for(unsigned long i=0; i < self.items_.size(); ++i) {
            if(self.items_[i].argN_ == self.cur_arg_) {
                put<Ch, Tr, Alloc, T> (x, self.items_[i], self.items_[i].res_, 
                                self.buf_, boost::get_pointer(self.loc_) );
            }
        }
    }

    template<class Ch, class Tr, class Alloc, class T> 
    basic_format<Ch, Tr, Alloc>&  
    feed_impl (basic_format<Ch,Tr, Alloc>& self, T x) {
        if(self.dumped_) self.clear();
        distribute<Ch, Tr, Alloc, T> (self, x);
        ++self.cur_arg_;
        if(self.bound_.size() != 0) {
                while( self.cur_arg_ < self.num_args_ && self.bound_[self.cur_arg_] )
                    ++self.cur_arg_;
        }
        return self;
    }

    template<class Ch, class Tr, class Alloc, class T> inline
    basic_format<Ch, Tr, Alloc>&  
    feed (basic_format<Ch,Tr, Alloc>& self, T x) {
        return feed_impl<Ch, Tr, Alloc, const put_holder<Ch, Tr>&>(self, put_holder<Ch, Tr>(x));
    }
    
} // namespace detail
} // namespace io
} // namespace boost


#endif //  BOOST_FORMAT_FEED_ARGS_HPP

/* feed_args.hpp
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
*/